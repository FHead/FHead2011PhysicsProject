{
   jetTree->SetAlias("PT",     "sigJetJewelPt");
   jetTree->SetAlias("DR0",    "sigJetSDJeweldr12");
   jetTree->SetAlias("ZG0",    "sigJetSDJewelzg");
   jetTree->SetAlias("M0",     "sigJetSDJewelM");
   jetTree->SetAlias("GuuPT0", "sigJetSDJewelPt");
   jetTree->SetAlias("DR1",    "sig1JetSDJeweldr12");
   jetTree->SetAlias("ZG1",    "sig1JetSDJewelzg");
   jetTree->SetAlias("M1",     "sig1JetSDJewelM");
   jetTree->SetAlias("GuuPT1", "sig1JetSDJewelPt");
   jetTree->SetAlias("DR2",    "sig2JetSDJeweldr12");
   jetTree->SetAlias("ZG2",    "sig2JetSDJewelzg");
   jetTree->SetAlias("M2",     "sig2JetSDJewelM");
   jetTree->SetAlias("GuuPT2", "sig2JetSDJewelPt");
   jetTree->SetAlias("DR3",    "sig3JetSDJeweldr12");
   jetTree->SetAlias("ZG3",    "sig3JetSDJewelzg");
   jetTree->SetAlias("M3",     "sig3JetSDJewelM");
   jetTree->SetAlias("GuuPT3", "sig3JetSDJewelPt");
   jetTree->SetAlias("DR4",    "sig4JetSDJeweldr12");
   jetTree->SetAlias("ZG4",    "sig4JetSDJewelzg");
   jetTree->SetAlias("M4",     "sig4JetSDJewelM");
   jetTree->SetAlias("GuuPT4", "sig4JetSDJewelPt");
   jetTree->SetAlias("DR5",    "sig5JetSDJeweldr12");
   jetTree->SetAlias("ZG5",    "sig5JetSDJewelzg");
   jetTree->SetAlias("M5",     "sig5JetSDJewelM");
   jetTree->SetAlias("GuuPT5", "sig5JetSDJewelPt");
   jetTree->SetAlias("DR6",    "sig6JetSDJeweldr12");
   jetTree->SetAlias("ZG6",    "sig6JetSDJewelzg");
   jetTree->SetAlias("M6",     "sig6JetSDJewelM");
   jetTree->SetAlias("GuuPT6", "sig6JetSDJewelPt");

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

   jetTree->SetAlias("DPhi", "acos((ZPx*PT*cos(sigJetJewelPhi)+ZPy*PT*sin(sigJetJewelPhi))/ZPt/PT)");
}
