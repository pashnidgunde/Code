#include <future>
#include <iostream>
#include <thread>

// Please refer to future and promise example from fut_promise.cpp
// This will demonstrate usage of async, future and promise
// Example of thread communication using async , future and promise

std::string thread_function() {
  return "Hello From thread";
  // you can throw exceptions as well
  // throw std::exception("Not cool");
}

int main() {
  // async returns a future
  auto fut = std::async(thread_function);

  // You should cover get with try and catch because
  // the task might throw an exception
  try {
    std::cout << fut.get();
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
