#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Data - This struct holds the info for the
 * Binary Tree structure that would control
 * The data flow in the Allocator after being
 * Assigned some location based on filters ..
 */
typedef struct {
  size_t key;
  Node *left;
  Node *right;
} Node;

/**
 * BTAllocator - This struct holds the wrapper
 * For the Node struct and an unsigned data type
 * To clarify when a memory location is free
 */
typedef struct {
  Node *node;
  uint8_t free;
} BTAllocator;
