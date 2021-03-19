#!/usr/bin/python3
#_*_coding: UTF-8_*_

# https://docs.python.org/zn-cn/3/tutorial/stdlib.html
# 10.1. 操作系统接口¶
import os
# from os import * # 不要这样使用,open() 函数被 os.open() 隐式替换掉
print(os.getcwd()) # Return the current working directory
os.chdir(os.getcwd())   # Change current working directory
# os.system('mkdir today')   # Run the command mkdir in the system shell
# 内置的 dir() 和 help() 函数可用作交互式辅助工具，用于处理大型模块，如 os:
# print(dir(os))
# print(help(os))

# shutil 模块提供了更易于使用的更高级别的接口:
import shutil
# shutil.copyfile('fibo.py', 'fibo.py.back')
# shutil.move('/build/executables', 'installdir')

# 10.2. 文件通配符¶
# glob 模块提供了一个在目录中使用通配符搜索创建文件列表的函数:
import glob
print(glob.glob('*.py'))

# 10.3. 命令行参数¶
import sys
print(sys.argv)
#argparse 模块提供了一种更复杂的机制来处理命令行参数。 以下脚本可提取一个或多个文件名.
import argparse
parser = argparse.ArgumentParser(prog = 'top',
    description = 'Show top lines from each file')
parser.add_argument('filenames', nargs='+')
parser.add_argument('-l', '--lines', type=int, default=10)
args = parser.parse_args()
print(args)
# 当在通过 python top.py --lines=5 alpha.txt beta.txt 在命令行运行时，
# 该脚本会将 args.lines 设为 5 并将args.filenames 设为 ['alpha.txt', 'beta.txt']。

# 10.4. 错误输出重定向和程序终止¶
# sys 模块还具有 stdin ， stdout 和 stderr 的属性
sys.stderr.write('Warning, log file not found starting a new one\n')
# 终止脚本的最直接方法是使用 sys.exit() 。

# 10.5. 字符串模式匹配¶
# re 模块为高级字符串处理提供正则表达式工具。
import re
print(re.findall(r'\bf[a-z]*', 'which foot or hand fell fastest'))
print(re.sub(r'(\b[a-z]+) \1', r'\1', 'cat in the the hat'))
# 当只需要简单的功能时，首选字符串方法因为它们更容易阅读和调试:
print('tea for too'.replace('too', 'two'))

# 10.6. 数学¶
# math 模块提供对浮点数学的底层C库函数的访问:
import math
print(math.cos(math.pi / 4))
print(math.log(1024, 2))
# random 模块提供了进行随机选择的工具:
import random
print(random.choice(['apple', 'pear', 'banana']))
print(random.sample(range(100), 10)) # sampling without replacement
print(random.random())    # random float
print(random.randrange(6))    # random integer chosen from range(6)
# statistics 模块计算数值数据的基本统计属性（均值，中位数，方差等）:
import statistics
data = [2.75, 1.75, 1.25, 0.25, 0.5, 1.25, 3.5]
print(statistics.mean(data))
print(statistics.median(data))
# SciPy项目 <https://scipy.org> 有许多其他模块用于数值计算。

# 10.7. 互联网访问¶
# urllib.request 用于从URL检索数据
# smtplib 用于发送邮件
# ...
from urllib.request import urlopen
# with urlopen('http://tycho.usno.navy.mil/cgi-bin/timer.pl') as response:
#    for line in response:
#        line = line.decode('utf-8')  # Decoding the binary data to text.
#        if 'EST' in line or 'EDT' in line:  # look for Eastern Time
#            print(line)

# 10.8. 日期和时间¶
# datetime 模块提供了以简单和复杂的方式操作日期和时间的类。
# dates are easily constructed and formatted
from datetime import date
now = date.today()
print(now)
# datetime.date(2003, 12, 2)
print(now.strftime("%m-%d-%y. %d %b %Y is a %A on the %d day of %B."))
# '12-02-03. 02 Dec 2003 is a Tuesday on the 02 day of December.'

# dates support calendar arithmetic
birthday = date(1964, 7, 31)
age = now - birthday
print(age.days)
# 14368

# 10.9. 数据压缩¶
# 常见的数据存档和压缩格式由模块直接支持，包括：zlib, gzip, bz2, lzma, zipfile 和 tarfile
import zlib
s = b'witch which has which witches wrist watch'
print(len(s))
t = zlib.compress(s)
print(len(t))
# 37
print(zlib.decompress(t))
#b'witch which has which witches wrist watch'
print(zlib.crc32(s))
#226805979

# 10.10. 性能测量¶
from timeit import Timer
print(Timer('t=a; a=b; b=t', 'a=1; b=2').timeit())
#0.57535828626024577
print(Timer('a,b = b,a', 'a=1; b=2').timeit())
0.54962537085770791
# 与 timeit 的精细粒度级别相反，
# profile 和 pstats 模块提供了用于在较大的代码块中识别时间关键部分的工具。

# 10.11. 质量控制¶
# doctest 模块提供了一个工具，用于扫描模块并验证程序文档字符串中嵌入的测试。
def average(values):
    """Computes the arithmetic mean of a list of numbers.

    >>> print(average([20, 30, 70]))
    40.0
    """
    return sum(values) / len(values)

import doctest
print(doctest.testmod())   # automatically validate the embedded tests
# unittest 模块不像 doctest 模块那样易于使用，但它允许在一个单独的文件中维护更全面的测试集:
import unittest

class TestStatisticalFunctions(unittest.TestCase):

    def test_average(self):
        self.assertEqual(average([20, 30, 70]), 40.0)
        self.assertEqual(round(average([1, 5, 7]), 1), 4.3)
        with self.assertRaises(ZeroDivisionError):
            average([])
        with self.assertRaises(TypeError):
            average(20, 30, 70)

unittest.main()  # Calling from the command line invokes all tests

# 10.12. 自带电池¶
# xmlrpc.client 和 xmlrpc.server 模块使得实现远程过程调用变成了小菜一碟。
# email 包是一个用于管理电子邮件的库
# json 包为解析这种流行的数据交换格式提供了强大的支持
# csv 模块支持以逗号分隔值格式直接读取和写入文件
# sqlite3 模块是 SQLite 数据库库的包装器
# 国际化由许多模块支持，包括 gettext ， locale ，以及 codecs 包。
