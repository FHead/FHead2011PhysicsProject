#test
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/RunLikelihood Trees/SyncToys_7TeV_SMSignal.root Trees/SyncToys_7TeV_Bkg.root Trees/SyncToys_7TeV_Bkg.root Trees/SyncToys_7TeV_Bkg.root Trees/SyncToys_8TeV_SMSignal.root Trees/SyncToys_8TeV_Bkg.root Trees/SyncToys_8TeV_Bkg.root Trees/SyncToys_8TeV_Bkg.root 0 0 0 0 0 0 0 20 NNNNNNNN YYNNNNNN



/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/RunLikelihood /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_SMSignal.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_SMSignal.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root 0 0 0 0 0 0 0 20 NNNNNNNN YYNNNNNN





foreach i(`seq 1 1 99`)

set fa3 = `echo "" | awk "{print -1 + $i * 2.0/100}"`
set a2a1 = 0
set s2 = `echo "" | awk "{print $a2a1*$a2a1 / 3.276 / 3.276}"`
set a3a1 = `echo "" | awk "{print sqrt( (1+s2) / (1 - sqrt($fa3*$fa3))*sqrt($fa3*$fa3)*5.042*5.042)}"`

set fa3Negative = `echo "" | awk "{if($fa3 < 0){print 1}}"`
if ($fa3Negative == "1") then
  set a3a1 = `echo "" | awk "{print -1*$a3a1}"`
endif
echo $fa3 " " $a3a1

  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/RunLikelihood /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_SMSignal.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_7TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_SMSignal.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13162_FromToyNumber/Trees/SyncToys_8TeV_Bkg.root 0 0 0 0 0 0 0 20 NNNNNNNN YYNNNNNN


  mv LikelihoodFile.root LikelihoodFile_fa3_${fa3}_profile_a2.root 

end
 
 
