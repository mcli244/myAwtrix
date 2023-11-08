# Embed the server root certificate into the final binary
idf_build_get_property(project_dir PROJECT_DIR)
file(GLOB_RECURSE ZLG_GUI_SRCS ./ZLG_GUI/*.c)
idf_component_register(SRCS "my_ws2812.c" "led_strip_encoder.c" "main.c" "smartconfig_wifi.c" "mqtt_pro.c" "app_version.c" "cJSON.c"
                    ${ZLG_GUI_SRCS}
                    INCLUDE_DIRS "." "./ZLG_GUI"
                    EMBED_TXTFILES ${project_dir}/server_certs/ca_cert.pem)
