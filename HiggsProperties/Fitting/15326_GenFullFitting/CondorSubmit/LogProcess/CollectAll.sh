mkdir -p Collected

for i1 in JobBothS JobBoth
do
   for i2 in 5plet SMVV
   do
      for i3 in A J
      do
         for i in Calculated/${i1}_${i2}_ggPDF_${i3}_*_*
         do
            i=`basename ${i/.out}`
            echo $i
            i4=`echo $i | cut --delim='_' --field=5`
            sed "s/^/${i4} /" < Calculated/$i.out
         done | grep -v "Job" | grep -v nan \
            | TextToTree Collected/${i1}_${i2}_${i3}.root 19 "L:ID:I1N:I2N:I3N:I4N:I5N:I1P:I2P:I3P:I4P:I5P:I1L:I2L:I3L:I4L:I5L:NLL_SM:NLL_H5"
      done
   done
done
