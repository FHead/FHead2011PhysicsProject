#include <iostream>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "EFTBases.h"

#include "ProgressBar.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   TCanvas C;

   string FileName = "Graph.root";
   string Type = "Both";
   string Cut = "A";
   double Efficiency = 1;
   string Point = "A";
   double TrueA2ZZ = 0;
   double TrueA3ZZ = 0;
   double TrueA4ZZ = 0;
   double TrueA2ZA = 0;
   double TrueA3ZA = 0;
   double TrueA4ZA = 0;
   double TrueA2AA = 0;
   double TrueA3AA = 0;

   if(argc < 14)
   {
      cerr << "Usage: " << argv[0] << " FileName Type Cut Efficiency  Point  A2ZZ A3ZZ A4ZZ A2ZA A3ZA A4ZA A2AA A3AA" << endl;
      cerr << "   Example: " << argv[0] << " Graph.root Both A 1  0   0 0 0   0 0 0 0 0" << endl;
      return -1;
   }

   FileName = argv[1];
   Type = argv[2];
   Cut = argv[3];
   Efficiency = atof(argv[4]);
   Point = argv[5];
   TrueA2ZZ = atof(argv[6]);
   TrueA3ZZ = atof(argv[7]);
   TrueA4ZZ = atof(argv[8]);
   TrueA2ZA = atof(argv[9]);
   TrueA3ZA = atof(argv[10]);
   TrueA4ZA = atof(argv[11]);
   TrueA2AA = atof(argv[12]);
   TrueA3AA = atof(argv[13]);

   double Factor = 1;
   if(Type == "Both" || Type == "BothS" || Type == "BothHalf" || Type == "BothF")
      Factor = 2;

   AVVBasis TrueA;
   TrueA.A1ZZ = 2;
   TrueA.A2ZZ = TrueA2ZZ;
   TrueA.A3ZZ = TrueA3ZZ;
   TrueA.A4ZZ = TrueA4ZZ;
   TrueA.A1ZA = 0;
   TrueA.A2ZA = TrueA2ZA;
   TrueA.A3ZA = TrueA3ZA;
   TrueA.A4ZA = TrueA4ZA;
   TrueA.A1AA = 0;
   TrueA.A2AA = TrueA2AA;
   TrueA.A3AA = TrueA3AA;
   TrueA.A4AA = 0;
   
   HiggsBasis TrueH(TrueA);
   WarsawBasis TrueW(TrueA);

   int Count = 10;
   int N[] = {50, 100, 200, 400, 600, 1000, 2000, 4000, 7000, 10000};

   TFile File(FileName.c_str(), "RECREATE");

   string Name1[3] = {"AVV", "Higgs", "Warsaw"};
   string Name2[2] = {"WithSquare", "NoSquare"};
   string Name3[3][10] =
      {{"A2ZZ", "A3ZZ", "A4ZZ", "A2ZA", "A3ZA", "A4ZA", "A2AA", "A3AA", "Fem", "Fee"},
      {"DeltaCZ", "CZB", "CZZ", "CZZD", "CZA", "CZAD", "CAA", "CAAD", "Fem", "Fee"},
      {"CT", "CH", "CWW", "CWWD", "CWB", "CWBD", "CBB", "CBBD", "Fem", "Fee"}};
   string Name4[256];
   for(int i = 0; i < 256; i++)
   {
      Name4[i] = "NNNNNNNN";
      if((i / 1) % 2 == 1)     Name4[i][0] = 'Y';
      if((i / 2) % 2 == 1)     Name4[i][1] = 'Y';
      if((i / 4) % 2 == 1)     Name4[i][2] = 'Y';
      if((i / 8) % 2 == 1)     Name4[i][3] = 'Y';
      if((i / 16) % 2 == 1)    Name4[i][4] = 'Y';
      if((i / 32) % 2 == 1)    Name4[i][5] = 'Y';
      if((i / 64) % 2 == 1)    Name4[i][6] = 'Y';
      if((i / 128) % 2 == 1)   Name4[i][7] = 'Y';
   }
   string Name5[2];
   for(int i = 0; i < 2; i++)
   {
      Name5[i] = "N";
      if((i / 1) % 2 == 1)     Name5[i][0] = 'Y';
   }

   TGraphErrors G[3][2][10][256][2];
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 2; j++)
      {
         for(int k = 0; k < 10; k++)
         {
            for(int l = 0; l < 256; l++)
            {
               for(int m = 0; m < 2; m++)
               {
                  string ID = Name1[i] + "_" + Name3[i][k] + "_" + Type + "_" + Cut + "_" + "Count" + "_" + Name4[l] + "_" + Name2[j] + "_" + Name5[m] + "_Point" + Point;
                  G[i][j][k][l][m].SetNameTitle(ID.c_str(), ID.c_str());
               }
            }
         }
      }
   }

   for(int iN = 0; iN < 10; iN++)
   {
      TFile IndividualFile(Form("Trees/Result%s_Point%s_%s_%d.root", Type.c_str(), Point.c_str(), Cut.c_str(), N[iN]));

      TTree *Tree = (TTree *)IndividualFile.Get("ResultTree");
      if(Tree == NULL)
      {
         IndividualFile.Close();
         continue;
      }

      float P[10], PError[10];
      float Status;
      float NoSquareMode;
      float Basis;
      float Sem, Bem, See, Bee;
      float Priors[20];

      Tree->SetBranchAddress("P1", &P[0]);   Tree->SetBranchAddress("P1Error", &PError[0]);
      Tree->SetBranchAddress("P2", &P[1]);   Tree->SetBranchAddress("P2Error", &PError[1]);
      Tree->SetBranchAddress("P3", &P[2]);   Tree->SetBranchAddress("P3Error", &PError[2]);
      Tree->SetBranchAddress("P4", &P[3]);   Tree->SetBranchAddress("P4Error", &PError[3]);
      Tree->SetBranchAddress("P5", &P[4]);   Tree->SetBranchAddress("P5Error", &PError[4]);
      Tree->SetBranchAddress("P6", &P[5]);   Tree->SetBranchAddress("P6Error", &PError[5]);
      Tree->SetBranchAddress("P7", &P[6]);   Tree->SetBranchAddress("P7Error", &PError[6]);
      Tree->SetBranchAddress("P8", &P[7]);   Tree->SetBranchAddress("P8Error", &PError[7]);
      Tree->SetBranchAddress("Fem", &P[8]);  Tree->SetBranchAddress("FemError", &PError[8]);
      Tree->SetBranchAddress("Fee", &P[9]);  Tree->SetBranchAddress("FeeError", &PError[9]);
      Tree->SetBranchAddress("Status", &Status);
      Tree->SetBranchAddress("NoSquareMode", &NoSquareMode);
      Tree->SetBranchAddress("Basis", &Basis);
      Tree->SetBranchAddress("Sem", &Sem);   Tree->SetBranchAddress("Bem", &Bem);
      Tree->SetBranchAddress("See", &See);   Tree->SetBranchAddress("Bee", &Bee);
      Tree->SetBranchAddress("Prior0", &Priors[0]);

      double Total[3][2][10][256][2] = {{{0}}};
      int Count[3][2][10][256][2] = {{{0}}};

      int EntryCount = Tree->GetEntries();
      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);

         if(Status < 2.5)
            continue;
         if(PError[0] > 900)   continue;
         if(PError[1] > 900)   continue;
         if(PError[2] > 900)   continue;
         if(PError[3] > 900)   continue;
         if(PError[4] > 900)   continue;
         if(PError[5] > 900)   continue;
         if(PError[6] > 900)   continue;
         if(PError[7] > 900)   continue;

         int IntBasis = (int)(Basis + 0.1);
         int IntNoSquareMode = (int)(NoSquareMode + 0.1);

         double TrueValue[10] = {0};
         if(IntBasis == 0)
         {
            TrueValue[0] = TrueA.A2ZZ;            TrueValue[1] = TrueA.A3ZZ;
            TrueValue[2] = TrueA.A4ZZ;            TrueValue[3] = TrueA.A2ZA;
            TrueValue[4] = TrueA.A3ZA;            TrueValue[5] = TrueA.A4ZA;
            TrueValue[6] = TrueA.A2AA;            TrueValue[7] = TrueA.A3AA;
            TrueValue[8] = Bem / (Sem + Bem);     TrueValue[9] = Bee / (See + Bee);
         }
         else if(IntBasis == 1)
         {
            TrueValue[0] = TrueH.DeltaCZ;         TrueValue[1] = TrueH.CZB;
            TrueValue[2] = TrueH.CZZ;             TrueValue[3] = TrueH.CZZD;
            TrueValue[4] = TrueH.CZA;             TrueValue[5] = TrueH.CZAD;
            TrueValue[6] = TrueH.CAA;             TrueValue[7] = TrueH.CAAD;
            TrueValue[8] = Bem / (Sem + Bem);     TrueValue[9] = Bee / (See + Bee);
         }
         else if(IntBasis == 2)
         {
            TrueValue[0] = TrueW.CT;              TrueValue[1] = TrueW.CH;
            TrueValue[2] = TrueW.CWW;             TrueValue[3] = TrueW.CWWD;
            TrueValue[4] = TrueW.CWB;             TrueValue[5] = TrueW.CWBD;
            TrueValue[6] = TrueW.CBB;             TrueValue[7] = TrueW.CBBD;
            TrueValue[8] = Bem / (Sem + Bem);     TrueValue[9] = Bee / (See + Bee);
         }
         else
            continue;

         if(P[2] < -700)   // Hmm?
            continue;

         int FloatIndex = 0;
         if(PError[0] > 0)   FloatIndex = FloatIndex + 1;
         if(PError[1] > 0)   FloatIndex = FloatIndex + 2;
         if(PError[2] > 0)   FloatIndex = FloatIndex + 4;
         if(PError[3] > 0)   FloatIndex = FloatIndex + 8;
         if(PError[4] > 0)   FloatIndex = FloatIndex + 16;
         if(PError[5] > 0)   FloatIndex = FloatIndex + 32;
         if(PError[6] > 0)   FloatIndex = FloatIndex + 64;
         if(PError[7] > 0)   FloatIndex = FloatIndex + 128;

         int PriorIndex = 0;
         if(Priors[0] > 0)   PriorIndex = PriorIndex + 1;

         for(int i = 0; i < 10; i++)
         {
            Total[IntBasis][IntNoSquareMode][i][FloatIndex][PriorIndex] = Total[IntBasis][IntNoSquareMode][i][FloatIndex][PriorIndex] + fabs(P[i] - TrueValue[i]);
            Count[IntBasis][IntNoSquareMode][i][FloatIndex][PriorIndex] = Count[IntBasis][IntNoSquareMode][i][FloatIndex][PriorIndex] + 1;
         }
      }

      for(int i = 0; i < 3; i++)
      {
         for(int j = 0; j < 2; j++)
         {
            for(int k = 0; k < 10; k++)
            {
               for(int l = 0; l < 256; l++)
               {
                  for(int m = 0; m < 2; m++)
                  {
                     if(Count[i][j][k][l][m] == 0)
                        continue;

                     int Index = G[i][j][k][l][m].GetN();

                     G[i][j][k][l][m].SetPoint(Index, N[iN] * Factor, Total[i][j][k][l][m] / Count[i][j][k][l][m] * sqrt(PI / 2));
                  }
               }
            }
         }
      }

      IndividualFile.Close();
   }

   File.cd();

   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 2; j++)
      {
         for(int k = 0; k < 10; k++)
         {
            for(int l = 0; l < 256; l++)
            {
               for(int m = 0; m < 2; m++)
               {
                  if(G[i][j][k][l][m].GetN() == 0)
                     continue;

                  G[i][j][k][l][m].Write();
               }
            }
         }
      }
   }

   File.Close();

   return 0;
}




