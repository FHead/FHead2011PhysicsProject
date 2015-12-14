{
//=========Macro generated from canvas: jetInclNumber_cuts_30_Z_dataMC/jetInclNumber_cuts_30_Z_dataMC
//=========  (Mon Jan 17 14:51:50 2011) by ROOT version5.27/04
   TCanvas *jetInclNumber_cuts_30_Z_dataMC = new TCanvas("jetInclNumber_cuts_30_Z_dataMC", "jetInclNumber_cuts_30_Z_dataMC",687,360,700,500);
   gStyle->SetOptFit(1);
   jetInclNumber_cuts_30_Z_dataMC->Range(-0.625,0.6336985,5.625,4.848297);
   jetInclNumber_cuts_30_Z_dataMC->SetFillColor(0);
   jetInclNumber_cuts_30_Z_dataMC->SetBorderSize(2);
   jetInclNumber_cuts_30_Z_dataMC->SetLogy();
   
   TH1D *jetInclNumber_cuts_30_Z_data__1 = new TH1D("jetInclNumber_cuts_30_Z_data__1","",6,0,6);
   jetInclNumber_cuts_30_Z_data__1->SetBinContent(1,13984);
   jetInclNumber_cuts_30_Z_data__1->SetBinContent(2,2359);
   jetInclNumber_cuts_30_Z_data__1->SetBinContent(3,503);
   jetInclNumber_cuts_30_Z_data__1->SetBinContent(4,118);
   jetInclNumber_cuts_30_Z_data__1->SetBinContent(5,28);
   jetInclNumber_cuts_30_Z_data__1->SetEntries(16992);
   jetInclNumber_cuts_30_Z_data__1->SetDirectory(0);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.755,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetTextAlign(12);
   TText *text = ptstats->AddText("jetInclNumber_cuts_30_Z_data");
   text->SetTextSize(0.0552);
   text = ptstats->AddText("Entries = 16992  ");
   text = ptstats->AddText("Mean  = 0.7255");
   text = ptstats->AddText("RMS   = 0.5434");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(111);
   ptstats->Draw();
   jetInclNumber_cuts_30_Z_data__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(jetInclNumber_cuts_30_Z_data__1->GetListOfFunctions());
   jetInclNumber_cuts_30_Z_data__1->SetLineColor(2);
   jetInclNumber_cuts_30_Z_data__1->SetMarkerColor(2);
   jetInclNumber_cuts_30_Z_data__1->GetXaxis()->SetTitle("inclusive number of jets");
   jetInclNumber_cuts_30_Z_data__1->GetXaxis()->SetRange(1,5);
   jetInclNumber_cuts_30_Z_data__1->GetYaxis()->SetTitle("Events");
   jetInclNumber_cuts_30_Z_data__1->Draw("E");
   
   TH1D *jetInclNumber_cuts_30_Z_tt__2 = new TH1D("jetInclNumber_cuts_30_Z_tt__2","jet inclusive number (with cuts, pt>30)",6,0,6);
   jetInclNumber_cuts_30_Z_tt__2->SetBinContent(1,57.31838);
   jetInclNumber_cuts_30_Z_tt__2->SetBinContent(2,56.49675);
   jetInclNumber_cuts_30_Z_tt__2->SetBinContent(3,49.35641);
   jetInclNumber_cuts_30_Z_tt__2->SetBinContent(4,30.14595);
   jetInclNumber_cuts_30_Z_tt__2->SetBinContent(5,12.91131);
   jetInclNumber_cuts_30_Z_tt__2->SetEntries(10542);
   jetInclNumber_cuts_30_Z_tt__2->SetDirectory(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#009900");
   jetInclNumber_cuts_30_Z_tt__2->SetLineColor(ci);
   jetInclNumber_cuts_30_Z_tt__2->GetXaxis()->SetTitle("inclusive number of jets");
   jetInclNumber_cuts_30_Z_tt__2->GetYaxis()->SetTitle("Events");
   jetInclNumber_cuts_30_Z_tt__2->Draw("same");
   
   TH1D *jetInclNumber_cuts_30_Z_MCW__3 = new TH1D("jetInclNumber_cuts_30_Z_MCW__3","jet inclusive number (with cuts, pt>30)",6,0,6);
   jetInclNumber_cuts_30_Z_MCW__3->SetBinContent(1,94.91605);
   jetInclNumber_cuts_30_Z_MCW__3->SetBinContent(2,82.81512);
   jetInclNumber_cuts_30_Z_MCW__3->SetBinContent(3,61.38766);
   jetInclNumber_cuts_30_Z_MCW__3->SetBinContent(4,33.90571);
   jetInclNumber_cuts_30_Z_MCW__3->SetBinContent(5,13.66326);
   jetInclNumber_cuts_30_Z_MCW__3->SetEntries(10649);
   jetInclNumber_cuts_30_Z_MCW__3->SetDirectory(0);

   ci = TColor::GetColor("#ff9900");
   jetInclNumber_cuts_30_Z_MCW__3->SetLineColor(ci);
   jetInclNumber_cuts_30_Z_MCW__3->GetXaxis()->SetTitle("inclusive number of jets");
   jetInclNumber_cuts_30_Z_MCW__3->GetYaxis()->SetTitle("Events");
   jetInclNumber_cuts_30_Z_MCW__3->Draw("same");
   
   TH1D *jetInclNumber_cuts_30_Z_QCD__4 = new TH1D("jetInclNumber_cuts_30_Z_QCD__4","jet inclusive number (with cuts, pt>30)",6,0,6);
   jetInclNumber_cuts_30_Z_QCD__4->SetBinContent(1,137.9517);
   jetInclNumber_cuts_30_Z_QCD__4->SetBinContent(2,100.0294);
   jetInclNumber_cuts_30_Z_QCD__4->SetBinContent(3,65.69122);
   jetInclNumber_cuts_30_Z_QCD__4->SetBinContent(4,36.05749);
   jetInclNumber_cuts_30_Z_QCD__4->SetBinContent(5,13.66326);
   jetInclNumber_cuts_30_Z_QCD__4->SetEntries(10680);
   jetInclNumber_cuts_30_Z_QCD__4->SetDirectory(0);
   jetInclNumber_cuts_30_Z_QCD__4->SetLineColor(6);
   jetInclNumber_cuts_30_Z_QCD__4->GetXaxis()->SetTitle("inclusive number of jets");
   jetInclNumber_cuts_30_Z_QCD__4->GetYaxis()->SetTitle("Events");
   jetInclNumber_cuts_30_Z_QCD__4->Draw("same");
   
   TH1D *jetInclNumber_cuts_30_Z_MCZ__5 = new TH1D("jetInclNumber_cuts_30_Z_MCZ__5","jet inclusive number (with cuts, pt>30)",6,0,6);
   jetInclNumber_cuts_30_Z_MCZ__5->SetBinContent(1,14552.69);
   jetInclNumber_cuts_30_Z_MCZ__5->SetBinContent(2,2370.794);
   jetInclNumber_cuts_30_Z_MCZ__5->SetBinContent(3,505.6156);
   jetInclNumber_cuts_30_Z_MCZ__5->SetBinContent(4,111.2629);
   jetInclNumber_cuts_30_Z_MCZ__5->SetBinContent(5,27.82604);
   jetInclNumber_cuts_30_Z_MCZ__5->SetEntries(167479);
   jetInclNumber_cuts_30_Z_MCZ__5->SetDirectory(0);
   jetInclNumber_cuts_30_Z_MCZ__5->GetXaxis()->SetTitle("inclusive number of jets");
   jetInclNumber_cuts_30_Z_MCZ__5->GetYaxis()->SetTitle("Events");
   jetInclNumber_cuts_30_Z_MCZ__5->Draw("same");
   
   TLegend *leg = new TLegend(0.5,0.6,0.7,0.8,NULL,"brNDC");
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("jetInclNumber_cuts_30_Z_data","data","LP");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("jetInclNumber_cuts_30_Z_MCZ","signal","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("jetInclNumber_cuts_30_Z_QCD","QCD","L");
   entry->SetLineColor(6);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("jetInclNumber_cuts_30_Z_MCW","W","L");

   ci = TColor::GetColor("#ff9900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("jetInclNumber_cuts_30_Z_tt","TTBar","L");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   jetInclNumber_cuts_30_Z_dataMC->Modified();
   jetInclNumber_cuts_30_Z_dataMC->cd();
   jetInclNumber_cuts_30_Z_dataMC->SetSelected(jetInclNumber_cuts_30_Z_dataMC);
}
