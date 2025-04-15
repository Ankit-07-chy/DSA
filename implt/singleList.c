#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
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
}

// Insert at the beginning
void insertBeginning(Node **head, int data) {
    Node *newNode = createNode(data);
    newNode->next = *head;
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
        free(temp);
        return;
    }
    while (temp->next && temp->next->data != data) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Node not found!\n");
        return;
    }
    Node *toDelete = temp->next;
    temp->next = temp->next->next;
    free(toDelete);
}

// Display the list
void display(Node *head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node *temp = head;
    while (temp) {
        printf("%d -> ", temp->data);
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
