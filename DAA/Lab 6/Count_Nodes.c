#include<stdio.h>
#include<stdlib.h>
struct node{
	int val;
	struct node *left,*right;
};

typedef struct node *NODE;
NODE root=NULL;

int c=0;

NODE insert(int ele,NODE node){
    NODE temp;
    if(node==NULL){
        temp=(NODE)malloc(sizeof(struct node));
        temp->val=ele;
        temp->left=temp->right=NULL;
        if(root==NULL)
            root=temp;
        return temp;
    }
    else if(ele<node->val){
        node->left=insert(ele,node->left);
        return node;
    }
    else if(ele>node->val){
        node->right=insert(ele,node->right);
        return node;
    }
    else{
        printf("Duplicate element found while inserting. Insertion failed\n");
        return NULL;
    }
}

int count(NODE node){
    if (node == NULL)
        c++;
        return 0;
    else
        c++;
        return 1 + count(node->left) + count(node->right);
}

int main(){
    int ele, a, b;
    printf("Enter elements for the tree (enter -1 to stop):\n");
    while(1){
        printf("Enter an element: ");
        scanf("%d", &ele);
        if(ele == -1)
            break;
        insert(ele, root);
    }
    printf("no of nodes in the tree : %d",count(root));
    printf("No of op : %d ",c);
}
