#include <thread>
#include <iostream>


void fun()
{
    for (int i = 0; i < 100000; i++)
    {
        std::cout << "From Thread : " << i << std::endl;
    }
}




int main()
{
    // This is fine
    std::thread t1 = std::thread (fun);

    for (int i=0;i<10000;i++)
    {
        std::cout << "From Main thread : " << i << std::endl;
    }
    t1.join();
    
}
