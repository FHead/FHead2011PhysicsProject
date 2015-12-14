mkdir -p PickedPlots/

for i in png C eps pdf
do
   cp Plots/Pulse000334000000.$i PickedPlots/HcalNoise-Characterization-SpikeLikeNoise1.$i
   cp Plots/Event000334.$i PickedPlots/HcalNoise-Characterization-SpikeLikeNoise2.$i
   cp Plots/Pulse000175000000.$i PickedPlots/HcalNoise-Characterization-TriangleLikeNoise1.$i
   cp Plots/Pulse000175000003.$i PickedPlots/HcalNoise-Characterization-TriangleLikeNoise2.$i
   cp Plots/Event000175.$i PickedPlots/HcalNoise-Characterization-TriangleLikeNoise3.$i
   cp Plots/Pulse000389000529.$i PickedPlots/HcalNoise-Characterization-FlatLikeNoise1.$i
   cp Plots/Event000389.$i PickedPlots/HcalNoise-Characterization-FlatLikeNoise2.$i
done
