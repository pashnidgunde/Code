#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

int getIthPrime(int i) {
  auto prime_count = 0;

  auto next_number = 2;

  while (true) {
    auto prime = true;
    for (auto x = 2; x < next_number; ++x) {
      if (next_number % x == 0) {
        prime = false;
        break;
      }
    }

    if (prime && (++prime_count == i)) {
      break;
    }

    next_number = next_number + 1;
  }

  return next_number;
}

/*
int main() {
  int x = 859;
  for (int i = 1; i < x; i++) {
    std::cout << getIthPrime(i) << std::endl;
  }
}
*/

int main() {

  int n = 0, q = 0;

  std::cin >> n >> q;

  std::stack<int> A;

  int element = 0;
  std::stack<int> x;

  for (auto i = 1; i <= n; i++) {
    std::cin >> element;
    A.push(element);
  }

  std::vector<std::stack<int>> B;

  for (auto i = 0; i < q; i++) {
    auto ithPrime = getIthPrime(i + 1);
    std::stack<int> b_stack;
    std::stack<int> a_remaining;
    while (!A.empty()) {
      int element = A.top();
      if (element % ithPrime == 0) {
        b_stack.push(element);
      } else {
        a_remaining.push(element);
      }
      A.pop();
    }
    A = std::move(a_remaining);
    B.emplace_back(b_stack);
  }

  for (auto &s : B) {
    while (!s.empty()) {
      std::cout << s.top() << std::endl;
      s.pop();
    }
  }

  while (!A.empty()) {
    std::cout << A.top() << std::endl;
    A.pop();
  }

  return 0;
}
