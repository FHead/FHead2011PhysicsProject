cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - > /dev/null 2> /dev/null

for i in $*
do
   cat Profile_template.py | sed "s/__RUNNUM__/$i/g" > Profile_$i.py
   cmsRun Profile_$i.py > /tmp/chenyi/AllCharge_$i
done

