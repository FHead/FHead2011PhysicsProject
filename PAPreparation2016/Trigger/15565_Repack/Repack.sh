Current=`pwd`

mkdir -p Work
rm Work/*
cd Work

for i in `ls ../log`
do
   echo $i

   tar zxvf ../log/$i

   grep -v "^Jet" cmsRun-stdout-*.log | grep -v "Starting loop" | grep -v "^%Could not" | less | grep -v "^ Jet" | grep -v "^[0-9 .-]*$" | grep -v "^[0-9 .-]*Jet[0-9 .-]*$" | grep -v "Too many Tau" | grep -v "^%MSG-w L1TGlobal:" | grep -v "^%MSG$" > TEMP

   mv TEMP cmsRun-stdout-*.log

   tar zcvf $i *

   mv $i ../log/

   rm *
done

cd $Current
