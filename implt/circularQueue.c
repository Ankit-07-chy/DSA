#include <stdio.h>
#include <stdlib.h>
#define SIZE 5 // You can change the size as needed

typedef struct {
    int items[SIZE];
    int front, rear;
} CircularQueue;

// Initialize the queue
void initQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is full
int isFull(CircularQueue *q) {
    return ((q->rear + 1) % SIZE == q->front);
}

// Check if the queue is empty
int isEmpty(CircularQueue *q) {
    return (q->front == -1);
}

// Enqueue operation
void enqueue(CircularQueue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full! Cannot enqueue %d\n", value);
        return;
    }

    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % SIZE;
    }

    q->items[q->rear] = value;
    printf("Enqueued: %d\n", value);
}

// Dequeue operation
int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue\n");
        return -1;
    }

    int value = q->items[q->front];

    if (q->front == q->rear) {
        // Queue has only one element
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % SIZE;
    }

    return value;
}

// Peek front element
int peek(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    return q->items[q->front];
}

// Display queue elements
void displayQueue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue elements: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

// Example main function
int main() {
    CircularQueue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50); // Should show full

    displayQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Dequeued: %d\n", dequeue(&q));

    displayQueue(&q);

    enqueue(&q, 60);
    enqueue(&q, 70); // Wrap-around should work

    displayQueue(&q);

    printf("Front element: %d\n", peek(&q));

    return 0;
}
