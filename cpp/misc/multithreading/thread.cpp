#include <thread>
#include <string>
#include <iostream>


void fun()
{
     // print child threads id
    std::cout << "Child thread id " << std::this_thread::get_id() << std::endl;
}

// This accepts integer
void thread_function( int argument)
{
    // stupid thread function
    std::cout << "Argument passed : " << argument << std::endl;
}

//definition of thread
// std::thread(function_name , Args ... )

class Functor
{
    public:
        // This accepts string

// **********************
//  Note that even if you have reference to the string, 
//  parameter are always passed by value to the thread function.

// **********************

        void operator ()(std::string& value)
        {
            std::cout << "This is functor printing " << value << std::endl;
            // overide value with new value
            value = "This is to demo that thread params are always passed by value";
        }

};


int main()
{
    // This is fine
    std::thread t1 = std::thread (fun);
    t1.join();

    // This will not compile , because 
    // thread(thread&) = delete;
    //std::thread t2 = t1;
        
    // print main thread's id
    std::cout << "Main thread id : " << std::this_thread::get_id() << std::endl;
    std::cout << "Child threads id : " << t1.get_id() << std::endl;

    // standard way to create a thread
    // call with integer
    std::thread thread_with_thread_function(thread_function,10);
    thread_with_thread_function.join();

    // thread with functor
    Functor f;
    // call with string
    std::string str("This value is not changed in thread , even if passed by reference. You need to use std::ref(X) ");

    // The line below will not compile because value is passed , but thread accepts refrence.
    // This is tested on g++ and clang.
    //std::thread thread_with_functor_accepts_value(f,str);

    // Note that below, std::ref is used to pass reference of a string
    std::thread thread_with_functor_accepts_ref(f,std::ref(str));

    // Note that you can use std::move to move the str from main thread to child thread
    // This did not work on clang and g++, however seems to work on visual c++ ( as per youtube tutorial )
    //std::thread thread_with_functor_using_move(f,std::move(str));
    //thread_with_functor_using_move.join();
    std::cout << "priting value in Main : " << str;

    // Lets wait for thread to finish
    thread_with_functor_accepts_ref.join();
    
    // thread with lambda function
    std::thread lambda_thread ( [] () { std::cout << "Thread with lambda function" << std::endl; });
    lambda_thread.join();

}
