{
   TFile F1("Output_HiForest_2.root");
   TFile F2("Output_0.root");

   TTree *T1 = (TTree *)F1.Get("T");
   TTree *T2 = (TTree *)F2.Get("OutputTree");

   T2->SetAlias("X", "(Centrality/100)");
   T2->SetAlias("RMS1", "(exp(1.482-26.28*X)+exp(3.337-3.542*X))");
   T2->SetAlias("RMS2", "(19.15-23.28*X+4.567e-7*X*X-467.4*X*X*X+2110*X*X*X*X-2993*X*X*X*X*X+227.9*X*X*X*X*X*X+2019*X*X*X*X*X*X*X+876.3*X*X*X*X*X*X*X*X-3027*X*X*X*X*X*X*X*X*X+1239*X*X*X*X*X*X*X*X*X*X)");
   T2->SetAlias("ExcessPT", "(TotalPTInJet-Rho*0.4*0.4*3.1415926535)");
   T2->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT/(2*RMS2*RMS2))/exp(-ExcessPT*ExcessPT/(2*RMS1*RMS1)))");
}
