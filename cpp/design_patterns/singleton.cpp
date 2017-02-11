#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>

class Singleton
{
    private:
        Singleton() = default;
        ~Singleton() = default;

        static Singleton *instance;
        std::mutex _m;

    public:
        static Singleton* getInstance()
        {
            if (nullptr == instance)
            {
                std::lock_guard<mutex> (m);
                if (nullptr == instance)
                    instance = new Singleton();
            }

            return instance;
        }

        
};

Singleton* Singleton::instance = nullptr;


int main()
{
    Singleton *s = Singleton::getInstance();
    Singleton *s1 = Singleton::getInstance();

    assert(s == s1);

}
