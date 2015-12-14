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
void ReadEvents(vector<SingleEvent> &Events, string FileName);

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   srand(time(NULL));

   string FileName =  "EventF.root";
   int DatasetSize = 30;
   string BackgroundFileName = "EventF.root";
   int BackgroundDatasetSize = 30;

   if(argc <= 10)
   {
      cerr << "Usage: " << argv[0]
         << " SignalRootFile SignalDatasetSize BackgroundRootFile BackgroundDatasetSize"
         << " A2ZZ A3ZZ A2ZA A3ZA A2AA A3AA"
         << endl;
      return -1;
   }

   FileName = argv[1];
   DatasetSize = atoi(argv[2]);
   BackgroundFileName = argv[3];
   BackgroundDatasetSize = atoi(argv[4]);

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

   vector<SingleEvent> Signals, Backgrounds;
   ReadEvents(Signals, FileName);
   if(BackgroundDatasetSize > 0)
      ReadEvents(Backgrounds, BackgroundFileName);
   else
      Backgrounds = Signals;

   vector<FitConfiguration> Configurations;
   for(int i = 1; i <= 3; i++)
   {
      string As = "NNNNNN";
      if((i / 1) % 2 == 1)    As[0] = 'Y';
      if((i / 2) % 2 == 1)    As[1] = 'Y';
      if((i / 4) % 2 == 1)    As[2] = 'Y';
      if((i / 8) % 2 == 1)    As[3] = 'Y';
      if((i / 16) % 2 == 1)   As[4] = 'Y';
      if((i / 32) % 2 == 1)   As[5] = 'Y';

      string Phases = "NNNNNN";

      string Fs = "NNNN";
      if(BackgroundDatasetSize > 0)
         Fs = "YYYY";

      vector<double> AValues = ListToVector(6, 0, 0, 0, 0, 0, 0);
      /*if(As[0] == 'N')*/   AValues[0] = A2ZZ;
      /*if(As[1] == 'N')*/   AValues[1] = A3ZZ;
      /*if(As[2] == 'N')*/   AValues[2] = A2ZA;
      /*if(As[3] == 'N')*/   AValues[3] = A3ZA;
      /*if(As[4] == 'N')*/   AValues[4] = A2AA;
      /*if(As[5] == 'N')*/   AValues[5] = A3AA;

      Configurations.push_back(FitConfiguration(As, Phases, Fs, "YNNNNNN",
         AValues,
         ListToVector(6, 0, 0, 0, 0, 0, 0),
         ListToVector(4, ((Fs[0] == 'Y') ? 0.5 : 0), ((Fs[1] == 'Y') ? 0.5 : 0),
            ((Fs[2] == 'Y') ? 0.5 : 0), ((Fs[3] == 'Y') ? 0.5 : 0)),
         ListToVector(7, 0, 0, 0, 0, 0, 0, 0)));
   }

   int BackgroundCounter = 0;

   ProgressBar Bar(cout, Signals.size());
   Bar.SetStyle(5);

   double RunningFem = 0, RunningFme = 0, RunningFee = 0, RunningFmm = 0;
   int CountFem = 0, CountFme = 0, CountFee = 0, CountFmm = 0;

   bool FirstFit = true;
   for(int iS = 0; iS < (int)Signals.size(); iS++)
   {
      if((iS % (Signals.size() / 300)) == 0)
      {
         Bar.Update(iS);
         Bar.Print();
      }

      cout << "\033[1G\033[10C";
      if(CountFem > 0)
         cout << "{EM " << RunningFem / CountFem << "}";
      if(CountFme > 0)
         cout << "{me " << RunningFme / CountFme << "}";
      if(CountFee > 0)
         cout << "{ee " << RunningFee / CountFee << "}";
      if(CountFmm > 0)
         cout << "{mm " << RunningFmm / CountFmm << "}";
      cout << flush;

      Fits.AddPoint(Signals[iS]);

      if(Signals[iS].state == "em")   Fits.SignalStateCount[0] = Fits.SignalStateCount[0] + 1;
      if(Signals[iS].state == "me")   Fits.SignalStateCount[1] = Fits.SignalStateCount[1] + 1;
      if(Signals[iS].state == "ee")   Fits.SignalStateCount[2] = Fits.SignalStateCount[2] + 1;
      if(Signals[iS].state == "mm")   Fits.SignalStateCount[3] = Fits.SignalStateCount[3] + 1;
      
      if(Fits.SampleSize < DatasetSize)
         continue;

      bool DoShuffle = false;
      while(Fits.SampleSize < DatasetSize + BackgroundDatasetSize)
      {
         Fits.AddPoint(Backgrounds[BackgroundCounter]);

         if(Backgrounds[BackgroundCounter].state == "em")
            Fits.BackgroundStateCount[0] = Fits.BackgroundStateCount[0] + 1;
         if(Backgrounds[BackgroundCounter].state == "me")
            Fits.BackgroundStateCount[1] = Fits.BackgroundStateCount[1] + 1;
         if(Backgrounds[BackgroundCounter].state == "ee")
            Fits.BackgroundStateCount[2] = Fits.BackgroundStateCount[2] + 1;
         if(Backgrounds[BackgroundCounter].state == "mm")
            Fits.BackgroundStateCount[3] = Fits.BackgroundStateCount[3] + 1;

         BackgroundCounter = BackgroundCounter + 1;
         if(BackgroundCounter >= Backgrounds.size())
         {
            BackgroundCounter = 0;
            DoShuffle = true;
         }
      }

      if(DoShuffle == true)
         random_shuffle(Backgrounds.begin(), Backgrounds.end());

      for(int iC = 0; iC < (int)Configurations.size(); iC++)
      {
         FitResultSummary ResultTemp = Fits.DoFit(Configurations[iC]);
         Results.push_back(ResultTemp);

         if(ResultTemp.FitStatus == 3)
         {
            if(ResultTemp.Sem + ResultTemp.Bem > 0)
            {
               RunningFem = RunningFem + ResultTemp.Fem;
               CountFem = CountFem + 1;
            }
            if(ResultTemp.Sme + ResultTemp.Bme > 0)
            {
               RunningFme = RunningFme + ResultTemp.Fme;
               CountFme = CountFme + 1;
            }
            if(ResultTemp.See + ResultTemp.Bee > 0)
            {
               RunningFee = RunningFee + ResultTemp.Fee;
               CountFee = CountFee + 1;
            }
            if(ResultTemp.Smm + ResultTemp.Bmm > 0)
            {
               RunningFmm = RunningFmm + ResultTemp.Fmm;
               CountFmm = CountFmm + 1;
            }
         }

         if(FirstFit == true)
         {
            FirstFit = false;

            // for(int i2 = 0; i2 <= 100; i2++)
            // {
            //    for(int i3 = 0; i3 <= 100; i3++)
            //    {
            //       for(int iF = 0; iF <= 100; iF++)
            //       {
            //          // double fa2 = i2 * 0.01;
            //          // double fa3 = i3 * 0.01;
            //          // double f = iF * 0.01;

            //          // if(fa2 + fa3 >= 1)
            //          //    continue;

            //          // double A2 = fa2 / (1 - fa2 - fa3);
            //          // double A3 = fa3 / (1 - fa2 - fa3);

            //          // double Parameters[] = {A2, 0, A3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            //          //    0, f, 0, 0,
            //          //    0, 0, 0, 0,
            //          //    0, 0, 0, 0,
            //          //    0, 0, 0, 0, 0, 0, 0};
            //          // 
            //          // cout << "LIKELIHOOD " << fa2 << " " << fa3 << " " << f << " " << Fits.CalculateLogLikelihoodAll(Parameters) << endl;
            //       }
            //    }
            // }
         }
      }
      FitCount = FitCount + 1;

      Fits.ClearPoints();
   }

   Bar.Update(Signals.size());
   Bar.Print();
   Bar.PrintLine();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   TFile OutputFile("OutputFile.root", "RECREATE");

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
   BranchList = BranchList + ":RatioFloats:NFloats:TruthNLL:BestNLL";
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100];
      Array[0] = Results[i].A2ZZA1ZZ;     Array[31] = Results[i].A2ZZA1ZZError;
      Array[1] = Results[i].A2ZZPhase;    Array[32] = Results[i].A2ZZPhaseError;
      Array[2] = Results[i].A3ZZA1ZZ;     Array[33] = Results[i].A3ZZA1ZZError;
      Array[3] = Results[i].A3ZZPhase;    Array[34] = Results[i].A3ZZPhaseError;
      Array[4] = Results[i].A2ZAA1ZZ;     Array[35] = Results[i].A2ZAA1ZZError;
      Array[5] = Results[i].A2ZAPhase;    Array[36] = Results[i].A2ZAPhaseError;
      Array[6] = Results[i].A3ZAA1ZZ;     Array[37] = Results[i].A3ZAA1ZZError;
      Array[7] = Results[i].A3ZAPhase;    Array[38] = Results[i].A3ZAPhaseError;
      Array[8] = Results[i].A2AAA1ZZ;     Array[39] = Results[i].A2AAA1ZZError;
      Array[9] = Results[i].A2AAPhase;    Array[40] = Results[i].A2AAPhaseError;
      Array[10] = Results[i].A3AAA1ZZ;    Array[41] = Results[i].A3AAA1ZZError;
      Array[11] = Results[i].A3AAPhase;   Array[42] = Results[i].A3AAPhaseError;
      Array[12] = Results[i].N1;          Array[43] = Results[i].N1Error;
      Array[13] = Results[i].N2;          Array[44] = Results[i].N2Error;
      Array[14] = Results[i].N3;          Array[45] = Results[i].N3Error;
      Array[15] = Results[i].N4;          Array[46] = Results[i].N4Error;
      Array[16] = Results[i].N5;          Array[47] = Results[i].N5Error;
      Array[17] = Results[i].N6;          Array[48] = Results[i].N6Error;
      Array[18] = Results[i].N7;          Array[49] = Results[i].N7Error;
      Array[19] = Results[i].Fem;         Array[50] = Results[i].FemError;
      Array[20] = Results[i].Fme;         Array[51] = Results[i].FmeError;
      Array[21] = Results[i].Fee;         Array[52] = Results[i].FeeError;
      Array[22] = Results[i].Fmm;         Array[53] = Results[i].FmmError;
      Array[23] = Results[i].FZJem;       Array[54] = Results[i].FZJemError;
      Array[24] = Results[i].FZJme;       Array[55] = Results[i].FZJmeError;
      Array[25] = Results[i].FZJee;       Array[56] = Results[i].FZJeeError;
      Array[26] = Results[i].FZJmm;       Array[57] = Results[i].FZJmmError;
      Array[27] = Results[i].FggZZem;     Array[58] = Results[i].FggZZemError;
      Array[28] = Results[i].FggZZme;     Array[59] = Results[i].FggZZmeError;
      Array[29] = Results[i].FggZZee;     Array[60] = Results[i].FggZZeeError;
      Array[30] = Results[i].FggZZmm;     Array[61] = Results[i].FggZZmmError;

      Array[62] = Results[i].EDM;
      Array[63] = Results[i].FitStatus;

      Array[64] = Results[i].Sem;         Array[68] = Results[i].Bem;
      Array[65] = Results[i].Sme;         Array[69] = Results[i].Bme;
      Array[66] = Results[i].See;         Array[70] = Results[i].Bee;
      Array[67] = Results[i].Smm;         Array[71] = Results[i].Bmm;

      Array[72] = 0;
      Array[73] = 0;

      Array[74] = Results[i].TruthNLL;
      Array[75] = Results[i].BestNLL;
      
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

