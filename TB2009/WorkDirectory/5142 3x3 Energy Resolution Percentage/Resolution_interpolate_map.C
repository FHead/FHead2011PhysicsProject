{
//=========Macro generated from canvas: c1/c1
//=========  (Wed Aug 19 14:51:56 2009) by ROOT version5.18/00a
   TCanvas *c1 = new TCanvas("c1", "c1",8,49,699,501);
   c1->Range(-40.72341,-0.02425466,371.4255,0.216552);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   
   TGraphErrors *gre = new TGraphErrors(8);
   gre->SetName("Graph");
   gre->SetTitle("Resolution (\sigma/<E>)");
   gre->SetFillColor(1);
   gre->SetLineColor(4);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(4);
   gre->SetPoint(0,300,0.07541937);
   gre->SetPointError(0,0,0.0007352021);
   gre->SetPoint(1,225,0.08564238);
   gre->SetPointError(1,0,0.0008350517);
   gre->SetPoint(2,150,0.09829155);
   gre->SetPointError(2,0,0.000892306);
   gre->SetPoint(3,100,0.1178402);
   gre->SetPointError(3,0,0.0008577563);
   gre->SetPoint(4,99.70213,0.1156295);
   gre->SetPointError(4,0,0.001351154);
   gre->SetPoint(5,49.40162,0.1379337);
   gre->SetPointError(5,0,0.001421709);
   gre->SetPoint(6,30,0.1738448);
   gre->SetPointError(6,0,0.001351425);
   gre->SetPoint(7,0,0);
   gre->SetPointError(7,0,0);
   
   TH1 *Graph_h12 = new TH1F("Graph_h12","Resolution (\sigma/<E>)",100,0,330);
   Graph_h12->SetMinimum(0.0001927158);
   Graph_h12->SetMaximum(0.1927158);
   Graph_h12->SetDirectory(0);
   Graph_h12->SetStats(0);
   Graph_h12->GetXaxis()->SetTitle("Beam energy (GeV)");
   Graph_h12->GetYaxis()->SetTitle("Resolution");
   Graph_h12->GetYaxis()->SetTitleOffset(1.1);
   gre->SetHistogram(Graph_h12);
   
   
   TF1 *f = new TF1("f","[0]/sqrt(x)+[1]",0,1);
   f->SetFillColor(19);
   f->SetFillStyle(0);
   f->SetLineWidth(3);
   f->SetParameter(0,0);
   f->SetParError(0,1.414214);
   f->SetParLimits(0,0,0);
   f->SetParameter(1,0);
   f->SetParError(1,1);
   f->SetParLimits(1,0,0);
   gre->GetListOfFunctions()->Add(f);
   
   TF1 *f = new TF1("f","[0]/sqrt(x)+[1]",25,310);
   f->SetFillColor(19);
   f->SetFillStyle(0);
   f->SetLineWidth(2);
   f->SetLineStyle(3);
   f->SetChisquare(102.1645);
   f->SetParameter(0,0.7825575);
   f->SetParError(0,0.01055496);
   f->SetParLimits(0,0,0);
   f->SetParameter(1,0.0336109);
   f->SetParError(1,0.001006705);
   f->SetParLimits(1,0,0);
   gre->GetListOfFunctions()->Add(f);
   gre->Draw("ap");
   
   TPaveText *pt = new TPaveText(0.01,0.945,0.3025724,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   TText *text = pt->AddText("Resolution (\sigma/<E>)");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
