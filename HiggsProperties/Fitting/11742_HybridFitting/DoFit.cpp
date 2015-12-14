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

#include "Code/DrawRandom.h"
#include "DataHelper.h"

struct FitResultSummary;
class FitClass;
int main(int argc, char *argv[]);

#define PI 3.14159265358979323846264338327950288479716939937510

struct FitResultSummary
{
public:
   double A2A1, A2A1Error;
   double A2Phase, A2PhaseError;
   double A3A1, A3A1Error;
   double A3Phase, A3PhaseError;
   double F, FError;
   double N1, N1Error;
   double N2, N2Error;
   double EDM;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   vector<double> V[16][5];   // Background = 0, Signal = 1-15; second index = CUDWN
   vector<double> I[16][5];   // same as above
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodUpDown(const double *Parameters) const;
   double CalculateLogLikelihoodNarrowWide(const double *Parameters) const;
   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(double v[16][5], double I[16][5]);
   void ClearPoints();

   FitResultSummary DoFit();
};

int main(int argc, char *argv[])
{
   string FileName =  "EventB.root";
   int DatasetSize = 30;

   if(argc <= 2)
   {
      cerr << "Usage: " << argv[0] << " RootFile DatasetSize" << endl;
      return -1;
   }

   FileName = argv[1];
   DatasetSize = atoi(argv[2]);

   DataHelper DHFile("Normalization.dh");

   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");

   int l1id, l3id;
   Tree->SetBranchAddress("l1id", &l1id);
   Tree->SetBranchAddress("l3id", &l3id);

   string SignalBranch[] = {"T26", "T3", "T5", "T7", "T9"};
   string BackgroundBranch[] = {"T2", "T4", "T6", "T8", "T10"};

   double Value[16][5] = {{0}};
   double Integral[16][5] = {{0}};

   string suffix[15] = {"A1RA1R", "A2RA2R", "A2IA2I", "A3RA3R", "A3IA3I",
      "A1RA2R", "A1RA2I", "A1RA3R", "A1RA3I", "A2RA2I",
      "A2RA3R", "A2RA3I", "A2IA3R", "A2IA3I", "A3RA3I"};
   vector<string> Suffix(suffix, suffix + 15);

   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &Value[i+1][0]);
   Tree->SetBranchAddress("B2", &Value[0][0]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B3_%s", Suffix[i].c_str()), &Value[i+1][1]);
   Tree->SetBranchAddress("B4", &Value[0][1]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B5_%s", Suffix[i].c_str()), &Value[i+1][2]);
   Tree->SetBranchAddress("B6", &Value[0][2]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B7_%s", Suffix[i].c_str()), &Value[i+1][3]);
   Tree->SetBranchAddress("B8", &Value[0][3]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B9_%s", Suffix[i].c_str()), &Value[i+1][4]);
   Tree->SetBranchAddress("B10", &Value[0][4]);

   float Weight;
   Tree->SetBranchAddress("weight", &Weight);

   FitClass Fits;

   vector<FitResultSummary> Results;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      if(DrawRandom(0, 1) > Weight)   // killed by efficiency
         continue;

      for(int j = 0; j < 5; j++)
      {
         Value[10][j] = 0;
         Value[15][j] = 0;
      }

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      string State = "";
      if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      if(l1id == 13 && l3id == 11)   State = "me";
      if(l1id == 13 && l3id == 13)   State = "mm";

      if(State == "")   // WTF
         continue;
      else
      {
         for(int j = 0; j < 5; j++)
         {
            Integral[0][j] = DHFile[State][BackgroundBranch[j]].GetDouble();
            for(int i = 1; i < 16; i++)
            {
               char BranchSuffix[2] = "A";
               BranchSuffix[0] = char('A' + (i - 1));
               string Branch = SignalBranch[j] + BranchSuffix;
               Integral[i][j] = DHFile[State][Branch].GetDouble();

               if(i == 10 || i == 15)
                  Integral[i][j] = 0;
            }
         }
      }

      if(State == "em" || State == "me")   // bug fix of A2 cross terms!
      {
         for(int j = 1; j < 5; j++)
         {
            Integral[6][j] = -Integral[6][j];
            Integral[7][j] = -Integral[7][j];
            Integral[11][j] = -Integral[11][j];
            Integral[12][j] = -Integral[12][j];
            Integral[13][j] = -Integral[13][j];
            Integral[14][j] = -Integral[14][j];
         }
      }

      bool Good = true;
      for(int i = 0; i < 16; i++)
         for(int j = 0; j < 5; j++)
            if(Value[i][j] > 0.99 || (i <= 5 && Value[i][j] < 1e-35))
               Good = false;
      if(Good == false)
         continue;

      Fits.AddPoint(Value, Integral);

      if(Fits.SampleSize < DatasetSize)
         continue;

      FitResultSummary ResultTemp = Fits.DoFit();
      Results.push_back(ResultTemp);

      Fits.ClearPoints();
   }

   File.Close();

   TFile OutputFile("OutputFile.root", "RECREATE");

   TNtuple OutputTree("ResultTree", "", "A2A1:A2Phase:A3A1:A3Phase:N1:N2:F:A2A1Error:A2PhaseError:A3A1Error:A3PhaseError:N1Error:N2Error:FError:EDM:Status");

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100];
      Array[0] = Results[i].A2A1;      Array[7] = Results[i].A2A1Error;
      Array[1] = Results[i].A2Phase;   Array[8] = Results[i].A2PhaseError;
      Array[2] = Results[i].A3A1;      Array[9] = Results[i].A3A1Error;
      Array[3] = Results[i].A3Phase;   Array[10] = Results[i].A3PhaseError;
      Array[4] = Results[i].N1;        Array[11] = Results[i].N1Error;
      Array[5] = Results[i].N2;        Array[12] = Results[i].N2Error;
      Array[6] = Results[i].F;         Array[13] = Results[i].FError;

      Array[14] = Results[i].EDM;
      Array[15] = Results[i].FitStatus;
      
      OutputTree.Fill(Array);
   }

   OutputTree.SetAlias("A3Phase1", "(A3Phase+(A3A1<0)*3.1415926535)");
   OutputTree.SetAlias("A3Phase2", "(A3Phase1-int(A3Phase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3PrimaryPhase", "(A3Phase2+(A3Phase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2Phase1", "(A2Phase+(A2A1<0)*3.1415926535)");
   OutputTree.SetAlias("A2Phase2", "(A2Phase1-int(A2Phase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2PrimaryPhase", "(A2Phase2+(A2Phase2<0)*2*3.1415926535)");

   OutputTree.SetAlias("A", "sqrt(A2A1*A2A1+A3A1*A3A1+1)");
   OutputTree.SetAlias("A1A", "1/sqrt(A2A1*A2A1+A3A1*A3A1+1)");
   OutputTree.SetAlias("A2A", "abs(A2A1)/sqrt(A2A1*A2A1+A3A1*A3A1+1)");
   OutputTree.SetAlias("A3A", "abs(A3A1)/sqrt(A2A1*A2A1+A3A1*A3A1+1)");
   OutputTree.SetAlias("As", "sqrt(A2A1*A2A1/3.125/3.125+A3A1*A3A1/5/5+1)");
   OutputTree.SetAlias("A1sAs", "1/sqrt(A2A1*A2A1/3.125/3.125+A3A1*A3A1/5/5+1)");
   OutputTree.SetAlias("A2sAs", "abs(A2A1/3.125)/sqrt(A2A1*A2A1/3.125/3.125+A3A1*A3A1/5/5+1)");
   OutputTree.SetAlias("A3sAs", "abs(A3A1/5)/sqrt(A2A1*A2A1/3.125/3.125+A3A1*A3A1/5/5+1)");

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double A1R = 1;
   double A3R = Parameters[0] * cos(Parameters[1]);
   double A3I = Parameters[0] * sin(Parameters[1]);
   double A2R = Parameters[2] * cos(Parameters[3]);
   double A2I = Parameters[2] * sin(Parameters[3]);
   double F = Parameters[4];
   double N1 = Parameters[5];
   double N2 = Parameters[6];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value[5] = {0}, Integral[5] = {0}, Likelihood[5] = {0};
      double LikelihoodB[5] = {0};

      for(int i = 0; i < 5; i++)
      {
         Value[i] = A1R * A1R * V[1][i][iS] + A2R * A2R * V[2][i][iS] + A2I * A2I * V[3][i][iS]
            + A3R * A3R * V[4][i][iS] + A3I * A3I * V[5][i][iS]
            + A1R * A2R * V[6][i][iS] + A1R * A2I * V[7][i][iS] + A1R * A3R * V[8][i][iS]
            + A1R * A3I * V[9][i][iS] + A2R * A2I * V[10][i][iS]
            + A2R * A3R * V[11][i][iS] + A2R * A3I * V[12][i][iS] + A2I * A3R * V[13][i][iS]
            + A2I * A3I * V[14][i][iS] + A3R * A3I * V[15][i][iS];
         Integral[i] = A1R * A1R * I[1][i][iS] + A2R * A2R * I[2][i][iS] + A2I * A2I * I[3][i][iS]
            + A3R * A3R * I[4][i][iS] + A3I * A3I * I[5][i][iS]
            + A1R * A2R * I[6][i][iS] + A1R * A2I * I[7][i][iS] + A1R * A3R * I[8][i][iS]
            + A1R * A3I * I[9][i][iS] + A2R * A2I * I[10][i][iS]
            + A2R * A3R * I[11][i][iS] + A2R * A3I * I[12][i][iS] + A2I * A3R * I[13][i][iS]
            + A2I * A3I * I[14][i][iS] + A3R * A3I * I[15][i][iS];
         Likelihood[i] = Value[i] / Integral[i];

         LikelihoodB[i] = V[0][i][iS] / I[0][i][iS];
      }

      bool Good = true;
      for(int i = 0; i < 5; i++)
         if(Likelihood[i] < 0)
            Good = false;
      if(Good == false)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }
      double LSa = Likelihood[0];
      double LSb1 = (N1 > 0) ? (Likelihood[1] - Likelihood[0]) : (Likelihood[0] - Likelihood[2]);
      double LSb2 = (N2 > 0) ? (Likelihood[3] - Likelihood[0]) : (Likelihood[0] - Likelihood[4]);
      double LBa = LikelihoodB[0];
      double LBb1 = (N1 > 0) ? (LikelihoodB[1] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[2]);
      double LBb2 = (N2 > 0) ? (LikelihoodB[3] - LikelihoodB[0]) : (LikelihoodB[0] - LikelihoodB[4]);

      double SignalLikelihood = LSa + LSb1 * N1 + LSb2 * N2;
      double BackgroundLikelihood = LBa + LBb1 * N1 + LBb2 * N2;

      if(SignalLikelihood <= 0 || BackgroundLikelihood <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      LogTotal = LogTotal + log(SignalLikelihood * (1 - F) + BackgroundLikelihood * F) - N1 * N1 / 2 - N2 * N2 / 2;
   }

   return -LogTotal;
}

