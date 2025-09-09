// TCP Math Client (Single Client)
// Sends two integers and an operator to server, receives result, prints it, then terminates.

#include "common.h"   // use the umbrella header file

#define PORTNO 10200  // Must match server port

int main() {
    int sockfd;
    struct sockaddr_in seraddr;
    char buffer[256];

    // Step 1: Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // Step 2: Setup server address
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(PORTNO);
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Change if server is remote

    // Step 3: Connect to server
    if (connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        perror("connect");
        exit(1);
    }

    // Step 4: Take input from user
    int a, b;
    char op;
    printf("Enter expression (e.g., 10 + 5): ");
    scanf("%d %c %d", &a, &op, &b);

    // Step 5: Send input to server
    snprintf(buffer, sizeof(buffer), "%d %c %d", a, op, b);
    write(sockfd, buffer, strlen(buffer) + 1);

    // Step 6: Receive result
    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));

    printf("Response from Server: %s\n", buffer);

    // Step 7: Close connection
    close(sockfd);
    return 0;
}
