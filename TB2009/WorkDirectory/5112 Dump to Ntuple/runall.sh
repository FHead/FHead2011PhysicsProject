cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - > /tmp/chenyi/guu

for i in $*
do
   rfcp $CASTOR_HOME/TB2009/HTB_$i.root /tmp/chenyi/
   cat DumpToNtuple_template.py | sed "s/__RUNNUM__/$i/g" > DumpToNtuple_$i.py
   cmsRun DumpToNtuple_$i.py > DumpToNtuple_$i.log
done
