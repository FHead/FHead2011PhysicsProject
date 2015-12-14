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
   double N1, N1Error;
   double N2, N2Error;
   double EDM;
   int FitStatus;
};

class FitClass
{
public:
   int SampleSize;
   vector<double> L11C;   vector<double> L22C;   vector<double> L33C;   vector<double> L44C;
   vector<double> L55C;   vector<double> L12C;   vector<double> L13C;   vector<double> L14C;
   vector<double> L15C;   vector<double> L23C;   vector<double> L24C;   vector<double> L25C;
   vector<double> L34C;   vector<double> L35C;   vector<double> L45C;   vector<double> LBC;
   vector<double> L11U;   vector<double> L22U;   vector<double> L33U;   vector<double> L44U;
   vector<double> L55U;   vector<double> L12U;   vector<double> L13U;   vector<double> L14U;
   vector<double> L15U;   vector<double> L23U;   vector<double> L24U;   vector<double> L25U;
   vector<double> L34U;   vector<double> L35U;   vector<double> L45U;   vector<double> LBU;
   vector<double> L11D;   vector<double> L22D;   vector<double> L33D;   vector<double> L44D;
   vector<double> L55D;   vector<double> L12D;   vector<double> L13D;   vector<double> L14D;
   vector<double> L15D;   vector<double> L23D;   vector<double> L24D;   vector<double> L25D;
   vector<double> L34D;   vector<double> L35D;   vector<double> L45D;   vector<double> LBD;
   vector<double> L11W;   vector<double> L22W;   vector<double> L33W;   vector<double> L44W;
   vector<double> L55W;   vector<double> L12W;   vector<double> L13W;   vector<double> L14W;
   vector<double> L15W;   vector<double> L23W;   vector<double> L24W;   vector<double> L25W;
   vector<double> L34W;   vector<double> L35W;   vector<double> L45W;   vector<double> LBW;
   vector<double> L11N;   vector<double> L22N;   vector<double> L33N;   vector<double> L44N;
   vector<double> L55N;   vector<double> L12N;   vector<double> L13N;   vector<double> L14N;
   vector<double> L15N;   vector<double> L23N;   vector<double> L24N;   vector<double> L25N;
   vector<double> L34N;   vector<double> L35N;   vector<double> L45N;   vector<double> LBN;
   vector<double> I11C;   vector<double> I22C;   vector<double> I33C;   vector<double> I44C;
   vector<double> I55C;   vector<double> I12C;   vector<double> I13C;   vector<double> I14C;
   vector<double> I15C;   vector<double> I23C;   vector<double> I24C;   vector<double> I25C;
   vector<double> I34C;   vector<double> I35C;   vector<double> I45C;   vector<double> IBC;
   vector<double> I11U;   vector<double> I22U;   vector<double> I33U;   vector<double> I44U;
   vector<double> I55U;   vector<double> I12U;   vector<double> I13U;   vector<double> I14U;
   vector<double> I15U;   vector<double> I23U;   vector<double> I24U;   vector<double> I25U;
   vector<double> I34U;   vector<double> I35U;   vector<double> I45U;   vector<double> IBU;
   vector<double> I11D;   vector<double> I22D;   vector<double> I33D;   vector<double> I44D;
   vector<double> I55D;   vector<double> I12D;   vector<double> I13D;   vector<double> I14D;
   vector<double> I15D;   vector<double> I23D;   vector<double> I24D;   vector<double> I25D;
   vector<double> I34D;   vector<double> I35D;   vector<double> I45D;   vector<double> IBD;
   vector<double> I11W;   vector<double> I22W;   vector<double> I33W;   vector<double> I44W;
   vector<double> I55W;   vector<double> I12W;   vector<double> I13W;   vector<double> I14W;
   vector<double> I15W;   vector<double> I23W;   vector<double> I24W;   vector<double> I25W;
   vector<double> I34W;   vector<double> I35W;   vector<double> I45W;   vector<double> IBW;
   vector<double> I11N;   vector<double> I22N;   vector<double> I33N;   vector<double> I44N;
   vector<double> I55N;   vector<double> I12N;   vector<double> I13N;   vector<double> I14N;
   vector<double> I15N;   vector<double> I23N;   vector<double> I24N;   vector<double> I25N;
   vector<double> I34N;   vector<double> I35N;   vector<double> I45N;   vector<double> IBN;
public:
   FitClass() : SampleSize(0) {}

   double CalculateLogLikelihoodUpDown(const double *Parameters) const;
   double CalculateLogLikelihoodNarrowWide(const double *Parameters) const;
   double CalculateLogLikelihoodAll(const double *Parameters) const;

   void AddPoint(double l11c, double l22c, double l33c, double l44c, double l55c,
      double l12c, double l13c, double l14c, double l15c, double l23c,
      double l24c, double l25c, double l34c, double l35c, double l45c, double lbc,
      double l11u, double l22u, double l33u, double l44u, double l55u,
      double l12u, double l13u, double l14u, double l15u, double l23u,
      double l24u, double l25u, double l34u, double l35u, double l45u, double lbu,
      double l11d, double l22d, double l33d, double l44d, double l55d,
      double l12d, double l13d, double l14d, double l15d, double l23d,
      double l24d, double l25d, double l34d, double l35d, double l45d, double lbd,
      double l11w, double l22w, double l33w, double l44w, double l55w,
      double l12w, double l13w, double l14w, double l15w, double l23w,
      double l24w, double l25w, double l34w, double l35w, double l45w, double lbw,
      double l11n, double l22n, double l33n, double l44n, double l55n,
      double l12n, double l13n, double l14n, double l15n, double l23n,
      double l24n, double l25n, double l34n, double l35n, double l45n, double lbn,
      double i11c, double i22c, double i33c, double i44c, double i55c,
      double i12c, double i13c, double i14c, double i15c, double i23c,
      double i24c, double i25c, double i34c, double i35c, double i45c, double ibc,
      double i11u, double i22u, double i33u, double i44u, double i55u,
      double i12u, double i13u, double i14u, double i15u, double i23u,
      double i24u, double i25u, double i34u, double i35u, double i45u, double ibu,
      double i11d, double i22d, double i33d, double i44d, double i55d,
      double i12d, double i13d, double i14d, double i15d, double i23d,
      double i24d, double i25d, double i34d, double i35d, double i45d, double ibd,
      double i11w, double i22w, double i33w, double i44w, double i55w,
      double i12w, double i13w, double i14w, double i15w, double i23w,
      double i24w, double i25w, double i34w, double i35w, double i45w, double ibw,
      double i11n, double i22n, double i33n, double i44n, double i55n,
      double i12n, double i13n, double i14n, double i15n, double i23n,
      double i24n, double i25n, double i34n, double i35n, double i45n, double ibn);
   void ClearPoints();

