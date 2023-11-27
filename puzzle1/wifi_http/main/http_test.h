#ifndef _HTTP_TEST_H_
#define _HTTP_TEST_H_

/* The URL to be accessed */
#define URL "https://dummyjson.com/products/1"

/* Function declaration */
esp_err_t _http_event_handle(esp_http_client_event_t *evt);

// http client config, send http request, ande get response data
char *httpClient_config_requestData();

//Parsing response data in JSON format
char *json_parse(char *json_string, char *obj_str);
#endif
