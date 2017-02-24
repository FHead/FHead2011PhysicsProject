{
   Tree->SetAlias("RawJetDPhi", "(JetPhi-NewJetPhi)");
   Tree->SetAlias("JetDPhi", "(RawJetDPhi+2*3.1415926535*(RawJetDPhi<-3.1415926535)-2*3.1415926535*(RawJetDPhi>3.1415926535))");
   Tree->SetAlias("JetDEta", "(JetEta-NewJetEta)");
   Tree->SetAlias("JetShift", "sqrt(JetDPhi*JetDPhi+JetDEta*JetDEta)");
   Tree->SetAlias("Baseline", "(log(JetShift)/log(10) < -2.8 && NewJetPT/JetPT > 0.8 && JetSDZG > 0)");
   Tree->SetAlias("JEC", "(JetPT/NewJetPT)");
}





