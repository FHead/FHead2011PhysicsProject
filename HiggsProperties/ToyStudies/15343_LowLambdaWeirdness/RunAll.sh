mkdir -p Organized

for i in `ls Result/`
do
   Lumi=`echo $i | cut --delim='_' --field=6`
   ./RunOrganize Result/$i Organized/$i $Lumi
done

mkdir -p Collected

hadd -f Collected/JobBoth.root Organized/*JobBoth_*
hadd -f Collected/JobBothS.root Organized/*JobBothS_*


