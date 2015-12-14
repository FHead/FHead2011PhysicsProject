cd ~/CMSSW_2_2_13/src
eval `scram runtime -sh`
cd - > /dev/null

# cmsRun FillAdcDistribution_300.py | tee FillAdcDistribution_300.log   # <== 50k events
# cmsRun FillAdcDistribution_150.py | tee FillAdcDistribution_150.log   # <== 50k events

# we only run through motherboard 0
for iChannel in `seq 0 15`
do
   root -l -q "CreateCdf.C(\"Adc_300.root\", 0, $iChannel, \"Cdf_0_${iChannel}_300.txt\", 30)"
   root -l -q "CreateCdf.C(\"Adc_150.root\", 0, $iChannel, \"Cdf_0_${iChannel}_150.txt\", 30)"
   ./CreateAdcMapping Cdf_0_${iChannel}_300.txt Cdf_0_${iChannel}_150.txt AdcMapping_0_${iChannel}.txt
   root -l -q "PlotTwoColumnFile.C(\"AdcMapping_0_$iChannel.txt\", \"AdcMapping_0_$iChannel.root\")"
   # root -l -q "FitScale.C+(\"AdcMapping_0_4.root\", 500, 4000)" | grep FitScale | cut --fields=6-6 --delim=' ' > Scale_0_$iChannel.txt
   ./FitScale AdcMapping_0_$iChannel.txt | grep FitScale | cut --fields=6-6 --delim=' ' > Scale_0_$iChannel.txt
   Scale=`cat Scale_0_$iChannel.txt`
   ./ScaleSecondColumn AdcMapping_0_$iChannel.txt $Scale > PreampOnAdcMapping_0_$iChannel.txt
   ./RemoveBeforeCrossingPoint PreampOnAdcMapping_0_${iChannel}.txt > CloseToFinalAdcMapping_0_${iChannel}.txt
   ./AddText.sh CloseToFinalAdcMapping_0_${iChannel}.txt FinalAdcMapping_0_${iChannel}.txt "0 $iChannel "
done

# cat FinalAdcMapping_0_*.txt > FinalAdcMapping_All.txt
rm FinalAdcMapping_0_*.txt
rm CloseToFinalAdcMapping_0_*.txt
rm PreampOnAdcMapping_0_*.txt
# rm AdcMapping_0_*.txt
rm Cdf_0_*.txt

