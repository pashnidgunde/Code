/*
 * max_sum_range.cpp
 *
 *  Created on: 16-Jan-2017
 *      Author: rupa
 */

#include <iostream>

void printMaxSumAndRange(int arr[], int size = 8) {
  int sum = 0;
  int max_sum = 0;
  int beginIndex = 0;
  int endIndex = 0;
  for (int i = 0; i < size; i++) {
    sum = sum + arr[i];
    if (sum < 0) {
      sum = 0;
    }
    if (max_sum < sum) {
      if (beginIndex == 0) {
        beginIndex = i;
      }
      if (endIndex < i) {
        endIndex = i;
      }
      max_sum = sum;
    }
  }

  std::cout << "Max sum :: " << max_sum;
  std::cout << "Begin Index :: " << beginIndex << " End Index :: " << endIndex
            << std::endl;
}

int main() {
  int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};

  printMaxSumAndRange(arr, 8);
}
