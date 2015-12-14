{
   TFile FA2ZA("LikelihoodFileA2ZA.root");
   TFile FA3ZA("LikelihoodFileA3ZA.root");
   TFile FA2AA("LikelihoodFileA2AA.root");
   TFile FA3AA("LikelihoodFileA3AA.root");

   TTree *TA2ZA = (TTree *)FA2ZA.Get("ResultTree");
   TTree *TA3ZA = (TTree *)FA3ZA.Get("ResultTree");
   TTree *TA2AA = (TTree *)FA2AA.Get("ResultTree");
   TTree *TA3AA = (TTree *)FA3AA.Get("ResultTree");

   TA2ZA->SetAlias("SA2ZA", "(A2ZA*A2ZA/0.1/0.1)");
   TA2ZA->SetAlias("FA2ZA", "SA2ZA/(1+SA2ZA)*((A2ZA>0)-(A2ZA<0))");
   TA3ZA->SetAlias("SA3ZA", "(A3ZA*A3ZA/0.11/0.11)");
   TA3ZA->SetAlias("FA3ZA", "SA3ZA/(1+SA3ZA)*((A3ZA>0)-(A3ZA<0))");
   TA2AA->SetAlias("SA2AA", "(A2AA*A2AA/0.108/0.108)");
   TA2AA->SetAlias("FA2AA", "SA2AA/(1+SA2AA)*((A2AA>0)-(A2AA<0))");
   TA3AA->SetAlias("SA3AA", "(A3AA*A3AA/0.109/0.109)");
   TA3AA->SetAlias("FA3AA", "SA3AA/(1+SA3AA)*((A3AA>0)-(A3AA<0))");

   TCanvas C("C", "C", 1024, 1024);

   TH1D HWorld("HWorld", ";f;", 100, -1, 1);

   HWorld.SetStats(0);
   HWorld.SetMinimum(0);
   HWorld.SetMaximum(20);

   TGraph G1, G2;
   G1.SetPoint(0, -1, 1);
   G1.SetPoint(1, +1, 1);
   G2.SetPoint(0, -1, 4);
   G2.SetPoint(1, +1, 4);
   G1.SetLineStyle(kDashed);
   G2.SetLineStyle(kDashed);

   HWorld.SetMaximum(20);
   HWorld.Draw();
   TA2ZA->Draw("BestNLL/305+315.2:FA2ZA", "", "same");
   G1.Draw("l");
   G2.Draw("l");
   C.SaveAs("FA2ZA.png");
   C.SaveAs("FA2ZA.C");
   C.SaveAs("FA2ZA.eps");
   C.SaveAs("FA2ZA.pdf");

   HWorld.SetMaximum(29);
   HWorld.Draw();
   TA3ZA->Draw("BestNLL/305-338668.85:FA3ZA", "", "same");
   G1.Draw("l");
   G2.Draw("l");
   C.SaveAs("FA3ZA.png");
   C.SaveAs("FA3ZA.C");
   C.SaveAs("FA3ZA.eps");
   C.SaveAs("FA3ZA.pdf");

   HWorld.SetMaximum(40);
   HWorld.Draw();
   TA2AA->Draw("BestNLL/305-974.3:FA2AA", "", "same");
   G1.Draw("l");
   G2.Draw("l");
   C.SaveAs("FA2AA.png");
   C.SaveAs("FA2AA.C");
   C.SaveAs("FA2AA.eps");
   C.SaveAs("FA2AA.pdf");

   HWorld.SetMaximum(40);
   HWorld.Draw();
   TA3AA->Draw("BestNLL/305+334.1:FA3AA", "", "same");
   G1.Draw("l");
   G2.Draw("l");
   C.SaveAs("FA3AA.png");
   C.SaveAs("FA3AA.C");
   C.SaveAs("FA3AA.eps");
   C.SaveAs("FA3AA.pdf");
}
