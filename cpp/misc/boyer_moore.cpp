
// Algorithm to find the majority vote
// The majority vote is the vote where the vote is greater than n/2
// Approach 1 : Count occurance of each element by visiting all elements.
//              Complexity = O(n*n)
// Approach 2 : Sort and count occurances )(n log n)
// Approach 3 : O(n) , use of unordered_map to hash count of occurances
// Approach 4 : Boyer and Moore algorithm

#include <algorithm.h>  // for partitioning
#include <cassert>
#include <unordered_map>
#include <vector>
#include "algorithm.h"
#include "functors.h"
#include "utils.h"

// O(n*n)
template <typename T>
T majorityUsingCount(std::vector<T>& sequence) {
  for (auto iter = sequence.begin(); iter != sequence.end(); iter++) {
    size_t count = 0u;
    for (auto innerIter = sequence.begin(); innerIter != sequence.end();
         innerIter++) {
      if (*iter == *innerIter) {
        count++;
      }
      if (count > (sequence.size() / 2)) {
        return *iter;
      }
    }
  }

  // TODO :  How to return a default type
  return -1;
}

// O(n log n)
template <typename T>
T majorityUsingCountAfterSort(std::vector<T>& sequence) {
  if (sequence.empty()) return -1;
  pn::algo::countingSort(sequence.begin(), sequence.end(),
                         pn::functors::less<T>());
  auto iter = sequence.begin();
  auto prevElement = *iter;
  iter++;
  auto count = 0u;
  while (iter != sequence.end()) {
    if (*iter == prevElement) {
      count++;
      if (count > sequence.size() / 2) {
        return *iter;
      }
    } else {
      count = 0;
      prevElement = *iter;
    }
    iter++;
  }
  return -1;
}

// O(n)
template <typename T>
T majorityUsingUnorderedMap(std::vector<T>& sequence) {
  std::unordered_map<T, size_t> hashMap;
  for (const auto& elem : sequence) {
    hashMap[elem]++;
  }

  for (const auto& elem : hashMap) {
    if (elem.second > sequence.size() / 2) return elem.first;
  }

  return -1;
}

// O(n) and constant space
template <typename T>
T majorityUsingBoyerMoore(std::vector<T>& sequence) {
  int m = -1;
  size_t count = 0;
  for (const auto& elem : sequence) {
    if (0 == count) {
      m = elem;
      count = 1;
    } else {
      (m == elem) ? count++ : count--;
      if (count > sequence.size() / 2) return elem;
    }
  }

  return -1;
}

int main() {
  std::vector<int> v{1, 0, 0, 0, 0, 1, 2, 0, 0, 0, 1, 0};
  assert(majorityUsingCount(v) == 0);
  assert(majorityUsingCountAfterSort(v) == 0);
  assert(majorityUsingUnorderedMap(v) == 0);
  assert(majorityUsingBoyerMoore(v) == 0);

  std::vector<int> v1{1, 2, 3, 4, 5};
  assert(majorityUsingCount(v1) == -1);
  assert(majorityUsingCountAfterSort(v1) == -1);
  assert(majorityUsingUnorderedMap(v1) == -1);
  assert(majorityUsingBoyerMoore(v1) == -1);

  return 0;
}
