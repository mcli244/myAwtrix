//-------以下是HSV颜色空间和RGB颜色空间相互转换接口------------
#include "hsv2rgb.h"
#include <math.h>

// 以下是HSV颜色空间和RGB颜色空间相互转换接口
/*********************************************************************************************
红：    
    R   255         H:0
    G   0           S:100
    B   0           V:100    
绿：
    R   0           H:120   
    G   255         S:100
    B   0           V:100    
蓝：
    R   0           H:240   
    G   0           S:100
    B   255         V:100    
*********************************************************************************************/

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max3(a,b,c) (((a) > (b) ? (a) : (b)) > (c) ? ((a) > (b) ? (a) : (b)) : (c))
#define min3(a,b,c) (((a) < (b) ? (a) : (b)) < (c) ? ((a) < (b) ? (a) : (b)) : (c))


/*********************************************************************************************
RGB转化到HSV的算法:
    max=max(R,G,B)；
    min=min(R,G,B)；
    V=max(R,G,B)；
    S=(max-min)/max；
    if (R = max) H =(G-B)/(max-min)* 60；
    if (G = max) H = 120+(B-R)/(max-min)* 60；
    if (B = max) H = 240 +(R-G)/(max-min)* 60；
    if (H < 0) H = H + 360；
***********************************************************************************************/

/**
 * @brief   RGB颜色空间 转  HSV颜色空间 
 * @param   rgb:RGB颜色空间参数
 * @param   hsv:HSV颜色空间参数
 * @note    The R,G,B values are divided by 255 to change the range from 0..255 to 0..1:
 * @return  none
*/
void rgb2hsv(color_rgb_t *rgb, color_hsv_t *hsv)
{
    float max, min, delta=0;
    float r = (float)((float)((int)rgb->r)/255);
    float g = (float)((float)((int)rgb->g)/255);
    float b = (float)((float)((int)rgb->b)/255);

    max = max3(r, g, b);
    min = min3(r, g, b);
    delta = (max - min);

    //printf("r:%f, g:%f, b:%f\n", r, g, b);

    if (delta == 0) {
        hsv->h = 0;
    } else {
        if (r == max) {
            hsv->h = ((g-b)/delta)*60; 
        } else if (g == max) {
            hsv->h = 120+(((b-r)/delta)*60); 
        } else if (b == max) {
            hsv->h = 240 + (((r-g)/delta)*60);
        }

        if (hsv->h < 0) {
            hsv->h += 360;
        }
    }

    if (max == 0) {
        hsv->s = 0;
    } else {
        hsv->s = (float)(delta/max);
    }

    hsv->v = max;

    rgb->color = (unsigned int)(((rgb->r&0xff)<<16) | ((rgb->g&0xff)<<8) | (rgb->b&0xff));
}


/*************************************************************************
HSV转化到RGB的算法:
    if (s = 0)
    R=G=B=V;
    else
    H /= 60;
    i = INTEGER(H);
    f = H - i;
    a = V * ( 1 - s );
    b = V * ( 1 - s * f );
    c = V * ( 1 - s * (1 - f ) );
    switch(i)
    case 0: R = V; G = c; B = a;
    case 1: R = b; G = v; B = a;
    case 2: R = a; G = v; B = c;
    case 3: R = a; G = b; B = v;
    case 4: R = c; G = a; B = v;
    case 5: R = v; G = a; B = b;
*******************************************************************************/

