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

for i in SMVV:5 5plet:5
do
   tag=`echo $i | tr ':' ' ' | awk '{print $1}'`
   max=`echo $i | tr ':' ' ' | awk '{print $2}'`
   for ii in `seq 1 $max`
   do
      for j in A J L
      do
         for k in 50 100 200 400 600 1000 2000 4000 7000 10000
         do
            CutString=$j

            SEMSize=$k
            SEESize=$k

            SEMFile=Trees15236/ggtoHto2e2mu_${tag}_125GeV_noPDF_Full_${ii}.root
            SEEFile=Trees15236/ggtoHto4e_${tag}_125GeV_noPDF_Full_${ii}.root
            BEMFile=Dummy.root
            BEEFile=Dummy.root
            Energy=0TeV

            JobLabel=JobEM_${tag}_noPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo

            JobLabel=JobEE_${tag}_noPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo

            JobLabel=JobBoth_${tag}_noPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEESize $SEEFile $SEESize $BEMFile $BEESize $BEEFile $BEESize $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo
         done
      done
   done
done

for i in SMVV:5 
do
   tag=`echo $i | tr ':' ' ' | awk '{print $1}'`
   max=`echo $i | tr ':' ' ' | awk '{print $2}'`
   for ii in `seq 1 $max`
   do
      for j in A J L
      do
         for k in 50 100 200 400 600 1000 2000 4000 7000 10000
         do
            CutString=$j

            SEMSize=$k
            SEESize=$k

            SEMFile=Trees15236/ggtoHto2e2mu_${tag}_115to135GeV_ggPDF_13TeV_GenCuts_${ii}.root
            SEEFile=Trees15236/ggtoHto4e_${tag}_115to135GeV_ggPDF_13TeV_GenCuts_${ii}.root
            BEMFile=Dummy.root
            BEEFile=Dummy.root
            Energy=0TeV

            JobLabel=JobEM_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEMSize $SEEFile -1 $BEMFile $BEMSize $BEEFile -1 $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo

            JobLabel=JobEE_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile -1 $SEEFile $SEESize $BEMFile -1 $BEEFile $BEESize $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo

            JobLabel=JobBoth_${tag}_ggPDF_${CutString}_${k}_${ii}

            echo "executable              = RunPoint${tag}.sh"
            echo "arguments               = $SEMFile $SEESize $SEEFile $SEESize $BEMFile $BEESize $BEEFile $BEESize $Energy $CutString $JobLabel"
            echo "output                  = Log/$JobLabel.out"
            echo "error                   = Log/$JobLabel.err"
            echo "log                     = Log/$JobLabel.log"
            echo "queue"
            echo
         done
      done
   done
done





