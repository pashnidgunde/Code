#include <stdio.h>
#include <stdlib.h>
#include "./deque.h"
#include "./tree.h"

// Assumption that it wont grow beyond 100
Queue *bucketStartingWith2[100000];
Queue *bucketStartingWith3[100000];

void CopyToBuckets(Queue *queueForPath) {
  struct Queue *copy = NULL;
  struct QueueNode *temp = temp;
  intializeQueue(copy);

  if (queueForPath->head->next == queueForPath->tail) {
    // printf("Queue is empty\n");
    return;
  }

  // first element is 0, skip it
  temp = queueForPath->head->next->next;

  while (temp != queueForPath->tail) {
    enqueueAtRear(copy, temp->data);
    printf("%-3d", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

void printPathsUtil(struct node *curr_node, Queue *queueForPath, int sum,
                    int sum_so_far) {
  if (curr_node == NULL) return;

  // add the current node's value
  sum_so_far += curr_node->data;

  // add the value to path
  enqueueAtRear(queueForPath, curr_node->data);

  // print the required path
  if (sum_so_far == sum) {
    printf("\nPath found: ");
    display(queueForPath);
    // copyToBuckets(queueForPath);
  }

  // if left child exists
  if (curr_node->left != NULL)
    printPathsUtil(curr_node->left, queueForPath, sum, sum_so_far);

  // if right child exists
  if (curr_node->right != NULL)
    printPathsUtil(curr_node->right, queueForPath, sum, sum_so_far);

  // Remove last element from path
  // and move back to parent
  dequeueAtRear(queueForPath);
}

void buildTree(struct node *parent, int remaining) {
  struct node *newNode = NULL;
  if (remaining <= 0) return;
  if (remaining - 2 >= 0) {
    newNode = createNewTreeNode(2);
    parent->left = newNode;
    buildTree(newNode, remaining - 2);
  }
  if (remaining - 3 >= 0) {
    newNode = createNewTreeNode(3);
    parent->right = newNode;
    buildTree(newNode, remaining - 3);
  }
}

int main() {
  /*create root*/
  struct node *root = createNewTreeNode(0);
  buildTree(root, 330);

  Queue *queueForPath = (Queue *)(malloc(sizeof(Queue)));
  intializeQueue(queueForPath);
  printPathsUtil(root, queueForPath, 330, 0);

  getchar();
  return 0;
}