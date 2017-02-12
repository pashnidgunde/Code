#include <iostream>

class Fred {};

class FredList {
  Fred x[20];

public:
  const Fred &operator[](int i) const { return x[i]; }
  Fred &operator[](int i) { return x[i]; }
};

int main() {

  // In this case , the mutable ( non const version gets called)
  FredList list;
  Fred f;
  list[0] = f;
  f = list[10];

  // In this case the const version is used and hence it it wont compile
  const FredList const_list;
  // const_list[0] = f;
  f = const_list[10];
}