#!/bin/sh

if [ -n $1 ] && [ $1 -gt 0 ] && [ -n $2 ]
then
	./corewar -d $1 $2 $3 $4 $5 > dump_zaz.txt
	../corewar/corewar -d $1 $2 $3 $4 $5 > dump_team.txt
	diff dump_zaz.txt dump_team.txt
else
	echo "Arguments non valides"
fi