#include <thread>
#include <iostream>

class scoped_thread
{
    public:
        explicit scoped_thread(std::thread t) : _t(std::move(t))
        {

        }

        ~scoped_thread()
        {
            _t.join();
        }


    private:
        std::thread _t;

};


class Functor
{
    public:
        void operator ()()
        {
            // does nothing
        }
};



int main()
{
    Functor f;
    scoped_thread(std::thread(f));

    scoped_thread(std::thread([]() { std::cout << "Hello"; }));
    
}

