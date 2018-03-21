#!/bin/sh

# Copyright (C) 1996-2007 Wiley Publish Inc.
# GPL License

##################################################
# 需求
# 管理大量CD唱片
# 信息：名称、类型、艺术家名字、曲目信息

###################################################
# 设计
# 基于文本格式存放
# 功能：更新、检索、显示
# 决策1：标题信息、曲目信息分开成2根文件
# 决策2：标题信息
#        唱片目录编号
#        标题
#        曲目类型（古典、摇滚、流行、爵士等）
#        艺术家
#
#        曲目信息
#        曲目编号
#        曲名
# 决策3：使用 , 分隔数据项
#
# 样本数据
# CD123        Coll sax       jazz        Bix
# CD234        Classic violin classical   Bach
# CD345        Hits99         pop         Varous
#
# CD123        1              Some jazz
# CD123        2              More jazz
# CD234        1              Sonata in D minor
# CD345        1              Dizzy

###################################################
# 代码
# 函数概览
# get_return()  ;获取回车
# get_confirm() ;获取确认 y/n
# set_menu_choice()
# insert_title() ; 向数据库文件添加目录
# insert_track() ; 向数据库文件添加曲目(音轨)
# add_record_tracks() ; 添加曲目，模式匹配确保数据项没有 , 分隔符
# add_records() ;添加CD
# find_cd()
# update_cd()
# remove_records()
# list_tracks()

# 设置全局变量
menu_choice=""
current_cd=""
cdcatnum=""
title_file="title.cdb"
tracks_file="tracks.cdb"
# $$ 获取进程号
temp_file=/tmp/cdb.$$


# 信号处理
trap 'rm -f $temp_file' EXIT INT

# 定义函数
get_return(){
    echo -e "Press return \c"
    read x
    return 0
}
# get_return

get_confirm(){
    echo -e "Are you sure? \c"
    while :;do
        read x
        case "$x" in
            [Yy]*)
                return 0;;
            [Nn]*)
                echo
                echo "Cancelled"
                return 1;;
            *)
                echo "Please enter yes or no.";;
        esac
    done
}
# get_confirm

set_menu_choice(){
    clear
    echo "Options :-"
    echo
    echo "  a) Add new CD"
    echo "  f) Find CD"
    echo "  c) Count the CDs and tracks in the catalog"
    if [ "$cdcatnum" != "" ]; then
        echo "  l) List tracks on $cdtitle"
        echo "  r) Remove $cdtitle"
        echo "  u) Update track information for $cdtitle"
    fi
    echo "  D) delete all data"
    echo "  q) Quit"
    echo
    echo -e "Please enter choice then press return \c"
    read menu_choice
    return
}
# set_menu_choice
# echo $menu_choice

insert_title(){
    echo $* >> $title_file
    return
}
#insert_title title,title1,title2

insert_track(){
    echo $* >> $tracks_file
    return
}
#insert_track track1,trace2,track3

add_record_tracks(){
    echo "Enter track information for this CD"
    echo "When no more tracks enter [q]"
    cdtrack=1
    cdtitle=""

    while [ "$cdtitle" != "q" ]; do
        echo -e "Track $cdtrack, track title? \c"
        read tmp
        # 过滤 ,* 保留头部部分
        cdtitle=${tmp%%,*}
        if [ "$tmp" != "$cdtitle" ]; then
            # 包含 , 提示错误信息，等待下次输入
            echo "Sorry, no commas allowed."
            continue
        fi
        if [ -n "$cdtitle" ]; then
            if [ "$cdtitle" != "q" ]; then
                insert_track $cdcatnum,$cdtrack,$cdtitle
            fi
        else
            # 计算表达式
            cdtrack=$((cdtrack-1))
        fi
        cdtrack=$((cdtrack+1))
    done
}

add_records(){
    # Prompt for the initial infomation
    echo -e "Enter catalog name \c"
    read tmp
    cdcatnum=${tmp%%,*}

    echo -e "Enter title name \c"
    read tmp
    cdtitle=${tmp%%,*}

    echo -e "Enter type \c"
    read tmp
    cdtype=${tmp%%,*}

    echo -e "Enter artist/composer \c"
    read tmp
    cdac=${tmp%%,*}

    # Check that they want to enter the infomation
    echo "Abort to add new entry:"
    echo "$cdcatnum $cdtitle $cdtype $cdac"

    # If confirmed then append it to the title file
    if get_confirm ; then
        insert_title $cdcatnum,$cdtitle,$cdtype,$cdac
        add_record_tracks
    else
        remote_records
    fi
    return
}
#add_records

