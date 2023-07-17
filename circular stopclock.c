#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int hours;
    int minutes;
    int seconds;
    struct Node* next;
} Node;

Node* createNode(int hours, int minutes, int seconds) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->hours = hours;
    newNode->minutes = minutes;
    newNode->seconds = seconds;
    newNode->next = NULL;
    return newNode;
}

void insertNode(Node** head, int hours, int minutes, int seconds) {
    Node* newNode = createNode(hours, minutes, seconds);
    if (*head == NULL) {
        *head = newNode;
        newNode->next = newNode;  // Point back to itself to create a circular linked list
    } else {
        newNode->next = (*head)->next;
        (*head)->next = newNode;
        *head = newNode;
    }
}

void displayClock(Node* head) {
    if (head == NULL) {
        printf("Clock is empty.\n");
        return;
    }

    Node* current = head->next;
    printf("Clock:\n");
    do {
        printf("%02d:%02d:%02d\n", current->hours, current->minutes, current->seconds);
        current = current->next;
    } while (current != head->next);
}

void freeClock(Node** head) {
    if (*head == NULL) {
        return;
    }

    Node* current = (*head)->next;
    while (current != *head) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(*head);
    *head = NULL;
}

int main() {
    Node* clock = NULL;

    // Insert nodes representing time intervals
    insertNode(&clock, 0, 0, 0); // Start with 00:00:00
    insertNode(&clock, 0, 0, 5); // Add 5 seconds
    insertNode(&clock, 0, 1, 0); // Add 1 minute
    insertNode(&clock, 1, 0, 0); // Add 1 hour

    displayClock(clock);

    freeClock(&clock);

    return 0;
}
