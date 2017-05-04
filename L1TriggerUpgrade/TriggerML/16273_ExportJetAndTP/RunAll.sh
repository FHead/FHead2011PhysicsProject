#!/bin/sh

mkdir -p Result/
mkdir -p Result/Combined/

for Sample in `ls Samples/ | grep WToEnu`
do
   echo Start processing sample $Sample
   mkdir -p Result/$Sample

   for File in `ls Samples/$Sample/`
   do
      echo File $File

      ./RunExport Samples/$Sample/$File Result/$Sample/${File/.root/.txt} 2>&1 | grep -v L1Classes_rdict.pcm
   done

   cat Result/$Sample/* > Result/Combined/${Sample}.txt
   cat Result/Combined/${Sample}.txt | TextToTree Result/Combined/${Sample}.root 158
   
   echo
done




