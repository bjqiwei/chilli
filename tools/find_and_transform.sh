#!/bin/sh

#!/bin/sh
#ext="pcap"
function ergodic(){
echo "开始扫描目录 $1"
for file in ` ls $1`
do
    if [ -d $1"/"$file ] 
    then
        ergodic $1"/"$file
    else
        local path=$1"/"$file 

 
        echo "开始转换 $path"
        dos2unix  "$path"
    fi

done
}

ergodic $1



