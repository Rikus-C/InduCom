#include "./tcp_client.h"

void DisconnectFromServer(_tcpClient* thisClient){
  thisClient->connected = false;
  close(thisClient->client_socket);
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

void* Timeout(void* thisClientArgs){
  while(thisC->timeoutCounter < thisC->timeoutLimit){
    if(thisC->stopThreads) pthread_exit(NULL);
    delayMilliSeconds(1);
    thisC->timeoutCounter++;
  }if(!thisC->connected)
    DisconnectFromServer(thisC);
  pthread_exit(NULL);
}

void KillThreads(_tcpClient* thisClient){
  thisClient->stopThreads = true;
  pthread_join(*thisClient->connectThread, NULL);
  pthread_join(*thisClient->timeoutThread, NULL);
}

void ConnectToServerTCP(_tcpClient* thisClient, const char* ip, int port , int timeout) {
  CONNECT: thisClient->connected = false;
  thisClient->stopThreads = false;
  thisClient->timeoutCounter = 0;
  thisClient->timeoutLimit = timeout;
  thisClient->ip = ip; thisClient->port = port;
  thisClient->client_socket = socket(AF_INET, SOCK_STREAM, 0);
  pthread_create(thisClient->timeoutThread, NULL, Timeout, (void*)thisClient);
  pthread_create(thisClient->connectThread, NULL, Connect, (void*)thisClient);
  while((thisClient->connected == false)&& 
  (thisClient->timeoutCounter < thisClient->timeoutLimit)) 
    delayMilliSeconds(10);
  if(!thisClient->connected){ 
    KillThreads(thisClient);
    thisClient->stopThreads = false;
    goto CONNECT;
  }KillThreads(thisClient);
}

/*int SendMessageTCP(_tcpClient*, const char*, int, int){
   send(client_socket, message, strlen(message), 0);
    if (strcmp(message, "exit\n") == 0) {
      printf("Client exiting.\n");
      break;
    }

    ssize_t bytes_received = recv(client_socket, message, sizeof(message), 0);
    if (bytes_received <= 0) {
      printf("Server disconnected.\n");
      break;
    }
    message[bytes_received] = '\0';
    printf("Received from server: %s", message);

    (void)send(this->sock, msg->c_str(), msg->size(), 0);  
  if (!response) return true; 
  this->receiveFailed = false;
  this->doneRecieving = false;
  this->timeoutCounter = 0;
  this->timeoutThread = thread([&timeoutTime, &response, this]{
    while (this->timeoutCounter < timeoutTime){
      this->timeoutChecker.milliSeconds(1);
      this->timeoutCounter++;
    }
    if (!this->doneRecieving){
      if (timeoutTime != 0){
        shutdown(this->sock, SHUT_RDWR);
        this->receiveFailed = true;
      }
    } 
  });
  this->receiveThread = thread([&timeoutTime, this]{

    memset(this->buff, 0, 65535); 
    this->bytesReceived = recv(this->sock, this->buff, 65535, 0);
    this->resReceived = string(this->buff, bytesReceived);
    this->doneRecieving = true;
    this->timeoutCounter = timeoutTime;
  });
  this->timeoutThread.join();
  this->receiveThread.join(); 
  if (receiveFailed) return false;
  return true;

}*/

