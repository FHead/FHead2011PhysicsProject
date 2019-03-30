#include <iostream>
#include <vector>
using namespace std;

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
using namespace fastjet;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper4.h"
#include "Code/TauHelperFunctions3.h"
#include "ProgressBar.h"

#include "CommandLine.h"

#define MAXJET 10000
#define MAXD0 10000

int main(int argc, char *argv[])
{
   SetThesisStyle();

   ClusterSequence::set_fastjet_banner_stream(NULL);

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputBase = CL.Get("OutputBase", "QPythia");
   double Percentage = CL.GetDouble("Percentage", 1.0);
   double JetPTMin = CL.GetDouble("JetPTMin", 30);
   double JetEtaMin = CL.GetDouble("JetEtaMin", -4.0);
   double JetEtaMax = CL.GetDouble("JetEtaMax", +4.0);

   TFile OutputFile((OutputBase + ".root").c_str(), "RECREATE");

   PdfFileHelper PdfFile(OutputBase + ".pdf");
   PdfFile.AddTextPage("QPythia plots");

   TH1D HN("HN", ";;", 2, 0, 2);
   TH1D HPiPlusCount("HPiPlusCount", "pi+ count", 50, 0, 50);
   TH1D HPiMinusCount("HPiMinusCount", "pi- count", 50, 0, 50);
   TH1D HKPlusCount("HKPlusCount", "K+ count", 30, 0, 30);
   TH1D HKMinusCount("HKMinusCount", "K- count", 30, 0, 30);
   TH1D HD0Count("HD0Count", "D0 count", 100, 0, 100);
   TH1D HD0barCount("HD0barCount", "D0bar count", 100, 0, 100);
   TH1D HD0Mass("HD0Mass", "D0 Mass", 100, 1.862, 1.868);
   TH1D HD0barMass("HD0barMass", "D0bar Mass", 100, 1.862, 1.868);
   TH1D HMass0("HMass0", "D0 & D0bar Mass", 100, 1.862, 1.868);
   TH1D HMass1("HMass1", "D0 & D0bar Mass", 100, 1.8638, 1.865);
   TH1D HMass2("HMass2", "D0 & D0bar Mass", 100, 1.8644, 1.8646);
   TH1D HMass3("HMass3", "D0 & D0bar Mass;M_{K#pi} - 1.8645 (GeV)", 100, -0.0001, 0.0001);
   TH1D HMass4("HMass4", "D0 & D0bar Mass;M_{K#pi} - 1.8645 (GeV)", 100, -0.00002, 0.00002);
   TH1D HMass5("HMass5", "D0 & D0bar Mass;M_{K#pi} - 1.8645 (GeV)", 100, -0.000002, 0.000002);
   TH1D HD0CandidateCount("HD0CandidateCount", "D0 candidate count", 5, 0, 5);

   TTree OutputTree("Tree", "Tree");

   double TreeWeight, TreePTHat;
   int TreeJetCount;
   double TreeJetPT[MAXJET], TreeJetEta[MAXJET], TreeJetPhi[MAXJET];
   int TreeD0Count;
   double TreeD0M[MAXD0], TreeD0PT[MAXD0], TreeD0Eta[MAXD0], TreeD0Phi[MAXD0];
   double TreeKPT[MAXD0], TreeKEta[MAXD0], TreeKPhi[MAXD0];
   double TreePiPT[MAXD0], TreePiEta[MAXD0], TreePiPhi[MAXD0];

   OutputTree.Branch("Weight", &TreeWeight, "Weight/D");
   OutputTree.Branch("PTHat", &TreePTHat, "PTHat/D");
   OutputTree.Branch("JetCount", &TreeJetCount, "JetCount/I");
   OutputTree.Branch("JetPT", &TreeJetPT, "JetPT[JetCount]/D");
   OutputTree.Branch("JetEta", &TreeJetEta, "JetEta[JetCount]/D");
   OutputTree.Branch("JetPhi", &TreeJetPhi, "JetPhi[JetCount]/D");
   OutputTree.Branch("D0Count", &TreeD0Count, "D0Count/I");
   OutputTree.Branch("D0M", &TreeD0M, "D0M[D0Count]/D");
   OutputTree.Branch("D0PT", &TreeD0PT, "D0PT[D0Count]/D");
   OutputTree.Branch("D0Eta", &TreeD0Eta, "D0Eta[D0Count]/D");
   OutputTree.Branch("D0Phi", &TreeD0Phi, "D0Phi[D0Count]/D");
   OutputTree.Branch("KPT", &TreeKPT, "KPT[D0Count]/D");
   OutputTree.Branch("KEta", &TreeKEta, "KEta[D0Count]/D");
   OutputTree.Branch("KPhi", &TreeKPhi, "KPhi[D0Count]/D");
   OutputTree.Branch("PiPT", &TreePiPT, "PiPT[D0Count]/D");
   OutputTree.Branch("PiEta", &TreePiEta, "PiEta[D0Count]/D");
   OutputTree.Branch("PiPhi", &TreePiPhi, "PiPhi[D0Count]/D");

   for(string FileName : InputFileNames)
   {
      cout << "Begin processing file " << FileName << endl;
      TFile File(FileName.c_str());

      TTree *Tree = (TTree *)File.Get("Tdata");
      if(Tree == nullptr)
      {
         cout << "Tree not found for file " << FileName << endl;
         File.Close();
         continue;
      }

      vector<double> *Px = nullptr;
      vector<double> *Py = nullptr;
      vector<double> *Pz = nullptr;
      vector<double> *E = nullptr;
      vector<int> *ID = nullptr;
      double CrossSection;
      double Weight;

      Tree->SetBranchAddress("px", &Px);
      Tree->SetBranchAddress("py", &Py);
      Tree->SetBranchAddress("pz", &Pz);
      Tree->SetBranchAddress("En", &E);
      Tree->SetBranchAddress("id", &ID);
      Tree->SetBranchAddress("xSec", &CrossSection);
      Tree->SetBranchAddress("weight", &Weight);

      int EntryCount = Tree->GetEntries() * Percentage;
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         if(EntryCount < 500 || (iE % (EntryCount / 250) == 0))
            Bar.Print();

         Tree->GetEntry(iE);

         Weight = CrossSection;

         HN.Fill(0);
         HN.Fill(1, Weight);

         TreeWeight = Weight;
         TreePTHat = -1;

         int ParticleCount = E->size();

         vector<FourVector> P;
         for(int iP = 0; iP < ParticleCount; iP++)
         {
            double PT2 = (*Px)[iP] * (*Px)[iP] + (*Py)[iP] * (*Py)[iP];
            if(PT2 < 2 * 2)
               continue;
            P.push_back(FourVector((*E)[iP], (*Px)[iP], (*Py)[iP], (*Pz)[iP]));
         }

         vector<FourVector> PiPlus;
         vector<FourVector> PiMinus;
         vector<FourVector> KPlus;
         vector<FourVector> KMinus;

         for(int iP = 0; iP < (int)P.size(); iP++)
         {
            if(P[iP].GetEta() > 2 || P[iP].GetEta() < -2)
               continue;
            if(P[iP].GetPT() < 2)
               continue;

            if((*ID)[iP] == 211)       PiPlus.push_back(P[iP]);
            if((*ID)[iP] == -211)      PiMinus.push_back(P[iP]);
            if((*ID)[iP] == 321)       KPlus.push_back(P[iP]);
            if((*ID)[iP] == -321)      KMinus.push_back(P[iP]);
         }

         HPiPlusCount.Fill(PiPlus.size());
         HPiMinusCount.Fill(PiMinus.size());
         HKPlusCount.Fill(KPlus.size());
         HKMinusCount.Fill(KMinus.size());

         vector<FourVector> D0;
         vector<FourVector> D0bar;

         TreeD0Count = 0;

         for(int iPi = 0; iPi < (int)PiPlus.size(); iPi++)
         {
            for(int iK = 0; iK < (int)KMinus.size(); iK++)
            {
               FourVector PD0 = PiPlus[iPi] + KMinus[iK];
               if(PD0.GetPT() < 4)
                  continue;
               if(PD0.GetRapidity() < -2 || PD0.GetRapidity() > 2)
                  continue;

               D0.push_back(PD0);

               HD0Mass.Fill(PD0.GetMass());
               HMass0.Fill(PD0.GetMass());
               HMass1.Fill(PD0.GetMass());
               HMass2.Fill(PD0.GetMass());
               HMass3.Fill(PD0.GetMass() - 1.8645);
               HMass4.Fill(PD0.GetMass() - 1.8645);
               HMass5.Fill(PD0.GetMass() - 1.8645);

               if(PD0.GetMass() - 1.8645 > -1e-6 && PD0.GetMass() - 1.8645 < 1e-6)
               {
                  TreeD0M[TreeD0Count]   = PD0.GetMass();
                  TreeD0PT[TreeD0Count]  = PD0.GetPT();
                  TreeD0Eta[TreeD0Count] = PD0.GetEta();
                  TreeD0Phi[TreeD0Count] = PD0.GetPhi();
                  TreeKPT[TreeD0Count]   = KMinus[iK].GetPT();
                  TreeKEta[TreeD0Count]  = KMinus[iK].GetEta();
                  TreeKPhi[TreeD0Count]  = KMinus[iK].GetPhi();
                  TreePiPT[TreeD0Count]  = PiPlus[iPi].GetPT();
                  TreePiEta[TreeD0Count] = PiPlus[iPi].GetEta();
                  TreePiPhi[TreeD0Count] = PiPlus[iPi].GetPhi();
                  TreeD0Count = TreeD0Count + 1;
               }
            }
         }

         for(int iPi = 0; iPi < (int)PiMinus.size(); iPi++)
         {
            for(int iK = 0; iK < (int)KPlus.size(); iK++)
            {
               FourVector PD0 = PiMinus[iPi] + KPlus[iK];
               if(PD0.GetPT() < 4)
                  continue;
               if(PD0.GetRapidity() < -2 || PD0.GetRapidity() > 2)
                  continue;

               D0bar.push_back(PD0);

               HD0barMass.Fill(PD0.GetMass());
               HMass0.Fill(PD0.GetMass());
               HMass1.Fill(PD0.GetMass());
               HMass2.Fill(PD0.GetMass());
               HMass3.Fill(PD0.GetMass() - 1.8645);
               HMass4.Fill(PD0.GetMass() - 1.8645);
               HMass5.Fill(PD0.GetMass() - 1.8645);
               
               if(PD0.GetMass() - 1.8645 > -1e-6 && PD0.GetMass() - 1.8645 < 1e-6)
               {
                  TreeD0M[TreeD0Count]   = PD0.GetMass();
                  TreeD0PT[TreeD0Count]  = PD0.GetPT();
                  TreeD0Eta[TreeD0Count] = PD0.GetEta();
                  TreeD0Phi[TreeD0Count] = PD0.GetPhi();
                  TreeKPT[TreeD0Count]   = KPlus[iK].GetPT();
                  TreeKEta[TreeD0Count]  = KPlus[iK].GetEta();
                  TreeKPhi[TreeD0Count]  = KPlus[iK].GetPhi();
                  TreePiPT[TreeD0Count]  = PiMinus[iPi].GetPT();
                  TreePiEta[TreeD0Count] = PiMinus[iPi].GetEta();
                  TreePiPhi[TreeD0Count] = PiMinus[iPi].GetPhi();
                  TreeD0Count = TreeD0Count + 1;
               }
            }
         }

         HD0Count.Fill(D0.size());
         HD0barCount.Fill(D0bar.size());

         if(TreeD0Count == 0)
            continue;

         vector<PseudoJet> Particles;
         for(int iP = 0; iP < ParticleCount; iP++)
         {
            if((*ID)[iP] == 12 || (*ID)[iP] == -12)
               continue;
            if((*ID)[iP] == 14 || (*ID)[iP] == -16)
               continue;
            if((*ID)[iP] == 14 || (*ID)[iP] == -16)
               continue;

            FourVector P((*E)[iP], (*Px)[iP], (*Py)[iP], (*Pz)[iP]);
            Particles.push_back(PseudoJet(P[1], P[2], P[3], P[0]));
         }
         JetDefinition Definition(antikt_algorithm, 0.3);
         ClusterSequence Sequence(Particles, Definition);
         vector<PseudoJet> FastJets = Sequence.inclusive_jets();
         
         vector<FourVector> Jets;
         for(PseudoJet J : FastJets)
         {
            if(J.eta() < -3 && J.eta() > 3)
               continue;

            Jets.push_back(FourVector(J.e(), J.px(), J.py(), J.pz()));
         }

         TreeJetCount = 0;
         for(int iJ = 0; iJ < (int)Jets.size(); iJ++)
         {
            if(Jets[iJ].GetPT() > JetPTMin && Jets[iJ].GetEta() > JetEtaMin && Jets[iJ].GetEta() < JetEtaMax)
            {
               TreeJetPT[TreeJetCount] = Jets[iJ].GetPT();
               TreeJetEta[TreeJetCount] = Jets[iJ].GetEta();
               TreeJetPhi[TreeJetCount] = Jets[iJ].GetPhi();
               TreeJetCount = TreeJetCount + 1;
            }
         }

         OutputTree.Fill();
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   PdfFile.AddPlot(HPiPlusCount, "", true);
   PdfFile.AddPlot(HPiMinusCount, "", true);
   PdfFile.AddPlot(HKPlusCount, "", true);
   PdfFile.AddPlot(HKMinusCount, "", true);
   PdfFile.AddPlot(HD0Count, "", true);
   PdfFile.AddPlot(HD0barCount, "", true);
   PdfFile.AddPlot(HD0Mass, "", true);
   PdfFile.AddPlot(HD0barMass, "", true);
   PdfFile.AddPlot(HMass0, "", true);
   PdfFile.AddPlot(HMass1, "", true);
   PdfFile.AddPlot(HMass2, "", true);
   PdfFile.AddPlot(HMass3, "", true);
   PdfFile.AddPlot(HMass4, "", true);
   PdfFile.AddPlot(HMass5, "", true);

   OutputFile.cd();
   
   HN.Write();
   HPiPlusCount.Write();
   HPiMinusCount.Write();
   HKPlusCount.Write();
   HKMinusCount.Write();
   HD0Count.Write();
   HD0barCount.Write();
   HD0Mass.Write();
   HD0barMass.Write();
   HMass0.Write();
   HMass1.Write();
   HMass2.Write();
   HMass3.Write();
   HMass4.Write();
   HMass5.Write();

   OutputTree.Write();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



