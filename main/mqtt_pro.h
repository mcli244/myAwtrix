#ifndef _MQTT_PRO_H_
#define _MQTT_PRO_H_
#include "mqtt_client.h"

// MQTT 
#define MQTT_SERVER_HOST    "www.lixiangjun.work"
#define MQTT_SERVER_PORT    1883
#define MQTT_USERNAME       "admin"
#define MQTT_PASSWORKD      "public"

// MQTT topic
#define CATBOX_TX_COM_TOPIC "home/myAwtrix_TX"
#define CATBOX_TX_INFO_TOPIC "home/myAwtrix_TX/Info"
#define CATBOX_TX_TEST_TOPIC "home/myAwtrix_TX/test"
#define CATBOX_RX_COM_TOPIC "home/myAwtrix_RX"


esp_mqtt_client_handle_t mqtt_init(esp_mqtt_client_config_t *mqtt_cfg, esp_event_handler_t event_handler, void* event_handler_arg);
void mqtt_deinit(esp_mqtt_client_handle_t client);
void mqtt_pro_init(void);

#endif /* _MQTT_PRO_H_ */