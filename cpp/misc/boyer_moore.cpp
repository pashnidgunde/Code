
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
template <typename Iter, typename ResultType>
bool majorityUsingCount(Iter begin, Iter end, ResultType& result) {
  size_t max_vote_size = std::distance(begin, end) / 2;
  for (auto iter = begin; iter != end; iter++) {
    size_t count = 1u;
    for (auto inner_iter = begin; inner_iter != end; inner_iter++) {
      if (*iter == *inner_iter) {
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
template <typename Iter, typename ResultType>
bool majorityUsingCountAfterSort(Iter begin, Iter end, ResultType& result) {
  size_t max_vote_size = std::distance(begin, end) / 2;
  // sort with O(n)
  // pn::algo::countingSort(begin, end, pn::functors::less<T>());
  std::sort(begin, end, pn::functors::less<ResultType>());
  auto iter = begin;
  auto prev_element = *iter;
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

// O(n)
template <typename Iter, typename ResultType>
bool majorityUsingUnorderedMap(Iter begin, Iter end, ResultType& result) {
  size_t max_vote_size = std::distance(begin, end) / 2;
  std::unordered_map<ResultType, size_t> hashMap;
  while (begin != end) {
    hashMap[*begin]++;
    std::advance(begin, 1);
  }

  for (const auto& elem : hashMap) {
    if (elem.second > max_vote_size) {
      result = elem.first;
      return true;
    }
  }

  return false;
}

// O(n) and constant space
// 1,2,3,4,5

template <typename Iter, typename ResultType>
bool majorityUsingBoyerMoore(Iter begin, Iter end, ResultType& result) {
  size_t max_vote_size = std::distance(begin, end) / 2;
  size_t count = 0u;
  Iter prev_element = begin;
  while (begin != end) {
    // when count reaches zero make sure to begin again
    // from current location
    if (count == 0) {
      prev_element = begin;
      count = 1;
    } else {
      // continue looking for next element
      (*prev_element == *begin) ? count++ : count--;
      if (count > max_vote_size) {
        result = *begin;
        return true;
      }
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
