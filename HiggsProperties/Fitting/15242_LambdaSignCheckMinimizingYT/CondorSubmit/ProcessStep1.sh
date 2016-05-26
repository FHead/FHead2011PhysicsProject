for i in Log/*out
do
   tail -n+20 $i | grep ^[1-9] | grep 'N' | cut --delim=' ' --field=1,3- > Processing/Log/N_`basename $i`
   tail -n+20 $i | grep ^[1-9] | grep 'Y' | cut --delim=' ' --field=1,3- > Processing/Log/Y_`basename $i`
done
