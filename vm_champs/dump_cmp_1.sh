#!/bin/sh

if [ -f $1 ]
then
	echo "usage: \x1b[33mPrecisez un dump de départ"
	exit
elif [ -z $2 ]
then
	echo "usage: \x1b[33mPrécisez un champion en deuxième paramètre"
	exit
else
	dump=$1
	while [ $dump ]
	do
		echo "\x1b[33m" $dump "\x1b[39m"
		./corewar -d $dump $2 $3 $4 $5 > dump_zaz.txt
		../corewar/corewar -d $dump $2 $3 $4 $5 > dump_team.txt
		diff dump_zaz.txt dump_team.txt
		dump=$((dump+10))
	done
fi
