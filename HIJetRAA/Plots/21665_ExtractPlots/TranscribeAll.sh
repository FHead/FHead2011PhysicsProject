for i in `ls 20190928 | grep C$`
do
   echo Processing $i
   root -l -b -q 20190928/${i/.C}.C "Transcribe.C(\"root/${i/.C/.root}\")"
done
