#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUF_SIZE 1024
#define XOR_KEY 0xAA   // Simple symmetric key

int clients[MAX_CLIENTS];
int client_count = 0;

void xor_encrypt_decrypt(char *message) {
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= XOR_KEY;
    }
}

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[BUF_SIZE];
    int n;

    while ((n = recv(client_socket, buffer, BUF_SIZE, 0)) > 0) {
        buffer[n] = '\0';

        // Decrypt the message
        xor_encrypt_decrypt(buffer);

        printf("Received: %s\n", buffer);

        // Re-encrypt before broadcasting
        xor_encrypt_decrypt(buffer);

        // Broadcast to all clients except sender
        for (int i = 0; i < client_count; i++) {
            if (clients[i] != client_socket) {
                send(clients[i], buffer, strlen(buffer), 0);
            }
        }
    }

    // Remove client when disconnected
    for (int i = 0; i < client_count; i++) {
        if (clients[i] == client_socket) {
            for (int j = i; j < client_count - 1; j++) {
                clients[j] = clients[j + 1];
            }
            client_count--;
            break;
        }
    }

    close(client_socket);
    return NULL;
}

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    pthread_t tid;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind error");
        exit(1);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen error");
        exit(1);
    }

    printf("Server started on port %d...\n", PORT);

    while (1) {
        addr_size = sizeof(client_addr);
        new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);

        if (new_socket >= 0) {
            printf("Client connected.\n");
            clients[client_count++] = new_socket;
            pthread_create(&tid, NULL, handle_client, &new_socket);
            pthread_detach(tid);
        }
    }

    close(server_socket);
    return 0;
}
