#!/bin/sh

cmd_dir=$(pwd)
# cd work-dir
cd ${0%/*}

. ./os-name.sh

if [ "${os_name}" = "CentOS" ]; then
    init 5
else
    echo_err "not support os: ${os_name}"
fi

cd ${cmd_dir}
exit 0