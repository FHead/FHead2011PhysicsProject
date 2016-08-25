#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Pythia8/Pythia.h"
using namespace Pythia8;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TH1D.h"
#include "TH2D.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TTree.h"
#include "TEllipse.h"
#include "TLegend.h"
#include "TGraph.h"

#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "GenparticleTree2.h"
#include "SetStyle.h"

class Node;
int main(int argc, char *argv[]);
void NormalizeHistogram(TH1D &H);

class Node
{
public:
   FourVector P;
   Node *Child1;
   Node *Child2;
   int N;   // multiplicity: how many nodes (including self) under this node
public:
   Node() : P(0, 0, 0, 0), Child1(NULL), Child2(NULL), N(1) {}
   Node(FourVector &p) : P(p), Child1(NULL), Child2(NULL), N(1) {}
   Node(Node *n1, Node *n2) : P(0, 0, 0, 0), Child1(NULL), Child2(NULL), N(1)
   {
      if(n1 == NULL || n2 == NULL)
         return;

      P = n1->P + n2->P;
      Child1 = n1;
      Child2 = n2;
      N = n1->N + n2->N + 1;
   }
   ~Node()
   {
      if(Child1 != NULL)   delete Child1;
      if(Child2 != NULL)   delete Child2;

      Child1 = NULL;
      Child2 = NULL;
   }
};

