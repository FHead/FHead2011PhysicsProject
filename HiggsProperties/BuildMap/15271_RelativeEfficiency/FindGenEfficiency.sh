for i in 5plet SMVV
do
   for j in 2e2mu 4e
   do
      echo -n "$i $j "
      ./Run Trees15274/ggtoHto${j}_${i}_115to135GeV_ggPDF_13TeV_ForEff_1.root \
         | awk '{print $3/$2}' \
         | DivideConst `DHQueryDouble Efficiencies.dh ${i}_${j} CutA`
   done
done 2>/dev/null

