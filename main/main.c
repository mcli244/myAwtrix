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
#include "protocol_examples_common.h"
#include <sys/socket.h>
#if CONFIG_EXAMPLE_CONNECT_WIFI
#include "esp_wifi.h"
#endif

static const char *TAG = "simple_ota_example";
extern const uint8_t server_cert_pem_start[] asm("_binary_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_ca_cert_pem_end");

#define OTA_URL_SIZE 256

// add 
#include "esp_sntp.h"
// #include "wifi.h"
#include "mqtt_pro.h"
#include "cJSON.h"
#include "app_version.h"
#include "freertos/event_groups.h"
// #include "error_code.h"
#include "smartconfig_wifi.h"

#define HASH_LEN 32
#define CATBOX_TX_COM_TOPIC "home/myAwtrix_TX"
#define CATBOX_TX_INFO_TOPIC "home/myAwtrix_TX/Info"
#define CATBOX_TX_TEST_TOPIC "home/myAwtrix_TX/test"
#define CATBOX_RX_COM_TOPIC "home/myAwtrix_RX"

#ifdef CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF
/* The interface name value can refer to if_desc in esp_netif_defaults.h */
#if CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF_ETH
static const char *bind_interface_name = "eth";
#elif CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF_STA
static const char *bind_interface_name = "sta";
#endif
#endif

static char compile_time[64] = {0};
typedef struct
{
    char url[OTA_URL_SIZE];
    esp_mqtt_event_handle_t event;
}OTA_TaskInfo;

typedef struct
{
    int hour;
    int min;
    int sec;
}RUN_TimeTypdef;
typedef struct 
{
    uint8_t macaddr[6];
    RUN_TimeTypdef deviceRunTime;
    struct tm deviceUpTime;      // 设备开机时间，依赖于SNTP
    uint32_t triggerCnt;

    // 风扇
    RUN_TimeTypdef fanRunTime;      // 风扇所有运行时间
    uint32_t fanRunCnt;             // 风扇运行次数

    //wifi连上事件定义
    EventGroupHandle_t wifi_event_group;
    int CONNECTED_BIT;

    // OTA相关
    OTA_TaskInfo ota_task_info;

    #define TRIGGER_TIME_MAX 5
    time_t  triggerTimeList[TRIGGER_TIME_MAX];

    #define CATOUTTIME_DEF  30
    #define FANARRIVALTIME_DEF  90
    int catOutTime;     // 触发后多长时间没被再次触发认为是确认离开，单位秒
    int fanArrivalTime; // 风扇触发后多长时间到达最大转速，单位秒

    #define CAT_STA_IDEL       0           
    #define CAT_STA_OUT       1           // 离开了
    #define CAT_STA_IN    2           // 达到了
    #define CAT_STA_MOVE    3          // 在里面移动
    #define CAT_STA_TIMEOUT    4          // 在里面超时了
    uint8_t catState;

    esp_mqtt_client_handle_t mqtt_client;
    int mqtt_is_connected;

    // hx711_data
    int hx711_is_connected;
    int32_t hx711_data;
    int32_t hx711_fur_data; // 毛皮
    float weight;

    int32_t hx711_triger_value;

    uint8_t hx_reload_flag;
    #define HX711_DATA_MAX  30
    int32_t hx711_data_list[HX711_DATA_MAX];

    time_t use_time;    // 使用时间

}RUN_Info;

static RUN_Info runInfo;
// add end

#define HASH_LEN 32

#ifdef CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF
/* The interface name value can refer to if_desc in esp_netif_defaults.h */
#if CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF_ETH
static const char *bind_interface_name = EXAMPLE_NETIF_DESC_ETH;
#elif CONFIG_EXAMPLE_FIRMWARE_UPGRADE_BIND_IF_STA
static const char *bind_interface_name = EXAMPLE_NETIF_DESC_STA;
#endif
#endif

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
#ifdef CONFIG_EXAMPLE_USE_CERT_BUNDLE
        .crt_bundle_attach = esp_crt_bundle_attach,
#else
        .cert_pem = (char *)server_cert_pem_start,
#endif /* CONFIG_EXAMPLE_USE_CERT_BUNDLE */
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

static void print_sha256(const uint8_t *image_hash, const char *label)
{
    char hash_print[HASH_LEN * 2 + 1];
    hash_print[HASH_LEN * 2] = 0;
    for (int i = 0; i < HASH_LEN; ++i) {
        sprintf(&hash_print[i * 2], "%02x", image_hash[i]);
    }
    ESP_LOGI(TAG, "%s %s", label, hash_print);
}

static void get_sha256_of_partitions(void)
{
    uint8_t sha_256[HASH_LEN] = { 0 };
    esp_partition_t partition;

    // get sha256 digest for bootloader
    partition.address   = ESP_BOOTLOADER_OFFSET;
    partition.size      = ESP_PARTITION_TABLE_OFFSET;
    partition.type      = ESP_PARTITION_TYPE_APP;
    esp_partition_get_sha256(&partition, sha_256);
    print_sha256(sha_256, "SHA-256 for bootloader: ");

    // get sha256 digest for running partition
    esp_partition_get_sha256(esp_ota_get_running_partition(), sha_256);
    print_sha256(sha_256, "SHA-256 for current firmware: ");
}

