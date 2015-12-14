#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TH2D.h"
#include "TEllipse.h"

#include "GenparticleTree.h"
#include "TauHelperFunctions.h"
#include "PlotHelper.h"

int main(int argc, char *argv[]);
void ExportDotFiles(string InputMass);
void ExportSingleTree(GenParticleTree &Tree, double MinE, string OutputFileName);

int main(int argc, char *argv[])
{
   gROOT->SetStyle("Plain");

   TStyle gStyle;
   
   const Int_t NRGBs = 5;
   const Int_t NCont = 255;

   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
   TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
   gStyle.SetNumberContours(NCont);

   string InputMass = "350";
   if(argc >= 2)
      InputMass = argv[1];
   ExportDotFiles(InputMass);

   return 0;
};

void ExportDotFiles(string InputMass)
{
   ifstream in(("Samples/LQ" + InputMass + "Sample").c_str());

   SaveHelper Helper;
   in.read(Helper.CharValue, 16);
   int NumberOfEntries = Helper.IntValue;

   PsFileHelper PsFile("EtaPhiMaps" + InputMass + ".ps");
   PsFile.AddTextPage("Eta-Phi pt map");

   for(int iEvent = 0; iEvent < NumberOfEntries; iEvent++)
   {
      if((iEvent + 1) % 5000 == 0)
         cout << "Processing entry " << iEvent + 1 << "/" << NumberOfEntries << endl;
      if(iEvent >= 50000)
         break;

      GenParticleTree Tree;
      Tree.LoadFromStream(in);

      vector<PseudoJet> VisibleParticles;
      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].StatusCode != 1)   // not final
            continue;
         if(Tree[i].PDGID == 12 || Tree[i].PDGID == -12)   // e neutrino
            continue;
         if(Tree[i].PDGID == 14 || Tree[i].PDGID == -14)   // mu neutrino
            continue;
         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16)   // tau neutrino
            continue;
         if(fabs(GetEta(Tree[i].P)) > 2.4)
            continue;

         VisibleParticles.push_back(PseudoJet(Tree[i].P[1], Tree[i].P[2], Tree[i].P[3], Tree[i].P[0]));
      }

      JetDefinition Definition(antikt_algorithm, 0.5);
      ClusterSequence Sequence(VisibleParticles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets(0.5);

      int NJet50 = 0;
      for(int i = 0; i < (int)Jets.size(); i++)
         if(Jets[i].perp() > 50)
            NJet50 = NJet50 + 1;

      if(NJet50 <= 5)   // we want strange events
         continue;

      stringstream outputname;
      outputname << "DotFiles/Mass" << InputMass
         << "_Run" << Tree.GetRunNumber()
         << "_Event" << Tree.GetEventNumber()
         << ".dot";

      ExportSingleTree(Tree, 25, outputname.str());

      TH2D HEtaPhiPT("HEtaPhiPT", Form("Run %d, Event %d", Tree.GetRunNumber(), Tree.GetEventNumber()),
         100, -5, 5, 100, -3.2, 3.2);
      HEtaPhiPT.GetXaxis()->SetTitle("Eta");
      HEtaPhiPT.GetYaxis()->SetTitle("Phi");
      HEtaPhiPT.GetZaxis()->SetTitle("Total PT in bin");

      for(int i = 0; i < Tree.ParticleCount(); i++)
      {
         if(Tree[i].StatusCode != 1)   // not final
            continue;
         if(Tree[i].PDGID == 12 || Tree[i].PDGID == -12)   // e neutrino
            continue;
         if(Tree[i].PDGID == 14 || Tree[i].PDGID == -14)   // mu neutrino
            continue;
         if(Tree[i].PDGID == 16 || Tree[i].PDGID == -16)   // tau neutrino
            continue;

         HEtaPhiPT.Fill(GetEta(Tree[i].P), GetPhi(Tree[i].P), GetPT(Tree[i].P));
      }

      HEtaPhiPT.SetStats(0);

      TCanvas Canvas("EtaPhiMapCanvas", "Eta-phi map canvas");
      HEtaPhiPT.Draw("colz");

      vector<TEllipse *> Ellipses;

      for(int i = 0; i < (int)Jets.size(); i++)
      {
         if(Jets[i].perp() < 50)
            continue;

         double JetP[4] = {Jets[i].e(), Jets[i].px(), Jets[i].py(), Jets[i].pz()};

         Ellipses.push_back(new TEllipse(GetEta(JetP), GetPhi(JetP), 0.5));
         
         if(GetPhi(JetP) > PI - 0.6)
            Ellipses.push_back(new TEllipse(GetEta(JetP), GetPhi(JetP) - 2 * PI, 0.5));
         if(GetPhi(JetP) < -PI + 0.6)
            Ellipses.push_back(new TEllipse(GetEta(JetP), GetPhi(JetP) + 2 * PI, 0.5));
      }

      for(int i = 0; i < (int)Ellipses.size(); i++)
      {
         Ellipses[i]->SetFillStyle(0);
         Ellipses[i]->SetFillColor(1);
         Ellipses[i]->Draw();
      }

      PsFile.AddCanvas(Canvas);

      for(int i = 0; i < (int)Ellipses.size(); i++)
         delete Ellipses[i];
      Ellipses.clear();
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   in.close();
}

