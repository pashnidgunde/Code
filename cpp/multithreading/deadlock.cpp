/*
 * Deadlock when you lock same mutex twice.
 *
 *
 */


#include <iostream>
#include <thread>
#include <mutex>

std::mutex m;

void thread_function()
{
	m.lock();
	//Some code
	// Lock same mutex again

	// Never lock same mutex again.
	//
	m.lock();
}


int main()
{

    // standard way to create a thread
    std::thread thread_with_thread_function(thread_function);
    thread_with_thread_function.join();
}

