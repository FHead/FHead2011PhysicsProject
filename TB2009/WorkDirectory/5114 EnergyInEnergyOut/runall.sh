cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - > /dev/null

for i in `cat EnergyScanRunNumber`
do
   # rfcp $CASTOR_HOME/TB2009/HTB_$i.root /tmp/chenyi
   cat EnergyOut_template.py | sed "s/__RUNNUM__/$i/g" > EnergyOut_$i.py
   cmsRun EnergyOut_$i.py | tee $i.log
done

