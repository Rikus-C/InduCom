#include "./tcp_server.h"

void KillServer(_tcpServer* thisServer){}

void ListenforRequests(void* Callback){}

int InitiateServer(_tcpServer* thisServer, const char* ip, int port, void* Callback) {
  int server_socket, client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_addr_size;

  // Create socket
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  // Setup server address structure
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(12345);  // Port number

  // Bind socket to address
  if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    perror("Error binding");
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_socket, 5) == -1) {
    perror("Error listening");
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port 12345...\n");

  // Accept and handle client connections
  client_addr_size = sizeof(client_addr);
  client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);
  if (client_socket == -1) {
    perror("Error accepting client connection");
    exit(EXIT_FAILURE);
  }

  printf("Client connected.\n");

  // Handle communication with client
  char buffer[1024];
  ssize_t bytes_received;

  while (1) {
    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0) {
      printf("Client disconnected.\n");
      break;
    }
    buffer[bytes_received] = '\0';
    printf("Received from client: %s", buffer);
    send(client_socket, buffer, bytes_received, 0);
  }

  // Close sockets
  close(client_socket);
  close(server_socket);

  return 0;
}
