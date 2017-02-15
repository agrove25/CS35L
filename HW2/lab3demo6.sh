#!/bin/sh

IFS=$'/'

file_list=`find -maxdepth 1 -type f | sed "s/.\//\//g" | sed "s/\n//g"`
echo $file_list

for i in `find -maxdepth 1 -type f | sed "s/.\//\//g"`
do
    i=`echo $i | sed "s/'\n$'//"`
    stat "$i";

done
