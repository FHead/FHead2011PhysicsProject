#!/bin/sh

Executable=./RunCheck

$Executable Samples/QCD_TuneD6T_HT-50To100_7TeV-madgraph_All.root QCD50 30000000
$Executable Samples/QCD_TuneD6T_HT-100To250_7TeV-madgraph_All.root QCD100 7000000
$Executable Samples/QCD_TuneD6T_HT-250To500_7TeV-madgraph_All.root QCD250 171000
$Executable Samples/QCD_TuneD6T_HT-500To1000_7TeV-madgraph_All.root QCD500 5200
$Executable Samples/QCD_TuneD6T_HT-1000_7TeV-madgraph_All.root QCD1000 83
hadd QCDAll.root QCD50.root QCD100.root QCD250.root QCD500.root QCD1000.root
./MakePlots QCDAll.root QCDAll





