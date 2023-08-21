#include "./tcp_client.h"

void DisconnectFromServer(_tcpClient* thisClient){
  close(thisClient->client_socket);
}

bool ConnectToServerTCP(_tcpClient*, const char* frame, int port , int timeout) {
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  timeoutThread = thread([&timeoutTime, this]{
    while (this->timeoutCounter < timeoutTime){
      this->timeoutChecker.milliSeconds(1);
      this->timeoutCounter++;
    }
    if (!this->connectionDone){
      shutdown(this->sock, SHUT_RDWR);
      this->connectionFailed = true;
    } 
  });
  if(client_socket == -1){
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(frame); 
  server_addr.sin_port = htons(port);  
  if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
    perror("Error connecting to server");
    exit(EXIT_FAILURE);
  }
  return true;

  /*
  TEST:
  this->connectionDone    = false;
  this->connectionFailed  = false;
  this->currentTime       = 0;
  this->timeoutCounter    = 0;
  this->timeoutThread = thread([&timeoutTime, this]{
    while (this->timeoutCounter < timeoutTime){
      this->timeoutChecker.milliSeconds(1);
      this->timeoutCounter++;
    }
    if (!this->connectionDone){
      shutdown(this->sock, SHUT_RDWR);
      this->connectionFailed = true;
    } 
  });
  this->connectThread = thread([&IP, &PORT, &timeoutTime, this] {       

    this->Connect(&IP, PORT);
    this->connectionDone = true;
    this->timeoutCounter = timeoutTime;
  });
  timeoutThread.join();
  connectThread.join();
  if(connectionFailed)
    goto TEST;  
  this->connected = true;
  */
}

bool SendMessageTCP(_tcpClient*, const char*, int){
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
    /*
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
  */
}

