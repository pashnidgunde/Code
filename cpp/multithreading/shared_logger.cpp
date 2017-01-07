#include <thread>
#include <fstream>
#include <mutex>



std::mutex m;

/*
void print (const std::string& message , int i)
{
	std::lock_guard<std::mutex> guard(m);

	// Note that even if its scope locked, the cout object itself
	// is global and hence need a better version for locking this global
	// variable cout.
	// Check shared_logger.cpp
	std::cout << message << " " << i << std::endl;
}

*/

// Note that here s is locked completely
// Here, lock is binded with the resource.
class SharedLogger
{
public:

	SharedLogger()
	{
		s.open("File.txt");
	}

	void log(const std::string& message, int val)
	{
		std::lock_guard<std::mutex> guard(m);
		// Can't get id from a thread_id
		//ss << message << " " << std::this_thread::get_id() << " " << val;

		s << message << val << std::endl;
	}

	~SharedLogger()
	{
		s.close();
	}
private:
	std::ofstream s;
};

/* Synchronized fun */
void fun(SharedLogger& logger)
{
    for (int i=0;i< 1000;i++)
    {
        logger.log("From Fun " , i);
    }
}

int main()
{
	// One shared logger
	SharedLogger logger;

	// create few threads
    std::thread t1(fun, std::ref(logger));
    std::thread t2(fun, std::ref(logger));
    std::thread t3(fun, std::ref(logger));

    for (int i=0;i<1000;i++)
    {
        logger.log("From Main" , i);
    }

    t1.join();
    t2.join();
    t3.join();
}

