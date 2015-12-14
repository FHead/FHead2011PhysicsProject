#!/bin/sh
hadd -f QCDAll.root QCD50All.root QCD100All.root QCD200All.root QCD500All.root QCD1000All.root
hadd -f BQCDAll.root BQCD30All.root BQCD50All.root BQCD150All.root
hadd -f BQCD_B0.root BQCD30_B0.root BQCD50_B0.root BQCD150_B0.root
hadd -f BQCD_B1.root BQCD30_B1.root BQCD50_B1.root BQCD150_B1.root
hadd -f BQCD_B2.root BQCD30_B2.root BQCD50_B2.root BQCD150_B2.root

./MakeSinglePlot QCDAll.root QCDAll
./MakeSinglePlot BQCDAll.root BQCDAll
./MakeSinglePlot BQCD_B0.root BQCD_B0
./MakeSinglePlot BQCD_B1.root BQCD_B1
./MakeSinglePlot BQCD_B2.root BQCD_B2




