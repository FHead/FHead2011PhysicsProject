Tag=$1

awk '{print $1-1,$1+1,1,1,1}' < 010_${Tag}_r_RAA_R3_over_R2.dat > R2Temp
awk '{print ($6+$7)/2,$6,$7}' < 010_${Tag}_r_RAA_R3_over_R2.dat > R3Temp
awk '{print ($6+$7)/2,$6,$7}' < 010_${Tag}_r_RAA_R4_over_R2.dat > R4Temp
awk '{print ($6+$7)/2,$6,$7}' < 010_${Tag}_r_RAA_R6_over_R2.dat > R6Temp
awk '{print ($6+$7)/2,$6,$7}' < 010_${Tag}_r_RAA_R8_over_R2.dat > R8Temp
awk '{print ($6+$7)/2,$6,$7}' < 010_${Tag}_r_RAA_R10_over_R2.dat > R10Temp

FileLineAppend R2Temp R3Temp Total
mv Total Temp
FileLineAppend Temp R4Temp Total
mv Total Temp
FileLineAppend Temp R6Temp Total
mv Total Temp
FileLineAppend Temp R8Temp Total
mv Total Temp
FileLineAppend Temp R10Temp Total

rm Temp R*Temp
mv Total Daniel_$Tag.txt
