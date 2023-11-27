/* This is a file about HTTP testing */

#include "esp_http_client.h"
#include <cJSON.h>
#include <string.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#include "http_test.h"

char *TAG_HTTP = "http request";
char *url_response_data = NULL;
char *parse_ret = NULL;

esp_err_t _http_event_handle(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGI(TAG_HTTP, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI(TAG_HTTP, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI(TAG_HTTP, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI(TAG_HTTP, "HTTP_EVENT_ON_HEADER");
            printf("%.*s\n", evt->data_len, (char*)evt->data);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(TAG_HTTP, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
               printf("%.*s\n", evt->data_len, (char*)evt->data);
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG_HTTP, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG_HTTP, "HTTP_EVENT_DISCONNECTED");
            break;
    }
    return ESP_OK;
}

// http client config, send http request, ande get response data, return response data.
char *httpClient_config_requestData()
{
    // create http client config
    esp_http_client_config_t config = {
     .url = URL,
     .event_handler = _http_event_handle,
    };

    // send http request
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err_Perform = esp_http_client_perform(client);
    if(err_Perform == ESP_OK){
        ESP_LOGI(TAG_HTTP, "Status = %d, content_length = %d",
        esp_http_client_get_status_code(client),
        esp_http_client_get_content_length(client));
    }

    // Read data from http stream.
    url_response_data = (char *)malloc(esp_http_client_get_content_length(client) + 2);
    //memcpy(url_response_data, evt->data, evt->data_len);
    esp_err_t err_open = esp_http_client_open(client, 0);
    if (err_open == ESP_OK) {
        esp_http_client_read(client, url_response_data, esp_http_client_get_content_length(client));
        strcat(url_response_data, "\0");
        printf("%s\n", url_response_data);
    }
    
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
    return url_response_data;
}

//Parsing response data in JSON format
char *json_parse(char *json_string, char *obj_str) 
{
    //get value of "brand"
    cJSON *json = cJSON_Parse(json_string);
    if (json == NULL) {
        printf("Failed to parse JSON string\n");
    }
    cJSON *brand = cJSON_GetObjectItemCaseSensitive(json, obj_str);
    if (cJSON_IsString(brand) && (brand->valuestring != NULL)) {
        printf("Brand: %s\n", brand->valuestring);
    }
    parse_ret = (char *)malloc(strlen(brand->valuestring) + 1);
    memcpy(parse_ret, brand->valuestring, strlen(brand->valuestring));
    cJSON_Delete(json);
    return parse_ret;
}

