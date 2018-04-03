#include <stdio.h>
#include <stdlib.h>
#include "./deque.h"
#include "./tree.h"

// Max to 30
struct ListOfQueues *hashmap[30];

void buildTree(struct node *parent) {
  struct node *newNode = NULL;
  if (parent->data < 0) return;

  if (parent->data - 2 >= 0) {
    newNode = createNewTreeNode(parent->data - 2);
    parent->left = newNode;
    buildTree(newNode);
  }
  if (parent->data - 3 >= 0) {
    newNode = createNewTreeNode(parent->data - 3);
    parent->right = newNode;
    buildTree(newNode);
  }
}

void printPathsUtil(struct node *curr_node, Queue *queueForPath, int weight) {
  if (curr_node == NULL) return;

  if (weight != 0) {
    enqueueAtRear(queueForPath, weight);
  }

  if (curr_node->data == 0) {
    printf("\nPath found: ");
    display(queueForPath);
  }

  if (curr_node->left) {
    printPathsUtil(curr_node->left, queueForPath, 2);
  }
  if (curr_node->right) {
    printPathsUtil(curr_node->right, queueForPath, 3);
  }

  // Remove last element from path
  // and move back to parent
  dequeueAtRear(queueForPath);
}

int main() {
  // register first few patterns
  ListOfQueues *zero = (ListOfQueues *)(malloc(sizeof(ListOfQueues)));
  zero->countOfTwos = 0;
  zero->countOfThrees = 0;
  hashmap[0] = zero;

  // register first few patterns
  ListOfQueues *one = (ListOfQueues *)(malloc(sizeof(ListOfQueues)));
  one->countOfTwos = 0;
  one->countOfThrees = 0;
  hashmap[1] = one;

  // register first few patterns
  ListOfQueues *two = (ListOfQueues *)(malloc(sizeof(ListOfQueues)));
  Queue *q1 = (Queue *)malloc(sizeof(Queue));
  intializeQueue(q1);
  enqueueAtFront(q1, 2);
  two->countOfTwos = 1;
  two->countOfThrees = 0;
  two->listOfTwos[two->countOfTwos - 1] = q1;
  hashmap[2] = two;

  // register first few patterns
  ListOfQueues *three = (ListOfQueues *)(malloc(sizeof(ListOfQueues)));
  Queue *element = (Queue *)malloc(sizeof(Queue));
  intializeQueue(element);
  enqueueAtFront(element, 3);
  two->countOfTwos = 0;
  two->countOfThrees = 1;
  two->listOfTwos[two->countOfThrees - 1] = element;
  hashmap[3] = three;

  /*create root*/
  struct node *root = createNewTreeNode(10);
  buildTree(root);
  Queue *queueForPath = (Queue *)malloc(sizeof(Queue));
  intializeQueue(queueForPath);
  printPathsUtil(root, queueForPath, 0);
  // printPathsUtil(root->right, queueForPath, 2);
  printPreorder(root);

  getchar();
  return 0;
}