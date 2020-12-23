#include <functional>
#include <iostream>
#include <string>

template <typename T>
struct sum {
  T operator()(const T& a, const T& b) {
    std::cout << "a+b= " << a + b << std::endl;
    return a + b;
  }
};

template <typename T>
struct subtract {
  T operator()(const T& a, const T& b) {
    std::cout << "a-b= " << a - b << std::endl;
    return a - b;
  }
};

double add_double(double x, double y) {
  std::cout << "x+y " << x + y;
  return x + y;
}

namespace pn {
class HelloWorld {
 public:
  void sayHello() const { std::cout << "Hello World" << std::endl; }
  void sayHelloTo(const std::string& name) {
    std::cout << "Hello  " << name << std::endl;
  }
};

// TO DO : Find a fix
// overloaded sayHello causes compilation error as compiler doesnt perform
// overloading
// https://stackoverflow.com/questions/30393285/stdfunction-fails-to-distinguish-overloaded-functions
// void sayHello(const std::string& name) const {
//   std::cout << "Ehllo " << name << std::endl;
// }

class OverloadedHello {
 public:
  void sayHello() const { std::cout << "Hello world" << std::endl; }
  void sayHello(const std::string&) const {
    std::cout << "Hello World" << std::endl;
  }
};
}  // namespace pn

// Note there is no getter function here
struct DataMemberAccessorDemo {
  int _x = 10;
};

int main() {
  // lambdas
  std::function<void()> hello_world;
  auto hello_world_lamda = []() { std::cout << "Hello World" << std::endl; };
  hello_world = hello_world_lamda;
  hello_world();

  // function objects
  std::function<int(int, int)> func;
  sum<int> do_sum;
  subtract<int> do_minus;
  for (int i = 0; i < 100; i++) {
    if ((rand() % 2 == 0))
      func = do_sum;
    else
      func = do_minus;

    func(rand(), rand());
  }

  // raw_functions
  std::function<double(double, double)> double_func = add_double;
  add_double(10.20, 10.20);

  // std::bind
  // Note when bound, no need to specify function arguments in std::function
  std::function<double()> bind_func =
      std::bind(subtract<double>(), 10.35, 10.35);
  std::cout << "bind : " << bind_func() << std::endl;

  pn::HelloWorld pn_hello_world;
  std::function<void(const pn::HelloWorld&)> member_func_callable =
      &pn::HelloWorld::sayHello;
  member_func_callable(pn_hello_world);

  // TO DO : Determine how to fix this with overloaded functions
  // pn::OverloadedHello overloaded_hello;
  // std::function<void()> overloaded_mem_fun =
  //     // static_cast<void (*)()>(&pn::OverloadedHello::sayHello());
  //     std::bind(&pn::OverloadedHello::sayHello, overloaded_hello);

  DataMemberAccessorDemo d;
  std::function<int(DataMemberAccessorDemo const&)> dma_func =
      &DataMemberAccessorDemo::_x;
  std::cout << "Data member accessor : " << dma_func(d) << std::endl;

  // function object example
  std::function<double(const double, const double)> func_obj =
      subtract<double>();
  std::cout << "Function object : " << func_obj(10.00, 10.00) << std::endl;

  // store a call to a member function and object
  std::function<void(const std::string&)> fun_placeholder_bind = std::bind(
      &pn::HelloWorld::sayHelloTo, pn_hello_world, std::placeholders::_1);
  fun_placeholder_bind("blah");

  // store a call to a member function and pointer
  std::function<void(const std::string&)> fun_placeholder_bind1 = std::bind(
      &pn::HelloWorld::sayHelloTo, &pn_hello_world, std::placeholders::_1);
  fun_placeholder_bind1("blahblah");

  return 0;

void print(int number) { std::cout << number << std::endl; }

struct Foo {
  Foo(int number) : number_(number) {}
  int number_;
  void print() const { std::cout << number_ << std::endl; }

  void printx(int x) const { std::cout << number_ + x << std::endl; }
};

struct PrintPredicate {
  PrintPredicate(int number) : number_(number) {}
  void operator()() { std::cout << number_ << std::endl; }
  int number_;
};

int main1() { 
  // 1. free functions
  std::function<void(int)> printFunc = print;
  printFunc(10);

  // 2. lambda functions
  std::function<void()> printFunc1 = []() { print(100); };
  printFunc1();

  // std::bind
  std::function<void()> printWithBindFunc = std::bind(print, 1000);
  printWithBindFunc();

  // Use of member function in std::function
  std::function<void(const Foo &)> fooMemberFunction = &Foo::print;
  const Foo foo(100);
  fooMemberFunction(foo);
  // implicit conversion to Foo
  fooMemberFunction(200);

  // Use of data member in std::function
  std::function<int(Foo const &)> fooMember = &Foo::number_;
  // implicit conversion to Foo
  std::cout << "Member of foo :: " << fooMember(foo);

  // store a call to member function and object
  using std::placeholders::_1;
  std::function<void(int)> fPlaceHolder = std::bind(&Foo::printx, foo, _1);
  fPlaceHolder(2);

  // store a call to member function and object pointer
  std::function<void(int)> fPlaceHolderObjectPointer =
      std::bind(&Foo::printx, &foo, _1);
  fPlaceHolderObjectPointer(5);

    // store a call to member function and object pointer
    std::function<void(int)> fPlaceHolderObjectPointer = std::bind(&Foo::printx, &foo, _1);
    fPlaceHolderObjectPointer(5);

    std::function<void()> printPredicateFunc = PrintPredicate(500);
    printPredicateFunc(); 

  return 0;
}