find_cd(){
    if [ "$1" = "n" ]; then
        asklist=n
    else
        asklist=y
    fi

    cdcatnum=""
    echo -e "Enter a string to search for in the cd titles :\c"
    read searchstr
    if [ "$searchstr" = "" ]; then
        return 0
    fi

    grep "$searchstr" $title_file > $temp_file

    set $(wc -l $temp_file)
    linesfound=$1

    case "$linesfound" in
        0)
            echo "Sorry, nothing found"
            get_return
            return 0;;
        1)  ;;
        2)
            echo "Sorry, not unique."
            echo "Found the following"
            cat $temp_file
            get_return
            return 0
    esac

    #设置 , 分隔符
    ifs=$IFS
    IFS=","
    read cdcatnum cdtitle cdtype cdac < $temp_file
    IFS=ifs

    if [ -z "$cdcatnum" ]; then
        echo "Sorry, could not extract catalog field from $temp_file"
        get_return
        return 0
    fi

    echo
    echo "Catalog number: $cdcatnum"
    echo "Title: $cdtitle"
    echo "Type: $cdtype"
    echo "Artist/Composer: $cdac"
    echo
    get_return

    if [ "$asklist" = "y" ]; then
        echo -e "View tracks fro this CD? \c"
        read readed
        if [ "$readed" = "y" ]; then
            echo
            list_tracks
            echo
        fi
    fi
    return 0
}

update_cd(){
    if [ -z "cdcatnum" ]; then
        echo "You must select a CD first"
        find_cd n
    fi

    if [ -n "cdcatnum" ]; then
        echo "Current tracks are:-"
        list_tracks
        echo
        echo "This will re-enter the tracks for $cdtitle"
        get_confirm && {
            grep -v "^${cdcatnum}," $tracks_file > $temp_file
            mv $temp_file $tracks_file
            echo
            add_record_tracks
        }
    fi
    return
}

count_cds(){
    set $(wc -l $title_file)
    num_titles=$1
    set $(wc -l $tracks_file)
    num_tracks=$1
    echo "found $num_titles CDs, with a total of $num_tracks tracks"
    get_return
    return
}

remote_records(){
    if [ -z "cdcatnum" ]; then
        echo "You mast select a CD first"
        find_cd n
    fi

    if [ -n "cdcatnum" ]; then
        echo "You are about to delete $cdtitle"
        get_confirm && {
            grep -v "^${cdcatnum}," $title_file > $temp_file
            mv $temp_file $title_file
            grep -v "^${cdcatnum}," $stracks_file > $temp_file
            mv $temp_file $tracks_file
            cdcatnum=""
            echo Entry removed
        }
        get_return
    fi
    return
}

list_tracks(){
    if [ "$cdcatnum" = "" ]; then
        echo "no CD selected yet"
    else
        grep "^${cdcatnum}," $tracks_file > $temp_file
        num_tracks=$(wc -l $temp_file)
        if [ "$num_tracks" = "0" ]; then
            echo "no tracks found for $cdtitle"
        else {
            echo
            echo "$cdtitle:-"
            echo
            cut -f 2- -d , $temp_file
            echo
        } | ${PAGER:-more}
        fi
    fi
    get_return
    return
}

# main entry
rm -f $temp_file
if [ ! -f $title_file ]; then
    touch $title_file
fi
if [ ! -f $tracks_file ]; then
    touch $tracks_file
fi

clear
echo
echo
echo "Mini CD manager"
sleep 1

quit=n
while [ "$quit" != "y" ]; do
    set_menu_choice
    case "$menu_choice" in
        a)  add_records;;
        r) remove_records;;
        f) find_cd y;;
        u) update_cd;;
        c) count_cds;;
        l) list_tracks;;
        b) echo
           more $title_file
           echo
           get_return;;
        q | Q) quit=y;;
        *) echo "Sorry, choice not recognized";;
    esac
done

# Tidy up de leave

rm -f $temp_file
echo "CD Manager Finished"

exit 0
