cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - > /dev/null

for i in `cat EnergyScanRunNumber`
do
   # rfcp $CASTOR_HOME/TB2009/HTB_$i.root /tmp/chenyi
   cat EnergyOutSingleTower_template.py | sed "s/__RUNNUM__/$i/g" > EnergyOutSingleTower_$i.py
   cmsRun EnergyOutSingleTower_$i.py | tee ${i}_singletower.log
done

