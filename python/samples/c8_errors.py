#!/usr/bin/python3
# _*_ coding: UTF-8 _*_

import sys

# 8. 错误和异常¶
# 8.3. 处理异常¶
while True:
    try:
        x = 3 #int(input("Please enter a number: "))
        break
    except ValueError:
        print("Oops!  That was no valid number.  Try again...")
    except (RuntimeError, TypeError, NameError):
        pass

class B(Exception):
    pass

class C(B):
    pass

class D(C):
    pass

for cls in [B, C, D]:
    try:
        raise cls()
    except D:
        print("D")
    except C:
        print("C")
    except B:
        print("B")

try:
    f = open('fibo.py')
    s = f.readline()
    i = int(s.strip())
except OSError as err:
    print("OS error: {0}".format(err))
except ValueError:
    print("Could not convert data to an integer.")
except: # 最后最为通配
    print("Unexpected error:", sys.exc_info()[0])
    raise

for arg in sys.argv[1:]:
    try:
        f = open(arg, 'r')
    except OSError:
        print('cannot open', arg)
    else: # 相当于 finally
        print(arg, 'has', len(f.readlines()), 'lines')
        f.close()

try:
    raise Exception('spam', 'eggs')
except Exception as inst:
    print(type(inst))    # the exception instance
    print(inst.args)     # arguments stored in .args
    print(inst)          # __str__ allows args to be printed directly,
                         # but may be overridden in exception subclasses
    x, y = inst.args     # unpack args
    print('x =', x)
    print('y =', y)
# <class 'Exception'>
# ('spam', 'eggs')
# ('spam', 'eggs')
# x = spam
# y = eggs


# 8.4. 抛出异常¶
# raise 语句允许程序员强制发生指定的异常。例如:
try:
    raise NameError('HiThere')
except NameError as nerr:
    print(f'error {nerr}')
    #raise # 继续抛出该异常

# 8.5. 用户自定义异常¶
class Error(Exception):
    """Base class for exceptions in this module."""
    pass

class InputError(Error):
    """Exception raised for errors in the input.

    Attributes:
        expression -- input expression in which the error occurred
        message -- explanation of the error
    """

    def __init__(self, expression, message):
        self.expression = expression
        self.message = message

class TransitionError(Error):
    """Raised when an operation attempts a state transition that's not
    allowed.

    Attributes:
        previous -- state at beginning of transition
        next -- attempted new state
        message -- explanation of why the specific transition is not allowed
    """

    def __init__(self, previous, next, message):
        self.previous = previous
        self.next = next
        self.message = message

# 8.6. 定义清理操作¶
# finally
try:
    #raise KeyboardInterrupt
    print('raise KeyboardInterrupt')
finally:
    print('Goodbye, world!')


# 8.7. 预定义的清理操作¶
# with 语句允许像文件这样的对象能够以一种确保它们得到及时和正确的清理的方式