#!/bin/sh --login

#BSUB -q 2nw

export SCRAM_ARCH=slc6_amd64_gcc491
cd ~/work/CMSSW/CMSSW_7_5_8_patch3/src
# cd ~/work/CMSSW/CMSSW_8_0_21/src
eval `scramv1 runtime -sh`
cd - > /dev/null

cp /afs/cern.ch/user/c/chenyi/work/PhysicsWorkspace/HIJetMass/JetStudies/16163_PPLowerTrigger/*dh .

echo "Start copying input file"
cmsStage -f __INPUT__ Input.root
echo "File copied."
echo

DefaultOutput=__OUTPUT__

OutputBase=`dirname $DefaultOutput`
OutputName=`basename $DefaultOutput`

OutputBase=/store/cmst3/user/chenyi/BatchOutput/HIJetMass/JetStudies/16163_PPLowerTrigger/Result

Mod=Mod__EXTRA2__
#Mod=

# __EXECUTABLE__ Input.root Output1.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 1.00 0.8  __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output1.root ${OutputBase}1/$Mod$OutputName
# __EXECUTABLE__ Input.root Output2.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 1.50 0.8  __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output2.root ${OutputBase}2/$Mod$OutputName
# __EXECUTABLE__ Input.root Output3.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 2.00 0.8  __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output3.root ${OutputBase}3/$Mod$OutputName
# __EXECUTABLE__ Input.root Output4.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 4.00 0.8  __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output4.root ${OutputBase}4/$Mod$OutputName
# __EXECUTABLE__ Input.root Output5.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 0.50 0.8  __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output5.root ${OutputBase}5/$Mod$OutputName
# __EXECUTABLE__ Input.root Output6.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.10 1.00 0.8  __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output6.root ${OutputBase}6/$Mod$OutputName
# __EXECUTABLE__ Input.root Output7.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.05 1.00 0.8  __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output7.root ${OutputBase}7/$Mod$OutputName
# __EXECUTABLE__ Input.root Output8.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.30 1.00 0.8  __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output8.root ${OutputBase}8/$Mod$OutputName
# __EXECUTABLE__ Input.root Output9.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.20 0.07 0.16 1.00 0.8  __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output9.root ${OutputBase}9/$Mod$OutputName
# __EXECUTABLE__ Input.root Output10.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.50 0.07 0.13 1.00 0.8 __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output10.root ${OutputBase}10/$Mod$OutputName
# __EXECUTABLE__ Input.root Output11.root __TAG__ __PTHATMIN__ __PTHATMAX__ 0.80 0.07 0.25 1.00 0.8 __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output11.root ${OutputBase}11/$Mod$OutputName
# __EXECUTABLE__ Input.root Output12.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.10 0.20 1.00 0.8 __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output12.root ${OutputBase}12/$Mod$OutputName
__EXECUTABLE__ Input.root Output13.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 1.00 1.2 __EXTRA1__ __EXTRA2__ __EXTRA3__
cmsStage -f Output13.root ${OutputBase}13/$Mod$OutputName
# __EXECUTABLE__ Input.root Output14.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 1.00 0.6 __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output14.root ${OutputBase}14/$Mod$OutputName
# __EXECUTABLE__ Input.root Output15.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.04 0.20 1.00 0.8 __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output15.root ${OutputBase}15/$Mod$OutputName
# __EXECUTABLE__ Input.root Output16.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.02 0.20 1.00 0.8 __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output16.root ${OutputBase}16/$Mod$OutputName
# __EXECUTABLE__ Input.root Output17.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 1.00 1.6 __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output17.root ${OutputBase}17/$Mod$OutputName
# __EXECUTABLE__ Input.root Output18.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 1.00 2.0 __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output18.root ${OutputBase}18/$Mod$OutputName
# __EXECUTABLE__ Input.root Output19.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 1.20 0.8 __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output19.root ${OutputBase}19/$Mod$OutputName
# __EXECUTABLE__ Input.root Output20.root __TAG__ __PTHATMIN__ __PTHATMAX__ 1.00 0.07 0.20 0.80 0.8 __EXTRA1__ __EXTRA2__ __EXTRA3__
# cmsStage -f Output20.root ${OutputBase}20/$Mod$OutputName


