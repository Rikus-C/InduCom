#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[1024];

    // Create socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Setup server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
    server_addr.sin_port = htons(12345);  // Server port number

    // Send and receive messages
    while (1) {
        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);
        sendto(client_socket, message, strlen(message), 0,
               (struct sockaddr*)&server_addr, sizeof(server_addr));

        if (strcmp(message, "exit\n") == 0) {
            printf("Client exiting.\n");
            break;
        }

        ssize_t bytes_received = recvfrom(client_socket, message, sizeof(message), 0,
                                          NULL, NULL);
        if (bytes_received == -1) {
            perror("Error receiving data");
            continue;
        }
        message[bytes_received] = '\0';
        printf("Received from server: %s", message);
    }

    // Close socket
    close(client_socket);

    return 0;
}

