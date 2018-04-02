#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

struct node {
  int data;
  struct node *left;
  struct node *right;
};

struct StackNode {
  int data;
  struct StackNode *next;
};

struct StackNode *top = NULL;
void push(int);
void pop();
void display();

/* newNode() allocates a new node with the given data and NULL left and
   right pointers. */
struct node *createNewNode(int data) {
  // Allocate memory for new node
  struct node *node = (struct node *)malloc(sizeof(struct node));

  // Assign data to this node
  node->data = data;

  // Initialize left and right children as NULL
  node->left = NULL;
  node->right = NULL;
  return (node);
}

void buildTree(struct node *parent, int remaining) {
  struct node *newNode = NULL;
  if (remaining <= 0) return;
  if (remaining - 2 >= 0) {
    newNode = createNewNode(2);
    parent->left = newNode;
    buildTree(newNode, remaining - 2);
  }
  if (remaining - 3 >= 0) {
    newNode = createNewNode(3);
    parent->right = newNode;
    buildTree(newNode, remaining - 3);
  }
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

void printPathsUtil(struct node *curr_node, int sum, int sum_so_far) {
  if (curr_node == NULL) return;

  // add the current node's value
  sum_so_far += curr_node->data;

  // add the value to path
  push(curr_node->data);

  // print the required path
  if (sum_so_far == sum) {
    printf("\nPath found: ");
    display();
  }

  // if left child exists
  if (curr_node->left != NULL) printPathsUtil(curr_node->left, sum, sum_so_far);

  // if right child exists
  if (curr_node->right != NULL)
    printPathsUtil(curr_node->right, sum, sum_so_far);

  // Remove last element from path
  // and move back to parent
  pop();
}

void push(int value) {
  struct StackNode *newNode =
      (struct StackNode *)malloc(sizeof(struct StackNode));
  newNode->data = value;
  if (top == NULL)
    newNode->next = NULL;
  else
    newNode->next = top;
  top = newNode;
  // printf("\nInsertion is Success!!!\n");
}

void pop() {
  if (top == NULL)
    // printf("\nStack is Empty!!!\n");
    return;
  else {
    struct StackNode *temp = top;
    // printf("\nDeleted element: %d", temp->data);
    top = temp->next;
    free(temp);
  }
}

void display() {
  if (top == NULL) {
    // printf("\nStack is Empty!!!\n");
    return;
  } else {
    struct StackNode *temp = top;
    while (temp->next != NULL) {
      printf("%d--->", temp->data);
      temp = temp->next;
    }
    printf("%d--->NULL", temp->data);
  }
}

int main() {
  /*create root*/
  struct node *root = createNewNode(0);
  buildTree(root, 10);
  // printPreorder(root);
  printPathsUtil(root, 10, 0);

  getchar();
  return 0;
}