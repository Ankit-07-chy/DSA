#include <stdio.h>
#include <stdlib.h>
#define max 100

typedef struct node{
    int id;
    struct node* next;
}Node;

typedef struct graph{
    int n;
    struct node* List[max];
}Graph;

Node* create_node(int id){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->id = id;
    temp->next = NULL;
    return temp;
}

Graph* create_graph(int n){
    Graph* temp = (Graph*)malloc(sizeof(Graph));
    temp->n = n;
    for(int i=0; i<n; i++){
        temp->List[i] = NULL;
    }
    return temp;
}

void add_edge(Graph* graph, int u, int v){
    Node* new_node1 = create_node(v);
    new_node1->next = graph->List[u];
    graph->List[u] = new_node1;

    Node* new_node2 = create_node(u);
    new_node2->next = graph->List[v];
    graph->List[v] = new_node2;
}

void traversal_graph(Graph* graph){
    for(int i=0; i<graph->n; i++){
        printf("%d : ",i);
        Node* temp = graph->List[i];
        while(temp!=NULL){
            printf("%d ",temp->id);
            temp=temp->next;
        }
        printf("\n");
    }
}

int main(){
    int n, m;
    printf("enter n and m: \n");//n for nodes and m for edges
    scanf("%d%d",&n,&m);
    Graph* graph = create_graph(n);//here list in column form is created

    int u, v;
    printf("enter u and v:\n");
    for(int i=0; i<m;  i++){
        scanf("%d%d",&u,&v);
        add_edge(graph,u,v);
    }
    traversal_graph(graph);//traversal for graph
}

//here add few more things like BFS and DFS