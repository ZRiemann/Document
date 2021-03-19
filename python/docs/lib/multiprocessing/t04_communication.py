#!/usr/bin/env python3

from multiprocessing import Process, Queue, Pipe

def f(queue_1, pipe_cli):
    queue_1.put([42, None, 'hello'])
    pipe_cli.send(['a', 0, None])
    pipe_cli.close()

if __name__ == '__main__':
    q = Queue()
    pipe_svr, pipe_cli = Pipe()
    p = Process(target=f, args=(q,pipe_cli,))
    p.start()
    print(q.get())
    print(pipe_svr.recv())
    p.join()
    pipe_svr.close()

