# Prnue background
# awk '{if($7 != 20 && $7 != 19 && $7 != -20 && $7 != -19) print}' < WToEnu140PU.txt  > WToEnu140PUPruned.txt
# awk '{if($7 != 20 && $7 != 19 && $7 != -20 && $7 != -19) print}' < WToEnu200PU.txt  > WToEnu200PUPruned.txt

# Do the learning!
for i in ECAL WithHCAL WithIEta All
do
   for j in 140PU 200PU 140PUPruned 200PUPruned
   do
      python3 LearnEnergy.py $j $i
   done
done

