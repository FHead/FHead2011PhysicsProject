for i in 001 002 004 007 010
do
   sh ../../CommonCode/script/CombineResult.sh Result_$i CombinedResult_$i
   sh ../../CommonCode/script/ScaleHistograms.sh CombinedResult_$i ScaledResult_$i
done
