#include <thread>
#include <iostream>
#include <mutex>


std::mutex m;

/*
This function is not correct because the if t
void print(const std::string& message, int i)
{
    // you can use scoped_lock too
    m.lock();
    std::cout << message << " " << i << std::endl;
    // some  code here can throw exceptions making unlock never called.
    // Need to unlock in all cases , use scoped_lock or lock_guard
    m.unlock();
}
*/

void print (const std::string& message , int i)
{
	std::lock_guard<std::mutex> guard(m);

	// Note that even if its scope locked, the cout object itself
	// is global and hence need a better version for locking this global
	// variable cout.
	// Check shared_logger.cpp
	std::cout << message << " " << i << std::endl;
}

/* Synchronized fun */
void fun()
{
    for (int i=0;i< 100;i++)
    {
        print("From Fun " , i);
    }

}

int main()
{
    // This is fine
    std::thread t1(fun);

    for (int i=0;i<100;i++)
    {
        print("From Main" , i);
    }


    t1.join();
}    

