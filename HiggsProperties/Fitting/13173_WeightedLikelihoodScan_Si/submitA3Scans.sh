/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/RunLikelihood \
/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/SignalAll7TeV.root \
/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/BackgroundAll7TeV.root  \
/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_MC_ZJets_8TeV.root \
/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_ggZZ.root \
/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/SignalAll8TeV.root  \
/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/BackgroundAll8TeV.root  \
/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_MC_ZJets_8TeV.root \
/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_ggZZ.root \
 0 0 0 0 0 0 0 -1 NNNNNNNN NNNNNNNN NNNNNNNNNNNN NNNN

/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/RunLikelihoodBatch \
/afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/SignalAll7TeV.root \
1000 0 7 -1 0 \
 0 0 0 0 0 0 0 -1 





foreach f(`seq 0 1 92`)
  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/SignalAll8TeV.root -1 8 50000 ${f} FA3_Signal8TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/
end

foreach f(`seq 0 1 47`)
  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/BackgroundAll8TeV.root 0 8 50000 ${f} FA3_Background8TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/
end

foreach f(`seq 0 1 29`)
  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/HZZEventFitFormat_MC_ZJets_8TeV.root 1 8 50000 ${f} FA3_ZJets8TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/
end

foreach f(`seq 0 1 16`)
  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_ggZZ.root 1 8 50000 ${f} FA3_ggZZ8TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/
end

foreach f(`seq 0 1 57`)
  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/SignalAll7TeV.root -1 7 50000 ${f} FA3_Signal7TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/
end

foreach f(`seq 0 1 119`)
  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/BackgroundAll7TeV.root 0 7 50000 ${f} FA3_Background7TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/
end

foreach f(`seq 0 1 29`)
  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/HZZEventFitFormat_MC_ZJets_8TeV.root 1 7 50000 ${f} FA3_ZJets7TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/
end

foreach f(`seq 0 1 16`)
  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_ggZZ.root 1 7 50000 ${f} FA3_ggZZ7TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/
end

 
##################################################
#Combine Trees
##################################################
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Signal8TeV_8TeV_channel0 93 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Signal8TeV_8TeV_channel0_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Signal7TeV_7TeV_channel0 57 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Signal7TeV_7TeV_channel0_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Background8TeV_8TeV_channel0 47 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Background8TeV_8TeV_channel0_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Background7TeV_7TeV_channel0 119 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Background7TeV_7TeV_channel0_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ZJets8TeV_8TeV_channel0 29 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ZJets8TeV_8TeV_channel0_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ZJets7TeV_7TeV_channel0 29 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ZJets7TeV_7TeV_channel0_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ggZZ8TeV_8TeV_channel0 16 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ggZZ8TeV_8TeV_channel0_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ggZZ7TeV_7TeV_channel0 16 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ggZZ7TeV_7TeV_channel0_combined.root

/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Signal8TeV_8TeV_channel1 93 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Signal8TeV_8TeV_channel1_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Signal7TeV_7TeV_channel1 57 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Signal7TeV_7TeV_channel1_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Background8TeV_8TeV_channel1 47 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Background8TeV_8TeV_channel1_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Background7TeV_7TeV_channel1 119 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Background7TeV_7TeV_channel1_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ZJets8TeV_8TeV_channel1 29 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ZJets8TeV_8TeV_channel1_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ZJets7TeV_7TeV_channel1 29 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ZJets7TeV_7TeV_channel1_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ggZZ8TeV_8TeV_channel1 16 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ggZZ8TeV_8TeV_channel1_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ggZZ7TeV_7TeV_channel1 16 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ggZZ7TeV_7TeV_channel1_combined.root

/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Signal8TeV_8TeV_channel2 93 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Signal8TeV_8TeV_channel2_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Signal7TeV_7TeV_channel2 57 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Signal7TeV_7TeV_channel2_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Background8TeV_8TeV_channel2 47 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Background8TeV_8TeV_channel2_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Background7TeV_7TeV_channel2 119 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Background7TeV_7TeV_channel2_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ZJets8TeV_8TeV_channel2 29 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ZJets8TeV_8TeV_channel2_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ZJets7TeV_7TeV_channel2 29 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ZJets7TeV_7TeV_channel2_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ggZZ8TeV_8TeV_channel2 16 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ggZZ8TeV_8TeV_channel2_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ggZZ7TeV_7TeV_channel2 16 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ggZZ7TeV_7TeV_channel2_combined.root

/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Signal8TeV_8TeV_channel3 93 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Signal8TeV_8TeV_channel3_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Signal7TeV_7TeV_channel3 57 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Signal7TeV_7TeV_channel3_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Background8TeV_8TeV_channel3 47 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Background8TeV_8TeV_channel3_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_Background7TeV_7TeV_channel3 119 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_Background7TeV_7TeV_channel3_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ZJets8TeV_8TeV_channel3 29 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ZJets8TeV_8TeV_channel3_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ZJets7TeV_7TeV_channel3 29 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ZJets7TeV_7TeV_channel3_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ggZZ8TeV_8TeV_channel3 16 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ggZZ8TeV_8TeV_channel3_combined.root
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihoodJobs /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_ggZZ7TeV_7TeV_channel3 16 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_ggZZ7TeV_7TeV_channel3_combined.root



##################################################
#Final Combine
##################################################
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihood /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/FA3_combined.root










##################################################
#Run on unweighted sample
##################################################
set f=0

  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/unweighted/SignalAll8TeV.root -1 8 -1 ${f} FA3_Signal8TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/

  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/unweighted/BackgroundAll8TeV.root 0 8 -1 ${f} FA3_Background8TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/

  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_MC_ZJets_8TeV.root 1 8 -1 ${f} FA3_ZJets8TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/

  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_ggZZ_8TeV.root 1 8 -1 ${f} FA3_ggZZ8TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/

  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Signal7TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal7TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/unweighted/SignalAll7TeV.root -1 7 -1 ${f} FA3_Signal7TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/

  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_Background7TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Background7TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/unweighted/BackgroundAll7TeV.root 0 7 -1 ${f} FA3_Background7TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/

  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_ZJets7TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_ZJets7TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_MC_ZJets_8TeV.root 1 7 -1 ${f} FA3_ZJets7TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/

  bsub -q 8nh -o /afs/cern.ch/user/s/sixie/work/private/condor/res/HZZ4L/LikelihoodBatch_fa3_ggZZ7TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_ggZZ8TeV_Job${f}  /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_ggZZ_8TeV.root 1 7 -1 ${f} FA3_ggZZ7TeV /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/


############   Combine   ############
/afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/CombineLikelihood /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3 /afs/cern.ch/work/s/sixie/public/PhysicsWorkspace/HiggsProperties/Fitting/13173_WeightedLikelihoodScan/LikelihoodScanResults/jobs/FA3_combined.root

