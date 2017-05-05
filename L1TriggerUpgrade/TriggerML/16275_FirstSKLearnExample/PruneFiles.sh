awk '{if($7 != 20 && $7 != 19 && $7 != -20 && $7 != -19) print}' < WToEnu140PU.txt  > WToEnu140PUPruned.txt
awk '{if($7 != 20 && $7 != 19 && $7 != -20 && $7 != -19) print}' < WToEnu200PU.txt  > WToEnu200PUPruned.txt