void FitClass::AddPoint(double v[16][5], double i[16][5])
{
   for(int i1 = 0; i1 < 16; i1++)
   {
      for(int i2 = 0; i2 < 5; i2++)
      {
         V[i1][i2].push_back(v[i1][i2]);
         I[i1][i2].push_back(i[i1][i2]);
      }
   }

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   for(int i1 = 0; i1 < 16; i1++)
   {
      for(int i2 = 0; i2 < 5; i2++)
      {
         V[i1][i2].clear();
         I[i1][i2].clear();
      }
   }

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit()
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   Worker->SetPrintLevel(1);
   Worker->SetMaxFunctionCalls(1000000);
   Worker->SetMaxIterations(100000);
   Worker->SetTolerance(1e-3);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 7);
   Worker->SetFunction(Function);

   Worker->SetLimitedVariable(0, "A3A1", 1.02, 0.5, -100, 100);
   Worker->SetLimitedVariable(1, "A3Phase", -0.1, 0.1, -PI * 10, PI * 10);
   Worker->SetLimitedVariable(2, "A2A1", 1.1, 0.5, -100, 100);
   Worker->SetLimitedVariable(3, "A2Phase", -0.1, 0.1, -PI * 10, PI * 10);
   Worker->SetLimitedVariable(4, "F", 0, 0, 0, 1);
   Worker->SetLimitedVariable(5, "N1", 0, 0, -1, 1);
   Worker->SetLimitedVariable(6, "N2", 0, 0, -1, 1);
   
   Worker->Minimize();

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.A3A1 = Parameters[0];
   Result.A3A1Error = Errors[0];
   Result.A3Phase = Parameters[1];
   Result.A3PhaseError = Errors[1];
   Result.A2A1 = Parameters[2];
   
   Result.A2Phase = Parameters[3];
   Result.A2PhaseError = Errors[3];
   Result.F = Parameters[4];
   Result.FError = Errors[4];
   Result.N1 = Parameters[5];
   Result.N1Error = Errors[5];
   Result.N2 = Parameters[6];
   Result.N2Error = Errors[6];
   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   delete Worker;

   return Result;
}




