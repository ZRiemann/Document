#!/bin/bash

if [ "1" != "$#" ]; then
    echo "usage $0 <bin-name>"
    exit 1
fi

BIN_NAME=$1

echo "strip $BIN_NAME symbol (gcc -g)"
echo "needs gcc -g floag"
echo "needs open core dump, @see core_dump.sh"

objcopy --only-keep-debug ${BIN_NAME} ${BIN_NAME}.symbol
objcopy --strip-debug ${BIN_NAME} ${BIN_NAME}.out

echo "gdb -e ${BIN_NAME}.out -s ${BIN_NAME}.symbol -c <core-dump>"
exit 0
