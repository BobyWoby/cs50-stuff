#include <stdio.h>
#include <stdlib.h>


typedef struct tree{
    int number;
    struct tree *left;
    struct tree *right;
}treeNode;

typedef struct node{
    int number;
    struct node *next;
}node;

void free_tree(treeNode *root);
void print_tree(treeNode *root);

int main(void){
    treeNode *tree = NULL;

    treeNode *n = malloc(sizeof(tree));

    if(n == NULL){
        return 0;
    }
    n->number = 2;
    n->left = NULL;
    n->right = NULL;
    tree = n;

    n = malloc(sizeof(tree));
    if(n == NULL){
        //Free memory
        return 1;
    }
    n->number = 1;
    n->left = NULL;
    n->right = NULL;

    tree->left = n;

    n = malloc(sizeof(tree));
    if(n == NULL){
        //Free memory
        return 1;
    }
    n->number = 3;
    n->left = NULL;
    n->right = NULL;

    tree->right = n;


    print_tree(tree);
    return 0;
}

void free_tree(treeNode *root){
    if(root == NULL){
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);

}

void print_tree(treeNode *root){

    if(root == NULL){
        return;
    }

    print_tree(root->left);
    printf("%i\n", root->number);
    print_tree(root->right);
}