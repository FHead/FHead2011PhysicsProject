#!/bin/sh

Executable=./a.out

# arguments: inputfile, outputbase, btag, box, MR min, tries, (one component?)

# 0.30, 0.35, 0.40
time $Executable Samples/Wjets.root WJetMuBox 0 3 200 2
time $Executable Samples/MU_May10.root DataMuBoxNoTag 0 3 200 2

# 0.30, 0.35, 0.40
# time $Executable Samples/Wjets.root WJetEleBox 0 4 300 10
# time $Executable Samples/ELE_May10.root DataEleBoxNoTag 0 4 300 10

# 0.30, 0.35, 0.40, 0.50
# time $Executable Samples/ttbar.root TTbarMuBox 1 3 300 10
# time $Executable Samples/MU_May10.root DataMuBoxWithTag 1 3 300 10

# 0.30, 0.35, 0.40, 0.50
# time $Executable Samples/ttbar.root TTbarEleBox 1 4 250 10
# time $Executable Samples/ELE_May10.root DataEleBoxWithTag 1 4 250 10




 
