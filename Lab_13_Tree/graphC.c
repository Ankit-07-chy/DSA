//graph implementation using list
#include<stdio.h>
#include<stdlib.h>
#define max 100

typedef struct node{
    int id;
    struct node* next;
}Node;

typedef struct graph{
    int n;
    struct node *list[max];
}Graph;

Graph* create_graph(int n){
    Graph* temp = (Graph*)malloc(sizeof(Graph));
    temp->n = n;
    for(int i=0; i<temp->n; i++){
        temp->list[i]=NULL;
    }
    return temp;
}

Node* create_node(int id){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->id = id;
    temp->next = NULL;
    return temp;
}

void add_edge(Graph* graph, int u, int v){
    Node* newNode1 = create_node(u);
    newNode1->id=graph->list[v];
    graph->list[v]=newNode1;

    Node* newNode2 = create_node(v);
    newNode2->id = graph->list[u];
    graph->list[u] = newNode2;
}

void traverse(Graph* graph){
    for(int i=0; i<graph->n; i++){
        printf("%d : ",graph->list[i]);
        Node* temp = graph->list[i];
        while(temp!=NULL){
            printf("%d ",temp->id);
            temp=temp->next;
        }
        printf("\n");
    }
}



int main(){
    int n;//nodes
    int m; //edges
    
    printf("enter n and m: ");
    scanf("%d%d",&n,&m);
    Graph* graph = create_graph(n);
    int u, v;
    for(int i=0; i<m; i++){
        scanf("%d%d",&u,&v);
        add_edge(graph,u,v);
    }
    printf("Traversal: \n");
    traverse(graph);
}
