#include <thread>
#include <iostream>
#include <mutex>

// Main thread and fun try to use resource cout causing weird output.
// So, lets synchronize using mutex.
// Uncomment below to see how it matters to use mutex
/*
void fun()
{
    for (int i = 0; i < 100; i++)
    {
        std::cout << "From Thread : " << i << std::endl;
    }
}

int main()
{
    // This is fine
    std::thread t1 = std::thread (fun);

    for (int i=0;i<100;i++)
    {
        std::cout << "From Main thread : " << i << std::endl;
    }
    t1.join();
}    

*/


std::mutex m;

void print(const std::string& message, int i)
{
    // you can use scoped_lock too
    m.lock();
    std::cout << message << " " << i << std::endl;
    m.unlock();
}

/* Synchronized fun */
void fun()
{
    for (int i=0;i< 100;i++)
    {
        print ("From Fun " , i);
    }

}

int main()
{
    // This is fine
    std::thread t1 = std::thread (fun);

    for (int i=0;i<100;i++)
    {
        print("From Main" , i);
    }


    t1.join();
}    

