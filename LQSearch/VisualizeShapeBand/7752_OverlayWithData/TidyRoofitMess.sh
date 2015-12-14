cat FinalResultPlot1_Log.C | sed "s#Int\[RSQ]#IntRSQ#g" | sed "s#_Norm\[MR,RSQ]#_NormMRRSQ#g" | sed "s#Comp\[#Comp#g" | sed "s#Model_\([0-9]*\),#Model\1#g" | sed "s#\([0-9]\)]\([0-9]\)#\1\2#g" > FitResultPlot.C

