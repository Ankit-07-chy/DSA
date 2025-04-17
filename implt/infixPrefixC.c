#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define stack structure
#define MAX 100

typedef struct Stack {
    char arr[MAX][MAX];
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
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to get precedence of operators
int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    }
    return 0;
}

// Function to reverse a string
void reverse(char* str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Function to convert infix to prefix
void infixToPrefix(char infix[], char prefix[]) {
    Stack operators;
    initStack(&operators);

    char result[MAX] = "";  // Result string
    reverse(infix);  // Reverse the infix expression

    for (int i = 0; i < strlen(infix); i++) {
        char ch = infix[i];

        if (isalnum(ch)) {  // If operand, append to result
            char operand[2] = {ch, '\0'};
            strcat(result, operand);
        } else if (ch == ')') {  // Push closing parenthesis
            push(&operators, ")");
        } else if (ch == '(') {  // Pop until closing parenthesis is found
            while (!isEmpty(&operators) && strcmp(peek(&operators), ")") != 0) {
                strcat(result, pop(&operators));
            }
            pop(&operators);  // Remove closing parenthesis
        } else if (isOperator(ch)) {  // Operator case
            while (!isEmpty(&operators) &&
                   precedence(ch) <= precedence(peek(&operators)[0])) {
                strcat(result, pop(&operators));
            }
            char operator[2] = {ch, '\0'};
            push(&operators, operator);
        }
    }

    // Append remaining operators
    while (!isEmpty(&operators)) {
        strcat(result, pop(&operators));
    }

    reverse(result);  // Reverse the result to get prefix
    strcpy(prefix, result);
}

// Function to convert prefix to infix
void prefixToInfix(char prefix[], char infix[]) {
    Stack stack;
    initStack(&stack);

    reverse(prefix);  // Reverse the prefix expression

    for (int i = 0; i < strlen(prefix); i++) {
        char ch = prefix[i];

        if (isalnum(ch)) {  // If operand, push to stack
            char operand[2] = {ch, '\0'};
            push(&stack, operand);
        } else if (isOperator(ch)) {  // If operator, pop two elements
            char *op1 = pop(&stack);
            char *op2 = pop(&stack);

            char temp[MAX];
            snprintf(temp, sizeof(temp), "(%s%c%s)", op1, ch, op2);
            push(&stack, temp);  // Push the resulting string
        }
    }

    // The final infix expression will be the only element in the stack
    strcpy(infix, pop(&stack));
}

// Main function
int main() {
    char infix[MAX], prefix[MAX], result[MAX];
    int choice;

    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Convert Infix to Prefix\n");
        printf("2. Convert Prefix to Infix\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter an infix expression: ");
            scanf("%s", infix);
            infixToPrefix(infix, prefix);
            printf("Prefix expression: %s\n", prefix);
            break;

        case 2:
            printf("Enter a prefix expression: ");
            scanf("%s", prefix);
            prefixToInfix(prefix, result);
            printf("Infix expression: %s\n", result);
            break;

        case 3:
            exit(0);

        default:
            printf("Invalid choice. Try again!\n");
        }
    }

    return 0;
}
