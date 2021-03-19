#!/usr/bin/env python3

# create a Trace object, telling it what to ignore, and whether to
# do tracing or line-counting or both.

def not_call():
    print('not called')

def main():
    print('main')
    result = 3 + 4
    print(result)

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