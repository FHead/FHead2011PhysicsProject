mkdir -p root
for i in `ls 20191120 | grep C$`
do
   echo Processing $i
   root -l -b -q 20191120/${i/.C}.C "Transcribe.C(\"root/${i/.C/.root}\")"
done
