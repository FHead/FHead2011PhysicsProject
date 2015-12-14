{
//=========Macro generated from canvas: c1/c1
//=========  (Mon Aug  3 10:59:13 2009) by ROOT version5.18/00a
   TCanvas *c1 = new TCanvas("c1", "c1",8,49,492,499);
   c1->Range(-41.25,-0.5193568,371.25,4.674211);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   
   TGraph *graph = new TGraph(7);
   graph->SetName("Graph");
   graph->SetTitle("Energy deposited in central tower / incoming particle energy");
   graph->SetFillColor(1);
   graph->SetMarkerStyle(20);
   graph->SetPoint(0,300,3.644433);
   graph->SetPoint(1,225,3.279342);
   graph->SetPoint(2,150,3.327153);
   graph->SetPoint(3,100,3.13071);
   graph->SetPoint(4,100,3.05071);
   graph->SetPoint(5,49.40162,3.777859);
   graph->SetPoint(6,30,3.686033);
   
   TH1 *Graph_h1 = new TH1F("Graph_h1","Energy deposited in central tower / incoming particle energy",100,0,330);
   Graph_h1->SetMinimum(0);
   Graph_h1->SetMaximum(4.154854);
   Graph_h1->SetDirectory(0);
   Graph_h1->SetStats(0);
   Graph_h1->GetXaxis()->SetTitle("Pion energy (GeV)");
   Graph_h1->GetYaxis()->SetTitle("Energy (MIP) / incoming energy (GeV)");
   graph->SetHistogram(Graph_h1);
   
   graph->Draw("ap");
   
   TPaveText *pt = new TPaveText(0.01,0.9401777,0.71,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   TText *text = pt->AddText("Energy deposited in central tower / incoming particle energy");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
