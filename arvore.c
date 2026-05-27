// arvore.c

#include <stdio.h>
#include <stdlib.h>

#include "arvore.h"



TreeNode *createNode(int value) {

    TreeNode *newNode;

    newNode = (TreeNode *) malloc(sizeof(TreeNode));

    if (newNode == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    newNode->value = value;

    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}



TreeNode *insertNode(TreeNode *root, int value) {

    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->value) {
        root->left = insertNode(root->left, value);
    }

    else if (value > root->value) {
        root->right = insertNode(root->right, value);
    }

    return root;
}



TreeNode *searchNode(TreeNode *root, int value) {

    if (root == NULL || root->value == value) {
        return root;
    }

    if (value < root->value) {
        return searchNode(root->left, value);
    }

    return searchNode(root->right, value);
}



TreeNode *findMin(TreeNode *root) {

    while (root != NULL && root->left != NULL) {
        root = root->left;
    }

    return root;
}



TreeNode *deleteNode(TreeNode *root, int value) {

    TreeNode *temp;

    if (root == NULL) {
        return root;
    }

    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    }

    else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    }

    else {

        // Node with only one child or no child
        if (root->left == NULL) {

            temp = root->right;

            free(root);

            return temp;
        }

        else if (root->right == NULL) {

            temp = root->left;

            free(root);

            return temp;
        }

        // Node with two children
        temp = findMin(root->right);

        root->value = temp->value;

        root->right = deleteNode(root->right, temp->value);
    }

    return root;
}


void printInOrder(TreeNode *root) {

    if (root == NULL)
        return;

    printInOrder(root->left);

    printf("%d ", root->value);

    printInOrder(root->right);
}



void printPreOrder(TreeNode *root) {

    if (root == NULL)
        return;

    printf("%d ", root->value);

    printPreOrder(root->left);

    printPreOrder(root->right);
}


void printPostOrder(TreeNode *root) {

    if (root == NULL)
        return;

    printPostOrder(root->left);

    printPostOrder(root->right);

    printf("%d ", root->value);
}


void freeTree(TreeNode *root) {

    if (root == NULL)
        return;

    freeTree(root->left);

    freeTree(root->right);

    free(root);
}