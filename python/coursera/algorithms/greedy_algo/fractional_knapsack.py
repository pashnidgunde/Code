# Uses python3
import sys
from operator import truediv

#Task. The goal of this code problem is to implement an algorithm for the fractional knapsack problem.
# Input:
# 3 50
# 60 20
# 100 50
# 120 30
# Output:
# 180.0000

def get_optimal_value(capacity, weights, values):
    
    # Divide two arrays 
    # Courtesy : https://stackoverflow.com/questions/16418415/divide-two-lists-in-python

    value_per_weight = list(map(truediv, values, weights))

    # This will return indexes of sorted elements
    # Courtesy : https://stackoverflow.com/questions/6422700/how-to-get-indices-of-a-sorted-array-in-python
    # To sort in reverse order use reverse = true 
    sorted_indexes = [i[0] for i in sorted(enumerate(value_per_weight), key=lambda x:x[1], reverse = True)]

    value = 0.
    i = 0
    
    while(capacity > 0):
        value += weights[sorted_indexes[i]] * value_per_weight[sorted_indexes[i]]
        capacity -= weights[i]
        i+=1

    return value

# ===================== List Slicing     =========================================

# a[start:end] # items start through end-1
# a[start:]    # items start through the rest of the array
# a[:end]      # items from the beginning through end-1
# a[:]         # a copy of the whole array
# a[start:end:step] # start through not past end, by step
# a[-1]    # last item in the array
# a[-2:]   # last two items in the array
# a[:-2]   # everything except the last two items

# ==================================================================================


if __name__ == "__main__":
  
    # This is to read all elements from input in one big list or array
    data = list(map(int, sys.stdin.read().split()))
  
    # Take elements at index 0 to 2 
    n, capacity = data[0:2]

    # Take elements from 2 to ( 2*n + 2) with step of 2
    values = data[2:(2 * n + 2):2]

    # Take elements from 3 to ( 2*n + 2) with step of 2
    weights = data[3:(2 * n + 2):2]

    opt_value = get_optimal_value(capacity, weights, values)
    
    print("{:.4f}".format(opt_value))
