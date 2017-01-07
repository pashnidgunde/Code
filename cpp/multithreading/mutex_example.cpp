#include <thread>
#include <iostream>


void fun()
{
    for (int i = 0; i < 1000; i++)
    {
        std::cout << "From Thread : " << i << std::endl;
    }
}




int main()
{
    // This is fine
    std::thread t1 = std::thread (fun);

    for (int i=0;i<1000;i++)
    {
        std::cout << "From Main thread : " << i << std::endl;
    }
    t1.join();
    
}
