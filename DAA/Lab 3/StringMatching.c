#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char text[100], p[50];
    int opcount = 0;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the pattern to search: ");
    fgets(p, sizeof(p), stdin);

    int tl = strlen(text);
    int pl = strlen(p);
    int found = 0;

    for (int i = 0; i <= tl - pl; i++) {
        for (int j = 0; j < pl; j++) {
            opcount++;
            if (text[i + j] != p[j]) {
                break;
            }
        }
        if (j == pl) {
            printf("Pattern found at index %d\n", i);
            found = 1;
        }
    }
    if (!found) {
        printf("Pattern not found.\n");
    }
    printf("opcount : %d\n", opcount);
}
