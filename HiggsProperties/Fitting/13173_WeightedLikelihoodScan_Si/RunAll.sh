S8=/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/unweighted/SignalAll8TeV.root
B8=/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/unweighted/BackgroundAll8TeV.root
Z8=/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_MC_ZJets_8TeV.root
G8=/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_MC_ZJets_8TeV.root
S7=/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/unweighted/SignalAll7TeV.root
B7=/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/unweighted/BackgroundAll7TeV.root
Z7=/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_MC_ZJets_8TeV.root
G7=/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_ggZZ_8TeV.root


# ./runA3Scan.sh $S8 -1  8 -1  0 FA3_Signal8TeV     Jobs/
# ./runA3Scan.sh $B8  0  8 -1  0 FA3_Background8TeV Jobs/
# ./runA3Scan.sh $Z8  1  8 -1  0 FA3_ZJets8TeV      Jobs/
# ./runA3Scan.sh $G8  1  8 -1  0 FA3_ggZZ8TeV       Jobs/
# ./runA3Scan.sh $S7 -1  7 -1  0 FA3_Signal7TeV     Jobs/
# ./runA3Scan.sh $B7  0  7 -1  0 FA3_Background7TeV Jobs/
# ./runA3Scan.sh $Z7  1  7 -1  0 FA3_ZJets7TeV      Jobs/
# ./runA3Scan.sh $G7  1  7 -1  0 FA3_ggZZ7TeV       Jobs/

./runA3Scan.sh $S8 -1  8 -1  0 FA2_Signal8TeV     Jobs/
./runA3Scan.sh $B8  0  8 -1  0 FA2_Background8TeV Jobs/
./runA3Scan.sh $Z8  1  8 -1  0 FA2_ZJets8TeV      Jobs/
./runA3Scan.sh $G8  1  8 -1  0 FA2_ggZZ8TeV       Jobs/
./runA3Scan.sh $S7 -1  7 -1  0 FA2_Signal7TeV     Jobs/
./runA3Scan.sh $B7  0  7 -1  0 FA2_Background7TeV Jobs/
./runA3Scan.sh $Z7  1  7 -1  0 FA2_ZJets7TeV      Jobs/
./runA3Scan.sh $G7  1  7 -1  0 FA2_ggZZ7TeV       Jobs/




