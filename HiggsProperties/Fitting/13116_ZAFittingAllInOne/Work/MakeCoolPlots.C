{
   TFile F("All.root");

   TCanvas C("C", "C", 1024, 1024);
   C.SetLogz();

   ResultTree->Draw("PhiV:log(SignalDatasetSize+Background)/log(10)", "PhiV < 1.5 && PhiV > 0 && Status == 3", "colz");

   TGraph GV;
   GV.SetPoint(0, 0, atan(0.8/0.7));
   GV.SetPoint(1, 100, atan(0.8/0.7));
   GV.Draw("l");

   C.SaveAs("PhiV.png");
   C.SaveAs("PhiV.C");
   C.SaveAs("PhiV.eps");
   C.SaveAs("PhiV.pdf");

   ResultTree->Draw("PhiZA:log(SignalDatasetSize+Background)/log(10)", "PhiZA < 2 && PhiZA > -2 && Status == 3", "colz");

   TGraph GZA;
   GZA.SetPoint(0, 0, 0);
   GZA.SetPoint(1, 100, 0);
   GZA.Draw("l");

   C.SaveAs("PhiZA.png");
   C.SaveAs("PhiZA.C");
   C.SaveAs("PhiZA.eps");
   C.SaveAs("PhiZA.pdf");

   ResultTree->Draw("PhiAA:log(SignalDatasetSize+Background)/log(10)", "PhiAA < 4 && PhiAA > 2 && Status == 3", "colz");

   TGraph GAA;
   GAA.SetPoint(0, 0, 3.1415926535);
   GAA.SetPoint(1, 100, 3.1415926535);
   GAA.Draw("l");

   C.SaveAs("PhiAA.png");
   C.SaveAs("PhiAA.C");
   C.SaveAs("PhiAA.eps");
   C.SaveAs("PhiAA.pdf");

   ResultTree->SetAlias("A2ZA", "cos(PhiV)*cos(PhiZA)");
   ResultTree->SetAlias("A3ZA", "cos(PhiV)*sin(PhiZA)");
   ResultTree->SetAlias("A2AA", "sin(PhiV)*cos(PhiAA)");
   ResultTree->SetAlias("A3AA", "sin(PhiV)*sin(PhiAA)");

   ResultTree->Draw("Fraction:log(SignalDatasetSize+Background)/log(10)", "Status == 3", "colz");

   TGraph GF;
   GF.SetPoint(0, 0, 0.9);
   GF.SetPoint(1, 100, 0.9);
   GF.Draw("l");

   C.SaveAs("Fraction.png");
   C.SaveAs("Fraction.C");
   C.SaveAs("Fraction.eps");
   C.SaveAs("Fraction.pdf");

   ResultTree->Draw("A2ZA/A2AA*(-0.008):log(SignalDatasetSize+Background)/log(10)", "Status == 3 && abs(A2ZA/A2AA*(-0.008))<0.1", "colz");

   C.SaveAs("A2ZAA2AA.png");
   C.SaveAs("A2ZAA2AA.C");
   C.SaveAs("A2ZAA2AA.eps");
   C.SaveAs("A2ZAA2AA.pdf");

   ResultTree->Draw("A3ZA/A2AA*(-0.008):log(SignalDatasetSize+Background)/log(10)", "Status == 3 && abs(A3ZA/A2AA*(-0.008)) < 0.5", "colz");

   C.SaveAs("A3ZAA2AA.png");
   C.SaveAs("A3ZAA2AA.C");
   C.SaveAs("A3ZAA2AA.eps");
   C.SaveAs("A3ZAA2AA.pdf");

   ResultTree->Draw("A3AA/A2AA*(-0.008):log(SignalDatasetSize+Background)/log(10)", "Status == 3 && abs(A3AA/A2AA*(-0.008)) < 0.5", "colz");

   C.SaveAs("A3AAA2AA.png");
   C.SaveAs("A3AAA2AA.C");
   C.SaveAs("A3AAA2AA.eps");
   C.SaveAs("A3AAA2AA.pdf");

   C.SetLogy();

   ResultTree->Draw("abs(A2ZA/A2AA*(-0.008)-0.007)*sqrt(3.1415926535/2):log(SignalDatasetSize+Background)/log(10)", "Status == 3", "prof");

   C.SaveAs("A2ZAA2AASigma.png");
   C.SaveAs("A2ZAA2AASigma.C");
   C.SaveAs("A2ZAA2AASigma.eps");
   C.SaveAs("A2ZAA2AASigma.pdf");

   ResultTree->Draw("abs(A3ZA/A2AA*(-0.008)-0.000)*sqrt(3.1415926535/2):log(SignalDatasetSize+Background)/log(10)", "Status == 3", "prof");

   C.SaveAs("A3ZAA2AASigma.png");
   C.SaveAs("A3ZAA2AASigma.C");
   C.SaveAs("A3ZAA2AASigma.eps");
   C.SaveAs("A3ZAA2AASigma.pdf");

   ResultTree->Draw("abs(A3AA/A2AA*(-0.008)-0.000)*sqrt(3.1415926535/2):log(SignalDatasetSize+Background)/log(10)", "Status == 3", "prof");

   C.SaveAs("A3AAA2AASigma.png");
   C.SaveAs("A3AAA2AASigma.C");
   C.SaveAs("A3AAA2AASigma.eps");
   C.SaveAs("A3AAA2AASigma.pdf");
}
