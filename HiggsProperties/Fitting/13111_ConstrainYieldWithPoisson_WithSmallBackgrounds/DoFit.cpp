#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TROOT.h"
#include "TCanvas.h"

#include "Code/DrawRandom.h"
#include "DataHelper.h"
#include "PlotHelper2.h"
#include "ProgressBar.h"

#include "AngleConversion.h"
#include "Lists.h"
#include "Cuts.h"

#include "FitClass.h"
// #include "ProjectionHelper.h"

int main(int argc, char *argv[]);
void ReadEvents(vector<SingleEvent> &EventsEM, vector<SingleEvent> &EventsME,
   vector<SingleEvent> &EventsEE, vector<SingleEvent> &EventsMM,
   string FileName, bool Capital, double MaxWeight = 1);
int GetEventCount(double Mean, double Sigma);
int PullEvents(vector<SingleEvent> &Events, vector<SingleEvent> &Source, double Mean, double Sigma);

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   srand(time(NULL));

   string SignalFileName =  "EventF.root";
   string BackgroundFileName = "EventF.root";
   string ZJFileName =  "EventF.root";
   string ggZZFileName =  "EventF.root";

   if(argc < 11)
   {
      cerr << "Usage: " << argv[0]
         << " SignalRootFile BackgroundRootFile ZJRootFile ggZZRootFile"
         << " A2ZZ A3ZZ A2ZA A3ZA A2AA A3AA"
         << endl;
      return -1;
   }

   SignalFileName = argv[1];
   BackgroundFileName = argv[2];
   ZJFileName = argv[3];
   ggZZFileName = argv[4];

   double A2ZZ = atof(argv[5]);
   double A3ZZ = atof(argv[6]);
   double A2ZA = atof(argv[7]);
   double A3ZA = atof(argv[8]);
   double A2AA = atof(argv[9]);
   double A3AA = atof(argv[10]);

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   vector<FitResultSummary> Results;

   PsFileHelper PsFile("FitResult.ps");

   vector<SingleEvent> SignalEM, SignalME, SignalEE, SignalMM;
   vector<SingleEvent> BackgroundEM, BackgroundME, BackgroundEE, BackgroundMM;
   vector<SingleEvent> ZJEM, ZJME, ZJEE, ZJMM;
   vector<SingleEvent> ggZZEM, ggZZME, ggZZEE, ggZZMM;
   
   ReadEvents(SignalEM, SignalME, SignalEE, SignalMM, SignalFileName, true, 1);
   ReadEvents(BackgroundEM, BackgroundME, BackgroundEE, BackgroundMM, BackgroundFileName, true, 1);
   ReadEvents(ZJEM, ZJME, ZJEE, ZJMM, ZJFileName, false, 6e-6);
   ReadEvents(ggZZEM, ggZZME, ggZZEE, ggZZMM, ggZZFileName, false, 1e-4);

   vector<double> NS = ListToVector(4, 4.43783616325471, 3.44582607240994, 2.82352993495287, 5.52214303721489);
   vector<double> NSSigma = ListToVector(4, 0.11, 0.11, 0.11, 0.11);
   vector<double> NB = ListToVector(4, 3.76890178716858, 2.15926664889866, 1.88891626468769, 4.72368839592275);
   vector<double> NBSigma = ListToVector(4, 0.048, 0.048, 0.047, 0.047);
   vector<double> NZJ = ListToVector(4, 0.612389991208584, 1.76446477648119, 1.32305122153358, 0.755234938724669);
   vector<double> NZJSigma = ListToVector(4, 0.40, 0.40, 0.40, 0.40);
   vector<double> NggZZ = ListToVector(4, 0.058757182128872, 0.047165629191883, 0.047627447237569, 0.094525245283019);
   vector<double> NggZZSigma = ListToVector(4, 0.25, 0.25, 0.25, 0.25);

   vector<FitConfiguration> Configurations;
   for(int i = 1; i <= 63; i++)
   {
      if(i != 1 && i != 2 && i != 3 && i != 63)
         continue;

      string As = "NNNNNN";
      if((i / 1) % 2 == 1)    As[0] = 'Y';
      if((i / 2) % 2 == 1)    As[1] = 'Y';
      if((i / 4) % 2 == 1)    As[2] = 'Y';
      if((i / 8) % 2 == 1)    As[3] = 'Y';
      if((i / 16) % 2 == 1)   As[4] = 'Y';
      if((i / 32) % 2 == 1)   As[5] = 'Y';

      string Phases = "NNNNNN";

      string Counts = "YYYY";
      string Fs = "YYYYYYYYYYYY";

      Configurations.push_back(FitConfiguration(As, Phases, Counts, Fs, "NNNNNNN",   /* What to float */
         ListToVector(6, A2ZZ, A3ZZ, A2ZA, A3ZA, A2AA, A3AA),                        /* Ratios */
         ListToVector(6, 0, 0, 0, 0, 0, 0),                                          /* Phases */
         ListToVector(4, NS[0] + NB[0] + NZJ[0] + NggZZ[0], NS[1] + NB[1] + NZJ[1] + NggZZ[1],
            NS[2] + NB[2] + NZJ[2] + NggZZ[2], NS[3] + NB[3] + NZJ[3] + NggZZ[3]),   /* Event Counts */
         ListToVector(12, ((Fs[0] == 'Y') ? 0.5 : 0), ((Fs[1] == 'Y') ? 0.5 : 0),
            ((Fs[2] == 'Y') ? 0.5 : 0), ((Fs[3] == 'Y') ? 0.5 : 0),
            ((Fs[4] == 'Y') ? 0.1 : 0), ((Fs[5] == 'Y') ? 0.1 : 0),
            ((Fs[6] == 'Y') ? 0.1 : 0), ((Fs[7] == 'Y') ? 0.1 : 0),
            ((Fs[8] == 'Y') ? 0.1 : 0), ((Fs[9] == 'Y') ? 0.1 : 0),
            ((Fs[10] == 'Y') ? 0.1 : 0), ((Fs[11] == 'Y') ? 0.1 : 0)),               /* Background fraction */
         ListToVector(7, 0, 0, 0, 0, 0, 0, 0),                                       /* Systematics */
         NS, NSSigma, NB, NBSigma, NZJ, NZJSigma, NggZZ, NggZZSigma));               /* Constraints */
   }

   TFile OutputFile("OutputFile.root", "RECREATE");

   int BackgroundCounter = 0;

   int SignalEMSize = SignalEM.size();
   ProgressBar Bar(cout, SignalEMSize);
   Bar.SetStyle(5);

   bool FirstFit = true;
   bool Good = true;
   while(Good == true)
   {
      Bar.Update(SignalEMSize - SignalEM.size());
      Bar.Print();

      int Count = -1;
      vector<SingleEvent> Events;

      Fits.SignalStateCount[0] = PullEvents(Events, SignalEM, NS[0], NSSigma[0]);
      Fits.SignalStateCount[1] = PullEvents(Events, SignalME, NS[1], NSSigma[1]);
      Fits.SignalStateCount[2] = PullEvents(Events, SignalEE, NS[2], NSSigma[2]);
      Fits.SignalStateCount[3] = PullEvents(Events, SignalMM, NS[3], NSSigma[3]);
      Fits.BackgroundStateCount[0] = PullEvents(Events, BackgroundEM, NB[0], NBSigma[0]);
      Fits.BackgroundStateCount[1] = PullEvents(Events, BackgroundME, NB[1], NBSigma[1]);
      Fits.BackgroundStateCount[2] = PullEvents(Events, BackgroundEE, NB[2], NBSigma[2]);
      Fits.BackgroundStateCount[3] = PullEvents(Events, BackgroundMM, NB[3], NBSigma[3]);
      Fits.ZJStateCount[0] = PullEvents(Events, ZJEM, NZJ[0], NZJSigma[0]);
      Fits.ZJStateCount[1] = PullEvents(Events, ZJME, NZJ[1], NZJSigma[1]);
      Fits.ZJStateCount[2] = PullEvents(Events, ZJEE, NZJ[2], NZJSigma[2]);
      Fits.ZJStateCount[3] = PullEvents(Events, ZJMM, NZJ[3], NZJSigma[3]);
      Fits.ggZZStateCount[0] = PullEvents(Events, ggZZEM, NggZZ[0], NggZZSigma[0]);
      Fits.ggZZStateCount[1] = PullEvents(Events, ggZZME, NggZZ[1], NggZZSigma[1]);
      Fits.ggZZStateCount[2] = PullEvents(Events, ggZZEE, NggZZ[2], NggZZSigma[2]);
      Fits.ggZZStateCount[3] = PullEvents(Events, ggZZMM, NggZZ[3], NggZZSigma[3]);

      for(int i = 0; i < 4; i++)
      {
         if(Fits.SignalStateCount[i] < 0)
            Good = false;
         if(Fits.BackgroundStateCount[i] < 0)
            Good = false;
      }
      if(Good == false)
         break;

      for(int i = 0; i < (int)Events.size(); i++)
         Fits.AddPoint(Events[i]);

      for(int iC = 0; iC < (int)Configurations.size(); iC++)
      {
         // double TrueParameters[31] = {0};
         // TrueParameters[0] = Configurations[iC].AAInitialValue[0];
         // TrueParameters[1] = Configurations[iC].PhaseInitialValue[0];
         // TrueParameters[2] = Configurations[iC].AAInitialValue[1];
         // TrueParameters[3] = Configurations[iC].PhaseInitialValue[1];
         // TrueParameters[4] = Configurations[iC].AAInitialValue[2];
         // TrueParameters[5] = Configurations[iC].PhaseInitialValue[2];
         // TrueParameters[6] = Configurations[iC].AAInitialValue[3];
         // TrueParameters[7] = Configurations[iC].PhaseInitialValue[3];
         // TrueParameters[8] = Configurations[iC].AAInitialValue[4];
         // TrueParameters[9] = Configurations[iC].PhaseInitialValue[4];
         // TrueParameters[10] = Configurations[iC].AAInitialValue[5];
         // TrueParameters[11] = Configurations[iC].PhaseInitialValue[5];
         // TrueParameters[12] =
         //    Fits.BackgroundStateCount[0] / (Fits.SignalStateCount[0] + Fits.BackgroundStateCount[0]);
         // TrueParameters[13] =
         //    Fits.BackgroundStateCount[1] / (Fits.SignalStateCount[1] + Fits.BackgroundStateCount[1]);
         // TrueParameters[14] =
         //    Fits.BackgroundStateCount[2] / (Fits.SignalStateCount[2] + Fits.BackgroundStateCount[2]);
         // TrueParameters[15] =
         //    Fits.BackgroundStateCount[3] / (Fits.SignalStateCount[3] + Fits.BackgroundStateCount[3]);
         // for(int i = 16; i < 31; i++)
         //    TrueParameters[i] = 0;
         // for(int i = 0; i < 31; i++)
         //    cout << i << " " << TrueParameters[i] << endl;

         FitResultSummary ResultTemp = Fits.DoFit(Configurations[iC]);
         Results.push_back(ResultTemp);

         /*
         if(iC == 0)
         {
            TH1D HScanFA2(Form("HScanFA2_%d_%d", iC, FitCount), "FA2Scan", 100, -1, 1);
            for(int iB = 1; iB <= HScanFA2.GetNbinsX(); iB++)
            {
               double FA2 = HScanFA2.GetXaxis()->GetBinCenter(iB);
               double A3A1 = Configurations[iC].AAInitialValue[1];
               double S3 = A3A1 * A3A1 / 5.042 / 5.042;
               double A2A1 = sqrt((1 + S3) / (1 - fabs(FA2)) * fabs(FA2) * 3.276 * 3.276);
               if(FA2 > 0)
                  A2A1 = -A2A1;
               TrueParameters[0] = A2A1;

               double Likelihood = Fits.CalculateLogLikelihoodAll(TrueParameters);
               if(Likelihood == Likelihood)
                  HScanFA2.SetBinContent(iB, Likelihood);
               
               TrueParameters[0] = Configurations[iC].AAInitialValue[0];
            }
            HScanFA2.Write();

            TH1D HScanFA3(Form("HScanFA3_%d_%d", iC, FitCount), "FA3Scan", 100, -1, 1);
            for(int iB = 1; iB <= HScanFA3.GetNbinsX(); iB++)
            {
               double FA3 = HScanFA3.GetXaxis()->GetBinCenter(iB);
               double A2A1 = Configurations[iC].AAInitialValue[0];
               double S2 = A2A1 * A2A1 / 3.276 / 3.276;
               double A3A1 = sqrt((1 + S2) / (1 - fabs(FA3)) * fabs(FA3) * 5.042 * 5.042);
               if(FA3 > 0)
                  A3A1 = -A3A1;
               TrueParameters[2] = A3A1;

               double Likelihood = Fits.CalculateLogLikelihoodAll(TrueParameters);
               if(Likelihood == Likelihood)
                  HScanFA3.SetBinContent(iB, Likelihood);

               TrueParameters[2] = Configurations[iC].AAInitialValue[1];
            }
            HScanFA3.Write();
         }
         */
      }
      FitCount = FitCount + 1;

      Fits.ClearPoints();
   }

   Bar.Update(SignalEMSize);
   Bar.Print();
   Bar.PrintLine();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   string BranchList = "";
   BranchList = BranchList + "A2ZZA1ZZ:A2ZZPhase:A3ZZA1ZZ:A3ZZPhase";
   BranchList = BranchList + ":A2ZAA1ZZ:A2ZAPhase:A3ZAA1ZZ:A3ZAPhase";
   BranchList = BranchList + ":A2AAA1ZZ:A2AAPhase:A3AAA1ZZ:A3AAPhase";
   BranchList = BranchList + ":N1:N2:N3:N4:N5:N6:N7";
   BranchList = BranchList + ":Fem:Fme:Fee:Fmm";
   BranchList = BranchList + ":FZJem:FZJme:FZJee:FZJmm";
   BranchList = BranchList + ":FggZZem:FggZZme:FggZZee:FggZZmm";
   BranchList = BranchList + ":A2ZZA1ZZError:A2ZZPhaseError:A3ZZA1ZZError:A3ZZPhaseError";
   BranchList = BranchList + ":A2ZAA1ZZError:A2ZAPhaseError:A3ZAA1ZZError:A3ZAPhaseError";
   BranchList = BranchList + ":A2AAA1ZZError:A2AAPhaseError:A3AAA1ZZError:A3AAPhaseError";
   BranchList = BranchList + ":N1Error:N2Error:N3Error:N4Error:N5Error:N6Error:N7Error";
   BranchList = BranchList + ":FemError:FmeError:FeeError:FmmError";
   BranchList = BranchList + ":FZJemError:FZJmeError:FZJeeError:FZJmmError";
   BranchList = BranchList + ":FggZZemError:FggZZmeError:FggZZeeError:FggZZmmError";
   BranchList = BranchList + ":EDM:Status:Sem:Sme:See:Smm:Bem:Bme:Bee:Bmm";
   BranchList = BranchList + ":ZJem:ZJme:ZJee:ZJmm:ggZZem:ggZZme:ggZZee:ggZZmm";
   BranchList = BranchList + ":RatioFloats:NFloats:TruthNLL:BestNLL";
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100];
      Array[0] = Results[i].AA[0];        Array[31] = Results[i].AAError[0];
      Array[1] = Results[i].Phase[0];     Array[32] = Results[i].PhaseError[0];
      Array[2] = Results[i].AA[1];        Array[33] = Results[i].AAError[1];
      Array[3] = Results[i].Phase[1];     Array[34] = Results[i].PhaseError[1];
      Array[4] = Results[i].AA[2];        Array[35] = Results[i].AAError[2];
      Array[5] = Results[i].Phase[2];     Array[36] = Results[i].PhaseError[2];
      Array[6] = Results[i].AA[3];        Array[37] = Results[i].AAError[3];
      Array[7] = Results[i].Phase[3];     Array[38] = Results[i].PhaseError[3];
      Array[8] = Results[i].AA[4];        Array[39] = Results[i].AAError[4];
      Array[9] = Results[i].Phase[4];     Array[40] = Results[i].PhaseError[4];
      Array[10] = Results[i].AA[5];       Array[41] = Results[i].AAError[5];
      Array[11] = Results[i].Phase[5];    Array[42] = Results[i].PhaseError[5];
      Array[12] = Results[i].N[0];        Array[43] = Results[i].NError[0];
      Array[13] = Results[i].N[1];        Array[44] = Results[i].NError[1];
      Array[14] = Results[i].N[2];        Array[45] = Results[i].NError[2];
      Array[15] = Results[i].N[3];        Array[46] = Results[i].NError[3];
      Array[16] = Results[i].N[4];        Array[47] = Results[i].NError[4];
      Array[17] = Results[i].N[5];        Array[48] = Results[i].NError[5];
      Array[18] = Results[i].N[6];        Array[49] = Results[i].NError[6];
      Array[19] = Results[i].F[0];        Array[50] = Results[i].FError[0];
      Array[20] = Results[i].F[1];        Array[51] = Results[i].FError[1];
      Array[21] = Results[i].F[2];        Array[52] = Results[i].FError[2];
      Array[22] = Results[i].F[3];        Array[53] = Results[i].FError[3];
      Array[23] = Results[i].FZJ[0];      Array[54] = Results[i].FZJError[0];
      Array[24] = Results[i].FZJ[1];      Array[55] = Results[i].FZJError[1];
      Array[25] = Results[i].FZJ[2];      Array[56] = Results[i].FZJError[2];
      Array[26] = Results[i].FZJ[3];      Array[57] = Results[i].FZJError[3];
      Array[27] = Results[i].FggZZ[0];    Array[58] = Results[i].FggZZError[0];
      Array[28] = Results[i].FggZZ[1];    Array[59] = Results[i].FggZZError[1];
      Array[29] = Results[i].FggZZ[2];    Array[60] = Results[i].FggZZError[2];
      Array[30] = Results[i].FggZZ[3];    Array[61] = Results[i].FggZZError[3];

      Array[62] = Results[i].EDM;
      Array[63] = Results[i].FitStatus;

      Array[64] = Results[i].S[0];        Array[68] = Results[i].B[0];
      Array[65] = Results[i].S[1];        Array[69] = Results[i].B[1];
      Array[66] = Results[i].S[2];        Array[70] = Results[i].B[2];
      Array[67] = Results[i].S[3];        Array[71] = Results[i].B[3];

      Array[72] = Results[i].ZJ[0];       Array[76] = Results[i].ggZZ[0];
      Array[73] = Results[i].ZJ[1];       Array[77] = Results[i].ggZZ[1];
      Array[74] = Results[i].ZJ[2];       Array[78] = Results[i].ggZZ[2];
      Array[75] = Results[i].ZJ[3];       Array[79] = Results[i].ggZZ[3];

      Array[80] = 0;
      Array[81] = 0;

      Array[82] = Results[i].TruthNLL;
      Array[83] = Results[i].BestNLL;
      
      OutputTree.Fill(Array);
   }

   OutputTree.SetAlias("A3ZZPhase1", "(A3ZZPhase+(A3ZZA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A3ZZPhase2", "(A3ZZPhase1-int(A3ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3ZZPrimaryPhase", "(A3ZZPhase2+(A3ZZPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2ZZPhase1", "(A2ZZPhase+(A2ZZA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A2ZZPhase2", "(A2ZZPhase1-int(A2ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2ZZPrimaryPhase", "(A2ZZPhase2+(A2ZZPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A3ZAPhase1", "(A3ZAPhase+(A3ZAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A3ZAPhase2", "(A3ZAPhase1-int(A3ZAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3ZAPrimaryPhase", "(A3ZAPhase2+(A3ZAPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2ZAPhase1", "(A2ZAPhase+(A2ZAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A2ZAPhase2", "(A2ZAPhase1-int(A2ZAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2ZAPrimaryPhase", "(A2ZAPhase2+(A2ZAPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A3AAPhase1", "(A3AAPhase+(A3AAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A3AAPhase2", "(A3AAPhase1-int(A3AAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3AAPrimaryPhase", "(A3AAPhase2+(A3AAPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2AAPhase1", "(A2AAPhase+(A2AAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A2AAPhase2", "(A2AAPhase1-int(A2AAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2AAPrimaryPhase", "(A2AAPhase2+(A2AAPhase2<0)*2*3.1415926535)");

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

