#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a node in adjacency list
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Structure to represent an adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure to represent a graph
struct Graph {
    int numVertices;
    struct AdjList* array;
};

// Structure for queue used in BFS
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    
    // Create an array of adjacency lists
    graph->array = (struct AdjList*)malloc(numVertices * sizeof(struct AdjList));
    
    // Initialize each adjacency list as empty
    for (int i = 0; i < numVertices; ++i)
        graph->array[i].head = NULL;
    
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Queue functions for BFS
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

bool isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// BFS traversal
void BFS(struct Graph* graph, int startVertex) {
    // Create a queue for BFS
    struct Queue* queue = createQueue(graph->numVertices);
    
    // Mark all vertices as not visited
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = false;
    
    // Mark the current node as visited and enqueue it
    visited[startVertex] = true;
    enqueue(queue, startVertex);
    
    printf("BFS Traversal: ");
    
    while (!isEmpty(queue)) {
        // Dequeue a vertex and print it
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);
        
        // Get all adjacent vertices of the dequeued vertex
        struct AdjListNode* temp = graph->array[currentVertex].head;
        while (temp != NULL) {
            int adjVertex = temp->dest;
            
            // If adjacent vertex not visited, mark and enqueue it
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    
    free(queue->array);
    free(queue);
    free(visited);
}

// DFS utility function
void DFSUtil(struct Graph* graph, int vertex, bool visited[]) {
    // Mark the current node as visited and print it
    visited[vertex] = true;
    printf("%d ", vertex);
    
    // Recur for all vertices adjacent to this vertex
    struct AdjListNode* temp = graph->array[vertex].head;
    while (temp != NULL) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex])
            DFSUtil(graph, adjVertex, visited);
        temp = temp->next;
    }
}

// DFS traversal
void DFS(struct Graph* graph, int startVertex) {
    // Mark all vertices as not visited
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = false;
    
    printf("DFS Traversal: ");
    DFSUtil(graph, startVertex, visited);
    printf("\n");
    
    free(visited);
}

// Function to print the adjacency list representation of graph
void printGraph(struct Graph* graph) {
    printf("\nAdjacency List Representation:\n");
    for (int v = 0; v < graph->numVertices; ++v) {
        struct AdjListNode* temp = graph->array[v].head;
        printf("\nVertex %d: ", v);
        while (temp) {
            printf("%d -> ", temp->dest);
            temp = temp->next;
        }
        printf("NULL");
    }
    printf("\n");
}

int main() {
    // Create a graph with 5 vertices
    struct Graph* graph = createGraph(5);
    
    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    
    // Print the adjacency list representation
    printGraph(graph);
    
    // Perform traversals
    BFS(graph, 0); // Start BFS from vertex 0
    DFS(graph, 0);  // Start DFS from vertex 0
    
    // Free memory
    for (int v = 0; v < graph->numVertices; ++v) {
        struct AdjListNode* temp = graph->array[v].head;
        while (temp) {
            struct AdjListNode* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->array);
    free(graph);
    
    return 0;
}