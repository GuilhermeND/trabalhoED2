// arvore.h

#ifndef ARVORE_H
#define ARVORE_H

typedef struct TreeNode {

    int value;

    struct TreeNode *left;
    struct TreeNode *right;

} TreeNode;



TreeNode *createNode(int value);

TreeNode *insertNode(TreeNode *root, int value);

TreeNode *searchNode(TreeNode *root, int value);

TreeNode *deleteNode(TreeNode *root, int value);

TreeNode *findMin(TreeNode *root);

void printInOrder(TreeNode *root);
void printPreOrder(TreeNode *root);
void printPostOrder(TreeNode *root);

void freeTree(TreeNode *root);

#endif