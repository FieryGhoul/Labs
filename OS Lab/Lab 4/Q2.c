#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char line[1024];
    int line_count = 0;
    int i;
    
    if (argc < 2) {
        printf("Usage: %s <file1> [file2] ...\n", argv[0]);
        return 1;
    }
    
    // Process each file
    for (i = 1; i < argc; i++) {
        file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("Error: Cannot open file %s\n", argv[i]);
            continue;
        }
        
        printf("\n==> %s <==\n", argv[i]);
        line_count = 0;
        
        // Read and display file line by line
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
            line_count++;
            
            // After every 20 lines, wait for user input
            if (line_count % 20 == 0) {
                printf("--More-- (Press any key to continue, 'q' to quit this file)");
                int ch = getchar();
                if (ch == 'q' || ch == 'Q') {
                    break;
                }
                // Clear any remaining characters in input buffer
                while (getchar() != '\n' && ch != '\n');
            }
        }
        
        fclose(file);
    }
    
    return 0;
}

/*
Compilation and usage:
gcc -o simple_more simple_more.c
./simple_more file1.txt file2.txt
*/
