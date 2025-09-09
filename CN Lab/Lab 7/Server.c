#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 10200
#define MAX_CLIENTS 10
#define BUF_SIZE 1024
#define SYM_KEY 'K'   // simple symmetric key (char)

int clients[MAX_CLIENTS];  // shared array of clients

// XOR encrypt/decrypt
void xor_encrypt_decrypt(char *msg, char key) {
    for (int i = 0; msg[i] != '\0'; i++) {
        msg[i] ^= key;
    }
}

// Broadcast message to all clients
void broadcast_message(char *msg, int sender_sock) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] != 0 && clients[i] != sender_sock) {
            send(clients[i], msg, strlen(msg), 0);
        }
    }
}

// Handle client communication
void *handle_client(void *arg) {
    int sock = *(int *)arg;
    char buffer[BUF_SIZE];

    // Step 1: Send symmetric key to client
    char key_msg[2] = {SYM_KEY, '\0'};
    send(sock, key_msg, strlen(key_msg), 0);

    while (1) {
        memset(buffer, 0, BUF_SIZE);
        int bytes = recv(sock, buffer, BUF_SIZE, 0);
        if (bytes <= 0) {
            printf("Client %d disconnected.\n", sock);
            close(sock);

            // Mark as removed
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i] == sock) {
                    clients[i] = 0;
                    break;
                }
            }
            break;
        }

        buffer[bytes] = '\0';

        // Decrypt incoming message
        xor_encrypt_decrypt(buffer, SYM_KEY);
        printf("Client(%d): %s\n", sock, buffer);

        // Re-encrypt and broadcast
        xor_encrypt_decrypt(buffer, SYM_KEY);
        broadcast_message(buffer, sock);
    }

    free(arg);
    pthread_exit(NULL);
}

int main() {
    int server_sock, new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_sock);
        exit(1);
    }

    // Listen
    if (listen(server_sock, MAX_CLIENTS) == -1) {
        perror("Listen failed");
        close(server_sock);
        exit(1);
    }

    printf("Server listening on port %d...\n", PORT);

    // Initialize client array
    for (int i = 0; i < MAX_CLIENTS; i++) clients[i] = 0;

    while (1) {
        addr_size = sizeof(client_addr);
        new_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        if (new_sock == -1) {
            perror("Accept failed");
            continue;
        }

        printf("New client connected: %d\n", new_sock);

        // Add client to array
        int added = 0;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] == 0) {
                clients[i] = new_sock;
                added = 1;
                break;
            }
        }

        if (!added) {
            printf("Max clients reached. Connection rejected.\n");
            close(new_sock);
        } else {
            pthread_t tid;
            int *pclient = malloc(sizeof(int));
            *pclient = new_sock;
            pthread_create(&tid, NULL, handle_client, pclient);
            pthread_detach(tid);
        }
    }

    close(server_sock);
    return 0;
}
