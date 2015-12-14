SEMLabel=TreeLinks/gg_h_2e2mu_A1ZZ_Mllgt1_eTlt2500_115to135GeV
SEELabel=TreeLinks/gg_h_4e_A1ZZ_Mllgt1_eTlt2500_115to135GeV
BEMLabel=TreeLinks/ddbar_PDF_to_ZApAApZZ_to_2e2mu_Mllgt4_eTlt2d4_pTgt2_115to135GeV
BEELabel=TreeLinks/ddbar_PDF_to_ZApAApZZ_to_4e_Mllgt4_eTlt2d4_pTgt2_115to135GeV

SEMSize=-1
BEMSize=-1
SEESize=-1
BEESize=-1

echo "executable              = Run.sh"
echo "universe                = vanilla"
echo "input                   ="
echo "should_transfer_files   = YES"
echo "transfer_output_files   = DummyFile"
echo "when_to_transfer_output = ON_EXIT"
# echo "request_memory          = 2000"
echo

for i in `seq 1 100`
do
   # for j in A:1 B:0.5208137 C:0.5259202 D:0.5624076 E:0.6055779 F:0.3283080 G:0.5351151 H:0.5329452 I:1.2009122 J:0.5805546
   # for j in K:0.59533
   for j in A:1 H:0.5329452 I:1.2009122 J:0.5805546
   do
      for k in 50 100 200 400 600 1000 2000 4000 7000 10000
      do
         CutString=`echo $j | cut --delim=':' --field=1`
         SOverB=`echo $j | cut --delim=':' --field=2`

         SEMSize=$k
         BEMSize=`echo $k | DivideConst $SOverB`
         SEESize=$k
         BEESize=`echo $k | DivideConst $SOverB`

         SEMFile=${SEMLabel}_$i.root
         SEEFile=${SEELabel}_$i.root
         BEMFile=${BEMLabel}_$i.root
         BEEFile=${BEELabel}_$i.root

         JobLabel=JobBoth_A1ZZ_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile $BEMSize $BEEFile $BEESize $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo

         JobLabel=JobEM_A1ZZ_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         # echo "queue"
         echo

         JobLabel=JobEE_A1ZZ_${i}_${CutString}_$k

         echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         # echo "queue"
         echo

         JobLabel=JobBothS_A1ZZ_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile -1 $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo

         JobLabel=JobEMS_A1ZZ_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile -1 $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo

         JobLabel=JobEES_A1ZZ_${i}_${CutString}_$k

         echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo
      done
   done
done

exit

SEMLabel=TreeLinks/gg_h_2e2mu_SMZZ1ZA2AA2_ZZ2d01_ZZ4d009_Mllgt1_eTlt2500_115to135GeV
SEELabel=TreeLinks/gg_h_4e_SMZZ1ZA2AA2_ZZ2d01_ZZ4d009_Mllgt1_eTlt2500_115to135GeV
BEMLabel=TreeLinks/ddbar_PDF_to_ZApAApZZ_to_2e2mu_Mllgt4_eTlt2d4_pTgt2_115to135GeV
BEELabel=TreeLinks/ddbar_PDF_to_ZApAApZZ_to_4e_Mllgt4_eTlt2d4_pTgt2_115to135GeV

SEMSize=-1
BEMSize=-1
SEESize=-1
BEESize=-1

for i in `seq 1 100`
do
   for j in A:1 B:0.5208137 C:0.5259202 D:0.5624076 E:0.6055779 F:0.3283080 G:0.5351151 H:0.5329452 I:1.2009122 J:0.5805546
   # for j in A:1
   do
      for k in 50 100 200 400 600 1000 2000 4000 7000 10000
      do
         CutString=`echo $j | cut --delim=':' --field=1`
         SOverB=`echo $j | cut --delim=':' --field=2`
         
         SEMSize=$k
         BEMSize=`echo $k | DivideConst $SOverB`
         SEESize=$k
         BEESize=`echo $k | DivideConst $SOverB`

         SEMFile=${SEMLabel}_$i.root
         SEEFile=${SEELabel}_$i.root
         BEMFile=${BEMLabel}_$i.root
         BEEFile=${BEELabel}_$i.root

         JobLabel=JobBoth_SM_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile $BEMSize $BEEFile $BEESize $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo

         JobLabel=JobEM_SM_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo

         JobLabel=JobEE_SM_${i}_${CutString}_$k

         echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo
         
         JobLabel=JobBothS_SM_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile -1 $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo

         JobLabel=JobEMS_SM_${i}_${CutString}_$k

         echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile -1 $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo

         JobLabel=JobEES_SM_${i}_${CutString}_$k

         echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile -1 $CutString $JobLabel"
         echo "output                  = Log/$JobLabel.out"
         echo "error                   = Log/$JobLabel.err"
         echo "log                     = Log/$JobLabel.log"
         echo "queue"
         echo
      done
   done
done




