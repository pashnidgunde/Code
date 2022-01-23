
// Algorithm to find the majority vote
// The majority vote is the vote where the vote is greater than n/2
// Approach 1 : Count occurance of each element by visiting all elements.
//              Complexity = O(n*n)
// Approach 2 : Sort and count occurances )(n log n)
// Approach 3 : O(n) , use of unordered_map to hash count of occurances
// Approach 4 : Boyer and Moore algorithm

#include "algorithm.h"
#include "functors.h"
#include "utils.h"
#include <algorithm.h> // for partitioning
#include <cassert>
#include <unordered_map>
#include <vector>

// O(n*n)
template <typename T> T majorityUsingCount(std::vector<T> &sequence) {
  for (auto iter = sequence.begin(); iter != sequence.end(); iter++) {
    size_t count = 0u;
    for (auto innerIter = sequence.begin(); innerIter != sequence.end();
         innerIter++) {
      if (*iter == *innerIter) {

        count++;
      }
      if (count > max_vote_size) {
        result = *iter;
        return true;
      }
    }
  }
  return false;
}

// O(n log n)

template <typename T> T majorityUsingCountAfterSort(std::vector<T> &sequence) {
  if (sequence.empty())
    return -1;
  pn::algo::countingSort(sequence.begin(), sequence.end(),
                         pn::functors::less<T>());
  auto iter = sequence.begin();
  auto prevElement = *iter;

  iter++;
  auto count = 1u;
  while (iter != end) {
    if (*iter == prev_element) {
      count++;
      if (count > max_vote_size) {
        result = *iter;
        return true;
      }
    } else {
      count = 1;
      prev_element = *iter;
    }
    std::advance(iter, 1);
  }
  return false;
}


template <typename T> T majorityUsingUnorderedMap(std::vector<T> &sequence) {
  std::unordered_map<T, size_t> hashMap;
  for (const auto &elem : sequence) {
    hashMap[elem]++;
  }

  for (const auto &elem : hashMap) {
    if (elem.second > sequence.size() / 2)
      return elem.first;

  }

  return false;
}

// O(n) and constant space
template <typename T> T majorityUsingBoyerMoore(std::vector<T> &sequence) {
  int prevElement = -1;
  size_t count = 0;
  for (const auto &elem : sequence) {
    if (0 == count) {
      prevElement = elem;
      count = 1;
    } else {
      (prevElement == elem) ? count++ : count--;
      if (count > sequence.size() / 2)
        return elem;
    }

    std::advance(begin, 1);
  }
  return false;
}

int main() {
  std::vector<int> v{1, 0, 0, 0, 0, 1, 2, 0, 0, 0, 1, 0};
  int result;
  assert(majorityUsingCount(std::begin(v), std::end(v), result) == true);
  assert(result == 0);

  assert(majorityUsingCountAfterSort(std::begin(v), std::end(v), result) ==
         true);
  assert(result == 0);

  assert(majorityUsingUnorderedMap(std::begin(v), std::end(v), result) == true);
  assert(result == 0);

  assert(majorityUsingBoyerMoore(std::begin(v), std::end(v), result) == true);
  assert(result == 0);

  std::vector<int> v1{1, 2, 3, 4, 5};
  assert(majorityUsingCount(std::begin(v1), std::end(v1), result) == false);
  assert(majorityUsingCountAfterSort(std::begin(v1), std::end(v1), result) ==
         false);
  assert(majorityUsingUnorderedMap(std::begin(v1), std::end(v1), result) ==
         false);
  assert(majorityUsingBoyerMoore(std::begin(v1), std::end(v1), result) ==
         false);

  std::vector<int> v2{1, 0, 1, 0, 1};
  assert(majorityUsingBoyerMoore(std::begin(v2), std::end(v2), result) ==
         false);
  assert(result == 1);

  return 0;
}
