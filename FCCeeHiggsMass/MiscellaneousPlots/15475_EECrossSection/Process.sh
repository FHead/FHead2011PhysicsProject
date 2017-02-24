#!/bin/sh

for i in EEVVH EEEEH EEMMH
do
   Reformat 7 < ${i}.txt | awk '{print $1, $4, $6}' | tee ${i}.data
done

FileLineAppend EEVVH.data EEEEH.data Temp
FileLineAppend EEMMH.data Temp All.data

awk '{print 2*$1, $2, $3, $5, $6, $8, $9}' < All.data | TextToTree All.root 7 "E:MM:MMError:VV:VVError:EE:EEError"



