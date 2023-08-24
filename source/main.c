#include <stdio.h>
#include <wchar.h>

#include "../inducom/macros/basic_macros.h"
#include "../inducom/c_libraries/delays/delay.h"
#include "../inducom/c_libraries/linked_list/linked_list.h"
#include "../inducom/c_libraries/tcp_socket_ipv4/tcp_client.h"
 
int main(){
  _tcpClient testClient;
  ConnectToServerTCP(&testClient, "127.0.0.1", 12345, 3000);
  delaySeconds(50); 
  DisconnectFromServerTCP(&testClient);
  return 0;
}
