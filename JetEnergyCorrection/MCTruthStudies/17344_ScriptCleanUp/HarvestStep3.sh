source Setup_FileLocation.sh

hadd -k -f $Step3Output/Merged.root $Step3Output/jra_*root

jet_l2_correction_x \
   -input $Step3Output/Merged.root \
   -algs ak4pfchsl1 \
   -era ParallelMC \
   -output l2.root \
   -outputDir Files/ \
   -makeCanvasVariable AbsCorVsJetPt:JetEta \
   -l2l3 true \
   -batch true \
   -histMet median \
   -delphes false \
   -maxFitIter 30 \
   -l2calofit DynamicMin \
   -l2pffit splineAkima \
   -ptclip 20




