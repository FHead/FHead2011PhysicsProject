{
   string RootFile = "Samples/ZJetsAll.root";

   RooRealVar ZMass("ZMass", "Invariant mass of dimuon pair", 60, 120, "GeV/c^2");
   RooRealVar NCaloJet("NCaloJet", "Count of jets", 0.5, 100000);
   RooArgSet TreeVarSet(ZMass, NCaloJet);

   TFile F(RootFile.c_str());
   TTree *ZTree = (TTree *)F.Get("outTree");
   RooDataSet DataSet("ZCandidates", "ZCandidates", ZTree, TreeVarSet);

   TCut NumberOfJetCut = "NCaloJet == 1";
   RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce(NumberOfJetCut);

   RooRealVar PeakPosition("PeakPosition", "Z peak position", 91.18, 80, 100, "GeV/c^2");
   RooRealVar AlphaR("AlphaR", "AlphaR", 0.435, 50.01, 1000000);
   RooRealVar AlphaL("AlphaL", "AlphaL", 0.508, 50.01, 1000000);
   RooRealVar SigmaR("SigmaR", "SigmaR", 2.189, 50.01, 1000000);
   RooRealVar SigmaL("SigmaL", "SigmaL", 2.349, 50.01, 1000000);

   RooCruijff Signal1JetShape("Signal1JetShape", "Signal, 1 jet", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooCruijff Signal2JetShape("Signal2JetShape", "Signal, 2 jet", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooCruijff Signal3JetShape("Signal3JetShape", "Signal, 3 jet", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooCruijff Signal4JetShape("Signal4JetShape", "Signal, 4 jet", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);
   RooCruijff Signal5JetShape("Signal5JetShape", "Signal, >= 5 jet", ZMass, PeakPosition, SigmaR, AlphaR, SigmaL, AlphaL);

   RooSameAs Constraint1Jet("Constraint1Jet", "Delta function at 1 jet", NCaloJet, 1, 0.5);
   RooSameAs Constraint2Jet("Constraint2Jet", "Delta function at 2 jet", NCaloJet, 2, 0.5);
   RooSameAs Constraint3Jet("Constraint3Jet", "Delta function at 3 jet", NCaloJet, 3, 0.5);
   RooSameAs Constraint4Jet("Constraint4Jet", "Delta function at 4 jet", NCaloJet, 4, 0.5);
   RooAtLeast Constraint5Jet("Constraint5Jet", "At least 5 jets", NCaloJet, 5 - 0.001);

   RooProdPdf Signal1Jet("Signal1Jet", "Signal, 1 jet", RooArgSet(Signal1JetShape, Constraint1Jet));
   RooProdPdf Signal2Jet("Signal2Jet", "Signal, 2 jet", RooArgSet(Signal2JetShape, Constraint2Jet));
   RooProdPdf Signal3Jet("Signal3Jet", "Signal, 3 jet", RooArgSet(Signal3JetShape, Constraint3Jet));
   RooProdPdf Signal4Jet("Signal4Jet", "Signal, 4 jet", RooArgSet(Signal4JetShape, Constraint4Jet));
   RooProdPdf Signal5Jet("Signal5Jet", "Signal, 5 jet", RooArgSet(Signal5JetShape, Constraint5Jet));

   RooRealVar SignalInclusiveYield("SignalInclusiveYield", "Signal yield for >= 1 jet", 1000, 1, 10000000);
   RooRealVar Alpha("Alpha", "Alpha parameter in signal yield", 0.2, 0.0001, 0.5);
   RooRealVar Beta("Beta", "Beta parameter in signal yield", 0.0001, 0.00000001, 0.1);

   RooFormulaVar Signal1JetYield("Signal1JetYield", "N = 1",
      "(1-@0-2*@1)", RooArgList(Alpha, Beta));
   RooFormulaVar Signal2JetYield("Signal2JetYield", "N = 2",
      "(@0+2*@1)*(1-@0-3*@1)", RooArgList(Alpha, Beta));
   RooFormulaVar Signal3JetYield("Signal3JetYield", "N = 3",
      "(@0+2*@1)*(@0+3*@1)*(1-@0-4*@1)", RooArgList(Alpha, Beta));
   RooFormulaVar Signal4JetYield("Signal4JetYield", "N = 4",
      "(@0+2*@1)*(@0+3*@1)*(@0+4*@1)*(1-@0-5*@1)", RooArgList(Alpha, Beta));
   RooFormulaVar Signal5JetYield("Signal5JetYield", "N >= 5",
      "(@0+2*@1)*(@0+3*@1)*(@0+4*@1)*(@0+5*@1)", RooArgList(Alpha, Beta));

   // RooArgSet SignalModels(Signal1Jet, Signal2Jet, Signal3Jet, Signal4Jet, Signal5Jet);
   // RooArgSet SignalRelativeYields(Signal1JetYield, Signal2JetYield, Signal3JetYield, Signal4JetYield, Signal5JetYield);
   RooArgSet SignalModels(Signal1Jet);
   RooArgSet SignalRelativeYields(Signal1JetYield);
   RooAddPdf SignalModel("SignalModel", "Signal model", SignalModels, SignalRelativeYields);

   RooArgSet TopLevelModels(SignalModel);
   RooArgSet TopLevelYields(SignalInclusiveYield);
   RooAddPdf FinalModel("FinalModel", "Final model", TopLevelModels, TopLevelYields);

   FinalModel.fitTo(*ReducedDataSet);
}


