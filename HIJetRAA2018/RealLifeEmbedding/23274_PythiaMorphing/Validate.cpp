#include <map>
#include <iostream>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TCanvas.h"
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "Code/TauHelperFunctions3.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

#define MAX 100000

int main(int argc, char *argv[]);
void LoopFile(string FileName, map<string, TH1D *> &H,
   bool OriginalJet = false, bool WTA = false, bool NoGrass = false);
void ComparePlot(PdfFileHelper &PdfFile, map<string, TH1D *> &H1, map<string, TH1D *> &H2, string Label);
double GetBinWidth(TH1D *H);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string InputPythia = CL.Get("pythia");
   string InputMorphed = CL.Get("morphed");
   string Output = CL.Get("output");
   bool OriginalJet = CL.GetBool("originaljet", false);
   bool WTA = CL.GetBool("wta", false);
   bool NoGrass = CL.GetBool("nograss", false);

   map<string, TH1D *> HPythia;
   map<string, TH1D *> HMorphed;

   LoopFile(InputPythia, HPythia, OriginalJet, WTA, NoGrass);
   LoopFile(InputMorphed, HMorphed, OriginalJet, WTA, NoGrass);

   PdfFileHelper PdfFile(Output);
   PdfFile.AddTextPage("Validation");

   ComparePlot(PdfFile, HPythia, HMorphed, "JetPT");
   ComparePlot(PdfFile, HPythia, HMorphed, "JetXi");
   ComparePlot(PdfFile, HPythia, HMorphed, "JetRho07");
   ComparePlot(PdfFile, HPythia, HMorphed, "JetRho10");
   ComparePlot(PdfFile, HPythia, HMorphed, "JetRho10Grass");
   ComparePlot(PdfFile, HPythia, HMorphed, "JetRho10NoGrass");
   ComparePlot(PdfFile, HPythia, HMorphed, "JetRho20");
   ComparePlot(PdfFile, HPythia, HMorphed, "JetRho40");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void LoopFile(string FileName, map<string, TH1D *> &H, bool OriginalJet, bool WTA, bool NoGrass)
{
   static int index = 0;
   index = index + 1;

   for(auto iter : H)
   {
      if(iter.second != nullptr)
         delete iter.second;
   }
   H.clear();

   H["JetPT"] = new TH1D(Form("HJetPT_%d", index), ";Jet PT;", 100, 0, 300);
   H["JetXi"] = new TH1D(Form("HJetXi_%d", index), ";#xi;", 20, 0, 5);
   H["JetRho07"] = new TH1D(Form("HJetRho07_%d", index), ";r;#rho(r)_{p_{T} > 0.7}", 20, 0, 0.4);
   H["JetRho10"] = new TH1D(Form("HJetRho10_%d", index), ";r;#rho(r)_{p_{T} > 1.0}", 20, 0, 0.4);
   H["JetRho10Grass"] = new TH1D(Form("HJetRho10Grass_%d", index), ";r;#rho(r)_{p_{T} > 1.0}", 20, 0, 0.4);
   H["JetRho10NoGrass"] = new TH1D(Form("HJetRho10NoGrass_%d", index), ";r;#rho(r)_{p_{T} > 1.0}", 20, 0, 0.4);
   H["JetRho20"] = new TH1D(Form("HJetRho20_%d", index), ";r;#rho(r)_{p_{T} > 2.0}", 20, 0, 0.4);
   H["JetRho40"] = new TH1D(Form("HJetRho40_%d", index), ";r;#rho(r)_{p_{T} > 4.0}", 20, 0, 0.4);

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MorphedTree");

   double JetEtaMax = 2.0;

   double JetR = 0.4;
   int N;
   double E[MAX], PX[MAX], PY[MAX], PZ[MAX];
   int PID[MAX], Status[MAX];
   int NJ;
   double JE[MAX], JPX[MAX], JPY[MAX], JPZ[MAX];

   Tree->SetBranchAddress("N", &N);
   Tree->SetBranchAddress("E", &E);
   Tree->SetBranchAddress("PX", &PX);
   Tree->SetBranchAddress("PY", &PY);
   Tree->SetBranchAddress("PZ", &PZ);
   Tree->SetBranchAddress("PID", &PID);
   Tree->SetBranchAddress("Status", &Status);
   Tree->SetBranchAddress("NJ", &NJ);
   Tree->SetBranchAddress("JE", &JE);
   Tree->SetBranchAddress("JPX", &JPX);
   Tree->SetBranchAddress("JPY", &JPY);
   Tree->SetBranchAddress("JPZ", &JPZ);

   int EntryCount = Tree->GetEntries();
 
   int TotalJet = 0;

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);
      
      vector<FourVector> Particles;
      vector<PseudoJet> FastJetParticles;
      vector<bool> IsGrass;
      for(int i = 0; i < N; i++)
      {
         if(Status[i] != 1)                  continue;
         if(PID[i] == 12 || PID[i] == -12)   continue;
         if(PID[i] == 14 || PID[i] == -14)   continue;
         if(PID[i] == 16 || PID[i] == -16)   continue;

         bool Grass = false;
         if(PID[i] == 299 || PID[i] == -299)
            Grass = true;

         if(NoGrass == true && Grass == true)
            continue;

         FastJetParticles.push_back(PseudoJet(PX[i], PY[i], PZ[i], E[i]));
         Particles.emplace_back(FourVector(E[i], PX[i], PY[i], PZ[i]));
         IsGrass.push_back(Grass);
      }
      
      int NJet;
      vector<FourVector> Jets;
      
      if(OriginalJet == true)
      {
         NJet = NJ;
         for(int iJ = 0; iJ < NJet; iJ++)
            Jets.emplace_back(JE[iJ], JPX[iJ], JPY[iJ], JPZ[iJ]);

         cout << NJ << " " << Jets.size() << endl;
      }
      else
      {
         RecombinationScheme Scheme = WTA ? WTA_pt_scheme : E_scheme;
         JetDefinition Definition(antikt_algorithm, JetR, Scheme);
         ClusterSequence Sequence(FastJetParticles, Definition);
         vector<PseudoJet> FastJets = Sequence.inclusive_jets();

         NJet = FastJets.size();
         for(int iJ = 0; iJ < NJet; iJ++)
            Jets.emplace_back(FastJets[iJ].e(), FastJets[iJ].px(), FastJets[iJ].py(), FastJets[iJ].pz());
      }

      if(iE == 0)
      {
         for(int iJ = 0; iJ < NJet; iJ++)
            if(Jets[iJ].GetPT() > 50)
               cout << Jets[iJ] << endl;
         cout << "===" << endl;
      }

      for(int iJ = 0; iJ < NJet; iJ++)
      {
         if(Jets[iJ].GetAbsEta() > JetEtaMax)
            continue;

         H["JetPT"]->Fill(Jets[iJ].GetPT());

         if(Jets[iJ].GetPT() > 100)
         {
            TotalJet = TotalJet + 1;

            for(int iP = 0; iP < (int)Particles.size(); iP++)
            {
               double DR = GetDR(Particles[iP], Jets[iJ]);
               if(DR > JetR)
                  continue;

               // Fragmentation function: https://arxiv.org/pdf/1406.0932.pdf
               if(Particles[iP].GetPT() > 1)
               {
                  double Z = Jets[iJ].SpatialDot(Particles[iP]) / Jets[iJ].GetP() / Jets[iJ].GetP();
                  double Xi = log(1 / Z);
                  H["JetXi"]->Fill(Xi);
               }

               // Jet shape: https://arxiv.org/pdf/1310.0878.pdf
               if(Particles[iP].GetPT() > 0.7)
                  H["JetRho07"]->Fill(DR, Particles[iP].GetPT() / Jets[iJ].GetPT());
               if(Particles[iP].GetPT() > 1.0)
                  H["JetRho10"]->Fill(DR, Particles[iP].GetPT() / Jets[iJ].GetPT());
               if(Particles[iP].GetPT() > 1.0 && IsGrass[iP] == true)
                  H["JetRho10Grass"]->Fill(DR, Particles[iP].GetPT() / Jets[iJ].GetPT());
               if(Particles[iP].GetPT() > 1.0 && IsGrass[iP] == false)
                  H["JetRho10NoGrass"]->Fill(DR, Particles[iP].GetPT() / Jets[iJ].GetPT());
               if(Particles[iP].GetPT() > 2.0)
                  H["JetRho20"]->Fill(DR, Particles[iP].GetPT() / Jets[iJ].GetPT());
               if(Particles[iP].GetPT() > 4.0)
                  H["JetRho40"]->Fill(DR, Particles[iP].GetPT() / Jets[iJ].GetPT());
            }
         }
      }
   }

   H["JetXi"]->Scale(1.0 / TotalJet / GetBinWidth(H["JetXi"]));
   H["JetRho07"]->Scale(1.0 / TotalJet / GetBinWidth(H["JetRho07"]));
   H["JetRho10"]->Scale(1.0 / TotalJet / GetBinWidth(H["JetRho10"]));
   H["JetRho10Grass"]->Scale(1.0 / TotalJet / GetBinWidth(H["JetRho10Grass"]));
   H["JetRho10NoGrass"]->Scale(1.0 / TotalJet / GetBinWidth(H["JetRho10NoGrass"]));
   H["JetRho20"]->Scale(1.0 / TotalJet / GetBinWidth(H["JetRho20"]));
   H["JetRho40"]->Scale(1.0 / TotalJet / GetBinWidth(H["JetRho40"]));

   File.Close();
}

