#include <stdio.h>
#include <stdlib.h>

// Tree node structure
struct Node {
    char data;
    struct Node* left;
    struct Node* right;
};

// Create a new tree node
struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Search for a value in inorder array
int search(char inorder[], int start, int end, char value) {
    for (int i = start; i <= end; i++)
        if (inorder[i] == value)
            return i;
    return -1;
}

// Static index to keep track of current root in preorder
int preIndex = 0;

// Recursive function to build tree
struct Node* buildTree(char inorder[], char preorder[], int inStart, int inEnd) {
    if (inStart > inEnd)
        return NULL;

    // Pick current node from preorder
    char current = preorder[preIndex++];
    struct Node* node = newNode(current);

    // If this node has no children
    if (inStart == inEnd)
        return node;

    // Find index of current node in inorder
    int inIndex = search(inorder, inStart, inEnd, current);

    // Build left and right subtrees
    node->left = buildTree(inorder, preorder, inStart, inIndex - 1);
    node->right = buildTree(inorder, preorder, inIndex + 1, inEnd);

    return node;
}

// Postorder traversal (to verify tree)
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

int main() {
    // Example
    char inorder[] =  {'D', 'B', 'E', 'A', 'F', 'C'};
    char preorder[] = {'A', 'B', 'D', 'E', 'C', 'F'};
    int length = sizeof(inorder)/sizeof(inorder[0]);

    struct Node* root = buildTree(inorder, preorder, 0, length - 1);

    printf("Postorder traversal of the constructed tree:\n");
    postorder(root);

    return 0;
}
