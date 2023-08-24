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

}_tcpServer;

void KillServer(_tcpServer*);
void ListenForMessages(void*);
int InitiateServer(_tcpServer*, const char*, int, void*);
