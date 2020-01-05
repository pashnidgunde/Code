#include <iostream>
#include <thread>

void hello() { std::cout << "Hello" << std::endl; }

int main() {
  // hello();

  std::thread t1(hello); // t1 starts running child thread for function hello
  t1.join();             // main thread waits for t1 to finish.

  // t1.detach(); // main thread does not wait for t1 to finish. t1 becomes
  // daemon process

  // once detached you can not join the thread again.
  // so following will crash the program
  // t1.join();

  // so first check if  thread is joinable by using joinable

  if (t1.joinable())
    t1.join();

  // But there is no detachable API
  // if (t1.detachable())
  //    t1.detach();

  return 0;
}
