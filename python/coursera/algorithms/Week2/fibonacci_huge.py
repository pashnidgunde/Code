# Uses python3

# Program that computes the last digit of a fibonacci number
# Here the logic is that instead of computing a long fibonacci 
# and then computing a complex mod operator, just store the remainder
# and use the remainder
#
#Naive solution will turn out to be too slow, because as 𝑖 grows the 𝑖th iteration of the loop computes the sum of longer
#and longer numbers. Also, for example, 𝐹1000 does not fit into the standard C++ int type. To overcome
#this difficulty, you may want to store in 𝐹[𝑖] not the 𝑖th Fibonacci number itself, but just its last digit (that
#is, 𝐹𝑖 mod 10). Computing the last digit of 𝐹𝑖
#is easy: it is just the last digit of the sum of the last digits of
#𝐹𝑖−1 and 𝐹𝑖−2:



import sys

def get_fibonacci_huge_naive(n, m):
    if n <= 1:
        return n

    previous = 0
    current  = 1

    for _ in range(n - 1):
        previous, current = current, (previous + current) % m 

    return current % m

if __name__ == '__main__':
    input = sys.stdin.read();
    n, m = map(int, input.split())
    print(get_fibonacci_huge_naive(n, m))
