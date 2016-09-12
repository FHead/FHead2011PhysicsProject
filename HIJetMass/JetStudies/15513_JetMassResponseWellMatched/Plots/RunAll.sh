#!/bin/sh

mkdir -p Plots

hadd -f -k PP6Dijet.root Result/PP6Dijet*
hadd -f -k PP8Dijet.root Result/PP8Dijet*
hadd -f -k AA6Dijet.root Result/AA6Dijet*
hadd -f -k AA8Dijet.root Result/AA8Dijet*

./a.out PP6Dijet.root Plots/PP6Dijet
./a.out PP8Dijet.root Plots/PP8Dijet
./a.out AA6Dijet.root Plots/AA6Dijet
./a.out AA8Dijet.root Plots/AA8Dijet

mkdir -p RenamedPlots

for i in `ls Plots | grep pdf | grep -v X | grep -v Spread`
do
   cp Plots/$i RenamedPlots/15513_WellMatchedSamples_$i
done
for i in `ls Plots | grep pdf | grep X`
do
   cp Plots/$i RenamedPlots/15513_SubJetLocation_$i
done
for i in `ls Plots | grep pdf | grep Spread`
do
   cp Plots/$i RenamedPlots/15513_SubJetLocation_$i
done
