#!/usr/bin/env python3

import multiprocessing as mp

def foo(q):
    q.put('hello')

def use_set_start_method():
    """
    Only support one method and be set once.
    """
    mp.set_start_method('spawn')
    q = mp.Queue()
    p = mp.Process(target=foo, args=(q,))
    p.start()
    print(q.get())
    p.join()

def use_get_context():
    """
    Support many different method by different context
    """
    ctx = mp.get_context('fork')
    q = ctx.Queue()
    p = ctx.Process(target=foo, args=(q,))

    ctx1 = mp.get_context('spawn')
    q1 = ctx1.Queue()
    p1 = ctx1.Process(target=foo, args=(q1,))

    p.start()
    p1.start()
    print(q.get())
    print(q1.get())
    p1.join()
    p.join()

if __name__ == '__main__':
    use_get_context()
#    use_set_start_method()

