{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Aug 18 11:50:06 2009) by ROOT version5.18/00a
   TCanvas *c1 = new TCanvas("c1", "c1",8,49,699,501);
   c1->Range(-41.25,-0.02427843,371.25,0.2185059);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   
   TGraphErrors *gre = new TGraphErrors(8);
   gre->SetName("Graph");
   gre->SetTitle("Energy resolution");
   gre->SetFillColor(1);
   gre->SetPoint(0,300,0.1001882);
   gre->SetPointError(0,0,0.00244752);
   gre->SetPoint(1,225,0.09823777);
   gre->SetPointError(1,0,0.002058109);
   gre->SetPoint(2,149.8914,0.1001947);
   gre->SetPointError(2,0,0.002335099);
   gre->SetPoint(3,100,0.1103824);
   gre->SetPointError(3,0,0.002092482);
   gre->SetPoint(4,99.99787,0.113135);
   gre->SetPointError(4,0,0.001811544);
   gre->SetPoint(5,50,0.1326045);
   gre->SetPointError(5,0,0.00427263);
   gre->SetPoint(6,30,0.1725512);
   gre->SetPointError(6,0,0.004019207);
   gre->SetPoint(7,0,0);
   gre->SetPointError(7,0,0);
   
   TH1 *Graph_h1 = new TH1F("Graph_h1","Energy resolution",100,0,330);
   Graph_h1->SetMinimum(0);
   Graph_h1->SetMaximum(0.1942275);
   Graph_h1->SetDirectory(0);
   Graph_h1->SetStats(0);
   Graph_h1->GetXaxis()->SetTitle("Energy (GeV)");
   Graph_h1->GetYaxis()->SetTitle("Resolution");
   Graph_h1->GetYaxis()->SetTitleOffset(1.1);
   gre->SetHistogram(Graph_h1);
   
   gre->Draw("ap");
   
   TPaveText *pt = new TPaveText(0.01,0.9401777,0.2889438,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   TText *text = pt->AddText("Energy resolution");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
