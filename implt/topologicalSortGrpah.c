#include <stdio.h>
#include <stdlib.h>

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
    int V; // Number of vertices
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    
    // Create an array of adjacency lists
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    
    // Initialize each adjacency list as empty
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    
    return graph;
}

// Function to add an edge to a directed graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// A recursive function used by topologicalSort
void topologicalSortUtil(struct Graph* graph, int v, int visited[], int* stack, int* stackIndex) {
    // Mark the current node as visited
    visited[v] = 1;
    
    // Recur for all vertices adjacent to this vertex
    struct AdjListNode* node = graph->array[v].head;
    while (node != NULL) {
        if (!visited[node->dest])
            topologicalSortUtil(graph, node->dest, visited, stack, stackIndex);
        node = node->next;
    }
    
    // Push current vertex to stack which stores result
    stack[(*stackIndex)++] = v;
}

// The function to do Topological Sort
void topologicalSort(struct Graph* graph) {
    int* stack = (int*)malloc(graph->V * sizeof(int));
    int stackIndex = 0;
    
    // Mark all vertices as not visited
    int* visited = (int*)malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; i++)
        visited[i] = 0;
    
    // Call the recursive helper function to store Topological Sort
    for (int i = 0; i < graph->V; i++)
        if (visited[i] == 0)
            topologicalSortUtil(graph, i, visited, stack, &stackIndex);
    
    // Print contents of stack in reverse order (which is the topological order)
    printf("Topological Sort of the graph:\n");
    for (int i = stackIndex - 1; i >= 0; i--)
        printf("%d ", stack[i]);
    printf("\n");
    
    free(stack);
    free(visited);
}

// Driver program to test above functions
int main() {
    // Create a graph
    int V = 6;
    struct Graph* graph = createGraph(V);
    
    // Add edges
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);
    
    // Perform topological sort
    topologicalSort(graph);
    
    // Free memory
    for (int v = 0; v < graph->V; ++v) {
        struct AdjListNode* node = graph->array[v].head;
        while (node != NULL) {
            struct AdjListNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
    
    return 0;
}