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
=>\n
""")
def f(a, L=[]):
    L.append(a)
    return L

print(f(1))
print(f(2))
print(f(3))

print("""################################################################################
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

print("""$4.7.2 关键字参数
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
""")
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

print("""################################################################################
$4.7.3 特殊参数
def f(pos1, pos2, /, pos_or_kwd, *, kwd1, kwd2):
      -----------    ----------     ----------
        |             |                  |
        |        Positional or keyword   |
        |                                - Keyword only
         -- Positional only

$4.7.4. 任意的参数列表
def write_multiple_items(file, separator, *args):
    file.write(separator.join(args))
>>> def concat(*args, sep="/"):
...     return sep.join(args)
...
>>> concat("earth", "mars", "venus")
'earth/mars/venus'
>>> concat("earth", "mars", "venus", sep=".")
'earth.mars.venus'
""")
def concat(*args, sep="/"):
    return sep.join(args)
concat("earth", "mars", "venus")
concat("earth", "mars", "venus", sep=".")

print("""################################################################################
$4.7.5 解包参数列表
>>> list(range(3, 6))            # normal call with separate arguments
[3, 4, 5]
>>> args = [3, 6]
>>> list(range(*args))            # call with arguments unpacked from a list
[3, 4, 5]

字典可使用 ** 操作符 来提供关键字参数:
>>> def parrot(voltage, state='a stiff', action='voom'):
...     print("-- This parrot wouldn't", action, end=' ')
...     print("if you put", voltage, "volts through it.", end=' ')
...     print("E's", state, "!")
...
>>> d = {"voltage": "four million", "state": "bleedin' demised", "action": "VOOM"}
>>> parrot(**d)\
""")
list(range(3, 6))            # normal call with separate arguments
args = [3, 6]
list(range(*args))            # call with arguments unpacked from a list

def parrot(voltage, state='a stiff', action='voom'):
    print("-- This parrot wouldn't", action, end=' ')
    print("if you put", voltage, "volts through it.", end=' ')
    print("E's", state, "!")
d = {"voltage": "four million", "state": "bleedin' demised", "action": "VOOM"}
parrot(**d)

print("""################################################################################
$4.7.6. Lambda 表达式
>>> pairs = [(1, 'one'), (2, 'two'), (3, 'three'), (4, 'four')]
>>> pairs.sort(key=lambda pair: pair[1])
>>> pairs
[(4, 'four'), (1, 'one'), (3, 'three'), (2, 'two')]
""")
pairs = [(1, 'one'), (2, 'two'), (3, 'three'), (4, 'four')]
pairs.sort(key=lambda pair: pair[1])
pairs

print("""################################################################################
$4.7.7 文档字符串
>>> def my_function():
...     \"""Do nothing, but document it.
...
...     No, really, it doesn't do anything.
...     \"""
...     pass
...
>>> print(my_function.__doc__)
Do nothing, but document it.

    No, really, it doesn't do anything.

$4.7.8. 文档标注
>>> def f(ham: str, eggs: str = 'eggs') -> str:
...     print("Annotations:", f.__annotations__)
...     print("Arguments:", ham, eggs)
...     return ham + ' and ' + eggs
...
>>> f('spam')
Annotations: {'ham': <class 'str'>, 'return': <class 'str'>, 'eggs': <class 'str'>}
Arguments: spam eggs
'spam and eggs'

$4.8 小插曲：编码风格
- 使用4个空格缩进，不要使用制表符。
- 4个空格是一个在小缩进（允许更大的嵌套深度）和大缩进（更容易阅读）的一种很好的折中方案。制表符会引入混乱，最好不要使用它。
  换行，使一行不超过79个字符。
  这有助于使用小型显示器的用户，并且可以在较大的显示器上并排放置多个代码文件。
- 使用空行分隔函数和类，以及函数内的较大的代码块。
  如果可能，把注释放到单独的一行。
- 使用文档字符串。
- 在运算符前后和逗号后使用空格，但不能直接在括号内使用： a = f(1, 2) + g(3, 4)。
- 以一致的规则为你的类和函数命名；按照惯例应使用 UpperCamelCase 来命名类，而以 lowercase_with_underscores 来命名函数和方   法。 始终应使用 self 来命名第一个方法参数 (有关类和方法的更多信息请参阅 初探类)。
- 如果你的代码旨在用于国际环境，请不要使用花哨的编码。Python 默认的 UTF-8 或者纯 ASCII 在任何情况下都能有最好的表现。
- 同样，哪怕只有很小的可能，遇到说不同语言的人阅读或维护代码，也不要在标识符中使用非ASCII字符。
""")