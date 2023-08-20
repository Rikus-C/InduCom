#include "./tcp_client.h"

bool ConnectToServerTCP() {
  // Create socket
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if(client_socket == -1){
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  // Setup server address structure
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
  server_addr.sin_port = htons(12345);  // Server port number

  // Connect to the server
  if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
    perror("Error connecting to server");
    exit(EXIT_FAILURE);
  }

  printf("Connected to server.\n");

  close(client_socket);

  return 0;
}

bool SendMessageTCP(){
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
}

