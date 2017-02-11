// Singleton.hpp
class Singleton {
public:
    static Singleton& Instance() {
        static Singleton S;
        return S;
    }

private:
    Singleton();
    ~Singleton();
};