/*
 * is_sorted.cpp
 *
 *  Created on: 15-Jan-2017
 *      Author: rupa
 */

#include <iostream>
#include <vector>

std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
std::vector<int> v1{8, 1, 2, 3, 4, 5, 6, 7};

bool is_sorted(std::vector<int>& v) {
  bool sorted = true;
  for (int i = 0; i < v.size(); i++) {
    for (int j = i + 1; j < v.size(); j++) {
      if (v[i] > v[j]) {
        sorted = false;
        break;
      }
    }
  }
  return sorted;
}

int main() {
  std::cout << is_sorted(v);
  std::cout << is_sorted(v1);
}
