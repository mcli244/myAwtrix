#include "mqtt_pro.h"
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
#include "nvs.h"
#include "nvs_flash.h"
#include <sys/socket.h>
#include "esp_wifi.h"
#include "cJSON.h"
#include "app_version.h"

extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");
#ifdef CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF
/* The interface name value can refer to if_desc in esp_netif_defaults.h */
#if CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF_ETH
static const char *bind_interface_name = "eth";
#elif CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF_STA
static const char *bind_interface_name = "sta";
#endif
#endif

#ifdef CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF
/* The interface name value can refer to if_desc in esp_netif_defaults.h */
#if CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF_ETH
static const char *bind_interface_name = EXAMPLE_NETIF_DESC_ETH;
#elif CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF_STA
static const char *bind_interface_name = EXAMPLE_NETIF_DESC_STA;
#endif
#endif

#define OTA_URL_SIZE 256

static const char *TAG = "mqtt_pro";
static int mqtt_is_connected = 0;
static uint8_t macaddr[6];

static char help[]={

};

typedef struct
{
    char url[OTA_URL_SIZE];
    esp_mqtt_event_handle_t event;
}OTA_TaskInfo;
// OTA相关
OTA_TaskInfo ota_task_info;

esp_mqtt_client_handle_t mqtt_client = NULL;

esp_mqtt_client_handle_t mqtt_init(esp_mqtt_client_config_t *mqtt_cfg, esp_event_handler_t event_handler, void* event_handler_arg)
{
    // esp_mqtt_client_handle_t client;
    mqtt_client = esp_mqtt_client_init(mqtt_cfg);
    esp_mqtt_client_register_event(mqtt_client, ESP_EVENT_ANY_ID, event_handler, event_handler_arg);
    esp_mqtt_client_start(mqtt_client);

    return mqtt_client;
}

void mqtt_deinit(esp_mqtt_client_handle_t pclient)
{
    esp_mqtt_client_disconnect(pclient);
}

static int mqtt_send_err(esp_mqtt_client_handle_t c, int errCode)
{
    char buf[32] = {0};

    snprintf(buf, sizeof(buf) - 1, "{\"cmd\":\"err\",\"errCode\":%d}", errCode);
    return esp_mqtt_client_publish(c, CATBOX_TX_COM_TOPIC, "{\"cmd\":\"err\",}", 0, 1, 0);
}



esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
    case HTTP_EVENT_ERROR:
        ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_DISCONNECTED");
        break;
    case HTTP_EVENT_REDIRECT:
        ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
        break;
    }
    return ESP_OK;
}



