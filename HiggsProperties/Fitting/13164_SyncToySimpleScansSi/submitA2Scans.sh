#test
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/RunLikelihood Trees/SyncToys_7TeV_SMSignal.root Trees/SyncToys_7TeV_Bkg.root Trees/SyncToys_7TeV_Bkg.root Trees/SyncToys_7TeV_Bkg.root Trees/SyncToys_8TeV_SMSignal.root Trees/SyncToys_8TeV_Bkg.root Trees/SyncToys_8TeV_Bkg.root Trees/SyncToys_8TeV_Bkg.root 0 0 0 0 0 0 0 20 NNNNNNNN YYNNNNNN



/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/RunLikelihoodScan /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_SMSignal.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_SMSignal.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root 0 0 0 0 0 0 0 20 NYNNNNNN NNNNNNNN NNNNNNNNNNNN 1.0

Þ
################
#Fixed Fs
################

foreach i(`seq 1 1 99`)

  set fa2 = `echo "" | awk "{print -1 + $i * 2.0/100}"`
  set a2a1 = `echo "" | awk "{print sqrt( 1 / (1 - sqrt($fa2*$fa2))*sqrt($fa2*$fa2)*3.276*3.276)}"`

  set fa2Negative = `echo "" | awk "{if($fa2 < 0){print 1}}"`
  if ($fa2Negative == "1") then
    set a2a1 = `echo "" | awk "{print -1*$a2a1}"`
  endif
  echo $fa2 " " $a2a1

  bsub -q 1nd -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/Fit_fa2_${fa2}_fixedFs_profile_nothing_lumi1.out -J HZZ4L_Fit_fa2_${fa2}_fixedFs_profile_nothing_lumi1 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/runA2Scan.sh $a2a1 NNNNNN NNNNNN NNNNNNNNNNNN 1.0 LikelihoodFile_fa2_${fa2}_fixedFs_profile_nothing_lumi1.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/FitResults/FA2/

end

foreach i(`seq 1 1 99`)

  set fa2 = `echo "" | awk "{print -1 + $i * 2.0/100}"`
  set a2a1 = `echo "" | awk "{print sqrt( 1 / (1 - sqrt($fa2*$fa2))*sqrt($fa2*$fa2)*3.276*3.276)}"`

  set fa2Negative = `echo "" | awk "{if($fa2 < 0){print 1}}"`
  if ($fa2Negative == "1") then
    set a2a1 = `echo "" | awk "{print -1*$a2a1}"`
  endif
  echo $fa2 " " $a2a1

  bsub -q 1nd -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/Fit_fa2_${fa2}_fixedFs_profile_nothing_lumi100.out -J HZZ4L_Fit_fa2_${fa2}_fixedFs_profile_nothing_lumi100 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/runA2Scan.sh $a2a1 NNNNNN NNNNNN NNNNNNNNNNNN 100.0 LikelihoodFile_fa2_${fa2}_fixedFs_profile_nothing_lumi100.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/FitResults/FA2/

end
 

foreach i(`seq 1 1 99`)

  set fa2 = `echo "" | awk "{print -1 + $i * 2.0/100}"`
  set a2a1 = `echo "" | awk "{print sqrt( 1 / (1 - sqrt($fa2*$fa2))*sqrt($fa2*$fa2)*3.276*3.276)}"`

  set fa2Negative = `echo "" | awk "{if($fa2 < 0){print 1}}"`
  if ($fa2Negative == "1") then
    set a2a1 = `echo "" | awk "{print -1*$a2a1}"`
  endif
  echo $fa2 " " $a2a1

  bsub -q 1nd -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/Fit_fa2_${fa2}_fixedFs_profile_a2_lumi100.out -J HZZ4L_Fit_fa2_${fa2}_fixedFs_profile_a2_lumi100 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/runA2Scan.sh $a3a1 YNNNNN NNNNNN NNNNNNNNNNNN 100.0 LikelihoodFile_fa2_${fa2}_fixedFs_profile_a2_lumi100.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/FitResults/FA2/

end


foreach i(`seq 1 1 99`)

  set fa2 = `echo "" | awk "{print -1 + $i * 2.0/100}"`
  set a2a1 = `echo "" | awk "{print sqrt( 1 / (1 - sqrt($fa2*$fa2))*sqrt($fa2*$fa2)*3.276*3.276)}"`

  set fa2Negative = `echo "" | awk "{if($fa2 < 0){print 1}}"`
  if ($fa2Negative == "1") then
    set a2a1 = `echo "" | awk "{print -1*$a2a1}"`
  endif
  echo $fa2 " " $a2a1

  bsub -q 1nd -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/Fit_fa2_${fa2}_fixedFs_profile_a3phase_lumi100.out -J HZZ4L_Fit_fa2_${fa2}_fixedFs_profile_a3phase_lumi100 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/runA2Scan.sh $a3a1 NNNNNN NYNNNN NNNNNNNNNNNN 100.0 LikelihoodFile_fa2_${fa2}_fixedFs_profile_a3phase_lumi100.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/FitResults/FA2/

end
 
foreach i(`seq 1 1 99`)

  set fa2 = `echo "" | awk "{print -1 + $i * 2.0/100}"`
  set a2a1 = `echo "" | awk "{print sqrt( 1 / (1 - sqrt($fa2*$fa2))*sqrt($fa2*$fa2)*3.276*3.276)}"`

  set fa2Negative = `echo "" | awk "{if($fa2 < 0){print 1}}"`
  if ($fa2Negative == "1") then
    set a2a1 = `echo "" | awk "{print -1*$a2a1}"`
  endif
  echo $fa2 " " $a2a1

  bsub -q 1nd -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/Fit_fa2_${fa2}_fixedFs_profile_a2a2phasea3phase_lumi100.out -J HZZ4L_Fit_fa2_${fa2}_fixedFs_profile_a2a2phasea3phase_lumi100 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/runA2Scan.sh $a3a1 YNNNNN YYNNNN NNNNNNNNNNNN 100.0 LikelihoodFile_fa2_${fa2}_fixedFs_profile_a2a2phasea3phase_lumi100.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/FitResults/FA2/

