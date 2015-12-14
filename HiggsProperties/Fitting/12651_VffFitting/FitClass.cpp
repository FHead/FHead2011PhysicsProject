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

#include "AngleConversion.h"

// #include "ProjectionHelper.h"
#include "FitClass.h"

#define PI 3.14159265358979323846264338327950288479716939937510

FitConfiguration::FitConfiguration()
{
   SetFloatGs("YYYYY");
   SetInitialRatios(ListToVector(5, 0, 0, 0, 0, 0));
}

FitConfiguration::FitConfiguration(string FloatGs)
{
   SetFloatGs(FloatGs);
   SetInitialRatios(ListToVector(5, 0, 0, 0, 0, 0));
}

FitConfiguration::FitConfiguration(string FloatGs, vector<double> Ratios)
{
   SetFloatGs(FloatGs);
   SetInitialRatios(Ratios);
}

FitConfiguration::~FitConfiguration()
{
}

void FitConfiguration::SetFloats(string FloatGs)
{
   SetFloatGs(FloatGs);
}

void FitConfiguration::SetFloatGs(string FloatGs)
{
   FloatEQEL = false;
   FloatGLEL = false;
   FloatGRGL = false;
   FloatGQLGL = false;
   FloatGQRGQL = false;

   if(FloatGs.size() > 0 && FloatGs[0] == 'Y')   FloatEQEL = true;
   if(FloatGs.size() > 1 && FloatGs[1] == 'Y')   FloatGLEL = true;
   if(FloatGs.size() > 2 && FloatGs[2] == 'Y')   FloatGRGL = true;
   if(FloatGs.size() > 3 && FloatGs[3] == 'Y')   FloatGQLGL = true;
   if(FloatGs.size() > 4 && FloatGs[4] == 'Y')   FloatGQRGQL = true;
}

void FitConfiguration::SetInitialRatios(const vector<double> Ratios)
{
   if(Ratios.size() > 0)   EQELInitialValue = Ratios[0];
   if(Ratios.size() > 1)   GLELInitialValue = Ratios[1];
   if(Ratios.size() > 2)   GRGLInitialValue = Ratios[2];
   if(Ratios.size() > 3)   GQLGLInitialValue = Ratios[3];
   if(Ratios.size() > 4)   GQRGQLInitialValue = Ratios[4];
}

int FitConfiguration::TotalNumberOfFloats()
{
   int Count = 0;

   if(FloatEQEL == true)     Count = Count + 1;
   if(FloatGLEL == true)     Count = Count + 1;
   if(FloatGRGL == true)     Count = Count + 1;
   if(FloatGQLGL == true)    Count = Count + 1;
   if(FloatGQRGQL == true)   Count = Count + 1;

   return Count;
}

