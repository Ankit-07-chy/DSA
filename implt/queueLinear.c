#include <stdio.h>
#include <stdlib.h>

// Node of the queue
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

// Queue structure with front and rear pointers
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Create a new node
QueueNode* createNode(int data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Initialize queue
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Enqueue operation
void enqueue(Queue* q, int data) {
    QueueNode* newNode = createNode(data);
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

// Dequeue operation
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue underflow!\n");
        return -1;
    }

    QueueNode* temp = q->front;
    int val = temp->data;

    q->front = q->front->next;

    // If queue becomes empty
    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return val;
}

// Peek at front element
int peek(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->front->data;
}

// Display queue
void displayQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }

    QueueNode* temp = q->front;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Free all nodes
void clearQueue(Queue* q) {
    while (!isEmpty(q))
        dequeue(q);
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    displayQueue(&q);

    printf("Front element: %d\n", peek(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q)); // underflow

    displayQueue(&q);
    clearQueue(&q);

    return 0;
}
