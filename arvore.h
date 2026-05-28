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


void freeTree(TreeNode *root);

#endif