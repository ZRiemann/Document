#!/usr/bin/bash

"""
python -m timeit [-n N] [-r N] [-u U] [-s S] [-h] [statement ...]
如果了解以下选项：

-n N, --number=N
执行 '语句' 多少次

-r N, --repeat=N
重复计时器的次数（默认为5）

-s S, --setup=S
最初要执行一次的语句（默认为 pass ）

-p, --process
测量进程时间，而不是 wallclock 时间，使用 time.process_time() 而不是 time.perf_counter() ，这是默认值

3.3 新版功能.

-u, --unit=U
指定定时器输出的时间单位；可以选择 nsec，usec，msec或sec

3.5 新版功能.

-v, --verbose
打印原始计时结果；重复更多位数精度

-h, --help
打印一条简短的使用信息并退出

可以通过将每一行指定为单独的语句参数来给出多行语句；通过在引号中包含参数并使用前导空格可以缩进行。多个 -s 选项的处理方式相似。

如果未给出 -n，则会通过尝试按序列 1, 2, 5, 10, 20, 50, ... 递增的数值来计算合适的循环次数，直到总计时间至少为 0.2 秒。

default_timer() 测量可能受到在同一台机器上运行的其他程序的影响，因此在需要精确计时时最好的做法是重复几次计时并使用最佳时间。 -r 选项对此有利；在大多数情况下，默认的 5 次重复可能就足够了。 你可以使用 time.process_time() 来测量CPU时间。

注解 执行 pass 语句会产生一定的基线开销。这里的代码不会试图隐藏它，但你应该知道它。可以通过不带参数调用程序来测量基线开销，并且Python版本之间可能会有所不同。
例子
可以提供一个在开头只执行一次的 setup 语句：

$ python -m timeit -s 'text = "sample string"; char = "g"'  'char in text'
5000000 loops, best of 5: 0.0877 usec per loop
$ python -m timeit -s 'text = "sample string"; char = "g"'  'text.find(char)'
1000000 loops, best of 5: 0.342 usec per loop
>>>
>>> import timeit
>>> timeit.timeit('char in text', setup='text = "sample string"; char = "g"')
0.41440500499993504
>>> timeit.timeit('text.find(char)', setup='text = "sample string"; char = "g"')
1.7246671520006203
使用 Timer 类及其方法可以完成同样的操作:

>>>
>>> import timeit
>>> t = timeit.Timer('char in text', setup='text = "sample string"; char = "g"')
>>> t.timeit()
0.3955516149999312
>>> t.repeat()
[0.40183617287970225, 0.37027556854118704, 0.38344867356679524, 0.3712595970846668, 0.37866875250654886]
以下示例显示如何计算包含多行的
"""

python3 -m timeit $@