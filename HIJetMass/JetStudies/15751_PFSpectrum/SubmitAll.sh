for PT in 120_140 140_160 160_180 180_200 200_300 300_500
do
   PTMin=`echo $PT | cut --delim='_' --field=1`
   PTMax=`echo $PT | cut --delim='_' --field=2`

   for Centrality in 0.0_0.1 0.1_0.3 0.3_0.5 0.5_0.8
   do
      CentralityMin=`echo $Centrality | cut --delim='_' --field=1`
      CentralityMax=`echo $Centrality | cut --delim='_' --field=2`

      cat BatchTemplate.submit | \
         sed "s/__PTMin__/$PTMin/g" | \
         sed "s/__PTMax__/$PTMax/g" | \
         sed "s/__CentralityMin__/$CentralityMin/g" | \
         sed "s/__CentralityMax__/$CentralityMax/g" | \
         bsub -J PFSpectrum
   done
done
