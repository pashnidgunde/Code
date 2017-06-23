# Uses python3
import sys

#Task. The goal in this problem is to find the minimum number of coins needed to change the input value
#(an integer) into coins with denominations 1, 5, and 10.
#28 = 10 + 10 + 5 + 1 + 1 + 1.


def get_change(m):
    # list of denominations in greedy maaner to have largest denomiation as the begining
    change = [10,5,1]

    # index
    i = 0

    #count of coins
    coins = 0

    # while money is greater than 0
    while (m > 0):
        # Is there a denomination possible with largest change ?
        if ( m - change[i] >= 0 ):
            m -= change[i]
            coins += 1
            continue
        # Move to next denomination
        i += 1 

    return coins
        

if __name__ == '__main__':
    m = int(sys.stdin.read())
    print(get_change(m))
