#include <iostream>
#include <cassert>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CommandLine.h"
#include "ProgressBar.h"
#include "Code/TauHelperFunctions3.h"

#define TREEMAX 200000
#define GRIDSIZE 89
#define BINCOUNT 360
#define BINSIZE (2*M_PI/BINCOUNT)

int main(int argc, char *argv[]);
bool IsCharged(int PDGID);
bool IsNeutrino(int PDGID);
int GetEtaBin(double Eta);
int GetPhiBin(double Phi);
int GetDEtaBin(int Bin1, int Bin2);
int GetDPhiBin(int Bin1, int Bin2);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");
   string OutputFileName = CL.Get("output");
   string InputTreeName = CL.Get("tree", "JetTree");
   double PTCutOffCharged = CL.GetDouble("ptcutcharged", 0.5);
   double PTCutOffNeutral = CL.GetDouble("ptcutneutral", 0.5);

   int CenterBin = (GRIDSIZE + 1) / 2;

   double EtaBins[14+1] = {-3.5, -3.0, -2.5, -2.0, -1.5, -1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5};

   TFile InputFile(InputFileName.c_str());
   TTree *InputTree = (TTree *)InputFile.Get(InputTreeName.c_str());

   assert(InputTree != NULL);

   int HydjetEntry;          InputTree->SetBranchAddress("HydjetEntry", &HydjetEntry);
   int PythiaEntry;          InputTree->SetBranchAddress("PythiaEntry", &PythiaEntry);
   float HydjetRho[14];      InputTree->SetBranchAddress("HydjetRho", &HydjetRho);
   int AllJetCount;          InputTree->SetBranchAddress("AllJetCount", &AllJetCount);
   int JetCount;             InputTree->SetBranchAddress("JetCount", &JetCount);
   int JetIndex;             InputTree->SetBranchAddress("JetIndex", &JetIndex);
   float JetPT;              InputTree->SetBranchAddress("JetPT", &JetPT);
   float JetEta;             InputTree->SetBranchAddress("JetEta", &JetEta);
   float JetPhi;             InputTree->SetBranchAddress("JetPhi", &JetPhi);
   int N;                    InputTree->SetBranchAddress("N", &N);
   float Px[TREEMAX];        InputTree->SetBranchAddress("Px", &Px);
   float Py[TREEMAX];        InputTree->SetBranchAddress("Py", &Py);
   float Pz[TREEMAX];        InputTree->SetBranchAddress("Pz", &Pz);
   float E[TREEMAX];         InputTree->SetBranchAddress("E", &E);
   int ID[TREEMAX];          InputTree->SetBranchAddress("ID", &ID);
   int Type[TREEMAX];        InputTree->SetBranchAddress("Type", &Type);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("DiscretizedJetTree", "Discretized jet tree for ML");

   float Images[89][89][7];

   OutputTree.Branch("HydjetEntry", &HydjetEntry, "HydjetEntry/I");
   OutputTree.Branch("PythiaEntry", &PythiaEntry, "PythiaEntry/I");
   OutputTree.Branch("AllJetCount", &AllJetCount, "AllJetCount/I");
   OutputTree.Branch("JetCount", &JetCount, "JetCount/I");
   OutputTree.Branch("JetIndex", &JetIndex, "JetIndex/I");
   OutputTree.Branch("JetPT", &JetPT, "JetPT/F");
   OutputTree.Branch("JetEta", &JetEta, "JetEta/F");
   OutputTree.Branch("JetPhi", &JetPhi, "JetPhi/F");
   OutputTree.Branch("Images", &Images, "Images[89][89][7]/F");

   int EntryCount = InputTree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(5);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Bar.Update(iE);
      Bar.Print();

      InputTree->GetEntry(iE);

      FourVector FourVectorImages[89][89][2][2];   // eta, phi, S/B, neutral/charged

      int JetEtaBin = GetEtaBin(JetEta);
      int JetPhiBin = GetPhiBin(JetPhi);
      
      for(int i = 0; i < N; i++)
      {
         FourVector P(E[i], Px[i], Py[i], Pz[i]);

         bool Charged = IsCharged(ID[i]);
         bool IsBackground = (Type[i] == 1 ? false : true);

         if(Charged == true && P.GetPT() < PTCutOffCharged)    continue;
         if(Charged == false && P.GetPT() < PTCutOffNeutral)   continue;

         if(IsNeutrino(ID[i]) == true)   continue;

         int EtaBin = GetEtaBin(P.GetEta());
         int PhiBin = GetPhiBin(P.GetPhi());

         int DEtaBin = GetDEtaBin(EtaBin, JetEtaBin) + CenterBin;
         int DPhiBin = GetDPhiBin(PhiBin, JetPhiBin) + CenterBin;

         if(DEtaBin < 0 || DEtaBin >= GRIDSIZE)   continue;
         if(DPhiBin < 0 || DPhiBin >= GRIDSIZE)   continue;

         FourVectorImages[DEtaBin][DPhiBin][IsBackground][Charged]
            = FourVectorImages[DEtaBin][DPhiBin][IsBackground][Charged] + P;
      }

      for(int i = 0; i < 89; i++)
      {
         double EtaAtCenter = (JetEtaBin + 0.5) * BINSIZE;
         double Factor = 1 / cosh(EtaAtCenter);
         
         for(int j = 0; j < 89; j++)
         {
            Images[i][j][0] = FourVectorImages[i][j][0][1].GetPT();
            Images[i][j][1] = FourVectorImages[i][j][0][1][0] * Factor;
            Images[i][j][2] = FourVectorImages[i][j][0][0][0] * Factor;
            Images[i][j][3] = FourVectorImages[i][j][1][1].GetPT();
            Images[i][j][4] = FourVectorImages[i][j][1][1][0] * Factor;
            Images[i][j][5] = FourVectorImages[i][j][1][0][0] * Factor;
         }
      }
      
      for(int i = 0; i < 89; i++)
      {
         double EtaAtCenter = (JetEtaBin + 0.5) * BINSIZE;
         double Rho = 0;
         for(int j = 0; j < 14; j++)
            if(EtaBins[j] <= EtaAtCenter && EtaBins[j+1] > EtaAtCenter)
               Rho = HydjetRho[j];

         for(int j = 0; j < 89; j++)
            Images[i][j][6] = Rho * BINSIZE * BINSIZE;
      }

      OutputTree.Fill();
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputTree.Write();
   OutputFile.Close();

   InputFile.Close();

   return 0;
}

