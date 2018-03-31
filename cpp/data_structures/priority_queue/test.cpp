
#include <iostream>
#include "priority_queue.h"

// A utility function to swap two elements
void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    arr1ay, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(int arr1[], int low, int high) {
  int pivot = arr1[high];  // pivot
  int i = (low - 1);       // Index of smaller element

  for (int j = low; j <= high - 1; j++) {
    // If current element is smaller than or
    // equal to pivot
    if (arr1[j] <= pivot) {
      i++;  // increment index of smaller element
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
void quickSort(int arr1[], int low, int high) {
  if (low < high) {
    /* pi is partitioning index, arr1[p] is now
       at right place */
    int pi = partition(arr1, low, high);

    // Separately sort elements before
    // partition and after partition
    quickSort(arr1, low, pi - 1);
    quickSort(arr1, pi + 1, high);
  }
}

int main() {
  int i = 0;

  // int* temp = new int[TOTAL];

  // int* temp2 = temp;

  srand(time(NULL));

  reset();
  setPivotNumber(rand() % TOTAL);
  for (i = 1; i < TOTAL; i++) {
    insert(rand() % TOTAL);
  }
  print();

  quickSort(arr, MIN_INDEX, MAX_INDEX);
  std::cout << "\nOutput from Quick Sort= " << arr[pivot_index] << std::endl;
}

/*
int main1() {
  int i = 0;

  srand(time(NULL));

  // Test 1 = pivot_index Extreme Right
  reset();
  setPivotNumber(18);
  for (i = 0; i < TOTAL - 1; i++) {
    insert(i);
  }
  print();

  // Test 1 = pivot_index Extreme Left
  reset();
  setPivotNumber(1);
  for (i = 0; i < TOTAL - 1; i++) {
    insert(i);
  }
  print();

  // Test 1 = pivot_index random
  reset();
  setPivotNumber(rand() % 20);
  for (i = 0; i < TOTAL - 1; i++) {
    insert(rand() % 100);
  }
  print();

  return 0;
}

*/