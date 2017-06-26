#!/bin/sh

mkdir -p Result/
mkdir -p Result/Combined/
mkdir -p GenResult/
mkdir -p GenResult/Combined/

for Sample in `ls Samples/ | grep TT`
do
   echo Start processing sample $Sample
   mkdir -p Result/$Sample
   mkdir -p GenResult/$Sample

   for File in `ls Samples/$Sample/`
   do
      echo File $File

      ./RunClosestJet Samples/$Sample/$File Result/$Sample/$File 2>&1 | grep -v L1Classes_rdict.pcm
      ./RunClosestGenJet Samples/$Sample/$File GenResult/$Sample/$File 2>&1 | grep -v L1Classes_rdict.pcm
   done

   hadd -f Result/Combined/${Sample}.root Result/$Sample/*
   hadd -f GenResult/Combined/${Sample}.root GenResult/$Sample/*

   echo
done

CompileRootMacro QuickPlot.cpp

./a.out 140
./a.out 200

CompileRootMacro QuickPlotGen.cpp

./a.out 140
./a.out 200


