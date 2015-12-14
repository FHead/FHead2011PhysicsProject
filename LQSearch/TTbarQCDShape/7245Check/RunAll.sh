#!bin/sh

Executable=./a.out

$Executable Samples/QCD_TuneD6T_HT-1000_7TeV-madgraph_All.root 83 QCD1000
$Executable Samples/QCD_TuneD6T_HT-500To1000_7TeV-madgraph_All.root 5200 QCD500
$Executable Samples/QCD_TuneD6T_HT-250To500_7TeV-madgraph_All.root 171000 QCD250
$Executable Samples/QCD_TuneD6T_HT-100To250_7TeV-madgraph_All.root 7000000 QCD100
$Executable Samples/QCD_TuneD6T_HT-50To100_7TeV-madgraph_All.root 30000000 QCD50
$Executable Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_All.root 165 TTbar

hadd -f QCDAll.root QCD50.root QCD100.root QCD250.root QCD500.root QCD1000.root



