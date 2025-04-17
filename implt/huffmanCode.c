#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
// Structure for a Huffman tree node
typedef struct HuffmanNode {
    char data;                       // Character stored in the node
    int freq;                        // Frequency of the character
    struct HuffmanNode* left;        // Pointer to the left child
    struct HuffmanNode* right;       // Pointer to the right child
} HuffmanNode;

// Min-Heap structure for Huffman tree nodes
typedef struct MinHeap {
    int size;                        // Current size of the heap
    int capacity;                    // Maximum capacity of the heap
    HuffmanNode** array;             // Array of pointers to heap nodes
} MinHeap;

// Function to create a new Huffman tree node
HuffmanNode* createNode(char data, int freq) {
    HuffmanNode* newNode = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    newNode->data = data;
    newNode->freq = freq;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create a Min-Heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HuffmanNode**)malloc(minHeap->capacity * sizeof(HuffmanNode*));
    return minHeap;
}

// Function to swap two nodes in the Min-Heap
void swapNodes(HuffmanNode** a, HuffmanNode** b) {
    HuffmanNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the Min-Heap
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
        smallest = left;
    }
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
        smallest = right;
    }
    if (smallest != idx) {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Function to build a Min-Heap
void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--) {
        minHeapify(minHeap, i);
    }
}

// Function to insert a node into the Min-Heap
void insertMinHeap(MinHeap* minHeap, HuffmanNode* node) {
    minHeap->size++;
    int i = minHeap->size - 1;

    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// Function to extract the minimum node from the Min-Heap
HuffmanNode* extractMin(MinHeap* minHeap) {
    HuffmanNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

// Function to create a Huffman tree
HuffmanNode* buildHuffmanTree(char data[], int freq[], int size) {
    MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; i++) {
        minHeap->array[i] = createNode(data[i], freq[i]);
    }
    minHeap->size = size;
    buildMinHeap(minHeap);

    while (minHeap->size > 1) {
        HuffmanNode* left = extractMin(minHeap);
        HuffmanNode* right = extractMin(minHeap);

        HuffmanNode* newNode = createNode('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        insertMinHeap(minHeap, newNode);
    }
    return extractMin(minHeap);
}

// Function to print Huffman codes
void printCodes(HuffmanNode* root, char code[], int top) {
    if (root->left) {
        code[top] = '0';
        printCodes(root->left, code, top + 1);
    }
    if (root->right) {
        code[top] = '1';
        printCodes(root->right, code, top + 1);
    }
    if (root->left == NULL && root->right == NULL) {
        code[top] = '\0';
        printf("%c: %s\n", root->data, code);
    }
}

// Function to decode a Huffman-encoded string
void decode(HuffmanNode* root, char* encodedData) {
    HuffmanNode* current = root;
    printf("Decoded string: ");
    for (int i = 0; encodedData[i] != '\0'; i++) {
        if (encodedData[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == NULL && current->right == NULL) {
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}

// Main function
int main() {
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(data) / sizeof(data[0]);

    // Build Huffman Tree
    HuffmanNode* root = buildHuffmanTree(data, freq, size);

    // Print Huffman Codes
    char code[MAX];
    printf("Huffman Codes:\n");
    printCodes(root, code, 0);

    // Example encoded data
    char encodedData[] = "11001100101011111100"; // Replace with actual Huffman-encoded string
    decode(root, encodedData);

    return 0;
}
