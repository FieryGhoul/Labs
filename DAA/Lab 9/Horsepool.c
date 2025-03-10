#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256

void buildBadMatchTable(const char* pattern, int m, int badMatchTable[MAX_CHAR]) {
    for (int i = 0; i < MAX_CHAR; i++) {
        badMatchTable[i] = m;  // Set all characters' shift value to length of pattern
    }

    // Fill the table with actual shifts for each character in the pattern
    for (int i = 0; i < m - 1; i++) {
        badMatchTable[(int) pattern[i]] = m - i - 1;
    }
}

void horspoolSearch(const char* text, const char* pattern, int* comparisons) {
    int n = strlen(text);
    int m = strlen(pattern);
    
    if (m > n) {
        printf("Pattern not found\n");
        return;
    }

    int badMatchTable[MAX_CHAR];
    buildBadMatchTable(pattern, m, badMatchTable);
    
    int i = m - 1;
    *comparisons = 0;
    int found = 0;

    while (i < n) {
        int k = 0;

        // Compare pattern at position i
        while (k < m && pattern[m - 1 - k] == text[i - k]) {
            k++;
            (*comparisons)++;
        }

        // If the entire pattern matches, print the position
        if (k == m) {
            printf("Pattern found at position %d\n", i - m + 1);
            found = 1;
        }
        
        // Else, shift the pattern using the bad match table
        (*comparisons)++;
        i += badMatchTable[(int) text[i]];

    }

    if (!found) {
        printf("Pattern not found\n");
    }
}

int main() {
    const char* text = "THIS IS A TEST TEXT";
    const char* pattern = "IS";
    
    int comparisons = 0;
    horspoolSearch(text, pattern, &comparisons);
    printf("Number of comparisons in search: %d\n", comparisons);
    return 0;
}
    
