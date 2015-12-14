#!/bin/sh

Executable=./a.out

# arguments: inputfile, outputbase, btag, box, MR min, tries, (one component?)

time $Executable Samples/Wjets.root WJetMuBox 0 3 0.1 5
time $Executable Samples/MU_May10.root DataMuBoxNoTag 0 3 0.1 5

# time $Executable Samples/Wjets.root WJetEleBox 0 4 0.16 10 1
# time $Executable Samples/ELE_May10.root DataEleBoxNoTag 0 4 300 10 1

# time $Executable Samples/ttbar.root TTbarMuBox 1 3 0.16 10
# time $Executable Samples/MU_May10.root DataMuBoxWithTag 1 3 0.16 10

# time $Executable Samples/ttbar.root TTbarEleBox 1 4 0.16 10
# time $Executable Samples/ELE_May10.root DataEleBoxWithTag 1 4 0.16 10




 
