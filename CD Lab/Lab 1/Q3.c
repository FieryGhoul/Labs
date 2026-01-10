#include <stdio.h>

int main() {
    FILE *fp1, *fp2, *fp3;
    char line1[100], line2[100];

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("test2.txt", "r");
    fp3 = fopen("result.txt", "w");

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    while (fgets(line1, sizeof(line1), fp1) != NULL ||
           fgets(line2, sizeof(line2), fp2) != NULL) {

        if (!feof(fp1))
            fputs(line1, fp3);

        if (!feof(fp2))
            fputs(line2, fp3);
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    printf("Files merged alternately\n");
    return 0;
}
