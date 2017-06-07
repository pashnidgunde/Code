
import os
# import mean from statistics
from statistics import mean

# Function to determine the mean by droping first and last 
def drop_first_last(grades):
    # ignore first and last from the list of integers
    # Following works on iterable elements , in this case a list
    # _ is throw away which means this value you dont care
    _,*middle,_=grades

    # return mean of the numbers
    return mean(middle)

# Main
# input numbers from console and split on space
# once split they are still string, so map them to integer using int
# and then create a list of such integers
#numbers = list(map(int,(input().strip().split(' '))))
numbers = [10,20,30,40,50]
print (numbers)

print(drop_first_last(numbers))

# Example for *
line = 'nobody:*:-2:-2:Unpreviledged User:/var/empty:/usr/bin/false'
# * is for more than one , here you are throwing away all before dir and cmd
*_,dir,cmd = line.split(':')
print(dir, "::" , cmd)

# Another example
record = ('ACME', 50, 123.40,(12,18,2012))
name,*_,((*_,year)) = record
print (name , ":: " , year)
