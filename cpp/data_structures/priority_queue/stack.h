
#ifndef __stack__
#define __stack__

#include <stdio.h>
#include <stdlib.h>

struct StackNode {
  int data;
  struct StackNode *next;
};

struct StackNode *top = NULL;
void push(int);
void pop();
void display();

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

#endif