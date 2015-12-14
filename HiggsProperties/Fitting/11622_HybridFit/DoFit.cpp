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
   double A2A1, A2A1Error;
   double A2Phase, A2PhaseError;
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
   vector<double> V11a;   vector<double> V22a;   vector<double> V33a;   vector<double> V44a;
   vector<double> V55a;   vector<double> V12a;   vector<double> V13a;   vector<double> V14a;
   vector<double> V15a;   vector<double> V23a;   vector<double> V24a;   vector<double> V25a;
   vector<double> V34a;   vector<double> V35a;   vector<double> V45a;   vector<double> VBa;
   vector<double> V11b;   vector<double> V22b;   vector<double> V33b;   vector<double> V44b;
   vector<double> V55b;   vector<double> V12b;   vector<double> V13b;   vector<double> V14b;
   vector<double> V15b;   vector<double> V23b;   vector<double> V24b;   vector<double> V25b;
   vector<double> V34b;   vector<double> V35b;   vector<double> V45b;   vector<double> VBb;
   vector<double> I11a;   vector<double> I22a;   vector<double> I33a;   vector<double> I44a;
   vector<double> I55a;   vector<double> I12a;   vector<double> I13a;   vector<double> I14a;
   vector<double> I15a;   vector<double> I23a;   vector<double> I24a;   vector<double> I25a;
   vector<double> I34a;   vector<double> I35a;   vector<double> I45a;   vector<double> IBa;
   vector<double> I11b;   vector<double> I22b;   vector<double> I33b;   vector<double> I44b;
   vector<double> I55b;   vector<double> I12b;   vector<double> I13b;   vector<double> I14b;
   vector<double> I15b;   vector<double> I23b;   vector<double> I24b;   vector<double> I25b;
   vector<double> I34b;   vector<double> I35b;   vector<double> I45b;   vector<double> IBb;
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihood(const double *Parameters) const;

   void AddPoint(double v11a, double v22a, double v33a, double v44a, double v55a,
      double v12a, double v13a, double v14a, double v15a, double v23a,
      double v24a, double v25a, double v34a, double v35a, double v45a, double vba,
      double v11b, double v22b, double v33b, double v44b, double v55b,
      double v12b, double v13b, double v14b, double v15b, double v23b,
      double v24b, double v25b, double v34b, double v35b, double v45b, double vbb,
      double i11a, double i22a, double i33a, double i44a, double i55a,
      double i12a, double i13a, double i14a, double i15a, double i23a,
      double i24a, double i25a, double i34a, double i35a, double i45a, double iba,
      double i11b, double i22b, double i33b, double i44b, double i55b,
      double i12b, double i13b, double i14b, double i15b, double i23b,
      double i24b, double i25b, double i34b, double i35b, double i45b, double ibb);

   void ClearPoints();

   FitResultSummary DoFit();
};

