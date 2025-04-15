#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN_DEGREE 3
#define MAX_KEYS (2*MIN_DEGREE-1)
#define MIN_KEYS (MIN_DEGREE-1)
#define MAX_CHILDREN (2*MIN_DEGREE)

typedef struct BTreeNode {
    bool is_leaf;
    int num_keys;
    int keys[MAX_KEYS];
    struct BTreeNode *children[MAX_CHILDREN];
} BTreeNode;

BTreeNode* create_node(bool is_leaf) {
    BTreeNode* new_node = (BTreeNode*)malloc(sizeof(BTreeNode));
    new_node->is_leaf = is_leaf;
    new_node->num_keys = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        new_node->children[i] = NULL;
    }
    return new_node;
}

void traverse(BTreeNode* node) {
    int i;
    for (i = 0; i < node->num_keys; i++) {
        if (!node->is_leaf) {
            traverse(node->children[i]);
        }
        printf(" %d", node->keys[i]);
    }
    if (!node->is_leaf) {
        traverse(node->children[i]);
    }
}

BTreeNode* search(BTreeNode* node, int key) {
    int i = 0;
    while (i < node->num_keys && key > node->keys[i]) {
        i++;
    }
    if (i < node->num_keys && key == node->keys[i]) {
        return node;
    }
    if (node->is_leaf) {
        return NULL;
    }
    return search(node->children[i], key);
}

