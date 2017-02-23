// https://www.hackerrank.com/contests/university-codesprint-2/challenges/separate-the-numbers

#include <iostream>
#include <sstream>
#include <string>

int number_of_digits(int number) {
  std::stringstream s;
  s << number;
  return s.str().size();
}

int main() {

  auto number_of_strings = 0;
  std::cin >> number_of_strings;

  for (auto i = 0; i < number_of_strings; i++) {

    std::cin >> str;

    auto in_sequence = false;

    for (auto offset = 1; (offset < str.size() / 2 || in_sequence != true);
         ++offset) {
      auto index = 0;
      auto number = atoi(str.substr(index, offset).c_str());
      auto number_to_print = number;
      auto next_number_length = 0;

      while ((index + offset + next_number_length) < str.size()) {
        auto next_number = number + 1;
        auto next_number_length = number_of_digits(next_number);
        auto next_number_from_str =
            atoi(str.substr(index + offset, next_number_length).c_str());

        if (next_number_from_str != next_number) {
          in_sequence = false;
          std::cout << "NO" << std::endl;
          break;
        }

        in_sequence = true;
        number = next_number;
        index = index + next_number_length;
      }

      if (in_sequence) {
        std::cout << "YES" << number_to_print << std::endl;
        break;
      }
    }
  }
}