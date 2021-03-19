#!/usr/bin/python3
#_*_coding: UTF-8_*_

# 11. 标准库简介 —— 第二部分¶
# 专业编程所需要的更高级的模块, 很少用在小脚本中。
# 11.1. 格式化输出¶
# reprlib 模块提供了一个定制化版本的 repr() 函数，用于缩略显示大型或深层嵌套的容器对象:
import reprlib
print(reprlib.repr(set('supercalifragilisticexpialidocious')))
# "{'a', 'c', 'd', 'e', 'f', 'g', ...}"
# pprint 模块提供了更加复杂的打印控制
import pprint
t = [[[['black', 'cyan'], 'white', ['green', 'red']], [['magenta',
    'yellow'], 'blue']]]
pprint.pprint(t, width=30)
# [[[['black', 'cyan'],
#   'white',
#   ['green', 'red']],
#  [['magenta', 'yellow'],
#   'blue']]]
#textwrap 模块能够格式化文本段落，以适应给定的屏幕宽度:
import textwrap
doc = """The wrap() method is just like fill() except that it returns
a list of strings instead of one big string with newlines to separate
the wrapped lines."""

print(textwrap.fill(doc, width=30))
"""
The wrap() method is just like fill()
except that it returns a list of strings
instead of one big string with newlines
to separate the wrapped lines.
"""

# 11.2. 模板¶
# string 模块包含一个通用的 Template 类
from string import Template
t = Template('${village}folk send $$10 to $cause.')
print(t.substitute(village='Nottingham', cause='the ditch fund'))
# 'Nottinghamfolk send $10 to the ditch fund.'

t = Template('Return the $item to $owner.')
d = dict(item='unladen swallow')
#t.substitute(d)
#Traceback (most recent call last):
#  ...
#KeyError: 'owner'
t.safe_substitute(d)
# 'Return the unladen swallow to $owner.'
"""
>>> import time, os.path
>>> photofiles = ['img_1074.jpg', 'img_1076.jpg', 'img_1077.jpg']
>>> class BatchRename(Template):
...     delimiter = '%'
>>> fmt = input('Enter rename style (%d-date %n-seqnum %f-format):  ')
Enter rename style (%d-date %n-seqnum %f-format):  Ashley_%n%f

>>> t = BatchRename(fmt)
>>> date = time.strftime('%d%b%y')
>>> for i, filename in enumerate(photofiles):
...     base, ext = os.path.splitext(filename)
...     newname = t.substitute(d=date, n=i, f=ext)
...     print('{0} --> {1}'.format(filename, newname))
"""

# 11.3. 使用二进制数据记录格式¶
# struct 模块提供了 pack() 和 unpack() 函数，用于处理不定长度的二进制记录格式。

# 11.4. 多线程¶
# 然后使用 queue 模块向该线程供应来自其他线程的请求

# 11.5. 日志记录¶
# logging 模块提供功能齐全且灵活的日志记录系统。在最简单的情况下，日志消息被发送到文件或 sys.stderr
import logging
logging.debug('Debugging information')
logging.info('Informational message')
logging.warning('Warning:config file %s not found', 'server.conf')
logging.error('Error occurred')
logging.critical('Critical error -- shutting down')

# 11.6. 弱引用¶
# 典型应用包括对创建开销较大的对象进行缓存:
import weakref, gc
class A:
    def __init__(self, value):
        self.value = value
    def __repr__(self):
        return str(self.value)

a = A(10)                   # create a reference
d = weakref.WeakValueDictionary()
d['primary'] = a            # does not create a reference
d['primary']                # fetch the object if it is still alive
# 10
del a                       # remove the one reference
gc.collect()                # run garbage collection right away
# 0
d['primary']                # entry was automatically removed
"""
raceback (most recent call last):
  File "<stdin>", line 1, in <module>
    d['primary']                # entry was automatically removed
  File "C:/python38/lib/weakref.py", line 46, in __getitem__
    o = self.data[key]()
KeyError: 'primary'
"""

# 11.7. 用于操作列表的工具¶
# array 模块提供了一种 array() 对象
"""
>>> from array import array
>>> a = array('H', [4000, 10, 700, 22222])
>>> sum(a)
26932
>>> a[1:3]
array('H', [10, 700])
"""
# collections 模块提供了一种 deque() 对象
""">>> from collections import deque
>>> d = deque(["task1", "task2", "task3"])
>>> d.append("task4")
>>> print("Handling", d.popleft())
Handling task1
unsearched = deque([starting_node])
def breadth_first_search(unsearched):
    node = unsearched.popleft()
    for m in gen_moves(node):
        if is_goal(m):
            return m
        unsearched.append(m)
"""
