Executable=./RunIndividual

$Executable MCSamples/ZinvisibleJets_7TeV-madgraph_All.root 4500 Histograms/ZinvisibleJets_7TeV-madgraph_All.root O
$Executable MCSamples/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All.root 3048 Histograms/DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All.root O
$Executable DataSamples/PhotonHadRun2011A_All.root -1 Histograms/PhotonHadRun2011A_All.root P
$Executable DataSamples/PhotonHadRun2011B_All.root -1 Histograms/PhotonHadRun2011B_All.root P
$Executable MCSamples/GJet_40_HT_100_All.root 25690.0 Histograms/GJet_40_HT_100_All.root P
$Executable MCSamples/GJet_100_HT_200_All.root 5213.0 Histograms/GJet_100_HT_200_All.root P
$Executable MCSamples/GJet_200_HT_inf_All.root 798.3 Histograms/GJet_200_HT_inf_All.root P

cd Histograms
sh Merge.sh
cd ..

time ./a.out Histograms/ZinvisibleJets_7TeV-madgraph_All.root Znunu
time ./a.out Histograms/GJet_All.root GJet
time ./a.out Histograms/PhotonHadRun2011All.root PhotonHad



