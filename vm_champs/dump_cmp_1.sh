#!/bin/sh

if [ -z $1 ] || [ -z $2 ] || [ -z $3 ]
then
	echo "usage: \x1b[33mPrécisez un dump, un pas puis au moins un champion"
	exit
elif [ -f $1 ] || [ -f $2 ]
then
	echo "usage: \x1b[33mPrecisez un dump de départ et un pas d'incrémentation"
	exit
else
	dump=$1
	step=$2
	while [ $dump ]
	do
		echo "\x1b[33m" $dump "\x1b[39m"
		./corewar -d $dump $3 $4 $5 $6 > dump_zaz.txt
		../corewar/corewar -d $dump $3 $4 $5 $6 > dump_team.txt
		diff dump_zaz.txt dump_team.txt
		dump=$((dump+step))
	done
fi
