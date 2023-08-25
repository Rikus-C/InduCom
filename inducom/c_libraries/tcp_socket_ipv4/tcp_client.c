#include "./tcp_client.h"

void DisconnectFromServerTCP(_tcpClient* thisClient){
  thisClient->connected = false;
  close(thisClient->client_socket);
}

void* Receive(void* thisClientArgs){
  ssize_t recSize = recv(thisC->client_socket, thisC->buffer, sizeof(thisC->buffer), 0);
  if (recSize <= 0) pthread_exit(NULL);
  thisC->doneReceiving = true;
  pthread_exit(NULL);
}

void* ReceiveTimeout(void* thisClientArgs){ 
  while(thisC->timeoutCounter < thisC->timeoutLimit){
    if(thisC->stopThreads) pthread_exit(NULL);
    delayMilliSeconds(1);
    thisC->timeoutCounter++;
  } pthread_exit(NULL);
}

void* Connect(void* thisClientArgs){
  TRY_CONNECT: if(thisC->stopThreads) pthread_exit(NULL);
  thisC->server_addr.sin_family = AF_INET;
  thisC->server_addr.sin_addr.s_addr = inet_addr(thisC->ip); 
  thisC->server_addr.sin_port = htons(thisC->port);  
  int result = connect(thisC->client_socket,
  (struct sockaddr*)&thisC->server_addr, sizeof(thisC->server_addr));
  if (result == -1) thisC->connected = false;
  else thisC->connected = true;
  if(thisC->client_socket == -1){
    delayMilliSeconds(10);
    goto TRY_CONNECT;
  }pthread_exit(NULL);
}

void* ConnectTimeout(void* thisClientArgs){ 
  while(thisC->timeoutCounter < thisC->timeoutLimit){
    if(thisC->stopThreads) pthread_exit(NULL);
    delayMilliSeconds(1);
    thisC->timeoutCounter++;
  } pthread_exit(NULL);
}

void KillConnectThreads(_tcpClient* thisClient){
  thisClient->stopThreads = true;
  pthread_join(thisClient->connectThread, NULL);
  pthread_join(thisClient->timeoutThreadCon, NULL);
}

void KillReceiveThreads(_tcpClient* thisClient){
  thisClient->stopThreads = true;
  //pthread_join(thisClient->receiveThread, NULL);
  pthread_join(thisClient->timeoutThreadRec, NULL);

}

void ConnectToServerTCP(_tcpClient* thisClient, const char* ip, int port , int timeout){
  CONNECT: thisClient->connected = false;
  thisClient->stopThreads = false;
  thisClient->timeoutCounter = 0;
  thisClient->timeoutLimit = timeout;
  thisClient->ip = ip; thisClient->port = port;
  thisClient->client_socket = socket(AF_INET, SOCK_STREAM, 0);
  pthread_create(&thisClient->connectThread, NULL, Connect, (void*)thisClient);
  pthread_create(&thisClient->timeoutThreadCon, NULL, ConnectTimeout, (void*)thisClient);
  while((thisClient->connected == false)&& 
  (thisClient->timeoutCounter < thisClient->timeoutLimit)) 
    delayMilliSeconds(10);
  if(!thisClient->connected){ 
    KillConnectThreads(thisClient);
    thisClient->stopThreads = false;
    goto CONNECT;
  }KillConnectThreads(thisClient);
}

int SendMessageTCP(_tcpClient* thisClient, const char* message, int boolWait, int waitTime){
  send(thisClient->client_socket, message, strlen(message), 0); 
  if(!boolWait) return true;
  thisClient->doneReceiving = false;
  thisClient->timeoutCounter = 0;
  thisClient->stopThreads = false;
  thisClient->timeoutLimit = waitTime;
  pthread_create(&thisClient->receiveThread, NULL, Receive, (void*)thisClient);
  pthread_create(&thisClient->timeoutThreadRec, NULL, ReceiveTimeout, (void*)thisClient);
  while((thisClient->doneReceiving == false)&& 
  (thisClient->timeoutCounter < thisClient->timeoutLimit)) 
    delayMilliSeconds(10);
  KillConnectThreads(thisClient);
  return thisClient->doneReceiving;
}

