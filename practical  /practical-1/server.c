
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    char buffer[1024];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("Socket failed");
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&server,
             sizeof(server)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }

    // Listen for clients
    listen(server_fd, 5);

    printf("Server waiting for client...\n");

    // Accept client connection
    client_fd = accept(server_fd,
                       (struct sockaddr *)&client, &len);

    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        return 1;
    }

    printf("Client connected!\n");
    printf("Client IP: %s\n", inet_ntoa(client.sin_addr));

    // Receive message
    int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';
        printf("Client says: %s\n", buffer);
    }

    // Send response
    send(client_fd, "Hello from server!", 18, 0);

    close(client_fd);
    close(server_fd);

    return 0;
}
