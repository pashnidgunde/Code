
#include <algorithm>
#include <iostream>
#include <vector>

// for swap 
#include "swap.hpp"

// Program to check if a single swap can sort the array
// Solution is to 
// 1. find the first left incorrect position
// 2. Find first right side incorrect position
// 3. swap elements 
// 4. Check if array is sorted , if not, return false;
// 5. restore elements by swaping previously swapped elements in step 3

// Time Complexity : O(N)

bool solution(std::vector<int> &A) {
  int left_index = -1;
  for (size_t i = 0; i < A.size() - 1; ++i) {
    if (A[i] > A[i + 1]) {
      left_index = i;
    }
  }

  if (left_index == -1)
    return true;

  int right_index = -1;

  for (size_t i = A.size() - 1; i > 0; i--) {
    if (A[i] < A[i - 1]) {
      right_index = A[i];
    }
  }

  pn::algo::swap(A[left_index], A[right_index]);
  bool is_sorted = std::is_sorted(A.begin(), A.end());
  pn::algo::swap(A[right_index], A[left_index]);
  return is_sorted;
}

int main() {
  std::vector<int> v{1, 5, 3, 3, 7};
  std::cout << solution(v);
  std::vector<int> v1{1, 3, 5, 3, 4};
  std::cout << solution(v1);
  std::vector<int> v2{1, 3, 5};
  std::cout << solution(v2);

  return 0;
}