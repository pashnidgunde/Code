import os;


#defining different functions:


def Area_of_triangle (height,base):
    area = (1/2)* height * base
    return area



#MAIN

print("Enter Height:")
height = int(input())
print("Enter Base:")
base = int(input())
a = Area_of_triangle( height,base)
print("result =:" , a)