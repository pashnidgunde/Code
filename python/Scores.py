# https://www.hackerrank.com/contests/university-codesprint-2/challenges/breaking-best-and-worst-records

import os

n = int(input().strip())
input_list = list(map(int,input().strip().split(' ')))

highest_break = 0
lowest_break = 0

highest_score = input_list[0]
lowest_score = input_list[0]

for element in input_list:
    if element > highest_score :
        highest_score = element
        highest_break+=1

    if element < lowest_score :
        lowest_score = element
        lowest_break+=1
        
print (highest_break , lowest_break)








