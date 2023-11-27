#include <string.h>
#include "esp_log.h"
#include "wifi_connect.h"
#include "http_test.h"

extern char *TAG;
extern char *TAG_HTTP;
extern char *url_response_data;
extern char *parse_ret;

void app_main(void)
{
    //Initialize NVS
    nvs_init();

    //Initialize wifi as a station
    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();
    
    ESP_LOGI(TAG_HTTP, "following are about http request");
    // http client config, send http request, ande get response data
    httpClient_config_requestData();

    // parse data
    json_parse(url_response_data, "brand");
    
    // Verify that 'url_response_data' and 'parse_ret' have been stored
    printf("url===========================\n%s\n", url_response_data);
    printf("brand:========================\n%s\n", parse_ret);

    // disconnect wifi from AP
    wifi_disconnect();

    free(url_response_data);
    url_response_data = NULL;

    free(parse_ret);
    parse_ret = NULL;
}
