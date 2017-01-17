#include <iostream>

void merge(int arr[], int b, int m, int e) {
  int lsize = (m - b) + 1;
  int rsize = (e - m);

  int larray[lsize];
  int rarray[rsize];

  for (int i = 0; i < lsize; i++) {
    larray[i] = arr[b + i];
  }

  for (int j = 0; j < rsize; j++) {
    rarray[j] = arr[m + 1 + 1];
  }

  int i = 0, j = 0, k = 0;

  while ((i < lsize) && (j < rsize)) {
    if (larray[i] <= rarray[j]) {
      arr[k] = larray[i];
      i++;
      k++;
    } else {
      arr[k] = rarray[j];
      j++;
      k++;
    }
  }

  while (i < lsize) {
    arr[k] = larray[i];
    k++;
    i++;
  }

  while (j < rsize) {
    arr[k] = rarray[j];
    k++;
    j++;
  }
}

void mergeSort(int arr[], int b, int e) {
  if (b < e) {
    int m = (b + e) / 2;
    mergeSort(arr, b, m);
    mergeSort(arr, m + 1, e);

    merge(arr, b, m, e);
  }
}

int arr[10] = {3, 2, 1};

int main() {
  mergeSort(arr, 0, 2);
  return 0;
}
