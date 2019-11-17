#include <vector>
#include <list>
#include <map>
#include <unordered_map>

#include <iostream>

template <template <typename, typename...> class ContainerType,
          typename ValueType, typename... Args>
void print_container(const ContainerType<ValueType, Args...>& c) {
  for (const auto& v : c) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}

// Implement << for pairs: this is needed to print out mappings where range
// iteration goes over (key, value) pairs.
template <typename T, typename U>
std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& p) {
  out << "[" << p.first << ", " << p.second << "]";
  return out;
}

int main()
{
    std::vector<int> v {1,2,3,4,5};
    print_container(v);

    std::list<int> l {1,2,3,4,5};
    print_container(l);

    std::map<int,int> m {{1,2},{3,4}};
    print_container(m);

    std::unordered_map<int,int> u {{1,2},{3,4}};
    print_container(u);

}