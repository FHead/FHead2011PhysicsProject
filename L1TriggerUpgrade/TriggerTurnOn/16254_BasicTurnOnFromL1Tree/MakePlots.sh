CompileRootMacro PlotJet.cpp

./a.out Result/TT140.root Result/TT200.root TT | grep ^95 | awk '{print $3,$4,$5,$6}' \
   | TextToTree ScalingTT.root 4 "Type:N:N140:N200"
./a.out Result/WENu140.root Result/WENu200.root WENu | grep ^95 | awk '{print $3,$4,$5,$6}' \
  | TextToTree ScalingWENu.root 4 "Type:N:N140:N200"

CompileRootMacro MakeScalingPlot.cpp

# ./a.out ScalingTT.root TT
./a.out ScalingWENu.root WENu

CompileRootMacro MakeTurnOnOverlay.cpp

./a.out

CompileRootMacro PlotEfficiencyPlots.cpp

./a.out Result/WENu200.root WENu200
./a.out Result/WENu140.root WENu140

