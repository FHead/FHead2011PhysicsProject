#!/bin/bash

File=(`echo $1 | tr ',' '\n'`)
Tag=(`echo $2 | tr ',' '\n'`)

for i in "${!File[@]}"
do 
   echo "[${Tag[$i]}]"
   cat "${File[$i]}" | sed "s/Uncertainty/JECSource/"
done


