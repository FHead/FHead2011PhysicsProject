//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
//---------------------------------------------------------------------------
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TH2D.h"
//---------------------------------------------------------------------------
#include "Code/DrawRandom.h"
//---------------------------------------------------------------------------
#include "AngleConversion.h"
#include "Lists.h"
#include "Cuts.h"
//---------------------------------------------------------------------------
#include "FitClass.h"
#include "M4lSpectrum.h"
#include "FileIO.h"
//---------------------------------------------------------------------------
int main(int argc, char *argv[]);
vector<double> SumVector(vector<double> &V1, vector<double> &V2);
void SetAlias(TTree &ResultTree);
//---------------------------------------------------------------------------
#define PI 3.14159265358979323846264338327950288479716939937510
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   srand(31426);

   string SignalFileName[2]     = {"EventF.root", "Dummy.root"};
   string BackgroundFileName[2] = {"EventF.root", "Dummy.root"};
   string ZJFileName[2]         = {"EventF.root", "Dummy.root"};
   string ggZZFileName[2]       = {"EventF.root", "Dummy.root"};

   if(argc < 17)
   {
      cerr << "Usage: " << argv[0]
         << " SignalRootFile7TeV BackgroundRootFile7TeV ZJRootFile7TeV ggZZRootFile7TeV"
         << " SignalRootFile8TeV BackgroundRootFile8TeV ZJRootFile8TeV ggZZRootFile8TeV"
         << " A2ZZ A3ZZ A2ZA A3ZA A2AA A3AA A1L1ZZ ToyNumber"
         << endl;
      return -1;
   }

   SignalFileName[1]     = argv[1];
   BackgroundFileName[1] = argv[2];
   ZJFileName[1]         = argv[3];
   ggZZFileName[1]       = argv[4];
   SignalFileName[0]     = argv[5];
   BackgroundFileName[0] = argv[6];
   ZJFileName[0]         = argv[7];
   ggZZFileName[0]       = argv[8];

   double A2ZZ = atof(argv[9]);
   double A3ZZ = atof(argv[10]);
   double A2ZA = atof(argv[11]);
   double A3ZA = atof(argv[12]);
   double A2AA = atof(argv[13]);
   double A3AA = atof(argv[14]);
   double A1L1ZZ = atof(argv[15]);
   double A1LQZZ = 0;

   int TargetToyNumber = atoi(argv[16]);

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   vector<FitResultSummary> Results;

   PsFileHelper PsFile("FitResult.ps");

   vector<SingleEvent> EM[2], ME[2], EE[2], MM[2];

   // 8 TeV Yield
   vector<double> NS8 = ListToVector(4, 4.359, 3.385, 3.066, 5.983);
   vector<double> NSSigma8 = ListToVector(4, 0.11, 0.11, 0.11, 0.11);
   vector<double> NB8 = ListToVector(4, 3.523, 2.018, 1.785, 4.635);
   vector<double> NBSigma8 = ListToVector(4, 0.048, 0.048, 0.047, 0.047);
   vector<double> NZJ8 = ListToVector(4, 0.721, 2.077, 1.691, 0.823);
   vector<double> NZJSigma8 = ListToVector(4, 0.40, 0.40, 0.40, 0.40);
   vector<double> NggZZ8 = ListToVector(4, 0.185, 0.149, 0.120, 0.250);
   vector<double> NggZZSigma8 = ListToVector(4, 0.25, 0.25, 0.25, 0.25);

   // 8 TeV Yield for fa3 = 0.5 from sync toys
   /*
   vector<double> NS8 = ListToVector(4, 4.156, 3.227, 2.344, 4.897);
   vector<double> NSSigma8 = ListToVector(4, 0.11, 0.11, 0.11, 0.11);
   vector<double> NB8 = ListToVector(4, 3.446, 1.974, 1.652, 4.297);
   vector<double> NBSigma8 = ListToVector(4, 0.048, 0.048, 0.047, 0.047);
   vector<double> NZJ8 = ListToVector(4, 0.689, 1.984, 1.614, 0.740);
   vector<double> NZJSigma8 = ListToVector(4, 0.40, 0.40, 0.40, 0.40);
   vector<double> NggZZ8 = ListToVector(4, 0.169, 0.137, 0.084, 0.205);
   vector<double> NggZZSigma8 = ListToVector(4, 0.25, 0.25, 0.25, 0.25);
   */

   vector<double> NS8Prime = NS8;   // Primes combine EM and ME together
   vector<double> NB8Prime = NB8;
   vector<double> NZJ8Prime = NZJ8;
   vector<double> NggZZ8Prime = NggZZ8;

   // NS8Prime[0] = NS8[0] + NS8[1];            NS8Prime[1] = 0;
   // NB8Prime[0] = NB8[0] + NB8[1];            NB8Prime[1] = 0;
   // NZJ8Prime[0] = NZJ8[0] + NZJ8[1];         NZJ8Prime[1] = 0;
   // NggZZ8Prime[0] = NggZZ8[0] + NggZZ8[1];   NggZZ8Prime[1] = 0;

   // 7 TeV Yield
   vector<double> NS7 = ListToVector(4, 0.946, 0.743, 0.701, 1.127);
   vector<double> NSSigma7 = ListToVector(4, 0.11, 0.11, 0.11, 0.11);
   vector<double> NB7 = ListToVector(4, 0.873, 0.547, 0.518, 1.075);
   vector<double> NBSigma7 = ListToVector(4, 0.048, 0.048, 0.047, 0.047);
   vector<double> NZJ7 = ListToVector(4, 0.110, 0.583, 0.406, 0.167);
   vector<double> NZJSigma7 = ListToVector(4, 0.40, 0.40, 0.40, 0.40);
   vector<double> NggZZ7 = ListToVector(4, 0.0271, 0.0205, 0.0210, 0.0367);
   vector<double> NggZZSigma7 = ListToVector(4, 0.25, 0.25, 0.25, 0.25);

   // 7 TeV Yield for fa3 = 0.5 from sync toys
   /*
   vector<double> NS7 = ListToVector(4, 0.887, 0.696, 0.519, 1.014);
   vector<double> NSSigma7 = ListToVector(4, 0.11, 0.11, 0.11, 0.11);
   vector<double> NB7 = ListToVector(4, 0.833, 0.522, 0.446, 0.991);
   vector<double> NBSigma7 = ListToVector(4, 0.048, 0.048, 0.047, 0.047);
   vector<double> NZJ7 = ListToVector(4, 0.110, 0.586, 0.366, 0.107);
   vector<double> NZJSigma7 = ListToVector(4, 0.40, 0.40, 0.40, 0.40);
   vector<double> NggZZ7 = ListToVector(4, 0.0205, 0.0155, 0.015, 0.038);
   vector<double> NggZZSigma7 = ListToVector(4, 0.25, 0.25, 0.25, 0.25);
   */

   vector<double> NS7Prime = NS7;
   vector<double> NB7Prime = NB7;
   vector<double> NZJ7Prime = NZJ7;
   vector<double> NggZZ7Prime = NggZZ7;

   // NS7Prime[0] = NS7[0] + NS7[1];            NS7Prime[1] = 0;
   // NB7Prime[0] = NB7[0] + NB7[1];            NB7Prime[1] = 0;
   // NZJ7Prime[0] = NZJ7[0] + NZJ7[1];         NZJ7Prime[1] = 0;
   // NggZZ7Prime[0] = NggZZ7[0] + NggZZ7[1];   NggZZ7Prime[1] = 0;

   vector<FitConfiguration> Configurations;
   for(int i = 0; i <= 127; i++)
   {
      if(i != 0)
         continue;

      string As = "NNNNNNNN";
      if((i / 1) % 2 == 1)    As[0] = 'Y';
      if((i / 2) % 2 == 1)    As[1] = 'Y';
      if((i / 4) % 2 == 1)    As[2] = 'Y';
      if((i / 8) % 2 == 1)    As[3] = 'Y';
      if((i / 16) % 2 == 1)   As[4] = 'Y';
      if((i / 32) % 2 == 1)   As[5] = 'Y';
      if((i / 64) % 2 == 1)   As[6] = 'Y';
      if((i / 128) % 2 == 1)  As[7] = 'Y';   // LQZZ - not really applicable to us

      string Phases = "NNNNNNNN";

      string Counts = "YYYY";   // EM, ME, EE, MM
      string Fs = "YYYYNNNNNNNN";   // FB(EM, ME, EE, MM), FZJ(EM, ME, EE, MM), FggZZ(EM, ME, EE, MM)

      Configurations.push_back(FitConfiguration("N",                                 /* Weighted dataset! */
            As, Phases, Counts, Counts,
            Fs, Fs, "YYNNNYN", "Y",                                                  /* What to float */
            true,                                                                    /* Guess initial fraction */
         ListToVector(8, A2ZZ, A3ZZ, A2ZA, A3ZA, A2AA, A3AA, A1L1ZZ, A1LQZZ),        /* Ratios */
         ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0),                                    /* Phases */
         ListToVector(4, NS7Prime[0] + NB7Prime[0] + NZJ7Prime[0] + NggZZ7Prime[0], NS7Prime[1] + NB7Prime[1] + NZJ7Prime[1] + NggZZ7Prime[1],
            NS7Prime[2] + NB7Prime[2] + NZJ7Prime[2] + NggZZ7Prime[2], NS7Prime[3] + NB7Prime[3] + NZJ7Prime[3] + NggZZ7Prime[3]),   /* Event Counts */
         ListToVector(4, NS8Prime[0] + NB8Prime[0] + NZJ8Prime[0] + NggZZ8Prime[0], NS8Prime[1] + NB8Prime[1] + NZJ8Prime[1] + NggZZ8Prime[1],
            NS8Prime[2] + NB8Prime[2] + NZJ8Prime[2] + NggZZ8Prime[2], NS8Prime[3] + NB8Prime[3] + NZJ8Prime[3] + NggZZ8Prime[3]),   /* Event Counts */
         ListToVector(12, ((Fs[0] == 'Y') ? 0.5 : 0), ((Fs[1] == 'Y') ? 0.5 : 0),
            ((Fs[2] == 'Y') ? 0.5 : 0), ((Fs[3] == 'Y') ? 0.5 : 0),
            ((Fs[4] == 'Y') ? 0.15 : 0), ((Fs[5] == 'Y') ? 0.25 : 0),
            ((Fs[6] == 'Y') ? 0.25 : 0), ((Fs[7] == 'Y') ? 0.15 : 0),
            ((Fs[8] == 'Y') ? 0.12 : 0), ((Fs[9] == 'Y') ? 0.12 : 0),
            ((Fs[10] == 'Y') ? 0.12 : 0), ((Fs[11] == 'Y') ? 0.12 : 0)),             /* Background fraction */
         ListToVector(12, ((Fs[0] == 'Y') ? 0.5 : 0), ((Fs[1] == 'Y') ? 0.5 : 0),
            ((Fs[2] == 'Y') ? 0.5 : 0), ((Fs[3] == 'Y') ? 0.5 : 0),
            ((Fs[4] == 'Y') ? 0.15 : 0), ((Fs[5] == 'Y') ? 0.25 : 0),
            ((Fs[6] == 'Y') ? 0.25 : 0), ((Fs[7] == 'Y') ? 0.15 : 0),
            ((Fs[8] == 'Y') ? 0.12 : 0), ((Fs[9] == 'Y') ? 0.12 : 0),
            ((Fs[10] == 'Y') ? 0.12 : 0), ((Fs[11] == 'Y') ? 0.12 : 0)),             /* Background fraction */
         ListToVector(7, 0, 0, 0, 0, 0, 0, 0),                                       /* Systematics */
         NS7Prime, NS8Prime, NSSigma7, NSSigma8,
         NB7Prime, NB8Prime, NBSigma7, NBSigma8,
         NZJ7Prime, NZJ8Prime, NZJSigma7, NZJSigma8,
         NggZZ7Prime, NggZZ8Prime, NggZZSigma7, NggZZSigma8,                         /* Constraints */
         1));                                                                        /* Mu */
   }

   bool HasBadEvent[8] = {0};
   bool AnyHasBadEvent = false;

   TFile OutputFile("OutputFile.root", "RECREATE");

   int BackgroundCounter = 0;

   bool FirstFit = true;
   bool Good = true;
   while(Good == true)
   {
      int Count = -1;

      ReadEvents(EM[1], ME[1], EE[1], MM[1], SignalFileName[1], false, DEFAULT_PROCESS, 1, true,  false, TargetToyNumber, false, true, true, 1, false);
      ReadEvents(EM[0], ME[0], EE[0], MM[0], SignalFileName[0], false, DEFAULT_PROCESS, 1, false, false, TargetToyNumber, false, true, true, 1, false);
      
      for(int i = 0; i < (int)EM[0].size(); i++)
         Fits.AddPoint(EM[0][i]);
      for(int i = 0; i < (int)ME[0].size(); i++)
         Fits.AddPoint(ME[0][i]);
      for(int i = 0; i < (int)EE[0].size(); i++)
         Fits.AddPoint(EE[0][i]);
      for(int i = 0; i < (int)MM[0].size(); i++)
         Fits.AddPoint(MM[0][i]);
      for(int i = 0; i < (int)EM[1].size(); i++)
         Fits.AddPoint(EM[1][i]);
      for(int i = 0; i < (int)ME[1].size(); i++)
         Fits.AddPoint(ME[1][i]);
      for(int i = 0; i < (int)EE[1].size(); i++)
         Fits.AddPoint(EE[1][i]);
      for(int i = 0; i < (int)MM[1].size(); i++)
         Fits.AddPoint(MM[1][i]);

      Fits.SignalStateCount[1][0] = NS7Prime[0];
      Fits.SignalStateCount[1][1] = NS7Prime[1];
      Fits.SignalStateCount[1][2] = NS7Prime[2];
      Fits.SignalStateCount[1][3] = NS7Prime[3];
      Fits.SignalStateCount[0][0] = NS8Prime[0];
      Fits.SignalStateCount[0][1] = NS8Prime[1];
      Fits.SignalStateCount[0][2] = NS8Prime[2];
      Fits.SignalStateCount[0][3] = NS8Prime[3];
      Fits.BackgroundStateCount[1][0] = NB7Prime[0];
      Fits.BackgroundStateCount[1][1] = NB7Prime[1];
      Fits.BackgroundStateCount[1][2] = NB7Prime[2];
      Fits.BackgroundStateCount[1][3] = NB7Prime[3];
      Fits.BackgroundStateCount[0][0] = NB8Prime[0];
      Fits.BackgroundStateCount[0][1] = NB8Prime[1];
      Fits.BackgroundStateCount[0][2] = NB8Prime[2];
      Fits.BackgroundStateCount[0][3] = NB8Prime[3];
      Fits.ZJStateCount[1][0] = NZJ7Prime[0];
      Fits.ZJStateCount[1][1] = NZJ7Prime[1];
      Fits.ZJStateCount[1][2] = NZJ7Prime[2];
      Fits.ZJStateCount[1][3] = NZJ7Prime[3];
      Fits.ZJStateCount[0][0] = NZJ8Prime[0];
      Fits.ZJStateCount[0][1] = NZJ8Prime[1];
      Fits.ZJStateCount[0][2] = NZJ8Prime[2];
      Fits.ZJStateCount[0][3] = NZJ8Prime[3];
      Fits.ggZZStateCount[1][0] = NggZZ7Prime[0];
      Fits.ggZZStateCount[1][1] = NggZZ7Prime[1];
      Fits.ggZZStateCount[1][2] = NggZZ7Prime[2];
      Fits.ggZZStateCount[1][3] = NggZZ7Prime[3];
      Fits.ggZZStateCount[0][0] = NggZZ8Prime[0];
      Fits.ggZZStateCount[0][1] = NggZZ8Prime[1];
      Fits.ggZZStateCount[0][2] = NggZZ8Prime[2];
      Fits.ggZZStateCount[0][3] = NggZZ8Prime[3];
      
      for(int i = 0; i < 8; i++)
         if(HasBadEvent[i] == true)
            AnyHasBadEvent = true;

      cout << "S8 = " << Fits.SignalStateCount[0][0] << " " << Fits.SignalStateCount[0][1]
         << " " << Fits.SignalStateCount[0][2] << " " << Fits.SignalStateCount[0][3] << endl;
      cout << "B8 = " << Fits.BackgroundStateCount[0][0] << " " << Fits.BackgroundStateCount[0][1]
         << " " << Fits.BackgroundStateCount[0][2] << " " << Fits.BackgroundStateCount[0][3] << endl;
      cout << "Z8 = " << Fits.ZJStateCount[0][0] << " " << Fits.ZJStateCount[0][1]
         << " " << Fits.ZJStateCount[0][2] << " " << Fits.ZJStateCount[0][3] << endl;
      cout << "G8 = " << Fits.ggZZStateCount[0][0] << " " << Fits.ggZZStateCount[0][1]
         << " " << Fits.ggZZStateCount[0][2] << " " << Fits.ggZZStateCount[0][3] << endl;
      cout << "S7 = " << Fits.SignalStateCount[1][0] << " " << Fits.SignalStateCount[1][1]
         << " " << Fits.SignalStateCount[1][2] << " " << Fits.SignalStateCount[1][3] << endl;
      cout << "B7 = " << Fits.BackgroundStateCount[1][0] << " " << Fits.BackgroundStateCount[1][1]
         << " " << Fits.BackgroundStateCount[1][2] << " " << Fits.BackgroundStateCount[1][3] << endl;
      cout << "Z7 = " << Fits.ZJStateCount[1][0] << " " << Fits.ZJStateCount[1][1]
         << " " << Fits.ZJStateCount[1][2] << " " << Fits.ZJStateCount[1][3] << endl;
      cout << "G7 = " << Fits.ggZZStateCount[1][0] << " " << Fits.ggZZStateCount[1][1]
         << " " << Fits.ggZZStateCount[1][2] << " " << Fits.ggZZStateCount[1][3] << endl;

      for(int j = 0; j < 2; j++)
      {
         for(int i = 0; i < 4; i++)
         {
            if(Fits.SignalStateCount[j][i] < 0)
               Good = false;
            if(Fits.BackgroundStateCount[j][i] < 0)
               Good = false;
            if(Fits.ZJStateCount[j][i] < 0)
               Good = false;
            if(Fits.ggZZStateCount[j][i] < 0)
               Good = false;
         }
      }
      if(Good == false)
         break;

      for(int iC = 0; iC < (int)Configurations.size(); iC++)
      {
         const int Tries = 1;
         FitResultSummary ResultTemp[Tries];

         Configurations[iC].SetFloatNs("NNNNNNN");
         Configurations[iC].SetFloatFractions(0, "NNNNNNNNNNNN");
         Configurations[iC].SetFloatFractions(1, "NNNNNNNNNNNN");
         Configurations[iC].SetFloatMu("Y");
         ResultTemp[0] = Fits.DoFit(Configurations[iC]);
         
         Configurations[iC].MuInitialValue = ResultTemp[0].Mu;
         
         Configurations[iC].SetFloatNs("NNNNNNN");
         Configurations[iC].SetFloatFractions(0, "YYYYYYYYYYYY");
         Configurations[iC].SetFloatFractions(1, "YYYYYYYYYYYY");
         Configurations[iC].SetFloatMu("N");
         ResultTemp[0] = Fits.DoFit(Configurations[iC]);

         Configurations[iC].MuInitialValue = ResultTemp[0].Mu;
         Configurations[iC].SetInitialFractions(1, ListToVector(12,
            ResultTemp[0].F[1][0], ResultTemp[0].F[1][1], ResultTemp[0].F[1][2], ResultTemp[0].F[1][3],
            ResultTemp[0].FZJ[1][0], ResultTemp[0].FZJ[1][1], ResultTemp[0].FZJ[1][2], ResultTemp[0].FZJ[1][3],
            ResultTemp[0].FggZZ[1][0], ResultTemp[0].FggZZ[1][1], ResultTemp[0].FggZZ[1][2], ResultTemp[0].FggZZ[1][3]));
         Configurations[iC].SetInitialFractions(0, ListToVector(12,
            ResultTemp[0].F[0][0], ResultTemp[0].F[0][1], ResultTemp[0].F[0][2], ResultTemp[0].F[0][3],
            ResultTemp[0].FZJ[0][0], ResultTemp[0].FZJ[0][1], ResultTemp[0].FZJ[0][2], ResultTemp[0].FZJ[0][3],
            ResultTemp[0].FggZZ[0][0], ResultTemp[0].FggZZ[0][1], ResultTemp[0].FggZZ[0][2], ResultTemp[0].FggZZ[0][3]));
         
         Configurations[iC].SetFloatNs("YYNNNYN");
         Configurations[iC].SetFloatFractions(0, "NNNNNNNNNNNN");
         Configurations[iC].SetFloatFractions(1, "NNNNNNNNNNNN");
         Configurations[iC].SetGuessF(false);
         Configurations[iC].SetFloatMu("N");
         ResultTemp[0] = Fits.DoFit(Configurations[iC]);
 
         Configurations[iC].MuInitialValue = ResultTemp[0].Mu;
         Configurations[iC].SetInitialFractions(1, ListToVector(12,
            ResultTemp[0].F[1][0], ResultTemp[0].F[1][1], ResultTemp[0].F[1][2], ResultTemp[0].F[1][3],
            ResultTemp[0].FZJ[1][0], ResultTemp[0].FZJ[1][1], ResultTemp[0].FZJ[1][2], ResultTemp[0].FZJ[1][3],
            ResultTemp[0].FggZZ[1][0], ResultTemp[0].FggZZ[1][1], ResultTemp[0].FggZZ[1][2], ResultTemp[0].FggZZ[1][3]));
         Configurations[iC].SetInitialFractions(0, ListToVector(12,
            ResultTemp[0].F[0][0], ResultTemp[0].F[0][1], ResultTemp[0].F[0][2], ResultTemp[0].F[0][3],
            ResultTemp[0].FZJ[0][0], ResultTemp[0].FZJ[0][1], ResultTemp[0].FZJ[0][2], ResultTemp[0].FZJ[0][3],
            ResultTemp[0].FggZZ[0][0], ResultTemp[0].FggZZ[0][1], ResultTemp[0].FggZZ[0][2], ResultTemp[0].FggZZ[0][3]));
         Configurations[iC].SetInitialNs(vector<double>(ResultTemp[0].N, ResultTemp[0].N + 7));
         
         Configurations[iC].SetFloatNs("YYNNNYN");
         Configurations[iC].SetFloatFractions(0, "YYYYYYYYYYYY");
         Configurations[iC].SetFloatFractions(1, "YYYYYYYYYYYY");
         Configurations[iC].SetGuessF(false);
         Configurations[iC].SetFloatMu("Y");
         ResultTemp[0] = Fits.DoFit(Configurations[iC]);
         
         // for(int iT = 0; iT < Tries; iT++)
         // {
         //    FitConfiguration Current = Configurations[iC];
         //    if(Current.FloatAA[0] == true)   Current.AAInitialValue[0] = DrawRandom(-10, 10);
         //    if(Current.FloatAA[1] == true)   Current.AAInitialValue[1] = DrawRandom(-15, 15);
         //    Current.MuInitialValue = iT * 0.25 + 1.2;
         //    ResultTemp[iT] = Fits.DoFit(Current);
         // }

         int BestNLLIndex = 0;
         // for(int iT = 1; iT < Tries; iT++)
         // {
         //    // if(ResultTemp[iT].BestNLLNoPenalty < 80)
         //    //    continue;
         //    if(ResultTemp[iT].BestNLLNoPenalty < ResultTemp[BestNLLIndex].BestNLLNoPenalty)
         //       BestNLLIndex = iT;
         // }

         for(int iT = 0; iT < Tries; iT++)
            cout << iT << " " << ResultTemp[iT].BestNLL << endl;
         cout << "iC = " << iC << ", BestNLLIndex = " << BestNLLIndex
            << ", (A2, A3) = (" << ResultTemp[BestNLLIndex].AA[0] << ", " << ResultTemp[BestNLLIndex].AA[1] << ")" << endl;

         Results.push_back(ResultTemp[BestNLLIndex]);
      }
      FitCount = FitCount + 1;

      Fits.ClearPoints();

      break;
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   string BranchList = "";
   BranchList = BranchList + "A2ZZA1ZZ:A2ZZPhase:A3ZZA1ZZ:A3ZZPhase";                          // 4
   BranchList = BranchList + ":A2ZAA1ZZ:A2ZAPhase:A3ZAA1ZZ:A3ZAPhase";                         // 8
   BranchList = BranchList + ":A2AAA1ZZ:A2AAPhase:A3AAA1ZZ:A3AAPhase";                         // 12
   BranchList = BranchList + ":N1:N2:N3:N4:N5:N6:N7";                                          // 19
   BranchList = BranchList + ":Fem7:Fme7:Fee7:Fmm7";                                           // 23
   BranchList = BranchList + ":Fem8:Fme8:Fee8:Fmm8";                                           // 27
   BranchList = BranchList + ":FZJem7:FZJme7:FZJee7:FZJmm7";                                   // 31
   BranchList = BranchList + ":FZJem8:FZJme8:FZJee8:FZJmm8";                                   // 35
   BranchList = BranchList + ":FggZZem7:FggZZme7:FggZZee7:FggZZmm7";                           // 39
   BranchList = BranchList + ":FggZZem8:FggZZme8:FggZZee8:FggZZmm8";                           // 43
   BranchList = BranchList + ":A2ZZA1ZZError:A2ZZPhaseError:A3ZZA1ZZError:A3ZZPhaseError";     // 47
   BranchList = BranchList + ":A2ZAA1ZZError:A2ZAPhaseError:A3ZAA1ZZError:A3ZAPhaseError";     // 51
   BranchList = BranchList + ":A2AAA1ZZError:A2AAPhaseError:A3AAA1ZZError:A3AAPhaseError";     // 55
   BranchList = BranchList + ":N1Error:N2Error:N3Error:N4Error:N5Error:N6Error:N7Error";       // 62
   BranchList = BranchList + ":FemError7:FmeError7:FeeError7:FmmError7";                       // 66
   BranchList = BranchList + ":FemError8:FmeError8:FeeError8:FmmError8";                       // 70
   BranchList = BranchList + ":FZJemError7:FZJmeError7:FZJeeError7:FZJmmError7";               // 74
   BranchList = BranchList + ":FZJemError8:FZJmeError8:FZJeeError8:FZJmmError8";               // 78
   BranchList = BranchList + ":FggZZemError7:FggZZmeError7:FggZZeeError7:FggZZmmError7";       // 82
   BranchList = BranchList + ":FggZZemError8:FggZZmeError8:FggZZeeError8:FggZZmmError8";       // 86
   BranchList = BranchList + ":EDM:Status";                                                    // 88
   BranchList = BranchList + ":Sem7:Sme7:See7:Smm7";                                           // 92
   BranchList = BranchList + ":Sem8:Sme8:See8:Smm8";                                           // 96
   BranchList = BranchList + ":Bem7:Bme7:Bee7:Bmm7";                                           // 100
   BranchList = BranchList + ":Bem8:Bme8:Bee8:Bmm8";                                           // 104
   BranchList = BranchList + ":ZJem7:ZJme7:ZJee7:ZJmm7";                                       // 108
   BranchList = BranchList + ":ZJem8:ZJme8:ZJee8:ZJmm8";                                       // 112
   BranchList = BranchList + ":ggZZem7:ggZZme7:ggZZee7:ggZZmm7";                               // 116
   BranchList = BranchList + ":ggZZem8:ggZZme8:ggZZee8:ggZZmm8";                               // 120
   BranchList = BranchList + ":RatioFloats:NFloats:TruthNLL:BestNLL:BestNLLNoPenalty";         // 125
   BranchList = BranchList + ":Mu:MuError";                                                    // 127
   BranchList = BranchList + ":A1L1ZZ:A1L1ZZPhase:A1LQZZ:A1LQZZPhase";                         // 131
   BranchList = BranchList + ":A1L1ZZError:A1L1ZZPhaseError:A1LQZZError:A1LQZZPhaseError";     // 135
   BranchList = BranchList + ":Toy:Good";                                                      // 137
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[150];
      Array[0]   = Results[i].AA[0];          Array[43]  = Results[i].AAError[0];
      Array[1]   = Results[i].Phase[0];       Array[44]  = Results[i].PhaseError[0];
      Array[2]   = Results[i].AA[1];          Array[45]  = Results[i].AAError[1];
      Array[3]   = Results[i].Phase[1];       Array[46]  = Results[i].PhaseError[1];
      Array[4]   = Results[i].AA[2];          Array[47]  = Results[i].AAError[2];
      Array[5]   = Results[i].Phase[2];       Array[48]  = Results[i].PhaseError[2];
      Array[6]   = Results[i].AA[3];          Array[49]  = Results[i].AAError[3];
      Array[7]   = Results[i].Phase[3];       Array[50]  = Results[i].PhaseError[3];
      Array[8]   = Results[i].AA[4];          Array[51]  = Results[i].AAError[4];
      Array[9]   = Results[i].Phase[4];       Array[52]  = Results[i].PhaseError[4];
      Array[10]  = Results[i].AA[5];          Array[53]  = Results[i].AAError[5];
      Array[11]  = Results[i].Phase[5];       Array[54]  = Results[i].PhaseError[5];
      Array[12]  = Results[i].N[0];           Array[55]  = Results[i].NError[0];
      Array[13]  = Results[i].N[1];           Array[56]  = Results[i].NError[1];
      Array[14]  = Results[i].N[2];           Array[57]  = Results[i].NError[2];
      Array[15]  = Results[i].N[3];           Array[58]  = Results[i].NError[3];
      Array[16]  = Results[i].N[4];           Array[59]  = Results[i].NError[4];
      Array[17]  = Results[i].N[5];           Array[60]  = Results[i].NError[5];
      Array[18]  = Results[i].N[6];           Array[61]  = Results[i].NError[6];
      Array[19]  = Results[i].F[1][0];        Array[62]  = Results[i].FError[1][0];
      Array[20]  = Results[i].F[1][1];        Array[63]  = Results[i].FError[1][1];
      Array[21]  = Results[i].F[1][2];        Array[64]  = Results[i].FError[1][2];
      Array[22]  = Results[i].F[1][3];        Array[65]  = Results[i].FError[1][3];
      Array[23]  = Results[i].F[0][0];        Array[66]  = Results[i].FError[0][0];
      Array[24]  = Results[i].F[0][1];        Array[67]  = Results[i].FError[0][1];
      Array[25]  = Results[i].F[0][2];        Array[68]  = Results[i].FError[0][2];
      Array[26]  = Results[i].F[0][3];        Array[69]  = Results[i].FError[0][3];
      Array[27]  = Results[i].FZJ[1][0];      Array[70]  = Results[i].FZJError[1][0];
      Array[28]  = Results[i].FZJ[1][1];      Array[71]  = Results[i].FZJError[1][1];
      Array[29]  = Results[i].FZJ[1][2];      Array[72]  = Results[i].FZJError[1][2];
      Array[30]  = Results[i].FZJ[1][3];      Array[73]  = Results[i].FZJError[1][3];
      Array[31]  = Results[i].FZJ[0][0];      Array[74]  = Results[i].FZJError[0][0];
      Array[32]  = Results[i].FZJ[0][1];      Array[75]  = Results[i].FZJError[0][1];
      Array[33]  = Results[i].FZJ[0][2];      Array[76]  = Results[i].FZJError[0][2];
      Array[34]  = Results[i].FZJ[0][3];      Array[77]  = Results[i].FZJError[0][3];
      Array[35]  = Results[i].FggZZ[1][0];    Array[78]  = Results[i].FggZZError[1][0];
      Array[36]  = Results[i].FggZZ[1][1];    Array[79]  = Results[i].FggZZError[1][1];
      Array[37]  = Results[i].FggZZ[1][2];    Array[80]  = Results[i].FggZZError[1][2];
      Array[38]  = Results[i].FggZZ[1][3];    Array[81]  = Results[i].FggZZError[1][3];
      Array[39]  = Results[i].FggZZ[0][0];    Array[82]  = Results[i].FggZZError[0][0];
      Array[40]  = Results[i].FggZZ[0][1];    Array[83]  = Results[i].FggZZError[0][1];
      Array[41]  = Results[i].FggZZ[0][2];    Array[84]  = Results[i].FggZZError[0][2];
      Array[42]  = Results[i].FggZZ[0][3];    Array[85]  = Results[i].FggZZError[0][3];

      Array[86]  = Results[i].EDM;
      Array[87]  = Results[i].FitStatus;

      Array[88]  = Results[i].S[1][0];        Array[92]  = Results[i].S[0][0];
      Array[89]  = Results[i].S[1][1];        Array[93]  = Results[i].S[0][1];
      Array[90]  = Results[i].S[1][2];        Array[94]  = Results[i].S[0][2];
      Array[91]  = Results[i].S[1][3];        Array[95]  = Results[i].S[0][3];

      Array[96]  = Results[i].B[1][0];        Array[100] = Results[i].B[0][0];
      Array[97]  = Results[i].B[1][1];        Array[101] = Results[i].B[0][1];
      Array[98]  = Results[i].B[1][2];        Array[102] = Results[i].B[0][2];
      Array[99]  = Results[i].B[1][3];        Array[103] = Results[i].B[0][3];

      Array[104] = Results[i].ZJ[1][0];       Array[108] = Results[i].ZJ[0][0];
      Array[105] = Results[i].ZJ[1][1];       Array[109] = Results[i].ZJ[0][1];
      Array[106] = Results[i].ZJ[1][2];       Array[110] = Results[i].ZJ[0][2];
      Array[107] = Results[i].ZJ[1][3];       Array[111] = Results[i].ZJ[0][3];

      Array[112] = Results[i].ggZZ[1][0];     Array[116] = Results[i].ggZZ[0][0];
      Array[113] = Results[i].ggZZ[1][1];     Array[117] = Results[i].ggZZ[0][1];
      Array[114] = Results[i].ggZZ[1][2];     Array[118] = Results[i].ggZZ[0][2];
      Array[115] = Results[i].ggZZ[1][3];     Array[119] = Results[i].ggZZ[0][3];

      Array[120] = 0;
      Array[121] = 0;

      Array[122] = Results[i].TruthNLL;
      Array[123] = Results[i].BestNLL;
      Array[124] = Results[i].BestNLLNoPenalty;

      Array[125] = Results[i].Mu;
      Array[126] = Results[i].MuError;

      Array[127] = Results[i].AA[6];          Array[131] = Results[i].AAError[6];
      Array[128] = Results[i].Phase[6];       Array[132] = Results[i].PhaseError[6];
      Array[129] = Results[i].AA[7];          Array[133] = Results[i].AAError[7];
      Array[130] = Results[i].Phase[7];       Array[134] = Results[i].PhaseError[7];

      Array[135] = TargetToyNumber;
      Array[136] = !AnyHasBadEvent;

      OutputTree.Fill(Array);
   }

   SetAlias(OutputTree);

   OutputTree.SetMarkerStyle(20);

   OutputFile.cd();

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}
//---------------------------------------------------------------------------
vector<double> SumVector(vector<double> &V1, vector<double> &V2)
{
   vector<double> Answer(min(V1.size(), V2.size()));
   for(int i = 0; i < (int)Answer.size(); i++)
      Answer[i] = V1[i] + V2[i];
   return Answer;
}
//---------------------------------------------------------------------------
void SetAlias(TTree &ResultTree)
{
   for(int i1 = 0; i1 < 2; i1++)
   {
      for(int i2 = 0; i2 < 2; i2++)
      {
         for(int i3 = 0; i3 < 2; i3++)
         {
            for(int i4 = 0; i4 < 2; i4++)
            {
               for(int i5 = 0; i5 < 2; i5++)
               {
                  for(int i6 = 0; i6 < 2; i6++)
                  {
                     string S1 = "NNNNNN";
                     if(i1 == 1)   S1[0] = 'Y';
                     if(i2 == 1)   S1[1] = 'Y';
                     if(i3 == 1)   S1[2] = 'Y';
                     if(i4 == 1)   S1[3] = 'Y';
                     if(i5 == 1)   S1[4] = 'Y';
                     if(i6 == 1)   S1[5] = 'Y';

                     string S2 = "(";
                     if(i1 == 1)   S2 = S2 + "A2ZZA1ZZError > 0";
                     else          S2 = S2 + "A2ZZA1ZZError == 0";
                     if(i2 == 1)   S2 = S2 + " && A3ZZA1ZZError > 0";
                     else          S2 = S2 + " && A3ZZA1ZZError == 0";
                     if(i3 == 1)   S2 = S2 + " && A2ZAA1ZZError > 0";
                     else          S2 = S2 + " && A2ZAA1ZZError == 0";
                     if(i4 == 1)   S2 = S2 + " && A3ZAA1ZZError > 0";
                     else          S2 = S2 + " && A3ZAA1ZZError == 0";
                     if(i5 == 1)   S2 = S2 + " && A2AAA1ZZError > 0";
                     else          S2 = S2 + " && A2AAA1ZZError == 0";
                     if(i6 == 1)   S2 = S2 + " && A3AAA1ZZError > 0";
                     else          S2 = S2 + " && A3AAA1ZZError == 0";
                     S2 = S2 + ")";

                     ResultTree.SetAlias(S1.c_str(), S2.c_str());
                  }
               }
            }
         }
      }
   }

   ResultTree.SetAlias("A2ZZ", "A2ZZA1ZZ");
   ResultTree.SetAlias("A3ZZ", "A3ZZA1ZZ");
   ResultTree.SetAlias("A2ZA", "A2ZAA1ZZ");
   ResultTree.SetAlias("A3ZA", "A3ZAA1ZZ");
   ResultTree.SetAlias("A2AA", "A2AAA1ZZ");
   ResultTree.SetAlias("A3AA", "A3AAA1ZZ");

   ResultTree.SetAlias("ZZ", "sqrt(A2ZZ*A2ZZ+A3ZZ*A3ZZ+1)");
   ResultTree.SetAlias("ZA", "sqrt(A2ZA*A2ZA+A3ZA*A3ZA)");
   ResultTree.SetAlias("AA", "sqrt(A2AA*A2AA+A3AA*A3AA)");

   ResultTree.SetAlias("S1", "1");
   ResultTree.SetAlias("S2", "(A2ZZ*A2ZZ/3.276/3.276)");
   ResultTree.SetAlias("S3", "(A3ZZ*A3ZZ/5.042/5.042)");

   ResultTree.SetAlias("FA1", "(1/(1+S2+S3))");
   ResultTree.SetAlias("FA2", "(-S2/(1+S2+S3)*sign(A2ZZ))");
   ResultTree.SetAlias("FA3", "(-S3/(1+S2+S3)*sign(A3ZZ))");

   ResultTree.SetAlias("eFA2", "(A2ZZ*A2ZZ/9/(1+A2ZZ*A2ZZ/9)*sign(A2ZZ))");
   ResultTree.SetAlias("eFA3", "(A3ZZ*A3ZZ/25/(1+A3ZZ*A3ZZ/25)*sign(A3ZZ))");

   /*
   ResultTree.SetAlias("NBem", "Fem*(Sem+Bem+ZJem+ggZZem)");
   ResultTree.SetAlias("NBme", "Fme*(Sme+Bme+ZJme+ggZZme)");
   ResultTree.SetAlias("NBee", "Fee*(See+Bee+ZJee+ggZZee)");
   ResultTree.SetAlias("NBmm", "Fmm*(Smm+Bmm+ZJmm+ggZZmm)");
   ResultTree.SetAlias("NZJem", "FZJem*(Sem+Bem+ZJem+ggZZem)");
   ResultTree.SetAlias("NZJme", "FZJme*(Sme+Bme+ZJme+ggZZme)");
   ResultTree.SetAlias("NZJee", "FZJee*(See+Bee+ZJee+ggZZee)");
   ResultTree.SetAlias("NZJmm", "FZJmm*(Smm+Bmm+ZJmm+ggZZmm)");
   ResultTree.SetAlias("NggZZem", "FggZZem*(Sem+Bem+ZJem+ggZZem)");
   ResultTree.SetAlias("NggZZme", "FggZZme*(Sme+Bme+ZJme+ggZZme)");
   ResultTree.SetAlias("NggZZee", "FggZZee*(See+Bee+ZJee+ggZZee)");
   ResultTree.SetAlias("NggZZmm", "FggZZmm*(Smm+Bmm+ZJmm+ggZZmm)");
   ResultTree.SetAlias("NB", "NBem+NBme+NBee+NBmm");
   ResultTree.SetAlias("NZJ", "NZJem+NZJme+NZJee+NZJmm");
   ResultTree.SetAlias("NggZZ", "NggZZem+NggZZme+NggZZee+NggZZmm");
   */

   ResultTree.SetAlias("A3ZZPhase1", "(A3ZZPhase+(A3ZZA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A3ZZPhase2", "(A3ZZPhase1-int(A3ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A3ZZPrimaryPhase", "(A3ZZPhase2+(A3ZZPhase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A2ZZPhase1", "(A2ZZPhase+(A2ZZA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A2ZZPhase2", "(A2ZZPhase1-int(A2ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A2ZZPrimaryPhase", "(A2ZZPhase2+(A2ZZPhase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A3ZAPhase1", "(A3ZAPhase+(A3ZAA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A3ZAPhase2", "(A3ZAPhase1-int(A3ZAPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A3ZAPrimaryPhase", "(A3ZAPhase2+(A3ZAPhase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A2ZAPhase1", "(A2ZAPhase+(A2ZAA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A2ZAPhase2", "(A2ZAPhase1-int(A2ZAPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A2ZAPrimaryPhase", "(A2ZAPhase2+(A2ZAPhase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A3AAPhase1", "(A3AAPhase+(A3AAA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A3AAPhase2", "(A3AAPhase1-int(A3AAPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A3AAPrimaryPhase", "(A3AAPhase2+(A3AAPhase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A2AAPhase1", "(A2AAPhase+(A2AAA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A2AAPhase2", "(A2AAPhase1-int(A2AAPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A2AAPrimaryPhase", "(A2AAPhase2+(A2AAPhase2<0)*2*3.1415926535)");
}
//---------------------------------------------------------------------------








