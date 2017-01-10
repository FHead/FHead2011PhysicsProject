{
   OutputTree->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   OutputTree->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   OutputTree->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   OutputTree->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");

   OutputTree->SetAlias("X", "(Centrality/100)");
   OutputTree->SetAlias("RMS1", "(exp(1.482-26.28*X)+exp(3.337-3.542*X))");
   OutputTree->SetAlias("RMSA", "(27.83-165.2*X+682.8*X*X-1987*X*X*X+3409*X*X*X*X-3043*X*X*X*X*X+1097*X*X*X*X*X*X-7.243*X*X*X*X*X*X*X)");
   OutputTree->SetAlias("RMS2", "(19.15-23.28*X+4.567e-7*X*X-467.4*X*X*X+2110*X*X*X*X-2993*X*X*X*X*X+227.9*X*X*X*X*X*X+2019*X*X*X*X*X*X*X+876.3*X*X*X*X*X*X*X*X-3027*X*X*X*X*X*X*X*X*X+1239*X*X*X*X*X*X*X*X*X*X)");
   OutputTree->SetAlias("ExcessPT", "(TotalPTInJet-Rho*0.4*0.4*3.1415926535)");
   OutputTree->SetAlias("ExcessPT2", "((TotalPT-Rho*1.2*1.2*3.1415926535)/9)");
   OutputTree->SetAlias("SmearWeight", "(exp(-ExcessPT2*ExcessPT2/(2*RMS2*RMS2/3/3))/exp(-ExcessPT2*ExcessPT2/(2*RMSA*RMSA)))");   
}
