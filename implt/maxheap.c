#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct MaxHeap {
    int size;
    int arr[MAX_SIZE];
} MaxHeap;

// Function prototypes
void initMaxHeap(MaxHeap *heap);
void insert(MaxHeap *heap, int key);
void heapifyUp(MaxHeap *heap, int index);
void heapifyDown(MaxHeap *heap, int index);
int extractMax(MaxHeap *heap);
int getMax(MaxHeap *heap);
void increaseKey(MaxHeap *heap, int index, int newVal);
void deleteKey(MaxHeap *heap, int index);
void changePriority(MaxHeap *heap, int index, int newVal);
void displayHeap(MaxHeap *heap);

// Initialize heap
void initMaxHeap(MaxHeap *heap) {
    heap->size = 0;
}

// Get parent and children
int parent(int i) { return (i - 1) / 2; }
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

// Insert key
void insert(MaxHeap *heap, int key) {
    if (heap->size == MAX_SIZE) {
        printf("Heap is full!\n");
        return;
    }

    heap->arr[heap->size] = key;
    heapifyUp(heap, heap->size);
    heap->size++;
}

// Heapify up (restore max-heap property after insertion or key increase)
void heapifyUp(MaxHeap *heap, int index) {
    while (index != 0 && heap->arr[parent(index)] < heap->arr[index]) {
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[parent(index)];
        heap->arr[parent(index)] = temp;
        index = parent(index);
    }
}

// Heapify down (restore max-heap property after deletion or key decrease)
void heapifyDown(MaxHeap *heap, int index) {
    int largest = index;
    int l = left(index);
    int r = right(index);

    if (l < heap->size && heap->arr[l] > heap->arr[largest])
        largest = l;
    if (r < heap->size && heap->arr[r] > heap->arr[largest])
        largest = r;

    if (largest != index) {
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[largest];
        heap->arr[largest] = temp;

        heapifyDown(heap, largest);
    }
}

// Extract max
int extractMax(MaxHeap *heap) {
    if (heap->size <= 0)
        return INT_MIN;
    if (heap->size == 1)
        return heap->arr[--heap->size];

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->size];
    heapifyDown(heap, 0);

    return root;
}

// Get max
int getMax(MaxHeap *heap) {
    if (heap->size <= 0)
        return INT_MIN;
    return heap->arr[0];
}

// Increase key (i.e., increase value at index)
void increaseKey(MaxHeap *heap, int index, int newVal) {
    if (newVal < heap->arr[index]) {
        printf("New value is smaller than current value. Use changePriority instead.\n");
        return;
    }
    heap->arr[index] = newVal;
    heapifyUp(heap, index);
}

// Delete key at index
void deleteKey(MaxHeap *heap, int index) {
    increaseKey(heap, index, INT_MAX);
    extractMax(heap);
}

// 🆕 Change priority of a key
void changePriority(MaxHeap *heap, int index, int newVal) {
    if (index < 0 || index >= heap->size) {
        printf("Invalid index.\n");
        return;
    }

    int oldVal = heap->arr[index];
    heap->arr[index] = newVal;

    if (newVal > oldVal)
        heapifyUp(heap, index);
    else if (newVal < oldVal)
        heapifyDown(heap, index);
}

// Display heap
void displayHeap(MaxHeap *heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

// Main function
int main() {
    MaxHeap heap;
    initMaxHeap(&heap);

    insert(&heap, 10);
    insert(&heap, 40);
    insert(&heap, 20);
    insert(&heap, 5);
    insert(&heap, 25);

    displayHeap(&heap);

    printf("Change priority of index 3 to 50\n");
    changePriority(&heap, 3, 50);
    displayHeap(&heap);

    printf("Change priority of index 0 to 15\n");
    changePriority(&heap, 0, 15);
    displayHeap(&heap);

    return 0;
}
