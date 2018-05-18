#!/bin/sh

state=0
from="GB2312"
to="UTF-8"

# conv-txt -f GB2312 -t UTF-8 file-name1 [file-name2 ...]

[ $# -le 4 ] || [ "-f" != $1 -a "-t" != $3 ] && {
    echo "usage: conv-txt -f GB2312 -t UTF-8 file-name1 [file-name2 ...]"
    echo "format list see <iconv --list>"
    exit 1

}

from=$2
to=$4

shift
shift
shift
shift


for var in "${@}"; do
    echo "${var}"
    iconv -f ${from} -t ${to} ${var} -o ${var}.conv
    [ 0 -eq $? ] && mv ${var}.conv ${var} || rm -f ${var}.conv
done

exit 0