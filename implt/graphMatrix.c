#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MAX

#define MAX 100 // Maximum number of vertices

// Structure to represent a graph using an adjacency matrix
typedef struct Graph {
    int numVertices;
    int adjMatrix[MAX][MAX];
    int visited[MAX]; // Array to keep track of visited nodes
} Graph;

// Function to initialize the graph
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    // Initialize adjacency matrix and visited array
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph->adjMatrix[i][j] = 0; // No edges initially
        }
        graph->visited[i] = 0; // All vertices are unvisited
    }
    return graph;
}

// Function to add an edge to the graph (undirected graph)
void addEdge(Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

// Function to print the adjacency matrix
void printGraph(Graph* graph) {
    printf("\nGraph (Adjacency Matrix):\n");
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Depth-First Search (DFS)
void DFS(Graph* graph, int vertex) {
    printf("%d ", vertex);
    graph->visited[vertex] = 1; // Mark as visited

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && !graph->visited[i]) {
            DFS(graph, i);
        }
    }
}

// Breadth-First Search (BFS)
void BFS(Graph* graph, int startVertex) {
    int queue[MAX], front = 0, rear = 0;

    // Mark the starting vertex as visited and enqueue it
    graph->visited[startVertex] = 1;
    queue[rear++] = startVertex;

    printf("\nBFS Traversal: ");
    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Explore all adjacent vertices
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !graph->visited[i]) {
                graph->visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

// Function to find the minimum distance between two nodes using BFS
int findMinDistance(Graph* graph, int start, int end) {
    if (start == end) return 0; // If the start and end are the same

    int distance[MAX];
    for (int i = 0; i < graph->numVertices; i++) {
        distance[i] = INT_MAX; // Initialize distances as infinity
    }

    int queue[MAX], front = 0, rear = 0;

    // Initialize BFS
    graph->visited[start] = 1;
    distance[start] = 0;
    queue[rear++] = start;

    while (front < rear) {
        int currentVertex = queue[front++];
        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !graph->visited[i]) {
                graph->visited[i] = 1;
                distance[i] = distance[currentVertex] + 1;
                queue[rear++] = i;

                // If destination node is found
                if (i == end) {
                    return distance[end];
                }
            }
        }
    }

    return -1; // If no path exists
}

// Function to reset the visited array
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

// Main function
int main() {
    int numVertices, numEdges;

    // Input number of vertices and edges
    printf("Enter number of vertices: ");
    scanf("%d", &numVertices);
    printf("Enter number of edges: ");
    scanf("%d", &numEdges);

    // Create a graph with the specified number of vertices
    Graph* graph = createGraph(numVertices);

    // Input edges
    printf("Enter edges (pairs of vertices):\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    // Print the graph
    printGraph(graph);

    // Perform DFS
    int startVertex;
    printf("\nEnter the starting vertex for DFS: ");
    scanf("%d", &startVertex);
    printf("\nDFS Traversal: ");
    DFS(graph, startVertex);

    // Reset visited array
    resetVisited(graph);

    // Perform BFS
    printf("\n\nEnter the starting vertex for BFS: ");
    scanf("%d", &startVertex);
    BFS(graph, startVertex);

    // Reset visited array
    resetVisited(graph);

    // Find minimum distance between two nodes
    int start, end;
    printf("\n\nEnter the start node: ");
    scanf("%d", &start);
    printf("Enter the end node: ");
    scanf("%d", &end);
    int minDistance = findMinDistance(graph, start, end);
    if (minDistance != -1) {
        printf("\nMinimum distance between node %d and node %d is: %d\n", start, end, minDistance);
    } else {
        printf("\nNo path exists between node %d and node %d\n", start, end);
    }

    // Free allocated memory
    free(graph);

    printf("\nProgram terminated successfully.\n");
    return 0;
}
