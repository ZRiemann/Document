#!/bin/sh

# enable core dump for current user
#echo ulimit -c unlimited >> ~/.profile
ulimit -c unlimited

# Set core dump file save path
# %p - insert pid into filename 添加 pid
# %u - insert current uid into filename 添加当前 uid
# %g - insert current gid into filename 添加当前 gid
# %s - insert signal that caused the coredump into the filename 添加导致产生 core 的信号
# %t - insert UNIX time that the coredump occurred into filename 添加 core 文件生成时的 unix 时间
# %h - insert hostname where the coredump happened into filename 添加主机名
# %e - insert coredumping executable name into filename 添加命令名
echo /tmp/core-%e-%p-%s-%t > /proc/sys/kernel/core_pattern

echo 1 > /proc/sys/kernel/core_uses_pid

# show current configs
#cat ~/.profile
echo /proc/sys/kernel/core_pattern as fllow:
cat /proc/sys/kernel/core_pattern
cat /proc/sys/kernel/core_uses_pid
echo show all ulimit:
ulimit -a

# useage:
# gdb <exe_name> /tmp/core-*