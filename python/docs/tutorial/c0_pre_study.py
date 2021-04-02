#!/usr/bin/env python3

# create a Trace object, telling it what to ignore, and whether to
# do tracing or line-counting or both.

def not_call():
    print('not called')

def main():
    print("""span eggs""")
    print('''span eggs''')
    print('doesn\'t')
    print("doesn't")
    print('"Yes," they said')
    print('First line\nSecond line')
    print('C:\some\name')
    print(r'C:\some\name')
    print("""\
    Usage: thingy [OPTIONS]
    -h
    -H host name
    """)
    print(3 * 'un' + 'ium')
    print('Py' 'thon')
    print('Put several string within parentheses '
          'to have them joined together')

    prefix = "Py"
    print(prefix + 'thon')

    prefix += 'thon'
    print(prefix)

    print(prefix[0], prefix[-1])
    print(prefix[0:2], prefix[:2], prefix[2:])

    squares = [1, 4, 9, 16, 25]
    print(squares, squares[:])
    print(squares[0], squares[:3], squares[-3:])
    print(squares + [36, 49, 64, 81, 100])

    cubes = [1, 8, 27, 65555, 125]
    cubes[3] = 4 ** 3 # mutable
    cubes.append(216)
    cubes.append(7 ** 3)
    print(cubes)

    letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
    letters[2:5] = ['C', 'D', 'E']
    print(letters, len(letters))
    letters[2:5] = []
    print(letters, len(letters))
    letters[:] = []
    print(letters, len(letters))

    def fabs(max):
        a, b = 0, 1
        while a < max:
            a, b = b, a+b
            print(a)
    fabs(100)

    print(1, 2, 3, '\n', end=',')


if __name__ == '__main__':
    main()

    """
    import trace
    import sys

    tracer = trace.Trace(
        ignoredirs=[sys.prefix, sys.exec_prefix],
        trace=1,
        count=1,
#        countfuncs=1,
#        countcallers=1,
#        ignoremods=(),
#        infile=None,
#        outfile=None,
        timing=True
    )

    # run the new command using the given tracer
    tracer.run('main()')

    # make a report, placing output in the current directory
    r = tracer.results()
    r.write_results(show_missing=True, summary=True, coverdir=".")
    """