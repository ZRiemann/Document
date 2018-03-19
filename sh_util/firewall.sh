#!/bin/bash

# CentOS 7.x 防火墙命令
# 列出防火墙是否开启
echo "firewall state:"
firewall-cmd --state

# 启动防火墙
# systemctl start firewalld
# systemctl stop firewalld.service

# 查看已经开启的端口
echo "list ports:"
firewall-cmd --list-ports

# 添加新端口
#            公共域        开启1985/tcp端口    永久有效
#                          区间1900-2000/tcp
#firewall-cmd --zone=public --add-port=1985/tcp --permanent
firewall-cmd --zone=public --add-port=19350/tcp --permanent
#firewall-cmd --zone=public --add-port=9935/tcp --permanent
# 关闭端口
#firewall-cmd --zone=public --remove-port=1985/tcp --permanent

# 重启防火墙
echo "reload firewall."
firewall-cmd --reload

echo "list ports:"
firewall-cmd --list-ports
