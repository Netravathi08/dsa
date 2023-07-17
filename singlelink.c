#include <stdio.h>
#include <stdlib.h>

typedef struct Passenger {
    int passengerId;
    struct Passenger* next;
} Passenger;

Passenger* addToWaitingList(Passenger* head, int passengerId) {
    Passenger* newPassenger = (Passenger*)malloc(sizeof(Passenger));
    newPassenger->passengerId = passengerId;
    newPassenger->next = NULL;

    if (head == NULL) {
        head = newPassenger;
    } else {
        Passenger* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newPassenger;
    }

    printf("Passenger with ID %d added to waiting list.\n", passengerId);

    return head;
}

void displayWaitingList(Passenger* head) {
    if (head == NULL) {
        printf("Waiting list is empty.\n");
        return;
    }

    Passenger* current = head;
    printf("Waiting List:\n");
    while (current != NULL) {
        printf("Passenger ID: %d\n", current->passengerId);
        current = current->next;
    }
}

void freeWaitingList(Passenger* head) {
    Passenger* current = head;
    while (current != NULL) {
        Passenger* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    Passenger* waitingList = NULL;

    waitingList = addToWaitingList(waitingList, 1001);
    waitingList = addToWaitingList(waitingList, 1002);
    waitingList = addToWaitingList(waitingList, 1003);

    displayWaitingList(waitingList);

    freeWaitingList(waitingList);

    return 0;
}