double FitClass::CalculateLogLikelihoodAll(const double *Parameters) const
{
   double el = -1;
   double eq = Parameters[0] * el;
   double gL = Parameters[1] * el;
   double gR = Parameters[2] * gL;
   double gqL = Parameters[3] * gL;
   double gqR = Parameters[4] * gqL;

   double LogTotal = 0;

   for(int iS = 0; iS < SampleSize; iS++)
   {
      double Value[1] = {0}, Integral[1] = {0}, Likelihood[1] = {0};

      // for(int i = 0; i < 213; i++)
      //    cout << i << " " << iS << " " << V[i][iS] << endl;

      for(int i = 0; i < 1; i++)
      {
         Value[i] = 0
            + V[0][iS] * gR * gR * gR * gR * gqR * gqR * gqR * gqR
            + V[1][iS] * gR * gR * gR * gR * gqL * gqR * gqR * gqR
            + V[2][iS] * gR * gR * gR * gR * gqL * gqL * gqR * gqR
            + V[3][iS] * gR * gR * gR * gR * gqL * gqL * gqL * gqR
            + V[4][iS] * gR * gR * gR * gR * gqL * gqL * gqL * gqL
            + V[5][iS] * gR * gR * gR * gR * gR * gqR * gqR * gqR
            + V[6][iS] * gR * gR * gR * gR * gR * gqL * gqR * gqR
            + V[7][iS] * gR * gR * gR * gR * gR * gqL * gqL * gqR
            + V[8][iS] * gR * gR * gR * gR * gR * gqL * gqL * gqL
            + V[9][iS] * gR * gR * gR * gR * gR * gR * gqR * gqR
            + V[10][iS] * gR * gR * gR * gR * gR * gR * gqL * gqR
            + V[11][iS] * gR * gR * gR * gR * gR * gR * gqL * gqL
            + V[12][iS] * gL * gR * gR * gR * gqR * gqR * gqR * gqR
            + V[13][iS] * gL * gR * gR * gR * gqL * gqR * gqR * gqR
            + V[14][iS] * gL * gR * gR * gR * gqL * gqL * gqR * gqR
            + V[15][iS] * gL * gR * gR * gR * gqL * gqL * gqL * gqR
            + V[16][iS] * gL * gR * gR * gR * gqL * gqL * gqL * gqL
            + V[17][iS] * gL * gR * gR * gR * gR * gqR * gqR * gqR
            + V[18][iS] * gL * gR * gR * gR * gR * gqL * gqR * gqR
            + V[19][iS] * gL * gR * gR * gR * gR * gqL * gqL * gqR
            + V[20][iS] * gL * gR * gR * gR * gR * gqL * gqL * gqL
            + V[21][iS] * gL * gR * gR * gR * gR * gR * gqR * gqR
            + V[22][iS] * gL * gR * gR * gR * gR * gR * gqL * gqR
            + V[23][iS] * gL * gR * gR * gR * gR * gR * gqL * gqL
            + V[24][iS] * gL * gL * gR * gR * gqR * gqR * gqR * gqR
            + V[25][iS] * gL * gL * gR * gR * gqL * gqR * gqR * gqR
            + V[26][iS] * gL * gL * gR * gR * gqL * gqL * gqR * gqR
            + V[27][iS] * gL * gL * gR * gR * gqL * gqL * gqL * gqR
            + V[28][iS] * gL * gL * gR * gR * gqL * gqL * gqL * gqL
            + V[29][iS] * gL * gL * gR * gR * gR * gqR * gqR * gqR
            + V[30][iS] * gL * gL * gR * gR * gR * gqL * gqR * gqR
            + V[31][iS] * gL * gL * gR * gR * gR * gqL * gqL * gqR
            + V[32][iS] * gL * gL * gR * gR * gR * gqL * gqL * gqL
            + V[33][iS] * gL * gL * gR * gR * gR * gR * gqR * gqR
            + V[34][iS] * gL * gL * gR * gR * gR * gR * gqL * gqR
            + V[35][iS] * gL * gL * gR * gR * gR * gR * gqL * gqL
            + V[36][iS] * gL * gL * gL * gR * gqR * gqR * gqR * gqR
            + V[37][iS] * gL * gL * gL * gR * gqL * gqR * gqR * gqR
            + V[38][iS] * gL * gL * gL * gR * gqL * gqL * gqR * gqR
            + V[39][iS] * gL * gL * gL * gR * gqL * gqL * gqL * gqR
            + V[40][iS] * gL * gL * gL * gR * gqL * gqL * gqL * gqL
            + V[41][iS] * gL * gL * gL * gR * gR * gqR * gqR * gqR
            + V[42][iS] * gL * gL * gL * gR * gR * gqL * gqR * gqR
            + V[43][iS] * gL * gL * gL * gR * gR * gqL * gqL * gqR
            + V[44][iS] * gL * gL * gL * gR * gR * gqL * gqL * gqL
            + V[45][iS] * gL * gL * gL * gR * gR * gR * gqR * gqR
            + V[46][iS] * gL * gL * gL * gR * gR * gR * gqL * gqR
            + V[47][iS] * gL * gL * gL * gR * gR * gR * gqL * gqL
            + V[48][iS] * gL * gL * gL * gL * gqR * gqR * gqR * gqR
            + V[49][iS] * gL * gL * gL * gL * gqL * gqR * gqR * gqR
            + V[50][iS] * gL * gL * gL * gL * gqL * gqL * gqR * gqR
            + V[51][iS] * gL * gL * gL * gL * gqL * gqL * gqL * gqR
            + V[52][iS] * gL * gL * gL * gL * gqL * gqL * gqL * gqL
            + V[53][iS] * gL * gL * gL * gL * gR * gqR * gqR * gqR
            + V[54][iS] * gL * gL * gL * gL * gR * gqL * gqR * gqR
            + V[55][iS] * gL * gL * gL * gL * gR * gqL * gqL * gqR
            + V[56][iS] * gL * gL * gL * gL * gR * gqL * gqL * gqL
            + V[57][iS] * gL * gL * gL * gL * gR * gR * gqR * gqR
            + V[58][iS] * gL * gL * gL * gL * gR * gR * gqL * gqR
            + V[59][iS] * gL * gL * gL * gL * gR * gR * gqL * gqL
            + V[60][iS] * gL * gL * gL * gL * gL * gqR * gqR * gqR
            + V[61][iS] * gL * gL * gL * gL * gL * gqL * gqR * gqR
            + V[62][iS] * gL * gL * gL * gL * gL * gqL * gqL * gqR
            + V[63][iS] * gL * gL * gL * gL * gL * gqL * gqL * gqL
            + V[64][iS] * gL * gL * gL * gL * gL * gR * gqR * gqR
            + V[65][iS] * gL * gL * gL * gL * gL * gR * gqL * gqR
            + V[66][iS] * gL * gL * gL * gL * gL * gR * gqL * gqL
            + V[67][iS] * gL * gL * gL * gL * gL * gL * gqR * gqR
            + V[68][iS] * gL * gL * gL * gL * gL * gL * gqL * gqR
            + V[69][iS] * gL * gL * gL * gL * gL * gL * gqL * gqL
            + V[70][iS] * el * eq * gR * gR * gR * gqR * gqR * gqR
            + V[71][iS] * el * eq * gR * gR * gR * gqL * gqR * gqR
            + V[72][iS] * el * eq * gR * gR * gR * gqL * gqL * gqR
            + V[73][iS] * el * eq * gR * gR * gR * gqL * gqL * gqL
            + V[74][iS] * el * eq * gR * gR * gR * gR * gqR * gqR
            + V[75][iS] * el * eq * gR * gR * gR * gR * gqL * gqR
            + V[76][iS] * el * eq * gR * gR * gR * gR * gqL * gqL
            + V[77][iS] * el * eq * gR * gR * gR * gR * gR * gqR
            + V[78][iS] * el * eq * gR * gR * gR * gR * gR * gqL
            + V[79][iS] * el * eq * gL * gR * gR * gqR * gqR * gqR
            + V[80][iS] * el * eq * gL * gR * gR * gqL * gqR * gqR
            + V[81][iS] * el * eq * gL * gR * gR * gqL * gqL * gqR
            + V[82][iS] * el * eq * gL * gR * gR * gqL * gqL * gqL
            + V[83][iS] * el * eq * gL * gR * gR * gR * gqR * gqR
            + V[84][iS] * el * eq * gL * gR * gR * gR * gqL * gqR
            + V[85][iS] * el * eq * gL * gR * gR * gR * gqL * gqL
            + V[86][iS] * el * eq * gL * gR * gR * gR * gR * gqR
            + V[87][iS] * el * eq * gL * gR * gR * gR * gR * gqL
            + V[88][iS] * el * eq * gL * gL * gR * gqR * gqR * gqR
            + V[89][iS] * el * eq * gL * gL * gR * gqL * gqR * gqR
            + V[90][iS] * el * eq * gL * gL * gR * gqL * gqL * gqR
            + V[91][iS] * el * eq * gL * gL * gR * gqL * gqL * gqL
            + V[92][iS] * el * eq * gL * gL * gR * gR * gqR * gqR
            + V[93][iS] * el * eq * gL * gL * gR * gR * gqL * gqR
            + V[94][iS] * el * eq * gL * gL * gR * gR * gqL * gqL
            + V[95][iS] * el * eq * gL * gL * gR * gR * gR * gqR
            + V[96][iS] * el * eq * gL * gL * gR * gR * gR * gqL
            + V[97][iS] * el * eq * gL * gL * gL * gqR * gqR * gqR
            + V[98][iS] * el * eq * gL * gL * gL * gqL * gqR * gqR
            + V[99][iS] * el * eq * gL * gL * gL * gqL * gqL * gqR
            + V[100][iS] * el * eq * gL * gL * gL * gqL * gqL * gqL
            + V[101][iS] * el * eq * gL * gL * gL * gR * gqR * gqR
            + V[102][iS] * el * eq * gL * gL * gL * gR * gqL * gqR
            + V[103][iS] * el * eq * gL * gL * gL * gR * gqL * gqL
            + V[104][iS] * el * eq * gL * gL * gL * gR * gR * gqR
            + V[105][iS] * el * eq * gL * gL * gL * gR * gR * gqL
            + V[106][iS] * el * eq * gL * gL * gL * gL * gqR * gqR
            + V[107][iS] * el * eq * gL * gL * gL * gL * gqL * gqR
            + V[108][iS] * el * eq * gL * gL * gL * gL * gqL * gqL
            + V[109][iS] * el * eq * gL * gL * gL * gL * gR * gqR
            + V[110][iS] * el * eq * gL * gL * gL * gL * gR * gqL
            + V[111][iS] * el * eq * gL * gL * gL * gL * gL * gqR
            + V[112][iS] * el * eq * gL * gL * gL * gL * gL * gqL
            + V[113][iS] * el * el * gR * gR * gR * gqR * gqR * gqR
            + V[114][iS] * el * el * gR * gR * gR * gqL * gqR * gqR
            + V[115][iS] * el * el * gR * gR * gR * gqL * gqL * gqR
            + V[116][iS] * el * el * gR * gR * gR * gqL * gqL * gqL
            + V[117][iS] * el * el * gR * gR * gR * gR * gqR * gqR
            + V[118][iS] * el * el * gR * gR * gR * gR * gqL * gqR
            + V[119][iS] * el * el * gR * gR * gR * gR * gqL * gqL
            + V[120][iS] * el * el * gL * gR * gR * gqR * gqR * gqR
            + V[121][iS] * el * el * gL * gR * gR * gqL * gqR * gqR
            + V[122][iS] * el * el * gL * gR * gR * gqL * gqL * gqR
            + V[123][iS] * el * el * gL * gR * gR * gqL * gqL * gqL
            + V[124][iS] * el * el * gL * gR * gR * gR * gqR * gqR
            + V[125][iS] * el * el * gL * gR * gR * gR * gqL * gqR
            + V[126][iS] * el * el * gL * gR * gR * gR * gqL * gqL
            + V[127][iS] * el * el * gL * gL * gR * gqR * gqR * gqR
            + V[128][iS] * el * el * gL * gL * gR * gqL * gqR * gqR
            + V[129][iS] * el * el * gL * gL * gR * gqL * gqL * gqR
            + V[130][iS] * el * el * gL * gL * gR * gqL * gqL * gqL
            + V[131][iS] * el * el * gL * gL * gR * gR * gqR * gqR
            + V[132][iS] * el * el * gL * gL * gR * gR * gqL * gqR
            + V[133][iS] * el * el * gL * gL * gR * gR * gqL * gqL
            + V[134][iS] * el * el * gL * gL * gL * gqR * gqR * gqR
            + V[135][iS] * el * el * gL * gL * gL * gqL * gqR * gqR
            + V[136][iS] * el * el * gL * gL * gL * gqL * gqL * gqR
            + V[137][iS] * el * el * gL * gL * gL * gqL * gqL * gqL
            + V[138][iS] * el * el * gL * gL * gL * gR * gqR * gqR
            + V[139][iS] * el * el * gL * gL * gL * gR * gqL * gqR
            + V[140][iS] * el * el * gL * gL * gL * gR * gqL * gqL
            + V[141][iS] * el * el * gL * gL * gL * gL * gqR * gqR
            + V[142][iS] * el * el * gL * gL * gL * gL * gqL * gqR
            + V[143][iS] * el * el * gL * gL * gL * gL * gqL * gqL
            + V[144][iS] * el * el * eq * eq * gR * gR * gqR * gqR
            + V[145][iS] * el * el * eq * eq * gR * gR * gqL * gqR
            + V[146][iS] * el * el * eq * eq * gR * gR * gqL * gqL
            + V[147][iS] * el * el * eq * eq * gR * gR * gR * gqR
            + V[148][iS] * el * el * eq * eq * gR * gR * gR * gqL
            + V[149][iS] * el * el * eq * eq * gR * gR * gR * gR
            + V[150][iS] * el * el * eq * eq * gL * gR * gqR * gqR
            + V[151][iS] * el * el * eq * eq * gL * gR * gqL * gqR
            + V[152][iS] * el * el * eq * eq * gL * gR * gqL * gqL
            + V[153][iS] * el * el * eq * eq * gL * gR * gR * gqR
            + V[154][iS] * el * el * eq * eq * gL * gR * gR * gqL
            + V[155][iS] * el * el * eq * eq * gL * gR * gR * gR
            + V[156][iS] * el * el * eq * eq * gL * gL * gqR * gqR
            + V[157][iS] * el * el * eq * eq * gL * gL * gqL * gqR
            + V[158][iS] * el * el * eq * eq * gL * gL * gqL * gqL
            + V[159][iS] * el * el * eq * eq * gL * gL * gR * gqR
            + V[160][iS] * el * el * eq * eq * gL * gL * gR * gqL
            + V[161][iS] * el * el * eq * eq * gL * gL * gR * gR
            + V[162][iS] * el * el * eq * eq * gL * gL * gL * gqR
            + V[163][iS] * el * el * eq * eq * gL * gL * gL * gqL
            + V[164][iS] * el * el * eq * eq * gL * gL * gL * gR
            + V[165][iS] * el * el * eq * eq * gL * gL * gL * gL
            + V[166][iS] * el * el * el * eq * gR * gR * gqR * gqR
            + V[167][iS] * el * el * el * eq * gR * gR * gqL * gqR
            + V[168][iS] * el * el * el * eq * gR * gR * gqL * gqL
            + V[169][iS] * el * el * el * eq * gR * gR * gR * gqR
            + V[170][iS] * el * el * el * eq * gR * gR * gR * gqL
            + V[171][iS] * el * el * el * eq * gL * gR * gqR * gqR
            + V[172][iS] * el * el * el * eq * gL * gR * gqL * gqR
            + V[173][iS] * el * el * el * eq * gL * gR * gqL * gqL
            + V[174][iS] * el * el * el * eq * gL * gR * gR * gqR
            + V[175][iS] * el * el * el * eq * gL * gR * gR * gqL
            + V[176][iS] * el * el * el * eq * gL * gL * gqR * gqR
            + V[177][iS] * el * el * el * eq * gL * gL * gqL * gqR
            + V[178][iS] * el * el * el * eq * gL * gL * gqL * gqL
            + V[179][iS] * el * el * el * eq * gL * gL * gR * gqR
            + V[180][iS] * el * el * el * eq * gL * gL * gR * gqL
            + V[181][iS] * el * el * el * eq * gL * gL * gL * gqR
            + V[182][iS] * el * el * el * eq * gL * gL * gL * gqL
            + V[183][iS] * el * el * el * eq * eq * eq * gR * gqR
            + V[184][iS] * el * el * el * eq * eq * eq * gR * gqL
            + V[185][iS] * el * el * el * eq * eq * eq * gR * gR
            + V[186][iS] * el * el * el * eq * eq * eq * gL * gqR
            + V[187][iS] * el * el * el * eq * eq * eq * gL * gqL
            + V[188][iS] * el * el * el * eq * eq * eq * gL * gR
            + V[189][iS] * el * el * el * eq * eq * eq * gL * gL
            + V[190][iS] * el * el * el * el * gR * gR * gqR * gqR
            + V[191][iS] * el * el * el * el * gR * gR * gqL * gqR
            + V[192][iS] * el * el * el * el * gR * gR * gqL * gqL
            + V[193][iS] * el * el * el * el * gL * gR * gqR * gqR
            + V[194][iS] * el * el * el * el * gL * gR * gqL * gqR
            + V[195][iS] * el * el * el * el * gL * gR * gqL * gqL
            + V[196][iS] * el * el * el * el * gL * gL * gqR * gqR
            + V[197][iS] * el * el * el * el * gL * gL * gqL * gqR
            + V[198][iS] * el * el * el * el * gL * gL * gqL * gqL
            + V[199][iS] * el * el * el * el * eq * eq * gR * gqR
            + V[200][iS] * el * el * el * el * eq * eq * gR * gqL
            + V[201][iS] * el * el * el * el * eq * eq * gR * gR
            + V[202][iS] * el * el * el * el * eq * eq * gL * gqR
            + V[203][iS] * el * el * el * el * eq * eq * gL * gqL
            + V[204][iS] * el * el * el * el * eq * eq * gL * gR
            + V[205][iS] * el * el * el * el * eq * eq * gL * gL
            + V[206][iS] * el * el * el * el * eq * eq * eq * eq
            + V[207][iS] * el * el * el * el * el * eq * gR * gqR
            + V[208][iS] * el * el * el * el * el * eq * gR * gqL
            + V[209][iS] * el * el * el * el * el * eq * gL * gqR
            + V[210][iS] * el * el * el * el * el * eq * gL * gqL
            + V[211][iS] * el * el * el * el * el * eq * eq * eq
            + V[212][iS] * el * el * el * el * el * el * eq * eq;

         Integral[i] = 0
            + I[0][iS] * gR * gR * gR * gR * gqR * gqR * gqR * gqR
            + I[1][iS] * gR * gR * gR * gR * gqL * gqR * gqR * gqR
            + I[2][iS] * gR * gR * gR * gR * gqL * gqL * gqR * gqR
            + I[3][iS] * gR * gR * gR * gR * gqL * gqL * gqL * gqR
            + I[4][iS] * gR * gR * gR * gR * gqL * gqL * gqL * gqL
            + I[5][iS] * gR * gR * gR * gR * gR * gqR * gqR * gqR
            + I[6][iS] * gR * gR * gR * gR * gR * gqL * gqR * gqR
            + I[7][iS] * gR * gR * gR * gR * gR * gqL * gqL * gqR
            + I[8][iS] * gR * gR * gR * gR * gR * gqL * gqL * gqL
            + I[9][iS] * gR * gR * gR * gR * gR * gR * gqR * gqR
            + I[10][iS] * gR * gR * gR * gR * gR * gR * gqL * gqR
            + I[11][iS] * gR * gR * gR * gR * gR * gR * gqL * gqL
            + I[12][iS] * gL * gR * gR * gR * gqR * gqR * gqR * gqR
            + I[13][iS] * gL * gR * gR * gR * gqL * gqR * gqR * gqR
            + I[14][iS] * gL * gR * gR * gR * gqL * gqL * gqR * gqR
            + I[15][iS] * gL * gR * gR * gR * gqL * gqL * gqL * gqR
            + I[16][iS] * gL * gR * gR * gR * gqL * gqL * gqL * gqL
            + I[17][iS] * gL * gR * gR * gR * gR * gqR * gqR * gqR
            + I[18][iS] * gL * gR * gR * gR * gR * gqL * gqR * gqR
            + I[19][iS] * gL * gR * gR * gR * gR * gqL * gqL * gqR
            + I[20][iS] * gL * gR * gR * gR * gR * gqL * gqL * gqL
            + I[21][iS] * gL * gR * gR * gR * gR * gR * gqR * gqR
            + I[22][iS] * gL * gR * gR * gR * gR * gR * gqL * gqR
            + I[23][iS] * gL * gR * gR * gR * gR * gR * gqL * gqL
            + I[24][iS] * gL * gL * gR * gR * gqR * gqR * gqR * gqR
            + I[25][iS] * gL * gL * gR * gR * gqL * gqR * gqR * gqR
            + I[26][iS] * gL * gL * gR * gR * gqL * gqL * gqR * gqR
            + I[27][iS] * gL * gL * gR * gR * gqL * gqL * gqL * gqR
            + I[28][iS] * gL * gL * gR * gR * gqL * gqL * gqL * gqL
            + I[29][iS] * gL * gL * gR * gR * gR * gqR * gqR * gqR
            + I[30][iS] * gL * gL * gR * gR * gR * gqL * gqR * gqR
            + I[31][iS] * gL * gL * gR * gR * gR * gqL * gqL * gqR
            + I[32][iS] * gL * gL * gR * gR * gR * gqL * gqL * gqL
            + I[33][iS] * gL * gL * gR * gR * gR * gR * gqR * gqR
            + I[34][iS] * gL * gL * gR * gR * gR * gR * gqL * gqR
            + I[35][iS] * gL * gL * gR * gR * gR * gR * gqL * gqL
            + I[36][iS] * gL * gL * gL * gR * gqR * gqR * gqR * gqR
            + I[37][iS] * gL * gL * gL * gR * gqL * gqR * gqR * gqR
            + I[38][iS] * gL * gL * gL * gR * gqL * gqL * gqR * gqR
            + I[39][iS] * gL * gL * gL * gR * gqL * gqL * gqL * gqR
            + I[40][iS] * gL * gL * gL * gR * gqL * gqL * gqL * gqL
            + I[41][iS] * gL * gL * gL * gR * gR * gqR * gqR * gqR
            + I[42][iS] * gL * gL * gL * gR * gR * gqL * gqR * gqR
            + I[43][iS] * gL * gL * gL * gR * gR * gqL * gqL * gqR
            + I[44][iS] * gL * gL * gL * gR * gR * gqL * gqL * gqL
            + I[45][iS] * gL * gL * gL * gR * gR * gR * gqR * gqR
            + I[46][iS] * gL * gL * gL * gR * gR * gR * gqL * gqR
            + I[47][iS] * gL * gL * gL * gR * gR * gR * gqL * gqL
            + I[48][iS] * gL * gL * gL * gL * gqR * gqR * gqR * gqR
            + I[49][iS] * gL * gL * gL * gL * gqL * gqR * gqR * gqR
            + I[50][iS] * gL * gL * gL * gL * gqL * gqL * gqR * gqR
            + I[51][iS] * gL * gL * gL * gL * gqL * gqL * gqL * gqR
            + I[52][iS] * gL * gL * gL * gL * gqL * gqL * gqL * gqL
            + I[53][iS] * gL * gL * gL * gL * gR * gqR * gqR * gqR
            + I[54][iS] * gL * gL * gL * gL * gR * gqL * gqR * gqR
            + I[55][iS] * gL * gL * gL * gL * gR * gqL * gqL * gqR
            + I[56][iS] * gL * gL * gL * gL * gR * gqL * gqL * gqL
            + I[57][iS] * gL * gL * gL * gL * gR * gR * gqR * gqR
            + I[58][iS] * gL * gL * gL * gL * gR * gR * gqL * gqR
            + I[59][iS] * gL * gL * gL * gL * gR * gR * gqL * gqL
            + I[60][iS] * gL * gL * gL * gL * gL * gqR * gqR * gqR
            + I[61][iS] * gL * gL * gL * gL * gL * gqL * gqR * gqR
            + I[62][iS] * gL * gL * gL * gL * gL * gqL * gqL * gqR
            + I[63][iS] * gL * gL * gL * gL * gL * gqL * gqL * gqL
            + I[64][iS] * gL * gL * gL * gL * gL * gR * gqR * gqR
            + I[65][iS] * gL * gL * gL * gL * gL * gR * gqL * gqR
            + I[66][iS] * gL * gL * gL * gL * gL * gR * gqL * gqL
            + I[67][iS] * gL * gL * gL * gL * gL * gL * gqR * gqR
            + I[68][iS] * gL * gL * gL * gL * gL * gL * gqL * gqR
            + I[69][iS] * gL * gL * gL * gL * gL * gL * gqL * gqL
            + I[70][iS] * el * eq * gR * gR * gR * gqR * gqR * gqR
            + I[71][iS] * el * eq * gR * gR * gR * gqL * gqR * gqR
            + I[72][iS] * el * eq * gR * gR * gR * gqL * gqL * gqR
            + I[73][iS] * el * eq * gR * gR * gR * gqL * gqL * gqL
            + I[74][iS] * el * eq * gR * gR * gR * gR * gqR * gqR
            + I[75][iS] * el * eq * gR * gR * gR * gR * gqL * gqR
            + I[76][iS] * el * eq * gR * gR * gR * gR * gqL * gqL
            + I[77][iS] * el * eq * gR * gR * gR * gR * gR * gqR
            + I[78][iS] * el * eq * gR * gR * gR * gR * gR * gqL
            + I[79][iS] * el * eq * gL * gR * gR * gqR * gqR * gqR
            + I[80][iS] * el * eq * gL * gR * gR * gqL * gqR * gqR
            + I[81][iS] * el * eq * gL * gR * gR * gqL * gqL * gqR
            + I[82][iS] * el * eq * gL * gR * gR * gqL * gqL * gqL
            + I[83][iS] * el * eq * gL * gR * gR * gR * gqR * gqR
            + I[84][iS] * el * eq * gL * gR * gR * gR * gqL * gqR
            + I[85][iS] * el * eq * gL * gR * gR * gR * gqL * gqL
            + I[86][iS] * el * eq * gL * gR * gR * gR * gR * gqR
            + I[87][iS] * el * eq * gL * gR * gR * gR * gR * gqL
            + I[88][iS] * el * eq * gL * gL * gR * gqR * gqR * gqR
            + I[89][iS] * el * eq * gL * gL * gR * gqL * gqR * gqR
            + I[90][iS] * el * eq * gL * gL * gR * gqL * gqL * gqR
            + I[91][iS] * el * eq * gL * gL * gR * gqL * gqL * gqL
            + I[92][iS] * el * eq * gL * gL * gR * gR * gqR * gqR
            + I[93][iS] * el * eq * gL * gL * gR * gR * gqL * gqR
            + I[94][iS] * el * eq * gL * gL * gR * gR * gqL * gqL
            + I[95][iS] * el * eq * gL * gL * gR * gR * gR * gqR
            + I[96][iS] * el * eq * gL * gL * gR * gR * gR * gqL
            + I[97][iS] * el * eq * gL * gL * gL * gqR * gqR * gqR
            + I[98][iS] * el * eq * gL * gL * gL * gqL * gqR * gqR
            + I[99][iS] * el * eq * gL * gL * gL * gqL * gqL * gqR
            + I[100][iS] * el * eq * gL * gL * gL * gqL * gqL * gqL
            + I[101][iS] * el * eq * gL * gL * gL * gR * gqR * gqR
            + I[102][iS] * el * eq * gL * gL * gL * gR * gqL * gqR
            + I[103][iS] * el * eq * gL * gL * gL * gR * gqL * gqL
            + I[104][iS] * el * eq * gL * gL * gL * gR * gR * gqR
            + I[105][iS] * el * eq * gL * gL * gL * gR * gR * gqL
            + I[106][iS] * el * eq * gL * gL * gL * gL * gqR * gqR
            + I[107][iS] * el * eq * gL * gL * gL * gL * gqL * gqR
            + I[108][iS] * el * eq * gL * gL * gL * gL * gqL * gqL
            + I[109][iS] * el * eq * gL * gL * gL * gL * gR * gqR
            + I[110][iS] * el * eq * gL * gL * gL * gL * gR * gqL
            + I[111][iS] * el * eq * gL * gL * gL * gL * gL * gqR
            + I[112][iS] * el * eq * gL * gL * gL * gL * gL * gqL
            + I[113][iS] * el * el * gR * gR * gR * gqR * gqR * gqR
            + I[114][iS] * el * el * gR * gR * gR * gqL * gqR * gqR
            + I[115][iS] * el * el * gR * gR * gR * gqL * gqL * gqR
            + I[116][iS] * el * el * gR * gR * gR * gqL * gqL * gqL
            + I[117][iS] * el * el * gR * gR * gR * gR * gqR * gqR
            + I[118][iS] * el * el * gR * gR * gR * gR * gqL * gqR
            + I[119][iS] * el * el * gR * gR * gR * gR * gqL * gqL
            + I[120][iS] * el * el * gL * gR * gR * gqR * gqR * gqR
            + I[121][iS] * el * el * gL * gR * gR * gqL * gqR * gqR
            + I[122][iS] * el * el * gL * gR * gR * gqL * gqL * gqR
            + I[123][iS] * el * el * gL * gR * gR * gqL * gqL * gqL
            + I[124][iS] * el * el * gL * gR * gR * gR * gqR * gqR
            + I[125][iS] * el * el * gL * gR * gR * gR * gqL * gqR
            + I[126][iS] * el * el * gL * gR * gR * gR * gqL * gqL
            + I[127][iS] * el * el * gL * gL * gR * gqR * gqR * gqR
            + I[128][iS] * el * el * gL * gL * gR * gqL * gqR * gqR
            + I[129][iS] * el * el * gL * gL * gR * gqL * gqL * gqR
            + I[130][iS] * el * el * gL * gL * gR * gqL * gqL * gqL
            + I[131][iS] * el * el * gL * gL * gR * gR * gqR * gqR
            + I[132][iS] * el * el * gL * gL * gR * gR * gqL * gqR
            + I[133][iS] * el * el * gL * gL * gR * gR * gqL * gqL
            + I[134][iS] * el * el * gL * gL * gL * gqR * gqR * gqR
            + I[135][iS] * el * el * gL * gL * gL * gqL * gqR * gqR
            + I[136][iS] * el * el * gL * gL * gL * gqL * gqL * gqR
            + I[137][iS] * el * el * gL * gL * gL * gqL * gqL * gqL
            + I[138][iS] * el * el * gL * gL * gL * gR * gqR * gqR
            + I[139][iS] * el * el * gL * gL * gL * gR * gqL * gqR
            + I[140][iS] * el * el * gL * gL * gL * gR * gqL * gqL
            + I[141][iS] * el * el * gL * gL * gL * gL * gqR * gqR
            + I[142][iS] * el * el * gL * gL * gL * gL * gqL * gqR
            + I[143][iS] * el * el * gL * gL * gL * gL * gqL * gqL
            + I[144][iS] * el * el * eq * eq * gR * gR * gqR * gqR
            + I[145][iS] * el * el * eq * eq * gR * gR * gqL * gqR
            + I[146][iS] * el * el * eq * eq * gR * gR * gqL * gqL
            + I[147][iS] * el * el * eq * eq * gR * gR * gR * gqR
            + I[148][iS] * el * el * eq * eq * gR * gR * gR * gqL
            + I[149][iS] * el * el * eq * eq * gR * gR * gR * gR
            + I[150][iS] * el * el * eq * eq * gL * gR * gqR * gqR
            + I[151][iS] * el * el * eq * eq * gL * gR * gqL * gqR
            + I[152][iS] * el * el * eq * eq * gL * gR * gqL * gqL
            + I[153][iS] * el * el * eq * eq * gL * gR * gR * gqR
            + I[154][iS] * el * el * eq * eq * gL * gR * gR * gqL
            + I[155][iS] * el * el * eq * eq * gL * gR * gR * gR
            + I[156][iS] * el * el * eq * eq * gL * gL * gqR * gqR
            + I[157][iS] * el * el * eq * eq * gL * gL * gqL * gqR
            + I[158][iS] * el * el * eq * eq * gL * gL * gqL * gqL
            + I[159][iS] * el * el * eq * eq * gL * gL * gR * gqR
            + I[160][iS] * el * el * eq * eq * gL * gL * gR * gqL
            + I[161][iS] * el * el * eq * eq * gL * gL * gR * gR
            + I[162][iS] * el * el * eq * eq * gL * gL * gL * gqR
            + I[163][iS] * el * el * eq * eq * gL * gL * gL * gqL
            + I[164][iS] * el * el * eq * eq * gL * gL * gL * gR
            + I[165][iS] * el * el * eq * eq * gL * gL * gL * gL
            + I[166][iS] * el * el * el * eq * gR * gR * gqR * gqR
            + I[167][iS] * el * el * el * eq * gR * gR * gqL * gqR
            + I[168][iS] * el * el * el * eq * gR * gR * gqL * gqL
            + I[169][iS] * el * el * el * eq * gR * gR * gR * gqR
            + I[170][iS] * el * el * el * eq * gR * gR * gR * gqL
            + I[171][iS] * el * el * el * eq * gL * gR * gqR * gqR
            + I[172][iS] * el * el * el * eq * gL * gR * gqL * gqR
            + I[173][iS] * el * el * el * eq * gL * gR * gqL * gqL
            + I[174][iS] * el * el * el * eq * gL * gR * gR * gqR
            + I[175][iS] * el * el * el * eq * gL * gR * gR * gqL
            + I[176][iS] * el * el * el * eq * gL * gL * gqR * gqR
            + I[177][iS] * el * el * el * eq * gL * gL * gqL * gqR
            + I[178][iS] * el * el * el * eq * gL * gL * gqL * gqL
            + I[179][iS] * el * el * el * eq * gL * gL * gR * gqR
            + I[180][iS] * el * el * el * eq * gL * gL * gR * gqL
            + I[181][iS] * el * el * el * eq * gL * gL * gL * gqR
            + I[182][iS] * el * el * el * eq * gL * gL * gL * gqL
            + I[183][iS] * el * el * el * eq * eq * eq * gR * gqR
            + I[184][iS] * el * el * el * eq * eq * eq * gR * gqL
            + I[185][iS] * el * el * el * eq * eq * eq * gR * gR
            + I[186][iS] * el * el * el * eq * eq * eq * gL * gqR
            + I[187][iS] * el * el * el * eq * eq * eq * gL * gqL
            + I[188][iS] * el * el * el * eq * eq * eq * gL * gR
            + I[189][iS] * el * el * el * eq * eq * eq * gL * gL
            + I[190][iS] * el * el * el * el * gR * gR * gqR * gqR
            + I[191][iS] * el * el * el * el * gR * gR * gqL * gqR
            + I[192][iS] * el * el * el * el * gR * gR * gqL * gqL
            + I[193][iS] * el * el * el * el * gL * gR * gqR * gqR
            + I[194][iS] * el * el * el * el * gL * gR * gqL * gqR
            + I[195][iS] * el * el * el * el * gL * gR * gqL * gqL
            + I[196][iS] * el * el * el * el * gL * gL * gqR * gqR
            + I[197][iS] * el * el * el * el * gL * gL * gqL * gqR
            + I[198][iS] * el * el * el * el * gL * gL * gqL * gqL
            + I[199][iS] * el * el * el * el * eq * eq * gR * gqR
            + I[200][iS] * el * el * el * el * eq * eq * gR * gqL
            + I[201][iS] * el * el * el * el * eq * eq * gR * gR
            + I[202][iS] * el * el * el * el * eq * eq * gL * gqR
            + I[203][iS] * el * el * el * el * eq * eq * gL * gqL
            + I[204][iS] * el * el * el * el * eq * eq * gL * gR
            + I[205][iS] * el * el * el * el * eq * eq * gL * gL
            + I[206][iS] * el * el * el * el * eq * eq * eq * eq
            + I[207][iS] * el * el * el * el * el * eq * gR * gqR
            + I[208][iS] * el * el * el * el * el * eq * gR * gqL
            + I[209][iS] * el * el * el * el * el * eq * gL * gqR
            + I[210][iS] * el * el * el * el * el * eq * gL * gqL
            + I[211][iS] * el * el * el * el * el * eq * eq * eq
            + I[212][iS] * el * el * el * el * el * el * eq * eq;

         Likelihood[i] = Value[i] / Integral[i];

         // cout << el << " " << eq << " " << gL << " " << gR << " " << gqL << " " << gqR << endl;
         // cout << Value[i] << " " << Integral[i] << " " << Likelihood[i] << " " << V[213][iS] << endl;
      }

      bool Good = true;
      for(int i = 0; i < 1; i++)
         if(Likelihood[i] < 0)
            Good = false;
      if(Good == false)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      double SignalLikelihood = Likelihood[0];

      if(SignalLikelihood <= 0)
      {
         LogTotal = LogTotal - 99999;
         continue;
      }

      LogTotal = LogTotal + log(SignalLikelihood);
   }

   return -LogTotal * 2;
}

