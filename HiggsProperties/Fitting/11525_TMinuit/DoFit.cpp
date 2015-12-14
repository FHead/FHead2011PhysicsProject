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

struct FitResultSummary;
class FitClass;
int main();

#define PI 3.14159265358979323846264338327950288479716939937510

struct FitResultSummary
{
public:
   double A3A1, A3A1Error;
   double A3Phase, A3PhaseError;
   double F, FError;
   double N, NError;
   double EDM;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   vector<double> V11a;   vector<double> V33a;   vector<double> V44a;
   vector<double> V13a;   vector<double> V14a;   vector<double> V34a;   vector<double> VBa;
   vector<double> V11b;   vector<double> V33b;   vector<double> V44b;
   vector<double> V13b;   vector<double> V14b;   vector<double> V34b;   vector<double> VBb;
   vector<double> I11a;   vector<double> I33a;   vector<double> I44a;
   vector<double> I13a;   vector<double> I14a;   vector<double> I34a;   vector<double> IBa;
   vector<double> I11b;   vector<double> I33b;   vector<double> I44b;
   vector<double> I13b;   vector<double> I14b;   vector<double> I34b;   vector<double> IBb;
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihood(const double *Parameters) const;

   void AddPoint(double v11a, double v33a, double v44a, double v13a, double v14a, double v34a, double vba,
      double v11b, double v33b, double v44b, double v13b, double v14b, double v34b, double vbb,
      double i11a, double i33a, double i44a, double i13a, double i14a, double i34a, double iba,
      double i11b, double i33b, double i44b, double i13b, double i14b, double i34b, double ibb);
   void ClearPoints();

   FitResultSummary DoFit();
};

int main()
{
   TFile File("FitTree.root");
   TTree *Tree = (TTree *)File.Get("OutputTree");

   float V11a, V33a, V44a, V13a, V14a, V34a, VBa, V11b, V33b, V44b, V13b, V14b, V34b, VBb;
   float I11a, I33a, I44a, I13a, I14a, I34a, IBa, I11b, I33b, I44b, I13b, I14b, I34b, IBb;

   Tree->SetBranchAddress("V11a", &V11a);   Tree->SetBranchAddress("V11b", &V11b);
   Tree->SetBranchAddress("V33a", &V33a);   Tree->SetBranchAddress("V33b", &V33b);
   Tree->SetBranchAddress("V44a", &V44a);   Tree->SetBranchAddress("V44b", &V44b);
   Tree->SetBranchAddress("V13a", &V13a);   Tree->SetBranchAddress("V13b", &V13b);
   Tree->SetBranchAddress("V14a", &V14a);   Tree->SetBranchAddress("V14b", &V14b);
   Tree->SetBranchAddress("V34a", &V34a);   Tree->SetBranchAddress("V34b", &V34b);
   Tree->SetBranchAddress("VBa", &VBa);     Tree->SetBranchAddress("VBb", &VBb);

   Tree->SetBranchAddress("I11a", &I11a);   Tree->SetBranchAddress("I11b", &I11b);
   Tree->SetBranchAddress("I33a", &I33a);   Tree->SetBranchAddress("I33b", &I33b);
   Tree->SetBranchAddress("I44a", &I44a);   Tree->SetBranchAddress("I44b", &I44b);
   Tree->SetBranchAddress("I13a", &I13a);   Tree->SetBranchAddress("I13b", &I13b);
   Tree->SetBranchAddress("I14a", &I14a);   Tree->SetBranchAddress("I14b", &I14b);
   Tree->SetBranchAddress("I34a", &I34a);   Tree->SetBranchAddress("I34b", &I34b);
   Tree->SetBranchAddress("IBa", &IBa);     Tree->SetBranchAddress("IBb", &IBb);

   FitClass Fits;

   vector<FitResultSummary> Results;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      Fits.AddPoint(V11a, V33a, V44a, V13a, V14a, V34a, VBa, V11b, V33b, V44b, V13b, V14b, V34b, VBb,
         I11a, I33a, I44a, I13a, I14a, I34a, IBa, I11b, I33b, I44b, I13b, I14b, I34b, IBb);

      if(Fits.SampleSize < 30)
         continue;

      FitResultSummary ResultTemp = Fits.DoFit();
      Results.push_back(ResultTemp);

      Fits.ClearPoints();
   }

   File.Close();

   TFile OutputFile("OutputFile.root", "RECREATE");

   TNtuple ResultTree("ResultTree", "Result tree",
      "A3A1:A3A1Error:A3Phase:A3PhaseError:N:NError:F:FError:EDM:FitStatus");
   for(int i = 0; i < (int)Results.size(); i++)
   {
      ResultTree.Fill(Results[i].A3A1, Results[i].A3A1Error, Results[i].A3Phase, Results[i].A3PhaseError,
         Results[i].N, Results[i].NError, Results[i].F, Results[i].FError,
         Results[i].EDM, Results[i].FitStatus);
   }

   ResultTree.SetAlias("A3Phase1", "A3Phase+(A3A1<0)*3.1415926535");
   ResultTree.SetAlias("A3Phase2", "(A3Phase1-int(A3Phase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A3FinalPhase", "(A3Phase2+(A3Phase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A3A1Final", "A3A1*(1+(A3A1<0)*(-2))");

   ResultTree.Write();

   OutputFile.Close();

   return 0;
}

