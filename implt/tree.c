#include <stdio.h>
#include <stdlib.h>

// Define structure for a tree node
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Create a new node
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into BST
Node* insert(Node* root, int key) {
    if (root == NULL)
        return createNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

// Search a key
Node* search(Node* root, int key) {
    if (!root || root->key == key)
        return root;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}

// Find min value node
Node* minValueNode(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

// Find max value node
Node* maxValueNode(Node* node) {
    while (node && node->right)
        node = node->right;
    return node;
}

// Delete node
Node* deleteNode(Node* root, int key) {
    if (!root)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // One or no child
        if (!root->left) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Two children
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

// Inorder traversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(Node* root) {
    if (root) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal
void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

// Level order traversal (using queue)
typedef struct QueueNode {
    Node* treeNode;
    struct QueueNode* next;
} QueueNode;

QueueNode* createQueueNode(Node* treeNode) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    return newNode;
}

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

void enqueue(Queue* q, Node* treeNode) {
    QueueNode* newNode = createQueueNode(treeNode);
    if (!q->rear) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

Node* dequeue(Queue* q) {
    if (!q->front)
        return NULL;
    QueueNode* temp = q->front;
    Node* treeNode = temp->treeNode;
    q->front = q->front->next;
    if (!q->front)
        q->rear = NULL;
    free(temp);
    return treeNode;
}

int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

void levelOrder(Node* root) {
    if (!root)
        return;

    Queue q = {NULL, NULL};
    enqueue(&q, root);

    while (!isQueueEmpty(&q)) {
        Node* curr = dequeue(&q);
        printf("%d ", curr->key);
        if (curr->left)
            enqueue(&q, curr->left);
        if (curr->right)
            enqueue(&q, curr->right);
    }
}

// Get height of tree
int height(Node* root) {
    if (!root)
        return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

// Count total nodes
int countNodes(Node* root) {
    if (!root)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Count leaf nodes
int countLeaves(Node* root) {
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// Count internal nodes
int countInternalNodes(Node* root) {
    if (!root || (!root->left && !root->right))
        return 0;
    return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
}

// Main driver
int main() {
    Node* root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    printf("Level Order: ");
    levelOrder(root);
    printf("\n");

    printf("Height: %d\n", height(root));
    printf("Total Nodes: %d\n", countNodes(root));
    printf("Leaf Nodes: %d\n", countLeaves(root));
    printf("Internal Nodes: %d\n", countInternalNodes(root));

    printf("Deleting 70...\n");
    root = deleteNode(root, 70);
    printf("Inorder after deletion: ");
    inorder(root);
    printf("\n");

    int key = 40;
    Node* found = search(root, key);
    if (found)
        printf("Key %d found in BST.\n", key);
    else
        printf("Key %d not found in BST.\n", key);

    return 0;
}
