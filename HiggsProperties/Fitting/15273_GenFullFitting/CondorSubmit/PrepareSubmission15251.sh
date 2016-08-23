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
         for k in 25 50 100 200 400 800 1600 3200 6400 12800 25600
         do
            CutString=$j

            Luminosity=$k

            SEMSize=`DHQueryDouble Yields.dh ${tag}_2e2mu Cut${j} | MultiplyConst $k`
            SEESize=`DHQueryDouble Yields.dh ${tag}_4e Cut${j} | MultiplyConst $k`

            BEMSize1=`DHQueryDouble Yields.dh uubar_2e2mu Cut${j} | MultiplyConst $k`
            BEMSize2=`DHQueryDouble Yields.dh ddbar_2e2mu Cut${j} | MultiplyConst $k`
            BEESize1=`DHQueryDouble Yields.dh uubar_4e Cut${j} | MultiplyConst $k`
            BEESize2=`DHQueryDouble Yields.dh ddbar_4e Cut${j} | MultiplyConst $k`

            UUbarDDbarRatio2e2mu=`echo $BEMSize1 | DivideConst $BEMSize2`
            UUbarDDbarRatio4e=`echo $BEESize1 | DivideConst $BEESize2`
            
            BEMSize=`echo $BEMSize1 | AddConst $BEMSize2`
            BEESize=`echo $BEESize1 | AddConst $BEESize2`

            SEMFile=Trees15251/ggtoHto2e2mu_${tag}_115to135GeV_ggPDF_13TeV_GenCuts_${ii}.root
            SEEFile=Trees15251/ggtoHto4e_${tag}_115to135GeV_ggPDF_13TeV_GenCuts_${ii}.root
            BEMFile1=Trees15254/uuto2e2mu_115to135GeV_uubarPDF_13TeV_GenCuts_${ii}.root
            BEEFile1=Trees15254/uuto4e_115to135GeV_uubarPDF_13TeV_GenCuts_${ii}.root
            BEMFile2=Trees15254/ddto2e2mu_115to135GeV_ddbarPDF_13TeV_GenCuts_${ii}.root
            BEEFile2=Trees15254/ddto4e_115to135GeV_ddbarPDF_13TeV_GenCuts_${ii}.root
            Energy=13TeV

            JobLabel=JobEMS_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile1 -1 $BEEFile1 -1 $BEMFile2 -1 $BEEFile2 -1 $Energy $CutString $JobLabel $UUbarDDbarRatio2e2mu $UUbarDDbarRatio4e"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            # echo "queue"
            echo

            JobLabel=JobEES_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile1 -1 $BEEFile1 -1 $BEMFile2 -1 $BEEFile2 -1 $Energy $CutString $JobLabel $UUbarDDbarRatio2e2mu $UUbarDDbarRatio4e"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            # echo "queue"
            echo

            JobLabel=JobBothS_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile1 -1 $BEEFile1 -1 $BEMFile2 -1 $BEEFile2 -1 $Energy $CutString $JobLabel $UUbarDDbarRatio2e2mu $UUbarDDbarRatio4e"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo

            JobLabel=JobEM_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize1 $BEEFile1 -1 $BEMFile2 $BEMSize2 $BEEFile2 -1 $Energy $CutString $JobLabel $UUbarDDbarRatio2e2mu $UUbarDDbarRatio4e"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            # echo "queue"
            echo

            JobLabel=JobEE_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile1 -1 $BEEFile1 $BEESize1 $BEMFile2 -1 $BEEFile2 $BEESize2 $Energy $CutString $JobLabel $UUbarDDbarRatio2e2mu $UUbarDDbarRatio4e"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            # echo "queue"
            echo

            JobLabel=JobBoth_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEMSize $SEEFile $SEESize $BEMFile1 $BEMSize1 $BEEFile1 $BEESize1 $BEMFile2 $BEMSize2 $BEEFile2 $BEESize2 $Energy $CutString $JobLabel $UUbarDDbarRatio2e2mu $UUbarDDbarRatio4e"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo
         done
      done
   done
done





