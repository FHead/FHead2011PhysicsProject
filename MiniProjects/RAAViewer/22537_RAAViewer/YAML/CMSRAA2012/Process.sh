awk '{print $3,$5}' < X | tr -d ',}' > RawX
awk '{print ($1+$2)/2}' < RawX > AlmostFinalX
awk '{print ($1-$2)/2}' < RawX > AlmostFinalXError
for i in 1 2 3 4 5 6
do
   grep value Y$i | awk '{print $2}' > AlmostFinalY$i
   grep stat Y$i | awk '{print $5}' | tr -d '}' > AlmostFinalY${i}Stat
   grep sys Y$i | awk '{print $5}' | tr -d '}' > AlmostFinalY${i}Sys
done

for i in AlmostFinal*
do
    cat $i | tr '\n' ',' > ${i/Almost/}
done

rm AlmostFinal*

for i in 1 2 3 4 5 6
do
   FileName=CMSHadronRAA2012-${i}.json

   echo "{" > $FileName
   echo "   \"System\": \"PbPb\"," >> $FileName
   echo "   \"Energy\": \"2.76 TeV\"," >> $FileName
   echo "   \"Subject\": \"Hadron\"," >> $FileName
   echo "   \"Observable\": \"RAA\"," >> $FileName
   echo "   \"Dependency\": \"PT\"," >> $FileName
   echo "   \"Centrality\": \"0-10%\"," >> $FileName
   echo "   \"Record\": \"CMS 2012\"," >> $FileName
   echo "   \"Selection\": \"eta < 1.0\"," >> $FileName
   echo "   \"Comment\": \"\"," >> $FileName
   echo "   \"X\": ["`cat FinalX`"]," >> $FileName
   echo "   \"EXLow\": ["`cat FinalXError`"]," >> $FileName
   echo "   \"EXHigh\": ["`cat FinalXError`"]," >> $FileName
   echo "   \"Y\": ["`cat FinalY${i}`"]," >> $FileName
   echo "   \"EYStatLow\": ["`cat FinalY${i}Stat`"]," >> $FileName
   echo "   \"EYStatHigh\": ["`cat FinalY${i}Stat`"]," >> $FileName
   echo "   \"EYSysLow\": ["`cat FinalY${i}Sys`"]," >> $FileName
   echo "   \"EYSysHigh\": ["`cat FinalY${i}Sys`"]," >> $FileName
   echo "   \"GlobalUncertainty\": 0.00" >> $FileName
   echo "}," >> $FileName
done

rm Final*

