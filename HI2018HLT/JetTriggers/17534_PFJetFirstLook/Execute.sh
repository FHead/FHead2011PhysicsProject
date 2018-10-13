#!/bin/bash

Files=
for i in `ls Samples/*root`
do
   Files=`echo $Files \"file:$i\",`
done

sed "s#__FILE__#$Files#" < ExportedMenu.py > FinalMenu.py


