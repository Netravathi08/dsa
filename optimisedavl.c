#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int getBalance(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

struct Node* insert(struct Node* root, int key);
struct Node* delete(struct Node* root, int key);

struct Node* insert(struct Node* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        // Duplicate keys are not allowed
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }

    // Left Right Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

struct Node* delete(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = delete(root->left, key);
    } else if (key > root->key) {
        root->right = delete(root->right, key);
    } else {
        // Node to be deleted found

        // Case 1: No child or only one child
        if (root->left == NULL || root->right == NULL) {
            struct Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                // One child case
                *root = *temp;
            }
            free(temp);
        } else {
            // Case 2: Two children
            struct Node* temp = minValueNode(root->right);

            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
    }

    // If the tree had only one node, return
    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }// Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        inorderTraversal(root->left, file);
        fprintf(file, "%d ", root->key);
        inorderTraversal(root->right, file);
    }
}

void preorderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d ", root->key);
        preorderTraversal(root->left, file);
        preorderTraversal(root->right, file);
    }
}

void postorderTraversal(struct Node* root, FILE* file) {
    if (root != NULL) {
        postorderTraversal(root->left, file);
        postorderTraversal(root->right, file);
        fprintf(file, "%d ", root->key);
    }
}

void displayTree(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        displayTree(root->left);
        displayTree(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    srand(time(NULL));

    FILE* inputFile = fopen("input.txt", "w");

    if (inputFile == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        int randomKey = rand() % 100;
        fprintf(inputFile, "%d\n", randomKey);
    }

    fclose(inputFile);

    FILE* input = fopen("input.txt", "r");

    if (input == NULL) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    while (fscanf(input, "%d", &key) != EOF) {
        root = insert(root, key);
    }

    fclose(input);

    while (1) {
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Display the tree\n");
        printf("4. Inorder traversal\n");
        printf("5. Preorder traversal\n");
        printf("6. Postorder traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the key to be inserted: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Node inserted successfully!\n");
                break;

            case 2:
                printf("Enter the key to be deleted: ");
                scanf("%d", &key);
                root = delete(root, key);
                printf("Node deleted successfully!\n");
                break;

            case 3:
                printf("Tree elements: ");
                displayTree(root);
                printf("\n");
                break;

            case 4: {
                FILE* file = fopen("inorder.txt", "w");
                inorderTraversal(root, file);
                fclose(file);
                printf("Inorder traversal stored in 'inorder.txt' file.\n");
                break;
            }

            case 5: {
                FILE* file = fopen("preorder.txt", "w");
                preorderTraversal(root, file);
                fclose(file);
                printf("Preorder traversal stored in 'preorder.txt' file.\n");
                break;
            }

            case 6: {
                FILE* file = fopen("postorder.txt", "w");
                postorderTraversal(root, file);
                fclose(file);
                printf("Postorder traversal stored in 'postorder.txt' file.\n");
                break;
            }

            case 7:
                printf("Exiting the program...\n");
                exit(0);


            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
