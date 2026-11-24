
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char buffer[1024];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        perror("Socket failed");
        return 1;
    }

    // Configure server address
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_aton("127.0.0.1", &server.sin_addr);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server,
                sizeof(server)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    printf("Connected to server!\n");

    // Send message
    send(sock, "Hello from client!", 18, 0);

    // Receive response
    int n = recv(sock, buffer, sizeof(buffer) - 1, 0);

    if (n > 0) {
        buffer[n] = '\0';
        printf("Server says: %s\n", buffer);
    }

    close(sock);

    return 0;
}
