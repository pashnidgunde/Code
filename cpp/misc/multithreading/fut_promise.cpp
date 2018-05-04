#include <iostream>
#include <string>
#include <thread>
#include <future>

void thread_func(std::promise<std::string>&& p)
{
    // set the value in the shared valulue
    p.set_value("Hello");
}


int main()
{
    // step 1: create promise
    std::promise<std::string> p;
    // step2 :: get future from promise
    std::future<std::string> f = p.get_future();

    // Move promise to another thread
    // promise can not be copied , only moved.
    // Can be only 
    std::thread t(thread_func,std::move(p));

    // Wait for the other thread to set the value. ( This is blocking call)
    std::string s = f.get();
    std::cout << s << std::endl;
    
    // This is to wait for thread to finish
    t.join();

}





