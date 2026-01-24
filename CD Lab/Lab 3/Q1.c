#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][10] = {
    "int","char","if","else","while","for","return","void"
};

int isKeyword(char str[]) {
    for (int i = 0; i < 8; i++) {
        if (strcmp(keywords[i], str) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, buf[20];
    int i;

    fp = fopen("Q1Input.c", "r");

    while ((ch = fgetc(fp)) != EOF) {

        /* Identifier and keyword */
        if (isalpha(ch)) {
            i = 0;
            buf[i++] = ch;

            while (isalnum(ch = fgetc(fp)))
                buf[i++] = ch;

            buf[i] = '\0';
            ungetc(ch, fp);

            if (isKeyword(buf))
                printf("Keyword: %s\n", buf);
            else
                printf("Identifier: %s\n", buf);
        }

        /* Numeric constant */
        else if (isdigit(ch)) {
            i = 0;
            buf[i++] = ch;

            while (isdigit(ch = fgetc(fp)))
                buf[i++] = ch;

            buf[i] = '\0';
            ungetc(ch, fp);

            printf("Number: %s\n", buf);
        }

        /* Operators */
        else if (strchr("+-*/%=<>!", ch)) {
            printf("Operator: %c\n", ch);
        }

        /*special symbols*/
        else if (strchr(";,(){}", ch)) {
            printf("Special Symbol: %c\n", ch);
        }
    }

    fclose(fp);
}
