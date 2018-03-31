
#include <float.h>  /* For float limits */
#include <stdio.h>  /* standard input outuput */
#include <stdlib.h> /* malloc */

#define TOTAL 128000000 /* SAMPLE SIZE */
#define PERCENT_INDEX 0.95
#define PIVOT_INDEX (TOTAL * PERCENT_INDEX)
int pivot_index = PIVOT_INDEX;
int MAX_INDEX = (TOTAL - 1);
int MIN_INDEX = 0;

int compare(double lhs, double rhs) {
  if (lhs < rhs)
    return -1;
  else if (lhs > rhs)
    return 1;
  return 0;
}

/* A utility function to swap two elements */
void swap(double* a, double* b) {
  double t = *a;
  *a = *b;
  *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    arr1ay, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(double arr1[], int low, int high) {
  double pivot = arr1[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    /* If current element is smaller than or
    equal to pivot for doubles */
    int compareResult = compare(arr1[j], pivot);
    if (compareResult <= 0) {
      i++; /* increment index of smaller element */
      swap(&arr1[i], &arr1[j]);
    }
  }
  swap(&arr1[i + 1], &arr1[high]);
  return (i + 1);
}

/* The main function that implements QuickSort
 arr1[] --> arr1ay to be sorted,
  low  --> Starting index,
  high  --> Ending index */
/*
void quickSort(double arr1[], int low, int high) {
  if (low < high) {
    int pi = partition(arr1, low, high);

    quickSort(arr1, low, pi - 1);
    quickSort(arr1, pi + 1, high);
  }
}
*/

/* The main function that implements QuickSort but discards small numbers
 arr1[] --> arr1ay to be sorted,
  low  --> Starting index,
  high  --> Ending index */
double quickSortK(double arr1[], int low, int high, int k) {
  if (low < high) {
    /* pi is partitioning index, arr1[p] is now
       at right place */
    int pi = partition(arr1, low, high);
    if (pi < k) {
      quickSortK(arr1, pi + 1, high, k);
    } else if (pi > k) {
      quickSortK(arr1, low, pi - 1, k);
    }
  }
  return arr1[k];
}

int main() {
  int i = 0;

  double* input = (double*)malloc(TOTAL * sizeof(double));

  /* test code */
  /*srand(time(NULL));
  for (i = 0; i < TOTAL; i++) {
    input[i] = (double)(rand() / (double)RAND_MAX);
  }*/

  /* Requirement to use console input */
  for (i = 0; i < TOTAL; i++) {
    scanf("%lf", &input[i]);
  }
  /* quickSort(arr1, MIN_INDEX, MAX_INDEX);*/
  /* printf("\nOutput :: %.*e", DECIMAL_DIG, arr1[pivot_index]); */

  /* faster version*/
  quickSortK(input, MIN_INDEX, MAX_INDEX, pivot_index);
  printf("\nOutput :: %.*e", DECIMAL_DIG, input[pivot_index]);

  /* assert(quickSort(...)[pivot_index] == quickSortFast(...)[pivot_index]) */
  free(input);
}
