#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

// Structure to represent a node in adjacency list
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Array of pointers to Node (Adjacency list)
Node* adjList[MAX_NODES];

int numNodes;

// Add edge to the undirected graph
void addEdge(int u, int v, int w) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = u;
    newNode->weight = w;
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

// Function to find the vertex with minimum key value not in MST
int minKey(int key[], int inMST[]) {
    int min = INT_MAX, minIndex = -1;

    for (int v = 0; v < numNodes; v++) {
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Prim's Algorithm
void primMST() {
    int parent[MAX_NODES];   // Store MST
    int key[MAX_NODES];      // Min weight to connect to MST
    int inMST[MAX_NODES];    // Included in MST?

    for (int i = 0; i < numNodes; i++) {
        key[i] = INT_MAX;
        inMST[i] = 0;
        parent[i] = -1;
    }

    key[0] = 0; // Start from node 0

    for (int count = 0; count < numNodes - 1; count++) {
        int u = minKey(key, inMST);
        inMST[u] = 1;

        Node* temp = adjList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int w = temp->weight;

            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    printf("\nEdges in MST:\n");
    int totalCost = 0;
    for (int i = 1; i < numNodes; i++) {
        printf("%d - %d (weight: %d)\n", parent[i], i, key[i]);
        totalCost += key[i];
    }
    printf("Total cost of MST: %d\n", totalCost);
}

int main() {
    printf("Enter number of nodes: ");
    scanf("%d", &numNodes);

    for (int i = 0; i < numNodes; i++)
        adjList[i] = NULL;

    int edges;
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    primMST();
    return 0;
}
