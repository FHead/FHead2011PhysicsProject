{
   OutputTree->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   OutputTree->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   OutputTree->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   OutputTree->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   OutputTree->SetAlias("RawBestJetDPhi", "(JetPhi-BestJetPhi)");
   OutputTree->SetAlias("BestJetDPhi", "(RawBestJetDPhi+2*3.1415926535*(RawBestJetDPhi<-3.1415926535)-2*3.1415926535*(RawBestJetDPhi>3.1415926535))");
   OutputTree->SetAlias("BestJetDEta", "(JetEta-BestJetEta)");
   OutputTree->SetAlias("BestJetShift", "sqrt(BestJetDPhi*BestJetDPhi+BestJetDEta*BestJetDEta)");
   OutputTree->SetAlias("ExcessPT", "(TotalPT-Rho*0.8*0.8*3.1415926535)");

   OutputTree->SetAlias("Baseline", "(JetShift < 0.2)");
}
