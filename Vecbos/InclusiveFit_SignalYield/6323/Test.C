{
//=========Macro generated from canvas: Canvas2/Canvas2
//=========  (Wed Oct 20 15:48:25 2010) by ROOT version5.27/04
   TCanvas *Canvas2 = new TCanvas("Canvas2", "Canvas2",5,49,1024,768);
   Canvas2->Range(0,0,1,1);
   Canvas2->SetFillColor(0);
   Canvas2->SetBorderMode(0);
   Canvas2->SetBorderSize(2);
   Canvas2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: Canvas2_1
   TPad *Canvas2_1 = new TPad("Canvas2_1", "Canvas2_1",0.009803922,0.3378378,0.9892157,0.9905405);
   Canvas2_1->Draw();
   Canvas2_1->cd();
   Canvas2_1->Range(-3.725291e-08,-0.9215841,5,3.065469);
   Canvas2_1->SetFillColor(0);
   Canvas2_1->SetBorderMode(0);
   Canvas2_1->SetBorderSize(2);
   Canvas2_1->SetLogy();
   Canvas2_1->SetFrameBorderMode(0);
   Canvas2_1->SetFrameBorderMode(0);
   
   TH1D *HInclusiveYields = new TH1D("HInclusiveYields","Inclusive yields for PF jets",4,0.5,4.5);
   HInclusiveYields->SetBinContent(1,154.7543);
   HInclusiveYields->SetBinContent(2,28.20298);
   HInclusiveYields->SetBinContent(3,4.674409);
   HInclusiveYields->SetBinContent(4,1.930733e-05);
   HInclusiveYields->SetBinError(1,13.34652);
   HInclusiveYields->SetBinError(2,6.0306);
   HInclusiveYields->SetBinError(3,2.425097);
   HInclusiveYields->SetBinError(4,1.077088);
   HInclusiveYields->SetMinimum(0.3);
   HInclusiveYields->SetMaximum(464.2629);
   HInclusiveYields->SetEntries(4);
   HInclusiveYields->SetStats(0);
   HInclusiveYields->GetXaxis()->SetTitle("Inclusive jet count");
   HInclusiveYields->GetYaxis()->SetTitle("Yield");
   HInclusiveYields->Draw("error");
   
   TPaveText *pt = new TPaveText(0.01,0.9375676,0.2430852,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   TText *text = pt->AddText("Inclusive yields for PF jets");
   pt->Draw();
   Canvas2_1->Modified();
   Canvas2->cd();
  
// ------------>Primitives in pad: Canvas2_2
   Canvas2_2 = new TPad("Canvas2_2", "Canvas2_2",0.009803922,0.01081081,0.9892157,0.3175676);
   Canvas2_2->Draw();
   Canvas2_2->cd();
   Canvas2_2->Range(-3.725291e-08,-1.23626,5,11.12634);
   Canvas2_2->SetFillColor(0);
   Canvas2_2->SetBorderMode(0);
   Canvas2_2->SetBorderSize(2);
   Canvas2_2->SetFrameBorderMode(0);
   Canvas2_2->SetFrameBorderMode(0);
   
   TH1D *HRatio = new TH1D("HRatio","Ratio",4,0.5,4.5);
   HRatio->SetBinContent(1,5.487162);
   HRatio->SetBinContent(2,6.033485);
   HRatio->SetBinError(1,1.265151);
   HRatio->SetBinError(2,3.385636);
   HRatio->SetEntries(2);
   HRatio->SetStats(0);
   HRatio->GetXaxis()->SetTitle("N (Inclusive jet count)");
   HRatio->GetYaxis()->SetTitle("#frac{Z + N Jets}{Z + (N+1) Jets}");
   HRatio->Draw("error");
   
   pt = new TPaveText(0.01,0.945,0.07201681,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   text = pt->AddText("Ratio");
   pt->Draw();
   Canvas2_2->Modified();
   Canvas2->cd();
   Canvas2->Modified();
   Canvas2->cd();
   Canvas2->SetSelected(Canvas2);
}
