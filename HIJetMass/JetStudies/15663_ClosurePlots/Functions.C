void FourPanelComplicated(TTree *T1, TTree *T2, TTree *T3, string XAxis);
void TidyHistogram(TH1 *A, TH1 *B, TH1 *C, string XAxis);
void TidyHistogram(TH1 *A, TH1 *B, string XAxis);
void TidyHistogramNoNormalize(TH1 *A, TH1 *B, TH1 *C, string XAxis);
void TidyHistogramNoNormalize(TH1 *A, TH1 *B, string XAxis);
void FourPanel(TCanvas *C, TH1 *A1, TH1 *B1, TH1 *C1,
   TH1 *A2, TH1 *B2, TH1 *C2,
   TH1 *A3, TH1 *B3, TH1 *C3,
   TH1 *A4, TH1 *B4, TH1 *C4);
void SetupLegend(TLegend &Legend, TH1 *A, TH1 *B, TH1 *C);

void FourPanelComplicated(TTree *T1, TTree *T2, TTree *T3, string XAxis)
{
   TH1 *A1, *B1, *C1;
   TH1 *A2, *B2, *C2;
   TH1 *A3, *B3, *C3;
   TH1 *A4, *B4, *C4;

   TCanvas C;

   T1->Draw("SDRecoDR[0]>>A1(80,0.0,0.4)", "Base * C0", "");
   T2->Draw("SDRecoDR[0]>>B1(80,0.0,0.4)", "Base * C0", "same");
   T3->Draw("SDRecoDR[0]>>C1(80,0.0,0.4)", "Base * C0", "same");
   T1->Draw("SDRecoDR[0]>>A2(80,0.0,0.4)", "Base * C1", "");
   T2->Draw("SDRecoDR[0]>>B2(80,0.0,0.4)", "Base * C1", "same");
   T3->Draw("SDRecoDR[0]>>C2(80,0.0,0.4)", "Base * C1", "same");
   T1->Draw("SDRecoDR[0]>>A3(80,0.0,0.4)", "Base * C2", "");
   T2->Draw("SDRecoDR[0]>>B3(80,0.0,0.4)", "Base * C2", "same");
   T3->Draw("SDRecoDR[0]>>C3(80,0.0,0.4)", "Base * C2", "same");
   T1->Draw("SDRecoDR[0]>>A4(80,0.0,0.4)", "Base * C3", "");
   T2->Draw("SDRecoDR[0]>>B4(80,0.0,0.4)", "Base * C3", "same");
   T3->Draw("SDRecoDR[0]>>C4(80,0.0,0.4)", "Base * C3", "same");
   
   TidyHistogram(A1, B1, C1, XAxis);
   TidyHistogram(A2, B2, C2, XAxis);
   TidyHistogram(A3, B3, C3, XAxis);
   TidyHistogram(A4, B4, C4, XAxis);

   C.Divide(2,2);
   C.cd(1);
   A1->Draw();
   B1->Draw("same");
   C1->Draw("same");
   C.cd(2);
   A2->Draw();
   B2->Draw("same");
   C2->Draw("same");
   C.cd(3);
   A3->Draw();
   B3->Draw("same");
   C3->Draw("same");
   C.cd(4);
   A4->Draw();
   B4->Draw("same");
   C4->Draw("same");

   TLegend Legend(0.2, 0.8, 0.5, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(A1, "AA Data");
   Legend.AddEntry(B1, "Embedded Pythia 6");
   Legend.AddEntry(C1, "Embedded Pythia 8");
   Legend.Draw();
}

void TidyHistogram(TH1 *A, TH1 *B, TH1 *C, string XAxis)
{
   B->Scale(1 / B->Integral() * A->Integral());
   C->Scale(1 / C->Integral() * A->Integral());
   TidyHistogramNoNormalize(A, B, C, XAxis);
}

void TidyHistogramNoNormalize(TH1 *A, TH1 *B, string XAxis)
{
   B->SetLineColor(kRed);
   B->SetMarkerColor(kRed);
   B->SetMarkerStyle(20);
   A->GetXaxis()->SetTitle(XAxis.c_str());
   A->SetLineColor(kBlack);
   A->SetMarkerColor(kBlack);
   A->SetMarkerStyle(20);
   A->SetTitle("");
   
   A->SetStats(0);
   B->SetStats(0);
}

void TidyHistogramNoNormalize(TH1 *A, TH1 *B, TH1 *C, string XAxis)
{
   B->SetLineColor(kRed);
   B->SetMarkerColor(kRed);
   B->SetMarkerStyle(20);
   C->SetLineColor(kGreen);
   C->SetMarkerColor(kGreen);
   C->SetMarkerStyle(20);
   A->GetXaxis()->SetTitle(XAxis.c_str());
   A->SetLineColor(kBlack);
   A->SetMarkerColor(kBlack);
   A->SetMarkerStyle(20);
   A->SetTitle("");
   
   A->SetStats(0);
   B->SetStats(0);
   C->SetStats(0);
}

void TidyHistogram(TH1 *A, TH1 *B, string XAxis)
{
   B->Scale(1 / B->Integral() * A->Integral());
   TidyHistogramNoNormalize(A, B, XAxis);
}

void FourPanel(TCanvas *C, TH1 *A1, TH1 *B1, TH1 *C1,
   TH1 *A2, TH1 *B2, TH1 *C2,
   TH1 *A3, TH1 *B3, TH1 *C3,
   TH1 *A4, TH1 *B4, TH1 *C4)
{
   C->Divide(2, 2);

   C->cd(1);
   A1->Draw();
   B1->Draw("same");
   C1->Draw("same");

   C->cd(2);
   A2->Draw();
   B2->Draw("same");
   C2->Draw("same");

   C->cd(3);
   A3->Draw();
   B3->Draw("same");
   C3->Draw("same");

   C->cd(4);
   A4->Draw();
   B4->Draw("same");
   C4->Draw("same");
}

void SetupLegend(TLegend &Legend, TH1 *A, TH1 *B, TH1 *C)
{
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(A, "AA Data");
   Legend.AddEntry(B, "Embedded Pythia 6");
   Legend.AddEntry(C, "Embedded Pythia 8");
}


