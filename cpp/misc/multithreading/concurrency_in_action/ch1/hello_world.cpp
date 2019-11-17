#include <iostream>
#include <thread>

// thread function
void helloFunction
() { std::cout << "Hello from thread" << std::endl; }

// thread functor
class HelloFunctor {
    public:
      void operator()() {
        std::cout << "Hello World from functor." << std::endl;
      }
};

int main() { 
    std::thread functThread(helloFunction);
    functThread.join();

    HelloFunctor functor;
    std::thread functorThread(functor);
    functorThread.join();

    return 0;
}
