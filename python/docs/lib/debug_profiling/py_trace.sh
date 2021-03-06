#!/usr/bin/bash

python3 -m trace -ctmgs -C . $@

doc='
Command-Line Usage
The trace module can be invoked from the command line. It can be as simple as

python -m trace --count -C . somefile.py ...
The above will execute somefile.py and generate annotated listings of all Python modules imported during the execution into the current directory.

--help
Display usage and exit.

--version
Display the version of the module and exit.

3.8 新版功能: Added --module option that allows to run an executable module.

Main options
At least one of the following options must be specified when invoking trace. The --listfuncs option is mutually exclusive with the --trace and --count options. When --listfuncs is provided, neither --count nor --trace are accepted, and vice versa.

-c, --count
Produce a set of annotated listing files upon program completion that shows how many times each statement was executed. See also --coverdir, --file and --no-report below.

-t, --trace
Display lines as they are executed.

-l, --listfuncs
Display the functions executed by running the program.

-r, --report
Produce an annotated list from an earlier program run that used the --count and --file option. This does not execute any code.

-T, --trackcalls
Display the calling relationships exposed by running the program.

Modifiers
-f, --file=<file>
Name of a file to accumulate counts over several tracing runs. Should be used with the --count option.

-C, --coverdir=<dir>
Directory where the report files go. The coverage report for package.module is written to file dir/package/module.cover.

-m, --missing
When generating annotated listings, mark lines which were not executed with >>>>>>.

-s, --summary
When using --count or --report, write a brief summary to stdout for each file processed.

-R, --no-report
Do not generate annotated listings. This is useful if you intend to make several runs with --count, and then produce a single set of annotated listings at the end.

-g, --timing
Prefix each line with the time since the program started. Only used while tracing.

Filters
These options may be repeated multiple times.

--ignore-module=<mod>
Ignore each of the given module names and its submodules (if it is a package). The argument can be a list of names separated by a comma.

--ignore-dir=<dir>
Ignore all modules and packages in the named directory and subdirectories. The argument can be a list of directories separated by os.pathsep.
'
