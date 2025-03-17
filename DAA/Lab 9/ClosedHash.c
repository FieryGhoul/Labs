#include <stdio.h>
#include <stdlib.h>

#define MAX_KEY 1000
#define DELETED -1

struct HashTable {
    int* table;
    int size;
};

// Hash function
int hash(int key, int size) {
    return key % size;
}

struct HashTable* createHashTable(int size) {
    struct HashTable* newTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    newTable->size = size;
    newTable->table = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        newTable->table[i] = -1;  // Initialize with -1 (empty slot)
    }
    return newTable;
}

void insert(struct HashTable* table, int key) {
    int index = hash(key, table->size);
    int originalIndex = index;
    
    while (table->table[index] != -1 && table->table[index] != DELETED) {
        index = (index + 1) % table->size;
        if (index == originalIndex) {
            return;  // Table is full
        }
    }
    table->table[index] = key;
}

int search(struct HashTable* table, int key, int* comparisons) {
    int index = hash(key, table->size);
    int originalIndex = index;
    *comparisons = 0;

    while (table->table[index] != -1) {
        (*comparisons)++;
        if (table->table[index] == key) {
            return 1;  // Successful search
        }
        index = (index + 1) % table->size;
        if (index == originalIndex) {
            break;  // We have cycled back to the start
        }
    }
    return 0;  // Unsuccessful search
}

void deleteHashTable(struct HashTable* table) {
    free(table->table);
    free(table);
}

int main() {
    int sizes[] = {10, 20, 50};  // Different sizes for hash tables
    int keys[] = {50, 100, 200};  // Different numbers of keys to insert
    int successfulSearchComparisons, unsuccessfulSearchComparisons;

    // Iterate over different hash table sizes and key counts
    for (int i = 0; i < 3; i++) {
        int m = sizes[i];  // Hash table size
        for (int j = 0; j < 3; j++) {
            int n = keys[j];  // Number of keys to insert

            struct HashTable* table = createHashTable(m);

            // Insert 'n' random keys into the table
            for (int k = 0; k < n; k++) {
                insert(table, rand() % MAX_KEY);
            }

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
