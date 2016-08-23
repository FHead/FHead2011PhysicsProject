SEMSize=-1
BEMSize=-1
SEESize=-1
BEESize=-1

echo "universe                = vanilla"
echo "input                   ="
echo "should_transfer_files   = YES"
echo "transfer_output_files   = DummyFile"
echo "when_to_transfer_output = ON_EXIT"
echo


for j in A J L
do
   for k in 50 100 200 400 600 1000 2000 4000 7000 10000
   do
      CutString=$j

      SEMSize=$k
      SEESize=$k

      SEMFile=TreeLinks/ggtoHto2e2mu_SMVV_125GeV_noPDF_Full_1.root
      SEEFile=TreeLinks/ggtoHto4e_SMVV_125GeV_noPDF_Full_1.root
      BEMFile=Dummy.root
      BEEFile=Dummy.root
      Energy=0TeV

      JobLabel=JobBoth_SMVV_noPDF_${CutString}_$k

      echo "executable              = RunPointSMVV.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile $BEMSize $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEM_SMVV_noPDF_${CutString}_$k

      echo "executable              = RunPointSMVV.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEE_SMVV_noPDF_${i}_${CutString}_$k

      echo "executable              = RunPointSMVV.sh"
      echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo
      
      SEMFile=TreeLinks/ggtoHto2e2mu_5plet_125GeV_noPDF_Full_1.root
      SEEFile=TreeLinks/ggtoHto4e_5plet_125GeV_noPDF_Full_1.root
      BEMFile=Dummy.root
      BEEFile=Dummy.root
      Energy=0TeV

      JobLabel=JobBoth_H5_noPDF_${CutString}_$k

      echo "executable              = RunPointH5.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile $BEMSize $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEM_H5_noPDF_${CutString}_$k

      echo "executable              = RunPointH5.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEE_H5_noPDF_${i}_${CutString}_$k

      echo "executable              = RunPointH5.sh"
      echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo
      
      SEMFile=TreeLinks/ggtoHto2e2mu_5plet_125GeV_14TeV_Full_1.root
      SEEFile=TreeLinks/ggtoHto4e_5plet_125GeV_14TeV_Full_1.root
      BEMFile=Dummy.root
      BEEFile=Dummy.root
      Energy=14TeV

      JobLabel=JobBoth_H5_14TeV_${CutString}_$k

      echo "executable              = RunPointH5.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile $BEMSize $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEM_H5_14TeV_${CutString}_$k

      echo "executable              = RunPointH5.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEE_H5_14TeV_${i}_${CutString}_$k

      echo "executable              = RunPointH5.sh"
      echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo
      
      SEMFile=TreeLinks/ggtoHto2e2mu_SMZZ_125GeV_noPDF_Full_1.root
      SEEFile=TreeLinks/ggtoHto4e_SMZZ_125GeV_noPDF_Full_1.root
      BEMFile=Dummy.root
      BEEFile=Dummy.root
      Energy=0TeV

      JobLabel=JobBoth_SMZZ_noPDF_${CutString}_$k

      echo "executable              = RunPointSMZZ.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile $BEMSize $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEM_SMZZ_noPDF_${CutString}_$k

      echo "executable              = RunPointSMZZ.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEE_SMZZ_noPDF_${i}_${CutString}_$k

      echo "executable              = RunPointSMZZ.sh"
      echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo
      
      SEMFile=TreeLinks/ggtoHto2e2mu_SMZZ_125GeV_13TeV_Full_1.root
      SEEFile=TreeLinks/ggtoHto4e_SMZZ_125GeV_13TeV_Full_1.root
      BEMFile=Dummy.root
      BEEFile=Dummy.root
      Energy=13TeV

      JobLabel=JobBoth_SMZZ_13TeV_${CutString}_$k

      echo "executable              = RunPointSMZZ.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile $BEMSize $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEM_SMZZ_13TeV_${CutString}_$k

      echo "executable              = RunPointSMZZ.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEE_SMZZ_13TeV_${i}_${CutString}_$k

      echo "executable              = RunPointSMZZ.sh"
      echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo
      
      SEMFile=TreeLinks/ggtoHto2e2mu_SMZZ_125GeV_14TeV_Full_1.root
      SEEFile=TreeLinks/ggtoHto4e_SMZZ_125GeV_14TeV_Full_1.root
      BEMFile=Dummy.root
      BEEFile=Dummy.root
      Energy=14TeV

      JobLabel=JobBoth_SMZZ_14TeV_${CutString}_$k

      echo "executable              = RunPointSMZZ.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile $BEMSize $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEM_SMZZ_14TeV_${CutString}_$k

      echo "executable              = RunPointSMZZ.sh"
      echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo

      JobLabel=JobEE_SMZZ_14TeV_${i}_${CutString}_$k

      echo "executable              = RunPointSMZZ.sh"
      echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $Energy $CutString $JobLabel"
      echo "output                  = Log/$JobLabel.out"
      echo "error                   = Log/$JobLabel.err"
      echo "log                     = Log/$JobLabel.log"
      echo "queue"
      echo
      
   done
done




