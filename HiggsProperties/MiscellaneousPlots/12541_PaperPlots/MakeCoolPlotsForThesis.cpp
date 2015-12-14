#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
TH2D *ProcessCoolPlot(TFile &File, string IDFront, string IDBack, int ThinningFactor);

int main(int argc, char *argv[])
{
   if(argc < 5)
   {
      cerr << "Usage: " << argv[0] << " Input Output Model=(11|16|31|36) DoO=(0|1)" << endl;
      return -1;
   }

   bool DoO = false;
   if(argv[4][0] == '1')
      DoO = true;

   SetThesisRegularStyle();

   double TrueValue11N[] = {1, 0, 0, 0, 0, 0, 0, 0.375};
   double TrueValue16N[] = {0.15555843629401253, 0.5988999797319482, 0.7855701032847632, 0, 0, 0, 0, 0.375};
   double TrueValue11O[] = {-1, 0, 0, 0, 0, 0, 0, 0.375};
   double TrueValue16O[] = {-1, 3.85, 5.05, 0, 0, 0, 0, 0.375};
   
   double *TrueValue = TrueValue11N;
   if(DoO == false && (string(argv[3]) == "16" || string(argv[3]) == "36"))
      TrueValue = TrueValue16N;
   if(DoO == true && (string(argv[3]) == "16" || string(argv[3]) == "36"))
      TrueValue = TrueValue16O;
   if(DoO == false && (string(argv[3]) == "11" || string(argv[3]) == "31"))
      TrueValue = TrueValue11N;
   if(DoO == true && (string(argv[3]) == "11" || string(argv[3]) == "31"))
      TrueValue = TrueValue11O;

   PsFileHelper PsFile(Form("CoolPlot_%s.ps", argv[2]));
   PsFile.AddTextPage(string("Cool plots from file ") + argv[2]);

   TFile Input(argv[1]);

   TFile Output(argv[2], "RECREATE");

   string Labels[] = {"R_{1}^{ZZ}", "R_{2}^{ZZ}", "R_{3}^{ZZ}", "R_{2}^{Z#gamma}",
      "R_{3}^{Z#gamma}", "R_{2}^{#gamma#gamma}", "R_{3}^{#gamma#gamma}", "F_{B}"};
   if(DoO == true)
   {
      Labels[0] = "Error";
      Labels[1] = "A_{2}^{ZZ} / A_{1}^{ZZ}";
      Labels[2] = "A_{3}^{ZZ} / A_{1}^{ZZ}";
      Labels[3] = "A_{2}^{Z#gamma} / A_{1}^{ZZ}";
      Labels[4] = "A_{3}^{Z#gamma} / A_{1}^{ZZ}";
      Labels[5] = "A_{2}^{#gamma#gamma} / A_{1}^{ZZ}";
      Labels[6] = "A_{3}^{#gamma#gamma} / A_{1}^{ZZ}";
      Labels[7] = "F_{B}";
   }

   string NNString, FString;
   for(int iN = 0; iN < 2; iN++)
   {
      for(int iF = 0; iF < 2; iF++)
      {
         if(iN == 0)   NNString = "NN";
         else          NNString = "YY";

         if(iF == 0)   FString = "N";
         else          FString = "Y";

         for(int iC = 1; iC <= 8; iC++)
         {
            int ThinningFactor = 5;

            TH2D *H = ProcessCoolPlot(Input, Form("H_%s_%s_%s", (DoO ? "O" : ""), NNString.c_str(), FString.c_str()),
               Form("%d", iC), ThinningFactor);
            if(H == NULL)
               continue;
            H->Write();

            TH2D HWorld("HWorld", "", H->GetNbinsX() / ThinningFactor,
               H->GetXaxis()->GetBinLowEdge(1), H->GetXaxis()->GetBinUpEdge(H->GetNbinsX()),
               H->GetNbinsY(),
               H->GetYaxis()->GetBinLowEdge(1), H->GetYaxis()->GetBinUpEdge(H->GetNbinsY()));
            for(int i = 0; i < 7; i++)
               HWorld.GetXaxis()->SetBinLabel(i + 1,
                  H->GetXaxis()->GetBinLabel(ThinningFactor * i + 1 + ThinningFactor / 2));

            TGraph G;
            G.SetLineWidth(5);
            G.SetPoint(0, -100, TrueValue[iC-1]);
            G.SetPoint(1, 100, TrueValue[iC-1]);

            HWorld.SetStats(0);
            H->Rebin2D(1, 3);

            TCanvas C;

            HWorld.Draw();
            H->Draw("colz same");

            HWorld.SetTitle("");
            HWorld.GetXaxis()->SetTitle("N_{S}");
            HWorld.GetYaxis()->SetTitle(Labels[iC-1].c_str());

            // HWorld.GetXaxis()->SetTitleSize(0.06);
            // HWorld.GetYaxis()->SetTitleSize(0.06);
            // HWorld.GetXaxis()->SetTitleOffset(1);
            // HWorld.GetYaxis()->SetTitleOffset(1);

            HWorld.GetXaxis()->SetLabelSize(0.075);
            // HWorld.GetYaxis()->SetLabelSize(0.04);
            // HWorld.GetZaxis()->SetLabelSize(0.04);

            // HWorld.GetXaxis()->CenterTitle(true);
            // HWorld.GetYaxis()->CenterTitle(true);

            G.Draw("l");
            
            C.SetLogz();

            C.SaveAs(Form("PlotsForThesis/CoolPlot%s_%s_%s_%s_%d.png", (DoO ? "O" : ""), argv[2], NNString.c_str(), FString.c_str(), iC));
            C.SaveAs(Form("PlotsForThesis/CoolPlot%s_%s_%s_%s_%d.eps", (DoO ? "O" : ""), argv[2], NNString.c_str(), FString.c_str(), iC));
            C.SaveAs(Form("PlotsForThesis/CoolPlot%s_%s_%s_%s_%d.C",   (DoO ? "O" : ""), argv[2], NNString.c_str(), FString.c_str(), iC));
            C.SaveAs(Form("PlotsForThesis/CoolPlot%s_%s_%s_%s_%d.pdf", (DoO ? "O" : ""), argv[2], NNString.c_str(), FString.c_str(), iC));
            
            TCanvas C2;
            C2.SetLeftMargin(0.15);
            C2.SetRightMargin(0.15);
            C2.SetBottomMargin(0.20);
            HWorld.Draw();
            H->Draw("colz same");
            G.Draw("l");
            C2.SetLogz();

            PsFile.AddTextPage(Form("%s, %s, %s", NNString.c_str(), FString.c_str(), Labels[iC-1].c_str()));
            PsFile.AddCanvas(C2);
         }
      }
   }
   
   Output.Close();

   Input.Close();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

TH2D *ProcessCoolPlot(TFile &File, string IDFront, string IDBack, int ThinningFactor)
{
   vector<TH1D *> H;
   TH1D *SomeH = NULL;
   for(int i = 1; i <= 7; i++)
   {
      H.push_back((TH1D *)File.Get(Form("%s_%d_%s", IDFront.c_str(), i, IDBack.c_str())));
      if(SomeH == NULL && H[i-1] != NULL)
         SomeH = H[i-1];
   }
   if(SomeH == NULL)
      return NULL;

   int Indices[7];
   for(int i = 0; i < 7; i++)
      Indices[i] = i * ThinningFactor + 1 + ThinningFactor / 2;

   int BinCount = SomeH->GetNbinsX();
   double Min = SomeH->GetXaxis()->GetBinLowEdge(1);
   double Max = SomeH->GetXaxis()->GetBinUpEdge(BinCount);

   TH2D *H2D = new TH2D(Form("%s_All_%s", IDFront.c_str(), IDBack.c_str()), "H2D",
      7 * ThinningFactor, 0, 7, BinCount, Min, Max);
   H2D->GetXaxis()->SetBinLabel(Indices[0], "25");
   H2D->GetXaxis()->SetBinLabel(Indices[1], "50");
   H2D->GetXaxis()->SetBinLabel(Indices[2], "100");
   H2D->GetXaxis()->SetBinLabel(Indices[3], "200");
   H2D->GetXaxis()->SetBinLabel(Indices[4], "400");
   H2D->GetXaxis()->SetBinLabel(Indices[5], "800");
   H2D->GetXaxis()->SetBinLabel(Indices[6], "1600");

   for(int i = 1; i <= BinCount; i++)
   {
      int Index = (i - 1) * ThinningFactor + ThinningFactor / 2;
      if(H[0] != NULL)   H2D->SetBinContent(Indices[0], i, H[0]->GetBinContent(i));
      if(H[1] != NULL)   H2D->SetBinContent(Indices[1], i, H[1]->GetBinContent(i));
      if(H[2] != NULL)   H2D->SetBinContent(Indices[2], i, H[2]->GetBinContent(i));
      if(H[3] != NULL)   H2D->SetBinContent(Indices[3], i, H[3]->GetBinContent(i));
      if(H[4] != NULL)   H2D->SetBinContent(Indices[4], i, H[4]->GetBinContent(i));
      if(H[5] != NULL)   H2D->SetBinContent(Indices[5], i, H[5]->GetBinContent(i));
      if(H[6] != NULL)   H2D->SetBinContent(Indices[6], i, H[6]->GetBinContent(i));
   }

   return H2D;
}



