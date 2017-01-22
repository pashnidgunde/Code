/*
 * producer_consumer.cpp
 *
 *  Created on: 19-Jan-2017
 *      Author: rupa
 */

#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <thread>

int shared_list[10];
std::mutex m;
std::condition_variable c;

class Producer {
 public:
  void operator()() { produce(); }

 private:
  void produce() {
    while (1) {
      std::unique_lock<std::mutex>(m);
      int random = rand();
      std::cout << "Pushing :: " << random << std::endl;
      shared_list[(rand() % 10)] = rand();
      c.notify_one();
    }
  }
};

class Consumer {
 public:
  void operator()() { consume(); }

 private:
  void consume() {
    while (1) {
      if (shared_list.size()) {
        std::unique_lock<std::mutex>(m);
        c.wait(m);
        std::cout << " Popping :: " << shared_list.front() << std::endl;
        shared_list.pop_front();
      }
    }
  }
};

int main() {
  Producer p;
  Consumer c;

  std::thread producer_thread(p);
  std::thread consumer_thread(c);

  producer_thread.join();
  consumer_thread.join();
}
