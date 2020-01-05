#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long)a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long)a * b;
}

// For any two positive integers 𝑎 and 𝑏, LCM(𝑎, 𝑏)· GCD(𝑎, 𝑏) = 𝑎 · 𝑏.
// Prove this property and implement an algorithm for computing the least common
// multiple using your solution
// for the greatest common divisor
long gcd(int a, int b) {
  if (b > a)
    std::swap(a, b);

  if (a % b == 0)
    return b;

  return gcd(b, a % b);
}

long long lcm_faster(long long a, long long b) {
  return ((long long)(a * b) / gcd(a, b));
}

int main() {
  long long a, b;
  std::cin >> a >> b;
  // std::cout << lcm_naive(a, b) << std::endl;
  std::cout << lcm_faster(a, b) << std::endl;
  return 0;
}
