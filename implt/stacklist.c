#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Push to stack
void push(Node **top, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return;
    }
    newNode->data = value;
    newNode->next = *top;
    *top = newNode;
    printf("Pushed %d\n", value);
}

// Pop from stack
int pop(Node **top) {
    if (*top == NULL) {
        printf("Stack Underflow!\n");
        return -1;
    }
    Node *temp = *top;
    int popped = temp->data;
    *top = (*top)->next;
    free(temp);
    return popped;
}

// Peek top element
int peek(Node *top) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    return top->data;
}

// Display stack
void display(Node *top) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements: ");
    while (top) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

// Example usage
int main() {
    Node *stack = NULL;

    push(&stack, 100);
    push(&stack, 200);
    push(&stack, 300);
    display(stack);

    printf("Popped: %d\n", pop(&stack));
    printf("Top: %d\n", peek(stack));
    display(stack);

    return 0;
}
