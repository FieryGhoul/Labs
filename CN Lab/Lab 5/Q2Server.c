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
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buf[100];
    int matrix[ROWS][COLS];
    int row_count = 0;

    sd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORTNO);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    bind(sd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    while (row_count < ROWS) {
        memset(buf, 0, sizeof(buf));
        int received_bytes = recvfrom(sd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&client_addr, &addr_len);
        buf[received_bytes] = '\0';

        int col = 0;
        char *token = strtok(buf, " \n");
        while (token != NULL && col < COLS) {
            matrix[row_count][col] = atoi(token);
            token = strtok(NULL, " \n");
            col++;
        }

        printf("Received row %d\n", row_count + 1);
        row_count++;
    }
    printf("Complete matrix received:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    close(sd);
    return 0;
}

