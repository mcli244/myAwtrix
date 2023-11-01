# Embed the server root certificate into the final binary
idf_build_get_property(project_dir PROJECT_DIR)
idf_component_register(SRCS "ws2812.c" "led_strip_encoder.c" "main.c" "smartconfig_wifi.c" "mqtt_pro.c" "app_version.c" "cJSON.c"
                    INCLUDE_DIRS "."
                    EMBED_TXTFILES ${project_dir}/server_certs/ca_cert.pem)
