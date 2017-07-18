{
   TFile FAA("AA.root");
   TFile FPP("PP.root");
   TFile FPP2("PP6Dijet220HIReco.root");

   TTree *TAA = (TTree *)FAA.Get("T");
   TTree *TPP = (TTree *)FPP.Get("T");
   TTree *TPP2 = (TTree *)FPP2.Get("T");

   TAA->SetAlias("DEta", "(JetEta-PFEta)");
   TAA->SetAlias("DPhiX", "cos(JetPhi-PFPhi)");
   TAA->SetAlias("DPhiY", "sin(JetPhi-PFPhi)");
   TAA->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TAA->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");

   TPP->SetAlias("DEta", "(JetEta-PFEta)");
   TPP->SetAlias("DPhiX", "cos(JetPhi-PFPhi)");
   TPP->SetAlias("DPhiY", "sin(JetPhi-PFPhi)");
   TPP->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TPP->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");

   TPP2->SetAlias("DEta", "(JetEta-PFEta)");
   TPP2->SetAlias("DPhiX", "cos(JetPhi-PFPhi)");
   TPP2->SetAlias("DPhiY", "sin(JetPhi-PFPhi)");
   TPP2->SetAlias("DPhi", "(acos(DPhiX)*(1-2*(DPhiY<0)))");
   TPP2->SetAlias("DR", "sqrt(DEta*DEta+DPhi*DPhi)");

   TPP->Draw("DR>>HPP(100, 0.0, 0.6)", "abs(JetEta) < 1.0 && JetPT > 250 && PFID > 0 && PFPT > 0.5",                     "error");
   TAA->Draw("DR>>HAA",                "abs(JetEta) < 1.0 && JetPT > 250 && PFID > 0 && PFPT > 0.5 && Centrality > 0.8", "error same");
   TPP2->Draw("DR>>HPP2",              "abs(JetEta) < 1.0 && JetPT > 250 && PFID > 0 && PFPT > 0.5",                     "error same");

   double BinSize = (0.6 - 0.0) / 100;

   HPP->GetXaxis()->SetTitle("DR(PF Candidate, Jet)");
   HPP->GetYaxis()->SetTitle("#frac{1}{N_{Jet}} #frac{d N_{PF}}{d DR}");
   HPP->SetTitle("");
   HPP->SetStats(0);

   HAA->Scale(1.0 / TAA->GetEntries("JetPT > 250 && Centrality > 0.8") / BinSize);
   HPP->Scale(1.0 / TPP->GetEntries("JetPT > 250") / BinSize);
   HPP2->Scale(1.0 / TPP2->GetEntries("JetPT > 250") / BinSize);

   HPP->SetMinimum(0);
   
   HAA->SetLineColor(2);
   HPP->SetLineColor(4);
   HPP2->SetLineColor(3);
   
   HAA->SetMarkerColor(2);
   HPP->SetMarkerColor(4);
   HPP2->SetMarkerColor(3);
   
   HAA->SetMarkerStyle(20);
   HPP->SetMarkerStyle(20);
   HPP2->SetMarkerStyle(20);

   TLegend Legend(0.45, 0.80, 0.75, 0.60);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(HAA, "Embedded, 80-100%", "pl");
   Legend.AddEntry(HPP, "PP", "pl");
   Legend.AddEntry(HPP2, "PP (HI Reco)", "pl");
   Legend.Draw();

   c1->SaveAs("PFCandidates.pdf");
}

