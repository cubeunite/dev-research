#ifndef _WIFI_CONNECT_H_
#define _WIFI_CONNECT_H_
#include "esp_event.h"
#include "lwip/err.h"
#include "esp_http_client.h"

/* The following is WiFi configuration that you can set via project configuration menu
   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_ESP_WIFI_SSID      CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS      CONFIG_ESP_WIFI_PASSWORD
#define EXAMPLE_ESP_MAXIMUM_RETRY  CONFIG_ESP_MAXIMUM_RETRY

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

// try to connect to wifi 
void event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

/*Initialize NVS, Initialize non volatile memory(NVS) 
 * to store important data such as WiFi 
 * configuration and device status for the next connection
 * */
void nvs_init(void);

//Initialize esp32 as a station
void wifi_init_sta(void);

// disconnect wifi from AP
void wifi_disconnect(void);
#endif

