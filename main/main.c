/* OTA example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "protocol_examples_common.h"
#include "string.h"
#ifdef CONFIG_EXAMPLE_USE_CERT_BUNDLE
#include "esp_crt_bundle.h"
#endif
#include "nvs.h"
#include "nvs_flash.h"
#include <sys/socket.h>
#include "esp_wifi.h"
#include "esp_sntp.h"
#include "mqtt_pro.h"
#include "freertos/event_groups.h"
#include "smartconfig_wifi.h"
#include "driver/gpio.h"
#include "display.h"


static const char *TAG = "main";

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "Notification of a time synchronization event");
}


void wifi_clear_check(void)
{
    int cnt = 0;
    gpio_reset_pin(5);
    gpio_set_direction(5, GPIO_MODE_INPUT);
    gpio_set_pull_mode(5, GPIO_PULLUP_ONLY);

    do{
        cnt++;
        vTaskDelay(pdMS_TO_TICKS(100));
        if(cnt >= 30)
        {
            ESP_LOGW(TAG, "esp_wifi_restore.. ");
            // Initialize NVS
            esp_err_t err = nvs_flash_init();
            if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
                ESP_ERROR_CHECK(nvs_flash_erase());
                err = nvs_flash_init();
            }
            ESP_ERROR_CHECK( err );
            wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
            ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
            ESP_ERROR_CHECK(esp_wifi_restore());
            break;
        }
    }while(0 == gpio_get_level(5));
}

void sntp_pro_init(void)
{
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "time2.cloud.tencent.com");
    sntp_setservername(1, "ntp.aliyun.com");
    sntp_setservername(2, "ntp.ntsc.ac.cn");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    setenv("TZ", "CST-8", 1);
    tzset();
    sntp_init();    
}

void wifi_init(void)
{
    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );
    wifi_clear_check();
    smartconfig_app_main();
}

void app_main(void)
{
    display_init();
    wifi_init();
    sntp_pro_init();
    mqtt_pro_init();

    xTaskCreate(&display_task, "display_task", 8192, NULL, 5, NULL);
    while(1)
    {
        ESP_LOGI(TAG, "mimi.. ");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        
    }
}