void time_sync_notification_cb(struct timeval *tv)
{
    static int first_in = 0;
    time_t now = 0;

    if(0 == first_in)
    {
        first_in = 1;
        time(&now);
        localtime_r(&now, &runInfo.deviceUpTime);
        ESP_LOGI(TAG, "deviceUpTime save");
    }
    ESP_LOGI(TAG, "Notification of a time synchronization event");
}

char *get_app_version(void)
{
    return app_get_version_string();
}

char *get_compile_time(void)
{
    sprintf(compile_time, "%s %s", __DATE__, __TIME__);
    return compile_time;
}

static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

static int mqtt_send_err(esp_mqtt_client_handle_t c, int errCode)
{
    char buf[32] = {0};

    snprintf(buf, sizeof(buf) - 1, "{\"cmd\":\"err\",\"errCode\":%d}", errCode);
    return esp_mqtt_client_publish(c, CATBOX_TX_COM_TOPIC, "{\"cmd\":\"err\",}", 0, 1, 0);
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
                memset(&runInfo.ota_task_info, 0, sizeof(OTA_TaskInfo));
                strcpy(runInfo.ota_task_info.url, value->valuestring);
                runInfo.ota_task_info.event = event;
                ESP_LOGD(TAG, "url:[%s]", runInfo.ota_task_info.url);

                sprintf(msg, "{\"cmd\":\"OTAUpgrade\",\"value\":1,\"url\",\"%s\"}", runInfo.ota_task_info.url);
                esp_mqtt_client_publish(event->client, CATBOX_TX_COM_TOPIC, msg, strlen(msg), 1, 0);

                simple_ota_example_task(&runInfo.ota_task_info);
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
        runInfo.mqtt_is_connected = 1;
        msg_id = esp_mqtt_client_subscribe(client, CATBOX_RX_COM_TOPIC, 0);
        ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

        memset(&msg, 0, sizeof(msg));
        sprintf(msg, "{\"cmd\":\"connected\",\"value\":\"%02X:%02X:%02X:%02X:%02X:%02X\",\"ver\":\"%s\",\"compile\":\"%s\"}",
            runInfo.macaddr[0],runInfo.macaddr[1],runInfo.macaddr[2],runInfo.macaddr[3],runInfo.macaddr[4],runInfo.macaddr[5],
            get_app_version(), get_compile_time());
        esp_mqtt_client_publish(client, CATBOX_TX_COM_TOPIC, msg, len, 1, 0);

        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        runInfo.mqtt_is_connected = 0;
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
            log_error_if_nonzero("reported from esp-tls", event->error_handle->esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", event->error_handle->esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  event->error_handle->esp_transport_sock_errno);
            ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));

        }
        break;
    default:
        ESP_LOGI(TAG, "Other event id:%d", event->event_id);
        break;
    }
}


void app_main(void)
{

    

    get_sha256_of_partitions();

    memset(&runInfo, 0, sizeof(runInfo));
    runInfo.CONNECTED_BIT = BIT0;
    runInfo.wifi_event_group = xEventGroupCreate();

    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );

    // Open
    nvs_handle_t my_handle;
    err = nvs_open("runInfo", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } else {
        // err = nvs_get_i32(my_handle, "runTimeH", &runInfo.deviceRunTime.hour);
        // err = nvs_get_i32(my_handle, "runTimeM", &runInfo.deviceRunTime.min);
        // err = nvs_get_i32(my_handle, "runTimeS", &runInfo.deviceRunTime.sec);
        // err = nvs_get_i32(my_handle, "fanRunTimeH", &runInfo.fanRunTime.hour);
        // err = nvs_get_i32(my_handle, "fanRunTimeM", &runInfo.fanRunTime.min);
        // err = nvs_get_i32(my_handle, "fanRunTimeS", &runInfo.fanRunTime.sec);
        // err = nvs_get_u32(my_handle, "triggerCnt", &runInfo.triggerCnt);
        // err = nvs_get_u32(my_handle, "fanRunCnt", &runInfo.fanRunCnt);
        nvs_close(my_handle);
    }
    
    smartconfig_app_main();

    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "time2.cloud.tencent.com");
    sntp_setservername(1, "ntp.aliyun.com");
    sntp_setservername(2, "ntp.ntsc.ac.cn");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    setenv("TZ", "CST-8", 1);
    tzset();
    sntp_init();    

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://www.lixiangjun.work",
        .broker.address.port = MQTT_SERVER_PORT,
        .credentials.username = MQTT_USERNAME,
        .credentials.authentication.password = MQTT_PASSWORKD,
    };
    
    runInfo.mqtt_client = mqtt_init(&mqtt_cfg, mqtt_event_handler, NULL);

    esp_ota_mark_app_valid_cancel_rollback();   // 程序运行到这里，标记程序运行成功

    // xTaskCreate(&simple_ota_example_task, "ota_example_task", 8192, NULL, 5, NULL);
    while(1)
    {
        ESP_LOGI(TAG, "mimi..");
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}
