#!/bin/sh

mkdir -p Result/
mkdir -p Result/Combined/

for Sample in `ls Samples/ | grep Hgg`
do
   echo Start processing sample $Sample
   mkdir -p Result/$Sample

   for File in `ls Samples/$Sample/`
   do
      echo File $File

      ./RunTurnOn Samples/$Sample/$File Result/$Sample/$File 2>&1 | grep -v L1Classes_rdict.pcm
   done

   hadd -f Result/Combined/${Sample}.root Result/$Sample/*

   echo
done




