#!/bin/bash

#. ./color-ctl.sh

os_name="os-name-unknown"
get_os_name()
{
    if grep -Eqii "CentOS" /etc/issue || grep -Eq "CentOS" /etc/*-release; then
        os_name='CentOS'
        PM='yum'
    elif grep -Eqi "Red Hat Enterprise Linux Server" /etc/issue || grep -Eq "Red Hat Enterprise Linux Server" /etc/*-release; then
        os_name='RHEL'
        PM='yum'
    elif grep -Eqi "Aliyun" /etc/issue || grep -Eq "Aliyun" /etc/*-release; then
        os_name='Aliyun'
        PM='yum'
    elif grep -Eqi "Fedora" /etc/issue || grep -Eq "Fedora" /etc/*-release; then
        os_name='Fedora'
        PM='yum'
    elif grep -Eqi "Debian" /etc/issue || grep -Eq "Debian" /etc/*-release; then
        os_name='Debian'
        PM='apt'
    elif grep -Eqi "Ubuntu" /etc/issue || grep -Eq "Ubuntu" /etc/*-release; then
        os_name='Ubuntu'
        PM='apt'
    elif grep -Eqi "Raspbian" /etc/issue || grep -Eq "Raspbian" /etc/*-release; then
        os_name='Raspbian'
        PM='apt'
    else
        os_name='unknow'
    fi
    echo_dbg "os_name = ${os_name};"
}
get_os_name

os_task_arg=""

os_task()
{
    if grep -Eqii "CentOS" /etc/issue || grep -Eq "CentOS" /etc/*-release; then
        is_fn TaskCentOS
        [ 0 -eq $? ] && TaskCentOS ${os_task_arg} || echo_war "not support ${os_name}"
    elif grep -Eqi "Red Hat Enterprise Linux Server" /etc/issue || grep -Eq "Red Hat Enterprise Linux Server" /etc/*-release; then
        is_fn TaskRHEL
        [ 0 -eq $? ] && TaskRHEL ${os_task_arg} || echo_war "not support ${os_name}"
    elif grep -Eqi "Aliyun" /etc/issue || grep -Eq "Aliyun" /etc/*-release; then
        is_fn TaskAliyun
        [ 0 -eq $? ] && TaskAliyun ${os_task_arg} || echo_war "not support ${os_name}"
    elif grep -Eqi "Fedora" /etc/issue || grep -Eq "Fedora" /etc/*-release; then
        is_fn TaskFedora
        [ 0 -eq $? ] && TaskFedora ${os_task_arg} || echo_war "not support ${os_name}"

    elif grep -Eqi "Debian" /etc/issue || grep -Eq "Debian" /etc/*-release; then
        is_fn TaskDebian
        [ 0 -eq $? ] && TaskDebian ${os_task_arg} || echo_war "not support ${os_name}"
    elif grep -Eqi "Ubuntu" /etc/issue || grep -Eq "Ubuntu" /etc/*-release; then
        is_fn TaskUbuntu
        [ 0 -eq $? ] && TaskUbuntu ${os_task_arg} || echo_war "not support ${os_name}"
    elif grep -Eqi "Raspbian" /etc/issue || grep -Eq "Raspbian" /etc/*-release; then
        is_fn TaskRaspbian
        [ 0 -eq $? ] && TaskRaspbian ${os_task_arg} || echo_war "not support ${os_name}"
    else
        echo_err "unknown OS"
    fi
}