{
//=========Macro generated from canvas: c1/c1
//=========  (Sat Sep 26 22:52:48 2009) by ROOT version5.18/00a
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,696,472);
   c1->Range(-19.275,5.082362,365.475,7.279788);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogx();
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TGraph *graph = new TGraph(7);
   graph->SetName("Graph");
   graph->SetTitle("Mean layer of energy deposition");
   graph->SetFillColor(1);
   graph->SetMarkerStyle(8);
   graph->SetPoint(0,300,6.91355);
   graph->SetPoint(1,225,6.88681);
   graph->SetPoint(2,150,6.68096);
   graph->SetPoint(3,50,5.90608);
   graph->SetPoint(4,30,5.4486);
   graph->SetPoint(5,100,6.44408);
   graph->SetPoint(6,100,6.49035);
   
   TH1 *Graph1 = new TH1F("Graph1","Mean layer of energy deposition",100,3,327);
   Graph1->SetMinimum(5.302105);
   Graph1->SetMaximum(7.060045);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   Graph1->GetXaxis()->SetTitle("Energy (Gev)");
   Graph1->GetXaxis()->SetRange(6,100);
   Graph1->GetYaxis()->SetTitle("Mean Layer");
   graph->SetHistogram(Graph1);
   
   graph->Draw("ap");
   
   TPaveText *pt = new TPaveText(0.01,0.9382432,0.4924277,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(1);
   TText *text = pt->AddText("Mean layer of energy deposition");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
