cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - > /dev/null 2> /dev/null
export CMSSW_SEARCH_PATH=$CMSSW_SEARCH_PATH:~/CMSSW_2_2_13/work/EssentialFiles

for i in 108532 108533 108535 108537 108540 108541
do
   cat PionReco_template.py | sed "s/__RUNNUM__/$i/g" > PionReco_$i.py
   cmsRun PionReco_$i.py | tee log_PionReco_$i
done
