#include<iostream>
#include <memory>
namespace pn
{
  namespace design_patterns
  {
    class Singleton {
    public:
      // 1. a static instance returned by reference
      static Singleton &Instance() {
        static Singleton S; 
        return S;
      }

    private:
      // 2. default private constructor and destructor
      Singleton() = default;
      Singleton(const Singleton&) = delete;
      Singleton& operator=(Singleton&) = delete;
      ~Singleton() = default;
    };
  }
}

int main()
{
  auto & it = pn::design_patterns::Singleton::Instance();
  auto & it1 = it; // you can copy ?
  auto& it2 = it;

  // std::unique_ptr<int> x;
  // std::unique_ptr<int>& y = x;
  // return 0;
}