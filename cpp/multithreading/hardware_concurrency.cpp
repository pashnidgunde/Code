#include <iostream>
#include <thread>

void fun() {
  // print child threads id
  std::cout << "Child thread id " << std::this_thread::get_id() << std::endl;
}

int main() {
  // This is fine
  std::thread t1 = std::thread(fun);

  // print main thread's id
  std::cout << "Hardware Concurrancy, Gives number of cores. This can decide "
               "how many threads we can run  : "
            << std::thread::hardware_concurrency() << std::endl;

  t1.join();
}
