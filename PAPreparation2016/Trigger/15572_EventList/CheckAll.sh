for i in HLT_PA*txt
do
   echo $i
   cd ${i/.txt}
   crab status -d crab_pickEvents/
   cd ..
done
