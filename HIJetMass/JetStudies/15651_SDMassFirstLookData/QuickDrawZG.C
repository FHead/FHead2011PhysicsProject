{
   gROOT->LoadMacro("~/RootMacros/SetStyle.h");
   SetThesisStyle();

   TFile File285216("Output-285216.root");
   TFile File285530("Output-285530.root");
   TTree *Tree285216 = (TTree *)File285216.Get("Tree");
   TTree *Tree285530 = (TTree *)File285530.Get("Tree");

   TCanvas Canvas;

   TH1D H1("H1", "", 10, 0, 0.5);
   Tree285216->Draw("JetZG>>H1", "JetConePT > 120 && JetConePT < 140", "");
   H1.Sumw2();
   H1.Scale(1 / H1.Integral() / (0.5/10));
   H1.GetXaxis()->SetTitle("Z_{g}");
   H1.GetYaxis()->SetTitle("#frac{1}{N_{jet}} #frac{d N}{d Z_{g}}");
   H1.SetStats(0);

   H1.SetMaximum(8.50);
   H1.SetMarkerStyle(20);
   H1.SetMarkerSize(1.8);
   H1.SetMarkerColor(kBlue);
   H1.SetLineColor(kBlue);
   H1.SetLineWidth(2);
   
   TH1D H2("H2", "", 10, 0, 0.5);
   Tree285530->Draw("JetZG>>H2", "JetConePT > 120 && JetConePT < 140", "");
   H2.Sumw2();
   H2.Scale(1 / H2.Integral() / (0.5/10));
   H2.GetXaxis()->SetTitle("Z_{g}");
   H2.SetStats(0);

   H2.SetMarkerStyle(20);
   H2.SetMarkerSize(1.8);
   H2.SetMarkerColor(kRed);
   H2.SetLineColor(kRed);

   H1.Draw();
   H2.Draw("same");

   TFile FileMV("FromMarta/ZgInclusiveZgMin000__anaZgHistos.root");
   TH1D *HZG = (TH1D *)FileMV.Get("hZgCent0Pt2");   // 2 = 120-140

   HZG->Draw("same");

   TLegend Legend(0.4, 0.8, 0.8, 0.6);
   Legend.SetFillStyle(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.AddEntry(&H1, "Run 285216 (5 TeV pA)", "lp");
   Legend.AddEntry(&H2, "Run 285530 (8 TeV pA)", "lp");
   Legend.AddEntry(HZG, "ZG Analysis (5 TeV pp)", "lp");
   Legend.Draw();

   Canvas.SetGridx();
   Canvas.SetGridy();

   Canvas.SaveAs("ZG.png");
   Canvas.SaveAs("ZG.C");
   Canvas.SaveAs("ZG.eps");
   Canvas.SaveAs("ZG.pdf");
}

