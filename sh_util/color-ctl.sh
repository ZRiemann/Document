# linux shell color control
# cl_: color_
# r: red; g: green; b: blue y: yellow; p: purple
# c: close color control
# echo -e "${cl_r}echo red color${cl_c}"
cl_r="\\033[31m"
cl_g="\\033[32m"
cl_y="\\033[33m"
cl_b="\\033[34m"
cl_p="\\033[35m"
cl_c="\\033[0m"

echo_r(){
    echo -e "${cl_r}$*${cl_c}"
}
#echo_r red "RED"

echo_g(){
    echo -e "${cl_g}$*${cl_c}"
}
#echo_g red "RED"

echo_y(){
    echo -e "${cl_y}$*${cl_c}"
}
#echo_y red "RED"

echo_b(){
    echo -e "${cl_b}$*${cl_c}"
}
#echo_b red "RED"

echo_p(){
    echo -e "${cl_p}$*${cl_c}"
}
#echo_p red "RED"
enable_dbg=1
#set -x
#set -xv

echo_dbg(){
    [ 1 -eq $enable_dbg ] &&echo -e "${cl_b}$*${cl_c}"
}
echo_inf(){
    echo -e "${cl_p}$*${cl_c}"
}
echo_msg(){
    echo -e "${cl_b}$*${cl_c}"
}

echo_val(){
    echo -e "${cl_g}$*${cl_c}"
}

echo_war(){
    echo -e "${cl_y}$*${cl_c}"
}

echo_err(){
    echo -e "${cl_r}$*${cl_c}"
}

is_fn(){
    if [ "$(type -t $1)" = "function" ]; then
        echo_dbg "$1 is function"
        return 0
    else
        echo_dbg "$1 is not function"
        return 1
    fi
}

get_public_ip(){
    # Get public IP address
    public_ip=$(ip addr | egrep -o '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' | egrep -v "^192\.168|^172\.1[6-9]\.|^172\.2[0-9]\.|^172\.3[0-2]\.|^10\.|^127\.|^255\.|^0\." | head -n 1)
    if [[ "$IP" = "" ]]; then
        public_ip=$(wget -qO- -t1 -T2 ipv4.icanhazip.com)
    fi
    echo_dbg "Get public IP: ${public_ip}"
}

rootness(){
    if [[ $EUID -ne 0 ]]; then
       echo "Error:This script must be run as root!" 1>&2
       exit 1
    fi
}

disable_selinux(){
if [ -s /etc/selinux/config ] && grep 'SELINUX=enforcing' /etc/selinux/config; then
    sed -i 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/selinux/config
    setenforce 0
fi
}
