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
	while [ 1 ]
	do
#		echo "\x1b[36m" $dump "\x1b[39m"
		if [ $((dump % ($step * 10))) -eq 0 ]
			then
			#echo "\x1b[2K$3 $4 $5 $6 $dump\x1b[A"
			echo "\x1b[2K \x1b[32m$dump\x1b[39m\x1b[A"
		fi
		zaz=`./corewar -d $dump $3 $4 $5 $6`
		team=`../corewar/corewar -d $dump $3 $4 $5 $6`
		if [ "$zaz" != "$team" ]
			then
			echo "\x1b[2K\x1b[31m$dump\x1b[39m"
			echo "$zaz" > dump_zaz.txt
			echo "$team" > dump_team.txt
			diff dump_zaz.txt dump_team.txt
			exit
		fi
		dump=$(($dump+$step))
	done
fi
