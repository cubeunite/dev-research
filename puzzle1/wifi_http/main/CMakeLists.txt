idf_component_register(SRCS "main.c" "wifi_connect.c" "http_test.c"
                    INCLUDE_DIRS "."
                    REQUIRES "nvs_flash" "esp_http_client" "esp-tls" "json")
