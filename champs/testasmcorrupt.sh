#!/bin/sh

RED='\033[0;31m'
GREEN='\033[0;32m'
DEFAULT='\033[0;37m'

CORRUPTDIR='scorrupt'

while :
do
	rm -rf $CORRUPTDIR
	cp -rf s $CORRUPTDIR
	python3 ./corrupt.py $CORRUPTDIR/*.s
	for file in $CORRUPTDIR/*
	do
		../asm/asm $file 1>&- 2>&-
		ret=$?
		if [ $ret == 0 -o $ret == 1 ]
		then
			echo "$GREEN $file $ret $DEFAULT"
		else
			echo "$RED $file $ret $DEFAULT"
			exit
		fi
	done
done