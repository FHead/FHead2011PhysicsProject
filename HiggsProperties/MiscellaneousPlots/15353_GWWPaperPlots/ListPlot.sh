rm PlotList.json
echo "var List =" > PlotList.json
echo "[" >> PlotList.json
First="true"
for i in `ls *png`
do
   if [ $First == "true" ]
   then
      First="false"
   else
      echo "," >> PlotList.json
   fi
   echo -n "   \"${i/.png}\"" >> PlotList.json
done
echo >> PlotList.json
echo "];" >> PlotList.json
echo >> PlotList.json