/**
 * @brief   HSV颜色空间 转 RGB颜色空间
 * @param   hsv:HSV颜色空间参数
 * @param   rgb:RGB颜色空间参数
 * @note    When 0 ≤ H < 360, 0 ≤ S ≤ 1 and 0 ≤ V ≤ 1:
 * @return  none
*/
void hsv2rgb(color_hsv_t *hsv, color_rgb_t *rgb)
{
    int i;
    float f,a,b,c;

    float h = hsv->h;
    float s = hsv->s;
    float v = hsv->v;
	if (h >= 360) {
		h = 0;
	}
	
    if (s == 0) {
        rgb->r = (unsigned char)((int)(v*255));
        rgb->g = (unsigned char)((int)(v*255));
        rgb->b = (unsigned char)((int)(v*255));
    } else {
        h /= 60.0;  // sector 0 to 5, h_max=360 360/60=6[0,1,2,3,4,5]
        i = (int)floor(h); // floor(h)
        f = h-i; // factorial path of h
        a = v * (1-s);
        b = v * (1-s*f);
        c = v * (1-s*(1-f));
        switch(i) {
            case 0:
                rgb->r = (unsigned char)((int)(v*255)); //v*255
                rgb->g = (unsigned char)((int)(c*255)); //c*255;
                rgb->b = (unsigned char)((int)(a*255)); //a*255;
                break;
            case 1:
                rgb->r = (unsigned char)((int)(b*255)); //b*255;
                rgb->g = (unsigned char)((int)(v*255)); //v*255;
                rgb->b = (unsigned char)((int)(a*255)); //a*255;
                break;
            case 2:
                rgb->r = (unsigned char)((int)(a*255)); //a*255;
                rgb->g = (unsigned char)((int)(v*255)); //v*255;
                rgb->b = (unsigned char)((int)(c*255)); //c*255;
                break;
            case 3:
                rgb->r = (unsigned char)((int)(a*255));//a*255;
                rgb->g = (unsigned char)((int)(b*255));//b*255;
                rgb->b = (unsigned char)((int)(v*255));//v*255;
                break;
            case 4:
                rgb->r = (unsigned char)((int)(c*255)); //c*255;
                rgb->g = (unsigned char)((int)(a*255)); //a*255;
                rgb->b = (unsigned char)((int)(v*255)); //v*255;
                break;
            default:
                rgb->r = (unsigned char)((int)(v*255)); //v*255;
                rgb->g = (unsigned char)((int)(a*255)); //a*255;
                rgb->b = (unsigned char)((int)(b*255)); //b*255;
                break;
        }

    }

    rgb->color = (unsigned int)(((rgb->r&0xff)<<16) | ((rgb->g&0xff)<<8) | (rgb->b&0xff));
}

/**
 * @brief   调节HSV颜色空间 H值(0.0~360.0)
 * @param   hsv:HSV颜色空间参数
 * @param   h_offset:调节参数 增加>0.0，减小<0.0
 * @return  none
*/
void hsv_adjust_h(color_hsv_t *hsv, float h_offset)
{
    hsv->h += h_offset;
    if (hsv->h >= 360) {
        hsv->h = 360;
    } else if (hsv->h<=0) {
        hsv->h = 0;
    }
}


/**
 * @brief   调节HSV颜色空间 S值(0.0~1.0)
 * @param   hsv:HSV颜色空间参数
 * @param   s_offset:调节参数 增加>0.0，减小<0.0
 * @return  none
*/
void hsv_adjust_s(color_hsv_t *hsv, float s_offset)
{
    hsv->s += s_offset;
    if (hsv->s >= 1.0) {
        hsv->s = 1.0;
    } else if (hsv->s <= 0) {
        hsv->s = 0;
    }
}


/**
 * @brief   调节HSV颜色空间 V值(0.0~1.0)
 * @param   hsv:HSV颜色空间参数
 * @param   v_offset:调节参数 增加>0.0，减小<0.0
 * @return  none
*/
void hsv_adjust_v(color_hsv_t *hsv, float v_offset)
{
    hsv->v += v_offset;
    if (hsv->v >= 1.0) {
        hsv->v = 1.0;
    } else if (hsv->v<=0) {
        hsv->v = 0;
    }
}

#if 0
//  测试代码
static color_hsv_t hsv;
static color_hsv_t tmp_hsv；
static color_rgb_t rgb;

// 调节H的值整数增加，负数减小
hsv_adjust_h(&hsv, 10.0);
hsv_adjust_h(&hsv, -10.0);

// 调节S的值整数增加，负数减小
hsv_adjust_s(&hsv, 0.05);
hsv_adjust_s(&hsv, -0.05);

// 调节S的值整数增加，负数减小
hsv_adjust_v(&hsv, 0.05);
hsv_adjust_v(&hsv, -0.05);

// HSV颜色空间转RGB颜色空间
hsv.h = 0;      // 色调H(hue)  0~360° {R(0°),G(120°),B(240°)}
hsv.s = 0.5;    // 饱和度S(saturation)  0~1.0
hsv.v = 1;      // 亮度V(value)  0~1.0  
hsv2rgb(&hsv, &rgb);
printf("h:%f, s:%f, v:%f,  r:%d, g:%d, b:%d, color:0x%06x\n", hsv.h, hsv.s, hsv.v, rgb.r, rgb.g, rgb.b, rgb.color);

// RGB颜色空间转HSV颜色空间
rgb.r = 0xff;   // Red 0~255
rgb.g = 0x00;   // Green 0~255
rgb.b = 0x00;   // Blue 0~255
rgb2hsv(&rgb, &tmp_hsv);
printf("h:%f, s:%f, v:%f\n\n", tmp_hsv.h, tmp_hsv.s, tmp_hsv.v);
#endif
