#include <stdio.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 100

// Queue implementation using an array
typedef struct {
    int items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// Function to create an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Function to check if the queue is empty
bool isEmpty(Queue* queue) {
    return (queue->front == -1);
}

// Function to check if the queue is full
bool isFull(Queue* queue) {
    return (queue->rear == MAX_QUEUE_SIZE - 1);
}

// Function to add an item to the queue
void enqueue(Queue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue more elements.\n");
        return;
    }
    if (isEmpty(queue))
        queue->front = 0;
    queue->rear++;
    queue->items[queue->rear] = item;
}

// Function to remove an item from the queue
int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue elements.\n");
        return -1;
    }
    int item = queue->items[queue->front];
    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front++;
    }
    return item;
}

// Function to perform Breadth-First Search
void BFS(int graph[][7], int startVertex, int numVertices) {
    // Create a visited array to keep track of visited vertices
    bool visited[numVertices];
    for (int i = 0; i < numVertices; ++i)
        visited[i] = false;

    // Create a queue for BFS
    Queue* queue = createQueue();

    // Mark the current node as visited and enqueue it
    visited[startVertex] = true;
    enqueue(queue, startVertex);

    printf("BFS Traversal: ");

    // Iterate until the queue is empty
    while (!isEmpty(queue)) {
        // Dequeue a vertex from the queue and print it
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        // Visit all the adjacent vertices of the dequeued vertex
        for (int i = 0; i < numVertices; ++i) {
            if (graph[currentVertex][i] && !visited[i]) {
                // Mark the adjacent vertex as visited and enqueue it
                visited[i] = true;
                enqueue(queue, i);
            }
        }
    }

    printf("\n");
}

int main() {
    int graph[][7] = {{0, 1, 1, 0, 0, 0, 0},
                      {1, 0, 0, 1, 1, 0, 0},
                      {1, 0, 0, 0, 1, 0, 0},
                      {0, 1, 0, 0, 1, 1, 0},
                      {0, 1, 1, 1, 0, 1, 0},
                      {0, 0, 0, 1, 1, 0, 1},
                      {0, 0, 0, 0, 0, 1, 0}};

    int numVertices = sizeof(graph) / sizeof(graph[0]);
    int startVertex = 0;

    BFS(graph, startVertex, numVertices);

    return 0;
}
