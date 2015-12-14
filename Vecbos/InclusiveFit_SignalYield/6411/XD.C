{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Dec  8 18:04:32 2010) by ROOT version5.27/04
   TCanvas *c1 = new TCanvas("c1", "c1",15,49,700,502);
   c1->Range(-0.125,-0.13125,1.125,1.18125);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TF1 *XD = new TF1("XD","pol1",0,1);
   XD->SetFillColor(19);
   XD->SetFillStyle(0);
   XD->SetLineWidth(1);
   XD->SetLineStyle(2);
   XD->SetParameter(0,0);
   XD->SetParError(0,0);
   XD->SetParLimits(0,0,0);
   XD->SetParameter(1,0);
   XD->SetParError(1,0);
   XD->SetParLimits(1,0,0);
   XD->Draw("");
   
   TPaveText *pt = new TPaveText(0.01,0.9416102,0.09034483,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   TText *text = pt->AddText("pol1");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
