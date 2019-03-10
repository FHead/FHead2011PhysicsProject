#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TLegend.h"

#include "PlotHelper3.h"
#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
double GetDistance(double PT1, double Eta1, double Phi1, double PT2, double Eta2, double Phi2);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputFile = CL.Get("input");
   string OutputFile = CL.Get("output", "CHSCheck.pdf");
   string PFTree = CL.Get("pf", "ak4pf");
   string PFCHSTree = CL.Get("pfchs", "ak4pfchs");

   PdfFileHelper PdfFile(OutputFile);
   PdfFile.AddTextPage("PF vs PFCHS check");

   TH2D HPFVsPFCHS("HPFVsPFCHS", Form(";%s;%s", PFTree.c_str(), PFCHSTree.c_str()), 100, 0, 500, 100, 0, 500);
   TH2D HDiffVsRho("HDiffVsRho", Form(";Rho;%s - %s", PFTree.c_str(), PFCHSTree.c_str()), 100, 0, 70, 100, -50, 50);
   TProfile PDiffVsRho("PDiffVsRho", Form(";Rho;%s - %s", PFTree.c_str(), PFCHSTree.c_str()), 40, 0, 70);
   TH1D HDistance("HDistance", ";Distance;#", 100, 0, 1);
   TProfile PGenDiffPFVsRho("PGenDiffPFVsRho", Form(";Rho;RawPT * 1.1 - Gen", PFTree.c_str()), 40, 0, 70);
   TProfile PGenDiffPFCHSVsRho("PGenDiffPFCHSVsRho", Form(";Rho;RawPT * 1.1 - Gen", PFCHSTree.c_str()), 40, 0, 70);

   HPFVsPFCHS.SetStats(0);
   HDiffVsRho.SetStats(0);
   PGenDiffPFVsRho.SetStats(0);
   PGenDiffPFCHSVsRho.SetStats(0);

   PDiffVsRho.SetMarkerColor(kMagenta);
   PDiffVsRho.SetLineColor(kMagenta);

   PGenDiffPFVsRho.SetMarkerColor(kBlue);
   PGenDiffPFVsRho.SetLineColor(kBlue);
   PGenDiffPFCHSVsRho.SetMarkerColor(kRed);
   PGenDiffPFCHSVsRho.SetLineColor(kRed);

   TFile File(InputFile.c_str());

   TTree *T1 = (TTree *)File.Get(Form("%s/t", PFTree.c_str()));
   TTree *T2 = (TTree *)File.Get(Form("%s/t", PFCHSTree.c_str()));

   vector<float> *JetPT1 = NULL, *JetEta1 = NULL, *JetPhi1 = NULL;
   vector<float> *RefPT1 = NULL, *RefEta1 = NULL, *RefPhi1 = NULL;
   vector<float> *JetPT2 = NULL, *JetEta2 = NULL, *JetPhi2 = NULL;
   vector<float> *RefPT2 = NULL, *RefEta2 = NULL, *RefPhi2 = NULL;
   float Rho;

   T1->SetBranchAddress("jtpt", &JetPT1);
   T1->SetBranchAddress("jteta", &JetEta1);
   T1->SetBranchAddress("jtphi", &JetPhi1);
   T1->SetBranchAddress("refpt", &RefPT1);
   T1->SetBranchAddress("refeta", &RefEta1);
   T1->SetBranchAddress("refphi", &RefPhi1);
   
   T2->SetBranchAddress("jtpt", &JetPT2);
   T2->SetBranchAddress("jteta", &JetEta2);
   T2->SetBranchAddress("jtphi", &JetPhi2);
   T2->SetBranchAddress("refpt", &RefPT2);
   T2->SetBranchAddress("refeta", &RefEta2);
   T2->SetBranchAddress("refphi", &RefPhi2);

   T2->SetBranchAddress("rho", &Rho);

   int EntryCount = T1->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T1->GetEntry(iE);
      T2->GetEntry(iE);

      for(int i = 0; i < (int)RefPT1->size(); i++)
      {
         if((*RefPT1)[i] < 20 || (*RefPT1)[i] > 500)
            continue;
         if((*RefEta1)[i] < -2 || (*RefEta1)[i] > 2)
            continue;

         double BestJ = -1;
         double BestDistance = -1;
         for(int j = 0; j < (int)RefPT2->size(); j++)
         {
            if((*RefPT2)[j] < 20)
               continue;
            if((*RefEta2)[i] < -2 || (*RefEta2)[i] > 2)
               continue;

            double Distance = GetDistance((*RefPT1)[i], (*RefEta1)[i], (*RefPhi1)[i],
               (*RefPT2)[j], (*RefEta2)[j], (*RefPhi2)[j]);
            if(BestDistance < 0)
            {
               BestJ = j;
               BestDistance = Distance;
            }
            else if(Distance < BestDistance)
            {
               BestJ = j;
               BestDistance = Distance;
            }
         }

         if(BestDistance < 0)
            continue;

         HPFVsPFCHS.Fill((*JetPT1)[i], (*JetPT2)[BestJ]);
         HDiffVsRho.Fill(Rho, (*JetPT1)[i] - (*JetPT2)[BestJ]);
         PDiffVsRho.Fill(Rho, (*JetPT1)[i] - (*JetPT2)[BestJ]);
         HDistance.Fill(BestDistance);

         PGenDiffPFVsRho.Fill(Rho, 1.1 * (*JetPT1)[i] - (*RefPT1)[i]);
         PGenDiffPFCHSVsRho.Fill(Rho, 1.1 * (*JetPT2)[BestJ] - (*RefPT2)[BestJ]);
      }
   }

   File.Close();

   PdfFile.AddPlot(HPFVsPFCHS, "colz");

   TCanvas Canvas;
   HDiffVsRho.Draw("colz");
   PDiffVsRho.Draw("same");
   Canvas.SetLogz();
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddPlot(HDistance, "", true);

   TLegend Legend(0.2, 0.8, 0.5, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&PGenDiffPFVsRho, PFTree.c_str(), "pl");
   Legend.AddEntry(&PGenDiffPFCHSVsRho, PFCHSTree.c_str(), "pl");

   PGenDiffPFVsRho.SetMaximum(40);
   PGenDiffPFVsRho.Draw();
   PGenDiffPFCHSVsRho.Draw("same");
   Legend.Draw();
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

double GetDistance(double PT1, double Eta1, double Phi1, double PT2, double Eta2, double Phi2)
{
   double DPT = PT1 - PT2;
   double DEta = Eta1 - Eta2;
   double DPhi = Phi1 - Phi2;

   while(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
   while(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;

   return (DPT * DPT + DEta * DEta + DPhi * DPhi);
}







