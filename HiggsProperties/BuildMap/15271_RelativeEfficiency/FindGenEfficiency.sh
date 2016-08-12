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

for i in 5PpYT SMpMYT
do
   for j in 2e2mu 4e
   do
      echo -n "$i $j "
      ./Run Trees15315/ggtoHto${j}_${i}_115to135GeV_ggPDF_13TeV_ForEff_1.root \
         | awk '{print $3/$2}' \
         | DivideConst `DHQueryDouble Efficiencies.dh ${i}_${j} CutA`
   done
done 2>/dev/null

for i in uu dd
do
   for j in 2e2mu 4e
   do
      echo -n "$i $j "
      ./Run Trees15274/${i}to${j}_115to135GeV_${i}barPDF_13TeV_ForEff_1.root \
         | awk '{print $3/$2}' \
         | DivideConst `DHQueryDouble Efficiencies.dh ${i}bar_${j} CutA`
   done
done 2>/dev/null
