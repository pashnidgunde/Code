/*
 * unique_lock.cpp
 *
 *  Created on: 17-Aug-2016
 *      Author: rupa
 */


// Unique lock is heavier than lock guard
// For performence use lock_guard.


#include <mutex>
#include <thread>
#include <iostream>


std::mutex x;

void thread_function()
{
	std::unique_lock<std::mutex> lock(x);

	// You can defer the lock as below. Which means, you have the lock but its unlocked.
	//std::unique_lock<std::mutex> lock(x, std::defer_lock);

	std::cout << "Hello from thread. Unique locks can be copied.";

	// You can move the lock to unique_lock
	// Unique lock copy constructor is deleted
	std::unique_lock<std::mutex> lock1 = std::move(lock);

	lock1.lock();
		// you can perform other operations
		// Unlike lock_guard that applies gurard to whole function, you can lock specific section.
	lock1.unlock();

	// Some other operations not in critical section
	// Move code out of critical section if not critical


	// Now lock again and unlock.
	lock1.lock();
		// Another critical section
	lock1.unlock();

}


int main()
{

	std::cout << "Demonstration of unique_lock" << std::endl;

	std::thread t (thread_function);
	t.join();


}
