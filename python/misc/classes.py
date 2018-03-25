import os


#DEFINING CLASS

class shape:
    def __init__(self, x):
        self.x = x
    def area(self):
        return(3.14*self.x*self.x)

circle = shape(2)
print(circle.area())
 
