#include <iostream>

#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
#include <iostream>
#include <ratio>

using namespace std::chrono;

class RateLimiter {
  int rate = INT_MAX;
  double allowance = rate;
  long per = INT_MAX;

  std::chrono::time_point<std::chrono::steady_clock> last_check =
      steady_clock::now();

public:
  RateLimiter(int rate, long per) {
    this->rate = rate;
    this->per = per;
    allowance = rate;
    std::chrono::time_point<std::chrono::steady_clock> last_check =
        steady_clock::now();
  }

  bool canAdd() {
    if (rate == INT_MAX)
      return true;

    auto current = std::chrono::steady_clock::now();
    /* std::chrono::duration<double, std::milli>*/ auto time_passed =
        current - last_check;
    last_check = current;

    allowance += (time_passed.count()) * (rate / per);
    std::cout << "allowance : " << allowance << std::endl;
    if (allowance > rate)
      allowance = rate;
    std::cout << "allowance : " << allowance << std::endl;
    if (allowance < 1)
      return false;
    else {
      allowance = allowance - 1.0;
      return true;
    }
    return false;
  }
};

int main() {
  RateLimiter rateer(3, 2);
  std::cout << rateer.canAdd() << std::endl;
  std::cout << rateer.canAdd() << std::endl;
  std::cout << rateer.canAdd() << std::endl;
  std::cout << rateer.canAdd() << std::endl;
  return 0;
}