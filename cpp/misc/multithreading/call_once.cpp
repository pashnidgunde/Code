/*
 * call_once.cpp
 *
 *  Created on: 18-Aug-2016
 *      Author: rupa
 */

/* This is demonstration of call_once */

#include <mutex>
#include <thread>

class FileHandler {
  // Use this if you want to get something done once and in all threads
  // Can try for singleton pattern later
  std::once_flag f;
  std::mutex m;

  void open_file() { ofstream f("./data.txt") }

  void write_to_file(char *data) {
    // This will be called only once from all threads
    std::call_once(f, open_file);

    std::unique_lock<std::mutex> lock(m, std::defer_lock);

    std::cout << "I am doing something which does not need locks";

    std::cout << "Now my critical section begin";

    std::lock(lock);
  }
};

int main() { std::cout << "This is not funny "; }
