CompileRootMacro EstimateSystematics.cpp
for SD in 0 7
do
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult15/PP6Dijet.root $SD Ghost  Ghost    0.07 0.20
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult9/PP6Dijet.root  $SD Rho    Rho      0.07 0.20
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult13/PP6Dijet.root $SD Range  Range    0.07 0.20
   ./a.out ScaledResult13/PP6Dijet.root ScaledResult17/PP6Dijet.root $SD Range2 Range2   0.07 0.20
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult21/PP6Dijet.root $SD MB     MB2      0.07 0.20
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult22/PP6Dijet.root $SD MB     MB3      0.07 0.20
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult6/PP6Dijet.root  $SD Normal Smear    0.07 0.20
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult1/PP6Dijet.root  $SD PT     PTScale  0.07 0.20
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult1/PP6Dijet.root  $SD Eta    JetEta   0.05 0.20
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult1/PP6Dijet.root  $SD JER    JER      0.05 0.20
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult1/PP6Dijet.root  $SD Smear  NewSmear 0.07 0.17
   ./a.out ScaledResult1/PP6Dijet.root  ScaledResult1/PP6Dijet.root  $SD DR     DR       0.20 0.35
done

# CompileRootMacro MakeFlatGraphs.cpp
# 
# ./a.out OutputFile_Trigger_0.root 0.05
# ./a.out OutputFile_Trigger_7.root 0.05
# ./a.out OutputFile_GluonQuark_0.root 0.07
# ./a.out OutputFile_GluonQuark_7.root 0.07

CompileRootMacro CombineSystematics.cpp

./a.out 0 N
./a.out 7 N
./a.out 0 Y
./a.out 7 Y

CompileRootMacro PrettySystematicsPlot.cpp
mkdir -p Plots

for SD in 0 7
do
   for iC in `seq 0 3`
   do
      for iPT in `seq 1 5`
      do
         ./a.out C${iC}_P${iPT} $SD
      done
   done
done

CompileRootMacro PrintSystematicsTable.cpp

LATEX=LatexOutput.txt

rm -f $LATEX
touch $LATEX

echo Ghost 0 >> $LATEX
./a.out OutputFile_Ghost_0.root 0.10 >> $LATEX
echo >> $LATEX

echo Rho 0 >> $LATEX
./a.out OutputFile_Rho_0.root 0.10 >> $LATEX
echo >> $LATEX

echo Range 0 >> $LATEX
./a.out OutputFile_Range_0.root 0.10 >> $LATEX
echo >> $LATEX

echo Range2 0 >> $LATEX
./a.out OutputFile_Range2_0.root 0.10 >> $LATEX
echo >> $LATEX

echo MB2 0 >> $LATEX
./a.out OutputFile_MB2_0.root 0.10 >> $LATEX
echo >> $LATEX

echo MB3 0 >> $LATEX
./a.out OutputFile_MB3_0.root 0.10 >> $LATEX
echo >> $LATEX

echo Smear 0 >> $LATEX
./a.out OutputFile_Smear_0.root 0.10 >> $LATEX
echo >> $LATEX

echo PTScale 0 >> $LATEX
./a.out OutputFile_PTScale_0.root 0.10 >> $LATEX
echo >> $LATEX

echo JetEta 0 >> $LATEX
./a.out OutputFile_JetEta_0.root 0.10 >> $LATEX
echo >> $LATEX

echo JER 0 >> $LATEX
./a.out OutputFile_JER_0.root 0.10 >> $LATEX
echo >> $LATEX

echo NewSmear 0 >> $LATEX
./a.out OutputFile_NewSmear_0.root 0.10 >> $LATEX
echo >> $LATEX

echo DR 0 >> $LATEX
./a.out OutputFile_DR_0.root 0.25 >> $LATEX
echo >> $LATEX

echo Ghost 7 >> $LATEX
./a.out OutputFile_Ghost_7.root 0.10 >> $LATEX
echo >> $LATEX

echo Rho 7 >> $LATEX
./a.out OutputFile_Rho_7.root 0.10 >> $LATEX
echo >> $LATEX

echo Range 7 >> $LATEX
./a.out OutputFile_Range_7.root 0.10 >> $LATEX
echo >> $LATEX

echo Range2 7 >> $LATEX
./a.out OutputFile_Range2_7.root 0.10 >> $LATEX
echo >> $LATEX

echo MB2 7 >> $LATEX
./a.out OutputFile_MB2_7.root 0.10 >> $LATEX
echo >> $LATEX

echo MB3 7 >> $LATEX
./a.out OutputFile_MB3_7.root 0.10 >> $LATEX
echo >> $LATEX

echo Smear 7 >> $LATEX
./a.out OutputFile_Smear_7.root 0.10 >> $LATEX
echo >> $LATEX

echo PTScale 7 >> $LATEX
./a.out OutputFile_PTScale_7.root 0.10 >> $LATEX
echo >> $LATEX

echo JetEta 7 >> $LATEX
./a.out OutputFile_JetEta_7.root 0.10 >> $LATEX
echo >> $LATEX

echo JER 7 >> $LATEX
./a.out OutputFile_JER_7.root 0.10 >> $LATEX
echo >> $LATEX

echo NewSmear 7 >> $LATEX
./a.out OutputFile_NewSmear_7.root 0.10 >> $LATEX
echo >> $LATEX

echo DR 7 >> $LATEX
./a.out OutputFile_DR_7.root 0.25 >> $LATEX
echo >> $LATEX



