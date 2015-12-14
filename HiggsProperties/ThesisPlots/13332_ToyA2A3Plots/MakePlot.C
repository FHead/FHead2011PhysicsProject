{
   gROOT->LoadMacro("~/RootMacros/SetStyle.h");
   
   SetThesisRegularStyle();

   TFile F("FitResultTreeA2ZAA3ZA_100.root");
   TTree *T = (TTree *)F.Get("ResultTree");
   T->SetMarkerStyle(11);

   TH2D *H1 = new TH2D("H1", ";A_{2} (float both);A_{3} (float both)", 75, -0.5, 0.5, 75, -0.5, 0.5);
   TH2D *H2 = new TH2D("H2", ";A_{2} (float only A_{2});A_{3} (float both)", 75, -0.5, 0.5, 75, -0.5, 0.5);

   H1->SetStats(0);
   H2->SetStats(0);

   // H1->GetXaxis()->SetTitleOffset(1.1);
   // H1->GetYaxis()->SetTitleOffset(1.2);
   // H2->GetXaxis()->SetTitleOffset(1.1);
   // H2->GetYaxis()->SetTitleOffset(1.2);

   H1->SetMarkerStyle(1);
   H2->SetMarkerStyle(1);

   H1->GetXaxis()->SetNdivisions(505);
   H1->GetYaxis()->SetNdivisions(505);
   H2->GetXaxis()->SetNdivisions(505);
   H2->GetYaxis()->SetNdivisions(505);

   T->Draw("R2YY:R3YY>>H1");
   T->Draw("R2YN:R3YY>>H2");

   TCanvas C;

   H1.Draw("");

   C.SaveAs("PhysicsChallenge-MultiParameters-AsteriskLeft.png");
   C.SaveAs("PhysicsChallenge-MultiParameters-AsteriskLeft.C");
   C.SaveAs("PhysicsChallenge-MultiParameters-AsteriskLeft.eps");
   C.SaveAs("PhysicsChallenge-MultiParameters-AsteriskLeft.pdf");
   
   H2.Draw("");
   
   C.SaveAs("PhysicsChallenge-MultiParameters-AsteriskRight.png");
   C.SaveAs("PhysicsChallenge-MultiParameters-AsteriskRight.C");
   C.SaveAs("PhysicsChallenge-MultiParameters-AsteriskRight.eps");
   C.SaveAs("PhysicsChallenge-MultiParameters-AsteriskRight.pdf");
}
