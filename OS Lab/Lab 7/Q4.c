#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

#define SHM_KEY 0x1234
#define BOARD_SIZE 9

typedef struct {
    char board[BOARD_SIZE];  // 3x3 board flattened
    int turn;                // 0 or 1: player 0 or player 1's turn
    int moves;               // number of moves played
    int finished;            // 1 if game ended, 0 otherwise
    int winner;              // -1 no winner, 0 or 1 player won
} shared_data_t;

void print_board(char *board) {
    printf("\n");
    for (int i = 0; i < 9; i++) {
        char c = board[i] ? board[i] : ' ';
        printf(" %c ", c);
        if ((i + 1) % 3 == 0) printf("\n");
        else printf("|");
    }
    printf("\n");
}

int check_winner(char *board, char player_char) {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},  // rows
        {0,3,6}, {1,4,7}, {2,5,8},  // cols
        {0,4,8}, {2,4,6}            // diagonals
    };
    for (int i = 0; i < 8; i++) {
        if (board[wins[i][0]] == player_char &&
            board[wins[i][1]] == player_char &&
            board[wins[i][2]] == player_char) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <player_number (0 or 1)>\n", argv[0]);
        exit(1);
    }

    int player = atoi(argv[1]);
    if (player != 0 && player != 1) {
        printf("Player must be 0 or 1\n");
        exit(1);
    }

    int shmid = shmget(SHM_KEY, sizeof(shared_data_t), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    shared_data_t *data = (shared_data_t *)shmat(shmid, NULL, 0);
    if (data == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    // Initialize board if player 0 starts (first process)
    if (player == 0 && data->moves == 0 && data->finished == 0) {
        memset(data->board, 0, BOARD_SIZE);
        data->turn = 0;
        data->moves = 0;
        data->finished = 0;
        data->winner = -1;
    }

    char player_char = (player == 0) ? 'X' : 'O';

    printf("You are player %d (%c)\n", player, player_char);

    while (!data->finished) {
        if (data->turn == player) {
            print_board(data->board);
            printf("Your move (0-8): ");
            int pos;
            scanf("%d", &pos);

            if (pos < 0 || pos >= BOARD_SIZE) {
                printf("Invalid position. Try again.\n");
                continue;
            }
            if (data->board[pos] != 0) {
                printf("Position already taken. Try again.\n");
                continue;
            }

            data->board[pos] = player_char;
            data->moves++;

            if (check_winner(data->board, player_char)) {
                data->finished = 1;
                data->winner = player;
                print_board(data->board);
                printf("Player %d (%c) wins!\n", player, player_char);
                break;
            } else if (data->moves == BOARD_SIZE) {
                data->finished = 1;
                data->winner = -1;
                print_board(data->board);
                printf("Game is a draw.\n");
                break;
            }

            data->turn = 1 - player; // switch turn
        } else {
            printf("Waiting for player %d...\n", data->turn);
            sleep(1);
        }
    }

    // Game ended, detach shared memory
    shmdt(data);

    // Only player 0 removes shared memory after game ends
    if (player == 0 && data->finished) {
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}

