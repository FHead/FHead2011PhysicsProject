#include <string>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"

#include "PlotHelper.h"

struct TreeVariables;
void ProducePlotsBackground(string InputFile = "SFile.root");
void SetAddresses(TTree *Tree, TreeVariables &M);
void PrintOverlaidHistogram(TH1D *H[5], PsFileHelper &PsFile, bool LogY = false);

struct TreeVariables
{
   double Z_mass;
   double Npf_30;
   double firstJet_pt;
   double secondJet_pt;
   double muPt;
   double mu2Pt;
   double muEta;
   double mu2Eta;
   double Z_pt;
   double Z_eta;
   double Z_phi;
   double Dxy;
   double Dz;
   double Iso_pf_relpt;
   double BackgroundJetYield_sw[5];
};

void ProducePlotsBackground(string InputFile)
{
   TFile F(InputFile.c_str());

   // read tree, set branch address
   TTree *Tree = (TTree *)F.Get("SWeightTree");
   if(Tree == NULL)
      return;

   TreeVariables M;
   SetAddresses(Tree, M);

   // make histograms
   TH1D *HZMass[5];
   TH1D *HJet1PT[5];
   TH1D *HJet2PT[5];
   TH1D *HMu1PT[5];
   TH1D *HMu2PT[5];
   TH1D *HMu1Eta[5];
   TH1D *HMu2Eta[5];
   TH1D *HZPT[5];
   TH1D *HZEta[5];
   TH1D *HZPhi[5];
   TH1D *HDxy[5];
   TH1D *HDz[5];
   TH1D *HIsolation[5];

   for(int i = 0; i < 5; i++)
   {
      HZMass[i] = new TH1D(Form("HZMass%d", i), "Z Mass;Mass", 30, 60, 120);
      HJet1PT[i] = new TH1D(Form("HJet1PT%d", i), "Jet 1 PT;PT", 30, 0, 400);
      HJet2PT[i] = new TH1D(Form("HJet2PT%d", i), "Jet 2 PT;PT", 30, 0, 200);
      HMu1PT[i] = new TH1D(Form("HMu1PT%d", i), "Mu 1 PT;PT", 30, 0, 300);
      HMu2PT[i] = new TH1D(Form("HMu2PT%d", i), "Mu 2 PT;PT", 30, 0, 200);
      HMu1Eta[i] = new TH1D(Form("HMu1Eta%d", i), "Mu 1 Eta;Eta", 30, -3, 3);
      HMu2Eta[i] = new TH1D(Form("HMu2Eta%d", i), "Mu 2 Eta;Eta", 30, -3, 3);
      HZPT[i] = new TH1D(Form("HZPT%d", i), "Z PT;PT", 30, 0, 400);
      HZEta[i] = new TH1D(Form("HZEta%d", i), "Z Eta;Eta", 30, -8, 8);
      HZPhi[i] = new TH1D(Form("HZPhi%d", i), "Z Phi;Phi", 30, -3.5, 3.5);
      HDxy[i] = new TH1D(Form("HDxy%d", i), "Dxy;Dxy", 80, -0.1, 0.1);
      HDz[i] = new TH1D(Form("HDz%d", i), "Dz;Dz", 80, -1, 1);
      HIsolation[i] = new TH1D(Form("HIsolation%d", i), "Relative PF Isolation;Isolation", 30, 0, 1);
   }

   // output file
   PsFileHelper PsFile("SPlotsBackground.ps");
   PsFile.AddTextPage("(First) attempt at s-plot on data");

   vector<string> Explanation;
   Explanation.push_back("Starting from dataset by Will & Sara on Jan 17, 2011");
   Explanation.push_back("30 GeV, weighted dataset, no unfolding");
   Explanation.push_back("Extended unconstrained fit (including 0-jet bin with different shape)");
   Explanation.push_back("All of the plots here are with background weights");
   PsFile.AddTextPage(Explanation);

   // loop!
   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      for(int j = 0; j < 5; j++)
      {
         HZMass[j]->Fill(M.Z_mass, M.BackgroundJetYield_sw[j]);
         HJet1PT[j]->Fill(M.firstJet_pt, M.BackgroundJetYield_sw[j]);
         HJet2PT[j]->Fill(M.secondJet_pt, M.BackgroundJetYield_sw[j]);
         HMu1PT[j]->Fill(M.muPt, M.BackgroundJetYield_sw[j]);
         HMu2PT[j]->Fill(M.mu2Pt, M.BackgroundJetYield_sw[j]);
         HMu1Eta[j]->Fill(M.muEta, M.BackgroundJetYield_sw[j]);
         HMu2Eta[j]->Fill(M.mu2Eta, M.BackgroundJetYield_sw[j]);
         HZPT[j]->Fill(M.Z_pt, M.BackgroundJetYield_sw[j]);
         HZEta[j]->Fill(M.Z_eta, M.BackgroundJetYield_sw[j]);
         HZPhi[j]->Fill(M.Z_phi, M.BackgroundJetYield_sw[j]);
         HDxy[j]->Fill(M.Dxy, M.BackgroundJetYield_sw[j]);
         HDz[j]->Fill(M.Dz, M.BackgroundJetYield_sw[j]);
         HIsolation[j]->Fill(M.Iso_pf_relpt, M.BackgroundJetYield_sw[j]);
      }
   }

   // print histograms
   PrintOverlaidHistogram(HZMass, PsFile, false);
   // PrintOverlaidHistogram(HZMass, PsFile, true);
   PrintOverlaidHistogram(HJet1PT, PsFile, false);
   // PrintOverlaidHistogram(HJet1PT, PsFile, true);
   PrintOverlaidHistogram(HJet2PT, PsFile, false);
   // PrintOverlaidHistogram(HJet2PT, PsFile, true);
   PrintOverlaidHistogram(HMu1PT, PsFile, false);
   // PrintOverlaidHistogram(HMu1PT, PsFile, true);
   PrintOverlaidHistogram(HMu2PT, PsFile, false);
   // PrintOverlaidHistogram(HMu2PT, PsFile, true);
   PrintOverlaidHistogram(HMu1Eta, PsFile, false);
   // PrintOverlaidHistogram(HMu1Eta, PsFile, true);
   PrintOverlaidHistogram(HMu2Eta, PsFile, false);
   // PrintOverlaidHistogram(HMu2Eta, PsFile, true);
   PrintOverlaidHistogram(HZPT, PsFile, false);
   // PrintOverlaidHistogram(HZPT, PsFile, true);
   PrintOverlaidHistogram(HZEta, PsFile, false);
   // PrintOverlaidHistogram(HZEta, PsFile, true);
   PrintOverlaidHistogram(HZPhi, PsFile, false);
   // PrintOverlaidHistogram(HZPhi, PsFile, true);
   PrintOverlaidHistogram(HDxy, PsFile, false);
   // PrintOverlaidHistogram(HDxy, PsFile, true);
   PrintOverlaidHistogram(HDz, PsFile, false);
   // PrintOverlaidHistogram(HDz, PsFile, true);
   PrintOverlaidHistogram(HIsolation, PsFile, false);
   // PrintOverlaidHistogram(HIsolation, PsFile, true);

   // close output file
   PsFile.AddTimeStampPage();
   PsFile.Close();

   // delete histograms
   for(int i = 0; i < 5; i++)
   {
      delete HZMass[i];
      delete HJet1PT[i];
      delete HJet2PT[i];
      delete HMu1PT[i];
      delete HMu2PT[i];
      delete HMu1Eta[i];
      delete HMu2Eta[i];
      delete HZPT[i];
      delete HZEta[i];
      delete HZPhi[i];
      delete HDxy[i];
      delete HDz[i];
      delete HIsolation[i];
   }

   F.Close();
}

