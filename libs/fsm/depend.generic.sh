fname=$(basename $3)
basename=${fname%.*}

data=`$1 $2 -MM $3`

debug=
if [ $4 = "debug" ];then
	debug="-g"
else
    debug="-O3"
fi


if [ -z "$data" ];then
	echo "ÒÀÀµÎÄ¼þ¼ì²é´íÎó for $3"
else
	$1 $2 -MM $3 | sed 1,1s/"^"/"\.\/$4\/"/ > ./$4/$basename.d
	echo "	$1 $2 $debug -c \$< -o \$@" >> ./$4/$basename.d
fi
