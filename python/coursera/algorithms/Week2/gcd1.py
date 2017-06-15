import os

#A list based version that finds gcd in a list
def gcd_list(numbers):
    g = numbers[0]
    for number in numbers:
        g = gcd_faster(g,number) 
    return g


# This is naive approach 
# Iterate to look up if division is possible
def gcd(n1,n2):
    x = min(n1,n2)
    for i in range (x,1,-1):
        if n1 % i == 0 and n2 % i == 0:
            return i

    return 1

# This is fast approach 
# 
def gcd_faster(a,b):
    if b > a : 
        a,b = b,a

    if (a%b == 0):
        return b
    
    return gcd(b, a%b)

print (gcd(10,4))
print (gcd(20,30))
print (gcd_faster(10,4))
print (gcd_faster(30,20))
print (gcd_list([10,20,30,40]))


