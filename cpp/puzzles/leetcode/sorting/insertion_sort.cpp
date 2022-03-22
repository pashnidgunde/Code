#include "functors.h"
#include <iostream>
#include <vector>

template <typename T> void print(const std::vector<T> &v) {
  for (const auto &e : v)
    std::cout << e;

  std::cout << std::endl;
}

// Insertion sort
// Time complexity : O(n * n)

template <typename T, typename O> void sort(std::vector<T> &arr, O op) {
  // Have to check each element to find the right position for the element
  for (size_t i = 1; i < arr.size(); i++) {

    // Backup the original element, because when elements are moved to right, it
    // will be overwritten
    T temp = arr[i];

    // Start with index just before current index and compare.
    // Do this until we reach the begining
    // the temp is used in comparison because once elements are moved, the
    // location arr[i] will be overwritten
    T j = i - 1;
    while (j >= 0 && op(temp, arr[j])) {
      // Move elements to right
      arr[j + 1] = arr[j];
      j--;
    }

    // j+1 because for first location j will be -1 and we need j+1 for correct
    // location
    arr[j + 1] = temp;
  }
}

int main() {
  std::vector<int> arr{0, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9};
  sort(arr, pn::functors::greater<int>());
  print(arr);
  sort(arr, pn::functors::less<int>());
  print(arr);
  getchar();
  return 0;
}
