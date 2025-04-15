#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct MinHeap {
    int size;
    int arr[MAX_SIZE];
} MinHeap;

// Function prototypes
void initMinHeap(MinHeap *heap);
void insert(MinHeap *heap, int key);
void heapifyUp(MinHeap *heap, int index);
void heapifyDown(MinHeap *heap, int index);
int extractMin(MinHeap *heap);
int getMin(MinHeap *heap);
void decreaseKey(MinHeap *heap, int index, int newVal);
void deleteKey(MinHeap *heap, int index);
void changePriority(MinHeap *heap, int index, int newVal);
void displayHeap(MinHeap *heap);

// Initialize heap
void initMinHeap(MinHeap *heap) {
    heap->size = 0;
}

// Get parent index
int parent(int i) { return (i - 1) / 2; }
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

// Insert key
void insert(MinHeap *heap, int key) {
    if (heap->size == MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }

    heap->arr[heap->size] = key;
    heapifyUp(heap, heap->size);
    heap->size++;
}

// Heapify up
void heapifyUp(MinHeap *heap, int index) {
    while (index != 0 && heap->arr[parent(index)] > heap->arr[index]) {
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[parent(index)];
        heap->arr[parent(index)] = temp;
        index = parent(index);
    }
}

// Heapify down
void heapifyDown(MinHeap *heap, int index) {
    int smallest = index;
    int l = left(index);
    int r = right(index);

    if (l < heap->size && heap->arr[l] < heap->arr[smallest])
        smallest = l;
    if (r < heap->size && heap->arr[r] < heap->arr[smallest])
        smallest = r;

    if (smallest != index) {
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[smallest];
        heap->arr[smallest] = temp;

        heapifyDown(heap, smallest);
    }
}

// Extract min
int extractMin(MinHeap *heap) {
    if (heap->size <= 0)
        return INT_MAX;
    if (heap->size == 1)
        return heap->arr[--heap->size];

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    heapifyDown(heap, 0);

    return root;
}

// Get min
int getMin(MinHeap *heap) {
    if (heap->size <= 0)
        return INT_MAX;
    return heap->arr[0];
}

// Decrease key
void decreaseKey(MinHeap *heap, int index, int newVal) {
    if (newVal > heap->arr[index]) {
        printf("New value is greater than current value. Use changePriority instead.\n");
        return;
    }
    heap->arr[index] = newVal;
    heapifyUp(heap, index);
}

// Delete key
void deleteKey(MinHeap *heap, int index) {
    decreaseKey(heap, index, INT_MIN);
    extractMin(heap);
}

// 🆕 Change priority of a key
void changePriority(MinHeap *heap, int index, int newVal) {
    if (index < 0 || index >= heap->size) {
        printf("Invalid index.\n");
        return;
    }

    int oldVal = heap->arr[index];
    heap->arr[index] = newVal;

    if (newVal < oldVal)
        heapifyUp(heap, index);
    else if (newVal > oldVal)
        heapifyDown(heap, index);
}

// Display heap
void displayHeap(MinHeap *heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

// Main function
int main() {
    MinHeap heap;
    initMinHeap(&heap);

    insert(&heap, 10);
    insert(&heap, 5);
    insert(&heap, 30);
    insert(&heap, 2);
    insert(&heap, 8);

    displayHeap(&heap);

    printf("Change priority of index 2 to 1\n");
    changePriority(&heap, 2, 1);
    displayHeap(&heap);

    printf("Change priority of index 0 to 20\n");
    changePriority(&heap, 0, 20);
    displayHeap(&heap);

    return 0;
}
