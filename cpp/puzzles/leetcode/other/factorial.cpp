#include <cassert>
#include <iostream>
#include <stdlib.h>

// Recursive implementation
long long factorial_recursive(int n) {
  if (n == 1)
    return 1;

  return (long long)(n * factorial_recursive((long long)n - 1));
}

// Efficient Algorithm
long long factorial_nonrecursive(int n) {
  long long factorial = n;
  while (n > 1) {
    factorial = (long long)factorial * --n;
  }

  return factorial;
}

int main(int, char *argv[]) {

  int n = atoi(argv[1]);

  std::cout << factorial_recursive(n) << std::endl;
  std::cout << factorial_nonrecursive(n) << std::endl;
  return 0;
}