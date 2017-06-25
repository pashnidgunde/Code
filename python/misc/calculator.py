import os
import math

  ############ Calculator program
choice = 0

while True:
    print ("Welcome to calculator.py:")
    print("Your options are:")
    print (" ")
    print (" 1) Addition")
    print (" 2) Substraction")
    print (" 3) Multification")
    print (" 4) Division")
    print (" 5) Quit calculator.py")
    print ("  ")

    choice = int(input("Choose your option: "))
    if choice == 5:
        print ("Thank you For using calculator :")
        break

    number1 = int(input("Enter first number"))
    number2 = int(input("Enter second number"))
    
    if choice == 1:
        print (number1,"+", number2, "=", number1 + number2 )
    elif choice == 2:
        print (number1, "-",number2 ,"=", number1 - number2 )    
    elif choice == 3:
        print (number1, "*",number2, "=", number1 * number2 )
    elif choice == 4:
        print (number1, "/",number2, "=", number1 / number2 )    
            









