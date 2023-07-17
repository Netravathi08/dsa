#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in a binary tree
struct Node* insertNode(struct Node* root, int data)
{
    if (root == NULL) {
        root = createNode(data);
    }
    else {
        if (data <= root->data) {
            root->left = insertNode(root->left, data);
        }
        else {
            root->right = insertNode(root->right, data);
        }
    }
    return root;
}

// Function to count siblings at each level in a binary tree
void countSiblingsAtEachLevel(struct Node* root)
{
    if (root == NULL)
        return;

    struct Node* queue[100];  // Assuming the maximum number of nodes in the tree is 100
    int front = 0, rear = 0;
    int currentLevelNodes = 1;
    int nextLevelNodes = 0;
    int siblings = 0;
    int level = 0;

    queue[rear++] = root;

    while (front < rear)
    {
        struct Node* current = queue[front++];
        currentLevelNodes--;

        if (current->left != NULL)
        {
            queue[rear++] = current->left;
            nextLevelNodes++;
        }
        if (current->right != NULL)
        {
            queue[rear++] = current->right;
            nextLevelNodes++;
        }

        if (currentLevelNodes == 0)
        {
            printf("Level %d: %d siblings\n", level,(siblings+1));
            level++;
            siblings = 0;
            currentLevelNodes = nextLevelNodes;
            nextLevelNodes = 0;
        }
        else
        {
            siblings++;
        }
    }
}

// Function to display the tree structure
void displayTree(struct Node* root, int level)
{
    if (root == NULL)
        return;

    displayTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("%d\n", root->data);

    displayTree(root->left, level + 1);
}

int main() {
    struct Node* root = NULL;
    int numNodes, value;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    for (int i = 0; i < numNodes; i++)
    {
        printf("Enter the value of node %d: ", i + 1);
        scanf("%d", &value);
        root = insertNode(root, value);
    }

    printf("\nTree Structure:\n");
    displayTree(root, 0);

    printf("\nCounting siblings at each level:\n");
    countSiblingsAtEachLevel(root);

    return 0;
}
