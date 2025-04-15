#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

// Insert at the end
void insertEnd(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

// Insert at the beginning
void insertBeginning(Node **head, int data) {
    Node *newNode = createNode(data);
    newNode->next = *head;
    if (*head) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Delete a node
void deleteNode(Node **head, int data) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node *temp = *head;
    if (temp->data == data) {
        *head = temp->next;
        if (*head) {
            (*head)->prev = NULL;
        }
        free(temp);
        return;
    }
    while (temp->next && temp->data != data) {
        temp = temp->next;
    }
    if (temp->data != data) {
        printf("Node not found!\n");
        return;
    }
    if (temp->next) {
        temp->next->prev = temp->prev;
    }
    if (temp->prev) {
        temp->prev->next = temp->next;
    }
    free(temp);
}

// Display the list
void display(Node *head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node *temp = head;
    while (temp) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Main function
int main() {
    Node *head = NULL;

    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertBeginning(&head, 5);
    display(head);

    deleteNode(&head, 10);
    display(head);

    return 0;
}
