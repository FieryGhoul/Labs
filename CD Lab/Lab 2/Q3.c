#include <stdio.h>
#include <string.h>
#include <ctype.h>

char keywords[][10] = {
    "int", "float", "char", "if", "else",
    "for", "while", "return", "void"
};

int isKeyword(char *word) {
    int i;
    for (i = 0; i < 9; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

void toUpper(char *word) {
    int i;
    for (i = 0; word[i]; i++)
        word[i] = toupper(word[i]);
}

int main() {
    FILE *fp;
    char word[50];

    fp = fopen("inputQ3.c", "r");
    printf("Keywords in UPPER CASE:\n");

    while (fscanf(fp, "%s", word) != EOF) {
        if (isKeyword(word)) {
            toUpper(word);
            printf("%s\n", word);
        }
    }

    fclose(fp);
    return 0;
}
