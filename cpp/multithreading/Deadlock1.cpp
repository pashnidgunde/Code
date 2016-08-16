/*
 * Deadlock when one thread is wating for another to release resources.
 *
 *
 */


#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;
std::mutex m1;

void thread_function(std::string s)
{
	m.lock();
	//Some code
	// Lock same mutex again
	
	//
	m1.lock();
}

void thread1_function(std::string s)
{
	m1.lock();
	// Some code
	//
	
	std::cout << s;
	
	
	m.lock();
	
	std::cout << s.reverse();
}


int main()
{

    // standard way to create a thread
    
    std::thread thread_with_thread_function(thread_function);
    
    
    thread_with_thread_function.join();


	std::thread thread_with_thread1_function(thread1_function);
    thread_with_thread1_function.join();
}

