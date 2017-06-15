# Uses python3
import sys

def gcd_faster(a,b):
    if (b > a):
        a,b = b,a

    if (a % b == 0):
        return b

    return gcd_faster(b, a % b)


#def gcd_naive(a, b):
#    current_gcd = 1
#    for d in range(2, min(a, b) + 1):
#       if a % d == 0 and b % d == 0:
#           if d > current_gcd:
#                current_gcd = d

#   return current_gcd




if __name__ == "__main__":
    input = sys.stdin.read()
    a, b = map(int, input.split())
    print(gcd_faster(a, b))
