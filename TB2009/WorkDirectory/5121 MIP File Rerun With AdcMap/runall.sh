cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - > /dev/null

cmsRun CreateMIP_108528.py | tee 108528.log
cmsRun CreateMIP_108525.py | tee 108525.log
cmsRun CreateMIP_108523.py | tee 108523.log
