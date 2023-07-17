#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1000

struct StackNode {
    char text[MAX_TEXT_LENGTH];
    struct StackNode* next;
};

struct Stack {
    struct StackNode* top;
};

void initialize(struct Stack* stack) {
    stack->top = NULL;
}

int is_empty(struct Stack* stack) {
    return stack->top == NULL;
}

void push(struct Stack* stack, const char* text) {
    struct StackNode* new_node = (struct StackNode*)malloc(sizeof(struct StackNode));
    strcpy(new_node->text, text);
    new_node->next = stack->top;
    stack->top = new_node;
}

void pop(struct Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack is empty.\n");
        return;
    }

    struct StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
}

void display_top(struct Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Top of stack: %s\n", stack->top->text);
}

void free_stack(struct Stack* stack) {
    while (!is_empty(stack)) {
        pop(stack);
    }
}

int main() {
    struct Stack undo_stack;
    struct Stack redo_stack;
    initialize(&undo_stack);
    initialize(&redo_stack);

    // Simulating text edits
    push(&undo_stack, "Hello, world!");
    push(&undo_stack, "Hello, stack!");
    push(&undo_stack, "Hello, application!");

    display_top(&undo_stack);

    // Undo the last edit
    push(&redo_stack, undo_stack.top->text);
    pop(&undo_stack);

    display_top(&undo_stack);

    // Redo the undone edit
    push(&undo_stack, redo_stack.top->text);
    pop(&redo_stack);

    display_top(&undo_stack);

    free_stack(&undo_stack);
    free_stack(&redo_stack);

    return 0;
}