void simple_ota_example_task(void *pvParameter)
{
    ESP_LOGI(TAG, "Starting OTA example task");
#ifdef CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF
    esp_netif_t *netif = get_example_netif_from_desc(bind_interface_name);
    if (netif == NULL) {
        ESP_LOGE(TAG, "Can't find netif from interface description");
        abort();
    }
    struct ifreq ifr;
    esp_netif_get_netif_impl_name(netif, ifr.ifr_name);
    ESP_LOGI(TAG, "Bind interface name is %s", ifr.ifr_name);
#endif
    esp_http_client_config_t config = {
        .url = CONFIG_EXAMPLE_FIRMWARE_UPGRADE_URL,
        .cert_pem = (char *)server_cert_pem_start,
        .event_handler = _http_event_handler,
        .keep_alive_enable = true,
#ifdef CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF
        .if_name = &ifr,
#endif
    };

#ifdef CONFIG_EXAMPLE_FIRMWARE_UPGRADE_URL_FROM_STDIN
    char url_buf[OTA_URL_SIZE];
    if (strcmp(config.url, "FROM_STDIN") == 0) {
        example_configure_stdin_stdout();
        fgets(url_buf, OTA_URL_SIZE, stdin);
        int len = strlen(url_buf);
        url_buf[len - 1] = '\0';
        config.url = url_buf;
    } else {
        ESP_LOGE(TAG, "Configuration mismatch: wrong firmware upgrade image url");
        abort();
    }
#endif

#ifdef CONFIG_EXAMPLE_SKIP_COMMON_NAME_CHECK
    config.skip_cert_common_name_check = true;
#endif

    esp_https_ota_config_t ota_config = {
        .http_config = &config,
    };
    ESP_LOGI(TAG, "Attempting to download update from %s", config.url);
    esp_err_t ret = esp_https_ota(&ota_config);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "OTA Succeed, Rebooting...");
        esp_restart();
    } else {
        ESP_LOGE(TAG, "Firmware upgrade failed");
    }
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void mqtt_event_data_pro(esp_mqtt_event_handle_t event)
{
    char msg[512] = {0};

    cJSON *value = NULL;

    cJSON *root = cJSON_Parse(event->data);
    if (root == NULL)
    {
        mqtt_send_err(event->client, -1);
        return;
    }

    value = cJSON_GetObjectItem(root, "cmd");
    if (value)
    {
        if(0 == strcmp(value->valuestring, "getInfo"))
        {
            // send_catbox_info();
        }
        else if(0 == strcmp(value->valuestring, "reboot"))
        {
            memset(&msg, 0, sizeof(msg));
            sprintf(msg, "{\"cmd\":\"reboot\",\"value\":1}");
            esp_mqtt_client_publish(event->client, CATBOX_TX_COM_TOPIC, msg, strlen(msg), 1, 0);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            mqtt_deinit(event->client);
            esp_restart();
        }
        else if(0 == strcmp(value->valuestring, "OTAUpgrade"))
        {
            value = cJSON_GetObjectItem(root, "url");
            if (value)
            {
                memset(&ota_task_info, 0, sizeof(OTA_TaskInfo));
                strcpy(ota_task_info.url, value->valuestring);
                ota_task_info.event = event;
                ESP_LOGD(TAG, "url:[%s]", ota_task_info.url);

                sprintf(msg, "{\"cmd\":\"OTAUpgrade\",\"value\":1,\"url\",\"%s\"}", ota_task_info.url);
                esp_mqtt_client_publish(event->client, CATBOX_TX_COM_TOPIC, msg, strlen(msg), 1, 0);

                simple_ota_example_task(&ota_task_info);
            }
        }
        else if(0 == strcmp(value->valuestring, "help"))
        {
            sprintf(msg, "{\"cmd\":\"help\",\"links\":[{\"cmd\":\"getInfo\",\"value\":0},{\"cmd\":\"ctrFAN\",\"value\":1},{\"cmd\":\"OTAUpgrade\",\"url\":\"http://www.lixiangjun.work:8070/file/simple_ota.bin\"}]}");
            esp_mqtt_client_publish(event->client, CATBOX_TX_COM_TOPIC, msg, strlen(msg), 1, 0);
        }
        else
        {
            sprintf(msg, "{\"cmd\":\"help\",\"links\":[{\"cmd\":\"getInfo\",\"value\":0},{\"cmd\":\"ctrFAN\",\"value\":1},{\"cmd\":\"OTAUpgrade\",\"url\":\"http://www.lixiangjun.work:8070/file/simple_ota.bin\"}]}");
            esp_mqtt_client_publish(event->client, CATBOX_TX_COM_TOPIC, msg, strlen(msg), 1, 0);
        }

    }

    cJSON_Delete(root);
}


void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%ld", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;

    char msg[256] = {0};
    int len = 0;

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        mqtt_is_connected = 1;
        msg_id = esp_mqtt_client_subscribe(client, CATBOX_RX_COM_TOPIC, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        memset(&msg, 0, sizeof(msg));
        sprintf(msg, "{\"cmd\":\"connected\",\"value\":\"%02X:%02X:%02X:%02X:%02X:%02X\",\"ver\":\"%s\",\"compile\":\"%s\"}",
            macaddr[0],macaddr[1],macaddr[2],macaddr[3],macaddr[4],macaddr[5],
            app_get_version_string(), get_compile_time());
        esp_mqtt_client_publish(client, CATBOX_TX_COM_TOPIC, msg, len, 1, 0);

        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        mqtt_is_connected = 0;
        break;

    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
        printf("DATA=%.*s\r\n", event->data_len, event->data);
        mqtt_event_data_pro(event);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
            // log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            // log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            // log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}



void mqtt_pro_init(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://www.lixiangjun.work",
        .broker.address.port = MQTT_SERVER_PORT,
        .credentials.username = MQTT_USERNAME,
        .credentials.authentication.password = MQTT_PASSWORKD,
    };
    
    mqtt_client = mqtt_init(&mqtt_cfg, mqtt_event_handler, NULL);
}



