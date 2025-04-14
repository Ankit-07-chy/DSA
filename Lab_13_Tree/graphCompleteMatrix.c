#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Structure to represent a graph using adjacency matrix
typedef struct {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

// Queue structure for BFS implementation
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

// Graph operations
Graph* createGraph(int vertices) {
    if (vertices > MAX_VERTICES) {
        printf("Maximum number of vertices exceeded (%d)\n", MAX_VERTICES);
        return NULL;
    }

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // Initialize all matrix elements to 0
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0;
        }
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    if (src >= graph->numVertices || dest >= graph->numVertices) {
        printf("Invalid vertex index\n");
        return;
    }
    
    // For undirected graph, add both directions
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

void removeEdge(Graph* graph, int src, int dest) {
    if (src >= graph->numVertices || dest >= graph->numVertices) {
        printf("Invalid vertex index\n");
        return;
    }
    
    graph->adjMatrix[src][dest] = 0;
    graph->adjMatrix[dest][src] = 0;
}

bool hasEdge(Graph* graph, int src, int dest) {
    if (src >= graph->numVertices || dest >= graph->numVertices) {
        printf("Invalid vertex index\n");
        return false;
    }
    
    return graph->adjMatrix[src][dest] == 1;
}

void printGraph(Graph* graph) {
    printf("\nAdjacency Matrix Representation:\n");
    printf("   ");
    for (int i = 0; i < graph->numVertices; i++)
        printf("%2d ", i);
    printf("\n");
    
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%2d ", i);
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%2d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Queue operations for BFS
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1) {
        printf("Queue is full\n");
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

// BFS traversal
void BFS(Graph* graph, int startVertex) {
    if (startVertex >= graph->numVertices) {
        printf("Invalid start vertex\n");
        return;
    }

    Queue* q = createQueue();
    bool visited[MAX_VERTICES] = {false};
    
    visited[startVertex] = true;
    enqueue(q, startVertex);
    
    printf("BFS Traversal: ");
    
    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);
        
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(q, i);
            }
        }
    }
    printf("\n");
    free(q);
}

// DFS utility function
void DFSUtil(Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);
    
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }
}

// DFS traversal
void DFS(Graph* graph, int startVertex) {
    if (startVertex >= graph->numVertices) {
        printf("Invalid start vertex\n");
        return;
    }

    bool visited[MAX_VERTICES] = {false};
    printf("DFS Traversal: ");
    DFSUtil(graph, startVertex, visited);
    printf("\n");
}

int main() {
    // Create a graph with 5 vertices
    Graph* graph = createGraph(5);
    
    // Add edges
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    
    // Print the adjacency matrix
    printGraph(graph);
    
    // Test edge operations
    printf("\nEdge between 1 and 3 exists? %s\n", 
           hasEdge(graph, 1, 3) ? "Yes" : "No");
    printf("Removing edge between 1 and 3\n");
    removeEdge(graph, 1, 3);
    printf("Edge between 1 and 3 exists now? %s\n", 
           hasEdge(graph, 1, 3) ? "Yes" : "No");
    
    // Print updated matrix
    printGraph(graph);
    
    // Restore the edge for traversal demonstrations
    addEdge(graph, 1, 3);
    
    // Perform traversals
    BFS(graph, 0); // Start BFS from vertex 0
    DFS(graph, 0); // Start DFS from vertex 0
    
    // Free memory
    free(graph);
    
    return 0;
}