void split_child(BTreeNode* parent, int index, BTreeNode* child) {
    BTreeNode* new_child = create_node(child->is_leaf);
    new_child->num_keys = MIN_KEYS;
    
    for (int i = 0; i < MIN_KEYS; i++) {
        new_child->keys[i] = child->keys[i + MIN_DEGREE];
    }
    
    if (!child->is_leaf) {
        for (int i = 0; i < MIN_DEGREE; i++) {
            new_child->children[i] = child->children[i + MIN_DEGREE];
        }
    }
    
    child->num_keys = MIN_KEYS;
    
    for (int i = parent->num_keys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    
    parent->children[index + 1] = new_child;
    
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    
    parent->keys[index] = child->keys[MIN_KEYS];
    parent->num_keys++;
}

void insert_non_full(BTreeNode* node, int key) {
    int i = node->num_keys - 1;
    
    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        
        if (node->children[i]->num_keys == MAX_KEYS) {
            split_child(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insert_non_full(node->children[i], key);
    }
}

void insert(BTreeNode** root, int key) {
    BTreeNode* node = *root;
    
    if (node->num_keys == MAX_KEYS) {
        BTreeNode* new_root = create_node(false);
        new_root->children[0] = node;
        *root = new_root;
        split_child(new_root, 0, node);
        insert_non_full(new_root, key);
    } else {
        insert_non_full(node, key);
    }
}

int get_predecessor(BTreeNode* node, int index) {
    BTreeNode* current = node->children[index];
    while (!current->is_leaf) {
        current = current->children[current->num_keys];
    }
    return current->keys[current->num_keys - 1];
}

int get_successor(BTreeNode* node, int index) {
    BTreeNode* current = node->children[index + 1];
    while (!current->is_leaf) {
        current = current->children[0];
    }
    return current->keys[0];
}

void merge(BTreeNode* node, int index) {
    BTreeNode* child = node->children[index];
    BTreeNode* sibling = node->children[index + 1];
    
    child->keys[MIN_KEYS] = node->keys[index];
    
    for (int i = 0; i < sibling->num_keys; i++) {
        child->keys[i + MIN_DEGREE] = sibling->keys[i];
    }
    
    if (!child->is_leaf) {
        for (int i = 0; i <= sibling->num_keys; i++) {
            child->children[i + MIN_DEGREE] = sibling->children[i];
        }
    }
    
    for (int i = index + 1; i < node->num_keys; i++) {
        node->keys[i - 1] = node->keys[i];
    }
    
    for (int i = index + 2; i <= node->num_keys; i++) {
        node->children[i - 1] = node->children[i];
    }
    
    child->num_keys += sibling->num_keys + 1;
    node->num_keys--;
    
    free(sibling);
}

void borrow_from_prev(BTreeNode* node, int index) {
    BTreeNode* child = node->children[index];
    BTreeNode* sibling = node->children[index - 1];
    
    for (int i = child->num_keys - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }
    
    if (!child->is_leaf) {
        for (int i = child->num_keys; i >= 0; i--) {
            child->children[i + 1] = child->children[i];
        }
    }
    
    child->keys[0] = node->keys[index - 1];
    
    if (!child->is_leaf) {
        child->children[0] = sibling->children[sibling->num_keys];
    }
    
    node->keys[index - 1] = sibling->keys[sibling->num_keys - 1];
    
    child->num_keys++;
    sibling->num_keys--;
}

void borrow_from_next(BTreeNode* node, int index) {
    BTreeNode* child = node->children[index];
    BTreeNode* sibling = node->children[index + 1];
    
    child->keys[child->num_keys] = node->keys[index];
    
    if (!child->is_leaf) {
        child->children[child->num_keys + 1] = sibling->children[0];
    }
    
    node->keys[index] = sibling->keys[0];
    
    for (int i = 1; i < sibling->num_keys; i++) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    
    if (!sibling->is_leaf) {
        for (int i = 1; i <= sibling->num_keys; i++) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }
    
    child->num_keys++;
    sibling->num_keys--;
}

void fill(BTreeNode* node, int index) {
    if (index != 0 && node->children[index - 1]->num_keys > MIN_KEYS) {
        borrow_from_prev(node, index);
    } else if (index != node->num_keys && node->children[index + 1]->num_keys > MIN_KEYS) {
        borrow_from_next(node, index);
    } else {
        if (index != node->num_keys) {
            merge(node, index);
        } else {
            merge(node, index - 1);
        }
    }
}

void delete_from_leaf(BTreeNode* node, int index) {
    for (int i = index + 1; i < node->num_keys; i++) {
        node->keys[i - 1] = node->keys[i];
    }
    node->num_keys--;
}

void delete_from_non_leaf(BTreeNode* node, int index) {
    int key = node->keys[index];
    
    if (node->children[index]->num_keys >= MIN_DEGREE) {
        int pred = get_predecessor(node, index);
        node->keys[index] = pred;
        delete_key(node->children[index], pred);
    } else if (node->children[index + 1]->num_keys >= MIN_DEGREE) {
        int succ = get_successor(node, index);
        node->keys[index] = succ;
        delete_key(node->children[index + 1], succ);
    } else {
        merge(node, index);
        delete_key(node->children[index], key);
    }
}

void delete_key(BTreeNode* node, int key) {
    int index = 0;
    while (index < node->num_keys && key > node->keys[index]) {
        index++;
    }
    
    if (index < node->num_keys && key == node->keys[index]) {
        if (node->is_leaf) {
            delete_from_leaf(node, index);
        } else {
            delete_from_non_leaf(node, index);
        }
    } else {
        if (node->is_leaf) {
            printf("Key %d not found in the tree\n", key);
            return;
        }
        
        bool flag = (index == node->num_keys);
        
        if (node->children[index]->num_keys < MIN_DEGREE) {
            fill(node, index);
        }
        
        if (flag && index > node->num_keys) {
            delete_key(node->children[index - 1], key);
        } else {
            delete_key(node->children[index], key);
        }
    }
}

void delete(BTreeNode** root, int key) {
    if (!*root) {
        printf("Tree is empty\n");
        return;
    }
    
    delete_key(*root, key);
    
    if ((*root)->num_keys == 0) {
        BTreeNode* temp = *root;
        if ((*root)->is_leaf) {
            *root = NULL;
        } else {
            *root = (*root)->children[0];
        }
        free(temp);
    }
}

int predecessor(BTreeNode* root, int key) {
    BTreeNode* current = root;
    BTreeNode* ancestor = NULL;
    int pred = -1;
    
    while (current != NULL) {
        int i = 0;
        while (i < current->num_keys && key > current->keys[i]) {
            pred = current->keys[i];
            i++;
        }
        
        if (i < current->num_keys && key == current->keys[i]) {
            if (!current->is_leaf) {
                BTreeNode* temp = current->children[i];
                while (!temp->is_leaf) {
                    temp = temp->children[temp->num_keys];
                }
                return temp->keys[temp->num_keys - 1];
            } else if (i > 0) {
                return current->keys[i - 1];
            }
            return pred;
        }
        
        if (current->is_leaf) {
            return pred;
        }
        
        current = current->children[i];
    }
    
    return -1;
}

int successor(BTreeNode* root, int key) {
    BTreeNode* current = root;
    BTreeNode* ancestor = NULL;
    int succ = -1;
    
    while (current != NULL) {
        int i = 0;
        while (i < current->num_keys && key >= current->keys[i]) {
            i++;
        }
        
        if (i < current->num_keys) {
            succ = current->keys[i];
        }
        
        if (i < current->num_keys && key == current->keys[i]) {
            if (!current->is_leaf) {
                BTreeNode* temp = current->children[i + 1];
                while (!temp->is_leaf) {
                    temp = temp->children[0];
                }
                return temp->keys[0];
            } else if (i < current->num_keys - 1) {
                return current->keys[i + 1];
            }
            return succ;
        }
        
        if (current->is_leaf) {
            return succ;
        }
        
        current = current->children[i];
    }
    
    return -1;
}

void free_tree(BTreeNode* node) {
    if (node == NULL) return;
    
    if (!node->is_leaf) {
        for (int i = 0; i <= node->num_keys; i++) {
            free_tree(node->children[i]);
        }
    }
    
    free(node);
}

int main() {
    BTreeNode* root = create_node(true);
    
    // Insert keys
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(keys)/sizeof(keys[0]);
    
    for (int i = 0; i < n; i++) {
        insert(&root, keys[i]);
        printf("Inserted %d: ", keys[i]);
        traverse(root);
        printf("\n");
    }
    
    // Search for keys
    printf("Search for 6: %s\n", search(root, 6) ? "Found" : "Not Found");
    printf("Search for 15: %s\n", search(root, 15) ? "Found" : "Not Found");
    
    // Predecessor and successor
    printf("Predecessor of 7: %d\n", predecessor(root, 7));
    printf("Successor of 12: %d\n", successor(root, 12));
    
    // Delete keys
    int delete_keys[] = {6, 13, 7, 4, 20};
    for (int i = 0; i < sizeof(delete_keys)/sizeof(delete_keys[0]); i++) {
        delete(&root, delete_keys[i]);
        printf("Deleted %d: ", delete_keys[i]);
        traverse(root);
        printf("\n");
    }
    
    free_tree(root);
    
    return 0;
}