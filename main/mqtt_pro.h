#ifndef _MQTT_PRO_H_
#define _MQTT_PRO_H_
#include "mqtt_client.h"

// MQTT 
#define MQTT_SERVER_HOST    "www.lixiangjun.work"
#define MQTT_SERVER_PORT    1883
#define MQTT_USERNAME       "admin"
#define MQTT_PASSWORKD      "public"

esp_mqtt_client_handle_t mqtt_init(esp_mqtt_client_config_t *mqtt_cfg, esp_event_handler_t event_handler, void* event_handler_arg);
void mqtt_deinit(esp_mqtt_client_handle_t client);

#endif /* _MQTT_PRO_H_ */