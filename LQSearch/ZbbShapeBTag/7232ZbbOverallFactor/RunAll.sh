Executable=./a.out

$Executable DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All 3048
$Executable ZbbToLL_M-50_TuneZ2_7TeV-madgraph-pythia6_tauola_Summer11-PU_S4_START42_V11-v1_All 1
$Executable ZinvisibleJets_7TeV-madgraph_All 18272
$Executable WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All 31314

hadd -f InclusiveSamples.root ZinvisibleJets_7TeV-madgraph_All.root WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_All.root DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_All.root

./b.out | grep RATIO

