#!/usr/bin/bash

comment='
$ ./format.sh -a after -b befor VALUE1 "VALUE2 VALUE3" VALUE4
beforVALUE1after
beforVALUE2 VALUE3after
beforVALUE4after
$ ./format.sh -a after -b befor --mark
befor_test_after
$ ./format.sh -a after -b befor --mark="||" -u
BEFOR||TEST||AFTER
$ ./format.sh -a after -b befor --mark="||" -u --help
'

mark=""      # 链接符号
prefix=""    # 前缀
base="test"  # 默认字符串
suffix=""    # 后缀
upper=off    # 是否大写
# 显示声明一下这是个数组变量，其实没有必要
declare -a names  # 须要格式化输出的全部原始字符串
# 打印的帮助信息
help_str="
参数说明：
  -h, --help:           打印帮助信息
  -m, --mark [链接符]:  使用链接符，默认是下划线（_），能够指定
  -a, --after string:   添加后缀
  -b, --befor string:   添加前缀
  -s, --string string:  指定中间的字符串，默认是“test”
  -u, --upper:          全大写输出
"
# 解析命令行参数
getopt_cmd=$(getopt -o m::ha:b:s:u --long mark::,help,after:,befor:,string:,upper -n $(basename $0) -- "$@")
[ $? -ne 0 ] && exit 1
eval set -- "$getopt_cmd"
# 解析选项
while [ -n "$1" ]
do
    case "$1" in
        -m|--mark)
            case "$2" in
                "")
                    mark="_"
                    shift ;;
                *)
                    mark="$2"
                    shift ;;
            esac
            ;;
        -h|--help)
            echo -e "$help_str"
            exit ;;
        -a|--after)
            # 没有处理 -a -b 问题, -b被解释为 -a 的参数
            # 尝试判断参数第一个字符是否为'-'
            suffix="$2"
            shift ;;
        -b|--befor)
            prefix="$2"
            shift ;;
        -s|--string)
            base="$2"
            shift ;;
        -u|--upper)
            upper=on ;;
        --) shift
            break ;;
         *) echo "$1 is not an option"
            exit 1 ;;  # 发现未知参数，直接退出
    esac
    shift
done
# 解析参数
while [ -n "$1" ]
do
    names=("${names[@]}" "$1")
    shift
done
names[0]=${names[0]:-$base}
for name in "${names[@]}"
do
    # 添加前缀和后缀
    output="${prefix:+${prefix}${mark}}${name}${suffix:+${mark}${suffix}}"
    # 判断是否要全大写输出
    if [ $upper = on ]
    then
        output=${output^^}
    fi
    # 输出结果
    echo "$output"
done

exit 0
