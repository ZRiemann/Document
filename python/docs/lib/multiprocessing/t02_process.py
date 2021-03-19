#!/usr/bin/env python3

import os

from multiprocessing import Process

def f(name):
    info('function f()')
    print('hello', name)

def info(title):
    print(title)
    print('module name:', __name__)
    print('parent process:', os.getppid())
    print('process id:', os.getpid())

if __name__ == '__main__':
    info('main line')
    p = Process(target = f, args = ('bob',))
    p.start()
    p.join()