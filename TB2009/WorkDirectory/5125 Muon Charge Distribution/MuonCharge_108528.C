{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Aug 19 16:13:59 2009) by ROOT version5.18/00a
   TCanvas *c1 = new TCanvas("c1", "c1",8,49,699,501);
   c1->Range(-43.75,-0.8576336,219.75,4.708402);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetFrameFillColor(0);
   
   TH1 *TotalCharge = new TH1D("TotalCharge","Muon (run 108528)",30000,-1000,50000);
   TotalCharge->SetBinContent(588,14);
   TotalCharge->SetBinContent(589,3277);
   TotalCharge->SetBinContent(590,7486);
   TotalCharge->SetBinContent(591,606);
   TotalCharge->SetBinContent(592,134);
   TotalCharge->SetBinContent(593,60);
   TotalCharge->SetBinContent(594,36);
   TotalCharge->SetBinContent(595,17);
   TotalCharge->SetBinContent(596,13);
   TotalCharge->SetBinContent(597,9);
   TotalCharge->SetBinContent(598,7);
   TotalCharge->SetBinContent(599,5);
   TotalCharge->SetBinContent(600,10);
   TotalCharge->SetBinContent(601,6);
   TotalCharge->SetBinContent(602,6);
   TotalCharge->SetBinContent(603,2);
   TotalCharge->SetBinContent(604,2);
   TotalCharge->SetBinContent(605,5);
   TotalCharge->SetBinContent(606,3);
   TotalCharge->SetBinContent(607,2);
   TotalCharge->SetBinContent(608,2);
   TotalCharge->SetBinContent(609,2);
   TotalCharge->SetBinContent(610,1);
   TotalCharge->SetBinContent(612,1);
   TotalCharge->SetBinContent(614,4);
   TotalCharge->SetBinContent(617,2);
   TotalCharge->SetBinContent(619,1);
   TotalCharge->SetBinContent(623,1);
   TotalCharge->SetBinContent(626,1);
   TotalCharge->SetBinContent(628,1);
   TotalCharge->SetEntries(11716);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.835,0.98,0.995,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(2);
   ptstats->SetFillColor(19);
   ptstats->SetTextAlign(12);
   TText *text = ptstats->AddText("TotalCharge");
   text->SetTextSize(0.0368);
   text = ptstats->AddText("Entries = 11716  ");
   text = ptstats->AddText("Mean  =  2.015");
   text = ptstats->AddText("RMS   =  2.442");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   TotalCharge->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(TotalCharge->GetListOfFunctions());
   TotalCharge->GetXaxis()->SetTitle("Energy (GeV)");
   TotalCharge->GetXaxis()->SetRange(579,702);
   TotalCharge->Draw("");
   
   TPaveText *pt = new TPaveText(0.01,0.9432234,0.3008688,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   text = pt->AddText("Muon (run 108528)");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
