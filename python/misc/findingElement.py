#finding Element into the list
import os;


#function for Finding Elements from list

def FindingElements(numbers,num):
    for number in numbers:
        if (number == num):
            
            print("Yes")

            return
    print("No")



numbers = [1,2,3,4,5,6,7,8,9]
print("Enter input Number:")
x = int(input())
FindingElements(numbers,x)