void ComparePlot(PdfFileHelper &PdfFile, map<string, TH1D *> &H1, map<string, TH1D *> &H2, string Label)
{
   PdfFile.AddTextPage("Comparing " + Label);

   TCanvas Canvas;

   H1[Label]->SetStats(0);
   H2[Label]->SetStats(0);
   H1[Label]->SetLineWidth(2);
   H2[Label]->SetLineWidth(2);
   H1[Label]->SetLineColor(kBlue);
   H2[Label]->SetLineColor(kRed);
   H1[Label]->SetMarkerColor(kBlue);
   H2[Label]->SetMarkerColor(kRed);

   double Max = max(H1[Label]->GetMaximum(), H2[Label]->GetMaximum());

   H1[Label]->SetMaximum(Max * 1.2);
   H1[Label]->Draw();
   H2[Label]->Draw("same");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(H1[Label], "Original", "l");
   Legend.AddEntry(H2[Label], "Morphed", "l");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);
   H1[Label]->SetMaximum(Max * 2);
   Canvas.SetLogy();
   PdfFile.AddCanvas(Canvas);

   TH1D *H = (TH1D *)H2[Label]->Clone();
   H->Divide(H1[Label]);

   H->SetLineColor(kBlue);
   H->SetMarkerColor(kBlue);
   H->GetYaxis()->SetTitle("Morphed / Original");

   PdfFile.AddPlot(H);

   delete H;
}

double GetBinWidth(TH1D *H)
{
   if(H == nullptr)
      return 1;

   int N = H->GetNbinsX();
   double Max = H->GetXaxis()->GetBinUpEdge(N);
   double Min = H->GetXaxis()->GetBinLowEdge(1);
   return (Max - Min) / N;
}

