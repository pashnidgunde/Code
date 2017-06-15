import os

# factorial recursive
def factorial_recursive(n):
    if (n < 2):
        return n
    else:
        return n * factorial_recursive(n-1)

def factorial(n):
    f = n
    while ( n > 1):
        f = f * (n-1)
        n-=1
    
    return f


n = int(input().strip())
print (factorial_recursive(n))
print (factorial(n))

    
