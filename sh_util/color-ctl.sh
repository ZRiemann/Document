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