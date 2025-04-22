#include <stdio.h>
#include <stdlib.h>

// Tree node structure
struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

// Create new node
struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Search for a value in inorder[]
int search(char inorder[], int start, int end, char value) {
    for (int i = start; i <= end; i++)
        if (inorder[i] == value)
            return i;
    return -1;
}

// Static index to track root from postorder[]
int postIndex;

// Recursive function to build the tree
struct Node* buildTree(char inorder[], char postorder[], int inStart, int inEnd) {
    if (inStart > inEnd)
        return NULL;

    // Get current root from postorder
    char current = postorder[postIndex--];
    struct Node* node = newNode(current);

    // If node has no children
    if (inStart == inEnd)
        return node;

    // Find the index of this node in inorder[]
    int inIndex = search(inorder, inStart, inEnd, current);

    // Build right subtree before left (important!)
    node->right = buildTree(inorder, postorder, inIndex + 1, inEnd);
    node->left = buildTree(inorder, postorder, inStart, inIndex - 1);

    return node;
}

// Preorder traversal to verify the tree
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

int main() {
    // Example input
    char inorder[]    = {'D', 'B', 'E', 'A', 'F', 'C'};
    char postorder[]  = {'D', 'E', 'B', 'F', 'C', 'A'};
    int length = sizeof(inorder)/sizeof(inorder[0]);

    postIndex = length - 1;

    struct Node* root = buildTree(inorder, postorder, 0, length - 1);

    printf("Preorder traversal of the constructed tree:\n");
    preorder(root);

    return 0;
}
