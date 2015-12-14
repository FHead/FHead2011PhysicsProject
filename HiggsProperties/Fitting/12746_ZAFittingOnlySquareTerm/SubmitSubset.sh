Submit()
{
   for index in `seq 1 $2`
   do
      RunNumber=`printf "%03d" $index`
      echo qsub BatchSubmit/Run_Events_ZA01$RunNumber.root_$1.sh
      qsub BatchSubmit/Run_Events_ZA01$RunNumber.root_$1.sh
   done
}

Submit 1 1
Submit 2 1
Submit 3 2
Submit 4 5
Submit 5 10
Submit 6 20
Submit 7 30
Submit 8 60
Submit 9 125
Submit 10 250
Submit 11 500
Submit 12 500

