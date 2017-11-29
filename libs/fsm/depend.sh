fname=$(basename $3)
basename=${fname%.*}

echo "./$4/$basename.d : $3" >> ./$4/makefile.d
echo "	sh ./depend.generic.sh \"$1\" \"$2\" \"$3\" \"$4\" " >> ./$4/makefile.d
echo "" >> ./$4/makefile.d