void ReadEvents(vector<SingleEvent> &EventsEM, vector<SingleEvent> &EventsME,
   vector<SingleEvent> &EventsEE, vector<SingleEvent> &EventsMM,
   string FileName, bool Capital, double MaxWeight)
{
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("zz4lTree");
   if(Tree == NULL)
      return;

   DataHelper DHFile("Normalization.dh");

   int l1id, l3id;
   if(Capital == false)
   {
      Tree->SetBranchAddress("l1id", &l1id);
      Tree->SetBranchAddress("l3id", &l3id);
   }
   else
   {
      Tree->SetBranchAddress("L1ID", &l1id);
      Tree->SetBranchAddress("L3ID", &l3id);
   }

   string SignalBranch[] = {"T1", "T3", "T5", "T7", "T9", "T11", "T13", "T15", "T17", "T21", "T22", "T23", "T24"};
   string BackgroundBranch[] = {"T2Total", "T4Total", "T6Total", "T8Total", "T10Total", "T12Total", "T14Total", "T16Total", "T18Total",
      "T2Total", "T2Total", "T2Total", "T2Total"};

   double Value[92][13] = {{0}};
   double Integral[92][13] = {{0}};
   float Value2[2][13] = {{0}};
   double Integral2[2][13] = {{0}};

   vector<string> Suffix = GetHLLSignalSuffixList();

   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &Value[i+1][0]);
   Tree->SetBranchAddress("B2", &Value[0][0]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B3_%s", Suffix[i].c_str()), &Value[i+1][1]);
   // Tree->SetBranchAddress("B4", &Value[0][1]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B5_%s", Suffix[i].c_str()), &Value[i+1][2]);
   // Tree->SetBranchAddress("B6", &Value[0][2]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B7_%s", Suffix[i].c_str()), &Value[i+1][3]);
   // Tree->SetBranchAddress("B8", &Value[0][3]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B9_%s", Suffix[i].c_str()), &Value[i+1][4]);
   // Tree->SetBranchAddress("B10", &Value[0][4]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B11_%s", Suffix[i].c_str()), &Value[i+1][5]);
   // Tree->SetBranchAddress("B12", &Value[0][5]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B13_%s", Suffix[i].c_str()), &Value[i+1][6]);
   // Tree->SetBranchAddress("B14", &Value[0][6]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B15_%s", Suffix[i].c_str()), &Value[i+1][7]);
   // Tree->SetBranchAddress("B16", &Value[0][7]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B17_%s", Suffix[i].c_str()), &Value[i+1][8]);
   // Tree->SetBranchAddress("B18", &Value[0][8]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B21_%s", Suffix[i].c_str()), &Value[i+1][9]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B22_%s", Suffix[i].c_str()), &Value[i+1][10]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B23_%s", Suffix[i].c_str()), &Value[i+1][11]);
   // for(int i = 0; i < 91; i++)
   //    Tree->SetBranchAddress(Form("B24_%s", Suffix[i].c_str()), &Value[i+1][12]);
   
   Tree->SetBranchAddress("B19", &Value2[0][0]);
   Tree->SetBranchAddress("B20", &Value2[1][0]);

   float l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   float l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
   float weight = 1;
   double L1PT, L1Eta, L1Phi, L2PT, L2Eta, L2Phi;
   double L3PT, L3Eta, L3Phi, L4PT, L4Eta, L4Phi;
   double Weight = 1;
   if(Capital == false)
   {
      Tree->SetBranchAddress("l1pt", &l1pt);
      Tree->SetBranchAddress("l1eta", &l1eta);
      Tree->SetBranchAddress("l1phi", &l1phi);
      Tree->SetBranchAddress("l2pt", &l2pt);
      Tree->SetBranchAddress("l2eta", &l2eta);
      Tree->SetBranchAddress("l2phi", &l2phi);
      Tree->SetBranchAddress("l3pt", &l3pt);
      Tree->SetBranchAddress("l3eta", &l3eta);
      Tree->SetBranchAddress("l3phi", &l3phi);
      Tree->SetBranchAddress("l4pt", &l4pt);
      Tree->SetBranchAddress("l4eta", &l4eta);
      Tree->SetBranchAddress("l4phi", &l4phi);
      Tree->SetBranchAddress("weight", &weight);
   }
   else
   {
      Tree->SetBranchAddress("L1PT", &L1PT);
      Tree->SetBranchAddress("L1Eta", &L1Eta);
      Tree->SetBranchAddress("L1Phi", &L1Phi);
      Tree->SetBranchAddress("L2PT", &L2PT);
      Tree->SetBranchAddress("L2Eta", &L2Eta);
      Tree->SetBranchAddress("L2Phi", &L2Phi);
      Tree->SetBranchAddress("L3PT", &L3PT);
      Tree->SetBranchAddress("L3Eta", &L3Eta);
      Tree->SetBranchAddress("L3Phi", &L3Phi);
      Tree->SetBranchAddress("L4PT", &L4PT);
      Tree->SetBranchAddress("L4Eta", &L4Eta);
      Tree->SetBranchAddress("L4Phi", &L4Phi);
      Tree->SetBranchAddress("Weight", &Weight);
   }

   float z1mass, z2mass, zzmass;
   double M1, M2, MH;
   if(Capital == false)
   {
      Tree->SetBranchAddress("z1mass", &z1mass);
      Tree->SetBranchAddress("z2mass", &z2mass);
      Tree->SetBranchAddress("zzmass", &zzmass);
   }
   else
   {
      Tree->SetBranchAddress("M1", &M1);
      Tree->SetBranchAddress("M2", &M2);
      Tree->SetBranchAddress("MH", &MH);
   }

   bool PassEM, PassME, PassEE, PassMM;
   if(Capital == true)
   {
      Tree->SetBranchAddress("PassEM", &PassEM);
      Tree->SetBranchAddress("PassME", &PassME);
      Tree->SetBranchAddress("PassEE", &PassEE);
      Tree->SetBranchAddress("PassMM", &PassMM);
   }

   int EntryCount = Tree->GetEntries();
   // if(EntryCount > 1000000)EntryCount = EntryCount / 10;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(0);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(EntryCount < 1000 || (iE % (EntryCount / 1000) == 0))
      {
         Bar.Update(iE);
         Bar.Print();
      }
   
      if(Capital == false)
         Weight = weight;
      if(DrawRandom(0, 1) > Weight / MaxWeight)
         continue;
      Weight = 1;

      // if(DrawRandom(0, 1) > Weight)
      //    continue;

      // LeptonVectors Leptons;
      // Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      // Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      // Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      // Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      // EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      if(Capital == false && (zzmass > 135 || zzmass < 115))
         continue;
      if(Capital == false && max(z1mass, z2mass) < 40)
         continue;
      if(Capital == false && min(z1mass, z2mass) < 12)
         continue;
      if(Capital == true && (MH > 135 || MH < 115))
         continue;
      if(Capital == true && max(M1, M2) < 40)
         continue;
      if(Capital == true && min(M1, M2) < 12)
         continue;
      // if(PassBaselineCut(Event, l1id, l3id) == false)
      //    continue;

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      if(Capital == true)
      {
         if(l1id == 11 && l3id == 13 && PassEM == false)   continue;
         if(l1id == 13 && l3id == 11 && PassME == false)   continue;
         if(l1id == 11 && l3id == 11 && PassEE == false)   continue;
         if(l1id == 13 && l3id == 13 && PassMM == false)   continue;
      }
      
      string State = "";
      if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      if(l1id == 13 && l3id == 11)   State = "me";
      if(l1id == 13 && l3id == 13)   State = "mm";
      
      char BranchInitial = 'T';
      if(State == "em")   BranchInitial = 'T';
      if(State == "me")   BranchInitial = 'U';
      if(State == "ee")   BranchInitial = 'V';
      if(State == "mm")   BranchInitial = 'W';

      string DHState = State;

      if(State == "")   // WTF
         continue;
      else
      {
         for(int j = 0; j < 13; j++)
         {
            BackgroundBranch[j][0] = BranchInitial;

            Integral[0][j] = DHFile[DHState][BackgroundBranch[j]].GetDouble() / 2;
            if(State[0] != State[1])   Integral[0][j] = Integral[0][j] / 1.15;

            for(int i = 1; i < 92; i++)
            {
               SignalBranch[j][0] = BranchInitial;

               char BranchSuffix[100] = "";
               sprintf(BranchSuffix, "_%02d", i);
               string Branch = SignalBranch[j] + BranchSuffix;
               Integral[i][j] = DHFile[DHState][Branch].GetDouble();
            }
         }
      }

      for(int j = 9; j < 13; j++)   // Background doesn't change under different MH assumptions
      {
         Value[0][j] = Value[0][0];
         Integral[0][j] = Integral[0][0];
      }

      for(int i = 0; i < 2; i++)
         for(int j = 0; j < 13; j++)
            Integral2[i][j] = (2 * PI / 10) * (2.0 / 10) * (2 * PI / 10) * (2.0 / 10) * (2.0 / 10) * (60.0 / 20) * (58.0 / 10);
      
      for(int j = 1; j < 13; j++)   // No systematics yet on the small components
      {
         for(int i = 0; i < 2; i++)
         {
            Value2[i][j] = Value2[i][0];
            Integral2[i][j] = Integral2[i][0];
         }
      }

      for(int j = 1; j < 13; j++)   // For now!
      {
         for(int i = 0; i < 92; i++)
         {
            Value[i][j] = Value[i][0];
            Integral[i][j] = Integral[i][0];
         }
      }

      bool Good = true;
      for(int i = 0; i < 92; i++)
         for(int j = 0; j < 13; j++)
            if(Value[i][j] > 0.99 || (i < 14 && Value[i][j] < 1e-50))
               Good = false;
      if(Good == false)
         continue;

      SingleEvent NewEvent;

      for(int i = 0; i < 92; i++)
         for(int j = 0; j < 13; j++)
            NewEvent.v[i][j] = Value[i][j];
      for(int i = 0; i < 92; i++)
         for(int j = 0; j < 13; j++)
            NewEvent.i[i][j] = Integral[i][j];
      for(int i = 0; i < 2; i++)
         for(int j = 0; j < 13; j++)
            NewEvent.v2[i][j] = exp(Value2[i][j]);
      for(int i = 0; i < 2; i++)
         for(int j = 0; j < 13; j++)
            NewEvent.i2[i][j] = Integral2[i][j];
      // NewEvent.event = Event;
      NewEvent.state = State;
      NewEvent.weight = Weight;

      if(State == "em")   EventsEM.push_back(NewEvent);
      if(State == "me")   EventsME.push_back(NewEvent);
      if(State == "ee")   EventsEE.push_back(NewEvent);
      if(State == "mm")   EventsMM.push_back(NewEvent);
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();
   
   File.Close();

   random_shuffle(EventsEM.begin(), EventsEM.end());
   random_shuffle(EventsME.begin(), EventsME.end());
   random_shuffle(EventsEE.begin(), EventsEE.end());
   random_shuffle(EventsMM.begin(), EventsMM.end());

   cout << "Events read: " << EventsEM.size()
      << ", " << EventsME.size()
      << ", " << EventsEE.size()
      << ", " << EventsMM.size()
      << endl;
}

int GetEventCount(double Mean, double Sigma)
{
   double LogNormalMu = log(Mean) - log(1 + Sigma * Sigma) / 2;
   double LogNormalSigma = sqrt(log(1 + Sigma * Sigma));

   double PoissonMean = DrawLogNormal(LogNormalMu, LogNormalSigma);

   return DrawPoisson(PoissonMean);
}

int PullEvents(vector<SingleEvent> &Events, vector<SingleEvent> &Source, double Mean, double Sigma)
{
   int EventCount = GetEventCount(Mean, Sigma);

   vector<SingleEvent> NewEvents;

   while(NewEvents.size() < EventCount && Source.size() > 0)
   {
      SingleEvent Event = Source[Source.size()-1];
      Source.pop_back();
      
      if(DrawRandom(0, 1) > Event.weight)
         continue;

      NewEvents.push_back(Event);
   }

   if(NewEvents.size() < EventCount)
      return -1;

   Events.insert(Events.end(), NewEvents.begin(), NewEvents.end());

   return EventCount;
}






