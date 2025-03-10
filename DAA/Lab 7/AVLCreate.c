#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int data;
	struct Node *left;
	struct Node *right;
	int height;
}Node;

int height(Node *node){
	if(node==NULL){
		return 0;
	}
	return node->height;
}

int getBalance(Node *node){
	if(node==NULL){
		return 0;
	}
	return height(node->left)-height(node->right);
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    //perform rotation
    x->right = y;
    y->left = T2;

    //update heights
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    //perform rotation
    y->left = x;
    x->right = T2;

    //update heights
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}


Node *insert(Node *node, int data) {
    if (node == NULL) {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;  
        return newNode;
    }
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    } else {
        return node;
    }

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = getBalance(node);

    // ll
    if (balance > 1 && data < node->left->data) {
        return rightRotate(node);
    }

    // rr
    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }

    // lr
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // rl
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;

}
void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
} 

int main() {
    Node *root = NULL;
    int n, value;

    printf("Enter the number of nodes to insert: ");
    scanf("%d", &n);

    for (int i=0;i<n;i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("Inorder traversal of the AVL tree: ");
    inorder(root);
}
