#include <stdio.h>
#include <string.h>

#define SIZE 10

char hashTable[SIZE][20];

// Simple hash function
int hash(char *key) {
    return strlen(key) % SIZE;
}

// SEARCH function
int search(char *key) {
    int index = hash(key);

    if (strcmp(hashTable[index], key) == 0)
        return index;

    return -1;
}

// INSERT function
void insert(char *str) {
    int index;

    index = search(str);
    if (index != -1) {
        printf("Verb '%s' already exists at index %d\n", str, index);
        return;
    }

    index = hash(str);
    strcpy(hashTable[index], str);
    printf("Inserted verb '%s' at index %d\n", str, index);
}

// Check if word is a verb (ends with "ing")
int isVerb(char *word) {
    int len = strlen(word);

    if (len > 3 && strcmp(word + len - 3, "ing") == 0)
        return 1;

    return 0;
}

int main() {
    char sentence[100], word[20];
    int i = 0, j = 0;

    printf("Enter a statement:\n");
    gets(sentence);

    while (sentence[i] != '\0') {
        j = 0;

        while (sentence[i] != ' ' && sentence[i] != '\0') {
            word[j++] = sentence[i++];
        }
        word[j] = '\0';

        if (isVerb(word)) {
            insert(word);
        }

        if (sentence[i] == ' ')
            i++;
    }

    return 0;
}

