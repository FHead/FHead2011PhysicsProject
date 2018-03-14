#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

#include "fastjet/ClusterSequence.hh"
using namespace fastjet;

#include "TTree.h"
#include "TFile.h"

#include "Code/TauHelperFunctions3.h"
#include "ProgressBar.h"

#include "TreeMessenger.h"

int main(int argc, char *argv[]);
double GetDPhi(double Phi1, double Phi2);
int FindBin(double Value, int N, double Bins[]);

int main(int argc, char *argv[])
{
   ClusterSequence::set_fastjet_banner_stream(NULL);

   if(argc != 7)
   {
      cerr << "Usage: " << argv[0] << " Hydjet Pythia Output PythiaStart PythiaEnd HydjetFileIndex" << endl;
      return -1;
   }

   string HydjetFileName = argv[1];
   string PythiaFileName = argv[2];
   string OutputFileName = argv[3];
   int PythiaStart = atoi(argv[4]);
   int PythiaEnd = atoi(argv[5]);
   int HydjetFileIndex = atoi(argv[6]);

   TFile HydjetFile(HydjetFileName.c_str());
   TFile PythiaFile(PythiaFileName.c_str());

   TreeMessenger MHydjet(HydjetFile);
   TreeMessenger MPythia(PythiaFile);

   if(MPythia.EntryCount() < 0 || MHydjet.EntryCount() < 0)
   {
      cerr << "Tree read error!" << endl;
      return -1;
   }

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("JetTree", "Jet tree for ML");

   double EtaBins[14+1] = {-3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5};

   int HydjetEntry;
   int PythiaEntry;
   float HydjetRho[14];
   int AllJetCount;
   int JetCount;
   int JetIndex;
   float JetPT;
   float JetEta;
   float JetPhi;
   int N;
   float Px[TREEMAX];
   float Py[TREEMAX];
   float Pz[TREEMAX];
   float E[TREEMAX];
   int Type[TREEMAX];

   OutputTree.Branch("HydjetFileIndex", &HydjetFileIndex, "HydjetFileIndex/I");
   OutputTree.Branch("HydjetEntry", &HydjetEntry, "HydjetEntry/I");
   OutputTree.Branch("PythiaEntry", &PythiaEntry, "PythiaEntry/I");
   OutputTree.Branch("HydjetRho", &HydjetRho, "HydjetRho[14]/F");
   OutputTree.Branch("AllJetCount", &AllJetCount, "AllJetCount/I");
   OutputTree.Branch("JetCount", &JetCount, "JetCount/I");
   OutputTree.Branch("JetIndex", &JetIndex, "JetIndex/I");
   OutputTree.Branch("JetPT", &JetPT, "JetPT/F");
   OutputTree.Branch("JetEta", &JetEta, "JetEta/F");
   OutputTree.Branch("JetPhi", &JetPhi, "JetPhi/F");
   OutputTree.Branch("N", &N, "N/I");
   OutputTree.Branch("Px", &Px, "Px[N]/F");
   OutputTree.Branch("Py", &Py, "Py[N]/F");
   OutputTree.Branch("Pz", &Pz, "Pz[N]/F");
   OutputTree.Branch("E", &E, "E[N]/F");
   OutputTree.Branch("Type", &Type, "Type[N]/I");

   ProgressBar Bar(cout, PythiaEnd + 1, PythiaStart);
   Bar.SetStyle(3);

   for(int iEntry = PythiaStart; iEntry <= PythiaEnd; iEntry++)
   {
      PythiaEntry = iEntry;
      HydjetEntry = iEntry - PythiaStart;

      Bar.Update(iEntry);
      Bar.Print();

      bool PythiaGood = MPythia.GetEntry(iEntry);
      bool HydjetGood = MHydjet.GetEntry(iEntry - PythiaStart);

      if(PythiaGood == false || HydjetGood == false)
         continue;

      for(int i = 0; i < 14; i++)
         HydjetRho[i] = 0;
      for(int i = 0; i < MHydjet.Ntot; i++)
      {
         if(MHydjet.Final[i] == false)
            continue;
         FourVector P(MHydjet.E[i], MHydjet.Px[i], MHydjet.Py[i], MHydjet.Pz[i]);
         int Bin = FindBin(P.GetEta(), 14, EtaBins);
         if(Bin >= 0 && Bin < 14)
            HydjetRho[Bin] = HydjetRho[Bin] + P.GetPT();
      }
      for(int i = 0; i < 14; i++)
         HydjetRho[i] = HydjetRho[i] / (2 * M_PI * (EtaBins[i+1] - EtaBins[i]));

      vector<PseudoJet> Particles;
      for(int i = 0; i < MPythia.Ntot; i++)
      {
         if(MPythia.Final[i] == false)
            continue;
         Particles.push_back(PseudoJet(MPythia.Px[i], MPythia.Py[i], MPythia.Pz[i], MPythia.E[i]));
      }
      for(int i = 0; i < MHydjet.Ntot; i++)
      {
         if(MHydjet.Final[i] == false)
            continue;
         Particles.push_back(PseudoJet(MHydjet.Px[i], MHydjet.Py[i], MHydjet.Pz[i], MHydjet.E[i]));
      }
      JetDefinition Definition(antikt_algorithm, 0.4);
      ClusterSequence Sequence(Particles, Definition);
      vector<PseudoJet> Jets = Sequence.inclusive_jets();

      vector<pair<double, int>> JetSorter;
      for(int iJ = 0; iJ < (int)Jets.size(); iJ++)
      {
         if(Jets[iJ].perp() < 150 || fabs(Jets[iJ].eta() > 2.5))
            continue;
         JetSorter.push_back(pair<double, int>(Jets[iJ].perp(), iJ));
      }
      sort(JetSorter.begin(), JetSorter.end(), greater<pair<double, int>>());

      for(int iJS = 0; iJS < (int)JetSorter.size(); iJS++)
      {
         int iJ = JetSorter[iJS].second;

         JetPT = Jets[iJ].perp();
         JetEta = Jets[iJ].eta();
         JetPhi = Jets[iJ].phi();
         AllJetCount = Jets.size();
         JetCount = JetSorter.size();
         JetIndex = iJS;

         N = 0;
         for(int i = 0; i < TREEMAX; i++)
         {
            Px[i] = 0;
            Py[i] = 0;
            Pz[i] = 0;
            E[i] = 0;
            Type[i] = 0;
         }

         for(int i = 0; i < MPythia.Ntot; i++)
         {
            if(MPythia.Final[i] == false)
               continue;
            PseudoJet P(MPythia.Px[i], MPythia.Py[i], MPythia.Pz[i], MPythia.E[i]);
            if(fabs(P.eta() - Jets[iJ].eta()) > 0.8)
               continue;
            if(fabs(GetDPhi(P.phi(), Jets[iJ].phi())) > 0.8)
               continue;

            Px[N] = MPythia.Px[i];
            Py[N] = MPythia.Py[i];
            Pz[N] = MPythia.Pz[i];
            E[N] = MPythia.E[i];
            Type[N] = 1;
            N = N + 1;
         }
         for(int i = 0; i < MHydjet.Ntot; i++)
         {
            if(MHydjet.Final[i] == false)
               continue;
            PseudoJet P(MHydjet.Px[i], MHydjet.Py[i], MHydjet.Pz[i], MHydjet.E[i]);
            if(fabs(P.eta() - Jets[iJ].eta()) > 0.8)
               continue;
            if(fabs(GetDPhi(P.phi(), Jets[iJ].phi())) > 0.8)
               continue;

            Px[N] = MHydjet.Px[i];
            Py[N] = MHydjet.Py[i];
            Pz[N] = MHydjet.Pz[i];
            E[N] = MHydjet.E[i];
            Type[N] = 2;
            N = N + 1;
         }

         OutputTree.Fill();
      }
   }

   Bar.Update(PythiaEnd + 1);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   OutputFile.Close();

   HydjetFile.Close();
   PythiaFile.Close();

   return 0;
}

double GetDPhi(double Phi1, double Phi2)
{
   double DPhi = Phi1 - Phi2;
   if(DPhi < -M_PI)
      DPhi = DPhi + 2 * M_PI;
   if(DPhi > +M_PI)
      DPhi = DPhi - 2 * M_PI;
   return DPhi;
}

int FindBin(double Value, int N, double Bins[])
{
   if(N == 0)
      return -1;

   if(Value < Bins[0])
      return -1;
   
   for(int i = 0; i < N; i++)
      if(Value >= Bins[i] && Value < Bins[i+1])
         return i;

   return N + 1;
}



