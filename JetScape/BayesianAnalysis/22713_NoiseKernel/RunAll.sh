# for i in `seq 0 139`
# do
#    python3 RunOne.py --N $i --Model LBT --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.20 --CovType Separated
#    bzip2 txt/*txt
# done
	
for i in `seq 0 80`
do
   python3 RunOne.py --N $i --Model MatterLBT2 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.00 --CovType Separated
   python3 RunOne.py --N $i --Model MatterLBT2 --Nu 2.5 --KernelChoice MaternNoise --Alpha 0.20 --CovType Separated
   bzip2 txt/*txt
done

