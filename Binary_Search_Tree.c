#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node *createNode(int data) {
    Node *newNode=(Node*)malloc(sizeof(Node));
    if (newNode==NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

Node *insert(Node *root, int data) {
    if (root==NULL) {
        return createNode(data);
    }
    if (data<root->data) {
        root->left=insert(root->left,data);
    }
    else {
        root->right=insert(root->right,data);
    }
    return root;
}

void traverseTree(Node *root) { // traverses the tree in Inorder traversal i.e. Left subtree, Root, Right subtree
    if (root!=NULL) {
        traverseTree(root->left);
        printf("%d ",root->data);
        traverseTree(root->right);
    }
}

void freeTree(Node *root) { // this function frees the memory allocated to the tree by traversing it in a Post-Order traversal i.e. Left subtree, Right subtree, Root
    if (root != NULL) { 
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node *root=NULL;
    root=insert(root,20);
    root=insert(root,15);
    root=insert(root,30);
    root=insert(root,10);
    root=insert(root,7);
    printf("Inorder traversal of tree: ");
    traverseTree(root);
    freeTree(root);
    return 0;
}