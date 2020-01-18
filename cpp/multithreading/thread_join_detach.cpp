#include <iostream>
#include <thread>

void thread_function() {
  std::cout << "Thread function which is not joined or detached. Hence it will "
               "crash. You need to make sure that"
               "thread either joins or detaches. In case of exceptions, you "
               "should make sure that its joined or"
               "detached. Else program will crash. So this never gets printed";
}

int main() {

  std::thread t1(thread_function);
  // No detach
  // No join

  // program terminates. we need to know what we want to do with this thread.
}
