for i in Log/*
do
   ./a.out $i > Calculated/`basename $i`
done

mkdir -p Temp
for i in `ls Calculated | cut --delim='_' --field=1,2,4,5 | sort | uniq | sed "s/.out$//g" | sed "s/^Job//g"`
do
   F1=`echo $i | tr '_' ' ' | awk '{print $1}'`
   F2=`echo $i | tr '_' ' ' | awk '{print $2}'`
   F3=`echo $i | tr '_' ' ' | awk '{print $3}'`
   F4=`echo $i | tr '_' ' ' | awk '{print $4}'`

   cat Calculated/Job${F1}_${F2}_*_${F3}_${F4}.out \
      | sed "s/^/${F4} /g" > Temp/${F2}_${F1}_${F3}_${F4}
done
for i in `ls Temp | cut --delim='_' --field=1,2,3 | sort | uniq`
do
   # cat Temp/${i}_* | grep -v nan | tee Processed/$i.txt | TextToTree Processed/$i.root 4 "N:ID:P:S"
   cat Temp/${i}_* | grep -v nan | TextToTree Processed/$i.root 4 "N:ID:P:S"
done




