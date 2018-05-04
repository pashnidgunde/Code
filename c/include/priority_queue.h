#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL 50000000 /*28000000*/ /*128,000,000*/
#define PERCENT_INDEX 0.95
#define PIVOT_INDEX (TOTAL * PERCENT_INDEX)
int MAX_INDEX = (TOTAL - 1);
int MIN_INDEX = 0;
int rear_index = PIVOT_INDEX - 1;
int front_index = PIVOT_INDEX + 1;

// double *arr = NULL;
double arr[TOTAL];

void insertAtFront(double);
void insertAtRear(double);
double getMax(double);
// int getMin(int);
void printrow();
int getMaxFromRange();

void reset() {
  // if (arr != NULL) {
  //  delete[] arr;
  //}

  // arr = (double *)malloc(sizeof(double) * TOTAL);

  int i = 0;
  for (i = 0; i <= MAX_INDEX; i++) {
    arr[i] = DBL_MIN;
  }

  pivot_index = PIVOT_INDEX;
  rear_index = PIVOT_INDEX - 1;
  front_index = PIVOT_INDEX + 1;
}

double getMax(double number) {
  double max = number;
  int max_number_index = INT_MIN;
  int i;
  for (i = MIN_INDEX; i < pivot_index; i++) {
    if (arr[i] > max) {
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
  int min_number_index = DBL_MAX;
  int i;
  for (i = MAX_INDEX; i >= pivot_index; i--) {
    if (arr[i] <= min) {
      min = arr[i];
      min_number_index = i;
    }
  }

  if (DBL_MAX != min_number_index) {
    arr[min_number_index] = number;
  }

  return min;
}
*/

void reorderRightSideOfPivot(double number) {
  insertAtRear(arr[pivot_index]);
  arr[pivot_index] = number;
  int max_index = getMaxFromRange();
  int i;
  for (i = pivot_index + 1; i <= MAX_INDEX; ++i) {
    if (i != max_index && arr[i] != DBL_MIN) {
      insertAtRear(arr[i]);
      arr[i] = DBL_MIN;
      front_index--;
    }
  }
  if (pivot_index != max_index) {
    insertAtRear(arr[pivot_index]);
    arr[pivot_index] = arr[max_index];
    arr[max_index] = DBL_MIN;
    front_index--;
  }
}

/*
void reorderRightSideOfPivot(int number) {
  int max = getMaxFromRange();
  int i;
  for (i = pivot_index + 1; i <= MAX_INDEX; ++i) {
    insertAtRear(arr[i]);
    arr[i] = DBL_MIN;
    front_index--;
  }
  insertAtRear(arr[pivot_index]);
  arr[pivot_index] = max;
}
*/
double getMinFromRange() {
  double min = DBL_MAX;
  int i;
  for (i = pivot_index; i <= MAX_INDEX; i++) {
    if (arr[i] < min) {
      min = arr[i];
    }
  }
  return min;
}

int getMaxFromRange() {
  int max_index = DBL_MIN;
  double max = DBL_MIN;
  int i;
  for (i = pivot_index; i <= MAX_INDEX; i++) {
    if (arr[i] > max) {
      max_index = i;
      max = arr[i];
    }
  }
  return max_index;
  // return max;
}

void insertAtFront(double number) {
  if (front_index > MAX_INDEX) {
    reorderRightSideOfPivot(number);
  } else {
    arr[front_index] = number;
    front_index++;
  }
}

void insertAtRear(double number) {
  double max = DBL_MIN;
  if (rear_index < MIN_INDEX) {
    max = getMax(number);
    insertAtFront(max);
  } else {
    arr[rear_index] = number;
    rear_index--;
  }
}

void insert(double number) {
  int compareResult = compare(number, arr[pivot_index]);
  if (compareResult <= 0) {
    insertAtRear(number);
  } else /* if (number > arr[pivot_index]) */
  {
    insertAtFront(number);
  }
  printrow();
}

void setPivotNumber(double number) {
  arr[pivot_index] = number;
  printrow();
}

// void print() { printf("\nOutput :: %d", getMinFromRange()); }

void printrow() {
  int i = 0;
  printf("[ %d %d %d] ==> ", pivot_index, front_index, rear_index);
  for (i = 0; i < TOTAL; i++) {
    if (arr[i] == DBL_MIN) {
      printf("-, ");
    } else {
      printf("%f, ", arr[i]);
    }
  }
  printf("\n");
}