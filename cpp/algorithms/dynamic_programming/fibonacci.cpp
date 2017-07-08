#include <iostream>
#include <unordered_map>
#include <cassert>

// Dynamic programing approach to solve fibonacci problem

// This technique is memoization technique where you memoize the results previously computed
// This works in top down approach
// Sometimes avoids computation to subproblems e.g. longest common subsequence
// Sometimes more obvious to write e.g. matrix chain multiplication
std::unordered_map<int, int> dictionary;
int fibonacci_memoization(int N)
{
  // is already computed ? use memoize
  if (dictionary.find(N) != dictionary.end()) return dictionary[N];
  // Base condition
  int fib = 0;
  if (N <= 2) 
  {
      fib = 1;
  }
  else 
  {
    // recursion
    fib = fibonacci_memoization(N-1) + fibonacci_memoization(N-2);
  }

  // memoization
  dictionary.insert({N,fib});
  return fib;
}


// This technique is tabulatino approach
// Works in bottom up approach
// Avoids multiple lookups

int fibonacci_tabulation(int N) { 
  // create a dictionary
  std::unordered_map<int, int> dictionary;
  // Insert first two elements as we know the base cases
  dictionary.insert({0, 0});
  dictionary.insert({1, 1});

  // Compute next values and store computed value once computed.
  // Here we are referring to previous values computed already
  // Therefore we are using tabulation technique to retrieve values
  // There is no recursion.
  for (int i = 2; i <= N; i++) 
  {
    int fib = dictionary[i - 1] + dictionary[i - 2];
    dictionary[i] = fib;
  }

  return dictionary[N];
}

// Note : In previous tabulation method, we have maitained a dictionary
// But ideally what we need is two old values to compute next value
// Therefore, we remove dictionary and use two auto variables.

int fibonacci_tabulation_advanced(int N) { 
  // create a dictionary
  if (N == 0) return 0;
  if (N == 1) return 1;

  int i = 0, j = 1 , fib = 0;
  for (int k = 2; k <= N; k++) {
    fib = i + j;
    i = j;
    j = fib;
  }

  return fib;
}

int main() {
  assert(2 == fibonacci_memoization(3));
  assert(2 == fibonacci_tabulation(3));
  assert(2 == fibonacci_tabulation_advanced(3));
}
