#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

// Naive solution
long long MaxPairwiseProduct(const vector<int> &numbers) {
  long long result = 0;
  int n = numbers.size();
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      auto temp = (long long)(numbers[i]) * numbers[j];
      if (temp > result) {
        result = temp;
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

/*
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
*/

// This is the implementation of the stres test
int main() {
  while (true) {
    auto n = rand() % 10 + 2;
    std::vector<int> numbers;
    for (auto i = 0; i < n; i++) {
      numbers.emplace_back(rand());
    }

    long long number1 = MaxPairwiseProductFast(numbers);
    long long number2 = MaxPairwiseProduct(numbers);

    if (number1 != number2) {
      std::cout << "Failed" << std::endl;
      std::cout << "N :: " << n << std::endl;
      std::cout << "Numbers ::" << std::endl;

      for (const auto &number : numbers) {
        std::cout << number << " " << std::endl;
      }

      std::cout << "Number 1 :: " << number1 << std::endl;
      std::cout << "Number 2 :: " << number2 << std::endl;

      break;
    } else {
      std::cout << "PASS" << std::endl;
    }
  }

  return 0;
}