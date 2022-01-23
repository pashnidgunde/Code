#include <iostream>
#include <sstream>
#include <initializer_list>
#include <vector>

template <typename T> std::string to_string(T args) {
  std::stringstream s;
  s << args;
  return s.str();
}

void toString() { return; }

template <typename T, typename... Params>
void toString(const T &param, const Params... params) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  std::cout << param;
  toString(params...);
}

template <typename T, typename... Rest>
std::string to_string(T first, const Rest &... rest) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  std::stringstream s;
  s << first;
  s << to_string(rest...);
  return s.str();
}

template<typename... Args>
// TO DO : what's wrong with initializer list ?
//std::initializer_list<std::string> to_string_initializer_list(const Args&... args)
std::vector<std::string> to_string_initializer_list(const Args&... args)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  //return {to_string(args)...};
  // OR 
  // Generic lambda
  auto to_string_lambda = [](const auto& arg) {  std::stringstream s; s << arg; return s.str();};
  return {to_string_lambda(args)...};
}

int main() {
  std::cout << to_string(10) << std::endl;
  toString(1, 2, 2, 3, 4, 5, 5, 6, 6, 6, 6, 6, 6, 6);
  std::cout << to_string(1, "Hello", "5.5"
                                     "Done Done Done");

  auto strings = to_string_initializer_list(9,8,7,6,5,4);
  for (const auto& s : strings) { std::cout << s << "," ;}

}