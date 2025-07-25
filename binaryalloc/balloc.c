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
  
  /**
   * @brief 
   * Inorder Traversal for BinaryTree
   * Traverses Left & Iterates right
   * @param node 
   */
  void inorder(Node* node) {
    if (!node) return;
    inorder(node->left);
    printf("%d\n", node->key);
    inorder(node->right);
  }

  /**
   * @brief 
   * Preorder Traversal returns rootkey
   * Traverses Left & Traverses right
   * @param node 
   */
  void preorder(Node* node) {
    if (!node) return;
    printf(node->key);
    preorder(node->left);
    preorder(node->right);
  }

  /**
   * @brief 
   * Postorder Traversal iterates L&R
   * Then returns corresponding keys
   * @param node 
   */
  void postorder(Node* node){
    if (!node) return;
    postorder(node->left);
    postorder(node->right);
    printf(node->key);
  }