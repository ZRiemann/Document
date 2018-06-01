#!/bin/sh

cmd_dir=$(pwd)
# cd work-dir
cd ${0%/*}
cd ..

. ./color-ctl.sh
. ./os-name.sh

make_ceph_repo(){
    ceph_repo="ceph.repo"
    [ -f /etc/yum.repos.d/${ceph_repo} ] && return 0

    echo_inf "make ceph.repo"
    touch ${ceph_repo}
cat <<!CEPH_ERPO! > ${ceph_repo}
[ceph-noarch]
name=Ceph noarch packages
baseurl=http://download.ceph.com/rpm-mimic/el7/noarch
enabled=1
gpgcheck=1
type=rpm-md
gpgkey=https://download.ceph.com/keys/release.asc
!CEPH_ERPO!
    sudo mv ${ceph_repo} /etc/yum.repos.d/
}

install_ceph_node(){
    echo_inf "2. install ceph node."

    echo_inf "2.1 install NTP"
    sudo yum install ntp ntpdate ntp-doc

    echo_inf "2.2 install SSH Server"
    sudo yum install openssh-server

    echo_inf "2.3 Create and deploy ceph user (no pwd and sudo permission)"
    # ceph-deploy --username {username}
    username="zceph"
    echo_inf "2.3.1 Create new user ${username}"
    sudo useradd -d /home/${username} -m ${username}
    sudo passwd ${username}

    echo_inf "2.3.2 config ${username} has sudo permission"
    echo "${username} ALL = (root) NOPASSWD:ALL" | sudo tee /etc/sudoers.d/${username}
    sudo chmod 0440 /etc/sudoers.d/${username}

    echo_inf "2.3.2 Config login SSH with no password"
    ssh_file="~/.ssh/id_rsa"
    echo_inf "2.3.2.1 Generate key"
    echo_inf "      file-to-save: ${ssh_file}"
    echo_inf "      passphrase: (empty for no passphrase)"
    echo_inf "      identification: ${ssh_file}."
    echo_inf "      public key: ${ssh_file}.pub."
    ssh-keygen

    echo_inf "2.3.2.2 Copy public key to nodes"
    echo_inf "        ssh-copy-id ${username}@<nodenames>"

    echo_inf "2.3.2.3 Update ~/.ssh/config"
    echo_msg "        Host node1"
    echo_msg "          Hostname node1"
    echo_msg "          User ${username}"

    echo_inf "3.4 Connect network on boot"
    echo_msg "    /etc/sysconfig/network-scripts/ifcfg-{iface} ONBOOT = yes"

    echo_inf "3.5 Make sure host on line"
    echo_msg "    ping {hostname}"

    echo_inf "3.6 Open network port"
    echo_msg "    Ceph Monitors: 6789"
    echo_msg "    OSD: 6800-7300"
    echo_msg "    see: http://docs.ceph.org.cn/rados/configuration/network-config-ref/"
    echo_msg "    sudo firewall-cmd --zone=public --add-port=6789/tcp --permanent"
    sudo firewall-cmd --zone=public --add-port=6789/tcp --permanent

    echo_inf "3.7 TTY configure"
    echo_msg "    sudo visud /etc/suders Defaults:ceph !requiretty"

    echo_inf "3.8 SELINUX"
    echo_msg "    /etc/selinux/config
    echo_msg "    sudo setenvorce 0"

    echo_inf "3.9 Priority / preference"
    sudo yum install yum-plugin-priorities
    sudo yum install yum-plugin-priorities --enablerepo=rhel-7-server-optional-rpms
}
TaskCentOS()
{
    echo_msg "Start install ceph on CentOS..."

    echo_inf "1. prepare install"
    sudo yum install -y yum-utils
    sudo yum-config-manager --add-repo https://dl.fedoraproject.org/pub/epel/7/x86_64/
    sudo yum install --nogpgcheck -y epel-release
    sudo rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-7
    sudo rm /etc/yum.repos.d/dl.fedoraproject.org*

    make_ceph_repo

    echo_inf "1.1 update and install ceph_deploy"
    sudo yum update
    sudo yum install ceph-deploy
    echo_msg "ceph install done. "

    install_ceph_node
}

os_task

cd ${cmd_dir}
exit 0