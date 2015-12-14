cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - > /dev/null 2> /dev/null

for i in 108532 108533 108535 108538 108537 108540 108541
do
   cat CountSample.py | sed "s/__RUNNUM__/$i/g" > Count_$i.py
   cmsRun Count_$i.py | tee Log_$i
done
