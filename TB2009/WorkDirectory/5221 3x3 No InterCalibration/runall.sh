cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - > /dev/null 2> /dev/null
export CMSSW_SEARCH_PATH=$CMSSW_SEARCH_PATH:~/CMSSW_2_2_13/work/EssentialFiles

for i in $*
do
   cat Profile_template.py | sed "s/__RUNNUM__/$i/g" > Profile_$i.py
   cmsRun Profile_$i.py | tee Profile_$i.log
done

