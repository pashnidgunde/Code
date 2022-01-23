#include <iostream>
#include <vector>

long long gcd_faster(long long a, long long b) {

  if (a < b)
    std::swap(a, b);

  if (a % b == 0)
    return b;

  return gcd_faster(b, a % b);
}

long long gcd_faster(std::vector<long long> &numbers) {
  auto gcd = numbers[0];
  for (size_t i = 1; i < numbers.size(); ++i) {
    gcd = gcd_faster(gcd, numbers[i]);
  }

  return gcd;
}

int main(int, char *argv[]) {
  auto n = atoi(argv[1]);
  std::vector<long long> numbers;
  for (auto i = 0; i < n; ++i) {
    numbers.push_back(atoll(argv[i + 2]));
  }

  std::cout << gcd_faster(numbers);
}