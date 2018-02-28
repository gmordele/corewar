#!/bin/sh

mkdir vcor
mkdir gcor

for file in ./s/*.s
do
	cp $file ./vcor
	cp $file ./gcor
done

for file in ./vcor/*.s
do
	../vm_champs/asm $file
done

for file in ./gcor/*.s
do
	../asm/asm $file
done

echo "----------------------------------------------"
echo "CMP"
echo "----------------------------------------------"

for file in ./vcor/*.cor
do
	name=`basename $file`
	echo $name
	cmp ./gcor/$name ./vcor/$name
done

rm -rf vcor
rm -rf gcor