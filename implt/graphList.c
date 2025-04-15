#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MAX

// Structure to represent a node in the adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure to represent a graph
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited; // Array to keep track of visited nodes
} Graph;

// Function to create a node
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    // Allocate memory for adjacency lists and visited array
    graph->adjLists = (Node**)malloc(numVertices * sizeof(Node*));
    graph->visited = (int*)malloc(numVertices * sizeof(int));

    for (int i = 0; i < numVertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0; // Initialize all nodes as unvisited
    }
    return graph;
}

// Function to add an edge to the graph (undirected graph)
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to perform BFS to find the minimum distance between two nodes
int findMinDistance(Graph* graph, int start, int end) {
    if (start == end) return 0; // If both nodes are the same, distance is 0

    int* distance = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; i++) {
        distance[i] = INT_MAX; // Initialize distances as infinity
    }

    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;

    graph->visited[start] = 1; // Mark the start node as visited
    distance[start] = 0;       // Distance to itself is 0
    queue[rear++] = start;

    while (front < rear) {
        int currentVertex = queue[front++];
        Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                distance[adjVertex] = distance[currentVertex] + 1;
                queue[rear++] = adjVertex;

                // If we reach the destination node, return the distance
                if (adjVertex == end) {
                    free(distance);
                    free(queue);
                    return distance[adjVertex];
                }
            }
            temp = temp->next;
        }
    }

    // If we exhaust the BFS and don't find the destination node
    free(distance);
    free(queue);
    return -1; // Indicates no path exists
}

// Function to reset the visited array
void resetVisited(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
}

// Function to display the adjacency list of the graph
void printGraph(Graph* graph) {
    printf("\nGraph (Adjacency List):\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d:", i);
        Node* temp = graph->adjLists[i];
        while (temp) {
            printf(" %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
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

    // Input nodes to find the minimum distance
    int start, end;
    printf("\nEnter the start node: ");
    scanf("%d", &start);
    printf("Enter the end node: ");
    scanf("%d", &end);

    // Find the minimum distance
    resetVisited(graph); // Reset visited before BFS
    int minDistance = findMinDistance(graph, start, end);
    if (minDistance != -1) {
        printf("\nMinimum distance between node %d and node %d is: %d\n", start, end, minDistance);
    } else {
        printf("\nNo path exists between node %d and node %d\n", start, end);
    }

    // Free allocated memory
    for (int i = 0; i < numVertices; i++) {
        Node* temp = graph->adjLists[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);

    printf("\nProgram terminated successfully.\n");
    return 0;
}
