mkdir -p Calculated

for i in Trimmed/*
do
   echo Processing $i
   ./Calculate < $i > Calculated/`basename $i`
done
