#include <thread>


void fun()
{
}


int main()
{
    // This is fine
    std::thread t1 = std::thread (fun);

    // This will not compile , because 
    // thread(thread&) = delete;
    std::thread t2 = t1;
    t1.join();
}
