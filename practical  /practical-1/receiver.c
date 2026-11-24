
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock;
    char buffer[1024];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure receiver address
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9090);

    // Bind socket
    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Receiver waiting...\n");

    // Receive message
    int n = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&client, &len);

    if (n >= 0) {
        buffer[n] = '\0';
        printf("Message: %s\n", buffer);
        printf("Sender IP: %s\n", inet_ntoa(client.sin_addr));
    }

    close(sock);
    return 0;
}
