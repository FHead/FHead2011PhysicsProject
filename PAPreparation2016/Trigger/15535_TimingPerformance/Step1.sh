for i in Output*log
do
   grep TimeReport $i | cut --delim=' ' --field=2- > ${i/log/step1}
done
