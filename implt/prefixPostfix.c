#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define stack structure
#define MAX 100

typedef struct Stack {
    char arr[MAX][MAX]; // Array of strings
    int top;
} Stack;

// Initialize stack
void initStack(Stack *stack) {
    stack->top = -1;
}

// Check if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Push an element onto the stack
void push(Stack *stack, char *item) {
    if (stack->top == MAX - 1) {
        printf("Stack Overflow!\n");
        return;
    }
    strcpy(stack->arr[++stack->top], item);
}

// Pop an element from the stack
char* pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow!\n");
        return NULL;
    }
    return stack->arr[stack->top--];
}

// Peek the top element of the stack
char* peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty!\n");
        return NULL;
    }
    return stack->arr[stack->top];
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Function to convert prefix to postfix
void prefixToPostfix(char prefix[], char postfix[]) {
    Stack stack;
    initStack(&stack);

    // Reverse the prefix expression for easier processing
    int len = strlen(prefix);
    for (int i = len - 1; i >= 0; i--) {
        char ch = prefix[i];

        if (isalnum(ch)) { // If operand, push onto the stack
            char operand[2] = {ch, '\0'};
            push(&stack, operand);
        } else if (isOperator(ch)) { // If operator, pop two elements
            char *op1 = pop(&stack);
            char *op2 = pop(&stack);

            char temp[MAX];
            snprintf(temp, sizeof(temp), "%s%s%c", op1, op2, ch);
            push(&stack, temp); // Push the resulting expression
        }
    }

    // The final postfix expression will be the only element in the stack
    strcpy(postfix, pop(&stack));
}

// Function to convert postfix to prefix
void postfixToPrefix(char postfix[], char prefix[]) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; i < strlen(postfix); i++) {
        char ch = postfix[i];

        if (isalnum(ch)) { // If operand, push onto the stack
            char operand[2] = {ch, '\0'};
            push(&stack, operand);
        } else if (isOperator(ch)) { // If operator, pop two elements
            char *op2 = pop(&stack);
            char *op1 = pop(&stack);

            char temp[MAX];
            snprintf(temp, sizeof(temp), "%c%s%s", ch, op1, op2);
            push(&stack, temp); // Push the resulting expression
        }
    }

    // The final prefix expression will be the only element in the stack
    strcpy(prefix, pop(&stack));
}

// Main function
int main() {
    char prefix[MAX], postfix[MAX], result[MAX];
    int choice;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Convert Prefix to Postfix\n");
        printf("2. Convert Postfix to Prefix\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter a prefix expression: ");
            scanf("%s", prefix);
            prefixToPostfix(prefix, postfix);
            printf("Postfix expression: %s\n", postfix);
            break;

        case 2:
            printf("Enter a postfix expression: ");
            scanf("%s", postfix);
            postfixToPrefix(postfix, result);
            printf("Prefix expression: %s\n", result);
            break;

        case 3:
            exit(0);

        default:
            printf("Invalid choice. Try again!\n");
        }
    }

    return 0;
}
