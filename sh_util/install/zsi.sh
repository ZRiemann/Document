#!/bin/sh

. ../color-ctl.sh

down_file=master.zip
source_dir=zsi-master

echo_p "1. Down load ${down_file}"
wget https://github.com/ZRiemann/zsi/archive/${down_file}
unzip -q ${down_file}

echo_p "2. Build zsi and install"
cd ${source_dir}
./configure
make -j4
sudo make install
cd -

rm -fr ${source_dir} ${down_file}
echo_p "3. Install zsi OK."