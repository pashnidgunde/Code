
#include <iostream>
#include <vector>
#include "functors.h"

void print(const std::vector<int> &v) {
  for (const auto &e : v)
    std::cout << e << " ";
  std::cout << std::endl;
}

// Partition element considering pivot as last element of arrays
void partition(std::vector<int> &v, int begin, int end) {
  int i = begin-1;
  for (int j = begin; j < end; j++) {
      if (v[j] < v[end])
      {
        std::swap(v[i + 1], v[j]);
      }
  }

  std::swap(v[i + 1], v[end]);
}

// In quick sort you have to find a pivot such that 
// all elements to its left are lower than that of element at pivot
// and elements to its right are greater than element at pivot.
// Apply this same technique for sub arrays split in two at mid
// Method to split elements by comparing pivot element is called
// partitioning
void quick_sort(std::vector<int> &v, int begin, int end) { 
    if (begin < end)
    {
    partition(v, begin, end);
    int mid = (begin + end) / 2;
    quick_sort(v,begin, mid);
    quick_sort(v,mid + 1, end);
    }
}

int main() {
  std::vector<int> v{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  quick_sort(v,0,v.size()-1);
  print(v);

  char ch;
  std::cin >> ch;
  return 0;
}