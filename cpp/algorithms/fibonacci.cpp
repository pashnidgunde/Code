#include <cassert>
#include <iostream>

// Recursive implementation
int fibonacci_recursive(int n) {
  if (n < 2)
    return n;
  else
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

// Efficient Algorithm
long long fibonacci_nonrecursive(int n) {
  long long prev = 0;
  long long curr = 1;
  long long fib = 0;

  if (n < 2)
    return n;

  int i = 2;
  while (i <= n) {
    fib = prev + curr;
    prev = curr;
    curr = fib;
    i++;
  }
  return fib;
}

int main() {
  std::cout << fibonacci_recursive(15) << std::endl;
  std::cout << fibonacci_nonrecursive(15) << std::endl;
  return 0;
}