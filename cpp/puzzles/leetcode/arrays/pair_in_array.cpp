// http://www.techiedelight.com/find-pair-with-given-sum-array/

/*

For example,

Input:
arr = [8, 7, 2, 5, 3, 1]
sum = 10

Output:
Pair found at index 0 and 2	(8 + 2)
OR
Pair found at index 1 and 5 (7 + 3)

*/

// 1. Approach 1 : Look at number 1 , and check for the other number iterating
// the list , complexity O(n*n)
// 2. Approach 2 : Sort numbers and start with first and last to check if they
// total to sum , increment begin and decrement last O(N) * O(log N)
// 3. Approach 3 : Look at the current element from the vector, if sum - element
// value exists in map, take index of that element, add element to map

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <utility>
#include <vector>

struct PairsForSum {
  static std::vector<std::pair<int, int>>
  getPairsForSum_Approach1(std::vector<int> &arr, int sum) {
    std::vector<std::pair<int, int>> result;
    size_t size = arr.size();
    for (int i = 0; i < size; i++) {
      for (int j = i + 1; j < size; j++) {
        if (arr[i] + arr[j] == sum)
          result.emplace_back(std::make_pair(arr[i], arr[j]));
      }
    }

    return result;
  }

  static std::vector<std::pair<int, int>>
  getPairsForSum_Approach2(std::vector<int> &arr, int sum) {
    std::vector<std::pair<int, int>> result;
    size_t size = arr.size();

    // Sort in O(N log N)
    std::sort(arr.begin(), arr.end());

    int begin = 0, end = size - 1;

    while (begin < end) {
      if ((arr[begin] + arr[end]) == sum) {
        result.emplace_back(std::make_pair(arr[begin], arr[end]));
        begin++;
        end--;
        continue;
      }

      ((arr[begin] + arr[end]) < sum) ? begin++ : end--;
    }

    return result;
  }

  static std::vector<std::pair<int, int>>
  getPairsForSum_Approach3(std::vector<int> &arr, int sum) {
    std::vector<std::pair<int, int>> result;
    std::unordered_map<int, int> m;

    for (auto i = 0; i < arr.size(); i++) {
      if (m.find(sum - arr[i]) != m.end()) {
        result.emplace_back(std::make_pair(arr[i], m[sum - arr[i]]));
      }
      m[arr[i]] = i;
    }

    return result;
  }
};

int main() {
  std::vector<int> arr{8, 7, 2, 5, 3, 1};
  std::vector<std::pair<int, int>> pairs1 =
      PairsForSum::getPairsForSum_Approach1(arr, 10);
  std::vector<std::pair<int, int>> pairs2 =
      PairsForSum::getPairsForSum_Approach2(arr, 10);
  std::vector<std::pair<int, int>> pairs3 =
      PairsForSum::getPairsForSum_Approach3(arr, 10);

  std::cout << pairs1.size() << pairs2.size() << pairs3.size();
  assert((pairs1.size() == pairs2.size()) && (pairs2.size() == pairs3.size()));

  getchar();
  return 0;
}
