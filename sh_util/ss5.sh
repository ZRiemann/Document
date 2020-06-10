#!/bin/bash

yum -y install gcc gcc-c++ automake make pam-devel openldap-devel cyrus-sasl-devel openssl-devel
wget https://ncu.dl.sourceforge.net/project/ss5/ss5/3.8.9-8/ss5-3.8.9-8.tar.gz
tar zxvf ./ss5-3.8.9-8.tar.gz
cd ss5-3.8.9
./configure
make
make install

chmod +x /etc/init.d/ss5

echo "modify /etc/sysconf/ss5/conf"
echo "auth 0.0.0.0/0 - -"
echo "permit - 0.0.0.0/0 - - - - -"
echo "systemctl restart ss5"
echo "systemctl status ss5"