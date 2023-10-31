#ifndef _WIFI_H_
#define _WIFI_H_

#include "esp_wifi.h"

#define MY_WIFI_SSID    "Redmi_4A7E" 
#define MY_WIFI_PASSWORD    "0xbadbeef"

void wifi_init(esp_event_handler_t cb, const char *ssid, const char *password);

#endif /* _WIFI_H_ */