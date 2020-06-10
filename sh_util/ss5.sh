#!/bin/bash

version=ss5-3.8.9
yum -y install gcc gcc-c++ automake make pam-devel openldap-devel cyrus-sasl-devel openssl-devel
cd /tmp
wget https://nchc.dl.sourceforge.net/project/ss5/ss5/3.8.9-8/ss5-3.8.9-8.tar.gz
tar zxvf ./${version}.tar.gz
cd ${version}
./configure
make
make install
chmod +x /etc/init.d/ss5
cd -

echo "
vi /etc/sysconfig/ss5  
SS5_OPTS=" -u root -b 0.0.0.0:18080" #绑定端口为18080
systemctl start ss5 #启动服务

#增加用户登录权限
vi /etc/opt/ss5/ss5.conf  
auth 0.0.0.0/0 - u  
permit u 0.0.0.0/0 - 0.0.0.0/0 - - - - -

#设置用户名和密码，一个用户和密码一行，用空格间隔
vi /etc/opt/ss5/ss5.passwd  
user1 123456
user2 123456
"