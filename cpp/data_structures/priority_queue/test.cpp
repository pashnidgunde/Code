
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
  // for (int i = 0; i < TOTAL; i++) reset();
  // for (i = 0; i < TOTAL; i++) {
  //  temp[i] = i;
  //}
  /*
    int arr1[25];

    arr1[0] = 37932331;
    arr1[1] = 1591192088;
    arr1[2] = 648523324;
    arr1[3] = 252100903;
    arr1[4] = 1161048718;
    arr1[5] = 171641421;
    arr1[6] = 557973181;
    arr1[7] = 1539865825;
    arr1[8] = 512631962;
    arr1[9] = 1217084747;
    arr1[10] = 1884299726;
    arr1[11] = 776429328;
    arr1[12] = 1989638393;
    arr1[13] = 1481392567;
    arr1[14] = 1843337599;
    arr1[15] = 294688427;
    arr1[16] = 107663924;
    arr1[17] = 233965757;
    arr1[18] = 1108122245;
    arr1[19] = 503867850;
    arr1[20] = 466734275;
    arr1[21] = 668618006;
    arr1[22] = 136395077;
    arr1[23] = 1997486272;
    arr1[24] = 2119751936;
  */
  reset();
  setPivotNumber(rand() % 25);
  for (i = 1; i < TOTAL; i++) {
    insert(rand() % 25);
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