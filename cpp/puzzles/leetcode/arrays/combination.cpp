#include <cmath>
#include <iostream>
#include <set>
#include <string>
using namespace std;

int combination(const std::string &str) {
  auto size = str.size();
  auto count = 0;
  for (auto i = 0; i < size; i++) {
    for (auto offset = 1; offset <= size - i; offset++) {
      auto s = atol(str.substr(i, offset).c_str());
      std::cout << s << std::endl;
      if ((s % 8 == 0)) {
        count++;
      }
    }
  }

  return count;
}

int main(int argc, char **argv) {
  string str = "9688";
  auto count = combination(str);
  std::cout << count % int(pow(10, 9) + 7);

  return 0;
}
