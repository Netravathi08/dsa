#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// AVL Node structure
struct AVLNode {
    int fileNumber;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Function to get the height of a node
int getHeight(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new AVL node
struct AVLNode* createNode(int fileNumber) {
    struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    newNode->fileNumber = fileNumber;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to right rotate a subtree
struct AVLNode* rightRotate(struct AVLNode* node) {
    struct AVLNode* leftChild = node->left;
    struct AVLNode* rightChild = leftChild->right;

    // Perform rotation
    leftChild->right = node;
    node->left = rightChild;

    // Update heights
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    leftChild->height = max(getHeight(leftChild->left), getHeight(leftChild->right)) + 1;

    return leftChild;
}

// Function to left rotate a subtree
struct AVLNode* leftRotate(struct AVLNode* node) {
    struct AVLNode* rightChild = node->right;
    struct AVLNode* leftChild = rightChild->left;

    // Perform rotation
    rightChild->left = node;
    node->right = leftChild;

    // Update heights
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    rightChild->height = max(getHeight(rightChild->left), getHeight(rightChild->right)) + 1;

    return rightChild;
}

// Function to get the balance factor of a node
int getBalance(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a node into the AVL tree
struct AVLNode* insertNode(struct AVLNode* root, int fileNumber) {
    // Perform the normal BST insertion
    if (root == NULL)
        return createNode(fileNumber);

    if (fileNumber < root->fileNumber)
        root->left = insertNode(root->left, fileNumber);
    else if (fileNumber > root->fileNumber)
        root->right = insertNode(root->right, fileNumber);
    else // Duplicate fileNumber is not allowed
        return root;

    // Update the height of the current node
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

    // Check the balance factor and balance the tree if needed
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && fileNumber < root->left->fileNumber)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && fileNumber > root->right->fileNumber)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && fileNumber > root->left->fileNumber) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && fileNumber < root->right->fileNumber) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to print the AVL tree in inorder traversal
void inorderTraversal(struct AVLNode* root) {
    if (root == NULL)
        return;

    inorderTraversal(root->left);
    printf("%d ", root->fileNumber);
    inorderTraversal(root->right);
}

// Main function
int main() {
    struct AVLNode* root = NULL;
    int numFiles, i, fileNumber;

    printf("Enter the number of files: ");
    scanf("%d", &numFiles);

    srand(time(0)); // Initialize random seed

    printf("Randomly generated file numbers:\n");
    for (i = 0; i < numFiles; i++) {
        fileNumber = rand() % 1000; // Generate a random number between 0 and 999
        printf("%d ", fileNumber);
        root = insertNode(root, fileNumber);
    }
    printf("\n");

    printf("Inorder traversal of the AVL tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}

