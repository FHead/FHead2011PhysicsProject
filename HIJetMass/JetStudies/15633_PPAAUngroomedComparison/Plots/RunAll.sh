./a.out Y
./a.out N

mkdir -p RenamedPlots
for i in `ls Plots | grep pdf`
do
   cp Plots/$i RenamedPlots/15532_SecondLookAtData_$i
done

