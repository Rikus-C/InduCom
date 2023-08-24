#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#include "../delays/delay.h"
#include "../../macros/basic_macros.h"

#define thisC ((_tcpClient*)thisClientArgs) 

typedef struct _tcpClient{ 
  int port;
  int connected;
  const char* ip;
  int stopThreads;
  ssize_t received;
  int timeoutLimit;
  char buffer[1024];
  int client_socket;
  int timeoutCounter;
  pthread_t timeoutThread;
  pthread_t connectThread;
  struct sockaddr_in server_addr;
}_tcpClient;

void* Connect(void*);
void* Timeout(void*);
void* ReceiveResponse(void*);
void KillThreads(_tcpClient*);
void ConnectToServerTCP(_tcpClient*, const char*, int, int);
int SendMessageTCP(_tcpClient*, const char*, int, int);
void DisconnectFromServerTCP(_tcpClient*);
