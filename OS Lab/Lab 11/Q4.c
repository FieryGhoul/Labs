#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define MAX_BAD 10

// Structure for bad block table entry
struct BadBlock {
    int bad_block;
    int spare_block;
};

int main() {
    int total_blocks, spare_blocks;
    int file_start, file_length;
    int num_bad = 0;
    struct BadBlock bad_table[MAX_BAD];

    printf("Enter total number of disk blocks: ");
    scanf("%d", &total_blocks);

    printf("Enter number of spare blocks: ");
    scanf("%d", &spare_blocks);

    printf("Enter starting block of the file: ");
    scanf("%d", &file_start);

    printf("Enter length of the file (in blocks): ");
    scanf("%d", &file_length);

    int last_spare = total_blocks - spare_blocks + 1;

    printf("\nEnter number of bad blocks within the file: ");
    scanf("%d", &num_bad);

    printf("Enter bad block numbers:\n");
    for (int i = 0; i < num_bad; i++) {
        scanf("%d", &bad_table[i].bad_block);
        bad_table[i].spare_block = last_spare++;
    }

    printf("\nBad Blocks Table:\n");
    printf("Bad Block\tSpare Block\n");
    for (int i = 0; i < num_bad; i++) {
        printf("%d\t\t%d\n", bad_table[i].bad_block, bad_table[i].spare_block);
    }

    printf("\nFile stored from Block %d to Block %d\n", file_start, file_start + file_length - 1);
    printf("Spare blocks start from %d\n", total_blocks - spare_blocks + 1);

    printf("\nAccess Simulation:\n");
    for (int i = file_start; i < file_start + file_length; i++) {
        int replaced = 0;
        for (int j = 0; j < num_bad; j++) {
            if (bad_table[j].bad_block == i) {
                printf("Accessing Block %d -> Redirected to Spare Block %d\n",
                       i, bad_table[j].spare_block);
                replaced = 1;
                break;
            }
        }
        if (!replaced) {
            printf("Accessing Block %d (OK)\n", i);
        }
    }

    return 0;
}
