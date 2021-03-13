for i in JRA2018/*root
do
   j=`echo $i | cut -d '_' -f 2`
   time jet_response_analyzer_x jra.config \
      -input $i \
      -nbinsabsrsp 0 \
      -nbinsetarsp 0 \
      -nbinsphirsp 0 \
      -nbinsrelrsp 200 \
      -doflavor false \
      -flavorDefinition phys \
      -MCPUReWeighting MyMCPileupHistogram.root \
      -MCPUHistoName pileup \
      -DataPUReWeighting MyDataPileupHistogram.root \
      -DataPUHistoName pileup \
      -output singlejra.root \
      -useweight true \
      -nrefmax 3 \
      -algs ak1pf:0.08 ak2pf:0.1 ak3pf:0.15 ak4pf:0.2 ak5pf:0.25 ak6pf:0.3 ak7pf:0.4 ak8pf:0.5 ak9pf:0.6 \
      -drmax 0.2 \
      -relrspmin 0.0 \
      -relrspmax 2.0
      
   # mv singlejra.root Output2018/jra_$j
   exit
done

# hadd -f jra.root Output2018/jra_*.root




