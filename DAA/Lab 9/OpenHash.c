#include <stdio.h>
#include <stdlib.h>

#define MAX_KEY 1000

struct HashNode {
    int key;
    struct HashNode* next;
};

struct HashTable {
    int size;
    struct HashNode** table;
};

struct HashTable* createHashTable(int size) {
    struct HashTable* newTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    newTable->size = size;
    newTable->table = (struct HashNode**)malloc(sizeof(struct HashNode*) * size);
    for (int i = 0; i < size; i++) {
        newTable->table[i] = NULL;
    }
    return newTable;
}

//hash function
int hash(int key, int size) {
    return key % size;
}

void insert(struct HashTable* table, int key) {
    int index = hash(key, table->size);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode->key = key;
    newNode->next = table->table[index];
    table->table[index] = newNode;
}

int search(struct HashTable* table, int key, int* comparisons) {
    int index = hash(key, table->size);
    struct HashNode* current = table->table[index];
    *comparisons = 0;

    while (current != NULL) {
        (*comparisons)++;
        if (current->key == key) {
            return 1;  // Successful search
        }
        current = current->next;
    }
    return 0;
}

void deleteHashTable(struct HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        struct HashNode* current = table->table[i];
        while (current != NULL) {
            struct HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->table);
    free(table);
}

int main() {
    int sizes[] = {10, 20, 50};  //different sizes for hash tables
    int keys[] = {50, 100, 200};  //different numbers of keys to insert
    int successfulSearchComparisons, unsuccessfulSearchComparisons;

    // iterate over different hash table sizes and key counts
    for (int i = 0; i < 3; i++) {
        int m = sizes[i];  // hash table size
        for (int j = 0; j < 3; j++) {
            int n = keys[j];  // no. of keys to insert

            struct HashTable* table = createHashTable(m);

            for (int k = 0; k < n; k++) {
                insert(table, rand() % MAX_KEY);
            }

            //check the number of comparisons in successful and unsuccessful searches
            int comparisons = 0;
            int keyToSearch = rand() % MAX_KEY;
            int found = search(table, keyToSearch, &comparisons);
            printf("Table size: %d, Keys: %d, Searching key %d - ", m, n, keyToSearch);
            if (found) {
                printf("Successful search, Comparisons: %d\n", comparisons);
            } else {
                printf("Unsuccessful search, Comparisons: %d\n", comparisons);
            }

            deleteHashTable(table);
        }
    }

    return 0;
}
