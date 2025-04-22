// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <limits.h>

// #define MAX_TREE_HT 100

// // A Huffman tree node
// struct MinHeapNode {
//     char data;
//     unsigned freq;
//     struct MinHeapNode *left, *right;
// };

// // A Min Heap: Collection of min-heap (or Huffman tree) nodes
// struct MinHeap {
//     unsigned size;
//     unsigned capacity;
//     struct MinHeapNode** array;
// };

// // Function to create a new min heap node
// struct MinHeapNode* newNode(char data, unsigned freq) {
//     struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
//     temp->left = temp->right = NULL;
//     temp->data = data;
//     temp->freq = freq;
//     return temp;
// }

// // Function to create a min heap of given capacity
// struct MinHeap* createMinHeap(unsigned capacity) {
//     struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
//     minHeap->size = 0;
//     minHeap->capacity = capacity;
//     minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
//     return minHeap;
// }

// // Function to swap two min heap nodes
// void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
//     struct MinHeapNode* t = *a;
//     *a = *b;
//     *b = t;
// }

// // The standard minHeapify function
// void minHeapify(struct MinHeap* minHeap, int idx) {
//     int smallest = idx;
//     int left = 2 * idx + 1;
//     int right = 2 * idx + 2;

//     if (left < minHeap->size && 
//         minHeap->array[left]->freq < minHeap->array[smallest]->freq)
//         smallest = left;

//     if (right < minHeap->size && 
//         minHeap->array[right]->freq < minHeap->array[smallest]->freq)
//         smallest = right;

//     if (smallest != idx) {
//         swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
//         minHeapify(minHeap, smallest);
//     }
// }

// // Function to check if size of heap is 1 or not
// int isSizeOne(struct MinHeap* minHeap) {
//     return (minHeap->size == 1);
// }

// // Function to extract minimum value node from heap
// struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
//     struct MinHeapNode* temp = minHeap->array[0];
//     minHeap->array[0] = minHeap->array[minHeap->size - 1];
//     --minHeap->size;
//     minHeapify(minHeap, 0);
//     return temp;
// }

// // Function to insert a new node to Min Heap
// void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
//     ++minHeap->size;
//     int i = minHeap->size - 1;
//     while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
//         minHeap->array[i] = minHeap->array[(i - 1) / 2];
//         i = (i - 1) / 2;
//     }
//     minHeap->array[i] = minHeapNode;
// }

// // Function to build min heap
// void buildMinHeap(struct MinHeap* minHeap) {
//     int n = minHeap->size - 1;
//     int i;
//     for (i = (n - 1) / 2; i >= 0; --i)
//         minHeapify(minHeap, i);
// }

// // Function to print an array of size n
// void printArr(int arr[], int n) {
//     int i;
//     for (i = 0; i < n; ++i)
//         printf("%d", arr[i]);
//     printf("\n");
// }

// // Utility function to check if this node is leaf
// int isLeaf(struct MinHeapNode* root) {
//     return !(root->left) && !(root->right);
// }

// // Creates a min heap of capacity equal to size and inserts all characters of data[] in min heap.
// struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
//     struct MinHeap* minHeap = createMinHeap(size);
//     for (int i = 0; i < size; ++i)
//         minHeap->array[i] = newNode(data[i], freq[i]);
//     minHeap->size = size;
//     buildMinHeap(minHeap);
//     return minHeap;
// }

// // The main function that builds Huffman tree
// struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
//     struct MinHeapNode *left, *right, *top;
    
//     // Step 1: Create a min heap of capacity equal to size.
//     struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    
//     // Iterate while size of heap doesn't become 1
//     while (!isSizeOne(minHeap)) {
//         // Step 2: Extract the two minimum freq items from min heap
//         left = extractMin(minHeap);
//         right = extractMin(minHeap);
        
//         // Step 3: Create a new internal node with frequency equal to the sum of the two nodes frequencies.
//         top = newNode('$', left->freq + right->freq);
//         top->left = left;
//         top->right = right;
//         insertMinHeap(minHeap, top);
//     }
    
//     // Step 4: The remaining node is the root node and the tree is complete.
//     return extractMin(minHeap);
// }

// // Prints huffman codes from the root of Huffman Tree.
// void printCodes(struct MinHeapNode* root, int arr[], int top) {
//     // Assign 0 to left edge and recur
//     if (root->left) {
//         arr[top] = 0;
//         printCodes(root->left, arr, top + 1);
//     }
    
//     // Assign 1 to right edge and recur
//     if (root->right) {
//         arr[top] = 1;
//         printCodes(root->right, arr, top + 1);
//     }
    
//     // If this is a leaf node, then it contains one of the input characters, print the character and its code
//     if (isLeaf(root)) {
//         printf("%c: ", root->data);
//         printArr(arr, top);
//     }
// }

// // The main function that builds a Huffman Tree and print codes by traversing the built Huffman Tree
// void HuffmanCodes(char data[], int freq[], int size) {
//     // Construct Huffman Tree
//     struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    
//     // Print Huffman codes using the Huffman tree built above
//     int arr[MAX_TREE_HT], top = 0;
//     printCodes(root, arr, top);
// }

// // Function to calculate frequency of each character in the string
// void calculateFrequencies(char* str, int* freq, int size) {
//     for (int i = 0; i < size; i++) {
//         freq[(unsigned char)str[i]]++;
//     }
// }

// // Function to get unique characters and their frequencies
// void getUniqueCharsAndFreqs(char* str, char* data, int* freq, int* uniqueCount) {
//     int tempFreq[256] = {0};
//     int len = strlen(str);
    
//     // Calculate frequencies
//     for (int i = 0; i < len; i++) {
//         tempFreq[(unsigned char)str[i]]++;
//     }
    
