cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - > /dev/null 2> /dev/null
export CMSSW_SEARCH_PATH=$CMSSW_SEARCH_PATH:~/CMSSW_2_2_13/work/EssentialFiles

for i in $*
do
   cat StudyEnergyCut_template.py | sed "s/__RUNNUM__/$i/g" > StudyEnergyCut_$i.py
   cmsRun StudyEnergyCut_$i.py | tee log_$i
done