void FitClass::AddPoint(SingleEvent &event)
{
   AddPoint(event.v, event.i, event.event, event.state);
}

void FitClass::AddPoint(double v[214], double i[214], EventParameters &Event, string State)
{
   for(int i1 = 0; i1 < 214; i1++)
   {
      V[i1].push_back(v[i1]);
      I[i1].push_back(i[i1]);
   }

   E.push_back(Event);
   S.push_back(State);

   SampleSize = SampleSize + 1;
}

void FitClass::ClearPoints()
{
   for(int i = 0; i < 214; i++)
   {
      V[i].clear();
      I[i].clear();
   }

   E.clear();
   S.clear();

   SignalStateCount[0] = 0;
   SignalStateCount[1] = 0;
   SignalStateCount[2] = 0;
   SignalStateCount[3] = 0;

   SampleSize = 0;
}

FitResultSummary FitClass::DoFit(FitConfiguration configuration)
{
   ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit", "Migrad");
   // ROOT::Math::Minimizer *Worker = ROOT::Math::Factory::CreateMinimizer("Minuit2", "Migrad");

   Worker->SetPrintLevel(-2);
   Worker->SetMaxFunctionCalls(1e9);
   Worker->SetMaxIterations(1e9);
   Worker->SetTolerance(1e-10);

   ROOT::Math::Functor Function(this, &FitClass::CalculateLogLikelihoodAll, 5);
   Worker->SetFunction(Function);

   double StepSize[5] = {0};
   StepSize[0] = (configuration.FloatEQEL == true) ? 0.1 : 0;
   StepSize[1] = (configuration.FloatGLEL == true) ? 0.1 : 0;
   StepSize[2] = (configuration.FloatGRGL == true) ? 0.1 : 0;
   StepSize[3] = (configuration.FloatGQLGL == true) ? 0.1 : 0;
   StepSize[4] = (configuration.FloatGQRGQL == true) ? 0.1 : 0;

   // double InitialValues[18] = {0, 0, 5.05, 0.0, 0., 0.0, -0, 0.0, 0, 0.0, 0, 0.0, 0, 0, 0, 0, 0, 0};
   // double StepSize[18] = {0.1, 0, 0.1, 0, 0.1, 0, 0.1, 0, 0.1, 0, 0.1, 0, 0, 0, 0, 0, 0, 0};

   Worker->SetLimitedVariable(0, "EQEL",  configuration.EQELInitialValue, StepSize[0], -1000, 1000);
   Worker->SetLimitedVariable(1, "GLEL",  configuration.GLELInitialValue, StepSize[1], -1000, 1000);
   Worker->SetLimitedVariable(2, "GRGL",  configuration.GRGLInitialValue, StepSize[2], -1000, 1000);
   Worker->SetLimitedVariable(3, "GQLGL", configuration.GQLGLInitialValue, StepSize[3], -1000, 1000);
   Worker->SetLimitedVariable(4, "GQRGQL", configuration.GQRGQLInitialValue, StepSize[4], -1000, 1000);

   Worker->Minimize();   Worker->Minimize();
   Worker->Minimize();   Worker->Minimize();
   Worker->Minimize();   Worker->Minimize();
   Worker->Minimize();   Worker->Minimize();
   Worker->Minimize();   Worker->Minimize();

   const double *Parameters = Worker->X();
   const double *Errors = Worker->Errors();

   FitResultSummary Result;
   Result.EQEL = Parameters[0];
   Result.EQELError = Errors[0];
   Result.GLEL = Parameters[1];
   Result.GLELError = Errors[1];
   Result.GRGL = Parameters[2];
   Result.GRGLError = Errors[2];
   Result.GQLGL = Parameters[3];
   Result.GQLGLError = Errors[3];
   Result.GQRGQL = Parameters[4];
   Result.GQRGQLError = Errors[4];
   Result.EDM = Worker->Edm();
   Result.FitStatus = Worker->CovMatrixStatus();

   Result.Sem = SignalStateCount[0];
   Result.Sme = SignalStateCount[1];
   Result.See = SignalStateCount[2];
   Result.Smm = SignalStateCount[3];

   delete Worker;

   return Result;
}

vector<double> ListToVector(int N, double x1, double x2, double x3, double x4,
      double x5, double x6, double x7, double x8, double x9, double x10,
      double x11, double x12, double x13, double x14, double x15, double x16)
{
   vector<double> Result(N);

   if(N > 0)   Result[0] = x1;
   if(N > 1)   Result[1] = x2;
   if(N > 2)   Result[2] = x3;
   if(N > 3)   Result[3] = x4;
   if(N > 4)   Result[4] = x5;
   if(N > 5)   Result[5] = x6;
   if(N > 6)   Result[6] = x7;
   if(N > 7)   Result[7] = x8;
   if(N > 8)   Result[8] = x9;
   if(N > 9)   Result[9] = x10;
   if(N > 10)   Result[10] = x11;
   if(N > 11)   Result[11] = x12;
   if(N > 12)   Result[12] = x13;
   if(N > 13)   Result[13] = x14;
   if(N > 14)   Result[14] = x15;
   if(N > 15)   Result[15] = x16;

   return Result;
}




