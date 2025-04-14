#include <stdio.h>
#include <stdlib.h>

#define MAX_USERS 100

// Structure for adjacency list representation
typedef struct Node {
    int user_id;
    struct Node* next;
} Node;

// Graph representation
typedef struct Graph {
    int num_users;
    Node* adj_list[MAX_USERS];
} Graph;

// Function to create a new node
Node* create_node(int user_id) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->user_id = user_id;
    new_node->next = NULL;
    return new_node;
}

// Function to initialize the graph
Graph* create_graph(int num_users) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->num_users = num_users;
    
    for (int i = 0; i < num_users; i++) {
        graph->adj_list[i] = NULL;
    }
    return graph;
}

// Function to add edge (friendship) between users
void add_edge(Graph* graph, int u, int v) {
    Node* new_node1 = create_node(v);
    new_node1->next = graph->adj_list[u];
    graph->adj_list[u] = new_node1;

    Node* new_node2 = create_node(u);
    new_node2->next = graph->adj_list[v];
    graph->adj_list[v] = new_node2;
}

// Function to display the adjacency list
void display_graph(Graph* graph) {
    printf("\nGraph (Adjacency List):\n");
    for (int i = 0; i < graph->num_users; i++) {
        printf("%d:", i);
        Node* temp = graph->adj_list[i];
        while (temp) {
            printf(" %d", temp->user_id);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Function to find direct friends and friend suggestions using BFS
void find_friend_suggestions(Graph* graph, int user_id) {
    int visited[MAX_USERS] = {0};
    int queue[MAX_USERS], front = 0, rear = 0;
    int level[MAX_USERS] = {0};

    // BFS initialization
    visited[user_id] = 1;
    queue[rear++] = user_id;

    printf("\nDirect friends of user %d:", user_id);
    while (front < rear) {
        int current_user = queue[front++];
        Node* temp = graph->adj_list[current_user];

        while (temp) {
            int friend_id = temp->user_id;
            if (!visited[friend_id]) {
                visited[friend_id] = 1;
                level[friend_id] = level[current_user] + 1;
                queue[rear++] = friend_id;
            }
            temp = temp->next;
        }
    }

    // Display direct friends (distance = 1)
    for (int i = 0; i < graph->num_users; i++) {
        if (level[i] == 1) {
            printf(" %d", i);
        }
    }

    // Display friend suggestions (distance = 2 and not direct friends)
    printf("\nFriend suggestions for user %d:", user_id);
    for (int i = 0; i < graph->num_users; i++) {
        if (level[i] == 2) {
            printf(" %d", i);
        }
    }
    
    printf("\n\nExit:\n------\nProgram terminated successfully.\n");
}

// Main function
int main() {
    int num_users, num_friendships;
    printf("Enter number of users: ");
    scanf("%d", &num_users);

    Graph* graph = create_graph(num_users);

    printf("Enter number of friendships: ");
    scanf("%d", &num_friendships);

    printf("Enter friendships (pairs of user IDs, 0-based):\n");
    for (int i = 0; i < num_friendships; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(graph, u, v);
    }

    int user_id;
    printf("Enter user ID to find friend suggestions: ");
    scanf("%d", &user_id);

    // Display graph structure
    display_graph(graph);

    // Find direct friends and friend suggestions
    find_friend_suggestions(graph, user_id);

    return 0;
}
