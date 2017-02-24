for i in HLT_PA*txt
do
   echo $i
   cd ${i/.txt}
   crab submit -c pickevents_crab.py
   cd ..
done
