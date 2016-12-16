mkdir -p Plots

hadd -f -k AA6Dijet.root Result/AA6Dijet*
hadd -f -k AA8Dijet.root Result/AA8Dijet*
# hadd -f -k HydjetMB.root Result/HydjetMB*

./a.out AA6Dijet.root Plots/AA6Dijet
./a.out AA8Dijet.root Plots/AA8Dijet
# ./a.out HydjetMB.root Plots/HydjetMB
