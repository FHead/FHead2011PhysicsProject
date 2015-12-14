{
//=========Macro generated from canvas: C/C
//=========  (Fri Dec 14 00:37:18 2012) by ROOT version5.30/00
   TCanvas *C = new TCanvas("C", "C",0,0,1024,1024);
   C->SetHighLightColor(2);
   C->Range(0,0,1,1);
   C->SetFillColor(0);
   C->SetBorderMode(0);
   C->SetBorderSize(2);
   C->SetFrameBorderMode(0);
   
   TGraph *graph = new TGraph(15);
   graph->SetName("");
   graph->SetTitle("");
   graph->SetFillColor(1);
   graph->SetMarkerStyle(11);
   graph->SetPoint(0,0.05,0.43966);
   graph->SetPoint(1,0.02,0.46838);
   graph->SetPoint(2,0.01,0.49523);
   graph->SetPoint(3,0.005,0.50255);
   graph->SetPoint(4,0.002,0.54802);
   graph->SetPoint(5,0.001,0.57919);
   graph->SetPoint(6,0.0005,0.61138);
   graph->SetPoint(7,0.0002,0.69695);
   graph->SetPoint(8,0.0001,0.82256);
   graph->SetPoint(9,5e-05,1.17122);
   graph->SetPoint(10,2e-05,1.39186);
   graph->SetPoint(11,1e-05,2.14189);
   graph->SetPoint(12,5e-06,3.67954);
   graph->SetPoint(13,2e-06,5.95942);
   graph->SetPoint(14,1e-06,8.42486);
   graph->Draw("ap");

   graph->SetTitle("Time per event for adapted Simpson with tolerance (1, 0.1, 0.01, 0.1)X, and top-level division of (10, 10, 10, 10)");
   graph->GetXaxis()->SetTitle("Top-level tolerance level (relative)");
   graph->GetYaxis()->SetTitle("Time used per event (s)");

   C->SetLogx();
   C->SetLogy();
   C->SetGridx();
   C->SetGridy();

   C->Modified();
   C->cd();
   C->SetSelected(C);

   C->SaveAs("PrecisionVsTime.png");
   C->SaveAs("PrecisionVsTime.eps");
   C->SaveAs("PrecisionVsTime.pdf");
}
