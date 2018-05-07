#!/bin/sh

. ./os-name.sh

step=0
# inc_step: x=$(($step + 1))
if [ "${os_name}" = "CentOS" ]; then
    if [ ! -f /usr/bin/mysql ]; then
        down_file=mysql80-community-release-el7-1.noarch.rpm

        step=$(($step + 1))
        echo_inf "${step}. Adding the MySQL Yum Repository"
        wget https://dev.mysql.com/get/${down_file}
        sudo rpm -Uvh ${down_file}

        step=$(($step + 1))
        echo_inf "${step}. Selecting a Release Series"
        # sudo yum repolist all | grep mysql

        step=$(($step + 1))
        echo_inf "${step}. Installing MySQL"
        sudo yum install mysql-community-server

        rm -f ${down_file}
    else
        step=$(($step + 1))
        echo_inf "${step}. MySQL already installed"
    fi

    step=$(($step + 1))
    echo_inf "${step}. Starting the MySQL Server"
    sudo service mysqld start
    sudo service mysqld status

    step=$(($step + 1))
    echo_inf "${step}. Find temporary password, and Change it"
    sudo grep 'password' /var/log/mysqld.log
    echo_inf "mysql -uroot -p<temp-pwd>"
    echo_inf "mysql> set global validate_password.length=0;"
    echo_inf "mysql> set global validate_password.policy=0;"
    echo_inf "mysql> ALTER USER USER() IDENTIFIED BY 'root@mysql';"

    step=$(($step + 1))
    echo_inf "${step}. Install MySQL done."
else
    echo_err "not support os: ${os_name}"
fi
