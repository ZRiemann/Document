#!/usr/bin/python3
#_*_ coding: UTF-8 _*_

import sys

################################################################################
# $ 7.1 输出格式
year = 2016
event = 'Referendum'
print(f'Results of the {year} {event}')
#'Results of the 2016 Referendum'

yes_votes = 42_572_654
no_votes = 43_132_495
percentage = yes_votes / (yes_votes + no_votes)
print('{:-9} YES votes  {:2.2%}'.format(yes_votes, percentage))
#' 42572654 YES votes  49.67%'

s = 'Hello, world.'
print(str(s))
#'Hello, world.'
print(repr(s))
#"'Hello, world.'"
print(str(1/7))
#'0.14285714285714285'
x = 10 * 3.25
y = 200 * 200
s = 'The value of x is ' + repr(x) + ', and y is ' + repr(y) + '...'
print(s)
#The value of x is 32.5, and y is 40000...
# The repr() of a string adds string quotes and backslashes:
hello = 'hello, world\n'
hellos = repr(hello)
print(hellos)
#'hello, world\n'
# The argument to repr() may be any Python object:
print(repr((x, y, ('spam', 'eggs'))))
#"(32.5, 40000, ('spam', 'eggs'))"

import math
print(f'The value of pi is approximately {math.pi:.3f}.')
#The value of pi is approximately 3.142.

table = {'Sjoerd': 4127, 'Jack': 4098, 'Dcab': 7678}
for name, phone in table.items():
    print(f'{name:10} ==> {phone:10d}')

#Sjoerd     ==>       4127
#Jack       ==>       4098
#Dcab       ==>       7678

#'!a' 应用 ascii() ，'!s' 应用 str()，还有 '!r' 应用 repr():
animals = 'eels'
print(f'My hovercraft is full of {animals}.')
#My hovercraft is full of eels.
print(f'My hovercraft is full of {animals!r}.')
#My hovercraft is full of 'eels'.

# 7.1.2. 字符串的 format() 方法
# str.format() 方法的基本用法如下所示:
print('We are the {} who say "{}!"'.format('knights', 'Ni'))
# We are the knights who say "Ni!"
# 将替换为传递给 str.format() 方法的对象。花括号中的数字可用来表示传递给
print('{0} and {1}'.format('spam', 'eggs'))
# spam and eggs
print('{1} and {0}'.format('spam', 'eggs'))
# eggs and spam
print('This {food} is {adjective}.'.format(
    food='spam', adjective='absolutely horrible'))
# This spam is absolutely horrible.
print('The story of {0}, {1}, and {other}.'.format('Bill', 'Manfred',
    other='Georg'))
# The story of Bill, Manfred, and Georg.
table = {'Sjoerd': 4127, 'Jack': 4098, 'Dcab': 8637678}
print('Jack: {0[Jack]:d}; Sjoerd: {0[Sjoerd]:d}; '
      'Dcab: {0[Dcab]:d}'.format(table))
# Jack: 4098; Sjoerd: 4127; Dcab: 8637678
print('Jack: {Jack:d}; Sjoerd: {Sjoerd:d}; Dcab: {Dcab:d}'.format(**table))
# Jack: 4098; Sjoerd: 4127; Dcab: 8637678
for x in range(1, 11):
    print('{0:2d} {1:3d} {2:4d}'.format(x, x*x, x*x*x))
# 1   1    1
# 2   4    8
# 3   9   27
# 4  16   64
# 5  25  125
# 6  36  216
# 7  49  343
# 8  64  512
# 9  81  729
# 10 100 1000

# same as above
# ljust(n), rjust(n) 左/右测填充空格
for x in range(1, 11):
    print(repr(x).rjust(2), repr(x*x).rjust(3), end=' ')
    print(repr(x*x*x).rjust(4))
# str.zfill() ，它会在数字字符串的左边填充零。它能识别正负号:
print('12'.zfill(5))
# '00012'
print('-3.14'.zfill(7))
# '-003.14'
print('3.14159265359'.zfill(5))
# '3.14159265359'

# 7.2. 读写文件¶
# open() 返回一个 file object
# 最常用的有两个参数： open(filename, mode[r|w|a|r+|b])。
# 最好使用 with 关键字。 优点是当子句体结束后文件会正确关闭，即使在某个时刻引发了异常。
# 而且使用 with 相比等效的 try-finally 代码块要简短得多:
fname = 'fibo.py'
with open(fname) as f:
    read_data = f.read()
    print(read_data)
# We can check that the file has been automatically closed.
if f.closed:
    print(f'file {fname} automatically closed')
else:
    print(f'file {fname} NOT closed')

# 7.2.1. 文件对象的方法¶
# f.read(size) 它会读取一些数据并将其作为字符串
# f.read() # 当 size 被省略或者为负数时，将读取并返回整个文件的内容
# 'This is the entire file.\n'
# f.read() # 如果已到达文件末尾，f.read() 将返回一个空字符串 ('')。
# ''

# f.readline() 从文件中读取一行；
# f.readline() => 'This is the first line of the file.\n'
# f.readline() => 'Second line of the file\n'
# f.readline() => '' # end of file
with open(fname) as f:
    print('内存高效，快速的，并简化代码:')
    for line in f:
        print(line, end='')
with open(fname) as f:
    lines = list(f)
    print('list(f), f.readlines() 读取到列表\n', lines)

# f.write(string) 会把 string 的内容写入到文件中，并返回写入的字符数。:
# f.write('This is a test\n')
# 15

# 在写入其他类型的对象之前，需要先把它们转化为字符串（在文本模式下）或者字节对象（在二进制模式下）:
# value = ('the answer', 42)
# s = str(value)  # convert the tuple to string
# f.write(s)
# 18

# f.tell() 返回一个整数，给出文件对象在文件中的当前位置，表示为二进制模式下时从文件开始的字节数
# f.seek(offset, whence)
# 通过向一个参考点添加 offset 来计算位置；参考点由
# whence 参数指定。 whence 的 default:0 值表示从文件开头起算，1 表示使用当前文件位置，
# 2 表示使用文件末尾作为参考
# with open('test-file', 'rb+') as f:
#    print(f.write(b'0123456789abcdef'))
#    f.seek(5)      # Go to the 6th byte in the file
#    print(f.read(1)) # => b'5'
#    f.seek(-3, 2)  # Go to the 3rd byte before the end
#    print(f.read(1)) # => b'd'


# 7.2.2. 使用 json 保存结构化数据¶
import json
print(json.dumps([1, 'simple', 'list']))
# json.dump(x, f)
# x = json.load(f)
