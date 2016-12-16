#!/bin/sh

hadd -f -k PP6Dijet.root Result/PP6Dijet*.root 
hadd -f -k PP8Dijet.root Result/PP8Dijet*.root 
hadd -f -k AA6Dijet.root Result/AA6Dijet*.root 
hadd -f -k AA8Dijet.root Result/AA8Dijet*.root 
./a.out PP6Dijet.root Plots/PP6Dijet
./a.out PP8Dijet.root Plots/PP8Dijet
./a.out AA6Dijet.root Plots/AA6Dijet
./a.out AA8Dijet.root Plots/AA8Dijet

