#include <iostream>
#include <vector>

void print(const std::vector<int> &v) {
  for (const auto &e : v)
    std::cout << e << " ";
  std::cout << std::endl;
}

// In selection sort, you start with empty list
// Find miniumn of the list and swap elements if you find current element larger
// than the min element.
// Time complexity : O(n*n)
// The implementation below uses inplace substitution i.e. no seperate list is
// created but the same vector is manipulated to sort it
void selection_sort(std::vector<int> &v) {

  // Visit all elements O(n)
  for (size_t i = 0; i < v.size(); i++) {

    // Assume current element to be the minimum from the list
    auto min = v[i];
    // This index is required to swap elements
    auto min_index = i + 1;

    // Find minimum from rest of the elements O(n)
    for (size_t j = i + 1; j < v.size(); j++) {
      if (min > v[j]) {
        min = v[j];
        min_index = j;
      }
    }

    // swap element with minimum value with current value .. This is inplace
    // replacement.
    if (min < v[i]) {
      std::swap(v[i], v[min_index]);
    }
  }
}

int main() {
  std::vector<int> v{10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  selection_sort(v);
  print(v);

  char ch;
  std::cin >> ch;
  return 0;
}