double FitClass::CalculateLogLikelihood(const double *Parameters) const 
{
   double A1 = 1;
   double A3 = Parameters[0] * cos(Parameters[1]);
   double A4 = Parameters[0] * sin(Parameters[1]);
   double F = Parameters[2];
   double N = Parameters[3];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double V11 = V11a[iS] + V11b[iS] * N;
      double V33 = V33a[iS] + V33b[iS] * N;
      double V44 = V44a[iS] + V44b[iS] * N;
      double V13 = V13a[iS] + V13b[iS] * N;
      double V14 = V14a[iS] + V14b[iS] * N;
      double V34 = V34a[iS] + V34b[iS] * N;
      double VB = VBa[iS] + VBb[iS] * N;

      double I11 = I11a[iS] + I11b[iS] * N;
      double I33 = I33a[iS] + I33b[iS] * N;
      double I44 = I44a[iS] + I44b[iS] * N;
      double I13 = I13a[iS] + I13b[iS] * N;
      double I14 = I14a[iS] + I14b[iS] * N;
      double I34 = I34a[iS] + I34b[iS] * N;
      double IB = IBa[iS] + IBb[iS] * N;
      
      double Top = A1 * A1 * V11 + A3 * A3 * V33 + A4 * A4 * V44 + A1 * A3 * V13 + A1 * A4 * V14 + A3 * A4 * V34;
      double Bottom = A1 * A1 * I11 + A3 * A3 * I33 + A4 * A4 * I44 + A1 * A3 * I13 + A1 * A4 * I14 + A3 * A4 * I34;

      if(Top <= 0 || Bottom <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      double SignalLikelihood = Top / Bottom;
      double BackgroundLikelihood = VB / IB;

      LogTotal = LogTotal + log(SignalLikelihood * (1 - F) + BackgroundLikelihood * F) - N * N / 2;
   }

   return -LogTotal;
}

void FitClass::AddPoint(double v11a, double v33a, double v44a, double v13a, double v14a, double v34a, double vba,
   double v11b, double v33b, double v44b, double v13b, double v14b, double v34b, double vbb,
   double i11a, double i33a, double i44a, double i13a, double i14a, double i34a, double iba,
   double i11b, double i33b, double i44b, double i13b, double i14b, double i34b, double ibb)
{
   V11a.push_back(v11a);   V33a.push_back(v33a);   V44a.push_back(v44a);
   V13a.push_back(v13a);   V14a.push_back(v14a);   V34a.push_back(v34a);   VBa.push_back(vba);
   V11b.push_back(v11b);   V33b.push_back(v33b);   V44b.push_back(v44b);
   V13b.push_back(v13b);   V14b.push_back(v14b);   V34b.push_back(v34b);   VBb.push_back(vbb);
   I11a.push_back(i11a);   I33a.push_back(i33a);   I44a.push_back(i44a);
   I13a.push_back(i13a);   I14a.push_back(i14a);   I34a.push_back(i34a);   IBa.push_back(iba);
   I11b.push_back(i11b);   I33b.push_back(i33b);   I44b.push_back(i44b);
   I13b.push_back(i13b);   I14b.push_back(i14b);   I34b.push_back(i34b);   IBb.push_back(ibb);

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   V11a.clear();   V33a.clear();   V44a.clear();
   V13a.clear();   V14a.clear();   V34a.clear();   VBa.clear();
   V11b.clear();   V33b.clear();   V44b.clear();
   V13b.clear();   V14b.clear();   V34b.clear();   VBb.clear();
   I11a.clear();   I33a.clear();   I44a.clear();
   I13a.clear();   I14a.clear();   I34a.clear();   IBa.clear();
   I11b.clear();   I33b.clear();   I44b.clear();
   I13b.clear();   I14b.clear();   I34b.clear();   IBb.clear();

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit()
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");

   Worker->SetPrintLevel(-1);
   Worker->SetMaxFunctionCalls(1000000);
   Worker->SetMaxIterations(1000);
   Worker->SetTolerance(1e-3);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihood, 4);
   Worker->SetFunction(Function);

   Worker->SetLimitedVariable(0, "A3A1", 1, 0.1, -100, 100);
   Worker->SetLimitedVariable(1, "A3Phase", PI / 2, 0.1, -PI * 10, PI * 10);
   Worker->SetLimitedVariable(2, "F", 0.1, 0.01, 0, 1);
   Worker->SetLimitedVariable(3, "N", 0, 0.001, -1, 1);

   Worker->Minimize();

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.A3A1 = Parameters[0];
   Result.A3A1Error = Errors[0];
   Result.A3Phase = Parameters[1];
   Result.A3PhaseError = Errors[1];
   Result.F = Parameters[2];
   Result.FError = Errors[2];
   Result.N = Parameters[3];
   Result.NError = Errors[3];
   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   delete Worker;

   // cout << Result.A3A1 << " +- " << Result.A3A1Error << " "
   //    << Result.A3Phase << " +- " << Result.A3PhaseError << endl;

   return Result;
}




