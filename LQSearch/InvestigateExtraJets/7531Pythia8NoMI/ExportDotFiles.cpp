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
#include "TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void ExportDotFiles(string InputMass);
void ExportSingleTree(GenParticleTree &Tree, double MinE, string OutputFileName);

int main(int argc, char *argv[])
{
   SetStyle();

   string InputMass = "300";
   if(argc >= 2)
      InputMass = argv[1];
   ExportDotFiles(InputMass);

   return 0;
};

void ExportDotFiles(string InputMass)
{
   ifstream in(("Samples/Pythia8_NoMI_NoHadronization_LQ" + InputMass).c_str());

   SaveHelper Helper;
   in.read(Helper.CharValue, 16);
   int NumberOfEntries = Helper.IntValue;

   PsFileHelper PsFile("EtaPhiMaps" + InputMass + ".ps");
   PsFile.AddTextPage("Eta-Phi pt map");

   for(int iEvent = 0; iEvent < NumberOfEntries; iEvent++)
   {
      if((iEvent + 1) % 5000 == 0)
         cout << "Processing entry " << iEvent + 1 << "/" << NumberOfEntries << endl;
      if(iEvent >= 1000)
         break;

      GenParticleTree Tree;
      Tree.LoadFromStream(in);

      stringstream outputname;
      outputname << "DotFiles/Mass" << InputMass
         << "_Run" << Tree.GetRunNumber()
         << "_Event" << Tree.GetEventNumber()
         << ".dot";

      ExportSingleTree(Tree, 0, outputname.str());

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

         FourVector ParticleP(Tree[i].P);

         HEtaPhiPT.Fill(ParticleP.GetEta(), ParticleP.GetPhi(), ParticleP.GetPT());
      }

      HEtaPhiPT.SetStats(0);

      TCanvas Canvas("EtaPhiMapCanvas", "Eta-phi map canvas");
      HEtaPhiPT.Draw("colz");

      PsFile.AddCanvas(Canvas);
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

      FourVector ParticleP(Tree[i].P);

      out << "   Particle" << i << " [label = \"";
      out << "ID = " << Tree[i].PDGID << " (" << Tree[i].StatusCode << ")\\n";
      out << setprecision(4);
      out << "E = " << ParticleP[0] << "\\nPT = " << ParticleP.GetPT() << "\\n";
      out << "Eta = " << ParticleP.GetEta() << "\\nPhi = " << ParticleP.GetPhi() << "\\n";
      out << "\"";

      if(ParticleP.GetPT() > 30)
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







