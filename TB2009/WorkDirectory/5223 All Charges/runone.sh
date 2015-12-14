Runnum=$1
Min=`echo $2 | SubtractConst $3`
Max=`echo $2 | AddConst $3`
Energy=$2
cat ProduceCharge.py | sed "s/__RUNNUM__/$Runnum/g" | sed "s/__MINENERGY__/$Min/g" | sed "s/__MAXENERGY__/$Max/g" | sed "s/__ENERGY__/$Energy/g"> ExportCharge$Runnum.py

cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - >/dev/null 2> /dev/null
export CMSSW_SEARCH_PATH=$CMSSW_SEARCH_PATH:~/CMSSW_2_2_13/work/EssentialFiles

cmsRun ExportCharge$Runnum.py > /tmp/chenyi/AllCharge$Runnum.log
