#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

// Naive solution
int MaxPairwiseProduct(const vector<int> &numbers) {
  int result = 0;
  int n = numbers.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (numbers[i] * numbers[j] > result) {
        result = numbers[i] * numbers[j];
      }
    }
  }
  return result;
}

// Fast solution
long long MaxPairwiseProductFast(const std::vector<int> &numbers) {
  auto max_index1 = 0;
  auto max_index2 = 1;

  auto size = numbers.size();

  for (auto i = 2; i < size; ++i) {
    if (numbers[i] >= numbers[max_index1]) {
      if (numbers[max_index1] > numbers[max_index2])
        max_index2 = i;
      else
        max_index1 = i;

      continue;
    }

    if (numbers[i] >= numbers[max_index2]) {
      if (numbers[max_index2] > numbers[max_index1])
        max_index1 = i;
      else
        max_index2 = i;
    }
  }

  // In order to calculate a long long , treat atleast one number as long long
  // by typecasting.
  return ((long long)(numbers[max_index1]) * numbers[max_index2]);
}

int main() {
  int n;
  cin >> n;
  vector<int> numbers(n);
  for (int i = 0; i < n; ++i) {
    cin >> numbers[i];
  }

  auto result = MaxPairwiseProductFast(numbers);
  cout << result << "\n";
  return 0;
}
