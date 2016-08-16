#include<iostream>
#include<thread>
#include <mutex>

std::mutex m;

void thread_function()
{
	m.lock();

}


class Functor
{
    public:
        void operator ()()
        {
            std::cout << "This is functor " << std::endl;
        }

};

int main()
{

    // standard way to create a thread
    std::thread thread_with_thread_function(thread_function);
    thread_with_thread_function.join();


    // thread with functor
    Functor f;
    std::thread thread_with_functor(f);
    thread_with_functor.join();
   
}