int main()
{
   TFile File("FitTree.root");
   TTree *Tree = (TTree *)File.Get("OutputTree");

   float V11a, V22a, V33a, V44a, V55a, V12a, V13a, V14a, V15a, V23a, V24a, V25a, V34a, V35a, V45a, VBa;
   float V11b, V22b, V33b, V44b, V55b, V12b, V13b, V14b, V15b, V23b, V24b, V25b, V34b, V35b, V45b, VBb;
   float I11a, I22a, I33a, I44a, I55a, I12a, I13a, I14a, I15a, I23a, I24a, I25a, I34a, I35a, I45a, IBa;
   float I11b, I22b, I33b, I44b, I55b, I12b, I13b, I14b, I15b, I23b, I24b, I25b, I34b, I35b, I45b, IBb;

   Tree->SetBranchAddress("V11a", &V11a);   Tree->SetBranchAddress("V11b", &V11b);
   Tree->SetBranchAddress("V22a", &V22a);   Tree->SetBranchAddress("V22b", &V22b);
   Tree->SetBranchAddress("V33a", &V33a);   Tree->SetBranchAddress("V33b", &V33b);
   Tree->SetBranchAddress("V44a", &V44a);   Tree->SetBranchAddress("V44b", &V44b);
   Tree->SetBranchAddress("V55a", &V55a);   Tree->SetBranchAddress("V55b", &V55b);
   Tree->SetBranchAddress("V12a", &V12a);   Tree->SetBranchAddress("V12b", &V12b);
   Tree->SetBranchAddress("V13a", &V13a);   Tree->SetBranchAddress("V13b", &V13b);
   Tree->SetBranchAddress("V14a", &V14a);   Tree->SetBranchAddress("V14b", &V14b);
   Tree->SetBranchAddress("V15a", &V15a);   Tree->SetBranchAddress("V15b", &V15b);
   Tree->SetBranchAddress("V23a", &V23a);   Tree->SetBranchAddress("V23b", &V23b);
   Tree->SetBranchAddress("V24a", &V24a);   Tree->SetBranchAddress("V24b", &V24b);
   Tree->SetBranchAddress("V25a", &V25a);   Tree->SetBranchAddress("V25b", &V25b);
   Tree->SetBranchAddress("V34a", &V34a);   Tree->SetBranchAddress("V34b", &V34b);
   Tree->SetBranchAddress("V35a", &V35a);   Tree->SetBranchAddress("V35b", &V35b);
   Tree->SetBranchAddress("V45a", &V45a);   Tree->SetBranchAddress("V45b", &V45b);
   Tree->SetBranchAddress("VBa", &VBa);     Tree->SetBranchAddress("VBb", &VBb);

   Tree->SetBranchAddress("I11a", &I11a);   Tree->SetBranchAddress("I11b", &I11b);
   Tree->SetBranchAddress("I22a", &I22a);   Tree->SetBranchAddress("I22b", &I22b);
   Tree->SetBranchAddress("I33a", &I33a);   Tree->SetBranchAddress("I33b", &I33b);
   Tree->SetBranchAddress("I44a", &I44a);   Tree->SetBranchAddress("I44b", &I44b);
   Tree->SetBranchAddress("I55a", &I55a);   Tree->SetBranchAddress("I55b", &I55b);
   Tree->SetBranchAddress("I12a", &I12a);   Tree->SetBranchAddress("I12b", &I12b);
   Tree->SetBranchAddress("I13a", &I13a);   Tree->SetBranchAddress("I13b", &I13b);
   Tree->SetBranchAddress("I14a", &I14a);   Tree->SetBranchAddress("I14b", &I14b);
   Tree->SetBranchAddress("I15a", &I15a);   Tree->SetBranchAddress("I15b", &I15b);
   Tree->SetBranchAddress("I23a", &I23a);   Tree->SetBranchAddress("I23b", &I23b);
   Tree->SetBranchAddress("I24a", &I24a);   Tree->SetBranchAddress("I24b", &I24b);
   Tree->SetBranchAddress("I25a", &I25a);   Tree->SetBranchAddress("I25b", &I25b);
   Tree->SetBranchAddress("I34a", &I34a);   Tree->SetBranchAddress("I34b", &I34b);
   Tree->SetBranchAddress("I35a", &I35a);   Tree->SetBranchAddress("I35b", &I35b);
   Tree->SetBranchAddress("I45a", &I45a);   Tree->SetBranchAddress("I45b", &I45b);
   Tree->SetBranchAddress("IBa", &IBa);     Tree->SetBranchAddress("IBb", &IBb);

   FitClass Fits;

   vector<FitResultSummary> Results;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      Fits.AddPoint(V11a, V22a, V33a, V44a, V55a, V12a, V13a, V14a, V15a, V23a, V24a, V25a, V34a, V35a, V45a, VBa,
         V11b, V22b, V33b, V44b, V55b, V12b, V13b, V14b, V15b, V23b, V24b, V25b, V34b, V35b, V45b, VBb,
         I11a, I22a, I33a, I44a, I55a, I12a, I13a, I14a, I15a, I23a, I24a, I25a, I34a, I35a, I45a, IBa,
         I11b, I22b, I33b, I44b, I55b, I12b, I13b, I14b, I15b, I23b, I24b, I25b, I34b, I35b, I45b, IBb);

      if(Fits.SampleSize < 30)
         continue;

      FitResultSummary ResultTemp = Fits.DoFit();
      Results.push_back(ResultTemp);

      Fits.ClearPoints();
   }

   File.Close();

   TFile OutputFile("OutputFile.root", "RECREATE");

   TNtuple OutputTree("ResultTree", "", "A2A1:A2Phase:A3A1:A3Phase:N:F:A2A1Error:A2PhaseError:A3A1Error:A3PhaseError:NError:FError:EDM:Status");

   for(int i = 0; i < (int)Results.size(); i++)
   {
      OutputTree.Fill(Results[i].A2A1, Results[i].A2Phase, Results[i].A3A1, Results[i].A3Phase,
         Results[i].N, Results[i].F, Results[i].A2A1Error, Results[i].A2PhaseError,
         Results[i].A3A1Error, Results[i].A3PhaseError, Results[i].NError, Results[i].FError,
         Results[i].EDM, Results[i].FitStatus);
   }

   OutputTree.SetAlias("A3Phase1", "(A3Phase+(A3A1<0)*3.1415926535)");
   OutputTree.SetAlias("A3Phase2", "(A3Phase1-int(A3Phase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3PrimaryPhase", "(A3Phase2+(A3Phase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2Phase1", "(A2Phase+(A2A1<0)*3.1415926535)");
   OutputTree.SetAlias("A2Phase2", "(A2Phase1-int(A2Phase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2PrimaryPhase", "(A2Phase2+(A2Phase2<0)*2*3.1415926535)");

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

