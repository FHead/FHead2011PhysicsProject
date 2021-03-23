mkdir -p FinalFigures
for i in Figure*
do
   echo ${i/Figure[0-9]*_/Figure_}
   mv $i FinalFigures/${i/Figure[0-9]*_/Figure_}
done
