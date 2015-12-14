# for i in `seq 300 999`; do ./RunProjections ../RootFiles/IndividualResultTree_${i}.root Projection$i.root; done
for i in `seq 300 999`; do ./RunMatrixPlot ../RootFiles/IndividualResultTree_$i.root Matrix$i.root; done
# for i in `seq 300 999`; do ./RunPartialCrossSection ../RootFiles/IndividualResultTree_$i.root PartialCrossSection$i.root; done


