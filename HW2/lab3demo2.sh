#!/bin/sh
i=2
j=1

while [ $j -le 10 ] && [ $j -le 5 ]
do
    echo '2 **' $j = $i
    i=`expr $i '*' 2`
    j=`expr $j + 1`
done
