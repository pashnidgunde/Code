/*

 * Simple implementation of Priority Queue

 */
#ifndef __priority_q__
#define __priority_q__

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define FIVE_PERCENT_MEMORY_SIZE (TOTAL * 0.05)

long MAX = 0;

void insertByPriority(double);

void check(double);
void create();
void display_pqueue();
double *pri_que;
int rear;

void destroyQueue() {
  if (NULL != pri_que) {
    free(pri_que);
  }
}
/* Function to create an empty priority queue */

void initializeQueue() {
  pri_que = (double *)(malloc(sizeof(double) * FIVE_PERCENT_MEMORY_SIZE));
  MAX = FIVE_PERCENT_MEMORY_SIZE;
  rear = -1;
  long i = 0;
  pri_que = (double *)(malloc(sizeof(double) * MAX));
  for (i = 0; i < MAX; i++) {
    pri_que[i] = DBL_MIN;
  }
}

void insertByPriority(double data) {
  /* Discard numbers less than 95 % */
  if (compare(data, pri_que[MAX - 1]) <= 0) {
    return;
  }

  /* First insert, can be done onece */
  if (rear == -1) {
    rear++;
    pri_que[rear] = data;
    return;
  }

  check(data);
  rear++;

  /* Dont go beyond the limit */
  if (rear >= MAX - 1) {
    rear = MAX - 1;
  }
}

/* Function to check priority and place element */
/* Binary search could still be faster */
void check(double data) {
  long i, j;
  for (i = 0; i <= rear; i++) {
    if (compare(data, pri_que[i]) >= 0) {
      // if (data >= pri_que[i]) {
      for (j = rear + 1; j > i; j--) {
        pri_que[j] = pri_que[j - 1];
      }
      pri_que[i] = data;
      return;
    }
  }
  pri_que[i] = data;
}

/* Function to display queue elements */

void display_pqueue() {
  long i = 0;
  for (i = 0; i <= MAX - 1; i++) {
    printf(" %f ", pri_que[i]);
  }
}

#endif