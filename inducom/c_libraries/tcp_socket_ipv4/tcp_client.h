#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

typedef struct _tcpClient{
  int client_socket;
  int timeoutCounter;
  struct sockaddr_in server_addr;
  char message[1024]; 
  bool connected;
  p_thread timeoutThread;
}_tcpClient;

bool ConnectToServerTCP(_tcpClient*, const char*, int, int);
bool SendMessageTCP(_tcpClient*, const char*, int);
void DisconnectFromServerTCP(_tcpClient*);
