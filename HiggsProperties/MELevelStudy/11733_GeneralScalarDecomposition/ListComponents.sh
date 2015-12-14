echo Component list
for i in A1ZZR A1ZZI A2ZZR A2ZZI A3ZZR A3ZZI A2ZAR A2ZAI A3ZAR A3ZAI A2AAR A2AAI A3AAR A3AAI
do
   echo $i `grep $i Parts_* | grep -o "Parts_[0-9]*" | uniq | tr '\n' ' '`
done
echo

echo File list
for i in `seq 1 36`
do
   File="Parts_$i.txt"
   echo $File `grep -o A[1-3][ZA][ZA][RI] $File | sort | uniq | tr '\n' ' '`
done
echo
