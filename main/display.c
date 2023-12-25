#include "display.h"
#include "zlg_gui.h"
#include "pic.h"
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void display_init(void)
{
    GUI_Initialize();
    GUI_SetColor(0x00ff00, 0);
    GUI_SetBrightness(10);  // 10的亮度， 显示disp_time_week_pic 大致在400mA左右
    GUI_PutString(0, 0, "Test1234");
    GUI_Refresh();
}

void disp_time_week(uint8_t hour, uint8_t min, uint8_t sec, uint8_t week)
{
    TCOLOR color = 0;
    // TCOLOR clock_color = 0x0FAAD1;
    // TCOLOR week_color = 0x00B350;
    // TCOLOR week_bg_color = 0xDE1D5A;
    TCOLOR clock_color = 0x042a33;
    TCOLOR week_color = 0x003317;
    TCOLOR week_bg_color = 0x330715;

    GUI_GetDispColor(&color);

    GUI_SetColor(clock_color, 0);
    GUI_LoadPic(2, 1, &number_3x5[hour/10][0], 3, 5);
    GUI_LoadPic(6, 1, &number_3x5[hour%10][0], 3, 5);

    GUI_Point(10, 2, clock_color);
    GUI_Point(10, 4, clock_color);

    GUI_LoadPic(12, 1, &number_3x5[min/10][0], 3, 5);
    GUI_LoadPic(16, 1, &number_3x5[min%10][0], 3, 5);

    GUI_Point(20, 2, clock_color);
    GUI_Point(20, 4, clock_color);

    GUI_LoadPic(22, 1, &number_3x5[sec/10][0], 3, 5);
    GUI_LoadPic(26, 1, &number_3x5[sec%10][0], 3, 5);

    // week
    for(int i=0; i<7; i++)
    {
        if(week - 1 == i)
            GUI_HLine(i*4 + 2, 7, i*4 + 4, week_color);
        else
            GUI_HLine(i*4 + 2, 7, i*4 + 4, week_bg_color);
    }
        
    GUI_SetColor(color, 0);
}



// 显示一个8x8的图片+时间和周末
void disp_time_week_pic(uint8_t hour, uint8_t min, uint8_t sec, uint8_t week)
{
    TCOLOR color = 0;
    TCOLOR clock_color = 0x042a33;
    TCOLOR week_color = 0x003317;
    TCOLOR week_bg_color = 0x330715;
    static uint8_t sec_bak = 0;
    static uint8_t state = 0;
    static uint8_t cnt = 0;
    static uint8_t brightness = 100;

    GUI_GetDispColor(&color);

    if(cnt++ > 2) 
    {
        cnt = 0;
        GUI_LoadPicRGB(0, 0, gImage_zy4, 8, 8);
        srand(time(0));
        state = rand() % 11;
    }
    
    switch (state)
    {
    case 0: GUI_LoadPicRGB(0, 0, gImage_zy1, 8, 8); break;
    case 1: GUI_LoadPicRGB(0, 0, gImage_zy2, 8, 8); break;
    case 2: GUI_LoadPicRGB(0, 0, gImage_zy3, 8, 8); break; 
    case 3: GUI_LoadPicRGB(0, 0, gImage_zy4, 8, 8); break;   
    case 4: GUI_LoadPicRGB(0, 0, gImage_boom, 8, 8); break;   
    case 5: GUI_LoadPicRGB(0, 0, gImage_sun, 8, 8); break;   
    case 6: GUI_LoadPicRGB(0, 0, gImage_sun2cloudy, 8, 8); break;   
    case 7: GUI_LoadPicRGB(0, 0, gImage_rain_s, 8, 8); break;   
    case 8: GUI_LoadPicRGB(0, 0, gImage_rain_l, 8, 8); break;   
    case 9: GUI_LoadPicRGB(0, 0, gImage_rain_m, 8, 8); break; 
    case 10: GUI_LoadPicRGB(0, 0, gImage_rain_flash, 8, 8); break;
    default:
        break;
    }
    
    
    GUI_SetColor(clock_color, 0);
    GUI_LoadPic(11, 1, &number_3x5[hour/10][0], 3, 5);
    GUI_LoadPic(15, 1, &number_3x5[hour%10][0], 3, 5);

    sec_bak = !sec_bak;
    if(sec_bak)
    {
        GUI_Point(19, 2, clock_color);
        GUI_Point(19, 4, clock_color);
    }
    else
    {
        GUI_Point(19, 2, 0);
        GUI_Point(19, 4, 0);
    }
    

    GUI_LoadPic(21, 1, &number_3x5[min/10][0], 3, 5);
    GUI_LoadPic(25, 1, &number_3x5[min%10][0], 3, 5);

    // week
    for(int i=0; i<7; i++)
    {
        if(week - 1 == i)
            GUI_HLine(i*3 + 10, 7, i*3 + 11, week_color);
        else
            GUI_HLine(i*3 + 10, 7, i*3 + 11, week_bg_color);
    }
        
    GUI_SetColor(color, 0);
}

enum DISPLAY_TYPE{
    DT_START,
    DT_TIME_WEEK,
    DT_WIFI_CONNECTING,
    DT_WIFI_CONNECTED,
};

static enum DISPLAY_TYPE dtype = DT_TIME_WEEK;

// TODO:留给外部向display_task 发信号，来切换显示case

void display_task(void *pvParameter)
{
    time_t timer0 = 0;
    time_t timer_bak = 0xff;
    while(1)
    {
        switch(dtype)
        {
            case DT_START:
            case DT_WIFI_CONNECTING:
            case DT_WIFI_CONNECTED:
            case DT_TIME_WEEK:
            default:
                timer0 = time(NULL);
                if(timer0 != timer_bak)
                {
                    timer_bak = timer0;
                    struct tm* plocaltime = localtime(&timer0);

                    GUI_ClearSCR();
                    disp_time_week_pic(plocaltime->tm_hour, plocaltime->tm_min, plocaltime->tm_sec, plocaltime->tm_wday);
                    //disp_time_week(plocaltime->tm_hour, plocaltime->tm_min, plocaltime->tm_sec, plocaltime->tm_wday);
                    GUI_Refresh();

                }
                vTaskDelay(pdMS_TO_TICKS(200));
                break;
        }
	    vTaskDelay(pdMS_TO_TICKS(10));
    }
}


