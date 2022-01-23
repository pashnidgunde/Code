
#include "functors.h"
#include <iostream>
#include <vector>

template <typename T> void print(const std::vector<T> &v) {
  for (const auto &e : v)
    std::cout << e;

  std::cout << std::endl;
}

// Merge sort works on divide and conquer
// So we have to first divide the list to an extent that one element can be
// compared against another

template <typename T, typename O>
void merge(std::vector<T> &arr, int l, int m, int h, O op) {
  // Need to have seperate arrays, so that after comparison we can put the right
  // element in the vector
  const std::vector<T> lower_arr(arr.begin() + l, arr.begin() + m + 1);
  const std::vector<T> higher_arr(arr.begin() + m + 1, arr.begin() + h + 1);

  // iterators for lower , higher and actual result vectors
  size_t i = 0, j = 0, k = l;

  // compare elements
  while (i < lower_arr.size() && j < higher_arr.size()) {
    arr[k++] =
        // Note use of operator( less and greater )
        op(lower_arr[i], higher_arr[j]) ? lower_arr[i++] : higher_arr[j++];
  }

  // check if any element exists in the first vector
  while (i < lower_arr.size()) {
    arr[k++] = lower_arr[i++];
  }

  // check if element exists in the second vector
  while (j < higher_arr.size()) {
    arr[k++] = higher_arr[j++];
  }
}

// This function divides the arr to smallest magnitude
// Once divided , merge it back
template <typename T, typename O>
void sort(std::vector<T> &arr, int l, int h, O op) {
  if (l < h) {
    // Mid ( considers overflow of numbers)
    auto m = l + (h - l) / 2;

    sort(arr, l, m, op);
    sort(arr, m + 1, h, op);

    merge(arr, l, m, h, op);
  }
}

int main() {
  std::vector<int> arr{0, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9};
  sort(arr, 0, arr.size() - 1, pn::functors::greater<int>());
  print(arr);
  sort(arr, 0, arr.size() - 1, pn::functors::less<int>());
  print(arr);
  getchar();
  return 0;
}
