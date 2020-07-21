#!/usr/bin/python3
# _*_ coding: UTF-8 _*_

import sys

print("$4. range([begin,] <end> [, step])\n")
print("range(5, 10)\n=> ", list(range(5, 10)))
print("range(0, 10, 3)\n=> ", list(range(0, 10, 3)))
print("range(-10, -100, -30)\n=> ", range(-10, -100, -30))

print("""
>>> # 迭代数组
>>> a = ['Mary', 'had', 'a', 'little', 'lamb']
>>> for i in range(len(a)):
...     print(i, a[i])
...\
""")
a = ['Mary', 'had', 'a', 'little', 'lamb']
for i in range(len(a)):
    print(i, a[i])
print()
print("$4.4 break, continue, else")
print("""
>>> for n in range(2, 10):
...     for x in range(2, n):
...         if n % x == 0:
...             print(n, 'equals', x, '*', n//x)
...             break
...     else:
...         # loop fell through without finding a factor
...         print(n, 'is a prime number')
...\
""")
for n in range(2, 10):
     for x in range(2, n):
         if n % x == 0:
             print(n, 'equals', x, '*', n//x)
             break
     else:
         # loop fell through without finding a factor
         print(n, 'is a prime number')

print('\n$4.5 passe')
print('no operate, dummy')
print("""
>>> while True:
...     pass  # Busy-wait for keyboard interrupt (Ctrl+C)
...
>>> class MyEmptyClass:
...     pass
...
>>> def initlog(*args):
...     pass   # Remember to implement this!
...
""")

print("#############################################################")
print("$4.7 函数定义的更多形式")
print("$4.7.1 默认参数")
print("def ask_ok(prompt, retries=4, reminder='Please try again!'):")
def ask_ok(prompt, retries=4, reminder='Please try again!'):
    while True:
        ok = input(prompt)
        if ok in ('y', 'ye', 'yes'):
            return True
        if ok in ('n', 'no', 'nop', 'nope'):
            return False
        retries = retries - 1
        if retries < 0:
            raise ValueError('invalid user response')
        print(reminder)
#ask_ok("say yes:")

print("""
def f(a, L=[]):
    L.append(a)
    return L
=>\
""")
def f(a, L=[]):
    L.append(a)
    return L

print(f(1))
print(f(2))
print(f(3))

print("""
def f(a, L=None):
    if L is None:
        L = []
    L.append(a)
    return L
=>
""")
def f1(a, L=None):
    if L is None:
        L = []
    L.append(a)
    return L
print(f1(1))
print(f1(2))
print(f1(3))

print("$4.7.2 关键字参数")
def parrot(voltage, state='a stiff', action='voom', type='Norwegian Blue'):
    print("-- This parrot wouldn't", action, end=' ')
    print("if you put", voltage, "volts through it.")
    print("-- Lovely plumage, the", type)
    print("-- It's", state, "!")
parrot(1000)                                          # 1 positional argument
parrot(voltage=1000)                                  # 1 keyword argument
parrot(voltage=1000000, action='VOOOOOM')             # 2 keyword arguments
parrot(action='VOOOOOM', voltage=1000000)             # 2 keyword arguments
parrot('a million', 'bereft of life', 'jump')         # 3 positional arguments
parrot('a thousand', state='pushing up the daisies')  # 1 positional, 1 keyword