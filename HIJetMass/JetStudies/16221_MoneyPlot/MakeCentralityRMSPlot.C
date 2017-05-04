{
   TFile F("CentralityDependence.root");

   TGraph *GData = (TGraph *)F.Get("AADataMB");
   TGraph *GMC = (TGraph *)F.Get("HydjetMB");

   TCanvas C;

   GData->Draw("apl");
   GData->GetXaxis()->SetTitle("Centrality");
   GData->GetYaxis()->SetTitle("RMS");

   C.SaveAs("DataRMS.png");
   C.SaveAs("DataRMS.C");
   C.SaveAs("DataRMS.eps");
   C.SaveAs("DataRMS.pdf");

   GMC->Draw("apl");
   GMC->GetXaxis()->SetTitle("Centrality");
   GMC->GetYaxis()->SetTitle("RMS");

   C.SaveAs("MCRMS.png");
   C.SaveAs("MCRMS.C");
   C.SaveAs("MCRMS.eps");
   C.SaveAs("MCRMS.pdf");
}
