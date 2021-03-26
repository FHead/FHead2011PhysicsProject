Year=$1

for i in 1:8 2:8 3:8 4:8 5:8 6:10 7:12 8:14 9:16
do
   X=`echo $i | cut -d ':' -f 1`
   Y=`echo $i | cut -d ':' -f 2`

   jet_l2_correction_x \
      -input jra${Year}.root \
      -algs ak${X}pf \
      -era MeowMC${Year} \
      -output l2.root \
      -outputDir ./ \
      -makeCanvasVariable AbsCorVsJetPt:JetEta \
      -l2l3 true \
      -batch true \
      -histMet median \
      -delphes false \
      -maxFitIter 30 \
      -l2calofit DynamicMin \
      -l2pffit splineAkima \
      -ptclip ${Y}
done

