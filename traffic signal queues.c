#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct Vehicle {
    int vehicleId;
    struct Vehicle* next;
} Vehicle;

typedef struct Queue {
    Vehicle* front;
    Vehicle* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isQueueEmpty(Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(Queue* queue, int vehicleId) {
    Vehicle* newVehicle = (Vehicle*)malloc(sizeof(Vehicle));
    newVehicle->vehicleId = vehicleId;
    newVehicle->next = NULL;

    if (isQueueEmpty(queue)) {
        queue->front = newVehicle;
        queue->rear = newVehicle;
    } else {
        queue->rear->next = newVehicle;
        queue->rear = newVehicle;
    }

    printf("Vehicle with ID %d added to the queue.\n", vehicleId);
}

void dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    Vehicle* frontVehicle = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    printf("Vehicle with ID %d dequeued.\n", frontVehicle->vehicleId);
    free(frontVehicle);
}

void displayQueue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    Vehicle* current = queue->front;
    printf("Queue:\n");
    while (current != NULL) {
        printf("Vehicle ID: %d\n", current->vehicleId);
        current = current->next;
    }
}

void freeQueue(Queue* queue) {
    while (!isQueueEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

int main() {
    Queue* intersectionQueue = createQueue();

    enqueue(intersectionQueue, 1001);
    enqueue(intersectionQueue, 1002);
    enqueue(intersectionQueue, 1003);

    displayQueue(intersectionQueue);

    dequeue(intersectionQueue);

    displayQueue(intersectionQueue);

    freeQueue(intersectionQueue);

    return 0;
}

