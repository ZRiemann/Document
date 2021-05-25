from time import time,ctime

def ext_add(a, b):
        return a + b

def multiply(a,b):
    print("Will compute", a, "times", b)
    c = 0
    for i in range(0, a):
        c = c + b
    return c

if __name__ == '__main__':
        print('Today is', ctime(time()), ext_add(1, 1), multiply(3,4))