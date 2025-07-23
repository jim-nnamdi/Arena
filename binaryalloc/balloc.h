#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/** 
 * Data - This struct holds the info for the 
 * Binary Tree structure that would control
 * The data flow in the Allocator after being
 * Assigned some location based on filters ..
*/
typedef struct {
    size_t key;
    Node* left;
    Node* right;
}Node;

/**
 * BTAllocator - This struct holds the wrapper
 * For the Node struct and an unsigned data type
 * To clarify when a memory location is free
 */
typedef struct {
    Node* node;
    uint8_t free;
} BTAllocator;

/*
 * Creates a new Node with the given key value.
 *
 * Parameters:
 *   val - The key to assign to the new node.
 *
 * Returns:
 *   A pointer to the newly allocated Node, or NULL if memory allocation fails.
 */
Node* create(size_t val) {
    Node* node = (Node*)malloc(sizeof(Node));

    // Check if malloc failed
    if (!node) return NULL;

    // Set node fields
    node->key = val;
    node->left = node->right = NULL;

    return node;
}

/*
 * Inserts a new value into a binary search tree (BST).
 * If the tree is empty, it creates a new node.
 * Otherwise, it recursively finds the correct position
 * in the left or right subtree and inserts the value.
 *
 * Parameters:
 *   node - A pointer to the root of the BST or subtree.
 *   val  - The value to insert into the BST.
 *
 * Returns:
 *   The root node of the updated BST after insertion.
 */
Node* insert(Node* node, size_t val) {
    if (!node)
        return create(val);

    if (val < node->key) 
        node->left = insert(node->left, val);

    else if (val > node->key) 
        node->right = insert(node->right, val);

    return node;
}
