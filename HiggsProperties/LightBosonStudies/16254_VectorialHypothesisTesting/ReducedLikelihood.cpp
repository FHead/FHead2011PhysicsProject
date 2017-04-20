#include "ReducedLikelihood.h"

using namespace RealLikelihood;

Likelihood::Likelihood()
{
   for(int i = 0; i < 16; i++)
   {
      for(int j = 0; j < 16; j++)
      {
         VS[i][j] = 0;
         IS[i][j] = 1;
      }
   }

   VB = 0;
   IB = 1;
}

Likelihood::Likelihood(const Likelihood &L)
{
   for(int i = 0; i < 16; i++)
   {
      for(int j = 0; j < 16; j++)
      {
         VS[i][j] = L.VS[i][j];
         IS[i][j] = L.IS[i][j];
      }
   }

   VB = L.VB;
   IB = L.IB;
}

Likelihood &Likelihood::operator =(const Likelihood &L)
{
   for(int i = 0; i < 16; i++)
   {
      for(int j = 0; j < 16; j++)
      {
         VS[i][j] = L.VS[i][j];
         IS[i][j] = L.IS[i][j];
      }
   }

   VB = L.VB;
   IB = L.IB;

   return *this;
}

double Likelihood::Apply(FullAVVBasis &A, double F) const
{
   double VSAll = 0;
   double ISAll = 0;

   int Map[16] = {8, 10, 12, 24, 26, 28, 32, 34, 36, 40, 42, 44, 56, 58, 60, 35};
   
   for(int i = 0; i < 16; i++)
   {
      if(A.A[Map[i]] == 0)
         continue;

      for(int j = 0; j < 16; j++)
      {
         if(A.A[Map[j]] == 0)
            continue;

         VSAll = VSAll + A.A[Map[i]] * A.A[Map[j]] * VS[i][j];
         ISAll = ISAll + A.A[Map[i]] * A.A[Map[j]] * IS[i][j];
      }
   }

   double LS = VSAll / ISAll;
   double LB = VB / IB;

   if(ISAll <= 0)
      LS = 0;
   if(IB <= 0)
      LB = 0;

   double Answer = (1 - F) * LS + F * LB;
   if(Answer == 0)
      cerr << "Warning! Likeilhood = 0!" << endl;

   return Answer;
}

void Likelihood::SetBranchAddress(TTree *T)
{
   if(T == NULL)
   {
      cerr << "Tree is NULL while attempting to set branches" << endl;
      return;
   }

   vector<string> Suffix = GetXVVSignalSuffixList();

   int Map[16] = {8, 10, 12, 24, 26, 28, 32, 34, 36, 40, 42, 44, 56, 58, 60, 35};
   
   for(int i = 0; i < 72; i++)
      for(int j = 0; j < 72; j++)
         T->SetBranchStatus(Form("B1_%s_%s", Suffix[i].c_str(), Suffix[j].c_str()), false);

   for(int i = 0; i < 16; i++)
   {
      for(int j = 0; j < 16; j++)
      {
         T->SetBranchStatus(Form("B1_%s_%s", Suffix[Map[i]].c_str(), Suffix[Map[j]].c_str()), true);
         T->SetBranchAddress(Form("B1_%s_%s", Suffix[Map[i]].c_str(), Suffix[Map[j]].c_str()), &VS[i][j]);
      }
   }

   T->SetBranchAddress("B2_DDbar", &VB);
}

void Likelihood::SetIS(double is[72][72])
{
   int Map[16] = {8, 10, 12, 24, 26, 28, 32, 34, 36, 40, 42, 44, 56, 58, 60, 35};

   for(int i = 0; i < 16; i++)
      for(int j = 0; j < 16; j++)
         IS[i][j] = is[Map[i]][Map[j]];
}

void Likelihood::SetIB(double ib)
{
   IB = ib;
}




