// https://www.hackerrank.com/contests/university-codesprint-2/challenges/separate-the-numbers

#include <iostream>
#include <sstream>
#include <string>

std::string to_string(int number) {
  std::stringstream s;
  s << number;
  return s.str();
}

int main() {

  auto number_of_strings = 0;
  std::cin >> number_of_strings;

  for (auto i = 0; i < number_of_strings; i++) {

    std::cin >> str;

    auto offset = 1;
    auto in_sequence = false;
    while (d < str.size() / 2) {
      auto index = 0;
      auto number = atoi(str.substr(index, offset).c_str());

      while (1) {
        auto next_number = number + 1;
        auto next_number_str = to_string(next_number);
        auto next_number_length = next_number_str.size();

        if ((index + offset + next_number_length) > str.size()) {
          break;
        } else {
          std::string next_substr =
              str.substr(index + offset, next_number_length);
          if (next_substr == next_number_str) {
            in_sequence = true;
            number = next_number;
            index = index + next_substr.size();
          } else {
            in_sequence = false;
            break;
          }
        }
      }

      if (false == in_sequence) {
        d += 1;
      } else {
        in_sequence = true;
        break;
      }
    }

    if (in_sequence) {
      std::cout << "YES";
    }
  }
}
