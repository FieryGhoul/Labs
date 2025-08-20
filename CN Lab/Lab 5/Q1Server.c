#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORTNO 10200
#define MAX 256

void remove_duplicates(char *input, char *output) {
    char *words[100];
    int count = 0;
    char *token = strtok(input, " \n");
    
    while (token != NULL) {
        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(words[i], token) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) {
            words[count++] = token;
        }
        token = strtok(NULL, " \n");
    }
    output[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcat(output, words[i]);
        if (i < count - 1)
            strcat(output, " ");
    }
}


int main() {
    int sockfd, newsockfd;
    struct sockaddr_in seraddr, cliaddr;
    socklen_t clilen;
    char buf[MAX];
    char outbuf[MAX];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("172.16.48.73");
    seraddr.sin_port = htons(PORTNO);

    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);

    printf("server waiting.");

    while (1) {
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

        while (1) {
            memset(buf, 0, sizeof(buf));
            int n = read(newsockfd, buf, sizeof(buf) - 1);
            buf[n] = '\0';
            printf("Message from Client: %s\n", buf);

            remove_duplicates(buf, outbuf);
            write(newsockfd, outbuf, strlen(outbuf));
        }
        close(newsockfd);
    }
    close(sockfd);
}