end
 

################
#Float Fs
################







foreach i(`seq 1 1 99`)

  set fa2 = `echo "" | awk "{print -1 + $i * 2.0/100}"`
  set a2a1 = `echo "" | awk "{print sqrt( 1 / (1 - sqrt($fa2*$fa2))*sqrt($fa2*$fa2)*3.276*3.276)}"`

  set fa2Negative = `echo "" | awk "{if($fa2 < 0){print 1}}"`
  if ($fa2Negative == "1") then
    set a2a1 = `echo "" | awk "{print -1*$a2a1}"`
  endif
  echo $fa2 " " $a2a1

  bsub -q 1nd -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/Fit_fa2_${fa2}_floatFs_profile_nothing_lumi1.out -J HZZ4L_Fit_fa2_${fa2}_floatFs_profile_nothing_lumi1 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/runA2Scan.sh $a2a1 NNNNNN NNNNNN YNYYYNYYYNYY 1.0 LikelihoodFile_fa2_${fa2}_floatFs_profile_nothing_lumi1.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/FitResults/FA2/

end

foreach i(`seq 1 1 99`)

  set fa2 = `echo "" | awk "{print -1 + $i * 2.0/100}"`
  set a2a1 = `echo "" | awk "{print sqrt( 1 / (1 - sqrt($fa2*$fa2))*sqrt($fa2*$fa2)*3.276*3.276)}"`

  set fa2Negative = `echo "" | awk "{if($fa2 < 0){print 1}}"`
  if ($fa2Negative == "1") then
    set a2a1 = `echo "" | awk "{print -1*$a2a1}"`
  endif
  echo $fa2 " " $a2a1

  bsub -q 1nd -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/Fit_fa2_${fa2}_floatFs_profile_nothing_lumi10.out -J HZZ4L_Fit_fa2_${fa2}_floatFs_profile_nothing_lumi10 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/runA2Scan.sh $a2a1 NNNNNN NNNNNN YNYYYNYYYNYY N 10.0 LikelihoodFile_fa2_${fa2}_floatFs_profile_nothing_lumi10.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/FitResults/FA2/

end
 

foreach i(`seq 1 1 99`)

  set fa2 = `echo "" | awk "{print 0 + $i * 2.0/100}"`
  set a2a1 = `echo "" | awk "{print sqrt( 1 / (1 - sqrt($fa2*$fa2))*sqrt($fa2*$fa2)*3.276*3.276)}"`

  set fa2Negative = `echo "" | awk "{if($fa2 < 0){print 1}}"`
  if ($fa2Negative == "1") then
    set a2a1 = `echo "" | awk "{print -1*$a2a1}"`
  endif
  echo $fa2 " " $a2a1

  bsub -q 1nd -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/Fit_fa2_${fa2}_floatFs_profile_a3_lumi10.out -J HZZ4L_Fit_fa2_${fa2}_floatFs_profile_a3_lumi10 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/runA2Scan.sh $a2a1 YNNNNN NNNNNN YNYYYNYYYNYY Y 10.0 LikelihoodFile_fa2_${fa2}_floatFs_profile_a3_lumi10.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/FitResults/FA2/

end


foreach i(`seq 0 1 49`)

  set fa2 = `echo "" | awk "{print 0 + $i * 2.0/100}"`
  set a2a1 = `echo "" | awk "{print sqrt( 1 / (1 - sqrt($fa2*$fa2))*sqrt($fa2*$fa2)*3.276*3.276)}"`

  set fa2Negative = `echo "" | awk "{if($fa2 < 0){print 1}}"`
  if ($fa2Negative == "1") then
    set a2a1 = `echo "" | awk "{print -1*$a2a1}"`
  endif
  echo $fa2 " " $a2a1

  bsub -q 1nd -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/Fit_fa2_${fa2}_floatFs_profile_a2phase_lumi10.out -J HZZ4L_Fit_fa2_${fa2}_floatFs_profile_a2phase_lumi10 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/runA2Scan.sh $a2a1 NNNNNN NYNNNN YNYYYNYYYNYY N 10.0 LikelihoodFile_fa2_${fa2}_floatFs_profile_a2phase_lumi10.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/FitResults/FA2/

end
 
foreach i(`seq 0 1 49`)

  set fa2 = `echo "" | awk "{print 0 + $i * 2.0/100}"`
  set a2a1 = `echo "" | awk "{print sqrt( 1 / (1 - sqrt($fa2*$fa2))*sqrt($fa2*$fa2)*3.276*3.276)}"`

  set fa2Negative = `echo "" | awk "{if($fa2 < 0){print 1}}"`
  if ($fa2Negative == "1") then
    set a2a1 = `echo "" | awk "{print -1*$a2a1}"`
  endif
  echo $fa2 " " $a2a1

  bsub -q 1nd -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/Fit_fa2_${fa2}_floatFs_profile_a3a3phasea2phase_lumi10.out -J HZZ4L_Fit_fa2_${fa2}_floatFs_profile_a3a3phasea2phase_lumi10 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/runA2Scan.sh $a2a1 YNNNNN YYNNNN YNYYYNYYYNYY Y 10.0 LikelihoodFile_fa2_${fa2}_floatFs_profile_a3a3phasea2phase_lumi10.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/FitResults/FA2/

end
 





################
#
################

