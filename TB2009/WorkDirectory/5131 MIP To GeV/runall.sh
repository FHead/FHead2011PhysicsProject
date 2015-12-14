for i in $*
do
   cat ConversionFactor_template.py | sed "s/__RUNNUM__/$i/g" > ConversionFactor_$i.py
   cmsRun ConversionFactor_$i.py | tee ConversionLog_$i.py
done
