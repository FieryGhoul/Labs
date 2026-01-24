#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    char lexeme[30];
    char type[30];
    int row, col;
} Token;

char *keywords[] = {
    "int","char","float","if","else","while","return",NULL
};

int isKeyword(char *str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(keywords[i], str) == 0)
            return 1;
    }
    return 0;
}

Token getNextToken(FILE *fp) {
    static int row = 1, col = 0;
    Token t;
    char c;
    int i = 0;

    while ((c = fgetc(fp)) != EOF) {
        col++;

        if (c == '\n') {
            row++;
            col = 0;
            continue;
        }

        /* Ignore preprocessor */
        if (c == '#') {
            while (c != '\n')
                c = fgetc(fp);
            row++;
            col = 0;
            continue;
        }

        /* Ignore comments */
        if (c == '/') {
            char next = fgetc(fp);
            if (next == '/') {
                while (c != '\n')
                    c = fgetc(fp);
                row++;
                continue;
            } else if (next == '*') {
                while (!(c == '*' && fgetc(fp) == '/'))
                    c = fgetc(fp);
                continue;
            } else {
                ungetc(next, fp);
            }
        }

        /* Ignore string literals */
        if (c == '"') {
            while ((c = fgetc(fp)) != '"' && c != EOF);
            continue;
        }

        /* Identifier and keyword */
        if (isalpha(c)) {
            i = 0;
            t.lexeme[i++] = c;
            while (isalnum(c = fgetc(fp))) {
                t.lexeme[i++] = c;
                col++;
            }
            t.lexeme[i] = '\0';
            ungetc(c, fp);

            strcpy(t.type, isKeyword(t.lexeme) ? "KEYWORD" : "IDENTIFIER");
            t.row = row;
            t.col = col - strlen(t.lexeme) + 1;
            return t;
        }

        /* Number */
        if (isdigit(c)) {
            i = 0;
            t.lexeme[i++] = c;
            while (isdigit(c = fgetc(fp))) {
                t.lexeme[i++] = c;
                col++;
            }
            t.lexeme[i] = '\0';
            ungetc(c, fp);

            strcpy(t.type, "NUMBER");
            t.row = row;
            t.col = col - strlen(t.lexeme) + 1;
            return t;
        }

        /* Operators */
        if (strchr("+-*/<>=!", c)) {
            t.lexeme[0] = c;
            t.lexeme[1] = '\0';
            strcpy(t.type, "OPERATOR");
            t.row = row;
            t.col = col;
            return t;
        }

        /* Special Symbols */
        if (strchr(";(){}[],", c)) {
            t.lexeme[0] = c;
            t.lexeme[1] = '\0';
            strcpy(t.type, "SPECIAL SYMBOL");
            t.row = row;
            t.col = col;
            return t;
        }
    }

    strcpy(t.type, "EOF");
    return t;
}

int main() {
    FILE *fp = fopen("Q1Input.c", "r");
    Token t;

    while (strcmp((t = getNextToken(fp)).type, "EOF") != 0)
        printf("%s  %s  %d  %d\n", t.lexeme, t.type, t.row, t.col);

    fclose(fp);
    return 0;
}
