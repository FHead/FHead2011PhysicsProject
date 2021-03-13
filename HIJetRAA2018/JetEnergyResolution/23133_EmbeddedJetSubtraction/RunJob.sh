#!/bin/bash

cd ~/work/CMSSW/CMSSW_10_3_5/src
eval `scramv1 runtime -sh`
cd - > /dev/null
export CMSSW_SEARCH_PATH=$CMSSW_SEARCH_PATH:~/work/CMSSW/CMSSW_10_3_5/work/EssentialFiles

Input=$1
Output=$2
JetR=$3
RhoPhiEta=$4
Executable=$5

ln -s /afs/cern.ch/user/c/chenyi/work/CMSSW/JECDatabase/textFiles/Autumn18_HI_RAAV2_MC// JEC

cp $5 Execute

AlgoTag=AK1PF
if (( $(echo "$JetR == 0.15" | bc -l) )); then
   AlgoTag=AK1PF
elif (( $(echo "$JetR == 0.20" | bc -l) )); then
   AlgoTag=AK2PF
elif (( $(echo "$JetR == 0.30" | bc -l) )); then
   AlgoTag=AK3PF
elif (( $(echo "$JetR == 0.40" | bc -l) )); then
   AlgoTag=AK4PF
elif (( $(echo "$JetR == 0.50" | bc -l) )); then
   AlgoTag=AK5PF
elif (( $(echo "$JetR == 0.60" | bc -l) )); then
   AlgoTag=AK6PF
elif (( $(echo "$JetR == 0.80" | bc -l) )); then
   AlgoTag=AK7PF
elif (( $(echo "$JetR == 1.00" | bc -l) )); then
   AlgoTag=AK8PF
elif (( $(echo "$JetR == 1.20" | bc -l) )); then
   AlgoTag=AK9PF
fi

echo "Algo tag = $AlgoTag"

./Execute --input $Input --output SubtractedJet.root \
   --R $JetR --JEC JEC/Autumn18_HI_RAAV2_MC_L2Relative_${AlgoTag}.txt --fraction 1.00 \
   --GenMinPT 3 \
   --CSR -1 --CSAlpha 2 --MinProbability 0.05 --MaxProbability 0.95 \
   --RhoPhiMaxEta $RhoPhiEta

rm Execute
rm JEC

mv SubtractedJet.root $Output



