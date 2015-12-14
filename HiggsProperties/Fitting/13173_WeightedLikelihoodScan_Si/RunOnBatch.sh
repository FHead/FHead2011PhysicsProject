
ResultFolder=`pwd`/Result/
JobFolder=`pwd`/Jobs/

mkdir -p $ResultFolder
mkdir -p $JobFolder

for f in `seq 0 1 92`
do
  bsub -q 8nh -o $ResultFolder/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  `pwd`/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/SignalAll8TeV.root -1 8 50000 ${f} FA2FA3_Signal8TeV $JobFolder
done

for f in `seq 0 1 47`
do
  bsub -q 8nh -o $ResultFolder/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  `pwd`/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/BackgroundAll8TeV.root 0 8 50000 ${f} FA2FA3_Background8TeV $JobFolder
done

for f in `seq 0 1 29`
do
  bsub -q 8nh -o $ResultFolder/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  `pwd`/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/HZZEventFitFormat_MC_ZJets_8TeV.root 1 8 50000 ${f} FA2FA3_ZJets8TeV $JobFolder
done

for f in `seq 0 1 16`
do
  bsub -q 8nh -o $ResultFolder/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  `pwd`/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_ggZZ.root 1 8 50000 ${f} FA2FA3_ggZZ8TeV $JobFolder
done

for f in `seq 0 1 57`
do
  bsub -q 8nh -o $ResultFolder/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  `pwd`/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/SignalAll7TeV.root -1 7 50000 ${f} FA2FA3_Signal7TeV $JobFolder
done

for f in `seq 0 1 119`
do
  bsub -q 8nh -o $ResultFolder/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  `pwd`/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/HZZEventFitFormat/RecoToys/BackgroundAll7TeV.root 0 7 50000 ${f} FA2FA3_Background7TeV $JobFolder
done

for f in `seq 0 1 29`
do
  bsub -q 8nh -o $ResultFolder/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  `pwd`/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/HZZEventFitFormat_MC_ZJets_8TeV.root 1 7 50000 ${f} FA2FA3_ZJets7TeV $JobFolder
done

for f in `seq 0 1 16`
do
   bsub -q 8nh -o $ResultFolder/LikelihoodBatch_fa3_Signal8TeV_Job${f}.out -J HZZ4L_LikelihoodBatch_fa3_Signal8TeV_Job${f}  `pwd`/runA3Scan.sh /afs/cern.ch/work/s/sixie/public/HZZ4l/CouplingFit/RecoToyFits/InputEvents/unweighted/HZZEventFitFormat_ggZZ.root 1 7 50000 ${f} FA2FA3_ggZZ7TeV $JobFolder
done


