#include <iostream>
#include <thread>

void thread_function() {
  std::cout << "Some stupid thread function" << std::endl;
}

int main() {
  // thread starts running
  std::threadi t1(thread_function);

  // Note that join after for loop which has try catch
  // But if we get exception, we need to join before throw else program will
  // crash.
  // You could use RAII that joins in destructor

  try {
    for (int i = 0; i < 100; i++) {
      std::cout << "From Main :: " << i << std::endl;
    }
  } catch (...) {
    t1.join();
    throw;
  }

  // we are joining here.
  t1.join();
}
