#include "Likelihood.h"

using namespace FullLikelihood;

Likelihood::Likelihood()
{
   for(int i = 0; i < 72; i++)
   {
      for(int j = 0; j < 72; j++)
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
   for(int i = 0; i < 72; i++)
   {
      for(int j = 0; j < 72; j++)
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
   for(int i = 0; i < 72; i++)
   {
      for(int j = 0; j < 72; j++)
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

   for(int i = 0; i < 72; i++)
   {
      if(A.A[i] == 0)
         continue;

      for(int j = 0; j < 72; j++)
      {
         if(A.A[j] == 0)
            continue;

         VSAll = VSAll + A.A[i] * A.A[j] * VS[i][j];
         ISAll = ISAll + A.A[i] * A.A[j] * IS[i][j];
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

   bool Ignore[72] = {false};
   for(int i = 0; i < 72; i++)
      Ignore[i] = false;

   for(int i = 0; i < 8; i++)   // ZZ
      Ignore[i] = true;
   for(int i = 16; i < 24; i++)   // ZA
      Ignore[i] = true;
   for(int i = 48; i < 56; i++)   // AZ
      Ignore[i] = true;
   for(int i = 64; i < 72; i++)   // AA
      Ignore[i] = true;

   for(int i = 1; i < 72; i = i + 2)   // Imaginary
      Ignore[i] = true;

   for(int i = 0; i < 72; i++)
   {
      for(int j = 0; j < 72; j++)
      {
         if(Ignore[i] == true || Ignore[j] == true)
            T->SetBranchStatus(Form("B1_%s_%s", Suffix[i].c_str(), Suffix[j].c_str()), false);
         else
            T->SetBranchAddress(Form("B1_%s_%s", Suffix[i].c_str(), Suffix[j].c_str()), &VS[i][j]);
      }
   }

   T->SetBranchAddress("B2_DDbar", &VB);
}

void Likelihood::SetIS(double is[72][72])
{
   for(int i = 0; i < 15; i++)
      for(int j = 0; j < 15; j++)
         IS[i][j] = is[i][j];
}

void Likelihood::SetIB(double ib)
{
   IB = ib;
}






