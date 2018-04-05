#ifndef __quick_sort__
#define __quick_sort__

#include <stdlib.h>
#include <time.h>
#include "utils.h"

#define PERCENT_INDEX 0.95
#define PIVOT_INDEX (TOTAL * PERCENT_INDEX)

long pivot_index = PIVOT_INDEX;
long MAX_INDEX = (TOTAL - 1);
long MIN_INDEX = 0;
double* input = NULL;

void initialize() {
  long i = 0;
  input = (double*)malloc(TOTAL * sizeof(double)); /* test code */
  srand(time(NULL));
  for (i = 0; i < TOTAL; i++) {
    input[i] = (double)(rand() / (double)RAND_MAX);
  }
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    arr1ay, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(double arr1[], long low, long high) {
  double pivot = arr1[high];
  long i = (low - 1);

  for (long j = low; j <= high - 1; j++) {
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
double quickSortK(double arr1[], long low, long high, long k) {
  if (low < high) {
    /* pi is partitioning index, arr1[p] is now
       at right place */
    long pi = partition(arr1, low, high);
    if (pi < k) {
      quickSortK(arr1, pi + 1, high, k);
    } else if (pi > k) {
      quickSortK(arr1, low, pi - 1, k);
    }
  }
  return arr1[k];
}

double testUsingQSort() {
  initialize();
  /*quickSort(arr1, MIN_INDEX, MAX_INDEX);*/
  /* printf("\nOutput :: %.*e", DECIMAL_DIG, arr1[pivot_index]); */

  /* faster version of quick sort*/
  quickSortK(input, MIN_INDEX, MAX_INDEX, pivot_index);
  return input[pivot_index];
}

double* getInputArray() { return input; }

#endif