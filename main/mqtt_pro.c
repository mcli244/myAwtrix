#include "mqtt_pro.h"

esp_mqtt_client_handle_t client = NULL;

esp_mqtt_client_handle_t mqtt_init(esp_mqtt_client_config_t *mqtt_cfg, esp_event_handler_t event_handler, void* event_handler_arg)
{
    // esp_mqtt_client_handle_t client;
    client = esp_mqtt_client_init(mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, event_handler, event_handler_arg);
    esp_mqtt_client_start(client);

    return client;
}

void mqtt_deinit(esp_mqtt_client_handle_t pclient)
{
    esp_mqtt_client_disconnect(pclient);
}




