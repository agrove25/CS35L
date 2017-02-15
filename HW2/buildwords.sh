#!/bin/sh

cat $1 | grep td | sed "s/<[^>]*>//g" | sed 's/^ *//;s/*$//' | grep . | sed -n 'n;p' | sed '1,2d' | sed "s/\`/\'/g" | tr '[:upper:]' '[:lower:]' | grep -v [^pk\'mnwlhaeiou\ ] | sed "s/[^pk\'mnwlhaeiou]/\n/g" | grep . | sort -u
