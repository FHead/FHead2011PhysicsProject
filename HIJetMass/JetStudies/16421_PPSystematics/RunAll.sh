sh compile.sh

for SD in 0 7
do
   # ./RunSystematics PP6Dijet.root PP6Dijet.root $SD DR PP6_DR Exponential
   # ./RunSystematics PP6Dijet.root PP6Dijet.root $SD JER PP6_JER Linear
   # ./RunSystematics PP6Dijet.root PP6Dijet.root $SD JES PP6_JES Linear
   # ./RunSystematics PP6Dijet.root PP6Dijet.root $SD JetEta PP6_JetEta Linear
   ./RunSystematics PP6Dijet.root PP6Dijet.root $SD QuarkGluon PP6_QuarkGluon Quadratic
done

./RunCombination 0 Y
./RunCombination 0 N
./RunCombination 7 Y
./RunCombination 7 N