void ExportSingleTree(GenParticleTree &Tree, double MinE, string OutputFileName)
{
   ofstream out(OutputFileName.c_str());

   // start
   out << "digraph DummyName" << endl;
   out << "{" << endl;
   out << "   overlap = false;" << endl;

   // section 1: define nodes and labels
   for(int i = 0; i < Tree.ParticleCount(); i++)
   {
      if(Tree[i].P[0] < MinE)
         continue;

      out << "   Particle" << i << " [label = \"";
      out << "ID = " << Tree[i].PDGID << " (" << Tree[i].StatusCode << ")\\n";
      out << setprecision(4);
      out << "E = " << Tree[i].P[0] << "\\nPT = " << GetPT(Tree[i].P) << "\\n";
      out << "Eta = " << GetEta(Tree[i].P) << "\\nPhi = " << GetPhi(Tree[i].P) << "\\n";
      out << "\"";

      if(GetPT(Tree[i].P) > 30)
         out << " shape = box";

      out << "];" << endl;

      int IgnoredChildNodeCount = 0;
      for(int j = 0; j < (int)Tree[i].Daughters.size(); j++)
         if(Tree[Tree[i].Daughters[j]].P[0] < MinE)
            IgnoredChildNodeCount = IgnoredChildNodeCount + 1;

      if(IgnoredChildNodeCount >= 1)
      {
         out << "   Particle" << i << "_IgnoredNodes [label = \"Ignored\\n";
         out << IgnoredChildNodeCount << " particle";
         if(IgnoredChildNodeCount > 1)
            out << "s";
         out << "\"];" << endl;
      }
   }
   out << endl;

   // section 2: links --- mother -> daughter
   for(int i = 0; i < Tree.ParticleCount(); i++)
   {
      if(Tree[i].P[0] < MinE)
         continue;
      
      int IgnoredChildNodeCount = 0;
      for(int j = 0; j < (int)Tree[i].Daughters.size(); j++)
      {
         if(Tree[Tree[i].Daughters[j]].P[0] < MinE)
         {
            IgnoredChildNodeCount = IgnoredChildNodeCount + 1;
            continue;
         }

         out << "   Particle" << i << " -> Particle" << Tree[i].Daughters[j] << endl;
      }

      if(IgnoredChildNodeCount > 0)
         out << "   Particle" << i << " -> Particle" << i << "_IgnoredNodes" << endl;
   }

   out << "}" << endl;

   out.close();
}







