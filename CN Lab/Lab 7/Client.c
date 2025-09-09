#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUF_SIZE 1024
#define XOR_KEY 0xAA

int client_socket;

void xor_encrypt_decrypt(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= XOR_KEY;
    }
}

void *receive_messages(void *arg) {
    char buffer[BUF_SIZE];
    int n;
    while ((n = recv(client_socket, buffer, BUF_SIZE, 0)) > 0) {
        buffer[n] = '\0';

        // Decrypt before displaying
        xor_encrypt_decrypt(buffer);
        printf("\nMessage: %s\n", buffer);
    }
    return NULL;
}

int main() {
    struct sockaddr_in server_addr;
    pthread_t recv_thread;
    char buffer[BUF_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect error");
        exit(1);
    }

    printf("Connected to server. Start chatting!\n");

    pthread_create(&recv_thread, NULL, receive_messages, NULL);

    while (1) {
        printf("You: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        xor_encrypt_decrypt(buffer);
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
    return 0;
}
