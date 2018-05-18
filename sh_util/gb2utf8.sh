#!/bin/sh

for var in "${@}"; do
    echo "${var}"
    iconv -f GB2312 -t UTF-8 ${var} -o ${var}.u8
    mv ${var}.u8 ${var}
done

exit 0