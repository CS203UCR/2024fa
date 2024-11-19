

// C program to to implement binary tree

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bst.h"
// Define a structure for tree nodes


// Function to create a new node
Node* createNode(int64_t data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function for inserting a node in a binary tree
void insert(Node** root, int64_t data)
{
    Node* newNode = createNode(data);
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    // Level order traversal to find the appropriate place
    // for insertion
    Node* temp;
    Node* queue[131072];
    int front = -1, rear = -1;
    queue[++rear] = *root;

    while (front != rear) {
        temp = queue[++front];

        //  Insert new node as the left child
        if (temp->left == NULL) {
            temp->left = newNode;
            return;
        }
        // if left child is not missing push it to the queue
        else {
            queue[++rear] = temp->left;
        }
        // Insert new node as the right child
        if (temp->right == NULL) {
            temp->right = newNode;
            return;
        }
        // if right child is not missing push it to the
        // queue
        else {
            queue[++rear] = temp->right;
        }
    }
}

// Function to perform level order traversal to find the
// deepest rightmost node
Node* getDeepestRightmostNode(Node* root)
{
    Node* temp;
    Node* queue[131072];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        temp = queue[++front];

        if (temp->left != NULL) {
            queue[++rear] = temp->left;
        }

        if (temp->right != NULL) {
            queue[++rear] = temp->right;
        }
    }
    return temp;
}

// Function for deleting deepest rightmost node in a binary
// tree
void deleteNodeDeepestRightmostNode(Node* root, Node* dNode)
{
    Node* temp;
    Node* queue[131072];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        temp = queue[++front];

        if (temp == dNode) {
            temp = NULL;
            free(dNode);
            return;
        }

        if (temp->right != NULL) {
            if (temp->right == dNode) {
                temp->right = NULL;
                free(dNode);
                return;
            }
            else {
                queue[++rear] = temp->right;
            }
        }

        if (temp->left != NULL) {
            if (temp->left == dNode) {
                temp->left = NULL;
                free(dNode);
                return;
            }
            else {
                queue[++rear] = temp->left;
            }
        }
    }
}

// Function to deleteNode a node in the binary tree
void deleteNode (Node** root, int64_t data)
{
    if (*root == NULL) {
        //printf("Tree is empty.\n");
        return;
    }

    if ((*root)->left == NULL && (*root)->right == NULL) {
        if ((*root)->data == data) {
            free(*root);
            *root = NULL;
            return;
        }
        else {
            //printf("Node not found.\n");
            return;
        }
    }

    Node* temp;
    Node* queue[131072];
    int front = -1, rear = -1;
    queue[++rear] = *root;
    Node* keyNode = NULL;

    while (front != rear) {
        temp = queue[++front];

        if (temp->data == data) {
            keyNode = temp;
        }

        if (temp->left != NULL) {
            queue[++rear] = temp->left;
        }

        if (temp->right != NULL) {
            queue[++rear] = temp->right;
        }
    }

    if (keyNode != NULL) {
        Node* deepestNode = getDeepestRightmostNode(*root);
        keyNode->data = deepestNode->data;
        deleteNodeDeepestRightmostNode(*root, deepestNode);
    }
    else {
        //printf("Node not found.\n");
    }
}

// Function to search for a node in the binary tree
Node* search(Node* root, int64_t data)
{
    if (root == NULL) {
        return NULL;
    }

    Node* temp;
    Node* queue[131072];
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        temp = queue[++front];

        if (temp->data == data) {
            return temp;
        }

        if (temp->left != NULL) {
            queue[++rear] = temp->left;
        }

        if (temp->right != NULL) {
            queue[++rear] = temp->right;
        }
    }
    return NULL;
}

// function to perform inorder traversal in a binary tree
int inorderTraversal(Node* root)
{
    int total=0;
    if (root == NULL) {
        return total;
    }
    total++;

    total += inorderTraversal(root->left);
    //printf("%ld ", root->data);
    total += inorderTraversal(root->right);
    return total;
}
/*
int main(int *data, unsigned int size, int threshold)
{

    Node* root = NULL;

    // Inserting nodes
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 50);
    insert(&root, 60);
    insert(&root, 70);
    insert(&root, 80);

    // Inorder traversal
    //printf("Inorder traversal of the given Binary Search "
           "Tree is: ");
    inorderTraversal(root);
    //printf("\n");

    // Deleting a node
    int deleteNodeValue = 20;
    deleteNode (&root, deleteNodeValue);
    //printf("After deletion of %d: ", deleteNodeValue);
    inorderTraversal(root);
    //printf("\n");

    // Inserting a new node
    int insertValue = 25;
    insert(&root, insertValue);
    //printf("After insertion of %d: ", insertValue);
    inorderTraversal(root);
    //printf("\n");

    // Searching for a node
    int target = 25;
    Node* searchResult = search(root, target);
    if (searchResult != NULL) {
        //printf("Node %d found in the BST.\n", target);
    }
    else {
        //printf("Node %d not found in the BST.\n", target);
    }

    return 0;
}
*/
