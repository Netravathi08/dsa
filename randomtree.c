
#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the binary tree
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return root;
    } else if (data <= root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Function to perform inorder traversal
void inorderTraversal(Node* root, FILE* output) {
    if (root == NULL)
        return;

    inorderTraversal(root->left, output);
    fprintf(output, "%d ", root->data);
    inorderTraversal(root->right, output);
}

// Function to perform preorder traversal
void preorderTraversal(Node* root, FILE* output) {
    if (root == NULL)
        return;

    fprintf(output, "%d ", root->data);
    preorderTraversal(root->left, output);
    preorderTraversal(root->right, output);
}

// Function to perform postorder traversal
void postorderTraversal(Node* root, FILE* output) {
    if (root == NULL)
        return;

    postorderTraversal(root->left, output);
    postorderTraversal(root->right, output);
    fprintf(output, "%d ", root->data);
}



int main() {
    FILE* input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    // Create an empty binary tree
    Node* root = NULL;
    int num;

    // Read the numbers from the input file and insert them into the tree
    while (fscanf(input, "%d", &num) == 1) {
        root = insertNode(root, num);
    }

    fclose(input);

    FILE* inorderOutput = fopen("inorder.txt", "w");
    if (inorderOutput == NULL) {
        printf("Failed to open inorder output file.\n");
        return 1;
    }

    FILE* preorderOutput = fopen("preorder.txt", "w");
    if (preorderOutput == NULL) {
        printf("Failed to open preorder output file.\n");
        return 1;
    }

    FILE* postorderOutput = fopen("postorder.txt", "w");
    if (postorderOutput == NULL) {
        printf("Failed to open postorder output file.\n");
        return 1;
    }

    // Perform inorder, preorder, and postorder traversals
    inorderTraversal(root, inorderOutput);
    preorderTraversal(root, preorderOutput);
    postorderTraversal(root, postorderOutput);

    fclose(inorderOutput);
    fclose(preorderOutput);
    fclose(postorderOutput);



    return 0;
}
