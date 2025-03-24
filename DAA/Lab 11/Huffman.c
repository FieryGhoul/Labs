#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_NODES 256

// Structure to represent a node in the Huffman tree
struct Node {
    char character;
    int frequency;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* createNode(char character, int frequency) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to compare two nodes (used for sorting)
int compare(const void *a, const void *b) {
    return ((struct Node*)a)->frequency - ((struct Node*)b)->frequency;
}

// Function to build the Huffman tree
struct Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    struct Node* nodes[MAX_TREE_NODES];
    for (int i = 0; i < size; i++) {
        nodes[i] = createNode(characters[i], frequencies[i]);
    }

    int n = size;
    while (n > 1) {
        // Sort the nodes based on frequency
        qsort(nodes, n, sizeof(struct Node*), compare);

        // Create a new internal node with the two lowest frequency nodes
        struct Node* left = nodes[0];
        struct Node* right = nodes[1];
        struct Node* newNode = createNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        // Replace the two lowest nodes with the new node
        nodes[1] = newNode;
        for (int i = 2; i < n; i++) {
            nodes[i - 1] = nodes[i];
        }
        n--;
    }

    return nodes[0]; // The root of the Huffman tree
}

// Function to print the Huffman codes
void printCodes(struct Node* root, int arr[], int top) {
    // If the node is a leaf node, print the character and its code
    if (root->left == NULL && root->right == NULL) {
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
        return;
    }

    // Traverse the left and right subtrees
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
}

// Main function
int main() {
    char input[] = "huffman coding example";
    int frequency[MAX_TREE_NODES] = {0};
    char characters[MAX_TREE_NODES];
    int size = 0;

    // Calculate frequency of each character
    for (int i = 0; input[i] != '\0'; i++) {
        frequency[(unsigned char)input[i]]++;
    }

    // Store characters and their frequencies
    for (int i = 0; i < MAX_TREE_NODES; i++) {
        if (frequency[i] > 0) {
            characters[size] = (char)i;
            size++;
        }
    }

    // Build the Huffman tree
    struct Node* root = buildHuffmanTree(characters, frequency, size);

    // Print the Huffman codes
    int arr[MAX_TREE_NODES], top = 0;
    printf("Huffman Codes:\n");
    printCodes(root, arr, top);

    return 0;
}