int main(int argc, char *argv[])
{
   SetThesisStyle();

   TH1D HPT("HPT", "Jet PT;PT", 100, 0, 500);
   TH1D HPTRatio("HPTRatio", "PT Groomed / Original;PT Ratio", 100, 0.5, 1.0);
   TH1D HNDropped("HNDropped", "Dropped Branches;N_{dropped}", 12, 0, 12);
   TH1D HZG120("HZG120", "Z_{g} (PT = 120-140);Z_{g}", 10, 0, 0.5);
   TH1D HZG140("HZG140", "Z_{g} (PT = 140-160);Z_{g}", 10, 0, 0.5);
   TH1D HZG160("HZG160", "Z_{g} (PT = 160-180);Z_{g}", 10, 0, 0.5);
   TH1D HZG180("HZG180", "Z_{g} (PT = 180-200);Z_{g}", 10, 0, 0.5);
   TH1D HMassRatio120("HMassRatio120", "Mass Groomed / original (PT = 120-140);Mass Ratio", 100, 0, 1);
   TH1D HMassRatio140("HMassRatio140", "Mass Groomed / original (PT = 140-160);Mass Ratio", 100, 0, 1);
   TH1D HMassRatio160("HMassRatio160", "Mass Groomed / original (PT = 160-180);Mass Ratio", 100, 0, 1);
   TH1D HMassRatio180("HMassRatio180", "Mass Groomed / original (PT = 180-200);Mass Ratio", 100, 0, 1);
   TH2D HPTMass("HPTMass", "Jet PT vs. Mass;PT;Mass", 100, 120, 200, 100, 0, 60);
   TH2D HPTGroomedMass("HPTGroomedMass", "Jet PT vs. Groomed Mass;PT;Mass", 100, 120, 200, 100, 0, 60);
   TH2D HPTGroomedPT("HPTGroomedPT", "Jet PT vs. Groomed PT;PT;PT", 100, 120, 200, 100, 0, 200);

   HPT.SetStats(0);
   HPTRatio.SetStats(0);
   HNDropped.SetStats(0);
   HZG120.SetStats(0);
   HZG140.SetStats(0);
   HZG160.SetStats(0);
   HZG180.SetStats(0);
   HMassRatio120.SetStats(0);
   HMassRatio140.SetStats(0);
   HMassRatio160.SetStats(0);
   HMassRatio180.SetStats(0);
   HPTMass.SetStats(0);
   HPTGroomedMass.SetStats(0);
   HPTGroomedPT.SetStats(0);

   HZG120.Sumw2();
   HZG140.Sumw2();
   HZG160.Sumw2();
   HZG180.Sumw2();

   int EntryCount = 10;
   cin >> EntryCount;
   
   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      TH2D HEtaPhi(Form("HEtaPhi_%d", iEntry), Form("Event %d;#eta;#phi", iEntry), 100, -5, 5, 100, -3.14159, 3.14159);
      HEtaPhi.SetStats(0);
   
      if((iEntry + 1) % 1000 == 0)
         cout << "Processing entry " << iEntry + 1 << "/" << EntryCount << endl;

      int EventSize = 0;
      cin >> EventSize;
      if(EventSize == 0)
         break;
      
      // Particles
      vector<GenParticle> Particles(EventSize);

      // Loop over particles
      for(int j = 0; j < EventSize; j++)
      {
         cin >> Particles[j].P[0];
         cin >> Particles[j].P[1];
         cin >> Particles[j].P[2];
         cin >> Particles[j].P[3];

         Particles[j].V[0] = 0;
         Particles[j].V[1] = 0;
         Particles[j].V[2] = 0;
         Particles[j].V[3] = 0;

         cin >> Particles[j].PDGID;
         cin >> Particles[j].StatusCode;
      }
      GenParticleTree Tree(Particles, 1, iEntry + 1);

      // Fill pseudojets to be passed into fastjet
      vector<PseudoJet> VisibleParticles;
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].StatusCode != 1)
            continue;
         if(Tree[j].PDGID == 12 || Tree[j].PDGID == -12)
            continue;
         if(Tree[j].PDGID == 14 || Tree[j].PDGID == -14)
            continue;
         if(Tree[j].PDGID == 16 || Tree[j].PDGID == -16)
            continue;
         if(Tree[j].P.GetAbsEta() > 3)
            continue;
         if(Tree[j].P.GetPT() < 0.1)
            continue;
         
         HEtaPhi.Fill(Tree[j].P.GetEta(), Tree[j].P.GetPhi(), Tree[j].P.GetPT());

         VisibleParticles.push_back(PseudoJet(Tree[j].P[1], Tree[j].P[2], Tree[j].P[3], Tree[j].P[0]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.4);   // anti-kt, R = 0.4

      // Take the leading jet and get its constituents
      int LeadingIndex = 0;
      for(int i = 1; i < (int)Jets.size(); i++)
         if(Jets[i].perp() > Jets[LeadingIndex].perp())
            LeadingIndex = i;

      vector<PseudoJet> Constituents = Jets[LeadingIndex].constituents();

      // Prepare for CA algorithm
      vector<Node *> Nodes;
      for(int i = 0; i < (int)Constituents.size(); i++)
      {
         FourVector P(Constituents[i].e(), Constituents[i].px(), Constituents[i].py(), Constituents[i].pz());
         Nodes.push_back(new Node(P));
      }

      // Run the CA algorithm
      while(Nodes.size() > 1)
      {
         int IndexL = 0, IndexR = 1;
         double BestDistance = -1;

         for(int i = 0; i < (int)Nodes.size() - 1; i++)
         {
            for(int j = i + 1; j < (int)Nodes.size(); j++)
            {
               double Distance = GetDR(Nodes[i]->P, Nodes[j]->P);

               if(Distance < BestDistance || BestDistance < 0)
               {
                  IndexL = i;
                  IndexR = j;
                  BestDistance = Distance;
               }
            }
         }

         if(IndexR < IndexL)   // just in case
            swap(IndexL, IndexR);

         // Now make a new node
         Node *NewNode = new Node(Nodes[IndexL], Nodes[IndexR]);
         Nodes[IndexL] = NewNode;
         Nodes.erase(Nodes.begin() + IndexR);
      }

      // Run the softdrop algorithm
      double zcut = 0.1;
      double beta = 0;
      double r0 = 0.4;

      bool Done = false;
      Node *Current = Nodes[0];

      int Depth = 0;

      while(Done == false)
      {
         if(Current->N == 1)
            Done = true;
         else if(Current->N == 2)
         {
            cerr << "WTF!  Time to Debug!" << endl;
            Done = true;
         }
         else   // N >= 3 => two sub-jets
         {
            double PT1 = Current->Child1->P.GetPT();
            double PT2 = Current->Child2->P.GetPT();
            double PTRatio = min(PT1, PT2) / (PT1 + PT2);

            double DR = GetDR(Current->Child1->P, Current->Child2->P);

            double Threshold = zcut * pow(DR / r0, beta);

            if(PTRatio > Threshold)
               Done = true;
            else
            {
               if(PT1 > PT2)
                  Current = Current->Child1;
               else
                  Current = Current->Child2;

               Depth = Depth + 1;
            }
         }
      }

      HPT.Fill(Nodes[0]->P.GetPT());
      if(Jets[LeadingIndex].eta() < 1.3 && Jets[LeadingIndex].eta() > -1.3)
      {
         if(Jets[LeadingIndex].perp() > 140 && Jets[LeadingIndex].perp() < 160)
         {
            HPTRatio.Fill(Current->P.GetPT() / Nodes[0]->P.GetPT());
            HNDropped.Fill(Depth);
         }

         if(Current->Child1 != NULL && Current->Child2 != NULL)
         {
            double PT1 = Current->Child1->P.GetPT();
            double PT2 = Current->Child2->P.GetPT();
            double ZG = min(PT1, PT2) / (PT1 + PT2);

            if(Jets[LeadingIndex].perp() > 120 && Jets[LeadingIndex].perp() < 140)
               HZG120.Fill(ZG);
            if(Jets[LeadingIndex].perp() > 140 && Jets[LeadingIndex].perp() < 160)
               HZG140.Fill(ZG);
            if(Jets[LeadingIndex].perp() > 160 && Jets[LeadingIndex].perp() < 180)
               HZG160.Fill(ZG);
            if(Jets[LeadingIndex].perp() > 180 && Jets[LeadingIndex].perp() < 200)
               HZG180.Fill(ZG);
            
            if(Jets[LeadingIndex].perp() > 120 && Jets[LeadingIndex].perp() < 140)
               HMassRatio120.Fill(Current->P.GetMass() / Nodes[0]->P.GetMass());
            if(Jets[LeadingIndex].perp() > 140 && Jets[LeadingIndex].perp() < 160)
               HMassRatio140.Fill(Current->P.GetMass() / Nodes[0]->P.GetMass());
            if(Jets[LeadingIndex].perp() > 160 && Jets[LeadingIndex].perp() < 180)
               HMassRatio160.Fill(Current->P.GetMass() / Nodes[0]->P.GetMass());
            if(Jets[LeadingIndex].perp() > 180 && Jets[LeadingIndex].perp() < 200)
               HMassRatio180.Fill(Current->P.GetMass() / Nodes[0]->P.GetMass());

            HPTMass.Fill(Jets[LeadingIndex].perp(), Nodes[0]->P.GetMass());
            HPTGroomedMass.Fill(Jets[LeadingIndex].perp(), Current->P.GetMass());
            HPTGroomedPT.Fill(Jets[LeadingIndex].perp(), Current->P.GetPT());
         }
      }

      // Export some plots
      TCanvas *C = new TCanvas;

      HEtaPhi.Draw("colz");

      vector<TEllipse *> Ellipses;
      for(int i = 0; i < (int)Jets.size(); i++)
      {
         if(Jets[i].perp() < 10)
            continue;

         TEllipse *NewOne = NULL;

         NewOne = NULL;
         NewOne = new TEllipse(Jets[i].eta(), Jets[i].phi(), 0.4);
         NewOne->SetFillStyle(0);
         NewOne->Draw();
         Ellipses.push_back(NewOne);

         NewOne = NULL;
         NewOne = new TEllipse(Jets[i].eta(), Jets[i].phi() - 3.1415926535 * 2, 0.4);
         NewOne->SetFillStyle(0);
         NewOne->Draw();
         Ellipses.push_back(NewOne);

         NewOne = NULL;
         NewOne = new TEllipse(Jets[i].eta(), Jets[i].phi() + 3.1415926535 * 2, 0.4);
         NewOne->SetFillStyle(0);
         NewOne->Draw();
         Ellipses.push_back(NewOne);
      }

      // C->SaveAs(Form("Meow_%d.png", iEntry));

      // Cleanup
      delete Nodes[0];
      
      delete C;

      for(int i = 0; i < (int)Ellipses.size(); i++)
         if(Ellipses[i] != NULL)
            delete Ellipses[i];
      Ellipses.clear();
   }

   TCanvas C;
   C.SetGridx();
   C.SetGridy();
   C.SetLogy();

   NormalizeHistogram(HPT);
   HPT.Draw();

   C.SaveAs("PT.png");
   C.SaveAs("PT.C");
   C.SaveAs("PT.eps");
   C.SaveAs("PT.pdf");

   NormalizeHistogram(HPTRatio);
   HPTRatio.SetMinimum(0.02);
   HPTRatio.SetMaximum(100);
   HPTRatio.Draw();

   C.SaveAs("PTRatio.png");
   C.SaveAs("PTRatio.C");
   C.SaveAs("PTRatio.eps");
   C.SaveAs("PTRatio.pdf");

   NormalizeHistogram(HNDropped);
   HNDropped.SetMinimum(0.00005);
   HNDropped.SetMaximum(1);
   HNDropped.Draw();

   C.SaveAs("NDropped.png");
   C.SaveAs("NDropped.C");
   C.SaveAs("NDropped.eps");
   C.SaveAs("NDropped.pdf");

   NormalizeHistogram(HMassRatio120);
   HMassRatio120.Draw();

   C.SaveAs("MassRatio120.png");
   C.SaveAs("MassRatio120.C");
   C.SaveAs("MassRatio120.eps");
   C.SaveAs("MassRatio120.pdf");

   NormalizeHistogram(HMassRatio140);
   HMassRatio140.Draw();

   C.SaveAs("MassRatio140.png");
   C.SaveAs("MassRatio140.C");
   C.SaveAs("MassRatio140.eps");
   C.SaveAs("MassRatio140.pdf");

   NormalizeHistogram(HMassRatio160);
   HMassRatio160.Draw();

   C.SaveAs("MassRatio160.png");
   C.SaveAs("MassRatio160.C");
   C.SaveAs("MassRatio160.eps");
   C.SaveAs("MassRatio160.pdf");

   NormalizeHistogram(HMassRatio180);
   HMassRatio180.Draw();

   C.SaveAs("MassRatio180.png");
   C.SaveAs("MassRatio180.C");
   C.SaveAs("MassRatio180.eps");
   C.SaveAs("MassRatio180.pdf");

   C.SetLogy(false);

   NormalizeHistogram(HZG120);
   HZG120.SetMinimum(0);
   HZG120.SetMaximum(10);
   HZG120.Draw("error");

   C.SaveAs("ZG120.png");
   C.SaveAs("ZG120.C");
   C.SaveAs("ZG120.eps");
   C.SaveAs("ZG120.pdf");

   NormalizeHistogram(HZG140);
   HZG140.SetMinimum(0);
   HZG140.SetMaximum(10);
   HZG140.Draw("error");

   C.SaveAs("ZG140.png");
   C.SaveAs("ZG140.C");
   C.SaveAs("ZG140.eps");
   C.SaveAs("ZG140.pdf");

   NormalizeHistogram(HZG160);
   HZG160.SetMinimum(0);
   HZG160.SetMaximum(10);
   HZG160.Draw("error");

   C.SaveAs("ZG160.png");
   C.SaveAs("ZG160.C");
   C.SaveAs("ZG160.eps");
   C.SaveAs("ZG160.pdf");

   NormalizeHistogram(HZG180);
   HZG180.SetMinimum(0);
   HZG180.SetMaximum(10);
   HZG180.Draw("error");

   C.SaveAs("ZG180.png");
   C.SaveAs("ZG180.C");
   C.SaveAs("ZG180.eps");
   C.SaveAs("ZG180.pdf");

   HZG120.SetMarkerColor(kBlue);
   HZG120.SetLineColor(kBlue);
   HZG140.SetMarkerColor(kGreen);
   HZG140.SetLineColor(kGreen);
   HZG160.SetMarkerColor(kRed);
   HZG160.SetLineColor(kRed);
   HZG180.SetMarkerColor(kBlack);
   HZG180.SetLineColor(kBlack);

   HZG120.SetTitle("");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetBorderSize(0);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.AddEntry(&HZG120, "P_{T} = 120-140");
   Legend.AddEntry(&HZG140, "P_{T} = 140-160");
   Legend.AddEntry(&HZG160, "P_{T} = 160-180");
   Legend.AddEntry(&HZG180, "P_{T} = 180-200");

   HZG120.Draw("error");
   HZG140.Draw("error same");
   HZG160.Draw("error same");
   HZG180.Draw("error same");

   Legend.Draw();

   C.SaveAs("ZG.png");
   C.SaveAs("ZG.C");
   C.SaveAs("ZG.eps");
   C.SaveAs("ZG.pdf");
   
   HMassRatio120.SetMarkerColor(kBlue);
   HMassRatio120.SetLineColor(kBlue);
   HMassRatio140.SetMarkerColor(kGreen);
   HMassRatio140.SetLineColor(kGreen);
   HMassRatio160.SetMarkerColor(kRed);
   HMassRatio160.SetLineColor(kRed);
   HMassRatio180.SetMarkerColor(kBlack);
   HMassRatio180.SetLineColor(kBlack);

   TLegend Legend2(0.5, 0.2, 0.8, 0.4);
   Legend2.SetBorderSize(0);
   Legend2.SetTextFont(42);
   Legend2.SetTextSize(0.035);
   Legend2.AddEntry(&HZG120, "P_{T} = 120-140");
   Legend2.AddEntry(&HZG140, "P_{T} = 140-160");
   Legend2.AddEntry(&HZG160, "P_{T} = 160-180");
   Legend2.AddEntry(&HZG180, "P_{T} = 180-200");

   HMassRatio120.Draw();
   HMassRatio140.Draw("same");
   HMassRatio160.Draw("same");
   HMassRatio180.Draw("same");

   Legend2.Draw();

   C.SaveAs("MassRatio.png");
   C.SaveAs("MassRatio.C");
   C.SaveAs("MassRatio.eps");
   C.SaveAs("MassRatio.pdf");

   HPTMass.Draw("colz");

   C.SaveAs("PTMass.png");
   C.SaveAs("PTMass.C");
   C.SaveAs("PTMass.eps");
   C.SaveAs("PTMass.pdf");

   HPTGroomedMass.Draw("colz");

   C.SaveAs("PTGroomedMass.png");
   C.SaveAs("PTGroomedMass.C");
   C.SaveAs("PTGroomedMass.eps");
   C.SaveAs("PTGroomedMass.pdf");

   HPTGroomedPT.Draw("colz");

   C.SaveAs("PTGroomedPT.png");
   C.SaveAs("PTGroomedPT.C");
   C.SaveAs("PTGroomedPT.eps");
   C.SaveAs("PTGroomedPT.pdf");

   return 0;
}

void NormalizeHistogram(TH1D &H)
{
   double N = H.GetNbinsX();
   double L = H.GetXaxis()->GetBinLowEdge(1);
   double R = H.GetXaxis()->GetBinUpEdge(N);
   double BinSize = (R - L) / N;

   H.Scale(1 / H.Integral() / BinSize);
}


