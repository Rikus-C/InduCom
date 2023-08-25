#include <stdio.h>
#include <wchar.h>

#include "../inducom/macros/basic_macros.h"
#include "../inducom/c_libraries/delays/delay.h"
#include "../inducom/c_libraries/linked_list/linked_list.h"
#include "../inducom/c_libraries/tcp_socket_ipv4/tcp_client.h"
 
int main(){
  _tcpClient testClient;
  ConnectToServerTCP(&testClient, "127.0.0.1", 12345, 3000);
  int messageReceived = SendMessageTCP(&testClient, "Hello Python, from C", true, 3000);
  if(messageReceived) printf("i got a response\n");
  else print("I was left hanging\n");
  DisconnectFromServerTCP(&testClient);
  return 0;
}
