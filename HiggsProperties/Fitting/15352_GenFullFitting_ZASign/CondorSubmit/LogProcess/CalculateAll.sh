mkdir -p Calculated

# CompileRootMacro FixedYT.cpp DoFixed
# CompileRootMacro IntegrateYT.cpp DoIntegrate
# CompileRootMacro HypTest.cpp DoHypTest

for i in `seq 1 120`
do
   for j in A J
   do
      for k in JobBoth JobBothS
      do
         for m in 25 50 100 200 400 800 1600 3200 6400 12800 25600
         do
            for l in SMVV 5plet
            do
               FileName=${k}_${l}_ggPDF_${j}_${m}_${i}.out
               if [ -e Log/$FileName ] && [ -s Log/$FileName ]
               then
                  echo Processing $FileName
                  if [ ! -e Calculated/Fix_$FileName ] || [ ! -s Calculated/Fix_$FileName ]
                  then
                     echo Fix Log/$FileName
                     grep LikelihoodLog Log/$FileName | cut --delim=' ' --field=2- \
                        | ./DoFixed > Calculated/Fix_$FileName
                  fi
                  if [ ! -e Calculated/Int_$FileName ] || [ ! -s Calculated/Int_$FileName ]
                  then
                     echo Int Log/$FileName
                     grep IntYT Log/$FileName | ./DoIntegrate > Calculated/Int_$FileName
                  fi
                  if [ ! -e Calculated/Hyp_$FileName ] || [ ! -s Calculated/Hyp_$FileName ]
                  then
                     echo Hyp Log/$FileName
                     grep HypTest Log/$FileName | ./DoHypTest > Calculated/Hyp_$FileName
                  fi
               fi
            done
         done
      done
   done
done


