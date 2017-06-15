#include <iostream>

// Program that computes the last digit of a fibonacci number
// Here the logic is that instead of computing a long fibonacci 
// and then computing a complex mod operator, just store the remainder
// and use the remainder
//
//Naive solution will turn out to be too slow, because as 𝑖 grows the 𝑖th iteration of the loop computes the sum of longer
//and longer numbers. Also, for example, 𝐹1000 does not fit into the standard C++ int type. To overcome
//this difficulty, you may want to store in 𝐹[𝑖] not the 𝑖th Fibonacci number itself, but just its last digit (that
//is, 𝐹𝑖 mod 10). Computing the last digit of 𝐹𝑖
//is easy: it is just the last digit of the sum of the last digits of
//𝐹𝑖−1 and 𝐹𝑖−2:

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current) % 10;
    }

    return current % m;
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_naive(n, m) << '\n';
}
