for i in png C pdf eps
do
   for j in 1 2 3 4
   do
      mv Plot1-${j}.${i} Plot_ScanXi1_OutputXi${j}.${i}
      mv Plot2-${j}.${i} Plot_ScanA1sAs_OutputA${j}sAs.${i}
      mv Plot3-${j}.${i} Plot_ScanXi2_OutputXi${j}.${i}
      mv Plot4-${j}.${i} Plot_ScanA2sAs_OutputA${j}sAs.${i}
      mv Plot5-${j}.${i} Plot_ScanXi3_OutputXi${j}.${i}
      mv Plot6-${j}.${i} Plot_ScanA3sAs_OutputA${j}sAs.${i}
   done
done


