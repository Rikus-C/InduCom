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
  int received;
  int connected; 
  const char* ip;
  int stopThreads;
  int timeoutLimit;
  char buffer[1024];
  int doneReceiving;
  int client_socket;
  int timeoutCounter;  
  pthread_t connectThread;
  pthread_t receiveThread;
  pthread_t timeoutThreadCon;
  pthread_t timeoutThreadRec;
  struct sockaddr_in server_addr;
}_tcpClient;

void* Connect(void*);
void* Receive(void*);
void* ConnectTimeout(void*);
void* ReceiveTimeout(void*);
void KillConnectThreads(_tcpClient*);
void KillReceiveThreads(_tcpClient*);
void ConnectToServerTCP(_tcpClient*, const char*, int, int);
int SendMessageTCP(_tcpClient*, const char*, int, int);
void DisconnectFromServerTCP(_tcpClient*);
