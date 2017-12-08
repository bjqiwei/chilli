fname=$(basename $3)
basename=${fname%.*}

data=`$1 $2 -MM $3`

debug=
if [ $4 = "debug" ];then
	debug="-O0 -g"
else
    debug="-O0 -g"
fi


if [ -z "$data" ];then
	echo "依赖文件检查错误 for $3"
else
	$1 $2 -MM $3 | sed 1,1s/"^"/"\.\/$4\/"/ > ./$4/$basename.d
	echo "	$1 $2 $debug -c \$< -o \$@" >> ./$4/$basename.d
fi
