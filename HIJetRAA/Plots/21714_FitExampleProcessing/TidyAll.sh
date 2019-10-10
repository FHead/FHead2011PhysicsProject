mkdir -p TidyRoot

for i in `ls Root`
do
   echo $i
   ./Tidy --Input Root/$i --Output TidyRoot/$i
done

hadd -f AllPlotsPhiFitSide.root TidyRoot/phiFitSide_hiBin*
hadd -f AllPlotsPhiFit.root TidyRoot/phiFit_hiBin*
hadd -f AllPlots.root AllPlotsPhi*.root

