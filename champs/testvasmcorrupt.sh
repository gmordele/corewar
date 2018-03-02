#!/bin/sh

RED='\033[0;31m'
GREEN='\033[0;32m'
DEFAULT='\033[0;37m'

CORRUPTDIR='svcorrupt'

noleak=$(valgrind ./dum 2>&1 | grep lost | cut -c 14-)

while :
do
	rm -rf $CORRUPTDIR
	cp -rf s $CORRUPTDIR
	python3 ./corrupt.py $CORRUPTDIR/*.s
	for file in $CORRUPTDIR/*
	do
		leak=$(valgrind ../asm/asm $file 2>&1 1>& -| grep lost | cut -c 14-)
 		if [ "$leak" == "$noleak"  ]
 		then
 			echo "$GREEN $file $DEFAULT"
 		else
 			echo "$RED $file"
			echo "$leak $DEFAULT"
 			exit
 		fi
	done
done