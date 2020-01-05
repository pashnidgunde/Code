#include <condition_variable>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <thread>

std::list<std::string> messages;
std::mutex m;
std::condition_variable v;

class Producer {
public:
  void operator()() {
    std::string msg("Message from producer :: ");
    while (1) {
      std::unique_lock<std::mutex> guard(m);
      messages.push_back(msg);
      v.notify_one();
    }
  }
};

class Consumer {
public:
  void operator()() {
    while (1) {
      std::unique_lock<std::mutex> guard(m);
      v.wait(guard);
      std::cout << "Recieved from Producer :: " << messages.front();
    }
  }
};

int main() {

  Producer p;
  std::thread producer_thread(p);

  Consumer c;
  std::thread consumer_thread(c);

  producer_thread.join();
  consumer_thread.join();
}