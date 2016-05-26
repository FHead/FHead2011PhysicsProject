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

for i in SMVV:30 5plet:30
do
   tag=`echo $i | tr ':' ' ' | awk '{print $1}'`
   max=`echo $i | tr ':' ' ' | awk '{print $2}'`
   for ii in `seq 1 $max`
   do
      for j in A J
      do
         for k in 50 100 200 400 600 1000 2000 4000 7000 10000
         do
            CutString=$j

            SEMSize=$k
            SEESize=$k

            SEMFile=Trees15251/ggtoHto2e2mu_${tag}_115to135GeV_ggPDF_13TeV_GenCuts_${ii}.root
            SEEFile=Trees15251/ggtoHto4e_${tag}_115to135GeV_ggPDF_13TeV_GenCuts_${ii}.root
            BEMFile1=Trees15254/uuto2e2mu_115to135GeV_uubarPDF_13TeV_GenCuts_${ii}.root
            BEEFile1=Trees15254/uuto4e_115to135GeV_uubarPDF_13TeV_GenCuts_${ii}.root
            BEMFile2=Trees15254/ddto2e2mu_115to135GeV_ddbarPDF_13TeV_GenCuts_${ii}.root
            BEEFile2=Trees15254/ddto4e_115to135GeV_ddbarPDF_13TeV_GenCuts_${ii}.root
            Energy=13TeV

            BEMSize=$k
            BEESize=$k

            BEMSize1=-1
            BEESize1=-1
            BEMSize2=$BEMSize
            BEESize2=$BEESize

            JobLabel=JobEMS_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile1 -1 $BEEFile1 -1 $BEMFile2 -1 $BEEFile2 -1 $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            # echo "queue"
            echo

            JobLabel=JobEES_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile1 -1 $BEEFile1 -1 $BEMFile2 -1 $BEEFile2 -1 $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            # echo "queue"
            echo

            JobLabel=JobBothS_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEESize $SEEFile $SEESize $BEMFile1 -1 $BEEFile1 -1 $BEMFile2 -1 $BEEFile2 -1 $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo

            JobLabel=JobEM_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize1 $BEEFile1 -1 $BEMFile2 $BEMSize2 $BEEFile2 -1 $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo

            JobLabel=JobEE_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile1 -1 $BEEFile1 $BEESize1 $BEMFile2 -1 $BEEFile2 $BEESize2 $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo

            JobLabel=JobBoth_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEESize $SEEFile $SEESize $BEMFile1 $BEMSize1 $BEEFile1 $BEESize1 $BEMFile2 $BEMSize2 $BEEFile2 $BEESize2 $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo
         done
      done
   done
done





