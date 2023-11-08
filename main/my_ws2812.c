/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt_tx.h"
#include "led_strip_encoder.h"
#include "my_ws2812.h"


#define RMT_LED_STRIP_RESOLUTION_HZ 10000000 // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define RMT_LED_STRIP_GPIO_NUM      10

#define EXAMPLE_LED_NUMBERS         32*8
#define EXAMPLE_CHASE_SPEED_MS      10

static const char *TAG = "example";

// static uint8_t g_led.led_strip_pixels[EXAMPLE_LED_NUMBERS * 3];


struct led_info
{
    uint8_t *led_strip_pixels;
    uint32_t led_strip_pixels_bytes;
    uint32_t led_num;
    rmt_channel_handle_t led_chan;
    rmt_encoder_handle_t led_encoder;
    uint32_t led_matrix_w;
    uint32_t led_matrix_h;
    uint8_t initialized;
};

struct led_info g_led;


/**
 * @brief Simple helper function, converting HSV color space to RGB color space
 *
 * Wiki: https://en.wikipedia.org/wiki/HSL_and_HSV
 *
 */
void led_strip_hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b)
{
    h %= 360; // h -> [0,360]
    uint32_t rgb_max = v * 2.55f;
    uint32_t rgb_min = rgb_max * (100 - s) / 100.0f;

    uint32_t i = h / 60;
    uint32_t diff = h % 60;

    // RGB adjustment amount by hue
    uint32_t rgb_adj = (rgb_max - rgb_min) * diff / 60;

    switch (i) {
    case 0:
        *r = rgb_max;
        *g = rgb_min + rgb_adj;
        *b = rgb_min;
        break;
    case 1:
        *r = rgb_max - rgb_adj;
        *g = rgb_max;
        *b = rgb_min;
        break;
    case 2:
        *r = rgb_min;
        *g = rgb_max;
        *b = rgb_min + rgb_adj;
        break;
    case 3:
        *r = rgb_min;
        *g = rgb_max - rgb_adj;
        *b = rgb_max;
        break;
    case 4:
        *r = rgb_min + rgb_adj;
        *g = rgb_min;
        *b = rgb_max;
        break;
    default:
        *r = rgb_max;
        *g = rgb_min;
        *b = rgb_max - rgb_adj;
        break;
    }
}

void ws2812_hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b)
{
    led_strip_hsv2rgb(h, s, v, r, g, b);
}

void ws2812_init(int gpio, int matrix_w, int matrix_h)
{
    ESP_LOGI(TAG, "Create RMT TX channel");
    if(g_led.initialized)   return;
    g_led.led_matrix_w = matrix_w;
    g_led.led_matrix_h = matrix_h;
    g_led.led_num = g_led.led_matrix_w*g_led.led_matrix_h;
    g_led.led_strip_pixels_bytes = g_led.led_num * 3;

    g_led.led_strip_pixels = (uint8_t *)malloc(g_led.led_strip_pixels_bytes);
    assert(g_led.led_strip_pixels);
    memset(g_led.led_strip_pixels, 0, g_led.led_strip_pixels_bytes);
    
    rmt_tx_channel_config_t tx_chan_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT, // select source clock
        .gpio_num = gpio,
        .mem_block_symbols = 64, // increase the block size can make the LED less flickering
        .resolution_hz = RMT_LED_STRIP_RESOLUTION_HZ,
        .trans_queue_depth = 4, // set the number of transactions that can be pending in the background
    };
    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &g_led.led_chan));

    ESP_LOGI(TAG, "Install led strip encoder");
    led_strip_encoder_config_t encoder_config = {
        .resolution = RMT_LED_STRIP_RESOLUTION_HZ,
    };
    ESP_ERROR_CHECK(rmt_new_led_strip_encoder(&encoder_config, &g_led.led_encoder));

    ESP_LOGI(TAG, "Enable RMT TX channel");
    ESP_ERROR_CHECK(rmt_enable(g_led.led_chan));

    g_led.initialized = 1;
}

void ws2812_deinit(void)
{
    if(!g_led.initialized) return;
    ESP_LOGI(TAG, "ws2812_deinit");
    free(g_led.led_strip_pixels);
    memset(&g_led, 0, sizeof(struct led_info));
    g_led.initialized = 0;
}

/* 
    0 8 16 24 32 
    1 
    2
    3
    4
    5
    6
    7
*/
void ws2812_darw_point(int x, int y, uint32_t color)
{
    if(!g_led.initialized) return;
    // GRB
    g_led.led_strip_pixels[(x*8 + y)*3 + 1] = color>>16&0xff;
    g_led.led_strip_pixels[(x*8 + y)*3 + 0] = color>>8&0xff;
    g_led.led_strip_pixels[(x*8 + y)*3 + 2] = color&0xff;
}

void ws2812_fill(uint32_t color)
{
    if(!g_led.initialized) return;
    for(int i=0; i<g_led.led_num; i++)
    {
        g_led.led_strip_pixels[i* 3 + 1] = color>>16&0xff;
        g_led.led_strip_pixels[i* 3 + 0] = color>>8&0xff;
        g_led.led_strip_pixels[i* 3 + 2] = color&0xff;
    }
}

void ws2812_refresh(void)
{
    if(!g_led.initialized) return;
    rmt_transmit_config_t tx_config = {
            .loop_count = 0, // no transfer loop
        };
    ESP_ERROR_CHECK(rmt_transmit(g_led.led_chan, g_led.led_encoder, g_led.led_strip_pixels, g_led.led_strip_pixels_bytes, &tx_config));
    ESP_ERROR_CHECK(rmt_tx_wait_all_done(g_led.led_chan, portMAX_DELAY));
}

void ws2812_test(void)
{
    uint32_t red = 0;
    uint32_t green = 0;
    uint32_t blue = 0;
    uint16_t hue = 0;
    uint16_t start_rgb = 0;

    rmt_transmit_config_t tx_config = {
        .loop_count = 0, // no transfer loop
    };

    ws2812_init(10, 32, 8);

    ESP_LOGI(TAG, "Start LED rainbow chase");
    while (1) {
        for (int i = 0; i < 3; i++) {
            for (int j = i; j < EXAMPLE_LED_NUMBERS; j += 3) {
                // Build RGB pixels
                hue = j * 360 / EXAMPLE_LED_NUMBERS + start_rgb;
                led_strip_hsv2rgb(hue, 100, 100, &red, &green, &blue);
                g_led.led_strip_pixels[j * 3 + 0] = green;
                g_led.led_strip_pixels[j * 3 + 1] = blue;
                g_led.led_strip_pixels[j * 3 + 2] = red;
            }
            // Flush RGB values to LEDs
            ESP_ERROR_CHECK(rmt_transmit(g_led.led_chan, g_led.led_encoder, g_led.led_strip_pixels, 32*8*3, &tx_config));
            ESP_ERROR_CHECK(rmt_tx_wait_all_done(g_led.led_chan, portMAX_DELAY));
            vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
            memset(g_led.led_strip_pixels, 0, 32*8);
            ESP_ERROR_CHECK(rmt_transmit(g_led.led_chan, g_led.led_encoder, g_led.led_strip_pixels, 32*8*3, &tx_config));
            ESP_ERROR_CHECK(rmt_tx_wait_all_done(g_led.led_chan, portMAX_DELAY));
            vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
        }
        start_rgb += 60;
    }
}
