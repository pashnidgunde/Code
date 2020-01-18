#include <iostream>
#include <regex>

std::string matchandReplace(const std::regex& re, const std::string& match_str,
                            const std::string& replace) {
  //   if (regex_match(match_str, re)) {
  //     std::cout << "Matched: " << match_str << std::endl;
  //     return true;
  //   }
  return std::regex_replace(match_str, re, replace);
}

int main() {
  std::regex re_onechar("[A-Z]");
  std::string onechar = "9";
  std::cout << matchandReplace(re_onechar, onechar, "X") << std::endl;

  return 0;
}