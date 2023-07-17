#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int rollNumber;
    char name[100];
    struct Student* next;
};

struct StudentList {
    struct Student* head;
};

void initialize(struct StudentList* list) {
    list->head = NULL;
}

int is_empty(struct StudentList* list) {
    return list->head == NULL;
}

void add_student(struct StudentList* list, int rollNumber, const char* name) {
    struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));
    new_student->rollNumber = rollNumber;
    strcpy(new_student->name, name);
    new_student->next = NULL;

    if (is_empty(list)) {
        list->head = new_student;
    } else {
        struct Student* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_student;
    }

    printf("Student added: Roll Number: %d, Name: %s\n", rollNumber, name);
}

void search_student(struct StudentList* list, int rollNumber) {
    if (is_empty(list)) {
        printf("Student list is empty.\n");
        return;
    }

    struct Student* current = list->head;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            printf("Student found: Roll Number: %d, Name: %s\n", current->rollNumber, current->name);
            return;
        }
        current = current->next;
    }

    printf("Student with Roll Number %d not found.\n", rollNumber);
}

void update_student(struct StudentList* list, int rollNumber, const char* name) {
    if (is_empty(list)) {
        printf("Student list is empty.\n");
        return;
    }

    struct Student* current = list->head;
    while (current != NULL) {
        if (current->rollNumber == rollNumber) {
            strcpy(current->name, name);
            printf("Student details updated: Roll Number: %d, Updated Name: %s\n", current->rollNumber, current->name);
            return;
        }
        current = current->next;
    }

    printf("Student with Roll Number %d not found.\n", rollNumber);
}

void delete_student(struct StudentList* list, int rollNumber) {
    if (is_empty(list)) {
        printf("Student list is empty.\n");
        return;
    }

    struct Student* current = list->head;
    struct Student* prev = NULL;

    while (current != NULL && current->rollNumber != rollNumber) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student with Roll Number %d not found.\n", rollNumber);
        return;
    }

    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Student with Roll Number %d deleted.\n", rollNumber);
}

void display_students(struct StudentList* list) {
    if (is_empty(list)) {
        printf("Student list is empty.\n");
        return;
    }

    struct Student* current = list->head;
    printf("Student List:\n");
    while (current != NULL) {
        printf("Roll Number: %d, Name: %s\n", current->rollNumber, current->name);
        current = current->next;
    }
}

void free_student_list(struct StudentList* list) {
    struct Student* current = list->head;
    while (current != NULL) {
        struct Student* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

int main() {
    struct StudentList student_list;
    initialize(&student_list);

    add_student(&student_list, 101, "John Doe");
    add_student(&student_list, 102, "Jane Smith");
    add_student(&student_list, 103, "Alice Johnson");

    display_students(&student_list);

    printf("\n");

    search_student(&student_list, 102);

    printf("\n");

    update_student(&student_list, 101, "John Smith");

    printf("\n");

    delete_student(&student_list, 103);

    printf("\n");

    display_students(&student_list);

    free_student_list(&student_list);

    return 0;
}
