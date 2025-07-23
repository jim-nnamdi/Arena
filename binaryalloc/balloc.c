#include "balloc.h"

/**
 * @brief
 * New instance of the Binary tree
 * Used for initialising other Nodes 
 * @param val 
 * @return Node* 
 */
Node *create(size_t val) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
      return NULL;
    node->key = val;
    node->left = node->right = NULL;
  
    return node;
  }
  
  /**
   * @brief 
   * Insert Node values into the Tree
   * Parameterize corresponding Nodes
   * @param node 
   * @param val 
   * @return Node* 
   */
  Node *insert(Node *node, size_t val) {
    if (!node)
      return create(val);
    if (val < node->key)
      node->left = insert(node->left, val);
    else if (val > node->key)
      node->right = insert(node->right, val);
    return node;
  }
  