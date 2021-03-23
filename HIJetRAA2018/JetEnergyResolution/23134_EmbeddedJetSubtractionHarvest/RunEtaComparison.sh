
JetR=$1
Scan=$2
Restriction=$3
Min=$4
Max=$5
PhiType=$6

./ExecuteSummary --scan $Scan \
   --input R${JetR}_${PhiType}.dh,R${JetR}_${PhiType}.dh,R${JetR}_${PhiType}.dh,R${JetR}_${PhiType}.dh,R${JetR}_${PhiType}.dh,R${JetR}_${PhiType}.dh \
   --restriction "${Restriction}+Eta0","${Restriction}+Eta1","${Restriction}+Eta2","${Restriction}+Eta3","${Restriction}+Eta4","${Restriction}+Eta5" \
   --label "0.0-0.5","0.5-1.0","1.0-1.5","1.5-2.0","2.0-2.5","2.5-3.0" \
   --plot "Mean" \
   --output R${JetR}_${Scan}_${Restriction//+/_}_EtaBins_${PhiType}_Mean \
   --title deduce --xmin $Min --xmax $Max --ymin 0.6 --ymax 1.4
./ExecuteSummary --scan $Scan \
   --input R${JetR}_${PhiType}.dh,R${JetR}_${PhiType}.dh,R${JetR}_${PhiType}.dh,R${JetR}_${PhiType}.dh,R${JetR}_${PhiType}.dh,R${JetR}_${PhiType}.dh \
   --restriction "${Restriction}+Eta0","${Restriction}+Eta1","${Restriction}+Eta2","${Restriction}+Eta3","${Restriction}+Eta4","${Restriction}+Eta5" \
   --label "0.0-0.5","0.5-1.0","1.0-1.5","1.5-2.0","2.0-2.5","2.5-3.0" \
   --plot "RMS" \
   --output R${JetR}_${Scan}_${Restriction//+/_}_EtaBins_${PhiType}_RMS \
   --title deduce --xmin $Min --xmax $Max --ymin 0.0 --ymax 0.5
