import os

# Naive implementation of max_product
def max_product_in_range(numbers) :
    n = len(numbers)
    max_product = 0

    for i in range (0,n):
        for j in range (i+1,n):
            if numbers[i] * numbers[j] > max_product :
                max_product = numbers[i] * numbers[j]

    return max_product

# Faster implementation of max_product
def max_product_in_range_faster(numbers):
    n = len(numbers)
    max_index = 0
    for i in range (0,n):
        if (numbers[i] > numbers[max_index]):
            max_index = i

    max_index1 = 0
    for i in range(0,n):
        if ((i != max_index) and (numbers[i] > numbers[max_index1])):
            max_index1 = i

    return numbers[max_index] * numbers[max_index1]

# Main begins here
n =  int(input().strip())
numbers = [int(x) for x in input().split()]
#print (max_product_in_range(numbers))
print (max_product_in_range_faster(numbers))
        


