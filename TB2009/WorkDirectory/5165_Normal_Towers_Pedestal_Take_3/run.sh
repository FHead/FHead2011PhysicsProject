cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - > /dev/null 2> /dev/null
export CMSSW_SEARCH_PATH=$CMSSW_SEARCH_PATH:~/CMSSW_2_2_13/work/EssentialFiles

for i in $*
do
   # cat Reconstruction_template.py | sed "s/__RUNNUM__/$i/g" > Reconstruction_$i.py
   # cmsRun Reconstruction_$i.py | tee Log_$i
   root -l -q "GeneratePedestalMean.C+(\"NREnergyDistribution_$i.root\")" | grep "\[Result\]" | cut --delim=' ' --f=2-4 > PedestalShift_$i.txt
   ./CreatePedestalFile pedestals_TB2009.txt PedestalShift_$i.txt pedestals_TB2009_${i}.txt
done
