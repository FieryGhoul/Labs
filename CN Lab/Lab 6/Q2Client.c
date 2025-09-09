// TCP Client (Single Client)
// Sends a sentence to server, receives result, prints it.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 10200

int main() {
    int sockfd;
    struct sockaddr_in seraddr;
    char buffer[1024];

    // Step 1: Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // Step 2: Setup server address
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(PORTNO);
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // change if server is remote

    // Step 3: Connect to server
    if (connect(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        perror("connect");
        exit(1);
    }

    // Step 4: Take sentence from user
    printf("Enter a sentence: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Step 5: Send sentence to server
    write(sockfd, buffer, strlen(buffer) + 1);

    // Step 6: Receive result
    memset(buffer, 0, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));

    // Step 7: Print result
    printf("Processed sentence from server: %s\n", buffer);

    // Step 8: Close connection
    close(sockfd);
    return 0;
}
