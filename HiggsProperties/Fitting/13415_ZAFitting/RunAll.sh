mkdir -p Temp

for i in 100 200 400 800 1600 3200 6400 12800
do
   for j in `seq 1 10`
   do
      S1=Trees/gg_h_2eA_CPV1_ZApAA_LooseCuts_$j.root
      S2=Trees/gg_h_2eA_SM_ZApAA_LooseCuts_$j.root
      B=Trees/ddbar_to_ZApAA_to_2eA_LooseCuts_$j.root

      ./PerformFits $S1 $i $B -1 0.014 0 -0.008 0
      mv OutputFile.root Temp/Result_CPV_${i}_${j}.root
      ./PerformFits $S2 $i $B -1 0.014 0 -0.008 0
      mv OutputFile.root Temp/Result_SM_${i}_${j}.root
   done
done

hadd -f Reuslt_CPV.root Temp/Result_CPV_*
hadd -f Reuslt_SM.root Temp/Result_SM_*

