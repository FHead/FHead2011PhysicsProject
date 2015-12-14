cd ~/CMSSW_2_2_13/src
eval `scramv1 runtime -sh`
cd - 2> /dev/null > /dev/null
export CMSSW_SEARCH_PATH=$CMSSW_SEARCH_PATH:~/CMSSW_2_2_13/work/EssentialFiles

cmsRun Reconstruction_108538.py > /tmp/chenyi/AllCharges_108538
cmsRun Reconstruction_108537.py > /tmp/chenyi/AllCharges_108537
cmsRun Reconstruction_108540.py > /tmp/chenyi/AllCharges_108540
cmsRun Reconstruction_108541.py > /tmp/chenyi/AllCharges_108541
cmsRun Reconstruction_108535.py > /tmp/chenyi/AllCharges_108535
cmsRun Reconstruction_108533.py > /tmp/chenyi/AllCharges_108533
cmsRun Reconstruction_108532.py > /tmp/chenyi/AllCharges_108532
