#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "../../macros/basic_macros.h"
#include "../linked_list/linked_list.h"

#define BUFFER_SIZE 1024 

typedef struct _tcpServer{
  char buffer[BUFFER_SIZE];
  _list* bufferList; 
  int bufferListsize;
  pthread_t processBufferThread;
  pthread_t receiveMessageThread;

}_tcpServer;

void KillServer(_tcpServer*);
void ListenForRequests(void*);
int InitiateServer(_tcpServer*, const char*, int, void*);
