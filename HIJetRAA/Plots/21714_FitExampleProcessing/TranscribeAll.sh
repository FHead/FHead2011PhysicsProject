DIR=Oct9plots
mkdir -p root

for i in `ls $DIR | grep C$`
do
   echo Processing $i
   root -l -b -q $DIR/${i/.C}.C "Transcribe.C(\"root/${i/.C/.root}\")"
done
