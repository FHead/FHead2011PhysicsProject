#include <string>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TLegend.h"

#include "PlotHelper.h"

struct TreeVariables;
void ProducePlots(string InputFile = "SFile.root");
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
   double SignalInclusiveYieldJet_sw[5];
   double W;
};

void ProducePlots(string InputFile)
{
   TFile F(InputFile.c_str());

   // read tree, set branch address
   TTree *Tree = (TTree *)F.Get("SWeightTree");
   if(Tree == NULL)
      return;

   TreeVariables M;
   SetAddresses(Tree, M);

   // make histograms
   TFile OutputFile("SPlotHistograms.root", "RECREATE");
   TH1D *HZMassOriginal[5];
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
      HZMassOriginal[i] = new TH1D(Form("HZMassOriginal_%d", i), "Z Mass (without s-weight);Mass", 30, 60, 120);
      HZMass[i] = new TH1D(Form("HZMass_%d", i), "Z Mass (with s-weight);Mass", 30, 60, 120);
      HJet1PT[i] = new TH1D(Form("HJet1PT_%d", i), "Jet 1 PT;PT", 60, 0, 360);
      HJet2PT[i] = new TH1D(Form("HJet2PT_%d", i), "Jet 2 PT;PT", 40, 0, 240);
      HMu1PT[i] = new TH1D(Form("HMu1PT_%d", i), "Mu 1 PT;PT", 50, 0, 300);
      HMu2PT[i] = new TH1D(Form("HMu2PT_%d", i), "Mu 2 PT;PT", 40, 0, 240);
      HMu1Eta[i] = new TH1D(Form("HMu1Eta_%d", i), "Mu 1 Eta;Eta", 30, -3, 3);
      HMu2Eta[i] = new TH1D(Form("HMu2Eta_%d", i), "Mu 2 Eta;Eta", 30, -3, 3);
      HZPT[i] = new TH1D(Form("HZPT_%d", i), "Z PT;PT", 60, 0, 360);
      HZEta[i] = new TH1D(Form("HZEta_%d", i), "Z Eta;Eta", 30, -8, 8);
      HZPhi[i] = new TH1D(Form("HZPhi_%d", i), "Z Phi;Phi", 30, -3.5, 3.5);
      HDxy[i] = new TH1D(Form("HDxy_%d", i), "Dxy;Dxy", 80, -0.1, 0.1);
      HDz[i] = new TH1D(Form("HDz_%d", i), "Dz;Dz", 80, -1, 1);
      HIsolation[i] = new TH1D(Form("HIsolation_%d", i), "Relative PF Isolation;Isolation", 30, 0, 1);
   }

   for(int i = 0; i < 5; i++)
   {
      HZMassOriginal[i]->Sumw2();
      HZMass[i]->Sumw2();
      HJet1PT[i]->Sumw2();
      HJet2PT[i]->Sumw2();
      HMu1PT[i]->Sumw2();
      HMu2PT[i]->Sumw2();
      HMu1Eta[i]->Sumw2();
      HMu2Eta[i]->Sumw2();
      HZPT[i]->Sumw2();
      HZEta[i]->Sumw2();
      HZPhi[i]->Sumw2();
      HDxy[i]->Sumw2();
      HDz[i]->Sumw2();
      HIsolation[i]->Sumw2();
   }

   // output file
   PsFileHelper PsFile("SPlots.ps");
   PsFile.AddTextPage("(First) attempt at s-plot on data");

   vector<string> Explanation;
   Explanation.push_back("Starting from dataset by Will & Sara on Jan 17, 2011");
   Explanation.push_back("30 GeV, weighted dataset, no unfolding");
   Explanation.push_back("Extended unconstrained fit (including 0-jet bin with different shape)");
   Explanation.push_back("All of the plots here are with signal weights");
   Explanation.push_back("s-weights are calculated with RooStats package");
   Explanation.push_back("");
   Explanation.push_back("Z Mass without s-weight uses number of jets while filling histogram");
   Explanation.push_back("Z Mass with s-weight doesn't use number of jets");
   Explanation.push_back("      only the weight is applied");
   PsFile.AddTextPage(Explanation);

   // loop!
   int EntryCount = Tree->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      Tree->GetEntry(i);

      for(int j = 0; j < 5; j++)
      {
         if(j <= M.Npf_30)
            HZMassOriginal[j]->Fill(M.Z_mass, M.W);
         HZMass[j]->Fill(M.Z_mass, M.SignalInclusiveYieldJet_sw[j]);
         HJet1PT[j]->Fill(M.firstJet_pt, M.SignalInclusiveYieldJet_sw[j]);
         HJet2PT[j]->Fill(M.secondJet_pt, M.SignalInclusiveYieldJet_sw[j]);
         HMu1PT[j]->Fill(M.muPt, M.SignalInclusiveYieldJet_sw[j]);
         HMu2PT[j]->Fill(M.mu2Pt, M.SignalInclusiveYieldJet_sw[j]);
         HMu1Eta[j]->Fill(M.muEta, M.SignalInclusiveYieldJet_sw[j]);
         HMu2Eta[j]->Fill(M.mu2Eta, M.SignalInclusiveYieldJet_sw[j]);
         HZPT[j]->Fill(M.Z_pt, M.SignalInclusiveYieldJet_sw[j]);
         HZEta[j]->Fill(M.Z_eta, M.SignalInclusiveYieldJet_sw[j]);
         HZPhi[j]->Fill(M.Z_phi, M.SignalInclusiveYieldJet_sw[j]);
         HDxy[j]->Fill(M.Dxy, M.SignalInclusiveYieldJet_sw[j]);
         HDz[j]->Fill(M.Dz, M.SignalInclusiveYieldJet_sw[j]);
         HIsolation[j]->Fill(M.Iso_pf_relpt, M.SignalInclusiveYieldJet_sw[j]);
      }
   }

   HZMassOriginal[0]->SetMaximum(4550);
   HZMass[0]->SetMaximum(4550);
   HZMassOriginal[0]->SetMinimum(0);
   HZMass[0]->SetMinimum(0);

   // print histograms
   PrintOverlaidHistogram(HZMassOriginal, PsFile, false);
   PrintOverlaidHistogram(HZMass, PsFile, false);
   PrintOverlaidHistogram(HZMass, PsFile, true);
   PrintOverlaidHistogram(HJet1PT, PsFile, false);
   PrintOverlaidHistogram(HJet1PT, PsFile, true);
   PrintOverlaidHistogram(HJet2PT, PsFile, false);
   PrintOverlaidHistogram(HJet2PT, PsFile, true);
   PrintOverlaidHistogram(HMu1PT, PsFile, false);
   PrintOverlaidHistogram(HMu1PT, PsFile, true);
   PrintOverlaidHistogram(HMu2PT, PsFile, false);
   PrintOverlaidHistogram(HMu2PT, PsFile, true);
   PrintOverlaidHistogram(HMu1Eta, PsFile, false);
   PrintOverlaidHistogram(HMu1Eta, PsFile, true);
   PrintOverlaidHistogram(HMu2Eta, PsFile, false);
   PrintOverlaidHistogram(HMu2Eta, PsFile, true);
   PrintOverlaidHistogram(HZPT, PsFile, false);
   PrintOverlaidHistogram(HZPT, PsFile, true);
   PrintOverlaidHistogram(HZEta, PsFile, false);
   PrintOverlaidHistogram(HZEta, PsFile, true);
   PrintOverlaidHistogram(HZPhi, PsFile, false);
   PrintOverlaidHistogram(HZPhi, PsFile, true);
   PrintOverlaidHistogram(HDxy, PsFile, false);
   PrintOverlaidHistogram(HDxy, PsFile, true);
   PrintOverlaidHistogram(HDz, PsFile, false);
   PrintOverlaidHistogram(HDz, PsFile, true);
   PrintOverlaidHistogram(HIsolation, PsFile, false);
   PrintOverlaidHistogram(HIsolation, PsFile, true);

   // write histograms to file
   for(int i = 0; i < 5; i++)
   {
      // HZMassOriginal[i]->Write();
      HZMass[i]->Write();
      HJet1PT[i]->Write();
      HJet2PT[i]->Write();
      HMu1PT[i]->Write();
      HMu2PT[i]->Write();
      HMu1Eta[i]->Write();
      HMu2Eta[i]->Write();
      HZPT[i]->Write();
      HZEta[i]->Write();
      HZPhi[i]->Write();
      HDxy[i]->Write();
      HDz[i]->Write();
      HIsolation[i]->Write();
   }
   
   // close output file
   PsFile.AddTimeStampPage();
   PsFile.Close();
   
   // delete histograms
   for(int i = 0; i < 5; i++)
   {
      delete HZMassOriginal[i];
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

   OutputFile.Close();

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
   Tree->SetBranchAddress("SignalInclusiveYield0Jet_sw", &M.SignalInclusiveYieldJet_sw[0]);
   Tree->SetBranchAddress("SignalInclusiveYield1Jet_sw", &M.SignalInclusiveYieldJet_sw[1]);
   Tree->SetBranchAddress("SignalInclusiveYield2Jet_sw", &M.SignalInclusiveYieldJet_sw[2]);
   Tree->SetBranchAddress("SignalInclusiveYield3Jet_sw", &M.SignalInclusiveYieldJet_sw[3]);
   Tree->SetBranchAddress("SignalInclusiveYield4Jet_sw", &M.SignalInclusiveYieldJet_sw[4]);
   Tree->SetBranchAddress("W", &M.W);
}

void PrintOverlaidHistogram(TH1D *H[5], PsFileHelper &PsFile, bool LogY)
{
   TCanvas C("C", "C", 1024, 768);

   string Option = "hist error";

   TLegend legend(0.8, 0.95, 0.95, 0.75);

   int Colors[] = {1, 2, 3, 4, 6};

   for(int i = 0; i < 5; i++)
   {
      H[i]->SetStats(0);
      H[i]->SetLineWidth(2);
      H[i]->SetLineColor(Colors[i]);
      if(LogY == true)
         H[i]->SetMinimum(0.1);
      // else
      //    H[i]->SetMinimum(0);
      H[i]->Draw(Option.c_str());
      if(H[i]->GetMaximum() != 0)
         Option = "same hist error";

      legend.AddEntry(H[i], Form(">= %d Jets", i), "l");
   }

   legend.SetFillColor(0);
   legend.Draw();

   if(LogY == true)
      C.SetLogy();

   PsFile.AddCanvas(C);
}



