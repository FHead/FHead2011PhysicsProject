#!/bin/sh

# hadd -f -k PP6Dijet.root Result/PP6Dijet*.root 
hadd -f -k PP8Dijet.root Result/PP8Dijet*.root 
# hadd -f -k PPDataHighPTJet.root Result/PPDataHighPTJet*.root 
# ./a.out PP6Dijet.root Plots/PP6Dijet
./a.out PP8Dijet.root Plots/PP8Dijet
# ./a.out PPDataHighPTJet.root Plots/PPDataHighPTJet
