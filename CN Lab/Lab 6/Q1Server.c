// TCP Math Server (Single Client)
// Accepts two integers and an operator from client, performs calculation, sends result back.
// Terminates after serving one client.

#include "common.h"   // use the umbrella header file

#define PORTNO 10200  // Port number for server

int main() {
    int sockfd, newsockfd, clilen;
    struct sockaddr_in seraddr, cliaddr;
    char buffer[256];
    int n;

    // Step 1: Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // Step 2: Setup server address
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY;  // Accept any local IP
    seraddr.sin_port = htons(PORTNO);

    // Step 3: Bind socket to address
    if (bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        perror("bind");
        exit(1);
    }

    // Step 4: Listen for a single client
    listen(sockfd, 1);
    printf("Math Server waiting for client...\n");

    // Step 5: Accept one client connection
    clilen = sizeof(cliaddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&clilen);
    if (newsockfd < 0) {
        perror("accept");
        exit(1);
    }

    // Step 6: Read data from client
    memset(buffer, 0, sizeof(buffer));
    n = read(newsockfd, buffer, sizeof(buffer));
    if (n <= 0) {
        perror("read");
        close(newsockfd);
        close(sockfd);
        exit(1);
    }

    int a, b;
    char op;
    sscanf(buffer, "%d %c %d", &a, &op, &b);

    int result = 0;
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
            if (b != 0) result = a / b;
            else snprintf(buffer, sizeof(buffer), "Error: Division by zero");
            break;
        default:
            snprintf(buffer, sizeof(buffer), "Error: Invalid operator");
    }

    if (op != '/' || b != 0) {
        snprintf(buffer, sizeof(buffer), "Result = %d", result);
    }

    // Step 7: Send result back to client
    write(newsockfd, buffer, strlen(buffer) + 1);

    // Step 8: Close connection
    close(newsockfd);
    close(sockfd);

    printf("Server shutting down after one client.\n");
    return 0;
}
