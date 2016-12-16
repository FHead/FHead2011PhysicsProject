#!/bin/sh

mkdir -p Plots

# ./a.out Output.root Plots/AA8Dijet

hadd -f -k PP6Dijet.root Result/PP6Dijet*
hadd -f -k PP8Dijet.root Result/PP8Dijet*
hadd -f -k AA6Dijet.root Result/AA6Dijet*
hadd -f -k AA8Dijet.root Result/AA8Dijet*

./a.out PP6Dijet.root Plots/PP6Dijet
./a.out PP8Dijet.root Plots/PP8Dijet
./a.out AA6Dijet.root Plots/AA6Dijet
./a.out AA8Dijet.root Plots/AA8Dijet

mkdir -p RenamedPlots

for i in `ls Plots | grep pdf | grep AA8`
do
   cp Plots/$i RenamedPlots/15515_MassResponseReconstructedLevelDR_$i
   cp Dummy.pdf RenamedPlots/15515_MassResponseReconstructedLevelDR_${i/AA8/AA6}
   cp Dummy.pdf RenamedPlots/15515_MassResponseReconstructedLevelDR_${i/AA8/PP6}
   cp Dummy.pdf RenamedPlots/15515_MassResponseReconstructedLevelDR_${i/AA8/PP8}
done

for i in `ls Plots | grep pdf`
do
   cp Plots/$i RenamedPlots/15515_MassResponseReconstructedLevelDR_$i
done

for i in `ls Plots | grep pdf | grep -v [AP][AP][68]`
do
   cp Plots/$i RenamedPlots/15515_MassResponseReconstructedLevelDR_$i
done

for i in AA6Dijet.root AA8Dijet.root PP6Dijet.root PP8Dijet.root
do
   echo $i
   ./b.out $i
done

