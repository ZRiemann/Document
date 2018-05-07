#!/bin/sh

. ../color-ctl.sh

file=v1.1.0.zip
dest_dir=rapidjson-1.1.0
install_dir=/usr/local/include
wget https://github.com/Tencent/rapidjson/archive/${file}
unzip -q ${file}
sudo cp -r ${dest_dir}/include/rapidjson ${install_dir}
rm -fr ${dest_dir} ${file}
echo_g "${dest_dir} install at: ${install_dir}"

exit 0