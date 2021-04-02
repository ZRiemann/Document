#!/usr/bin/env python3

x = input('Please enter an integer:')
x = int(x)
if(x < 0):
    print("Negative changed to zero")
    x = 0
elif x == 0:
    print("Zero")
else:
    print("More")
