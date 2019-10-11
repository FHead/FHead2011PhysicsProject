Tag=$1

awk '{print $1-1,$1+1,($6+$7)/2,$6,$7}' < 010_RAA_R2_${Tag}.dat > R2Temp
awk '{print ($6+$7)/2,$6,$7}' < 010_RAA_R3_${Tag}.dat > R3Temp
awk '{print ($6+$7)/2,$6,$7}' < 010_RAA_R4_${Tag}.dat > R4Temp
awk '{print ($6+$7)/2,$6,$7}' < 010_RAA_R6_${Tag}.dat > R6Temp
awk '{print ($6+$7)/2,$6,$7}' < 010_RAA_R8_${Tag}.dat > R8Temp
awk '{print ($6+$7)/2,$6,$7}' < 010_RAA_R10_${Tag}.dat > R10Temp

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
