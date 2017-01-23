{
   TFile F1N("Baseline_000_N.root");
   TFile F1Y("Baseline_000_Y.root");
   TFile F2N("Baseline_002_N.root");
   TFile F2Y("Baseline_002_Y.root");
   TFile F3N("Baseline_005_N.root");
   TFile F3Y("Baseline_005_Y.root");
   TFile F4N("Baseline_010_N.root");
   TFile F4Y("Baseline_010_Y.root");

   TTree *T1N = (TTree *)F1N.Get("OutputTree");
   TTree *T1Y = (TTree *)F1Y.Get("OutputTree");
   TTree *T2N = (TTree *)F2N.Get("OutputTree");
   TTree *T2Y = (TTree *)F2Y.Get("OutputTree");
   TTree *T3N = (TTree *)F3N.Get("OutputTree");
   TTree *T3Y = (TTree *)F3Y.Get("OutputTree");
   TTree *T4N = (TTree *)F4N.Get("OutputTree");
   TTree *T4Y = (TTree *)F4Y.Get("OutputTree");

   T1N->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T1N->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T1N->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T1N->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");
   T1Y->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T1Y->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T1Y->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T1Y->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");
   T2N->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T2N->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T2N->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T2N->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");
   T2Y->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T2Y->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T2Y->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T2Y->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");
   T3N->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T3N->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T3N->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T3N->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");
   T3Y->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T3Y->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T3Y->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T3Y->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");
   T4N->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T4N->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T4N->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T4N->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");
   T4Y->SetAlias("MatchedDEta", "(BestJetEta-JetEta)");
   T4Y->SetAlias("MatchedDPhiRaw", "(BestJetPhi-JetPhi)");
   T4Y->SetAlias("MatchedDPhi", "(MatchedDPhiRaw+(MatchedDPhiRaw<-3.1415926535)*2*3.1415926535-(MatchedDPhiRaw>3.1415926535)*2*3.1415926535)");
   T4Y->SetAlias("MatchedDR", "sqrt(MatchedDEta*MatchedDEta+MatchedDPhi*MatchedDPhi)");

   string Baseline = "(BestJetPT > 100 && abs(BestJetEta) < 1.3 && MatchedDR < 0.2)";
   T1N->SetAlias("Baseline", Baseline.c_str());
   T1Y->SetAlias("Baseline", Baseline.c_str());
   T2N->SetAlias("Baseline", Baseline.c_str());
   T2Y->SetAlias("Baseline", Baseline.c_str());
   T3N->SetAlias("Baseline", Baseline.c_str());
   T3Y->SetAlias("Baseline", Baseline.c_str());
   T4N->SetAlias("Baseline", Baseline.c_str());
   T4Y->SetAlias("Baseline", Baseline.c_str());

   // T1N->SetAlias("X", "(Centrality/100)");
   // T1N->SetAlias("RMS1", "(exp(1.482-26.28*X)+exp(3.337-3.542*X))");
   // T1N->SetAlias("RMSA", "(27.83-165.2*X+682.8*X*X-1987*X*X*X+3409*X*X*X*X-3043*X*X*X*X*X+1097*X*X*X*X*X*X-7.243*X*X*X*X*X*X*X)");
   // T1N->SetAlias("RMS2", "(19.15-23.28*X+4.567e-7*X*X-467.4*X*X*X+2110*X*X*X*X-2993*X*X*X*X*X+227.9*X*X*X*X*X*X+2019*X*X*X*X*X*X*X+876.3*X*X*X*X*X*X*X*X-3027*X*X*X*X*X*X*X*X*X+1239*X*X*X*X*X*X*X*X*X*X)");
   // T1N->SetAlias("ExcessPT", "(TotalPTInJet-Rho*0.4*0.4*3.1415926535)");
   // T1N->SetAlias("SmearWeight", "(exp(-ExcessPT*ExcessPT/(2*RMS2*RMS2))/exp(-ExcessPT*ExcessPT/(2*RMSA*RMSA)))");   
}

