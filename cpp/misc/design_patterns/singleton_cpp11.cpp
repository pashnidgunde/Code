#include <cassert>
#include <iostream>
#include <mutex>

class Singleton {
private:
  Singleton() = default;
  ~Singleton() = default;

  static Singleton *instance;

  static void createInstance() { instance = new Singleton(); }

public:
  static Singleton *getInstance() {
    std::call_once(flag, &Singleton::createInstance);
    return instance;
  }

  static std::once_flag flag;
};

Singleton *Singleton::instance = nullptr;
std::once_flag Singleton::flag;

int main() {
  Singleton *p = Singleton::getInstance();
  Singleton *p1 = Singleton::getInstance();

  assert(p == p1);
}