./a.out Samples/QCD_TuneD6T_HT-50To100_7TeV-madgraph_All.root 30000000 gosi
./a.out Samples/QCD_TuneD6T_HT-100To250_7TeV-madgraph_All.root 7000000 etw
./a.out Samples/QCD_TuneD6T_HT-250To500_7TeV-madgraph_All.root 171000 qje
./a.out Samples/QCD_TuneD6T_HT-500To1000_7TeV-madgraph_All.root 5200 shd
./a.out Samples/QCD_TuneD6T_HT-1000_7TeV-madgraph_All.root 83 jga

hadd -f hfs.root gosi.root etw.root qje.root shd.root jga.root


