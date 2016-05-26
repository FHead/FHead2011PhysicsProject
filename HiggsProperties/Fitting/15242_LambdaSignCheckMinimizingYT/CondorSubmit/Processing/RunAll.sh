mkdir -p Calculated
mkdir -p Processed

for i in Log/*
do
   echo Processing $i
   ./a.out < $i > Calculated/`basename $i`
done

mkdir -p Temp
for i in `ls Calculated | cut --delim='_' --field=1-6 | sort | uniq | sed "s/.out$//g" | sed "s/^Job//g"`
do
   F1=`echo $i | tr '_' ' ' | awk '{print $2}'`
   F2=`echo $i | tr '_' ' ' | awk '{print $3}'`
   F3=`echo $i | tr '_' ' ' | awk '{print $4}'`
   F4=`echo $i | tr '_' ' ' | awk '{print $5}'`
   F5=`echo $i | tr '_' ' ' | awk '{print $6}'`
   F6=`echo $i | tr '_' ' ' | awk '{print $1}'`

   cat Calculated/${F6}_${F1}_${F2}_${F3}_${F4}_${F5}_*.out \
      | sed "s/^/${F5} /g" > Temp/${F2}_${F1}_${F3}_${F4}_Prior${F6}_${F5}
done

for i in `ls Temp | cut --delim='_' --field=1-5 | sort | uniq`
do
   # cat Temp/${i}_* | grep -v nan | tee Processed/$i.txt | TextToTree Processed/$i.root 5 "N:ID:P:S:R"
   cat Temp/${i}_* | grep -v nan | TextToTree Processed/$i.root 5 "N:YT:GWW:NLL:P"
done




