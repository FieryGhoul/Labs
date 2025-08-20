#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define ROWS 3
#define COLS 3
#define SERVER_IP "172.16.48.73"
#define PORTNO 10200

int main() {
    int sd;
    struct sockaddr_in server_addr;
    char buf[100];
    int i;

    sd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNO);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    for (i = 0; i < ROWS; i++) {
        printf("Enter row %d elements (space separated %d integers): ", i + 1, COLS);
        fgets(buf, sizeof(buf), stdin);

        int sent_bytes = sendto(sd, buf, strlen(buf), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    }
    printf("All rows sent to server.\n");
    close(sd);
    return 0;
}