void SetAddresses(TTree *Tree, TreeVariables &M)
{
   if(Tree == NULL)
      return;

   Tree->SetBranchAddress("Z_mass", &M.Z_mass);
   Tree->SetBranchAddress("Npf_30", &M.Npf_30);
   Tree->SetBranchAddress("firstJet_pt", &M.firstJet_pt);
   Tree->SetBranchAddress("secondJet_pt", &M.secondJet_pt);
   Tree->SetBranchAddress("muPt", &M.muPt);
   Tree->SetBranchAddress("mu2Pt", &M.mu2Pt);
   Tree->SetBranchAddress("muEta", &M.muEta);
   Tree->SetBranchAddress("mu2Eta", &M.mu2Eta);
   Tree->SetBranchAddress("Z_pt", &M.Z_pt);
   Tree->SetBranchAddress("Z_eta", &M.Z_eta);
   Tree->SetBranchAddress("Z_phi", &M.Z_phi);
   Tree->SetBranchAddress("Dxy", &M.Dxy);
   Tree->SetBranchAddress("Dz", &M.Dz);
   Tree->SetBranchAddress("Iso_pf_relpt", &M.Iso_pf_relpt);
   Tree->SetBranchAddress("Background0JetYield_sw", &M.BackgroundJetYield_sw[0]);
   Tree->SetBranchAddress("Background1JetYield_sw", &M.BackgroundJetYield_sw[1]);
   Tree->SetBranchAddress("Background2JetYield_sw", &M.BackgroundJetYield_sw[2]);
   Tree->SetBranchAddress("Background3JetYield_sw", &M.BackgroundJetYield_sw[3]);
   Tree->SetBranchAddress("Background4JetYield_sw", &M.BackgroundJetYield_sw[4]);
}

void PrintOverlaidHistogram(TH1D *H[5], PsFileHelper &PsFile, bool LogY)
{
   TCanvas C("C", "C", 1024, 768);

   string Option = "";

   TLegend legend(0.8, 0.95, 0.95, 0.75);

   double Maximum = 0;
   for(int i = 0; i < 5; i++)
      if(Maximum < H[i]->GetMaximum())
         Maximum = H[i]->GetMaximum();;

   for(int i = 0; i < 5; i++)
   {
      bool HasSomething = false;
      if(H[i]->GetMaximum() != 0)
         HasSomething = true;
      H[i]->SetMaximum(Maximum);
      H[i]->SetStats(0);
      H[i]->SetLineWidth(2);
      H[i]->SetLineColor(i + 1);
      H[i]->Draw(Option.c_str());
      if(HasSomething == true)
         Option = "same";
      if(LogY == true)
         H[i]->SetMinimum(0.1);

      legend.AddEntry(H[i], Form("== %d Jets", i), "l");
   }

   legend.SetFillColor(0);
   legend.Draw();

   if(LogY == true)
      C.SetLogy();

   PsFile.AddCanvas(C);
}



