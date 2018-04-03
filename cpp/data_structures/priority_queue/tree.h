#ifndef __tree__
#define __tree__
#include <stdio.h>
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

/* Given a binary tree, print its nodes in preorder*/
void printPreorder(struct node *node) {
  if (node == NULL) return;

  /* first print data of node */
  printf("%d ", node->data);

  /* then recur on left sutree */
  printPreorder(node->left);

  /* now recur on right subtree */
  printPreorder(node->right);
}

#endif