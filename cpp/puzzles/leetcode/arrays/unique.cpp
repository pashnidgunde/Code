/*
 * unique.cpp
 *
 *  Created on: 15-Jan-2017
 *      Author: rupa
 */

#include <iostream>

int arr[] = {1, 2, 2, 1, 2, 7, 2, 7, 3, 4, 5, 8, 1, 2, 8};

void remove(int array[], int j, int size) {
  std::cout << "Removing::" << array[j] << std::endl;
  while (j < size) {
    array[j] = array[j + 1];
    j++;
  }
}

void print(int array[], int size) {
  for (int i = 0; i < size; i++) {
    std::cout << arr[i];
  }
  std::cout << std::endl;
}

int unique(int array[], int size) {
  for (int i = 0; i < size; i++) {
    int j = i + 1;
    while (j < size) {
      if (array[i] == array[j]) {
        remove(array, j, size);
        size--;
        print(array, size);
      } else {
        j++;
      }
    }
  }
  return size;
}

int main() { int size = unique(arr, 15); }
