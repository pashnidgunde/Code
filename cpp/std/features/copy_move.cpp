#include <iostream>
#include <cstring>

class String
{
    public:
        String() = default;
        String(const char* other)
        {
            std::cout << "Constructor: New" << std::endl; 
            _size = strlen(other);
            _data = new char[_size];
            memcpy(_data,other,_size);
        }

        String(const String& other)
        {
            std::cout << "Copy constructor" << std::endl; 
            _size = other._size;
            _data = new char[_size];
            memcpy(_data,other._data,_size);
        }

        String(String&& other)
        {
            std::cout << "Move constructor" << std::endl; 
            _size = other._size;
            _data = other._data;

            other._size = 0;
            other._data = nullptr;
        }

        // String(String& rhs)
        // {
        //     std::cout << 
        // }

        void print()
        {
            for (size_t i=0; i < _size; i++)
            {
                std::cout << _data[i];
            }
            std::cout << std::endl;
        }

    private:
        char* _data = nullptr;
        size_t _size = 0;
};

class StringHandler
{
    public:
        StringHandler(String& s) : _s(s) {
            std::cout << "SH Copy" << std::endl;
        }

        StringHandler(String&& s) : _s(std::move(s)) {
            std::cout << "SH Move" << std::endl;
        }

        void print()
        {
            _s.print();
        }
    private:
        String _s;
};

int main()
{
    
    String s;
    String s1("Hello");
    String s2(std::move(s1));
    //s2.print();
    StringHandler sh(std::move(s2));
    sh.print();
    StringHandler sh1(s2);
    sh1.print();

}