//     // Collect unique characters and their frequencies
//     *uniqueCount = 0;
//     for (int i = 0; i < 256; i++) {
//         if (tempFreq[i] > 0) {
//             data[*uniqueCount] = (char)i;
//             freq[*uniqueCount] = tempFreq[i];
//             (*uniqueCount)++;
//         }
//     }
// }

// // Driver program to test above functions
// int main() {
//     char str[1000];
//     printf("Enter a string to encode: ");
//     fgets(str, sizeof(str), stdin);
//     str[strcspn(str, "\n")] = '\0'; // Remove newline character
    
//     char data[256];
//     int freq[256] = {0};
//     int uniqueCount = 0;
    
//     getUniqueCharsAndFreqs(str, data, freq, &uniqueCount);
    
//     printf("Huffman Codes:\n");
//     HuffmanCodes(data, freq, uniqueCount);
    
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_TREE_HT 100

// Huffman tree node
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// Min Heap structure
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// Huffman code structure
struct HuffmanCode {
    char character;
    char code[MAX_TREE_HT];
};

// Function prototypes
struct MinHeapNode* newNode(char data, unsigned freq);
struct MinHeap* createMinHeap(unsigned capacity);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
int isSizeOne(struct MinHeap* minHeap);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);
void storeCodes(struct MinHeapNode* root, int arr[], int top, struct HuffmanCode huffmanCodes[], int* codeIndex);
void HuffmanCodes(char data[], int freq[], int size, struct HuffmanCode huffmanCodes[], int* codeIndex);
void calculateFrequencies(char* str, int* freq, int size);
void getUniqueCharsAndFreqs(char* str, char* data, int* freq, int* uniqueCount);
char* encodeString(char* str, struct HuffmanCode huffmanCodes[], int codeCount);
void decodeString(struct MinHeapNode* root, char* encodedString);

// Create a new min heap node
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Create a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Standard minHeapify function
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && 
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && 
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Check if size of heap is 1
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Extract minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Insert a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Build min heap
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Create and build min heap
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Build Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    
    return extractMin(minHeap);
}

// Check if node is leaf
int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

// Store Huffman codes in an array
void storeCodes(struct MinHeapNode* root, int arr[], int top, struct HuffmanCode huffmanCodes[], int* codeIndex) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, huffmanCodes, codeIndex);
    }
    
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, huffmanCodes, codeIndex);
    }
    
    if (isLeaf(root)) {
        huffmanCodes[*codeIndex].character = root->data;
        for (int i = 0; i < top; i++) {
            huffmanCodes[*codeIndex].code[i] = arr[i] + '0';
        }
        huffmanCodes[*codeIndex].code[top] = '\0';
        (*codeIndex)++;
    }
}

// Build Huffman codes
void HuffmanCodes(char data[], int freq[], int size, struct HuffmanCode huffmanCodes[], int* codeIndex) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    storeCodes(root, arr, top, huffmanCodes, codeIndex);
}

// Calculate character frequencies
void calculateFrequencies(char* str, int* freq, int size) {
    for (int i = 0; i < size; i++) {
        freq[(unsigned char)str[i]]++;
    }
}

// Get unique characters and their frequencies
void getUniqueCharsAndFreqs(char* str, char* data, int* freq, int* uniqueCount) {
    int tempFreq[256] = {0};
    int len = strlen(str);
    
    for (int i = 0; i < len; i++) {
        tempFreq[(unsigned char)str[i]]++;
    }
    
    *uniqueCount = 0;
    for (int i = 0; i < 256; i++) {
        if (tempFreq[i] > 0) {
            data[*uniqueCount] = (char)i;
            freq[*uniqueCount] = tempFreq[i];
            (*uniqueCount)++;
        }
    }
}

// Encode the input string using Huffman codes
char* encodeString(char* str, struct HuffmanCode huffmanCodes[], int codeCount) {
    int len = strlen(str);
    // Calculate maximum possible size (all characters use max code length)
    int maxEncodedSize = len * MAX_TREE_HT;
    char* encodedString = (char*)malloc(maxEncodedSize + 1);
    encodedString[0] = '\0';
    
    for (int i = 0; i < len; i++) {
        char c = str[i];
        for (int j = 0; j < codeCount; j++) {
            if (huffmanCodes[j].character == c) {
                strcat(encodedString, huffmanCodes[j].code);
                break;
            }
        }
    }
    
    return encodedString;
}

// Decode the encoded string using Huffman tree
void decodeString(struct MinHeapNode* root, char* encodedString) {
    struct MinHeapNode* current = root;
    printf("Decoded string: ");
    
    for (int i = 0; encodedString[i] != '\0'; i++) {
        if (encodedString[i] == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        
        if (isLeaf(current)) {
            printf("%c", current->data);
            current = root;
        }
    }
    printf("\n");
}

int main() {
    char str[1000];
    printf("Enter a string to encode: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove newline character
    
    char data[256];
    int freq[256] = {0};
    int uniqueCount = 0;
    
    getUniqueCharsAndFreqs(str, data, freq, &uniqueCount);
    
    struct HuffmanCode huffmanCodes[256];
    int codeIndex = 0;
    
    printf("\nHuffman Codes:\n");
    HuffmanCodes(data, freq, uniqueCount, huffmanCodes, &codeIndex);
    
    for (int i = 0; i < codeIndex; i++) {
        printf("%c: %s\n", huffmanCodes[i].character, huffmanCodes[i].code);
    }
    
    char* encodedString = encodeString(str, huffmanCodes, codeIndex);
    printf("\nEncoded string: %s\n", encodedString);
    
    // Rebuild the Huffman tree for decoding
    struct MinHeapNode* root = buildHuffmanTree(data, freq, uniqueCount);
    decodeString(root, encodedString);
    
    free(encodedString);
    return 0;
}