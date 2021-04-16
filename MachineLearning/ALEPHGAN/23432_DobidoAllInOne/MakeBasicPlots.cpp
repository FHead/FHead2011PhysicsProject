#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TF1.h"

#include "TauHelperFunctions3.h"
#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

#define MAX 10000

#define DMODE_ALL 0
#define DMODE_OPPOSITE 1
#define DMODE_SAME 2
#define DMODE_ALL_STOREDMASS 3
#define DMODE_OPPOSITE_STOREDMASS 4
#define DMODE_SAME_STOREDMASS 5
#define DMODE_ALL_MID 6
#define DMODE_OPPOSITE_MID 7
#define DMODE_SAME_MID 8

int main(int argc, char *argv[]);
void Add1D(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Selection, string Title, int N, double Min, double Max);
void Add1D(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2);
void FillDCandidate(TTree *T, TH1D &H, int DMode, double MinP);

int main(int argc, char *argv[])
{
   SetThesisStyle();
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string BaseName    = CL.Get("Base");
   string VariantName = CL.Get("Variant");
   string OutputName  = CL.Get("Output");
   string OutputRoot  = CL.Get("OutputRoot", "Meow.root");

   TFile FBase(BaseName.c_str());
   TFile FVariant(VariantName.c_str());
   TFile FOutput(OutputRoot.c_str(), "RECREATE");

   TTree *TBase = (TTree *)FBase.Get("tgan");
   TTree *TVariant = (TTree *)FVariant.Get("tgan");

   PdfFileHelper PdfFile(OutputName);
   PdfFile.AddTextPage("GAN output comparison");

   PdfFile.AddTextPage({"Input files:", BaseName, VariantName});

   Add1D(PdfFile, TBase, TVariant, "px", "", ";p_{x};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "py", "", ";p_{y};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "pz", "", ";p_{z};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "theta", "", ";#theta;", 100, 0, M_PI);
   Add1D(PdfFile, TBase, TVariant, "phi", "", ";#phi;", 100, -M_PI, M_PI);
   Add1D(PdfFile, TBase, TVariant, "pmag", "", ";p;", 100, 0, 50);
   Add1D(PdfFile, TBase, TVariant, "nParticle", "", ";Mult.;", 100, 0, 100);
   Add1D(PdfFile, TBase, TVariant, "Sum$(pmag>1)", "", ";Mult. (p > 1);", 70, 0, 70);
   Add1D(PdfFile, TBase, TVariant, "charge", "", ";charge;", 3, -1, 2);
   Add1D(PdfFile, TBase, TVariant, "charge", "pmag > 1", "p > 1;charge;", 3, -1, 2);
   Add1D(PdfFile, TBase, TVariant, "px[0]", "", "first particle;p_{x};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "py[0]", "", "first particle;p_{y};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "pz[0]", "", "first particle;p_{z};", 100, -50, 50);
   Add1D(PdfFile, TBase, TVariant, "pmag[0]", "", "first particle;p;", 100, 0, 50);

   TH1D HDOppositeBase("HDOppositeBase", ";Opposite sign pair mass;", 100, 1.5, 2.0);
   TH1D HDSameBase("HDSameBase", ";Same sign pair mass;", 100, 1.5, 2.0);
   TH1D HDAllBase("HDAllBase", ";All pair mass;", 100, 1.5, 2.0);
   TH1D HDOppositeVariant("HDOppositeVariant", ";Opposite sign pair mass;", 100, 1.5, 2.0);
   TH1D HDSameVariant("HDSameVariant", ";Same sign pair mass;", 100, 1.5, 2.0);
   TH1D HDAllVariant("HDAllVariant", ";All pair mass;", 100, 1.5, 2.0);
   TH1D HD1OppositeBase("HD1OppositeBase", ";Opposite sign pair mass;", 100, 1.5, 2.0);
   TH1D HD1SameBase("HD1SameBase", ";Same sign pair mass;", 100, 1.5, 2.0);
   TH1D HD1AllBase("HD1AllBase", ";All pair mass;", 100, 1.5, 2.0);
   TH1D HD1OppositeVariant("HD1OppositeVariant", ";Opposite sign pair mass;", 100, 1.5, 2.0);
   TH1D HD1SameVariant("HD1SameVariant", ";Same sign pair mass;", 100, 1.5, 2.0);
   TH1D HD1AllVariant("HD1AllVariant", ";All pair mass;", 100, 1.5, 2.0);
   TH1D HD2OppositeBase("HD2OppositeBase", ";Opposite sign pair mass;", 100, 1.5, 2.0);
   TH1D HD2SameBase("HD2SameBase", ";Same sign pair mass;", 100, 1.5, 2.0);
   TH1D HD2AllBase("HD2AllBase", ";All pair mass;", 100, 1.5, 2.0);
   TH1D HD2OppositeVariant("HD2OppositeVariant", ";Opposite sign pair mass;", 100, 1.5, 2.0);
   TH1D HD2SameVariant("HD2SameVariant", ";Same sign pair mass;", 100, 1.5, 2.0);
   TH1D HD2AllVariant("HD2AllVariant", ";All pair mass;", 100, 1.5, 2.0);

   FillDCandidate(TBase, HDOppositeBase, DMODE_OPPOSITE, 0);
   FillDCandidate(TBase, HDSameBase, DMODE_SAME, 0);
   // FillDCandidate(TBase, HDAllBase, DMODE_ALL, 0);
   FillDCandidate(TVariant, HDOppositeVariant, DMODE_OPPOSITE, 0);
   FillDCandidate(TVariant, HDSameVariant, DMODE_SAME, 0);
   // FillDCandidate(TVariant, HDAllVariant, DMODE_ALL, 0);
   FillDCandidate(TBase, HD1OppositeBase, DMODE_OPPOSITE, 1);
   FillDCandidate(TBase, HD1SameBase, DMODE_SAME, 1);
   // FillDCandidate(TBase, HD1AllBase, DMODE_ALL, 1);
   FillDCandidate(TVariant, HD1OppositeVariant, DMODE_OPPOSITE, 1);
   FillDCandidate(TVariant, HD1SameVariant, DMODE_SAME, 1);
   // FillDCandidate(TVariant, HD1AllVariant, DMODE_ALL, 1);
   FillDCandidate(TBase, HD2OppositeBase, DMODE_OPPOSITE, 2);
   FillDCandidate(TBase, HD2SameBase, DMODE_SAME, 2);
   // FillDCandidate(TBase, HD2AllBase, DMODE_ALL, 2);
   FillDCandidate(TVariant, HD2OppositeVariant, DMODE_OPPOSITE, 2);
   FillDCandidate(TVariant, HD2SameVariant, DMODE_SAME, 2);
   // FillDCandidate(TVariant, HD2AllVariant, DMODE_ALL, 2);

   TH1D HDDiffBase("HDDiffBase", ";Pair mass;Opposite - Same", 100, 1.5, 2.0);
   TH1D HDDiffVariant("HDDiffVariant", ";Pair mass;Opposite - Same", 100, 1.5, 2.0);
   for(int i = 1; i <= HDOppositeBase.GetNbinsX(); i++)
   {
      double BS = HDSameBase.GetBinContent(i);
      double BO = HDOppositeBase.GetBinContent(i);
      double VS = HDSameVariant.GetBinContent(i);
      double VO = HDOppositeVariant.GetBinContent(i);

      HDDiffBase.SetBinContent(i, BO - BS);
      HDDiffVariant.SetBinContent(i, VO - VS);
   }

   HDOppositeBase.Write();
   HDSameBase.Write();
   HDAllBase.Write();
   HDOppositeVariant.Write();
   HDSameVariant.Write();
   HDAllVariant.Write();
   HD1OppositeBase.Write();
   HD1SameBase.Write();
   HD1AllBase.Write();
   HD1OppositeVariant.Write();
   HD1SameVariant.Write();
   HD1AllVariant.Write();
   HD2OppositeBase.Write();
   HD2SameBase.Write();
   HD2AllBase.Write();
   HD2OppositeVariant.Write();
   HD2SameVariant.Write();
   HD2AllVariant.Write();
   
   Add1D(PdfFile, HDAllBase, HDAllVariant);
   Add1D(PdfFile, HDOppositeBase, HDOppositeVariant);
   Add1D(PdfFile, HDSameBase, HDSameVariant);
   Add1D(PdfFile, HDDiffBase, HDDiffVariant);

   TLatex Latex;
   Latex.SetNDC();
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(11);

   TF1 F("F", "[0]*exp(-(x-[1])*(x-[1])/[2]/[2]/2)+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.5, 2.0);
   F.SetParameters(0.0003, 1.86, 0.001, 0.117, -0.149, 0.0703, -0.01156);
   // F.SetParLimits(1, 1.84, 1.90);
   // F.SetParLimits(2, 0, 0.1);
   HDOppositeBase.Fit(&F);

   TCanvas Canvas;
   HDOppositeBase.Draw();
   F.Draw("same");
   double Factor = 1 / fabs(F.GetParameter(2)) / sqrt(2 * M_PI);
   // Latex.DrawLatex(0.15, 0.30, Form("N = %.4f #pm %.4f", F.GetParameter(0) * Factor, F.GetParError(0) * Factor));
   Latex.DrawLatex(0.15, 0.25, Form("M = %.4f #pm %.4f", F.GetParameter(1), F.GetParError(1)));
   Latex.DrawLatex(0.15, 0.20, Form("#sigma = %.4f #pm %.4f", F.GetParameter(2), F.GetParError(2)));
   Latex.DrawLatex(0.10, 0.92, Form("#color[%d]{Reference}", Colors[1]));
   PdfFile.AddCanvas(Canvas);
   
   HDOppositeVariant.Fit(&F);
   HDOppositeVariant.SetStats(0);
   
   HDOppositeVariant.Draw();
   F.Draw("same");
   // Latex.DrawLatex(0.15, 0.30, Form("N = %.1f #pm %.1f", F.GetParameter(0), F.GetParError(0)));
   Latex.DrawLatex(0.15, 0.25, Form("M = %.4f #pm %.4f", F.GetParameter(1), F.GetParError(1)));
   Latex.DrawLatex(0.15, 0.20, Form("#sigma = %.4f #pm %.4f", F.GetParameter(2), F.GetParError(2)));
   Latex.DrawLatex(0.10, 0.92, Form("#color[%d]{Meow}", Colors[0]));
   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FOutput.Close();
   FVariant.Close();
   FBase.Close();

   return 0;
}

void Add1D(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string ToPlot, string Selection, string Title, int N, double Min, double Max)
{
   static int index = 0;
   index = index + 1;

   TH1D H1(Form("H%d_1", index), Title.c_str(), N, Min, Max);
   TH1D H2(Form("H%d_2", index), Title.c_str(), N, Min, Max);

   T1->Draw(Form("%s>>H%d_1", ToPlot.c_str(), index), Selection.c_str());
   T2->Draw(Form("%s>>H%d_2", ToPlot.c_str(), index), Selection.c_str());

   Add1D(PdfFile, H1, H2);
}

void Add1D(PdfFileHelper &PdfFile, TH1D &H1, TH1D &H2)
{
   static vector<int> Colors;
   if(Colors.size() == 0)
      Colors = GetPrimaryColors();

   H1.SetLineColor(Colors[1]);
   H1.SetMarkerStyle(20);
   H1.SetMarkerColor(Colors[1]);

   H2.SetLineColor(Colors[0]);
   H2.SetMarkerStyle(20);
   H2.SetMarkerColor(Colors[0]);

   H1.Scale(1 / H1.Integral());
   H2.Scale(1 / H2.Integral());

   H1.SetStats(0);

   TCanvas Canvas;

   H1.Draw();
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();
   Latex.DrawLatex(0.10, 0.92, Form("#color[%d]{Reference} #color[%d]{Meow}", Colors[1], Colors[0]));

   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);

   H1.SetMinimum(0);
   H1.Draw();
   H1.Draw("hist same");
   H2.Draw("same");
   H2.Draw("hist same");
   
   Latex.DrawLatex(0.10, 0.92, Form("#color[%d]{Reference} #color[%d]{Meow}", Colors[1], Colors[0]));

   Canvas.SetLogy(false);
   PdfFile.AddCanvas(Canvas);
   
   H1.SetMinimum();
}

void FillDCandidate(TTree *T, TH1D &H, int DMode, double MinP)
{
   if(T == nullptr)
      return;

   int NParticle;
   float PX[MAX];
   float PY[MAX];
   float PZ[MAX];
   float Mass[MAX];
   short Charge[MAX];

   T->SetBranchAddress("nParticle", &NParticle);
   T->SetBranchAddress("px", &PX);
   T->SetBranchAddress("py", &PY);
   T->SetBranchAddress("pz", &PZ);
   T->SetBranchAddress("mass", &Mass);
   T->SetBranchAddress("charge", &Charge);

   double KMass = 0.4937;
   double PiMass = 0.13957;
   double Tolerance = 0.1;

   int EntryCount = T->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      for(int i = 0; i < NParticle; i++)
      {
         if(DMode == DMODE_OPPOSITE || DMode == DMODE_SAME)
            if(Charge[i] == 0)
               continue;
         if(DMode == DMODE_OPPOSITE_STOREDMASS || DMode == DMODE_SAME_STOREDMASS)
            if(Charge[i] == 0)
               continue;
         
         if(DMode == DMODE_ALL_MID || DMode == DMODE_OPPOSITE_MID || DMode == DMODE_SAME_MID)
            if(Mass[i] < KMass - Tolerance || Mass[i] > KMass + Tolerance)
               continue;

         for(int j = 0; j < NParticle; j++)
         {
            if(i == j)
               continue;
            // if(DMode == DMODE_ALL || DMode == DMODE_OPPOSITE || DMode == DMODE_SAME)
            //    if(i < j)
            //       continue;
            // if(DMode == DMODE_ALL_STOREDMASS || DMode == DMODE_OPPOSITE_STOREDMASS || DMode == DMODE_SAME_STOREDMASS)
            //    if(i < j)
            //       continue;

            if(DMode == DMODE_OPPOSITE || DMode == DMODE_SAME)
               if(Charge[j] == 0)
                  continue;
            if(DMode == DMODE_OPPOSITE_STOREDMASS || DMode == DMODE_SAME_STOREDMASS)
               if(Charge[j] == 0)
                  continue;
            if(DMode == DMODE_OPPOSITE_MID || DMode == DMODE_SAME_MID)
               if(Charge[j] == 0)
                  continue;
         
            if(DMode == DMODE_ALL_MID || DMode == DMODE_OPPOSITE_MID || DMode == DMODE_SAME_MID)
               if(Mass[j] < PiMass - Tolerance || Mass[j] > PiMass + Tolerance)
                  continue;

            if(DMode == DMODE_OPPOSITE && Charge[i] == Charge[j])
               continue;
            if(DMode == DMODE_SAME && Charge[i] != Charge[j])
               continue;
            if(DMode == DMODE_OPPOSITE_STOREDMASS && Charge[i] == Charge[j])
               continue;
            if(DMode == DMODE_SAME_STOREDMASS && Charge[i] != Charge[j])
               continue;
            if(DMode == DMODE_OPPOSITE_MID && Charge[i] == Charge[j])
               continue;
            if(DMode == DMODE_SAME_MID && Charge[i] != Charge[j])
               continue;

            if(DMode == DMODE_ALL || DMode == DMODE_SAME || DMode == DMODE_OPPOSITE)
            {
               FourVector P1(0, PX[i], PY[i], PZ[i]);
               FourVector P2(0, PX[j], PY[j], PZ[j]);

               P1[0] = sqrt(P1.GetP() * P1.GetP() + KMass * KMass);
               P2[0] = sqrt(P2.GetP() * P2.GetP() + PiMass * PiMass);

               if((P1 + P2).GetP() > MinP)
                  H.Fill((P1 + P2).GetMass(), 0.5);

               P1[0] = sqrt(P1.GetP() * P1.GetP() + PiMass * PiMass);
               P2[0] = sqrt(P2.GetP() * P2.GetP() + KMass * KMass);

               if((P1 + P2).GetP() > MinP)
                  H.Fill((P1 + P2).GetMass(), 0.5);
            }
            else if(DMode == DMODE_ALL_STOREDMASS || DMode == DMODE_OPPOSITE_STOREDMASS || DMode == DMODE_SAME_STOREDMASS || DMode == DMODE_ALL_MID || DMode == DMODE_OPPOSITE_MID || DMode == DMODE_SAME_MID)
            {
               FourVector P1(0, PX[i], PY[i], PZ[i]);
               FourVector P2(0, PX[j], PY[j], PZ[j]);

               P1[0] = sqrt(P1.GetP() * P1.GetP() + Mass[i] * Mass[i]);
               P2[0] = sqrt(P2.GetP() * P2.GetP() + Mass[j] * Mass[j]);

               if((P1 + P2).GetP() > MinP)
                  H.Fill((P1 + P2).GetMass());
            }
         }
      }
   }
}