void ReadEvents(vector<SingleEvent> &Events, string FileName)
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
   Tree->SetBranchAddress("l1id", &l1id);
   Tree->SetBranchAddress("l3id", &l3id);

   string SignalBranch[] = {"T1", "T3", "T5", "T7", "T9", "T11", "T13", "T15", "T17", "T21", "T22", "T23", "T24"};
   string BackgroundBranch[] = {"T2Total", "T4Total", "T6Total", "T8Total", "T10Total", "T12Total", "T14Total", "T16Total", "T18Total", "T2Total", "T2Total", "T2Total", "T2Total"};

   double Value[92][13] = {{0}};
   double Integral[92][13] = {{0}};
   double Value2[2][13] = {{0}};
   double Integral2[2][13] = {{0}};

   vector<string> Suffix = GetHLLSignalSuffixList();

   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &Value[i+1][0]);
   Tree->SetBranchAddress("B2", &Value[0][0]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B3_%s", Suffix[i].c_str()), &Value[i+1][1]);
   Tree->SetBranchAddress("B4", &Value[0][1]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B5_%s", Suffix[i].c_str()), &Value[i+1][2]);
   Tree->SetBranchAddress("B6", &Value[0][2]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B7_%s", Suffix[i].c_str()), &Value[i+1][3]);
   Tree->SetBranchAddress("B8", &Value[0][3]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B9_%s", Suffix[i].c_str()), &Value[i+1][4]);
   Tree->SetBranchAddress("B10", &Value[0][4]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B11_%s", Suffix[i].c_str()), &Value[i+1][5]);
   Tree->SetBranchAddress("B12", &Value[0][5]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B13_%s", Suffix[i].c_str()), &Value[i+1][6]);
   Tree->SetBranchAddress("B14", &Value[0][6]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B15_%s", Suffix[i].c_str()), &Value[i+1][7]);
   Tree->SetBranchAddress("B16", &Value[0][7]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B17_%s", Suffix[i].c_str()), &Value[i+1][8]);
   Tree->SetBranchAddress("B18", &Value[0][8]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B21_%s", Suffix[i].c_str()), &Value[i+1][9]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B22_%s", Suffix[i].c_str()), &Value[i+1][10]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B23_%s", Suffix[i].c_str()), &Value[i+1][11]);
   for(int i = 0; i < 91; i++)
      Tree->SetBranchAddress(Form("B24_%s", Suffix[i].c_str()), &Value[i+1][12]);
   
   Tree->SetBranchAddress("B19", &Value2[0][0]);
   Tree->SetBranchAddress("B20", &Value2[1][0]);

   float l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   float l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
   float Weight;
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
   Tree->SetBranchAddress("Weight", &Weight);

   float z1mass, z2mass, zzmass;
   Tree->SetBranchAddress("z1mass", &z1mass);
   Tree->SetBranchAddress("z2mass", &z2mass);
   Tree->SetBranchAddress("zzmass", &zzmass);

   int EntryCount = Tree->GetEntries();
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

      // if(DrawRandom(0, 1) > Weight)
      //    continue;

      // LeptonVectors Leptons;
      // Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      // Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      // Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      // Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      // EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      if(zzmass > 135 || zzmass < 115)
         continue;
      if(max(z1mass, z2mass) < 40)
         continue;
      if(min(z1mass, z2mass) < 12)
         continue;
      // if(PassBaselineCut(Event, l1id, l3id) == false)
      //    continue;

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      string State = "";
      // if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      // if(l1id == 13 && l3id == 11)   State = "me";
      // if(l1id == 13 && l3id == 13)   State = "mm";
      
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

      for(int j = 1; j < 13; j++)   // No systematics yet on the small components
      {
         for(int i = 0; i < 2; i++)
         {
            Value2[i][j] = Value2[i][0];
            Integral2[i][j] = Integral2[i][0];
         }
      }

      Value[0][0] = 0.5;   // For now!  disable background
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
            NewEvent.v2[i][j] = Value2[i][j];
      for(int i = 0; i < 2; i++)
         for(int j = 0; j < 13; j++)
            NewEvent.i2[i][j] = Integral2[i][j];
      // NewEvent.event = Event;
      NewEvent.state = State;

      Events.push_back(NewEvent);
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();
   
   File.Close();

   random_shuffle(Events.begin(), Events.end());

   cout << "Events read: " << Events.size() << endl;
}



