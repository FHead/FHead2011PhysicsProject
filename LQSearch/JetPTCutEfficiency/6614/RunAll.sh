for i in `ls Samples/ | grep root$ | sed "s/.root//g"`
do
   echo ./CheckJetCut $i
   time ./CheckJetCut $i
done
