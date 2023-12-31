#ifndef __MY_WS2812_H__
#define __MY_WS2812_H__
#include <stdint.h>

void ws2812_init(int gpio, int matrix_w, int matrix_h);
void ws2812_deinit(void);
void ws2812_darw_point(int x, int y, uint32_t color);
void ws2812_read_point(int x, int y, uint32_t *color);
void ws2812_fill(uint32_t color);
void ws2812_refresh(void);
void ws2812_test(void);
void ws2812_hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b);
uint8_t ws2812_get_brightness(void);
void ws2812_set_brightness(uint8_t brightness);

#endif /*__WS2812_H__*/