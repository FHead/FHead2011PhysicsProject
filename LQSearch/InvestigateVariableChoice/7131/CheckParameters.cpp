// //---------------------------------------------------------------------------
#include <iostream>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TColor.h"
#include "TLegend.h"
//---------------------------------------------------------------------------
#include "PlotHelper2.h"
#include "ReadLQ3Tree.h"
#include "TauHelperFunctions2.h"
#include "SetStyle.h"
//---------------------------------------------------------------------------
class SampleHistograms;
int main(int argc, char *argv[]);
SampleHistograms ReadSample(PsFileHelper &PsFile, string FileName, string Tag = "", double CrossSection = 1);
//---------------------------------------------------------------------------
class SampleHistograms
{
public:
   string FileName;
   string Tag;
   double CrossSection;
   int AllEvents;
   TH1D *HMR_R020Cut;
   TH1D *HMRStar_MRTMRStar020Cut;
   TH1D *HMRStar_MRTGammaMRStar020Cut;
   TH1D *HGammaMRStar_MRTGammaMRStar020Cut;
   TH1D *HMR_R040Cut;
   TH1D *HMRStar_MRTMRStar040Cut;
   TH1D *HMRStar_MRTGammaMRStar040Cut;
   TH1D *HGammaMRStar_MRTGammaMRStar040Cut;
   TH1D *HMR_R060Cut;
   TH1D *HMRStar_MRTMRStar060Cut;
   TH1D *HMRStar_MRTGammaMRStar060Cut;
   TH1D *HGammaMRStar_MRTGammaMRStar060Cut;

public:
   SampleHistograms() {}
   ~SampleHistograms() {}
   void CleanHistograms()
   {
      if(HMR_R020Cut != NULL)                         delete HMR_R020Cut;
      if(HMRStar_MRTMRStar020Cut != NULL)             delete HMRStar_MRTMRStar020Cut;
      if(HMRStar_MRTGammaMRStar020Cut != NULL)        delete HMRStar_MRTGammaMRStar020Cut;
      if(HGammaMRStar_MRTGammaMRStar020Cut != NULL)   delete HGammaMRStar_MRTGammaMRStar020Cut;
      if(HMR_R040Cut != NULL)                         delete HMR_R040Cut;
      if(HMRStar_MRTMRStar040Cut != NULL)             delete HMRStar_MRTMRStar040Cut;
      if(HMRStar_MRTGammaMRStar040Cut != NULL)        delete HMRStar_MRTGammaMRStar040Cut;
      if(HGammaMRStar_MRTGammaMRStar040Cut != NULL)   delete HGammaMRStar_MRTGammaMRStar040Cut;
      if(HMR_R060Cut != NULL)                         delete HMR_R060Cut;
      if(HMRStar_MRTMRStar060Cut != NULL)             delete HMRStar_MRTMRStar060Cut;
      if(HMRStar_MRTGammaMRStar060Cut != NULL)        delete HMRStar_MRTGammaMRStar060Cut;
      if(HGammaMRStar_MRTGammaMRStar060Cut != NULL)   delete HGammaMRStar_MRTGammaMRStar060Cut;
   }
};
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   SetStyle();

   PsFileHelper PsFile("InvestigatingVariableChoice.ps");
   PsFile.AddTextPage("Investigate variable choice!");

   vector<SampleHistograms> Samples;

   Samples.push_back(ReadSample(PsFile, "Samples/LQ350_LQ3Tree.root", "LQ350", 0.477));
   Samples.push_back(ReadSample(PsFile, "Samples/LQ450_LQ3Tree.root", "LQ450", 0.0949));
   Samples.push_back(ReadSample(PsFile, "Samples/TTJets_TuneZ2_7TeV-madgraph-tauola_all.root", "TTbar", 165));
   Samples.push_back(ReadSample(PsFile, "Samples/WJetsToLNu_TuneZ2_7TeV-madgraph-tauola_all.root", "W", 31314));
   Samples.push_back(ReadSample(PsFile, "Samples/ZZtoAnything_TuneZ2_7TeV-pythia6-tauola_all.root", "ZZ", 5.9));
   Samples.push_back(ReadSample(PsFile, "Samples/WZtoAnything_TuneZ2_7TeV-pythia6-tauola_all.root", "WZ", 18.2));
   Samples.push_back(ReadSample(PsFile, "Samples/WWtoAnything_TuneZ2_7TeV-pythia6-tauola_all.root", "WW", 43));
   // Samples.push_back(ReadSample(PsFile, "Samples/PhotonVJets_7TeV-madgraph_all.root", "GammaVJet", 173));
   Samples.push_back(ReadSample(PsFile, "Samples/DYJetsToLL_TuneD6T_M-10To50_7TeV-madgraph-tauola_all.root",
      "DY_10_50", 3100));   // Guessed
   Samples.push_back(ReadSample(PsFile, "Samples/DYJetsToLL_TuneD6T_M-50_7TeV-madgraph-tauola_all.root",
      "DY_50", 3048));

   PsFile.AddTextPage("Summary plots");

   const double IntegratedLuminosity = 1000;   // 1/fb

   for(int i = (int)Samples.size() - 1; i > 2; i--)
   {
      Samples[i-1].HMR_R020Cut->Add(Samples[i].HMR_R020Cut);
      Samples[i-1].HMRStar_MRTMRStar020Cut->Add(Samples[i].HMRStar_MRTMRStar020Cut);
      Samples[i-1].HMRStar_MRTGammaMRStar020Cut->Add(Samples[i].HMRStar_MRTGammaMRStar020Cut);
      Samples[i-1].HGammaMRStar_MRTGammaMRStar020Cut->Add(Samples[i].HGammaMRStar_MRTGammaMRStar020Cut);
      Samples[i-1].HMR_R040Cut->Add(Samples[i].HMR_R040Cut);
      Samples[i-1].HMRStar_MRTMRStar040Cut->Add(Samples[i].HMRStar_MRTMRStar040Cut);
      Samples[i-1].HMRStar_MRTGammaMRStar040Cut->Add(Samples[i].HMRStar_MRTGammaMRStar040Cut);
      Samples[i-1].HGammaMRStar_MRTGammaMRStar040Cut->Add(Samples[i].HGammaMRStar_MRTGammaMRStar040Cut);
      Samples[i-1].HMR_R060Cut->Add(Samples[i].HMR_R060Cut);
      Samples[i-1].HMRStar_MRTMRStar060Cut->Add(Samples[i].HMRStar_MRTMRStar060Cut);
      Samples[i-1].HMRStar_MRTGammaMRStar060Cut->Add(Samples[i].HMRStar_MRTGammaMRStar060Cut);
      Samples[i-1].HGammaMRStar_MRTGammaMRStar060Cut->Add(Samples[i].HGammaMRStar_MRTGammaMRStar060Cut);
   }

   for(int i = 0; i < (int)Samples.size(); i++)
   {
      Samples[i].HMR_R020Cut->SetLineColor(i + 1);
      Samples[i].HMRStar_MRTMRStar020Cut->SetLineColor(i + 1);
      Samples[i].HMRStar_MRTGammaMRStar020Cut->SetLineColor(i + 1);
      Samples[i].HGammaMRStar_MRTGammaMRStar020Cut->SetLineColor(i + 1);
      Samples[i].HMR_R040Cut->SetLineColor(i + 1);
      Samples[i].HMRStar_MRTMRStar040Cut->SetLineColor(i + 1);
      Samples[i].HMRStar_MRTGammaMRStar040Cut->SetLineColor(i + 1);
      Samples[i].HGammaMRStar_MRTGammaMRStar040Cut->SetLineColor(i + 1);
      Samples[i].HMR_R060Cut->SetLineColor(i + 1);
      Samples[i].HMRStar_MRTMRStar060Cut->SetLineColor(i + 1);
      Samples[i].HMRStar_MRTGammaMRStar060Cut->SetLineColor(i + 1);
      Samples[i].HGammaMRStar_MRTGammaMRStar060Cut->SetLineColor(i + 1);

      Samples[i].HMR_R020Cut->SetMinimum(0.03);
      Samples[i].HMRStar_MRTMRStar020Cut->SetMinimum(0.03);
      Samples[i].HMRStar_MRTGammaMRStar020Cut->SetMinimum(0.03);
      Samples[i].HGammaMRStar_MRTGammaMRStar020Cut->SetMinimum(0.03);
      Samples[i].HMR_R040Cut->SetMinimum(0.03);
      Samples[i].HMRStar_MRTMRStar040Cut->SetMinimum(0.03);
      Samples[i].HMRStar_MRTGammaMRStar040Cut->SetMinimum(0.03);
      Samples[i].HGammaMRStar_MRTGammaMRStar040Cut->SetMinimum(0.03);
      Samples[i].HMR_R060Cut->SetMinimum(0.03);
      Samples[i].HMRStar_MRTMRStar060Cut->SetMinimum(0.03);
      Samples[i].HMRStar_MRTGammaMRStar060Cut->SetMinimum(0.03);
      Samples[i].HGammaMRStar_MRTGammaMRStar060Cut->SetMinimum(0.03);

      if(i >= 2)
      {
         Samples[i].HMR_R020Cut->SetFillColor(i + 1);
         Samples[i].HMRStar_MRTMRStar020Cut->SetFillColor(i + 1);
         Samples[i].HMRStar_MRTGammaMRStar020Cut->SetFillColor(i + 1);
         Samples[i].HGammaMRStar_MRTGammaMRStar020Cut->SetFillColor(i + 1);
         Samples[i].HMR_R040Cut->SetFillColor(i + 1);
         Samples[i].HMRStar_MRTMRStar040Cut->SetFillColor(i + 1);
         Samples[i].HMRStar_MRTGammaMRStar040Cut->SetFillColor(i + 1);
         Samples[i].HGammaMRStar_MRTGammaMRStar040Cut->SetFillColor(i + 1);
         Samples[i].HMR_R060Cut->SetFillColor(i + 1);
         Samples[i].HMRStar_MRTMRStar060Cut->SetFillColor(i + 1);
         Samples[i].HMRStar_MRTGammaMRStar060Cut->SetFillColor(i + 1);
         Samples[i].HGammaMRStar_MRTGammaMRStar060Cut->SetFillColor(i + 1);
      }
   }

   TCanvas Canvas_MR_R020;
   Samples[2].HMR_R020Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HMR_R020Cut->Draw("same");
   Samples[0].HMR_R020Cut->Draw("same");
   Samples[1].HMR_R020Cut->Draw("same");
   Canvas_MR_R020.SetLogy();
   PsFile.AddCanvas(Canvas_MR_R020);

   TCanvas Canvas_MRStar_MRTMRStar020;
   Samples[2].HMRStar_MRTMRStar020Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HMRStar_MRTMRStar020Cut->Draw("same");
   Samples[0].HMRStar_MRTMRStar020Cut->Draw("same");
   Samples[1].HMRStar_MRTMRStar020Cut->Draw("same");
   Canvas_MRStar_MRTMRStar020.SetLogy();
   PsFile.AddCanvas(Canvas_MRStar_MRTMRStar020);

   TCanvas Canvas_MRStar_MRTGammaMRStar020;
   Samples[2].HMRStar_MRTGammaMRStar020Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HMRStar_MRTGammaMRStar020Cut->Draw("same");
   Samples[0].HMRStar_MRTGammaMRStar020Cut->Draw("same");
   Samples[1].HMRStar_MRTGammaMRStar020Cut->Draw("same");
   Canvas_MRStar_MRTGammaMRStar020.SetLogy();
   PsFile.AddCanvas(Canvas_MRStar_MRTGammaMRStar020);

   TCanvas Canvas_GammaMRStar_MRTGammaMRStar020;
   Samples[2].HGammaMRStar_MRTGammaMRStar020Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HGammaMRStar_MRTGammaMRStar020Cut->Draw("same");
   Samples[0].HGammaMRStar_MRTGammaMRStar020Cut->Draw("same");
   Samples[1].HGammaMRStar_MRTGammaMRStar020Cut->Draw("same");
   Canvas_GammaMRStar_MRTGammaMRStar020.SetLogy();
   PsFile.AddCanvas(Canvas_GammaMRStar_MRTGammaMRStar020);

   TCanvas Canvas_MR_R040;
   Samples[2].HMR_R040Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HMR_R040Cut->Draw("same");
   Samples[0].HMR_R040Cut->Draw("same");
   Samples[1].HMR_R040Cut->Draw("same");
   Canvas_MR_R040.SetLogy();
   PsFile.AddCanvas(Canvas_MR_R040);

   TCanvas Canvas_MRStar_MRTMRStar040;
   Samples[2].HMRStar_MRTMRStar040Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HMRStar_MRTMRStar040Cut->Draw("same");
   Samples[0].HMRStar_MRTMRStar040Cut->Draw("same");
   Samples[1].HMRStar_MRTMRStar040Cut->Draw("same");
   Canvas_MRStar_MRTMRStar040.SetLogy();
   PsFile.AddCanvas(Canvas_MRStar_MRTMRStar040);

   TCanvas Canvas_MRStar_MRTGammaMRStar040;
   Samples[2].HMRStar_MRTGammaMRStar040Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HMRStar_MRTGammaMRStar040Cut->Draw("same");
   Samples[0].HMRStar_MRTGammaMRStar040Cut->Draw("same");
   Samples[1].HMRStar_MRTGammaMRStar040Cut->Draw("same");
   Canvas_MRStar_MRTGammaMRStar040.SetLogy();
   PsFile.AddCanvas(Canvas_MRStar_MRTGammaMRStar040);

   TCanvas Canvas_GammaMRStar_MRTGammaMRStar040;
   Samples[2].HGammaMRStar_MRTGammaMRStar040Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HGammaMRStar_MRTGammaMRStar040Cut->Draw("same");
   Samples[0].HGammaMRStar_MRTGammaMRStar040Cut->Draw("same");
   Samples[1].HGammaMRStar_MRTGammaMRStar040Cut->Draw("same");
   Canvas_GammaMRStar_MRTGammaMRStar040.SetLogy();
   PsFile.AddCanvas(Canvas_GammaMRStar_MRTGammaMRStar040);

   TCanvas Canvas_MR_R060;
   Samples[2].HMR_R060Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HMR_R060Cut->Draw("same");
   Samples[0].HMR_R060Cut->Draw("same");
   Samples[1].HMR_R060Cut->Draw("same");
   Canvas_MR_R060.SetLogy();
   PsFile.AddCanvas(Canvas_MR_R060);

   TCanvas Canvas_MRStar_MRTMRStar060;
   Samples[2].HMRStar_MRTMRStar060Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HMRStar_MRTMRStar060Cut->Draw("same");
   Samples[0].HMRStar_MRTMRStar060Cut->Draw("same");
   Samples[1].HMRStar_MRTMRStar060Cut->Draw("same");
   Canvas_MRStar_MRTMRStar060.SetLogy();
   PsFile.AddCanvas(Canvas_MRStar_MRTMRStar060);

   TCanvas Canvas_MRStar_MRTGammaMRStar060;
   Samples[2].HMRStar_MRTGammaMRStar060Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HMRStar_MRTGammaMRStar060Cut->Draw("same");
   Samples[0].HMRStar_MRTGammaMRStar060Cut->Draw("same");
   Samples[1].HMRStar_MRTGammaMRStar060Cut->Draw("same");
   Canvas_MRStar_MRTGammaMRStar060.SetLogy();
   PsFile.AddCanvas(Canvas_MRStar_MRTGammaMRStar060);

   TCanvas Canvas_GammaMRStar_MRTGammaMRStar060;
   Samples[2].HGammaMRStar_MRTGammaMRStar060Cut->Draw();
   for(int i = 3; i < (int)Samples.size(); i++)
      Samples[i].HGammaMRStar_MRTGammaMRStar060Cut->Draw("same");
   Samples[0].HGammaMRStar_MRTGammaMRStar060Cut->Draw("same");
   Samples[1].HGammaMRStar_MRTGammaMRStar060Cut->Draw("same");
   Canvas_GammaMRStar_MRTGammaMRStar060.SetLogy();
   PsFile.AddCanvas(Canvas_GammaMRStar_MRTGammaMRStar060);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   for(int i = 0; i < (int)Samples.size(); i++)
      Samples[i].CleanHistograms();

   return 0;
}
//---------------------------------------------------------------------------
SampleHistograms ReadSample(PsFileHelper &PsFile, string FileName, string Tag, double CrossSection)
{
   cout << "Start processing file \"" << FileName << "\" with tag \"" << Tag << "\"" << endl;

   SampleHistograms Result;
   Result.FileName = FileName;
   Result.Tag = Tag;
   Result.CrossSection = CrossSection;
   Result.AllEvents = 0;

   Result.HMR_R020Cut = new TH1D(Form("HMR_R020Cut_%s", Tag.c_str()),
      Form("MR, cut on R 0.20 (%s);MR", Tag.c_str()), 40, 0, 1500);
   Result.HMRStar_MRTMRStar020Cut = new TH1D(Form("HMRStar_MRTMRStar020Cut_%s", Tag.c_str()),
      Form("MRStar, cut on MRT/MRStar 0.20 (%s);MRStar", Tag.c_str()), 40, 0, 1500);
   Result.HMRStar_MRTGammaMRStar020Cut = new TH1D(Form("HMRStar_MRTGammaMRStar020Cut_%s", Tag.c_str()),
      Form("MRStar, cut on MRT/GammaMRStar 0.20 (%s);MRStar", Tag.c_str()), 40, 0, 1500);
   Result.HGammaMRStar_MRTGammaMRStar020Cut = new TH1D(Form("HGammaMRStar_MRTGammaMRStar020Cut_%s", Tag.c_str()),
      Form("GammaMRStar, cut on MRT/GammaMRStar 0.20 (%s);GammaMRStar", Tag.c_str()), 40, 0, 1500);
   Result.HMR_R040Cut = new TH1D(Form("HMR_R040Cut_%s", Tag.c_str()),
      Form("MR, cut on R 0.40 (%s);MR", Tag.c_str()), 40, 0, 1500);
   Result.HMRStar_MRTMRStar040Cut = new TH1D(Form("HMRStar_MRTMRStar040Cut_%s", Tag.c_str()),
      Form("MRStar, cut on MRT/MRStar 0.40 (%s);MRStar", Tag.c_str()), 40, 0, 1500);
   Result.HMRStar_MRTGammaMRStar040Cut = new TH1D(Form("HMRStar_MRTGammaMRStar040Cut_%s", Tag.c_str()),
      Form("MRStar, cut on MRT/GammaMRStar 0.40 (%s);MRStar", Tag.c_str()), 40, 0, 1500);
   Result.HGammaMRStar_MRTGammaMRStar040Cut = new TH1D(Form("HGammaMRStar_MRTGammaMRStar040Cut_%s", Tag.c_str()),
      Form("GammaMRStar, cut on MRT/GammaMRStar 0.40 (%s);GammaMRStar", Tag.c_str()), 40, 0, 1500);
   Result.HMR_R060Cut = new TH1D(Form("HMR_R060Cut_%s", Tag.c_str()),
      Form("MR, cut on R 0.60 (%s);MR", Tag.c_str()), 40, 0, 1500);
   Result.HMRStar_MRTMRStar060Cut = new TH1D(Form("HMRStar_MRTMRStar060Cut_%s", Tag.c_str()),
      Form("MRStar, cut on MRT/MRStar 0.60 (%s);MRStar", Tag.c_str()), 40, 0, 1500);
   Result.HMRStar_MRTGammaMRStar060Cut = new TH1D(Form("HMRStar_MRTGammaMRStar060Cut_%s", Tag.c_str()),
      Form("MRStar, cut on MRT/GammaMRStar 0.60 (%s);MRStar", Tag.c_str()), 40, 0, 1500);
   Result.HGammaMRStar_MRTGammaMRStar060Cut = new TH1D(Form("HGammaMRStar_MRTGammaMRStar060Cut_%s", Tag.c_str()),
      Form("GammaMRStar, cut on MRT/GammaMRStar 0.60 (%s);GammaMRStar", Tag.c_str()), 40, 0, 1500);

   TFile F(FileName.c_str());
   TTree *Tree = (TTree *)F.Get("LQ3Tree");

   if(Tree == NULL)
      return Result;

   TreeRecord M;
   M.SetBranchAddress(Tree);

   int EntryCount = Tree->GetEntries();   cout << "Number of entries = " << EntryCount << endl;
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      Tree->GetEntry(iEntry);

      Result.AllEvents = Result.AllEvents + 1;

      double CaloJetCount60 = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetPT[i] > 60 && M.CaloJetEta[i] < 3 && M.CaloJetEta[i] > -3)
            CaloJetCount60 = CaloJetCount60 + 1;
      if(CaloJetCount60 < 2)
         continue;

      int JetPassBTag = 0;
      for(int i = 0; i < M.CaloJetCount; i++)
         if(M.CaloJetTCHETag[i] > 10.2 && M.CaloJetPT[i] > 30 && M.CaloJetEta[i] < 2.4 && M.CaloJetEta[i] > -2.4)
            JetPassBTag = JetPassBTag + 1;
      if(JetPassBTag < 1)
         continue;

      if(M.GoodElectronCount >= 1)
         continue;

      if(M.GoodMuonCount >= 1)
         continue;

      vector<FourVector> CaloJets;
      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetPT[i] < 40)
            continue;
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         FourVector NewJet;
         NewJet.SetPtEtaPhi(M.CaloJetPT[i], M.CaloJetEta[i], M.CaloJetPhi[i]);
         CaloJets.push_back(NewJet);
      }
      vector<FourVector> Hemispheres = SplitIntoGroups(CaloJets, true);

      FourVector CaloMET(0, M.CaloMET[0], M.CaloMET[1], 0);
      CaloMET[0] = CaloMET.GetPT();

      double MR = GetMR(Hemispheres[0], Hemispheres[1]);
      double R = GetR(Hemispheres[0], Hemispheres[1], CaloMET);
      double Gamma = GetGammaRStar(Hemispheres[0], Hemispheres[1]);
      double MRStar = GetMRStar(Hemispheres[0], Hemispheres[1]);
      double GammaMRStar = GetMRStar(Hemispheres[0], Hemispheres[1]) * Gamma;
      double MRTMRStar = GetRStar(Hemispheres[0], Hemispheres[1], CaloMET) * Gamma;
      double MRTGammaMRStar = GetRStar(Hemispheres[0], Hemispheres[1], CaloMET);

      if(R > 0.20)
         Result.HMR_R020Cut->Fill(MR);
      if(MRTMRStar > 0.20)
         Result.HMRStar_MRTMRStar020Cut->Fill(MRStar);
      if(MRTGammaMRStar > 0.20)
         Result.HMRStar_MRTGammaMRStar020Cut->Fill(MRStar);
      if(MRTGammaMRStar > 0.20)
         Result.HGammaMRStar_MRTGammaMRStar020Cut->Fill(GammaMRStar);

      if(R > 0.40)
         Result.HMR_R040Cut->Fill(MR);
      if(MRTMRStar > 0.40)
         Result.HMRStar_MRTMRStar040Cut->Fill(MRStar);
      if(MRTGammaMRStar > 0.40)
         Result.HMRStar_MRTGammaMRStar040Cut->Fill(MRStar);
      if(MRTGammaMRStar > 0.40)
         Result.HGammaMRStar_MRTGammaMRStar040Cut->Fill(GammaMRStar);

      if(R > 0.60)
         Result.HMR_R060Cut->Fill(MR);
      if(MRTMRStar > 0.60)
         Result.HMRStar_MRTMRStar060Cut->Fill(MRStar);
      if(MRTGammaMRStar > 0.60)
         Result.HMRStar_MRTGammaMRStar060Cut->Fill(MRStar);
      if(MRTGammaMRStar > 0.60)
         Result.HGammaMRStar_MRTGammaMRStar060Cut->Fill(GammaMRStar);

      M.Clear();
   }

   PsFile.AddTextPage(Tag);

   Result.HMR_R020Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRStar_MRTMRStar020Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRStar_MRTGammaMRStar020Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HGammaMRStar_MRTGammaMRStar020Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMR_R040Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRStar_MRTMRStar040Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRStar_MRTGammaMRStar040Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HGammaMRStar_MRTGammaMRStar040Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMR_R060Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRStar_MRTMRStar060Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HMRStar_MRTGammaMRStar060Cut->Scale(CrossSection * 1000 / Result.AllEvents);
   Result.HGammaMRStar_MRTGammaMRStar060Cut->Scale(CrossSection * 1000 / Result.AllEvents);

   PsFile.AddPlot(Result.HMR_R020Cut, "", true);
   PsFile.AddPlot(Result.HMRStar_MRTMRStar020Cut, "", true);
   PsFile.AddPlot(Result.HMRStar_MRTGammaMRStar020Cut, "", true);
   PsFile.AddPlot(Result.HGammaMRStar_MRTGammaMRStar020Cut, "", true);
   PsFile.AddPlot(Result.HMR_R040Cut, "", true);
   PsFile.AddPlot(Result.HMRStar_MRTMRStar040Cut, "", true);
   PsFile.AddPlot(Result.HMRStar_MRTGammaMRStar040Cut, "", true);
   PsFile.AddPlot(Result.HGammaMRStar_MRTGammaMRStar040Cut, "", true);
   PsFile.AddPlot(Result.HMR_R060Cut, "", true);
   PsFile.AddPlot(Result.HMRStar_MRTMRStar060Cut, "", true);
   PsFile.AddPlot(Result.HMRStar_MRTGammaMRStar060Cut, "", true);
   PsFile.AddPlot(Result.HGammaMRStar_MRTGammaMRStar060Cut, "", true);

   return Result;
}
//---------------------------------------------------------------------------



