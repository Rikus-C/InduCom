#include <stdio.h>
#include <wchar.h>

#include "../inducom/macros/basic_macros.h"
#include "../inducom/macros/socket_macros.h"
#include "../inducom/c_libraries/delays/delay.h"
#include "../inducom/c_libraries/linked_list/linked_list.h"
#include "../inducom/c_libraries/tcp_socket_ipv4/tcp_client.h"
 
int main(){
  const char* res;
  CREATE_AND_CONNECT_TCP_CLIENT(testClient, "127.0.0.1", 12345, 3000);
  SEND_TCP_MESSAGE_WITH_RESPONSE(testClient, "Hello Python", res, 3000);
  printf("%s\n", res);
  SEND_TCP_MESSAGE_WITH_RESPONSE(testClient, "Hello Python", res, 3000);
  printf("%s\n", res);
  SEND_TCP_MESSAGE_WITH_RESPONSE(testClient, "Hello Python", res, 3000);
  printf("%s\n", res);
  SEND_TCP_MESSAGE_WITH_RESPONSE(testClient, "Hello Python", res, 3000);
  printf("%s\n", res);
  SEND_TCP_MESSAGE_WITH_RESPONSE(testClient, "Hello Python", res, 3000);
  printf("%s\n", res);
  SEND_TCP_MESSAGE_WITH_RESPONSE(testClient, "Hello Python", res, 3000);
  printf("%s\n", res);
  DISCONNECT_TCP_CLIENT(testClient);  
  return 0;
}
