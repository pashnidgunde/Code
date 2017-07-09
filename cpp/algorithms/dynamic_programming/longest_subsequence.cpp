#include "../std/max_element.hpp"
#include <cassert>
#include <iostream>
#include <vector>

// arr[] = {3, 10, 2, 1, 20}
// 3,10,2,1,20
// 1,1,1,1,1 (initial state)
// 1,2,1,1,1 (10)
// 1,2,1,1,1 (2)
// 1,2,1,1,1 (1)
// 1,2,1,1,3 (20)

//{50, 3, 10, 7, 40, 80}
// 1,1,1,1,1,1
// 1,1,1,1,1,1
// 1,1,2,1,1,1
// 1,1,2,2,1,1
// 1,1,2,2,3,1
// 1,1,2,2,3,4

// This is quadratic solution.
int longest_subsequence(const std::vector<int> &v) {
  // initialize lengths vector
  std::vector<int> lengths(v.size(), 1);

  // For each element in array, check if element is greater than its previous
  for (size_t i = 1; i < v.size(); ++i) {
    for (size_t j = 0; j < i; ++j) {
      // is current element greater than its previous ?
      if (v[i] > v[j]) {
        // is length of current element smaller than its previous + 1 ?
        if (lengths[j] + 1 > lengths[i]) {
          lengths[i] = lengths[j] + 1;
        }
      }
    }
  }
  return pn::algo::max_element(lengths.begin(), lengths.end());
  // return max;
}

int main() {
  std::vector<int> v{10, 22, 9, 33, 21, 50, 41, 60};
  assert(5 == longest_subsequence(v));
}