#!/bin/sh

STEP=1000
MAX=3000
CORDIR=./cor
COREWAR1=../corewar/corewar
COREWAR2=../vm_champs/corewar

corarr=(`ls $CORDIR/*.cor`)
arrlen=${#corarr[@]}

for i in `seq 0 $(($arrlen - 1))`
do
	for j in `seq $i $(($arrlen - 1))`
	do
		for dump in `seq $STEP $STEP $MAX`
		do
			df1=`$COREWAR1 ${corarr[$i]} ${corarr[$j]} -dump $dump`
			df2=`$COREWAR2 ${corarr[$i]} ${corarr[$j]} -d $dump`
			if [ "$df1" != "$df2" ]
			then
				echo "${corarr[$i]} ${corarr[$j]} FAIL with dump $dump"
				echo "$df1"
				echo "$df2"
				lines=`echo "$df1" | wc -l`
				echo $lines
				if [ $lines -gt 10 ]
				then
					echo ${corarr[$i]} ${corarr[$j]} dump = $dump >> failed
				fi
				break
			fi
		done
		echo ${corarr[$i]} ${corarr[$j]} done
	done
done