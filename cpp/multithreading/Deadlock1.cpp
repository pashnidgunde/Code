/*
 * Deadlock when one thread is wating for another to release resources.
 *
 *  This program will definately lock.
 *  Use gcore to create a dump of running process.
 *  Use gdb as
 *  gdb <binary_name> <core_file> to link attach core to gdb
 *  Before this, make sure to build binary as debug with
 *  g++ -g program name
 */

/* Things to avoid mutex :
 *
 * 1. Dont lock multiple locks at same time.
 * 2. Lock mutex in same order.
 * 3. Use std::lock to lock mutex.
 * 4. Avoid lock and unlock and ( instead use scoped_lock  or lock_guard )
 */


#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>

std::mutex m;
std::mutex m1;

void thread_function(std::string s)
{
	m.lock();
	for ( int i = 0 ; i< 10000;i++)
	{
		// do nothing , just increment
		i++;
	}
	m1.lock();
}

void thread1_function(std::string s)
{
	m1.lock();
	for ( int i = 0 ; i< 10000;i++) {
		i++;
	}
	
	std::cout << s;
	
	
	m.lock();

    std::reverse(s.begin(),s.end());
	
	std::cout << s;
}


int main()
{
    // standard way to create a thread
    
    std::thread thread_with_thread_function(thread_function, "hello");
    thread_with_thread_function.join();

	std::thread thread_with_thread1_function(thread1_function, "hows life");
    thread_with_thread1_function.join();
}