double FitClass::CalculateLogLikelihood(const double *Parameters) const
{
   double A1 = 1;
   double A3 = Parameters[0] * cos(Parameters[1]);
   double A4 = Parameters[0] * sin(Parameters[1]);
   double A2 = Parameters[2] * cos(Parameters[3]);
   double A5 = Parameters[2] * sin(Parameters[3]);
   double F = Parameters[4];
   // double N = Parameters[5];

   double N = 0;

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double V11 = V11a[iS] + V11b[iS] * N;
      double V22 = V22a[iS] + V22b[iS] * N;
      double V33 = V33a[iS] + V33b[iS] * N;
      double V44 = V44a[iS] + V44b[iS] * N;
      double V55 = V55a[iS] + V55b[iS] * N;
      double V12 = V12a[iS] + V12b[iS] * N;
      double V13 = V13a[iS] + V13b[iS] * N;
      double V14 = V14a[iS] + V14b[iS] * N;
      double V15 = V15a[iS] + V15b[iS] * N;
      double V23 = V23a[iS] + V23b[iS] * N;
      double V24 = V24a[iS] + V24b[iS] * N;
      double V25 = V25a[iS] + V25b[iS] * N;
      double V34 = V34a[iS] + V34b[iS] * N;
      double V35 = V35a[iS] + V35b[iS] * N;
      double V45 = V45a[iS] + V45b[iS] * N;
      double VB = VBa[iS] + VBb[iS] * N;

      double I11 = I11a[iS] + I11b[iS] * N;
      double I22 = I22a[iS] + I22b[iS] * N;
      double I33 = I33a[iS] + I33b[iS] * N;
      double I44 = I44a[iS] + I44b[iS] * N;
      double I55 = I55a[iS] + I55b[iS] * N;
      double I12 = I12a[iS] + I12b[iS] * N;
      double I13 = I13a[iS] + I13b[iS] * N;
      double I14 = I14a[iS] + I14b[iS] * N;
      double I15 = I15a[iS] + I15b[iS] * N;
      double I23 = I23a[iS] + I23b[iS] * N;
      double I24 = I24a[iS] + I24b[iS] * N;
      double I25 = I25a[iS] + I25b[iS] * N;
      double I34 = I34a[iS] + I34b[iS] * N;
      double I35 = I35a[iS] + I35b[iS] * N;
      double I45 = I45a[iS] + I45b[iS] * N;
      double IB = IBa[iS] + IBb[iS] * N;

      double Top = A1 * A1 * V11 + A2 * A2 * V22 + A3 * A3 * V33 + A4 * A4 * V44 + A5 * A5 * V55
         + A1 * A2 * V12 + A1 * A3 * V13 + A1 * A4 * V14 + A1 * A5 * V15 + A2 * A3 * V23
         + A2 * A4 * V24 + A2 * A5 * V25 + A3 * A4 * V34 + A3 * A5 * V35 + A4 * A5 * V45;
      double Bottom = A1 * A1 * I11 + A2 * A2 * I22 + A3 * A3 * I33 + A4 * A4 * I44 + A5 * A5 * I55
         + A1 * A2 * I12 + A1 * A3 * I13 + A1 * A4 * I14 + A1 * A5 * I15 + A2 * A3 * I23
         + A2 * A4 * I24 + A2 * A5 * I25 + A3 * A4 * I34 + A3 * A5 * I35 + A4 * A5 * I45;

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

void FitClass::AddPoint(double v11a, double v22a, double v33a, double v44a, double v55a,
      double v12a, double v13a, double v14a, double v15a, double v23a,
      double v24a, double v25a, double v34a, double v35a, double v45a, double vba,
      double v11b, double v22b, double v33b, double v44b, double v55b,
      double v12b, double v13b, double v14b, double v15b, double v23b,
      double v24b, double v25b, double v34b, double v35b, double v45b, double vbb,
      double i11a, double i22a, double i33a, double i44a, double i55a,
      double i12a, double i13a, double i14a, double i15a, double i23a,
      double i24a, double i25a, double i34a, double i35a, double i45a, double iba,
      double i11b, double i22b, double i33b, double i44b, double i55b,
      double i12b, double i13b, double i14b, double i15b, double i23b,
      double i24b, double i25b, double i34b, double i35b, double i45b, double ibb)
{
   V11a.push_back(v11a);   V22a.push_back(v22a);   V33a.push_back(v33a);   V44a.push_back(v44a);
   V55a.push_back(v55a);   V12a.push_back(v12a);   V13a.push_back(v13a);   V14a.push_back(v14a);
   V15a.push_back(v15a);   V23a.push_back(v23a);   V24a.push_back(v24a);   V25a.push_back(v25a);
   V34a.push_back(v34a);   V35a.push_back(v35a);   V45a.push_back(v45a);   VBa.push_back(vba);
   V11b.push_back(v11b);   V22b.push_back(v22b);   V33b.push_back(v33b);   V44b.push_back(v44b);
   V55b.push_back(v55b);   V12b.push_back(v12b);   V13b.push_back(v13b);   V14b.push_back(v14b);
   V15b.push_back(v15b);   V23b.push_back(v23b);   V24b.push_back(v24b);   V25b.push_back(v25b);
   V34b.push_back(v34b);   V35b.push_back(v35b);   V45b.push_back(v45b);   VBb.push_back(vbb);
   I11a.push_back(i11a);   I22a.push_back(i22a);   I33a.push_back(i33a);   I44a.push_back(i44a);
   I55a.push_back(i55a);   I12a.push_back(i12a);   I13a.push_back(i13a);   I14a.push_back(i14a);
   I15a.push_back(i15a);   I23a.push_back(i23a);   I24a.push_back(i24a);   I25a.push_back(i25a);
   I34a.push_back(i34a);   I35a.push_back(i35a);   I45a.push_back(i45a);   IBa.push_back(iba);
   I11b.push_back(i11b);   I22b.push_back(i22b);   I33b.push_back(i33b);   I44b.push_back(i44b);
   I55b.push_back(i55b);   I12b.push_back(i12b);   I13b.push_back(i13b);   I14b.push_back(i14b);
   I15b.push_back(i15b);   I23b.push_back(i23b);   I24b.push_back(i24b);   I25b.push_back(i25b);
   I34b.push_back(i34b);   I35b.push_back(i35b);   I45b.push_back(i45b);   IBb.push_back(ibb);

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   V11a.clear();   V22a.clear();   V33a.clear();   V44a.clear();
   V55a.clear();   V12a.clear();   V13a.clear();   V14a.clear();
   V15a.clear();   V23a.clear();   V24a.clear();   V25a.clear();
   V34a.clear();   V35a.clear();   V45a.clear();   VBa.clear();
   V11b.clear();   V22b.clear();   V33b.clear();   V44b.clear();
   V55b.clear();   V12b.clear();   V13b.clear();   V14b.clear();
   V15b.clear();   V23b.clear();   V24b.clear();   V25b.clear();
   V34b.clear();   V35b.clear();   V45b.clear();   VBb.clear();
   I11a.clear();   I22a.clear();   I33a.clear();   I44a.clear();
   I55a.clear();   I12a.clear();   I13a.clear();   I14a.clear();
   I15a.clear();   I23a.clear();   I24a.clear();   I25a.clear();
   I34a.clear();   I35a.clear();   I45a.clear();   IBa.clear();
   I11b.clear();   I22b.clear();   I33b.clear();   I44b.clear();
   I55b.clear();   I12b.clear();   I13b.clear();   I14b.clear();
   I15b.clear();   I23b.clear();   I24b.clear();   I25b.clear();
   I34b.clear();   I35b.clear();   I45b.clear();   IBb.clear();

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit()
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");

   Worker->SetPrintLevel(1);
   Worker->SetMaxFunctionCalls(1000000);
   Worker->SetMaxIterations(1000);
   Worker->SetTolerance(1e-3);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihood, 5);
   Worker->SetFunction(Function);

   Worker->SetLimitedVariable(0, "A3A1", 0, 0.1, -500, 500);
   Worker->SetLimitedVariable(1, "A3Phase", 0, 0.1, -PI * 10, PI * 10);
   Worker->SetLimitedVariable(2, "A2A1", 0, 0.5, -500, 500);
   Worker->SetLimitedVariable(3, "A2Phase", 0, 0.5, -PI * 10, PI * 10);
   Worker->SetLimitedVariable(4, "F", 0.001, 0.001, 0, 1);
   // Worker->SetLimitedVariable(5, "N", 0, 0.001, -1, 1);

   Worker->Minimize();

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.A3A1 = Parameters[0];
   Result.A3A1Error = Errors[0];
   Result.A3Phase = Parameters[1];
   Result.A3PhaseError = Errors[1];
   Result.A2A1 = Parameters[2];
   Result.A2A1Error = Errors[2];
   Result.A2Phase = Parameters[3];
   Result.A2PhaseError = Errors[3];
   Result.F = Parameters[4];
   Result.FError = Errors[4];
   Result.N = Parameters[5];
   Result.NError = Errors[5];
   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   delete Worker;

   return Result;
}




