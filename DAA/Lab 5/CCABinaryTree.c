#include<stdio.h>
#include<stdlib.h>
struct node{
	int val;
	struct node *left,*right;
};
typedef struct node *NODE;
NODE root=NULL;

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

NODE CCA(NODE root,int a,int b){
    if(root==NULL) return NULL;
    if(a<root->val && b<root->val) return CCA(root->left, a, b);
    if(a>root->val && b>root->val) return CCA(root->right, a, b);
    return root;
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
    printf("Enter two nodes to find the CCA: ");
    scanf("%d %d", &a, &b);
    NODE ccaNode = CCA(root, a, b);
    if(ccaNode != NULL)
        printf("The Closest Common Ancestor (CCA) of %d and %d is: %d\n", a, b, ccaNode->val);
    else
        printf("One or both of the nodes are not present in the tree.\n");
}
