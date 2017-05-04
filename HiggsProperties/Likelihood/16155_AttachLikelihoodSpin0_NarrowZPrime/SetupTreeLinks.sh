#!/bin/sh

rm AttachedTrees*
rm OriginalTrees*
for i in `ls /eos/user/c/chenyi/MGSample/`
do
   j=`echo $i | cut --delim='_' --field=1`
   ln -s /eos/user/c/chenyi/MGSample/$i/Processed OriginalTrees$j
   ln -s /eos/user/c/chenyi/MGSample/$i/AttachedSpin0XVV AttachedTrees$j
done
