InputFile=$1

echo -n "         \"JERSF\": {\"Eta\": {Data: ["
grep -v "{" $1 | grep -v "^[ ]*$" | \
   while read EtaMin EtaMax N SF SFMinus SFPlus
   do
      echo -n "[`echo $EtaMin | AddConst 0.0001`, $SF, $SFMinus, $SFPlus],"
      echo -n "[`echo $EtaMax | SubtractConst 0.0001`, $SF, $SFMinus, $SFPlus],"
   done
echo "]}},"


