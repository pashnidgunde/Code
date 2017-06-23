# Program to get fibonacci number for a given number

def fibonacci(n):
    if (n < 2):
        return n
    else:
        return fibonacci(n-1) + fibonacci(n-2)

def fibonacci_non_recursive(n):
    if ( n < 2) :
        return n
    prev = 0
    curr = 1
    while (n > 1) :
        fib = prev + curr
        prev = curr
        curr = fib
        n -= 1
    
    return fib
    

print (fibonacci(15))
print (fibonacci_non_recursive(15))
