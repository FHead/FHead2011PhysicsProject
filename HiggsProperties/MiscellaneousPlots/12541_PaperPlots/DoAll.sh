#!/bin/sh

source ~/.bashrc

# CompileRootMacro ConvertTree.cpp
# time ./a.out Gen11.root ReducedGen11.root
# time ./a.out Gen16.root ReducedGen16.root
# time ./a.out Gen31.root ReducedGen31.root
# time ./a.out Gen36.root ReducedGen36.root
# time ./a.out Reco11.root ReducedReco11.root
# time ./a.out Reco16.root ReducedReco16.root

# CompileRootMacro MakePlots.cpp
# time ./a.out ReducedGen11.root PlotsGen11.root 11
# time ./a.out ReducedGen16.root PlotsGen16.root 16
# time ./a.out ReducedGen31.root PlotsGen31.root 31
# time ./a.out ReducedGen36.root PlotsGen36.root 36
# time ./a.out ReducedReco11.root PlotsReco11.root 11
# time ./a.out ReducedReco16.root PlotsReco16.root 16

CompileRootMacro MakeCoolPlots.cpp
time ./a.out PlotsGen11.root CoolPlotsGen11.root 11 0
time ./a.out PlotsGen16.root CoolPlotsGen16.root 16 0
time ./a.out PlotsGen31.root CoolPlotsGen31.root 31 0
time ./a.out PlotsGen36.root CoolPlotsGen36.root 36 0
time ./a.out PlotsReco11.root CoolPlotsReco11.root 11 0
time ./a.out PlotsReco16.root CoolPlotsReco16.root 16 0
time ./a.out PlotsGen11.root CoolPlotsGen11.root 11 1
time ./a.out PlotsGen16.root CoolPlotsGen16.root 16 1
time ./a.out PlotsGen31.root CoolPlotsGen31.root 31 1
time ./a.out PlotsGen36.root CoolPlotsGen36.root 36 1
time ./a.out PlotsReco11.root CoolPlotsReco11.root 11 1
time ./a.out PlotsReco16.root CoolPlotsReco16.root 16 1

CompileRootMacro MakeGROverlayPlots.cpp
time ./a.out PlotsGen11.root PlotsReco11.root 11
time ./a.out PlotsGen16.root PlotsReco16.root 16
# time ./a.out PlotsGen31.root PlotsReco11.root 31
# time ./a.out PlotsGen36.root PlotsReco16.root 36

CompileRootMacro MakeOverlayPlots.cpp
time ./a.out PlotsGen11.root PlotsReco11.root 11
time ./a.out PlotsGen16.root PlotsReco16.root 16

CompileRootMacro MakeScatterPlots.cpp
# time ./a.out PlotsGen11.root 11
# time ./a.out PlotsGen16.root 16
# time ./a.out PlotsGen31.root 31
# time ./a.out PlotsGen36.root 36
time ./a.out PlotsReco11.root 11
time ./a.out PlotsReco16.root 16

CompileRootMacro MakeSigmaRange.cpp
time ./a.out ReducedGen11.root RangeGen11.dh
time ./a.out ReducedGen16.root RangeGen16.dh
time ./a.out ReducedGen31.root RangeGen31.dh
time ./a.out ReducedGen36.root RangeGen36.dh
time ./a.out ReducedReco11.root RangeReco11.dh
time ./a.out ReducedReco16.root RangeReco16.dh

CompileRootMacro MakeLatexTableRange.cpp
time ./a.out RangeGen11.dh
time ./a.out RangeGen16.dh
time ./a.out RangeGen31.dh
time ./a.out RangeGen36.dh
time ./a.out RangeReco11.dh
time ./a.out RangeReco16.dh

CompileRootMacro MakeCoolPlotsForThesis.cpp
time ./a.out PlotsReco11.root CoolPlotsThesisReco11.root 11 0
time ./a.out PlotsReco16.root CoolPlotsThesisReco16.root 16 0
time ./a.out PlotsReco11.root CoolPlotsThesisReco11.root 11 1
time ./a.out PlotsReco16.root CoolPlotsThesisReco16.root 16 1


