#include <iostream>
#include <assert>

// This is quadratic solution.
int longest_subsequence(const std::vector<int>& v) { 
    auto length = 0;
    std::vector lengths(v.size(), 1);

    auto max = 1;

    for (auto i = 1; i < v.size(); ++i) 
    {
      for (auto j = 0; j < i; ++j) 
      {
          if (arr[i] > arr[j])
          {
            max = 
          }
      }
    }
    return std::max(length.begin(),length.end());
}




int main() { std::vector<int> v{10, 22, 9, 33, 21, 50, 41, 60};
  assert(5 = longest_subsequence(v));
}