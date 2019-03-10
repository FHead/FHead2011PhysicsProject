{
   jetTree->SetAlias("PT",     "sigJetPt");
   jetTree->SetAlias("DR0",    "sigJetSDdr12");
   jetTree->SetAlias("ZG0",    "sigJetSDZg");
   jetTree->SetAlias("M0",     "sigJetSDM");
   jetTree->SetAlias("GuuPT0", "sigJetSDPt");
   jetTree->SetAlias("DR1",    "sig1JetSDdr12");
   jetTree->SetAlias("ZG1",    "sig1JetSDZg");
   jetTree->SetAlias("M1",     "sig1JetSDM");
   jetTree->SetAlias("GuuPT1", "sig1JetSDPt");
   jetTree->SetAlias("DR2",    "sig2JetSDdr12");
   jetTree->SetAlias("ZG2",    "sig2JetSDZg");
   jetTree->SetAlias("M2",     "sig2JetSDM");
   jetTree->SetAlias("GuuPT2", "sig2JetSDPt");
   jetTree->SetAlias("DR3",    "sig3JetSDdr12");
   jetTree->SetAlias("ZG3",    "sig3JetSDZg");
   jetTree->SetAlias("M3",     "sig3JetSDM");
   jetTree->SetAlias("GuuPT3", "sig3JetSDPt");
   jetTree->SetAlias("DR4",    "sig4JetSDdr12");
   jetTree->SetAlias("ZG4",    "sig4JetSDZg");
   jetTree->SetAlias("M4",     "sig4JetSDM");
   jetTree->SetAlias("GuuPT4", "sig4JetSDPt");
   jetTree->SetAlias("DR5",    "sig5JetSDdr12");
   jetTree->SetAlias("ZG5",    "sig5JetSDZg");
   jetTree->SetAlias("M5",     "sig5JetSDM");
   jetTree->SetAlias("GuuPT5", "sig5JetSDPt");
   jetTree->SetAlias("DR6",    "sig6JetSDdr12");
   jetTree->SetAlias("ZG6",    "sig6JetSDZg");
   jetTree->SetAlias("M6",     "sig6JetSDM");
   jetTree->SetAlias("GuuPT6", "sig6JetSDPt");

   jetTree->SetAlias("Mu1Px",  "(muonsPt[0]*cos(muonsPhi[0]))");
   jetTree->SetAlias("Mu1Py",  "(muonsPt[0]*sin(muonsPhi[0]))");
   jetTree->SetAlias("Mu1Pz",  "(muonsPt[0]*tanh(muonsEta[0]))");
   jetTree->SetAlias("Mu2Px",  "(muonsPt[1]*cos(muonsPhi[1]))");
   jetTree->SetAlias("Mu2Py",  "(muonsPt[1]*sin(muonsPhi[1]))");
   jetTree->SetAlias("Mu2Pz",  "(muonsPt[1]*tanh(muonsEta[1]))");
   jetTree->SetAlias("ZPx", "(Mu1Px+Mu2Px)");
   jetTree->SetAlias("ZPy", "(Mu1Py+Mu2Py)");
   jetTree->SetAlias("ZPz", "(Mu1Pz+Mu2Pz)");
   jetTree->SetAlias("ZPt", "sqrt(ZPx*ZPx+ZPy*ZPy)");
   jetTree->SetAlias("ZPhi", "(acos(ZPx/ZPt)*((ZPy>0)*2-1))");

   jetTree->SetAlias("DPhi", "acos((ZPx*PT*cos(sigJetPhi)+ZPy*PT*sin(sigJetPhi))/ZPt/PT)");
   jetTree->SetAlias("DPhiRaw", "(ZPhi-sigJetPhi)");
}
