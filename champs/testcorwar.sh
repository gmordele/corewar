#!/bin/sh

STEP=2000
MAX=5000
CORDIR=./cor
COREWAR1=../corewar/corewar
COREWAR2=../vm_champs/corewar

corarr=(`ls $CORDIR/*.cor`)
arrlen=${#corarr[@]}

rm -f failed.txt

for i in `seq 0 $(($arrlen - 1))`
do
	for j in `seq $i $(($arrlen - 1))`
	do
	#	echo "\x1b[2K\x1b[32m${corarr[$i]}\x1b[0m vs \x1b[36m${corarr[$j]}\x1b[0m\x1b[A"
		for dump in `seq 1000 $STEP $MAX`
		do
			echo "\x1b[2K $dump \x1b[32m${corarr[$i]}\x1b[0m vs \x1b[36m${corarr[$j]}\x1b[0m\x1b[A"
			df1=`$COREWAR1 ${corarr[$i]} ${corarr[$j]} -d $dump`
			df2=`$COREWAR2 ${corarr[$i]} ${corarr[$j]} -d $dump`
			if [ "$df1" != "$df2" ]
			then
				echo "${corarr[$i]} vs ${corarr[$j]} -d $dump" >> failed.txt
			#	diff $df1 $df2 >> failed.txt
#				echo "${corarr[$i]} ${corarr[$j]} FAIL with dump $dump"
#				echo "$df1"
#				echo "$df2"
#				lines=`echo "$df1" | wc -l`
#				echo $lines
#				if [ $lines -gt 10 ]
#				then
#					echo ${corarr[$i]} ${corarr[$j]} dump = $dump >> failed
#				fi
#				break
			fi
		done
	done
done