{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Jul 31 10:37:37 2009) by ROOT version5.18/00a
   TCanvas *c1 = new TCanvas("c1", "c1",8,49,699,501);
   c1->Range(-37.5,5.362355,367.5,5.671985);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   
   TGraph *graph = new TGraph(7);
   graph->SetName("Graph");
   graph->SetTitle("Mean of max-energy-layer over events");
   graph->SetFillColor(1);
   graph->SetMarkerStyle(20);
   graph->SetPoint(0,300,5.58324);
   graph->SetPoint(1,225,5.53678);
   graph->SetPoint(2,150,5.62038);
   graph->SetPoint(3,50,5.41396);
   graph->SetPoint(4,30,5.4614);
   graph->SetPoint(5,99.79983,5.528172);
   graph->SetPoint(6,100,5.53681);
   
   TH1 *Graph_h1 = new TH1F("Graph_h1","Mean of max-energy-layer over events",100,3,327);
   Graph_h1->SetMinimum(5.393318);
   Graph_h1->SetMaximum(5.641022);
   Graph_h1->SetDirectory(0);
   Graph_h1->SetStats(0);
   Graph_h1->GetXaxis()->SetTitle("Energy (GeV)");
   Graph_h1->GetYaxis()->SetTitle("Mean Layer");
   graph->SetHistogram(Graph_h1);
   
   graph->Draw("ap");
   
   TPaveText *pt = new TPaveText(0.01,0.945,0.5870698,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(2);
   pt->SetFillColor(19);
   TText *text = pt->AddText("Mean of max-energy-layer over events");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
