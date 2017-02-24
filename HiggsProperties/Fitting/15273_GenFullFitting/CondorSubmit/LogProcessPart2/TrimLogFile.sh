mkdir -p Trimmed
for i in `ls Log | grep out`
do
   grep MinYT Log/$i \
      | cut --delim=' ' --field=2- \
      > Trimmed/$i
done
