#include <stdio.h>

int main() {
    FILE *fp1, *fp2;
    char line[200];

    fp1 = fopen("inputQ2.c", "r");
    fp2 = fopen("outputQ2.c", "w");

    while (fgets(line, sizeof(line), fp1)) {
        if (line[0] != '#') {
            fputs(line, fp2);
        }
    }

    fclose(fp1);
    fclose(fp2);

    printf("Preprocessor directives removed\n");
    return 0;
}
