// TCP Server (Single Client)
// Receives a sentence, removes duplicate words, and sends result back.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNO 10200

// Function to remove duplicate words (retain first occurrence only)
void remove_duplicates(char *input, char *output) {
    char *words[100];     // store pointers to words
    int word_count = 0;

    char temp[1024];
    strcpy(temp, input);

    // Tokenize the input string
    char *token = strtok(temp, " \t\n");
    while (token != NULL) {
        int found = 0;

        // check if already present
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            words[word_count] = strdup(token);
            word_count++;
        }

        token = strtok(NULL, " \t\n");
    }

    // Prepare result string
    strcpy(output, "");
    for (int i = 0; i < word_count; i++) {
        strcat(output, words[i]);
        strcat(output, " ");
        free(words[i]); // free allocated memory
    }
}

int main() {
    int sockfd, newsockfd, clilen;
    struct sockaddr_in seraddr, cliaddr;
    char buffer[1024], result[1024];
    int n;

    // Step 1: Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(1);
    }

    // Step 2: Setup server address
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY;
    seraddr.sin_port = htons(PORTNO);

    // Step 3: Bind
    if (bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0) {
        perror("bind");
        exit(1);
    }

    // Step 4: Listen for one client
    listen(sockfd, 1);
    printf("Server running... waiting for client.\n");

    // Step 5: Accept connection
    clilen = sizeof(cliaddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&clilen);
    if (newsockfd < 0) {
        perror("accept");
        exit(1);
    }

    // Step 6: Read sentence from client
    memset(buffer, 0, sizeof(buffer));
    n = read(newsockfd, buffer, sizeof(buffer));
    if (n <= 0) {
        perror("read");
        close(newsockfd);
        close(sockfd);
        exit(1);
    }

    printf("Received from client: %s\n", buffer);

    // Step 7: Process sentence
    remove_duplicates(buffer, result);

    // Step 8: Send result back to client
    write(newsockfd, result, strlen(result) + 1);

    // Step 9: Close sockets
    close(newsockfd);
    close(sockfd);

    printf("Server shutting down after one client.\n");
    return 0;
}
