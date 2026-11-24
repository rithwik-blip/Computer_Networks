
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock;
    struct sockaddr_in receiver;

    // Create UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    // Configure receiver address
    receiver.sin_family = AF_INET;
    receiver.sin_port = htons(9090);
    inet_aton("127.0.0.1", &receiver.sin_addr);

    // Send message
    char message[] = "Hello from UDP sender!";

    sendto(sock, message, strlen(message), 0,
           (struct sockaddr *)&receiver, sizeof(receiver));

    printf("Message sent successfully!\n");

    close(sock);
    return 0;
}