bool IsCharged(int PDGID)
{
   if(PDGID < 0)
      PDGID = -PDGID;

   switch(PDGID)
   {
   case 12:
   case 14:
   case 16:
   case 22:
   case 130:
   case 310:
   case 111:
   case 113:
   case 311:
   case 2112:
   case 3322:
   case 3212:
   case 3122:
   case 4114:
   case 4112:
      return false;
   case 11:
   case 13:
   case 15:
   case 211:
   case 213:
   case 321:
   case 415:
   case 2212:
   case 3312:
   case 3112:
   case 3222:
   case 3334:
   case 4214:
   case 4224:
   case 4212:
   case 4222:
      return true;
   default:
      cout << PDGID << endl;
   }

   return false;
}

bool IsNeutrino(int PDGID)
{
   if(PDGID == 12)   return true;
   if(PDGID == 14)   return true;
   if(PDGID == 16)   return true;
   if(PDGID == -12)   return true;
   if(PDGID == -14)   return true;
   if(PDGID == -16)   return true;
   return false;
}

int GetEtaBin(double Eta)
{
   return floor(Eta / BINSIZE);
}

int GetPhiBin(double Phi)
{
   while(Phi < -M_PI)
      Phi = Phi + 2 * M_PI;
   while(Phi > M_PI)
      Phi = Phi - 2 * M_PI;
   return floor(Phi / BINSIZE);
}

int GetDEtaBin(int Bin1, int Bin2)
{
   return Bin1 - Bin2;
}

int GetDPhiBin(int Bin1, int Bin2)
{
   int DPhi = Bin1 - Bin2;
   while(DPhi < -BINCOUNT / 2)
      DPhi = DPhi + BINCOUNT;
   while(DPhi > BINCOUNT / 2)
      DPhi = DPhi - BINCOUNT;
   return DPhi;
}


