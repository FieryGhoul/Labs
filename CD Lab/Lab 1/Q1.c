#include <stdio.h>

int main() {
    FILE *fp;
    char ch;
    int lines = 0, chars = 0;

    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        printf("File cannot be opened\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        chars++;
        if (ch == '\n')
            lines++;
    }

    fclose(fp);

    printf("Number of characters = %d\n", chars);
    printf("Number of lines = %d\n", lines);

    return 0;
}

