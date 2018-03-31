#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL 25
#define PERCENT_INDEX 95

int MAX_INDEX = (TOTAL - 1);
int MIN_INDEX = 0;

//#define PIVOT_INDEX (TOTAL - (TOTAL * PERCENT_INDEX / 100))

#define PIVOT_INDEX ((TOTAL * PERCENT_INDEX / 100))

int pivot_index = PIVOT_INDEX;
int rear_index = PIVOT_INDEX - 1;
int front_index = PIVOT_INDEX + 1;

int arr[TOTAL];

void insertAtFront(int);
void insertAtRear(int);
int getMax(int);
// int getMin(int);
void printrow();
int getMaxFromRange();

void reset() {
  int i = 0;
  for (i = 0; i <= MAX_INDEX; i++) {
    arr[i] = INT_MIN;
  }

  pivot_index = PIVOT_INDEX;
  rear_index = PIVOT_INDEX - 1;
  front_index = PIVOT_INDEX + 1;
}

int getMax(int number) {
  int max = number;
  int max_number_index = INT_MIN;
  int i;
  for (i = MIN_INDEX; i < pivot_index; i++) {
    if (arr[i] >= max) {
      max = arr[i];
      max_number_index = i;
    }
  }

  if (INT_MIN != max_number_index) {
    arr[max_number_index] = number;
  }
  return max;
}

/*
int getMin(int number) {
  int min = number;
  int min_number_index = INT_MAX;
  int i;
  for (i = MAX_INDEX; i >= pivot_index; i--) {
    if (arr[i] <= min) {
      min = arr[i];
      min_number_index = i;
    }
  }

  if (INT_MAX != min_number_index) {
    arr[min_number_index] = number;
  }

  return min;
}
*/
void reorderRightSideOfPivot(int number) {
  insertAtRear(arr[pivot_index]);
  arr[pivot_index] = number;
  int max = getMaxFromRange();
  int i;
  for (i = pivot_index; i <= MAX_INDEX; ++i) {
    if (arr[i] < max && arr[i] != INT_MIN) {
      insertAtRear(arr[i]);
      arr[i] = INT_MIN;
      front_index--;
    }
  }
  // insertAtRear(arr[pivot_index]);
  arr[pivot_index] = max;
}

int getMinFromRange() {
  int min = INT_MAX;
  int i;
  for (i = pivot_index; i <= MAX_INDEX; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
  }
  return min;
}

int getMaxFromRange() {
  int max = INT_MIN;
  int i;
  for (i = pivot_index; i <= MAX_INDEX; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

void insertAtFront(int number) {
  if (front_index > MAX_INDEX) {
    reorderRightSideOfPivot(number);
  } else {
    arr[front_index] = number;
    front_index++;
  }
}

void insertAtRear(int number) {
  int max = INT_MIN;
  if (rear_index < MIN_INDEX) {
    max = getMax(number);
    insertAtFront(max);
  } else {
    arr[rear_index] = number;
    rear_index--;
  }
}

void insert(int number) {
  if (number <= arr[pivot_index]) {
    insertAtRear(number);
  } else  // if (number > arr[pivot_index])
  {
    insertAtFront(number);
  }
  printrow();
}

void setPivotNumber(int number) {
  arr[pivot_index] = number;
  printrow();
}

void print() {
  int i = 0;
  for (i = 0; i < TOTAL; ++i) {
    printf("\narr[%d] : %d", i, arr[i]);
  }

  printf("\nOutput :: %d", getMinFromRange());
}

void printrow() {
  int i = 0;
  printf("[ %d %d %d] ==> ", pivot_index, front_index, rear_index);
  for (i = 0; i < TOTAL; i++) {
    if (arr[i] == INT_MIN) {
      printf("-, ");
    } else {
      printf("%d, ", arr[i]);
    }
  }
  printf("\n");
}