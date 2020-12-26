#include <iostream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
std::string to_string_impl(T param) {
  std::stringstream ss;
  ss << param;
  return ss.str();
}

// specialization needs to be before variadic for compiler to pickup
std::vector<std::string> to_string() {
  return {};
}

template <typename Arg, typename... Args>
std::vector<std::string> to_string(const Arg& arg, const Args&... args) {
  std::vector<std::string> v;
  // to_string doesnt support const char*
  // v.emplace_back(std::to_string(arg));
  v.emplace_back(to_string_impl(arg));
  auto remainder = to_string(args...);
  v.insert(v.end(), remainder.begin(), remainder.end());
  return v;
}

// This will use intializiler list and argument pack expands
template <typename... Args>
std::vector<std::string> to_string_modified(const Args&... args) {
  return {to_string_impl(args)...};
}

int main() {
  auto print_func = [](auto& elems) {
    for (const auto& elem : elems) {
      std::cout << elem << '\n';
    }
  };
  auto elems = to_string(1, "hello", 2.0);
  print_func(elems);

  elems = to_string_modified(1, "ehll", 2);
  print_func(elems);

  return 0;
}