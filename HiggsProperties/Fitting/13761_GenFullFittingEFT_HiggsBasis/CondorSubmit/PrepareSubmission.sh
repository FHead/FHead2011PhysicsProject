# Point O
# SEMLabel=TreeLinks/gg_h_2e2mu_A1ZZ_Mllgt1_eTlt2500_115to135GeV
# SEELabel=TreeLinks/gg_h_4e_A1ZZ_Mllgt1_eTlt2500_115to135GeV

# Point 0
SEMLabel=TreeLinks/gg_h_2e2mu_All0_Relaxed_115to135GeV
SEELabel=TreeLinks/gg_h_4e_All0_Relaxed_115to135GeV

# Background
BEMLabel=TreeLinks/ddbar_PDF_to_ZApAApZZ_to_2e2mu_Mllgt4_eTlt2d4_pTgt2_115to135GeV
BEELabel=TreeLinks/ddbar_PDF_to_ZApAApZZ_to_4e_Mllgt4_eTlt2d4_pTgt2_115to135GeV

SEMSize=-1
BEMSize=-1
SEESize=-1
BEESize=-1

PointLabel="Point0"

echo "executable              = Run${PointLabel}.sh"
echo "universe                = vanilla"
echo "input                   ="
echo "should_transfer_files   = YES"
echo "transfer_output_files   = DummyFile"
echo "when_to_transfer_output = ON_EXIT"
# echo "request_memory          = 1000"
echo


for i in `seq 1 30`
do
   # for j in A:1 B:0.5208137 C:0.5259202 D:0.5624076 E:0.6055779 F:0.3283080 G:0.5351151 H:0.5329452 I:1.2009122 J:0.5805546
   for j in A:1 H:0.5329452 I:1.2009122 J:0.5805546
   # for j in B:0.5208137 C:0.5259202 D:0.5624076 
   do
      for k in 50 100 200 400 600 1000 2000 4000 7000 10000
      do
         CutString=`echo $j | cut --delim=':' --field=1`
         SOverB=`echo $j | cut --delim=':' --field=2`
         
         SEMSize=$k
         BEMSize=`echo $k | DivideConst $SOverB`
         SEESize=$k
         BEESize=`echo $k | DivideConst $SOverB`

         HalfBEMSize=`echo $BEMSize | DivideConst 2`
         HalfBEESize=`echo $BEESize | DivideConst 2`

         SEMFile=${SEMLabel}_$i.root
         SEEFile=${SEELabel}_$i.root
         BEMFile=${BEMLabel}_$i.root
         BEEFile=${BEELabel}_$i.root

         JobLabel=JobBothHalf_${PointLabel}_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile $HalfBEMSize $BEEFile $HalfBEESize $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         # echo "queue"
         echo

         JobLabel=JobBoth_${PointLabel}_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile $BEMSize $BEEFile $BEESize $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo

         JobLabel=JobEM_${PointLabel}_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         # echo "queue"
         echo

         JobLabel=JobEE_${PointLabel}_${i}_${CutString}_$k

         echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         # echo "queue"
         echo
         
         JobLabel=JobBothS_${PointLabel}_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile -1 $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo

         JobLabel=JobEMS_${PointLabel}_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile -1 $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         # echo "queue"
         echo

         JobLabel=JobEES_${PointLabel}_${i}_${CutString}_$k

         echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         # echo "queue"
         echo
      done
   done
done




