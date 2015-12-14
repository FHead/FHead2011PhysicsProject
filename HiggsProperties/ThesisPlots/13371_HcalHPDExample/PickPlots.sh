mkdir -p PickedPlots

for i in eps png pdf C
do
   cp Plots/Event000439.$i PickedPlots/HcalNoise-Characterization-HPDView1.$i
   cp Plots/HPD000439-13-0.$i PickedPlots/HcalNoise-Characterization-HPDView2.$i
   cp Plots/Event000175.$i PickedPlots/HcalNoise-Characterization-HPDView3.$i
   cp Plots/HPD000175-23-1.$i PickedPlots/HcalNoise-Characterization-HPDView4.$i
done




