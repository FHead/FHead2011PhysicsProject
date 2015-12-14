cd ~/CMSSW_2_2_13/src
eval `scram runtime -sh`
cd - > /dev/null

cmsRun FillAdcDistribution_On.py | tee FillAdcDistribution_On.log     # <== 50k event
# cmsRun FillAdcDistribution_Off.py | tee FillAdcDistribution_Off.log   # <== also 50k

# we only run through motherboard 0
for iChannel in `seq 0 15`
do
   root -l -q "CreateCdf.C(\"Adc_On.root\", 0, $iChannel, \"Cdf_0_${iChannel}_on.txt\", 150)"
   root -l -q "CreateCdf.C(\"Adc_Off.root\", 0, $iChannel, \"Cdf_0_${iChannel}_off.txt\", 30)"
   ./CreateAdcMapping Cdf_0_${iChannel}_on.txt Cdf_0_${iChannel}_off.txt AdcMapping_0_${iChannel}.txt
   root -l -q "PlotTwoColumnFile.C(\"AdcMapping_0_$iChannel.txt\", \"AdcMapping_0_$iChannel.root\")"
   # root -l -q "FitScale.C+(\"AdcMapping_0_4.root\", 500, 4000)" | grep FitScale | cut --fields=6-6 --delim=' ' > Scale_0_$iChannel.txt
   ./FitScale AdcMapping_0_$iChannel.txt | grep FitScale | cut --fields=6-6 --delim=' ' > Scale_0_$iChannel.txt
   Scale=`cat Scale_0_$iChannel.txt`
   ./ScaleSecondColumn AdcMapping_0_$iChannel.txt $Scale > PreampOnAdcMapping_0_$iChannel.txt
   ./RemoveBeforeCrossingPoint PreampOnAdcMapping_0_${iChannel}.txt > CloseToFinalAdcMapping_0_${iChannel}.txt
   ./AddText.sh CloseToFinalAdcMapping_0_${iChannel}.txt FinalAdcMapping_0_${iChannel}.txt "0 $iChannel "
done

cat FinalAdcMapping_0_*.txt > FinalAdcMapping_All.txt
rm FinalAdcMapping_0_*.txt
rm CloseToFinalAdcMapping_0_*.txt
rm PreampOnAdcMapping_0_*.txt
rm AdcMapping_0_*.txt
rm Cdf_0_*.txt

