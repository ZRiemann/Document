#!/bin/sh

cmd_dir=$(pwd)
# cd work-dir
cd ${0%/*}
cd ..

. ./color-ctl.sh

# admin-node   ----------> node1
# ceph-deploy   |          mon.node1
#               |
#               |--------> node2
#               |          osd.0
#               |
#               \--------> node3
#                          osd.1
#

cluster_dir="my-cluster"
echo_msg "mkdir ${cluster_dir} && cd ${cluster_dir}"
mkdir ${cluster_dir}
cd ${cluster_dir}

echo_msg "1. Create cluster"
echo_msg "1.1 Clear old cluster config"
node_name="nodename"
ceph-deploy purgedata ${node_name} [${node_name}]
ceph-deploy forgetkeys

echo_msg "1.1.1 uninstall ceph-deploy"
echo_inf "    ceph-deploy purge ${node_name} [${node_name}]"


echo_msg "1.2 Create cluster ${node_name}"
ceph-deploy new ${node_name}

echo_msg "1.3 Change config"
echo_inf "    config_file: osd pool default size = 2"

echo_msg "1.4 Config net work"
echo_inf "    config_file: public network={ip-address}/{netmask}"

echo_msg "1.5 Install ceph"
echo_inf "    ceph-deploy install ${node_name} [${nodes}...]"

echo_msg "1.6 Config monitor(s) and collect keys"
echo_inf "    ceph-deploy mon create-initial"

echo_msg "2. Add OSDs"

echo_inf "2.1 Make OSDs dir"
echo_inf "   ssh node2"
echo_inf "   sudo mkdir /var/local/osd0"
echo_inf "   exit"
echo_inf "   ssh node3"
echo_inf "   sudo mkdir /var/local/osd1"
echo_inf "   exit"

echo_msg "2.1 Prepare OSDs"
echo_inf "    ceph-deploy osd prepare {ceph-node}:/path/to/directory"
echo_inf "    ceph-deploy osd prepare node2:/var/local/osd0 node3:/var/local/osd1"

echo_msg "2.2 Activate OSDs"
echo_inf "    ceph-deploy osd activate {ceph-node}:/path/to/directory"
echo_inf "    ceph-deploy osd activate node2:/var/local/osd0 node3:/var/local/osd1"

echo_msg "2.3 Copy config files and admin key to monitor and nodes"
echo_msg "    brief: avoid enter monitor address and ceph.client.admin.keyring"
echo_inf "    ceph-deploy admin {admin-node} {ceph-node}"
echo_inf "    ceph-deploy admin admin-node node1 node2 node3"

echo_msg "2.4 Make sure keyring readable"
echo_inf "    sudo chmod +r /etc/ceph/ceph.client.admin.keyring"

echo_msg "2.5 Check ceph health"
echo_inf "    ceph health"
echo_msg "    after peering, cluster get active + clean status"


echo_msg "3. Cluster operater"
echo_msg "   Ubuntu: http://docs.ceph.org.cn/rados/operations/operating#rupstart-ceph"
echo_msg "   CentOS: http://docs.ceph.org.cn/rados/operations/operating/#sysvinit-ceph"
echo_msg "   peering: http://docs.ceph.org.cn/rados/operations/monitoring/"

echo_msg "4. Cluster Extern"
# ceph-deploy -------------> node1
# Admin Node   |             mon.node1
#              |             osd.2
#              |             mds.node1
#              |
#              |-----------> node2
#              |             osd.0
#              |             mon.node2
#              |
#              \-----------> node3
#                            osd.1
#                            mon.node3
cd ${cmd_dir}
exit 0