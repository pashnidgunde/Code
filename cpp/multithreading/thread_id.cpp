#include <thread>
#include <iostream>


void fun()
{
    // print child threads id
    std::cout << "Child thread id " << std::this_thread::get_id() << std::endl;
}


int main()
{
    // This is fine
    std::thread t1 = std::thread (fun);
    
    // print main thread's id
    std::cout << "Main thread id : " << std::this_thread::get_id() << std::endl;
    std::cout << "Child threads id : " << t1.get_id() << std::endl;

    t1.join();
}
