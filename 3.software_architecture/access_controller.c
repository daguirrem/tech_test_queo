
/* Only simulates the client-server comunnication
 */

#include "system.h"
#include "authorizator.h"
#include "web_sockets.h"


void auth_handler(auth_event_t *event);

void ws_handler(ws_event_t event);
void ws_on_connect(void *args);
void ws_on_dissconnect(void *args)

int app_main(void)
{
    system_init();
    
    /* Init the biometrical and document identy physical interfaces */
    auth_init(
        &auth_handler
    );
    
    /* Init WebSocket client */
    web_socket_client_init(
        WEB_SOCKET_URI,
        WEB_SOCKET_PORT,
        &WEB_SOCKET_CERT,
        
        &ws_on_connect,
        &ws_on_dissconnect
    );
    
    while(1){};
}

void auth_handler(auth_event_t *event)
{
    /* Suppose event is data structure with type, metadata, lenght */
    switch(event->type)
    {
        /* Event Report generates a POST request to Cloud Server to log event 
         * whit event metadata.
         */
        case AUTH_USER_OK:
            event_report(EVENT_ACCESS_OK, event->metadata);
            break;
        case AUTH_USER_NOT_FOUND:
            event_report(EVENT_ACCESS_NOTFOUND, event->metadata);
            break;
        default:
            break;
    }
}

void ws_handler(ws_event_t *event)
{
    /* Suppose event is data structure with type, payload, lenght */
    switch(event->type)
    {
        case RX_DATA:
            
            /* Request new biometrical / dni from server to new user */
            if (!srtncmp(event->payload,"RBIOMETRICAL", event->lenght))
            {
                uint32_t data[MAX_AUTH_PAYLOAD] = {};
                uint32_t size = auth_user_new(AUTH_BIOMETRICAL, &data);
                web_socket_send(data);
            } 
            else if (!srtncmp(event->payload,"RDNI", event->lenght))
            {
                uint32_t data[MAX_AUTH_PAYLOAD] = {};
                uint32_t size = auth_user_new(AUTH_DNI, &data);
                web_socket_send(data);
            }
            
            /* Check if send data is requested updated user list */
            /* Server sends AUSER_LIST,TYPE[BIOMETRICAL,DNI],USER_ID,RAW_DATA */
            else if (!strnstr(event->payload, "AUSER_LIST", event->lenght))
            {
                /* Auth update split and format data and request to respective
                 * interface update user database and data.
                 */
                auth_update(event->payload);
            }
            break;
           
         default:
            break;
    }
}

void ws_on_connect(void *args)
{
    web_socket_client_handler_set(&ws_handler);
    web_socket_send("RUSER_LIST");
}


void ws_on_disconnect(void *args)
{
    web_socket_client_handler_purge();
    ws_destroy();
}
