#ifndef __tree__
#define __tree__
#include <stdlib.h>

struct node {
  int data;
  struct node *left;
  struct node *right;
};

/* newNode() allocates a new node with the given data and NULL left and
   right pointers. */
struct node *createNewTreeNode(int data) {
  // Allocate memory for new node
  struct node *node = (struct node *)malloc(sizeof(struct node));

  // Assign data to this node
  node->data = data;

  // Initialize left and right children as NULL
  node->left = NULL;
  node->right = NULL;
  return (node);
}

#endif