
JetR=$1
Scan=$2
Restriction=$3
Min=$4
Max=$5

./ExecuteSummary --scan $Scan \
   --input R${JetR}_NoPhi.dh,R${JetR}_NominalPhi.dh,R${JetR}_WidePhi.dh \
   --restriction "${Restriction}" \
   --label "No #phi","Nominal #phi","Wide #phi" \
   --plot "Mean" \
   --output R${JetR}_${Scan}_${Restriction//+/_}_Mean \
   --title deduce --xmin $Min --xmax $Max --ymin 0.5 --ymax 1.5
./ExecuteSummary --scan $Scan \
   --input R${JetR}_NoPhi.dh,R${JetR}_NominalPhi.dh,R${JetR}_WidePhi.dh \
   --restriction "${Restriction}" \
   --label "No #phi","Nominal #phi","Wide #phi" \
   --plot "RMS" \
   --output R${JetR}_${Scan}_${Restriction//+/_}_RMS \
   --title deduce --xmin $Min --xmax $Max --ymin 0 --ymax 0.5
