#include <vector>
#include <iostream>
#include <algorithm>

#include "include/BasicUtilities.h"

double GetRho(std::vector<double> *EtaMax, std::vector<double> *Rho, double Eta)
{
   if(EtaMax == NULL || Rho == NULL || EtaMax->size() != Rho->size()
      || EtaMax->size() == 0)
   {
      std::cerr << "[GetRho] Input is invalid!  Return zero..." << std::endl;
      return 0;
   }

   for(int i = 0; i < (int)EtaMax->size(); i++)
   {
      if(Eta >= (*EtaMax)[i])
         continue;
      else
         return (*Rho)[i];
   }

   return (*Rho)[Rho->size()-1];
}

double GetCentrality(int Bin)
{
   return Bin * 0.005 + 0.00001;
}

bool IsDataFromTag(std::string Tag)
{
   if(Tag.find("Data") != std::string::npos)
      return true;
   if(Tag.find("DATA") != std::string::npos)
      return true;
   if(Tag.find("data") != std::string::npos)
      return true;
   return false;
}

bool IsPPFromTag(std::string Tag)
{
   if(Tag.find("PP") != std::string::npos)
      return true;
   if(Tag.find("pp") != std::string::npos)
      return true;
   return false;
}

template<class T, class U>
   std::vector<int> DRMatching(int BaseN, T BaseEta, T BasePhi,
      int TargetN, U TargetEta, U TargetPhi)
{
   std::vector<int> Result(BaseN);

   for(int i = 0; i < BaseN; i++)
   {
      int Best = -1;
      double BestDR2 = -1;

      for(int j = 0; j < TargetN; j++)
      {
         double DEta = BaseEta[i] - TargetEta[j];
         double DPhi = BasePhi[i] - TargetPhi[i];
         if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
         if(DPhi > +PI)   DPhi = DPhi - 2 * PI;
         double DR2 = DEta * DEta + DPhi * DPhi;

         if(DR2 < BestDR2 || BestDR2 < 0)
         {
            Best = j;
            BestDR2 = DR2;
         }
      }

      Result[i] = Best;
   }

   return Result;
}

template std::vector<int> DRMatching<float *, float *>(int, float *, float *,
   int, float *, float *);
template std::vector<int> DRMatching<std::vector<float>, std::vector<float> >
   (int, std::vector<float>, std::vector<float>,
   int, std::vector<float>, std::vector<float>);
template std::vector<int> DRMatching<float *, std::vector<float> >
   (int, float *, float *, int, std::vector<float>, std::vector<float>);
template std::vector<int> DRMatching<std::vector<float>, float *>
   (int, std::vector<float>, std::vector<float>, int, float *, float *);
template std::vector<int> DRMatching<std::vector<double>, float *>
   (int, std::vector<double>, std::vector<double>, int, float *, float *);


