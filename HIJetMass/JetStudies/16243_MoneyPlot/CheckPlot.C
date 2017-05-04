{
   TChain T1("T");

   for(int i = 0; i <= 38; i++)
      T1.AddFile(Form("AAData16144/AAData_%d.root", i));

   T1.SetLineColor(kRed);

   TChain T2("T");

   T2.AddFile("AAData16214/AADataMeow.root");

   TChain T3("T");

   T3.AddFile("AADataPrescale16214/AADataPrescale.root");

   T3.SetLineColor(kGreen);

   // T2.Draw("JetPT", "JetPT < 400 && abs(JetEta) < 1.3 && Centrality < 0.1 && MatchDR < 0.1");
   // T1.Draw("JetPT", "JetPT < 400 && abs(JetEta) < 1.3 && Centrality < 0.1 && MatchDR < 0.1", "same");
   
   // T2.Draw("JetPT", "JetPT > 400 && abs(JetEta) < 1.3 && Centrality < 0.1 && MatchDR < 0.1");
   // T1.Draw("JetPT", "JetPT > 400 && abs(JetEta) < 1.3 && Centrality < 0.1 && MatchDR < 0.1", "same");
   
   T1.Draw("SDMass0/MatchPT>>H1(15,0,0.3)", "MatchPT > 140 && MatchPT < 160 && abs(JetEta) < 1.3 && Centrality < 0.1 && SubJetDR0 > 0.1");
   T2.Draw("SDMass0/MatchPT>>H2", "MatchPT > 140 && MatchPT < 160 && abs(JetEta) < 1.3 && Centrality < 0.1 && SubJetDR0 > 0.1", "same");
   T3.Draw("SDMass0/MatchPT>>H3", "MatchPT > 140 && MatchPT < 160 && abs(JetEta) < 1.3 && Centrality < 0.1 && SubJetDR0 > 0.1", "same");

   H1->Scale(1/H1->Integral());
   H2->Scale(1/H2->Integral());
   H3->Scale(1/H3->Integral());

   c1->SetLogy();
}
