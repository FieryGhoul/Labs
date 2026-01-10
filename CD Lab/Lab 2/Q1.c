#include <stdio.h>

int main() {
    FILE *fp1, *fp2;
    char ch;
    int space = 0;

    fp1 = fopen("testQ1.txt", "r");
    fp2 = fopen("outputQ1.txt", "w");

    while ((ch = fgetc(fp1)) != EOF) {
        if (ch == ' ' || ch == '\t') {
            if (space == 0) {
                fputc(' ', fp2);
                space = 1;
            }
        } else {
            fputc(ch, fp2);
            space = 0;
        }
    }

    fclose(fp1);
    fclose(fp2);

    printf("Spaces and tabs replaced successfully\n");
    return 0;
}
