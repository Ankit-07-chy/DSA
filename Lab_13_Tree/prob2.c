#include<stdio.h>
#include<stdlib.h>
#define max 100

typedef struct node{
    int id;
    struct node* next;
}Node;

typedef struct graph{
    int n;
    struct node* list[max];
}Graph;

Graph* create_graph(int n){
    Graph* temp = (Graph*)malloc(sizeof(Graph));
    temp->n = n;
    for(int i=0; i<temp->n; i++){
        temp->list[i] = NULL;
    }
    return temp;
}

Node* create_node(int id){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp ->id = id;
    temp->next = NULL;
    return temp;
}

void add_edge(Graph* graph, int u, int v){
    Node* newnode1 = create_node(u);
    newnode1->next = graph->list[v];
    graph->list[v]= newnode1;

    Node* newnode2 = create_node(v);
    newnode2->next = graph->list[u];
    graph->list[u]= newnode2;
}

void graph_traversal(Graph* graph){
    for(int i = 0; i<graph->n; i++){
        printf("%d : ",i);
        Node* temp = graph->list[i];
        while(temp!=NULL){
            printf("%d ",temp->id);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main(){
    int n;//n for nodes
    int m; //m for edges
    printf("enter n and m : ");
    scanf("%d%d",&n,&m);
    Graph* graph = create_graph(n);
    int u, v;
    printf("enter u and v: \n");
    for(int i=0; i<m; i++){
        scanf("%d%d",&u,&v);
        add_edge(graph,u,v);
    }
    graph_traversal(graph);//graph tarverse complenter
    if(n>m){
        printf("not cycle\n");
    }else{
        printf("cylce\n");
    }
}