#!/bin/bash

for i in `cat ToCopy.txt`
do
   echo $i
   xrdcp -p -f root://cms-xrd-global/$i Samples/$i
done


