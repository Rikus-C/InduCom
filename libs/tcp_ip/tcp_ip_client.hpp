#pragma once

#include "../delays/delay.hpp"

#include <iostream>
#include <functional>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <thread>

using namespace std;

typedef class _tcpClient{
  int sock;
  int connectRes;
  int sendRes;
  int buffSize;
  int currentTime;
  int requestMade;
  int timeoutCounter;
  char buff[65535];   
  bool bufferLocked;
  bool doneRecieving;
  bool receiveFailed;
  bool connectionDone;
  bool connectionFailed;
  delay myDelay;
  delay connectionWait;
  delay timeoutChecker;
  string toSend;
  thread connectThread;
  thread receiveThread;
  thread timeoutThread;
  sockaddr_in hint;
  int bytesReceived;
  string resReceived;
  bool connected;
}_tcpClient;

void Connect(string*, int);
void ConnectToServer(string, int, int);
bool SendRequest(string*, int, bool);  
void KillConnection(); 
