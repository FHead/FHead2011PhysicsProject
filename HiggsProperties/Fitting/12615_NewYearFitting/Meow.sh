#!/bin/sh
#$ -S /bin/sh
#$ -V
source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /home/yichen/CMSSW/CMSSW_6_0_1/src
eval `scramv1 runtime -sh`
cd - 1>/dev/null 2>/dev/null

cd /home/yichen/PhysicsWorkspace/HiggsProperties/Fitting/12514_RecoFullFitting
mkdir -p /wntmp/yichen/

mkdir -p Work/WorkArea_Events_110001.root_3
cd Work/WorkArea_Events_110001.root_3
ln -s ../../Normalization.dh .
pwd
cp ../../DoFit.cpp .
cp ../../FitClass.cpp .
cp ../../FitClass.h .
cp ../../batchcompile.sh .
sh batchcompile.sh
time ./PerformFits ../../Samples/Events_110001.root 100 \
   ../../Samples/Events_210101.root 0 0 0 0 0 0 0
mv OutputFile.root OutputFile_S_100.root
time ./PerformFits ../../Samples/Events_110001.root 100 \
   ../../Samples/Events_210101.root 60 0 0 0 0 0 0
mv OutputFile.root OutputFile_SB_100.root
