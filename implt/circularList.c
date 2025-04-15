//herr
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
    newNode->next = newNode; // Points to itself initially for circular link
    return newNode;
}

// Insert at the end (circular behavior)
void insertEnd(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head; // Circular connection
    }
}

// Insert at the beginning (circular behavior)
void insertBeginning(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
        *head = newNode;
    }
}

// Delete a node
void deleteNode(Node **head, int data) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node *temp = *head, *prev = NULL;
    do {
        if (temp->data == data) {
            if (prev == NULL) { // Node to delete is head
                if (temp->next == *head) { // Only one node
                    free(temp);
                    *head = NULL;
                    return;
                } else {
                    prev = *head;
                    while (prev->next != *head) {
                        prev = prev->next;
                    }
                    *head = temp->next;
                    prev->next = *head;
                    free(temp);
                    return;
                }
            } else { // Node to delete is not head
                prev->next = temp->next;
                free(temp);
                return;
            }
        }
        prev = temp;
        temp = temp->next;
    } while (temp != *head);
    printf("Node not found!\n");
}

// Display the list (circular)
void display(Node *head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    Node *temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("(back to head)\n");
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
