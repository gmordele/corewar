#!/bin/sh

if [ -z $1 ] || [ -z $2 ] || [ -f $1 ]
then
	echo "usage: \x1b[33mPrécisez un dump puis au moins un champion"
	exit
else
	echo "\x1b[33m" $1 "\x1b[39m"
	./corewar -d $1 $2 $3 $4 $5> dump_zaz.txt
	../corewar/corewar -d $1 $2 $3 $4 $5 > dump_team.txt
	diff dump_zaz.txt dump_team.txt
fi
