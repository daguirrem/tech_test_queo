
/* Only simulates the server authorization module comunnication
 */

#include "web_sockets.h"
#include "authorizator_manager.h"

void auth_manager_ws_hanlder(ws_event_t event);
void auth_manager_rest_hanlder(rest_event_t *event);

int main(void)
{
    /* Init WebSocket Server */
    auth_manager_server_rest_init(
        RESTAPI_URI,
        RESTAPI_PORT,
        &COMMON_PRIVATE_KEY,
        &COMMON_PUBLIC_CERT
        
        &auth_manager_rest_hanlder
    );
    
    /* Init REST API Server */
    auth_manager_server_wss_init(
        AUTH_WEB_SOCKET_URI,
        AUTH_WEB_SOCKET_PORT,
        &COMMON_PRIVATE_KEY,
        &COMMON_PUBLIC_CERT,
        
        &auth_manager_ws_hanlder
    );
    
    while(1){};
}

void auth_manager_rest_hanlder(rest_event_t *event)
{
    switch(event->type)
    {
        case REST_EVENT_POST:
            if (!srtncmp(event->uri,"request_new_user", event->lenght))
            {
                uint8_t data[MAX_PAYLOAD_SIZE];
                uint32_t *metadata = event->payload;
                 
                /* Request biometrical / dni data to client ws and save
                 * returned data.
                 */
                authorizator_manager_request(&data, event->cliendid);
                
                /* Save data and metadata on internal DB */
                authorizator_manager_users_new(data, *metadata);
            }
            break;
        
        default:
            break;
    }
}

void auth_manager_ws_hanlder(ws_event_t *event)
{
    /* Suppose event is data structure with type, payload, lenght, clientid */
    switch(event->type)
    {
        case RX_DATA:
            
            /* Request updated user list */
            if (!srtncmp(event->payload,"RUSER_LIST", event->lenght))
            {
                auth_users_t users[AUTH_MAX_USERS];
                
                /* Get from internal DB and returns on users variable */
                uint32_t size = authorizator_manager_get_users(&users);
                
                /* Prepare data to send throught ws */
                authorizator_manager_users_send(&users, size, event->clientid);
            } 
           
         default:
            break;
    }
}
