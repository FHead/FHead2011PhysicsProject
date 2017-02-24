cat Exclude* | awk '{print $1}' > ModulesToExclude

mkdir -p Plots
for i in Output.step4_*
do
   ./RunPlot Plots/${i/.step4/_step5} < $i
done
