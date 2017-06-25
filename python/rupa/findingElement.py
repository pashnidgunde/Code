#finding Element into the list
import os;


#function for Finding Elements from list

def FindingElements(numbers,num):
    for number in numbers:
        if (number == num):
            print("Yes")
            return
    
    print("No")

#Fuction to finding minimum Element from list
def MinimumElement(numbers):
    minimum = numbers[0]
    for number in numbers:
        if(number < minimum):
            minimum = number
    return minimum

#Function to finding maximm Element from list
def MaximumElement(numbers):
    maximum = numbers[0]
    for number in numbers:
        if(number > maximum):
            maximum = number
    return maximum

#Revrsing the list

def  ReverseList(numbers):
    i = 0
    j =len (numbers)-1

    while(i <= j):    
        a = numbers[i]
        numbers[i] = numbers[j]
        numbers[j] = a
        i = i+1
        j = j-1

def SumOfList(numbers):
    total = 0
    for number in numbers:
        total = total + number
    return total         
    
def SumOfUserNumber(number):
    #total = 0
    #limit = 1
    #while (limit <= number):
    #    total = total + limit
    #    limit = limit + 1
    #return total

    return (number * (number+1) ) / 2


#list
numbers = [1,2,3,4,5,6,7,8,9]

min = MinimumElement(numbers)
print(min)
max = MaximumElement(numbers)
print(max)
ReverseList(numbers)
print(numbers)
sum = SumOfList(numbers)
print(sum)
print("enter your limit:")
lim = int(input())
total = SumOfUserNumber(lim)
print(total)

#print("Enter input Number:")
#x = int(input())
#FindingElements(numbers,x)