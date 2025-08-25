#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char line[1024];
    char *search_word;
    
    // Check if correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <search_word> <filename>\n", argv[0]);
        return 1;
    }
    
    search_word = argv[1];
    
    // Open the file
    file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", argv[2]);
        return 1;
    }
    
    // Read file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if the line contains the search word
        if (strstr(line, search_word) != NULL) {
            printf("%s", line);
        }
    }
    
    fclose(file);
    return 0;
}

/*
Compilation and usage:
gcc -o simple_grep simple_grep.c
./simple_grep "search_term" filename.txt
*/