   FitResultSummary DoFit();
};

int main()
{
   TFile File("FitTree.root");
   TTree *Tree = (TTree *)File.Get("OutputTree");

   float L11C, L22C, L33C, L44C, L55C, L12C, L13C, L14C, L15C, L23C, L24C, L25C, L34C, L35C, L45C, LBC;
   float L11U, L22U, L33U, L44U, L55U, L12U, L13U, L14U, L15U, L23U, L24U, L25U, L34U, L35U, L45U, LBU;
   float L11D, L22D, L33D, L44D, L55D, L12D, L13D, L14D, L15D, L23D, L24D, L25D, L34D, L35D, L45D, LBD;
   float L11W, L22W, L33W, L44W, L55W, L12W, L13W, L14W, L15W, L23W, L24W, L25W, L34W, L35W, L45W, LBW;
   float L11N, L22N, L33N, L44N, L55N, L12N, L13N, L14N, L15N, L23N, L24N, L25N, L34N, L35N, L45N, LBN;
   float I11C, I22C, I33C, I44C, I55C, I12C, I13C, I14C, I15C, I23C, I24C, I25C, I34C, I35C, I45C, IBC;
   float I11U, I22U, I33U, I44U, I55U, I12U, I13U, I14U, I15U, I23U, I24U, I25U, I34U, I35U, I45U, IBU;
   float I11D, I22D, I33D, I44D, I55D, I12D, I13D, I14D, I15D, I23D, I24D, I25D, I34D, I35D, I45D, IBD;
   float I11W, I22W, I33W, I44W, I55W, I12W, I13W, I14W, I15W, I23W, I24W, I25W, I34W, I35W, I45W, IBW;
   float I11N, I22N, I33N, I44N, I55N, I12N, I13N, I14N, I15N, I23N, I24N, I25N, I34N, I35N, I45N, IBN;

   Tree->SetBranchAddress("L11C", &L11C);   Tree->SetBranchAddress("I11C", &I11C);
   Tree->SetBranchAddress("L22C", &L22C);   Tree->SetBranchAddress("I22C", &I22C);
   Tree->SetBranchAddress("L33C", &L33C);   Tree->SetBranchAddress("I33C", &I33C);
   Tree->SetBranchAddress("L44C", &L44C);   Tree->SetBranchAddress("I44C", &I44C);
   Tree->SetBranchAddress("L55C", &L55C);   Tree->SetBranchAddress("I55C", &I55C);
   Tree->SetBranchAddress("L12C", &L12C);   Tree->SetBranchAddress("I12C", &I12C);
   Tree->SetBranchAddress("L13C", &L13C);   Tree->SetBranchAddress("I13C", &I13C);
   Tree->SetBranchAddress("L14C", &L14C);   Tree->SetBranchAddress("I14C", &I14C);
   Tree->SetBranchAddress("L15C", &L15C);   Tree->SetBranchAddress("I15C", &I15C);
   Tree->SetBranchAddress("L23C", &L23C);   Tree->SetBranchAddress("I23C", &I23C);
   Tree->SetBranchAddress("L24C", &L24C);   Tree->SetBranchAddress("I24C", &I24C);
   Tree->SetBranchAddress("L25C", &L25C);   Tree->SetBranchAddress("I25C", &I25C);
   Tree->SetBranchAddress("L34C", &L34C);   Tree->SetBranchAddress("I34C", &I34C);
   Tree->SetBranchAddress("L35C", &L35C);   Tree->SetBranchAddress("I35C", &I35C);
   Tree->SetBranchAddress("L45C", &L45C);   Tree->SetBranchAddress("I45C", &I45C);
   Tree->SetBranchAddress("LBC", &LBC);     Tree->SetBranchAddress("IBC", &IBC);

   Tree->SetBranchAddress("L11U", &L11U);   Tree->SetBranchAddress("I11U", &I11U);
   Tree->SetBranchAddress("L22U", &L22U);   Tree->SetBranchAddress("I22U", &I22U);
   Tree->SetBranchAddress("L33U", &L33U);   Tree->SetBranchAddress("I33U", &I33U);
   Tree->SetBranchAddress("L44U", &L44U);   Tree->SetBranchAddress("I44U", &I44U);
   Tree->SetBranchAddress("L55U", &L55U);   Tree->SetBranchAddress("I55U", &I55U);
   Tree->SetBranchAddress("L12U", &L12U);   Tree->SetBranchAddress("I12U", &I12U);
   Tree->SetBranchAddress("L13U", &L13U);   Tree->SetBranchAddress("I13U", &I13U);
   Tree->SetBranchAddress("L14U", &L14U);   Tree->SetBranchAddress("I14U", &I14U);
   Tree->SetBranchAddress("L15U", &L15U);   Tree->SetBranchAddress("I15U", &I15U);
   Tree->SetBranchAddress("L23U", &L23U);   Tree->SetBranchAddress("I23U", &I23U);
   Tree->SetBranchAddress("L24U", &L24U);   Tree->SetBranchAddress("I24U", &I24U);
   Tree->SetBranchAddress("L25U", &L25U);   Tree->SetBranchAddress("I25U", &I25U);
   Tree->SetBranchAddress("L34U", &L34U);   Tree->SetBranchAddress("I34U", &I34U);
   Tree->SetBranchAddress("L35U", &L35U);   Tree->SetBranchAddress("I35U", &I35U);
   Tree->SetBranchAddress("L45U", &L45U);   Tree->SetBranchAddress("I45U", &I45U);
   Tree->SetBranchAddress("LBU", &LBU);     Tree->SetBranchAddress("IBU", &IBU);

   Tree->SetBranchAddress("L11D", &L11D);   Tree->SetBranchAddress("I11D", &I11D);
   Tree->SetBranchAddress("L22D", &L22D);   Tree->SetBranchAddress("I22D", &I22D);
   Tree->SetBranchAddress("L33D", &L33D);   Tree->SetBranchAddress("I33D", &I33D);
   Tree->SetBranchAddress("L44D", &L44D);   Tree->SetBranchAddress("I44D", &I44D);
   Tree->SetBranchAddress("L55D", &L55D);   Tree->SetBranchAddress("I55D", &I55D);
   Tree->SetBranchAddress("L12D", &L12D);   Tree->SetBranchAddress("I12D", &I12D);
   Tree->SetBranchAddress("L13D", &L13D);   Tree->SetBranchAddress("I13D", &I13D);
   Tree->SetBranchAddress("L14D", &L14D);   Tree->SetBranchAddress("I14D", &I14D);
   Tree->SetBranchAddress("L15D", &L15D);   Tree->SetBranchAddress("I15D", &I15D);
   Tree->SetBranchAddress("L23D", &L23D);   Tree->SetBranchAddress("I23D", &I23D);
   Tree->SetBranchAddress("L24D", &L24D);   Tree->SetBranchAddress("I24D", &I24D);
   Tree->SetBranchAddress("L25D", &L25D);   Tree->SetBranchAddress("I25D", &I25D);
   Tree->SetBranchAddress("L34D", &L34D);   Tree->SetBranchAddress("I34D", &I34D);
   Tree->SetBranchAddress("L35D", &L35D);   Tree->SetBranchAddress("I35D", &I35D);
   Tree->SetBranchAddress("L45D", &L45D);   Tree->SetBranchAddress("I45D", &I45D);
   Tree->SetBranchAddress("LBD", &LBD);     Tree->SetBranchAddress("IBD", &IBD);

   Tree->SetBranchAddress("L11W", &L11W);   Tree->SetBranchAddress("I11W", &I11W);
   Tree->SetBranchAddress("L22W", &L22W);   Tree->SetBranchAddress("I22W", &I22W);
   Tree->SetBranchAddress("L33W", &L33W);   Tree->SetBranchAddress("I33W", &I33W);
   Tree->SetBranchAddress("L44W", &L44W);   Tree->SetBranchAddress("I44W", &I44W);
   Tree->SetBranchAddress("L55W", &L55W);   Tree->SetBranchAddress("I55W", &I55W);
   Tree->SetBranchAddress("L12W", &L12W);   Tree->SetBranchAddress("I12W", &I12W);
   Tree->SetBranchAddress("L13W", &L13W);   Tree->SetBranchAddress("I13W", &I13W);
   Tree->SetBranchAddress("L14W", &L14W);   Tree->SetBranchAddress("I14W", &I14W);
   Tree->SetBranchAddress("L15W", &L15W);   Tree->SetBranchAddress("I15W", &I15W);
   Tree->SetBranchAddress("L23W", &L23W);   Tree->SetBranchAddress("I23W", &I23W);
   Tree->SetBranchAddress("L24W", &L24W);   Tree->SetBranchAddress("I24W", &I24W);
   Tree->SetBranchAddress("L25W", &L25W);   Tree->SetBranchAddress("I25W", &I25W);
   Tree->SetBranchAddress("L34W", &L34W);   Tree->SetBranchAddress("I34W", &I34W);
   Tree->SetBranchAddress("L35W", &L35W);   Tree->SetBranchAddress("I35W", &I35W);
   Tree->SetBranchAddress("L45W", &L45W);   Tree->SetBranchAddress("I45W", &I45W);
   Tree->SetBranchAddress("LBW", &LBW);     Tree->SetBranchAddress("IBW", &IBW);

   Tree->SetBranchAddress("L11N", &L11N);   Tree->SetBranchAddress("I11N", &I11N);
   Tree->SetBranchAddress("L22N", &L22N);   Tree->SetBranchAddress("I22N", &I22N);
   Tree->SetBranchAddress("L33N", &L33N);   Tree->SetBranchAddress("I33N", &I33N);
   Tree->SetBranchAddress("L44N", &L44N);   Tree->SetBranchAddress("I44N", &I44N);
   Tree->SetBranchAddress("L55N", &L55N);   Tree->SetBranchAddress("I55N", &I55N);
   Tree->SetBranchAddress("L12N", &L12N);   Tree->SetBranchAddress("I12N", &I12N);
   Tree->SetBranchAddress("L13N", &L13N);   Tree->SetBranchAddress("I13N", &I13N);
   Tree->SetBranchAddress("L14N", &L14N);   Tree->SetBranchAddress("I14N", &I14N);
   Tree->SetBranchAddress("L15N", &L15N);   Tree->SetBranchAddress("I15N", &I15N);
   Tree->SetBranchAddress("L23N", &L23N);   Tree->SetBranchAddress("I23N", &I23N);
   Tree->SetBranchAddress("L24N", &L24N);   Tree->SetBranchAddress("I24N", &I24N);
   Tree->SetBranchAddress("L25N", &L25N);   Tree->SetBranchAddress("I25N", &I25N);
   Tree->SetBranchAddress("L34N", &L34N);   Tree->SetBranchAddress("I34N", &I34N);
   Tree->SetBranchAddress("L35N", &L35N);   Tree->SetBranchAddress("I35N", &I35N);
   Tree->SetBranchAddress("L45N", &L45N);   Tree->SetBranchAddress("I45N", &I45N);
   Tree->SetBranchAddress("LBN", &LBN);     Tree->SetBranchAddress("IBN", &IBN);

   FitClass Fits;

   vector<FitResultSummary> Results;

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      Fits.AddPoint(L11C, L22C, L33C, L44C, L55C, L12C, L13C, L14C, L15C, L23C, L24C, L25C, L34C, L35C, L45C, LBC,
         L11U, L22U, L33U, L44U, L55U, L12U, L13U, L14U, L15U, L23U, L24U, L25U, L34U, L35U, L45U, LBU,
         L11D, L22D, L33D, L44D, L55D, L12D, L13D, L14D, L15D, L23D, L24D, L25D, L34D, L35D, L45D, LBD,
         L11W, L22W, L33W, L44W, L55W, L12W, L13W, L14W, L15W, L23W, L24W, L25W, L34W, L35W, L45W, LBW,
         L11N, L22N, L33N, L44N, L55N, L12N, L13N, L14N, L15N, L23N, L24N, L25N, L34N, L35N, L45N, LBN,
         I11C, I22C, I33C, I44C, I55C, I12C, I13C, I14C, I15C, I23C, I24C, I25C, I34C, I35C, I45C, IBC,
         I11U, I22U, I33U, I44U, I55U, I12U, I13U, I14U, I15U, I23U, I24U, I25U, I34U, I35U, I45U, IBU,
         I11D, I22D, I33D, I44D, I55D, I12D, I13D, I14D, I15D, I23D, I24D, I25D, I34D, I35D, I45D, IBD,
         I11W, I22W, I33W, I44W, I55W, I12W, I13W, I14W, I15W, I23W, I24W, I25W, I34W, I35W, I45W, IBW,
         I11N, I22N, I33N, I44N, I55N, I12N, I13N, I14N, I15N, I23N, I24N, I25N, I34N, I35N, I45N, IBN);

      if(Fits.SampleSize < 30)
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

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

double FitClass::CalculateLogLikelihoodUpDown(const double *Parameters) const
{
   double A1 = 1;
   double A3 = Parameters[0] * cos(Parameters[1]);
   double A4 = Parameters[0] * sin(Parameters[1]);
   double A2 = Parameters[2] * cos(Parameters[3]);
   double A5 = Parameters[2] * sin(Parameters[3]);
   double F = Parameters[4];
   double N = Parameters[5];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double LC = A1 * A1 * L11C[iS] * I11C[iS] + A2 * A2 * L22C[iS] * I22C[iS] + A3 * A3 * L33C[iS] * I33C[iS]
         + A4 * A4 * L44C[iS] * I44C[iS] + A5 * A5 * L55C[iS] * I55C[iS]
         + A1 * A2 * L12C[iS] * I12C[iS] + A1 * A3 * L13C[iS] * I13C[iS] + A1 * A4 * L14C[iS] * I14C[iS]
         + A1 * A5 * L15C[iS] * I15C[iS] + A2 * A3 * L23C[iS] * I23C[iS]
         + A2 * A4 * L24C[iS] * I24C[iS] + A2 * A5 * L25C[iS] * I25C[iS] + A3 * A4 * L34C[iS] * I34C[iS]
         + A3 * A5 * L35C[iS] * I35C[iS] + A4 * A5 * L45C[iS] * I45C[iS];
      LC = LC / (A1 * A1 * I11C[iS] + A2 * A2 * I22C[iS] + A3 * A3 * I33C[iS]
         + A4 * A4 * I44C[iS] + A5 * A5 * I55C[iS]
         + A1 * A2 * I12C[iS] + A1 * A3 * I13C[iS] + A1 * A4 * I14C[iS]
         + A1 * A5 * I15C[iS] + A2 * A3 * I23C[iS]
         + A2 * A4 * I24C[iS] + A2 * A5 * I25C[iS] + A3 * A4 * I34C[iS]
         + A3 * A5 * I35C[iS] + A4 * A5 * I45C[iS]);

      double LU = A1 * A1 * L11U[iS] * I11U[iS] + A2 * A2 * L22U[iS] * I22U[iS] + A3 * A3 * L33U[iS] * I33U[iS]
         + A4 * A4 * L44U[iS] * I44U[iS] + A5 * A5 * L55U[iS] * I55U[iS]
         + A1 * A2 * L12U[iS] * I12U[iS] + A1 * A3 * L13U[iS] * I13U[iS] + A1 * A4 * L14U[iS] * I14U[iS]
         + A1 * A5 * L15U[iS] * I15U[iS] + A2 * A3 * L23U[iS] * I23U[iS]
         + A2 * A4 * L24U[iS] * I24U[iS] + A2 * A5 * L25U[iS] * I25U[iS] + A3 * A4 * L34U[iS] * I34U[iS]
         + A3 * A5 * L35U[iS] * I35U[iS] + A4 * A5 * L45U[iS] * I45U[iS];
      LU = LU / (A1 * A1 * I11U[iS] + A2 * A2 * I22U[iS] + A3 * A3 * I33U[iS]
         + A4 * A4 * I44U[iS] + A5 * A5 * I55U[iS]
         + A1 * A2 * I12U[iS] + A1 * A3 * I13U[iS] + A1 * A4 * I14U[iS]
         + A1 * A5 * I15U[iS] + A2 * A3 * I23U[iS]
         + A2 * A4 * I24U[iS] + A2 * A5 * I25U[iS] + A3 * A4 * I34U[iS]
         + A3 * A5 * I35U[iS] + A4 * A5 * I45U[iS]);

      double LD = A1 * A1 * L11D[iS] * I11D[iS] + A2 * A2 * L22D[iS] * I22D[iS] + A3 * A3 * L33D[iS] * I33D[iS]
         + A4 * A4 * L44D[iS] * I44D[iS] + A5 * A5 * L55D[iS] * I55D[iS]
         + A1 * A2 * L12D[iS] * I12D[iS] + A1 * A3 * L13D[iS] * I13D[iS] + A1 * A4 * L14D[iS] * I14D[iS]
         + A1 * A5 * L15D[iS] * I15D[iS] + A2 * A3 * L23D[iS] * I23D[iS]
         + A2 * A4 * L24D[iS] * I24D[iS] + A2 * A5 * L25D[iS] * I25D[iS] + A3 * A4 * L34D[iS] * I34D[iS]
         + A3 * A5 * L35D[iS] * I35D[iS] + A4 * A5 * L45D[iS] * I45D[iS];
      LD = LD / (A1 * A1 * I11D[iS] + A2 * A2 * I22D[iS] + A3 * A3 * I33D[iS]
         + A4 * A4 * I44D[iS] + A5 * A5 * I55D[iS]
         + A1 * A2 * I12D[iS] + A1 * A3 * I13D[iS] + A1 * A4 * I14D[iS]
         + A1 * A5 * I15D[iS] + A2 * A3 * I23D[iS]
         + A2 * A4 * I24D[iS] + A2 * A5 * I25D[iS] + A3 * A4 * I34D[iS]
         + A3 * A5 * I35D[iS] + A4 * A5 * I45D[iS]);

      if(LC <= 0 || LU <= 0 || LD <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      double LSa = (LC + LU + LD) / 3;
      double LSb = (LU - LD) / 2;
      double LBa = (LBC[iS]*IBC[iS] + LBU[iS]*IBU[iS] + LBD[iS]*IBD[iS]) / 3;
      double LBb = (LBU[iS]*IBU[iS] - LBD[iS]*IBD[iS]) / 2;

      // double LSa = LC;                  double LSb = 0;
      // double LBa = LBC[iS] * IBC[iS];   double LBb = 0;

      double SignalLikelihood = LSa + LSb * N;
      double BackgroundLikelihood = LBa + LBb * N;

      LogTotal = LogTotal + log(SignalLikelihood * (1 - F) + BackgroundLikelihood * F) - N * N / 2;
   }

   return -LogTotal;
}

double FitClass::CalculateLogLikelihoodNarrowWide(const double *Parameters) const
{
   double A1 = 1;
   double A3 = Parameters[0] * cos(Parameters[1]);
   double A4 = Parameters[0] * sin(Parameters[1]);
   double A2 = Parameters[2] * cos(Parameters[3]);
   double A5 = Parameters[2] * sin(Parameters[3]);
   double F = Parameters[4];
   double N = Parameters[5];

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double LC = A1 * A1 * L11C[iS] * I11C[iS] + A2 * A2 * L22C[iS] * I22C[iS] + A3 * A3 * L33C[iS] * I33C[iS]
         + A4 * A4 * L44C[iS] * I44C[iS] + A5 * A5 * L55C[iS] * I55C[iS]
         + A1 * A2 * L12C[iS] * I12C[iS] + A1 * A3 * L13C[iS] * I13C[iS] + A1 * A4 * L14C[iS] * I14C[iS]
         + A1 * A5 * L15C[iS] * I15C[iS] + A2 * A3 * L23C[iS] * I23C[iS]
         + A2 * A4 * L24C[iS] * I24C[iS] + A2 * A5 * L25C[iS] * I25C[iS] + A3 * A4 * L34C[iS] * I34C[iS]
         + A3 * A5 * L35C[iS] * I35C[iS] + A4 * A5 * L45C[iS] * I45C[iS];
      LC = LC / (A1 * A1 * I11C[iS] + A2 * A2 * I22C[iS] + A3 * A3 * I33C[iS]
         + A4 * A4 * I44C[iS] + A5 * A5 * I55C[iS]
         + A1 * A2 * I12C[iS] + A1 * A3 * I13C[iS] + A1 * A4 * I14C[iS]
         + A1 * A5 * I15C[iS] + A2 * A3 * I23C[iS]
         + A2 * A4 * I24C[iS] + A2 * A5 * I25C[iS] + A3 * A4 * I34C[iS]
         + A3 * A5 * I35C[iS] + A4 * A5 * I45C[iS]);

      double LW = A1 * A1 * L11W[iS] * I11W[iS] + A2 * A2 * L22W[iS] * I22W[iS] + A3 * A3 * L33W[iS] * I33W[iS]
         + A4 * A4 * L44W[iS] * I44W[iS] + A5 * A5 * L55W[iS] * I55W[iS]
         + A1 * A2 * L12W[iS] * I12W[iS] + A1 * A3 * L13W[iS] * I13W[iS] + A1 * A4 * L14W[iS] * I14W[iS]
         + A1 * A5 * L15W[iS] * I15W[iS] + A2 * A3 * L23W[iS] * I23W[iS]
         + A2 * A4 * L24W[iS] * I24W[iS] + A2 * A5 * L25W[iS] * I25W[iS] + A3 * A4 * L34W[iS] * I34W[iS]
         + A3 * A5 * L35W[iS] * I35W[iS] + A4 * A5 * L45W[iS] * I45W[iS];
      LW = LW / (A1 * A1 * I11W[iS] + A2 * A2 * I22W[iS] + A3 * A3 * I33W[iS]
         + A4 * A4 * I44W[iS] + A5 * A5 * I55W[iS]
         + A1 * A2 * I12W[iS] + A1 * A3 * I13W[iS] + A1 * A4 * I14W[iS]
         + A1 * A5 * I15W[iS] + A2 * A3 * I23W[iS]
         + A2 * A4 * I24W[iS] + A2 * A5 * I25W[iS] + A3 * A4 * I34W[iS]
         + A3 * A5 * I35W[iS] + A4 * A5 * I45W[iS]);

      double LN = A1 * A1 * L11N[iS] * I11N[iS] + A2 * A2 * L22N[iS] * I22N[iS] + A3 * A3 * L33N[iS] * I33N[iS]
         + A4 * A4 * L44N[iS] * I44N[iS] + A5 * A5 * L55N[iS] * I55N[iS]
         + A1 * A2 * L12N[iS] * I12N[iS] + A1 * A3 * L13N[iS] * I13N[iS] + A1 * A4 * L14N[iS] * I14N[iS]
         + A1 * A5 * L15N[iS] * I15N[iS] + A2 * A3 * L23N[iS] * I23N[iS]
         + A2 * A4 * L24N[iS] * I24N[iS] + A2 * A5 * L25N[iS] * I25N[iS] + A3 * A4 * L34N[iS] * I34N[iS]
         + A3 * A5 * L35N[iS] * I35N[iS] + A4 * A5 * L45N[iS] * I45N[iS];
      LN = LN / (A1 * A1 * I11N[iS] + A2 * A2 * I22N[iS] + A3 * A3 * I33N[iS]
         + A4 * A4 * I44N[iS] + A5 * A5 * I55N[iS]
         + A1 * A2 * I12N[iS] + A1 * A3 * I13N[iS] + A1 * A4 * I14N[iS]
         + A1 * A5 * I15N[iS] + A2 * A3 * I23N[iS]
         + A2 * A4 * I24N[iS] + A2 * A5 * I25N[iS] + A3 * A4 * I34N[iS]
         + A3 * A5 * I35N[iS] + A4 * A5 * I45N[iS]);

      if(LC <= 0 || LW <= 0 || LN <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      double LSa = (LC + LW + LN) / 3;
      double LSb = (LW - LN) / 2;
      double LBa = (LBC[iS]*IBC[iS] + LBW[iS]*IBW[iS] + LBN[iS]*IBN[iS]) / 3;
      double LBb = (LBW[iS]*IBW[iS] - LBN[iS]*IBN[iS]) / 2;

      double SignalLikelihood = LSa + LSb * N;
      double BackgroundLikelihood = LBa + LBb * N;

      LogTotal = LogTotal + log(SignalLikelihood * (1 - F) + BackgroundLikelihood * F) - N * N / 2;
   }

   return -LogTotal;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double A1 = 1;
   double A3 = Parameters[0] * cos(Parameters[1]);
   double A4 = Parameters[0] * sin(Parameters[1]);
   double A2 = Parameters[2] * cos(Parameters[3]);
   double A5 = Parameters[2] * sin(Parameters[3]);
   double F = Parameters[4];
   double N1 = Parameters[5];
   double N2 = Parameters[6];

   N1 = 0;
   N2 = 0;

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double LC = A1 * A1 * L11C[iS] * I11C[iS] + A2 * A2 * L22C[iS] * I22C[iS] + A3 * A3 * L33C[iS] * I33C[iS]
         + A4 * A4 * L44C[iS] * I44C[iS] + A5 * A5 * L55C[iS] * I55C[iS]
         + A1 * A2 * L12C[iS] * I12C[iS] + A1 * A3 * L13C[iS] * I13C[iS] + A1 * A4 * L14C[iS] * I14C[iS]
         + A1 * A5 * L15C[iS] * I15C[iS] + A2 * A3 * L23C[iS] * I23C[iS]
         + A2 * A4 * L24C[iS] * I24C[iS] + A2 * A5 * L25C[iS] * I25C[iS] + A3 * A4 * L34C[iS] * I34C[iS]
         + A3 * A5 * L35C[iS] * I35C[iS] + A4 * A5 * L45C[iS] * I45C[iS];
      LC = LC / (A1 * A1 * I11C[iS] + A2 * A2 * I22C[iS] + A3 * A3 * I33C[iS]
         + A4 * A4 * I44C[iS] + A5 * A5 * I55C[iS]
         + A1 * A2 * I12C[iS] + A1 * A3 * I13C[iS] + A1 * A4 * I14C[iS]
         + A1 * A5 * I15C[iS] + A2 * A3 * I23C[iS]
         + A2 * A4 * I24C[iS] + A2 * A5 * I25C[iS] + A3 * A4 * I34C[iS]
         + A3 * A5 * I35C[iS] + A4 * A5 * I45C[iS]);

      double LU = A1 * A1 * L11U[iS] * I11U[iS] + A2 * A2 * L22U[iS] * I22U[iS] + A3 * A3 * L33U[iS] * I33U[iS]
         + A4 * A4 * L44U[iS] * I44U[iS] + A5 * A5 * L55U[iS] * I55U[iS]
         + A1 * A2 * L12U[iS] * I12U[iS] + A1 * A3 * L13U[iS] * I13U[iS] + A1 * A4 * L14U[iS] * I14U[iS]
         + A1 * A5 * L15U[iS] * I15U[iS] + A2 * A3 * L23U[iS] * I23U[iS]
         + A2 * A4 * L24U[iS] * I24U[iS] + A2 * A5 * L25U[iS] * I25U[iS] + A3 * A4 * L34U[iS] * I34U[iS]
         + A3 * A5 * L35U[iS] * I35U[iS] + A4 * A5 * L45U[iS] * I45U[iS];
      LU = LU / (A1 * A1 * I11U[iS] + A2 * A2 * I22U[iS] + A3 * A3 * I33U[iS]
         + A4 * A4 * I44U[iS] + A5 * A5 * I55U[iS]
         + A1 * A2 * I12U[iS] + A1 * A3 * I13U[iS] + A1 * A4 * I14U[iS]
         + A1 * A5 * I15U[iS] + A2 * A3 * I23U[iS]
         + A2 * A4 * I24U[iS] + A2 * A5 * I25U[iS] + A3 * A4 * I34U[iS]
         + A3 * A5 * I35U[iS] + A4 * A5 * I45U[iS]);

      double LD = A1 * A1 * L11D[iS] * I11D[iS] + A2 * A2 * L22D[iS] * I22D[iS] + A3 * A3 * L33D[iS] * I33D[iS]
         + A4 * A4 * L44D[iS] * I44D[iS] + A5 * A5 * L55D[iS] * I55D[iS]
         + A1 * A2 * L12D[iS] * I12D[iS] + A1 * A3 * L13D[iS] * I13D[iS] + A1 * A4 * L14D[iS] * I14D[iS]
         + A1 * A5 * L15D[iS] * I15D[iS] + A2 * A3 * L23D[iS] * I23D[iS]
         + A2 * A4 * L24D[iS] * I24D[iS] + A2 * A5 * L25D[iS] * I25D[iS] + A3 * A4 * L34D[iS] * I34D[iS]
         + A3 * A5 * L35D[iS] * I35D[iS] + A4 * A5 * L45D[iS] * I45D[iS];
      LD = LD / (A1 * A1 * I11D[iS] + A2 * A2 * I22D[iS] + A3 * A3 * I33D[iS]
         + A4 * A4 * I44D[iS] + A5 * A5 * I55D[iS]
         + A1 * A2 * I12D[iS] + A1 * A3 * I13D[iS] + A1 * A4 * I14D[iS]
         + A1 * A5 * I15D[iS] + A2 * A3 * I23D[iS]
         + A2 * A4 * I24D[iS] + A2 * A5 * I25D[iS] + A3 * A4 * I34D[iS]
         + A3 * A5 * I35D[iS] + A4 * A5 * I45D[iS]);

      double LW = A1 * A1 * L11W[iS] * I11W[iS] + A2 * A2 * L22W[iS] * I22W[iS] + A3 * A3 * L33W[iS] * I33W[iS]
         + A4 * A4 * L44W[iS] * I44W[iS] + A5 * A5 * L55W[iS] * I55W[iS]
         + A1 * A2 * L12W[iS] * I12W[iS] + A1 * A3 * L13W[iS] * I13W[iS] + A1 * A4 * L14W[iS] * I14W[iS]
         + A1 * A5 * L15W[iS] * I15W[iS] + A2 * A3 * L23W[iS] * I23W[iS]
         + A2 * A4 * L24W[iS] * I24W[iS] + A2 * A5 * L25W[iS] * I25W[iS] + A3 * A4 * L34W[iS] * I34W[iS]
         + A3 * A5 * L35W[iS] * I35W[iS] + A4 * A5 * L45W[iS] * I45W[iS];
      LW = LW / (A1 * A1 * I11W[iS] + A2 * A2 * I22W[iS] + A3 * A3 * I33W[iS]
         + A4 * A4 * I44W[iS] + A5 * A5 * I55W[iS]
         + A1 * A2 * I12W[iS] + A1 * A3 * I13W[iS] + A1 * A4 * I14W[iS]
         + A1 * A5 * I15W[iS] + A2 * A3 * I23W[iS]
         + A2 * A4 * I24W[iS] + A2 * A5 * I25W[iS] + A3 * A4 * I34W[iS]
         + A3 * A5 * I35W[iS] + A4 * A5 * I45W[iS]);

      double LN = A1 * A1 * L11N[iS] * I11N[iS] + A2 * A2 * L22N[iS] * I22N[iS] + A3 * A3 * L33N[iS] * I33N[iS]
         + A4 * A4 * L44N[iS] * I44N[iS] + A5 * A5 * L55N[iS] * I55N[iS]
         + A1 * A2 * L12N[iS] * I12N[iS] + A1 * A3 * L13N[iS] * I13N[iS] + A1 * A4 * L14N[iS] * I14N[iS]
         + A1 * A5 * L15N[iS] * I15N[iS] + A2 * A3 * L23N[iS] * I23N[iS]
         + A2 * A4 * L24N[iS] * I24N[iS] + A2 * A5 * L25N[iS] * I25N[iS] + A3 * A4 * L34N[iS] * I34N[iS]
         + A3 * A5 * L35N[iS] * I35N[iS] + A4 * A5 * L45N[iS] * I45N[iS];
      LN = LN / (A1 * A1 * I11N[iS] + A2 * A2 * I22N[iS] + A3 * A3 * I33N[iS]
         + A4 * A4 * I44N[iS] + A5 * A5 * I55N[iS]
         + A1 * A2 * I12N[iS] + A1 * A3 * I13N[iS] + A1 * A4 * I14N[iS]
         + A1 * A5 * I15N[iS] + A2 * A3 * I23N[iS]
         + A2 * A4 * I24N[iS] + A2 * A5 * I25N[iS] + A3 * A4 * I34N[iS]
         + A3 * A5 * I35N[iS] + A4 * A5 * I45N[iS]);

      if(LC <= 0 || LU <= 0 || LD <= 0 || LW <= 0 || LN <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      /*
      double LSa = (LC + LU + LD + LW + LN) / 5;
      double LSb1 = (LU - LD) / 2;
      double LSb2 = (LW - LN) / 2;
      double LBa = (LBC[iS]*IBC[iS] + LBU[iS]*IBU[iS] + LBD[iS]*IBD[iS] + LBW[iS]*IBW[iS] + LBN[iS]*IBN[iS]) / 5;
      double LBb1 = (LBU[iS]*IBU[iS] - LBD[iS]*IBD[iS]) / 2;
      double LBb2 = (LBW[iS]*IBW[iS] - LBN[iS]*IBN[iS]) / 2;
      */

      double LSa = LC;
      double LSb1 = (N1 > 0) ? (LU - LC) : (LC - LD);
      double LSb2 = (N2 > 0) ? (LW - LC) : (LC - LN);
      double LBa = LBC[iS] * IBC[iS];
      double LBb1 = (N1 > 0) ? (LBU[iS] * IBU[iS] - LBC[iS] * IBC[iS]) : (LBC[iS] * IBC[iS] - LBD[iS] * IBD[iS]);
      double LBb2 = (N2 > 0) ? (LBW[iS] * IBW[iS] - LBC[iS] * IBC[iS]) : (LBC[iS] * IBC[iS] - LBN[iS] * IBN[iS]);

      double SignalLikelihood = LSa + LSb1 * N1 + LSb2 * N2;
      double BackgroundLikelihood = LBa + LBb1 * N1 + LBb2 * N2;

      LogTotal = LogTotal + log(SignalLikelihood * (1 - F) + BackgroundLikelihood * F) - N1 * N1 / 2 - N2 * N2 / 2;
   }

   return -LogTotal;
}

void FitClass::AddPoint(double l11c, double l22c, double l33c, double l44c, double l55c,
   double l12c, double l13c, double l14c, double l15c, double l23c,
   double l24c, double l25c, double l34c, double l35c, double l45c, double lbc,
   double l11u, double l22u, double l33u, double l44u, double l55u,
   double l12u, double l13u, double l14u, double l15u, double l23u,
   double l24u, double l25u, double l34u, double l35u, double l45u, double lbu,
   double l11d, double l22d, double l33d, double l44d, double l55d,
   double l12d, double l13d, double l14d, double l15d, double l23d,
   double l24d, double l25d, double l34d, double l35d, double l45d, double lbd,
   double l11w, double l22w, double l33w, double l44w, double l55w,
   double l12w, double l13w, double l14w, double l15w, double l23w,
   double l24w, double l25w, double l34w, double l35w, double l45w, double lbw,
   double l11n, double l22n, double l33n, double l44n, double l55n,
   double l12n, double l13n, double l14n, double l15n, double l23n,
   double l24n, double l25n, double l34n, double l35n, double l45n, double lbn,
   double i11c, double i22c, double i33c, double i44c, double i55c,
   double i12c, double i13c, double i14c, double i15c, double i23c,
   double i24c, double i25c, double i34c, double i35c, double i45c, double ibc,
   double i11u, double i22u, double i33u, double i44u, double i55u,
   double i12u, double i13u, double i14u, double i15u, double i23u,
   double i24u, double i25u, double i34u, double i35u, double i45u, double ibu,
   double i11d, double i22d, double i33d, double i44d, double i55d,
   double i12d, double i13d, double i14d, double i15d, double i23d,
   double i24d, double i25d, double i34d, double i35d, double i45d, double ibd,
   double i11w, double i22w, double i33w, double i44w, double i55w,
   double i12w, double i13w, double i14w, double i15w, double i23w,
   double i24w, double i25w, double i34w, double i35w, double i45w, double ibw,
   double i11n, double i22n, double i33n, double i44n, double i55n,
   double i12n, double i13n, double i14n, double i15n, double i23n,
   double i24n, double i25n, double i34n, double i35n, double i45n, double ibn)
{
   L11C.push_back(l11c);   L22C.push_back(l22c);   L33C.push_back(l33c);   L44C.push_back(l44c);
   L55C.push_back(l55c);   L12C.push_back(l12c);   L13C.push_back(l13c);   L14C.push_back(l14c);
   L15C.push_back(l15c);   L23C.push_back(l23c);   L24C.push_back(l24c);   L25C.push_back(l25c);
   L34C.push_back(l34c);   L35C.push_back(l35c);   L45C.push_back(l45c);   LBC.push_back(lbc);
   L11U.push_back(l11u);   L22U.push_back(l22u);   L33U.push_back(l33u);   L44U.push_back(l44u);
   L55U.push_back(l55u);   L12U.push_back(l12u);   L13U.push_back(l13u);   L14U.push_back(l14u);
   L15U.push_back(l15u);   L23U.push_back(l23u);   L24U.push_back(l24u);   L25U.push_back(l25u);
   L34U.push_back(l34u);   L35U.push_back(l35u);   L45U.push_back(l45u);   LBU.push_back(lbu);
   L11D.push_back(l11d);   L22D.push_back(l22d);   L33D.push_back(l33d);   L44D.push_back(l44d);
   L55D.push_back(l55d);   L12D.push_back(l12d);   L13D.push_back(l13d);   L14D.push_back(l14d);
   L15D.push_back(l15d);   L23D.push_back(l23d);   L24D.push_back(l24d);   L25D.push_back(l25d);
   L34D.push_back(l34d);   L35D.push_back(l35d);   L45D.push_back(l45d);   LBD.push_back(lbd);
   L11W.push_back(l11w);   L22W.push_back(l22w);   L33W.push_back(l33w);   L44W.push_back(l44w);
   L55W.push_back(l55w);   L12W.push_back(l12w);   L13W.push_back(l13w);   L14W.push_back(l14w);
   L15W.push_back(l15w);   L23W.push_back(l23w);   L24W.push_back(l24w);   L25W.push_back(l25w);
   L34W.push_back(l34w);   L35W.push_back(l35w);   L45W.push_back(l45w);   LBW.push_back(lbw);
   L11N.push_back(l11n);   L22N.push_back(l22n);   L33N.push_back(l33n);   L44N.push_back(l44n);
   L55N.push_back(l55n);   L12N.push_back(l12n);   L13N.push_back(l13n);   L14N.push_back(l14n);
   L15N.push_back(l15n);   L23N.push_back(l23n);   L24N.push_back(l24n);   L25N.push_back(l25n);
   L34N.push_back(l34n);   L35N.push_back(l35n);   L45N.push_back(l45n);   LBN.push_back(lbn);
   I11C.push_back(i11c);   I22C.push_back(i22c);   I33C.push_back(i33c);   I44C.push_back(i44c);
   I55C.push_back(i55c);   I12C.push_back(i12c);   I13C.push_back(i13c);   I14C.push_back(i14c);
   I15C.push_back(i15c);   I23C.push_back(i23c);   I24C.push_back(i24c);   I25C.push_back(i25c);
   I34C.push_back(i34c);   I35C.push_back(i35c);   I45C.push_back(i45c);   IBC.push_back(ibc);
   I11U.push_back(i11u);   I22U.push_back(i22u);   I33U.push_back(i33u);   I44U.push_back(i44u);
   I55U.push_back(i55u);   I12U.push_back(i12u);   I13U.push_back(i13u);   I14U.push_back(i14u);
   I15U.push_back(i15u);   I23U.push_back(i23u);   I24U.push_back(i24u);   I25U.push_back(i25u);
   I34U.push_back(i34u);   I35U.push_back(i35u);   I45U.push_back(i45u);   IBU.push_back(ibu);
   I11D.push_back(i11d);   I22D.push_back(i22d);   I33D.push_back(i33d);   I44D.push_back(i44d);
   I55D.push_back(i55d);   I12D.push_back(i12d);   I13D.push_back(i13d);   I14D.push_back(i14d);
   I15D.push_back(i15d);   I23D.push_back(i23d);   I24D.push_back(i24d);   I25D.push_back(i25d);
   I34D.push_back(i34d);   I35D.push_back(i35d);   I45D.push_back(i45d);   IBD.push_back(ibd);
   I11W.push_back(i11w);   I22W.push_back(i22w);   I33W.push_back(i33w);   I44W.push_back(i44w);
   I55W.push_back(i55w);   I12W.push_back(i12w);   I13W.push_back(i13w);   I14W.push_back(i14w);
   I15W.push_back(i15w);   I23W.push_back(i23w);   I24W.push_back(i24w);   I25W.push_back(i25w);
   I34W.push_back(i34w);   I35W.push_back(i35w);   I45W.push_back(i45w);   IBW.push_back(ibw);
   I11N.push_back(i11n);   I22N.push_back(i22n);   I33N.push_back(i33n);   I44N.push_back(i44n);
   I55N.push_back(i55n);   I12N.push_back(i12n);   I13N.push_back(i13n);   I14N.push_back(i14n);
   I15N.push_back(i15n);   I23N.push_back(i23n);   I24N.push_back(i24n);   I25N.push_back(i25n);
   I34N.push_back(i34n);   I35N.push_back(i35n);   I45N.push_back(i45n);   IBN.push_back(ibn);

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   L11C.clear();   L22C.clear();   L33C.clear();   L44C.clear();
   L55C.clear();   L12C.clear();   L13C.clear();   L14C.clear();
   L15C.clear();   L23C.clear();   L24C.clear();   L25C.clear();
   L34C.clear();   L35C.clear();   L45C.clear();   LBC.clear();
   L11U.clear();   L22U.clear();   L33U.clear();   L44U.clear();
   L55U.clear();   L12U.clear();   L13U.clear();   L14U.clear();
   L15U.clear();   L23U.clear();   L24U.clear();   L25U.clear();
   L34U.clear();   L35U.clear();   L45U.clear();   LBU.clear();
   L11D.clear();   L22D.clear();   L33D.clear();   L44D.clear();
   L55D.clear();   L12D.clear();   L13D.clear();   L14D.clear();
   L15D.clear();   L23D.clear();   L24D.clear();   L25D.clear();
   L34D.clear();   L35D.clear();   L45D.clear();   LBD.clear();
   L11W.clear();   L22W.clear();   L33W.clear();   L44W.clear();
   L55W.clear();   L12W.clear();   L13W.clear();   L14W.clear();
   L15W.clear();   L23W.clear();   L24W.clear();   L25W.clear();
   L34W.clear();   L35W.clear();   L45W.clear();   LBW.clear();
   L11N.clear();   L22N.clear();   L33N.clear();   L44N.clear();
   L55N.clear();   L12N.clear();   L13N.clear();   L14N.clear();
   L15N.clear();   L23N.clear();   L24N.clear();   L25N.clear();
   L34N.clear();   L35N.clear();   L45N.clear();   LBN.clear();
   I11C.clear();   I22C.clear();   I33C.clear();   I44C.clear();
   I55C.clear();   I12C.clear();   I13C.clear();   I14C.clear();
   I15C.clear();   I23C.clear();   I24C.clear();   I25C.clear();
   I34C.clear();   I35C.clear();   I45C.clear();   IBC.clear();
   I11U.clear();   I22U.clear();   I33U.clear();   I44U.clear();
   I55U.clear();   I12U.clear();   I13U.clear();   I14U.clear();
   I15U.clear();   I23U.clear();   I24U.clear();   I25U.clear();
   I34U.clear();   I35U.clear();   I45U.clear();   IBU.clear();
   I11D.clear();   I22D.clear();   I33D.clear();   I44D.clear();
   I55D.clear();   I12D.clear();   I13D.clear();   I14D.clear();
   I15D.clear();   I23D.clear();   I24D.clear();   I25D.clear();
   I34D.clear();   I35D.clear();   I45D.clear();   IBD.clear();
   I11W.clear();   I22W.clear();   I33W.clear();   I44W.clear();
   I55W.clear();   I12W.clear();   I13W.clear();   I14W.clear();
   I15W.clear();   I23W.clear();   I24W.clear();   I25W.clear();
   I34W.clear();   I35W.clear();   I45W.clear();   IBW.clear();
   I11N.clear();   I22N.clear();   I33N.clear();   I44N.clear();
   I55N.clear();   I12N.clear();   I13N.clear();   I14N.clear();
   I15N.clear();   I23N.clear();   I24N.clear();   I25N.clear();
   I34N.clear();   I35N.clear();   I45N.clear();   IBN.clear();

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit()
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");

   Worker->SetPrintLevel(1);
   Worker->SetMaxFunctionCalls(1000000);
   Worker->SetMaxIterations(1000);
   Worker->SetTolerance(1e-3);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 7);
   Worker->SetFunction(Function);

   Worker->SetLimitedVariable(0, "A3A1", 0, 0.1, -500, 500);
   Worker->SetLimitedVariable(1, "A3Phase", 0, 0.1, -PI * 10, PI * 10);
   Worker->SetLimitedVariable(2, "A2A1", 0, 0.5, -500, 500);
   Worker->SetLimitedVariable(3, "A2Phase", 0, 0.5, -PI * 10, PI * 10);
   Worker->SetLimitedVariable(4, "F", 0.001, 0.001, 0, 1);
   Worker->SetLimitedVariable(5, "N1", 0, 0.01, -1, 1);
   Worker->SetLimitedVariable(6, "N2", 0, 0.01, -1, 1);

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
   Result.N1 = Parameters[5];
   Result.N1Error = Errors[5];
   Result.N2 = Parameters[6];
   Result.N2Error = Errors[6];
   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   delete Worker;

   return Result;
}




