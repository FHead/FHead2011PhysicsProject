for i in `ls Trimmed`
do
   echo $i
   ./Filter NNNNNNYNNNNN < Trimmed/$i | cut --delim=' ' --field=1,4- > Meow
   ./Calculate Meow | grep -v nan > Processed/$i
done
