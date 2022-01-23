#include <iostream>
#include <math.h>
#include <vector>

// Facts of binary heap is that it can be represented in a vector or array
//  iParent(i)     = floor((i-1) / 2) where floor functions map a real number to
//  the smallest leading integer.
//  iLeftChild(i)  = 2*i + 1   // Left child of index I
//  iRightChild(i) = 2*i + 2   // Right child of index I

void print(const std::vector<int> &v) {
  for (const auto &e : v)
    std::cout << e << " ";
  std::cout << std::endl;
}

//  iParent(i) = floor((i-1) / 2) where floor functions
//  map a real number to the smallest leading integer.
int getParent(int index) { return floor((index - 1) / 2); }

// Heapify logic
void heapify(std::vector<int> &v) {
  // start with first index as 0th index is already heapified
  for (size_t i = 1; i < v.size(); ++i) {
    // A right spot needs to be evaluated for index hence a temporary k
    int k = i;
    while (true) {
      // calculate parent index
      int parent_index = getParent(k);

      // swap element at lower index with element at higher index
      // if the element at lower index is smaller than element at higher index
      // else it has found its spot , you can break.
      // Continue this until it finds its right spot
      if (v[parent_index] < v[k]) {
        std::swap(v[parent_index], v[k]);
        k = parent_index;
      } else {
        break;
      }
    }
  }
}

// The trick here is that the a vector can be represented as a binary tree
// where element 1 and 2 are children of element 0 and element 3,4 are children
// and so on

void heap_sort(std::vector<int> &v) {
  // Heapify the vector so that largest element is at the top or root
  heapify(v);

  // sort the heap
}

int main() {
  // std::vector<int> v{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::vector<int> v{6, 5, 3, 1, 8, 7, 2, 4};
  heap_sort(v);
  print(v);

  char ch;
  std::cin >> ch;
  return 0;
}