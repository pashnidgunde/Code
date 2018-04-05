#include <stdio.h>
#include <stdlib.h>
#include "./deque.h"
#include "./tree.h"

struct ListOfQueues hashmap[30];

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

int checkInHashMap(int currentNode, int weight) {
  int exists = 0;
  if ((weight == 2 && hashmap[currentNode].countOfTwos != 0) ||
      (weight == 3 && hashmap[currentNode].countOfThrees != 0)) {
    return 1;
  }
  return 0;
}

void getDataFromHashMap(int currentNode, int weight, Queue *queueForPath) {
  if (weight == 2) {
    for (int i = 0; i < hashmap[currentNode].countOfTwos; i++) {
      Queue *queue = hashmap[currentNode].listOfTwos[i];
      QueueNode *temp = queue->head->next;
      while (temp != queue->tail) {
        enqueueAtFront(queueForPath, temp->data);
        temp = temp->next;
      }
    }
  }
  if (weight == 3) {
    for (int i = 0; i < hashmap[currentNode].countOfThrees; i++) {
      Queue *queue = hashmap[currentNode].listOfThrees[i];
      QueueNode *temp = queue->head->next;
      while (temp != queue->tail) {
        enqueueAtFront(queueForPath, temp->data);
        temp = temp->next;
      }
    }
  }
}

void printPathsUtil(struct node *curr_node, Queue *queueForPath, int weight) {
  if (curr_node == NULL) return;

  if (weight != 0) {
    enqueueAtRear(queueForPath, weight);
  }

  if (checkInHashMap(curr_node->data, weight)) {
    getDataFromHashMap(curr_node->data, weight, queueForPath);
    display(queueForPath);
    return;
  }

  // if (curr_node->data == 0) {
  //  printf("\nPath found after 0: ");
  //  display(queueForPath);
  //}

  if (curr_node->left) {
    printPathsUtil(curr_node->left, queueForPath, 2);
  }
  if (curr_node->right) {
    printPathsUtil(curr_node->right, queueForPath, 3);
  }

  // printf("\n%d", curr_node->data);

  // Remove last element from path
  // and move back to parent
  dequeueAtRear(queueForPath);
}

int main() {
  // register first few patterns
  ListOfQueues zero;
  zero.countOfTwos = 0;
  zero.countOfThrees = 0;
  hashmap[0] = zero;

  // register first few patterns
  ListOfQueues one;
  one.countOfTwos = 0;
  one.countOfThrees = 0;
  hashmap[1] = one;

  // register first few patterns
  ListOfQueues two;
  Queue *q1 = (Queue *)malloc(sizeof(Queue));
  intializeQueue(q1);
  enqueueAtFront(q1, 2);
  two.countOfTwos = 1;
  two.countOfThrees = 0;
  two.listOfTwos[two.countOfTwos - 1] = q1;
  hashmap[2] = two;

  // register first few patterns
  ListOfQueues three;
  Queue *element = (Queue *)malloc(sizeof(Queue));
  intializeQueue(element);
  enqueueAtFront(element, 3);
  three.countOfTwos = 0;
  three.countOfThrees = 1;
  three.listOfThrees[three.countOfThrees - 1] = element;
  hashmap[3] = three;

  /*create root*/
  struct node *root = createNewTreeNode(10);
  buildTree(root);
  Queue *queueForPath = (Queue *)malloc(sizeof(Queue));
  intializeQueue(queueForPath);
  printPathsUtil(root, queueForPath, 0);
  // printPathsUtil(root->right, queueForPath, 2);
  // printPreorder(root);

  getchar();
  return 0;
}