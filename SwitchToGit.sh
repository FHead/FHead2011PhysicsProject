#!/bin/bash

for i in */
do
   cd $i
   echo $i
   j=`echo $i | tr -d '/'`
   git remote set-url origin git@github.com:FHead/Physics${j}.git
   cd ..
done

