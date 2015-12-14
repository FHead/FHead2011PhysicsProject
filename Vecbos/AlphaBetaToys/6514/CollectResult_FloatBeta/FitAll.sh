cp FloatBetaSamples/FitResultPF_30_3Jets.root FitXD1.root
cp UnconstrainedSamples/FitResultPF_30_4Jets.root FitXD2.root

root -l -b -q "CollectResult.C+(\"FitXD1.root\", \"FitXD2.root\", \"Histograms/Output0.root\", 0, 99)"
for i in `seq 1 49`
do
   root -l -b -q "CollectResult.C+(\"FitXD1.root\", \"FitXD2.root\", \"Histograms/Output${i}.root\", ${i}00, ${i}99)"
done

hadd -f FinalOutput.root Histograms/Output[0-9]*.root
root -l -b -q ProducePDF.C+



