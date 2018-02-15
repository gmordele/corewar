#!/bin/sh

if [ -n "$3" ]
then
	i=$3
else
	i="0"
fi
while :
do
	echo $i
	./corewar $1 $2 -d $i
	i=$((i+1))
	read 
done