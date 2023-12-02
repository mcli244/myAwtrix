#ifndef __HSV2RGB_H__
#define __HSV2RGB_H__


/**
 * @brief HSV颜色空间
*/
typedef struct {
    float h;    // 色调H(hue)  0~360° {R(0°),G(120°),B(240°)}
    float s;    // 饱和度S(saturation)  0~1.0
    float v;    // 明度V(value)  0~1.0  
}color_hsv_t;

typedef struct {
    unsigned char r;    // 0-255
    unsigned char g;    // 0-255
    unsigned char b;    // 0-255
    unsigned int color; // 0x000000 ~ 0xffffff
}color_rgb_t;


/**
 * @brief   RGB颜色空间 转  HSV颜色空间 
 * @param   rgb:RGB颜色空间参数
 * @param   hsv:HSV颜色空间参数
 * @return  none
*/
void rgb2hsv(color_rgb_t *rgb, color_hsv_t *hsv);

/**
 * @brief   HSV颜色空间 转 RGB颜色空间
 * @param   hsv:HSV颜色空间参数
 * @param   rgb:RGB颜色空间参数
 * @return  none
*/
void hsv2rgb(color_hsv_t *hsv, color_rgb_t *rgb);

/**
 * @brief   调节HSV颜色空间 H值(0.0~360.0)
 * @param   hsv:HSV颜色空间参数
 * @param   h_offset:调节参数 增加>0.0，减小<0.0
 * @return  none
*/
void hsv_adjust_h(color_hsv_t *hsv, float h_offset);

/**
 * @brief   调节HSV颜色空间 S值(0.0~1.0)
 * @param   hsv:HSV颜色空间参数
 * @param   s_offset:调节参数 增加>0.0，减小<0.0
 * @return  none
*/
void hsv_adjust_s(color_hsv_t *hsv, float s_offset);

/**
 * @brief   调节HSV颜色空间 V值(0.0~1.0)
 * @param   hsv:HSV颜色空间参数
 * @param   v_offset:调节参数 增加>0.0，减小<0.0
 * @return  none
*/
void hsv_adjust_v(color_hsv_t *hsv, float v_offset);




#endif /*__HSV2RGB_H__*/