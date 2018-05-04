#ifndef __deque__
#define __deque__

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
  int data;
  struct QueueNode *prev, *next;
} QueueNode;

QueueNode *createNode(int data) {
  QueueNode *newnode = (QueueNode *)malloc(sizeof(QueueNode));
  newnode->data = data;
  newnode->next = newnode->prev = NULL;
  return (newnode);
}

typedef struct Queue {
  QueueNode *head;
  QueueNode *tail;
} Queue;

void intializeQueue(Queue *queue) {
  queue->head = createNode(0);
  queue->tail = createNode(0);
  queue->head->next = queue->tail;
  queue->tail->prev = queue->head;
}

/* insertion at the front of the queue */
void enqueueAtFront(Queue *queue, int data) {
  QueueNode *newnode, *temp;
  newnode = createNode(data);
  temp = queue->head->next;
  queue->head->next = newnode;
  newnode->prev = queue->head;
  newnode->next = temp;
  temp->prev = newnode;
}

/*insertion at the rear of the queue */
void enqueueAtRear(Queue *queue, int data) {
  QueueNode *newnode, *temp;
  newnode = createNode(data);
  temp = queue->tail->prev;
  queue->tail->prev = newnode;
  newnode->next = queue->tail;
  newnode->prev = temp;
  temp->next = newnode;
}

/* deletion at the front of the queue */
void dequeueAtFront(Queue *queue) {
  QueueNode *temp;
  if (queue->head->next == queue->tail) {
    printf("Queue is empty\n");
  } else {
    temp = queue->head->next;
    queue->head->next = temp->next;
    temp->next->prev = queue->head;
    free(temp);
  }
  return;
}

/* deletion at the rear of the queue */

void dequeueAtRear(Queue *queue) {
  QueueNode *temp;
  if (queue->tail->prev == queue->head) {
    printf("Queue is empty\n");
  } else {
    temp = queue->tail->prev;
    queue->tail->prev = temp->prev;
    temp->prev->next = queue->tail;
    free(temp);
  }
  return;
}

/* display elements present in the queue */
void display(Queue *queue) {
  QueueNode *temp;

  if (queue->head->next == queue->tail) {
    printf("Queue is empty\n");
    return;
  }

  temp = queue->head->next;
  while (temp != queue->tail) {
    printf("%-3d", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

typedef struct ListOfQueues {
  Queue *listOfTwos[1000];
  Queue *listOfThrees[1000];
  int countOfTwos;
  int countOfThrees;
} ListOfQueues;

#endif