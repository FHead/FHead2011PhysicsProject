{
   TFile F1("AA6DijetCymbal.root");
   TFile F2("PP6Dijet.root");
   TFile F3("PP6DijetHIReco.root");
   TTree *T1 = (TTree *)F1.Get("T");
   TTree *T2 = (TTree *)F2.Get("OutputTree");
   TTree *T3 = (TTree *)F3.Get("OutputTree");
   T1->SetLineColor(kMagenta);
   T1->SetMarkerColor(kMagenta);
   T2->SetLineColor(kBlue);
   T2->SetMarkerColor(kBlue);
   T3->SetLineColor(kGreen - 3);
   T3->SetMarkerColor(kGreen - 3);

   T2->SetAlias("CWeight", "(8.38513e+02-3.85932e+03*Centrality+3.07751e+04*Centrality*Centrality-1.40224e+05*Centrality*Centrality*Centrality+3.38087e+05*Centrality*Centrality*Centrality*Centrality-4.02987e+05*Centrality*Centrality*Centrality*Centrality*Centrality+1.88666e+05*Centrality*Centrality*Centrality*Centrality*Centrality*Centrality)");
   T3->SetAlias("CWeight", "(8.38513e+02-3.85932e+03*Centrality+3.07751e+04*Centrality*Centrality-1.40224e+05*Centrality*Centrality*Centrality+3.38087e+05*Centrality*Centrality*Centrality*Centrality-4.02987e+05*Centrality*Centrality*Centrality*Centrality*Centrality+1.88666e+05*Centrality*Centrality*Centrality*Centrality*Centrality*Centrality)");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();
}
