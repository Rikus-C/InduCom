#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/*int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size;
    char buffer[1024];

    // Create socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
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

    printf("Server listening on port 12345...\n");

    // Receive and handle data from clients
    client_addr_size = sizeof(client_addr);

    while (1) {
        ssize_t bytes_received = recvfrom(server_socket, buffer, sizeof(buffer), 0,
                                          (struct sockaddr*)&client_addr, &client_addr_size);
        if (bytes_received == -1) {
            perror("Error receiving data");
            continue;
        }
        
        buffer[bytes_received] = '\0';
        printf("Received from client: %s", buffer);

        // Send a response back to the client
        sendto(server_socket, buffer, bytes_received, 0,
               (struct sockaddr*)&client_addr, client_addr_size);
    }

    // Close socket
    close(server_socket);

    return 0;
}*/
