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
#include "Cuts.h"
#include "Constants.h"

#include "FitClass.h"
#include "StockM4l.h"

int main(int argc, char *argv[]);
class FileHandle
{
public:
   string FileName;
   string CutLabel;
   StockM4l M4l;
   bool UseStockM4l;
   int CurrentIndex;
   DataHelper DHFile;
   TFile *File;
   TTree *Tree;
   string Energy;
public:
   double l1id, l3id;
   double VS[16][16];
   double IS[16][16];
   double VB[2];
   double IB[2];
   double l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   double l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
public:
   FileHandle(string filename, string cutlabel, string energy, bool usestockm4l);
   ~FileHandle();
   bool GiveNextEvent(SingleEvent &Event, bool Recycle = false);
};

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   PrintConstants();

   srand(time(NULL));

   string SEMFileName, SEEFileName, BEMFileName1, BEEFileName1, BEMFileName2, BEEFileName2;
   double SEMSize, SEESize, BEMSize1, BEESize1, BEMSize2, BEESize2;
   string Energy = "0TeV";
   string CutLabel = "A";

   if(argc != 33)
   {
      cerr << "Usage: " << argv[0] << endl
         << " SignalEMFile SignalEMSize BackgroundEMFile1 BackgroundEMSize1 BackgroundEMFile2 BackgroundEMSize2" << endl
         << " SignalEEFile SignalEESize BackgroundEEFile1 BackgroundEESize1 BackgroundEEFile2 BackgroundEESize2" << endl
         << " Energy CutLabel UUbarDDbarRatio_2e2mu UUbarDDbarRatio_4e" << endl
         << " A2ZZ A3ZZ A4ZZ A2ZA A3ZA A4ZA A2AA A3AA" << endl
         << " YT YTA MT GWW MW" << endl
         << " DoMinYT DoIntYT DoHypTest" << endl
         << endl;
      return -1;
   }

   SEMFileName = argv[1];     SEMSize = atof(argv[2]);
   BEMFileName1 = argv[3];    BEMSize1 = atof(argv[4]);
   BEMFileName2 = argv[5];    BEMSize2 = atof(argv[6]);
   SEEFileName = argv[7];     SEESize = atof(argv[8]);
   BEEFileName1 = argv[9];    BEESize1 = atof(argv[10]);
   BEEFileName2 = argv[11];   BEESize2 = atof(argv[12]);
   Energy = argv[13];
   CutLabel = argv[14];

   double UUbarDDbarRatio_2e2mu = atof(argv[15]);
   double UUbarDDbarRatio_4e = atof(argv[16]);

   double A2ZZ = atof(argv[17]);
   double A3ZZ = atof(argv[18]);
   double A4ZZ = atof(argv[19]);
   double A2ZA = atof(argv[20]);
   double A3ZA = atof(argv[21]);
   double A4ZA = atof(argv[22]);
   double A2AA = atof(argv[23]);
   double A3AA = atof(argv[24]);

   double TrueYT  = atof(argv[25]);
   double TrueYTA = atof(argv[26]);
   double TrueMT  = atof(argv[27]);
   double TrueGWW = atof(argv[28]);
   double TrueMW  = atof(argv[29]);

   bool DoMinYT = ((argv[30][0] == 'Y') ? true : false);
   bool DoIntYT = ((argv[31][0] == 'Y') ? true : false);
   bool DoHypTest = ((argv[32][0] == 'Y') ? true : false);

   double BEMSize = BEMSize1 + BEMSize2;
   double BEESize = BEESize1 + BEESize2;

   if(BEMSize1 < 0 && BEMSize2 >= 0)   BEMSize = BEMSize2;
   if(BEMSize2 < 0 && BEMSize1 >= 0)   BEMSize = BEMSize1;
   if(BEMSize1 < 0 && BEMSize2 < 0)    BEMSize = -1;
   if(BEESize1 < 0 && BEESize2 >= 0)   BEESize = BEESize2;
   if(BEESize2 < 0 && BEESize1 >= 0)   BEESize = BEESize1;
   if(BEESize1 < 0 && BEESize2 < 0)    BEESize = -1;

   AVVBasis TrueA;
   TrueA.A1ZZ = 2;   TrueA.A2ZZ = A2ZZ;   TrueA.A3ZZ = A3ZZ;   TrueA.A4ZZ = A4ZZ;
   TrueA.A1ZA = 0;   TrueA.A2ZA = A2ZA;   TrueA.A3ZA = A3ZA;   TrueA.A4ZA = A4ZA;
   TrueA.A1AA = 0;   TrueA.A2AA = A2AA;   TrueA.A3AA = A3AA;   TrueA.A4AA = 0;

   HiggsBasis TrueH(TrueA);
   WarsawBasis TrueW(TrueA);

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   FileHandle SEM(SEMFileName, CutLabel, Energy, true);
   FileHandle BEM1(BEMFileName1, CutLabel, Energy, false);
   FileHandle BEM2(BEMFileName2, CutLabel, Energy, false);
   FileHandle SEE(SEEFileName, CutLabel, Energy, true);
   FileHandle BEE1(BEEFileName1, CutLabel, Energy, false);
   FileHandle BEE2(BEEFileName2, CutLabel, Energy, false);

   vector<FitResultSummary> Results;

   vector<string> AVVConfigurations, AVVPriors;
   // AVVConfigurations.push_back("YYYYYYYY");   AVVPriors.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYNYY");   AVVPriors.push_back("NNNNNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYNYYNYY");   AVVPriors.push_back("NNNNNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("NYNNYNNY");   AVVPriors.push_back("NNNNNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YNNYNNYN");   AVVPriors.push_back("NNNNNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYYYY");   AVVPriors.push_back("YNNYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYNYY");   AVVPriors.push_back("YNNYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYNYYNYY");   AVVPriors.push_back("YNNYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("NYNNYNNY");   AVVPriors.push_back("YNNYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYYYY");   AVVPriors.push_back("YNNNNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYNYY");   AVVPriors.push_back("YNNNNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYNYYNYY");   AVVPriors.push_back("YNNNNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("NYNNYNNY");   AVVPriors.push_back("YNNNNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYYYY");   AVVPriors.push_back("NNNYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYNYY");   AVVPriors.push_back("NNNYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYNYYNYY");   AVVPriors.push_back("NNNYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("NYNNYNNY");   AVVPriors.push_back("NNNYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYYYY");   AVVPriors.push_back("YYYYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYNYY");   AVVPriors.push_back("YYYYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYNYYNYY");   AVVPriors.push_back("YYYYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("NYNNYNNY");   AVVPriors.push_back("YYYYNNNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYYYY");   AVVPriors.push_back("NNNNNYNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYNYY");   AVVPriors.push_back("NNNNNYNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYNYYNYY");   AVVPriors.push_back("NNNNNYNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("NYNNYNNY");   AVVPriors.push_back("NNNNNYNN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYYYY");   AVVPriors.push_back("NNNNNNYN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYNYY");   AVVPriors.push_back("NNNNNNYN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYNYYNYY");   AVVPriors.push_back("NNNNNNYN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("NYNNYNNY");   AVVPriors.push_back("NNNNNNYN.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYYYY");   AVVPriors.push_back("NNNNNNNY.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYYYYNYY");   AVVPriors.push_back("NNNNNNNY.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("YYNYYNYY");   AVVPriors.push_back("NNNNNNNY.push_back("NNNNNNNNN");
   // AVVConfigurations.push_back("NYNNYNNY");   AVVPriors.push_back("NNNNNNNY.push_back("NNNNNNNNN");

   vector<string> HiggsConfigurations, HiggsPriors;
   // HiggsConfigurations.push_back("NNYYYYYY");   HiggsPriors.push_back("NNNNNNNNN");
   // HiggsConfigurations.push_back("NNNYNYNY");   HiggsPriors.push_back("NNNNNNNNN");
   // HiggsConfigurations.push_back("NYNNNNNN");   HiggsPriors.push_back("NNNNNNNNN");
   // HiggsConfigurations.push_back("NYYYYYYY");   HiggsPriors.push_back("NNNNNNNNN");
   // HiggsConfigurations.push_back("NNYYYYYY");   HiggsPriors.push_back("YNNYNNNNN");
   // HiggsConfigurations.push_back("NNNYNYNY");   HiggsPriors.push_back("YNNYNNNNN");
   // HiggsConfigurations.push_back("NYNNNNNN");   HiggsPriors.push_back("YNNYNNNNN");
   // HiggsConfigurations.push_back("NYYYYYYY");   HiggsPriors.push_back("YNNYNNNNN");
   // HiggsConfigurations.push_back("NNYYYYYY");   HiggsPriors.push_back("YNNNNNNNN");
   // HiggsConfigurations.push_back("NNNYNYNY");   HiggsPriors.push_back("YNNNNNNNN");
   // HiggsConfigurations.push_back("NYNNNNNN");   HiggsPriors.push_back("YNNNNNNNN");
   // HiggsConfigurations.push_back("NYYYYYYY");   HiggsPriors.push_back("YNNNNNNNN");
   // HiggsConfigurations.push_back("NNYYYYYY");   HiggsPriors.push_back("NNNYNNNNN");
   // HiggsConfigurations.push_back("NNNYNYNY");   HiggsPriors.push_back("NNNYNNNNN");
   // HiggsConfigurations.push_back("NYNNNNNN");   HiggsPriors.push_back("NNNYNNNNN");
   // HiggsConfigurations.push_back("NYYYYYYY");   HiggsPriors.push_back("NNNYNNNNN");
   // HiggsConfigurations.push_back("NNYYYYYY");   HiggsPriors.push_back("YYYYNNNNN");
   // HiggsConfigurations.push_back("NNNYNYNY");   HiggsPriors.push_back("YYYYNNNNN");
   // HiggsConfigurations.push_back("NYNNNNNN");   HiggsPriors.push_back("YYYYNNNNN");
   // HiggsConfigurations.push_back("NYYYYYYY");   HiggsPriors.push_back("YYYYNNNNN");
   // HiggsConfigurations.push_back("NNYYYYYY");   HiggsPriors.push_back("NNNNNYNNN");
   // HiggsConfigurations.push_back("NNNYNYNY");   HiggsPriors.push_back("NNNNNYNNN");
   // HiggsConfigurations.push_back("NYNNNNNN");   HiggsPriors.push_back("NNNNNYNNN");
   // HiggsConfigurations.push_back("NYYYYYYY");   HiggsPriors.push_back("NNNNNYNNN");
   // HiggsConfigurations.push_back("NNYYYYYY");   HiggsPriors.push_back("NNNNNNYNN");
   // HiggsConfigurations.push_back("NNNYNYNY");   HiggsPriors.push_back("NNNNNNYNN");
   // HiggsConfigurations.push_back("NYNNNNNN");   HiggsPriors.push_back("NNNNNNYNN");
   // HiggsConfigurations.push_back("NYYYYYYY");   HiggsPriors.push_back("NNNNNNYNN");
   // HiggsConfigurations.push_back("NNYYYYYY");   HiggsPriors.push_back("NNNNNNNYN");
   // HiggsConfigurations.push_back("NNNYNYNY");   HiggsPriors.push_back("NNNNNNNYN");
   // HiggsConfigurations.push_back("NYNNNNNN");   HiggsPriors.push_back("NNNNNNNYN");
   // HiggsConfigurations.push_back("NYYYYYYY");   HiggsPriors.push_back("NNNNNNNYN");

   vector<string> WarsawConfigurations, WarsawPriors;
   // WarsawConfigurations.push_back("NNYYYYYY");   WarsawPriors.push_back("NNNNNNNNN");
   // WarsawConfigurations.push_back("YNYYYYYY");   WarsawPriors.push_back("NNNNNNNNN");
   // WarsawConfigurations.push_back("NNNYNYNY");   WarsawPriors.push_back("NNNNNNNNN");
   // WarsawConfigurations.push_back("NNYYYYYY");   WarsawPriors.push_back("YNNYNNNNN");
   // WarsawConfigurations.push_back("YNYYYYYY");   WarsawPriors.push_back("YNNYNNNNN");
   // WarsawConfigurations.push_back("NNNYNYNY");   WarsawPriors.push_back("YNNYNNNNN");
   // WarsawConfigurations.push_back("NNYYYYYY");   WarsawPriors.push_back("YNNNNNNNN");
   // WarsawConfigurations.push_back("YNYYYYYY");   WarsawPriors.push_back("YNNNNNNNN");
   // WarsawConfigurations.push_back("NNNYNYNY");   WarsawPriors.push_back("YNNNNNNNN");
   // WarsawConfigurations.push_back("NNYYYYYY");   WarsawPriors.push_back("NNNYNNNNN");
   // WarsawConfigurations.push_back("YNYYYYYY");   WarsawPriors.push_back("NNNYNNNNN");
   // WarsawConfigurations.push_back("NNNYNYNY");   WarsawPriors.push_back("NNNYNNNNN");
   // WarsawConfigurations.push_back("NNYYYYYY");   WarsawPriors.push_back("YYYYNNNNN");
   // WarsawConfigurations.push_back("YNYYYYYY");   WarsawPriors.push_back("YYYYNNNNN");
   // WarsawConfigurations.push_back("NNNYNYNY");   WarsawPriors.push_back("YYYYNNNNN");
   // WarsawConfigurations.push_back("NNYYYYYY");   WarsawPriors.push_back("NNNNNYNNN");
   // WarsawConfigurations.push_back("YNYYYYYY");   WarsawPriors.push_back("NNNNNYNNN");
   // WarsawConfigurations.push_back("NNNYNYNY");   WarsawPriors.push_back("NNNNNYNNN");
   // WarsawConfigurations.push_back("NNYYYYYY");   WarsawPriors.push_back("NNNNNNYNN");
   // WarsawConfigurations.push_back("YNYYYYYY");   WarsawPriors.push_back("NNNNNNYNN");
   // WarsawConfigurations.push_back("NNNYNYNY");   WarsawPriors.push_back("NNNNNNYNN");
   // WarsawConfigurations.push_back("NNYYYYYY");   WarsawPriors.push_back("NNNNNNNYN");
   // WarsawConfigurations.push_back("YNYYYYYY");   WarsawPriors.push_back("NNNNNNNYN");
   // WarsawConfigurations.push_back("NNNYNYNY");   WarsawPriors.push_back("NNNNNNNYN");

   vector<string> LoopConfigurations, LoopPriors;
   vector<bool> LoopVerbosity;
   // LoopConfigurations.push_back("NNNYYNYN");   LoopPriors.push_back("NNNNNNNNNN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("YYYNNNYN");   LoopPriors.push_back("NNNNNNNNNN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNNYNYN");   LoopPriors.push_back("NNNNNNNNNN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNYNNYN");   LoopPriors.push_back("NNNNNNNNNN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("YYYYYNYN");   LoopPriors.push_back("NNNNNNNNNN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNNNNYN");   LoopPriors.push_back("NNNNNNNNNN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNYYNYN");   LoopPriors.push_back("NNNNNNNNYN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("YYYNNNYN");   LoopPriors.push_back("NNNNNNNNYN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNNYNYN");   LoopPriors.push_back("NNNNNNNNYN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNYNNYN");   LoopPriors.push_back("NNNNNNNNYN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("YYYYYNYN");   LoopPriors.push_back("NNNNNNNNYN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNNNNYN");   LoopPriors.push_back("NNNNNNNNYN");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNYYNYN");   LoopPriors.push_back("NNNNNNNNNY");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("YYYNNNYN");   LoopPriors.push_back("NNNNNNNNNY");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNNYNYN");   LoopPriors.push_back("NNNNNNNNNY");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNYNNYN");   LoopPriors.push_back("NNNNNNNNNY");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("YYYYYNYN");   LoopPriors.push_back("NNNNNNNNNY");   LoopVerbosity.push_back(false);
   // LoopConfigurations.push_back("NNNNNNYN");   LoopPriors.push_back("NNNNNNNNNY");   LoopVerbosity.push_back(false);

   string Fs = "NNNN";
   if(BEMSize >= 0)         Fs[0] = 'Y';
   if(BEESize >= 0)         Fs[2] = 'Y';

   double TrueFem = BEMSize / (BEMSize + SEMSize);
   double TrueFee = BEESize / (BEESize + SEESize);

   if(BEMSize < 0 || TrueFem <= 0)   TrueFem = 0;
   if(BEESize < 0 || TrueFee <= 0)   TrueFee = 0;

   vector<FitConfiguration> Configurations;
   for(int i = 0; i < AVVConfigurations.size(); i++)
   {
      string As = AVVConfigurations[i];

      vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = TrueA.A2ZZ;   AValues[1] = TrueA.A3ZZ;   AValues[2] = TrueA.A4ZZ;
      AValues[3] = TrueA.A2ZA;   AValues[4] = TrueA.A3ZA;   AValues[5] = TrueA.A4ZA;
      AValues[6] = TrueA.A2AA;   AValues[7] = TrueA.A3AA;

      vector<double> UUbarDDbarRatio = ListToVector(4, UUbarDDbarRatio_2e2mu, UUbarDDbarRatio_2e2mu,
         UUbarDDbarRatio_4e, UUbarDDbarRatio_4e);

      Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), false, BASIS_AVV, AVVPriors[i], UUbarDDbarRatio));
      // Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), true, BASIS_AVV, AVVPriors[i], UUbarDDbarRatio));
   }
   for(int i = 0; i < HiggsConfigurations.size(); i++)
   {
      string As = HiggsConfigurations[i];

      vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = TrueH.DeltaCZ;   AValues[1] = TrueH.CZB;
      AValues[2] = TrueH.CZZ;       AValues[3] = TrueH.CZZD;
      AValues[4] = TrueH.CZA;       AValues[5] = TrueH.CZAD;
      AValues[6] = TrueH.CAA;       AValues[7] = TrueH.CAAD;

      vector<double> UUbarDDbarRatio = ListToVector(4, UUbarDDbarRatio_2e2mu, UUbarDDbarRatio_2e2mu,
         UUbarDDbarRatio_4e, UUbarDDbarRatio_4e);

      Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), false, BASIS_HIGGS, HiggsPriors[i], UUbarDDbarRatio));
      // Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), true, BASIS_HIGGS, HiggsPriors[i], UUbarDDbarRatio));
   }
   for(int i = 0; i < WarsawConfigurations.size(); i++)
   {
      string As = WarsawConfigurations[i];

      vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = TrueW.CT;    AValues[1] = TrueW.CH;
      AValues[2] = TrueW.CWW;   AValues[3] = TrueW.CWWD;
      AValues[4] = TrueW.CWB;   AValues[5] = TrueW.CWBD;
      AValues[6] = TrueW.CBB;   AValues[7] = TrueW.CBBD;

      vector<double> UUbarDDbarRatio = ListToVector(4, UUbarDDbarRatio_2e2mu, UUbarDDbarRatio_2e2mu,
         UUbarDDbarRatio_4e, UUbarDDbarRatio_4e);

      Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), false, BASIS_WARSAW, WarsawPriors[i], UUbarDDbarRatio));
      // Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), true, BASIS_WARSAW, WarsawPriors[i], UUbarDDbarRatio));
   }
   for(int i = 0; i < LoopConfigurations.size(); i++)
   {
      string As = LoopConfigurations[i];

      vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0);
      AValues[0] = TrueA.A2ZZ;    AValues[1] = TrueA.A3ZZ;   AValues[2] = TrueA.A4ZZ;
      AValues[3] = TrueYT;        AValues[4] = TrueYTA;
      AValues[5] = TrueMT;        AValues[6] = TrueGWW;
      AValues[7] = TrueMW;

      vector<double> UUbarDDbarRatio = ListToVector(4, UUbarDDbarRatio_2e2mu, UUbarDDbarRatio_2e2mu,
         UUbarDDbarRatio_4e, UUbarDDbarRatio_4e);

      Configurations.push_back(FitConfiguration(As, Fs, AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), false, BASIS_LOOP, LoopPriors[i], UUbarDDbarRatio));
      
      // if(Fs != "NNNN")
      //    Configurations.push_back(FitConfiguration(As, "NNNN", AValues, ListToVector(4, TrueFem, 0, TrueFee, 0), false, BASIS_LOOP, LoopPriors[i], UUbarDDbarRatio));
      // if(LoopVerbosity[i] == true)
      //    Configurations[Configurations.size()-1].SetVerbose(true);
   }

   int BackgroundCounter = 0;

   bool MoreEvents = true;
   while(MoreEvents == true)
   {
      int SEMCount = (SEMSize >= 0 ? DrawPoisson(SEMSize) : 0);
      int SEECount = (SEESize >= 0 ? DrawPoisson(SEESize) : 0);
      int BEMCount1 = (BEMSize1 >= 0 ? DrawPoisson(BEMSize1) : 0);
      int BEECount1 = (BEESize1 >= 0 ? DrawPoisson(BEESize1) : 0);
      int BEMCount2 = (BEMSize2 >= 0 ? DrawPoisson(BEMSize2) : 0);
      int BEECount2 = (BEESize2 >= 0 ? DrawPoisson(BEESize2) : 0);

      SingleEvent NewEvent;
      bool Good = true;
      for(int i = 0; i < SEMCount; i++)
      {
         if(SEM.GiveNextEvent(NewEvent, false) == true)
            Fits.AddPoint(NewEvent);
         else
            Good = false;
      }
      for(int i = 0; i < SEECount; i++)
      {
         if(SEE.GiveNextEvent(NewEvent, false) == true)
            Fits.AddPoint(NewEvent);
         else
            Good = false;
      }
      for(int i = 0; i < BEMCount1; i++)
      {
         if(BEM1.GiveNextEvent(NewEvent, true) == true)
            Fits.AddPoint(NewEvent);
         else
            Good = false;
      }
      for(int i = 0; i < BEECount1; i++)
      {
         if(BEE1.GiveNextEvent(NewEvent, true) == true)
            Fits.AddPoint(NewEvent);
         else
            Good = false;
      }
      for(int i = 0; i < BEMCount2; i++)
      {
         if(BEM2.GiveNextEvent(NewEvent, true) == true)
            Fits.AddPoint(NewEvent);
         else
            Good = false;
      }
      for(int i = 0; i < BEECount2; i++)
      {
         if(BEE2.GiveNextEvent(NewEvent, true) == true)
            Fits.AddPoint(NewEvent);
         else
            Good = false;
      }

      if(Good == false)
         break;

      Fits.SignalStateCount[0] = SEMCount;
      Fits.SignalStateCount[1] = 0;
      Fits.SignalStateCount[2] = SEECount;
      Fits.SignalStateCount[3] = 0;
      
      Fits.BackgroundStateCount[0] = BEMCount1 + BEMCount2;
      Fits.BackgroundStateCount[1] = 0;
      Fits.BackgroundStateCount[2] = BEECount1 + BEECount2;
      Fits.BackgroundStateCount[3] = 0;

      cout << "." << endl;

      // Normal Fits
      for(int iC = 0; iC < (int)Configurations.size(); iC++)
      {
         // cout << iC << "/" << (int)Configurations.size() << endl;

         FitConfiguration Temp = Configurations[iC];

         FitResultSummary ResultTemp = Fits.DoFit(Temp);
         ResultTemp.ID = FitCount;

         Results.push_back(ResultTemp);
      }

      // Scan gWW minimizing yt
      if(DoMinYT == true)
      {
         // Step 1 - find the best point
         vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0);
         AValues[0] = TrueA.A2ZZ;
         AValues[1] = TrueA.A3ZZ;
         AValues[2] = TrueA.A4ZZ;
         AValues[3] = TrueYT;        AValues[4] = TrueYTA;
         AValues[5] = TrueMT;        AValues[6] = TrueGWW;
         AValues[7] = TrueMW;

         vector<double> UUbarDDbarRatio
            = ListToVector(4, UUbarDDbarRatio_2e2mu, UUbarDDbarRatio_2e2mu,
               UUbarDDbarRatio_4e, UUbarDDbarRatio_4e);

         FitConfiguration Fit("NNNYNNYN", "NNNN",
            AValues, ListToVector(4, TrueFem, 0, TrueFee, 0),
            false, BASIS_LOOP, "NNNNNNNNNNNN", UUbarDDbarRatio);
         Fit.SetVerbose(false);
         
         FitResultSummary ResultTemp = Fits.DoFit(Fit);

         cout << "BestMinYT " << FitCount << " " << ResultTemp.Parameter4 << " " << ResultTemp.Parameter7 << " " << ResultTemp.BestNLL << endl;

         // Step 2 - scan around gww minimizing yt in the process
         double Unit = ResultTemp.Parameter7;
         if(fabs(Unit) < 2)
            Unit = 2;
         for(double iX = -10; iX <= 10; iX = iX + 0.2)
         {
            FitConfiguration Temp = Fit;
            Temp.SetFloatAs("NNNYNNNN");   // Float only yt
            Temp.Parameter4InitialValue = ResultTemp.Parameter4;
            Temp.Parameter7InitialValue = iX * Unit;

            FitResultSummary FitTemp = Fits.DoFit(Temp);

            cout << "MinYT " << FitCount<< " " << FitTemp.Parameter4 << " " << FitTemp.Parameter7 << " " << FitTemp.BestNLL << endl;
         }
      }

      // Scan gWW AND yt
      if(DoIntYT == true)
      {
         // Step 1 - find the best point
         vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0);
         AValues[0] = TrueA.A2ZZ;
         AValues[1] = TrueA.A3ZZ;
         AValues[2] = TrueA.A4ZZ;
         AValues[3] = TrueYT;        AValues[4] = TrueYTA;
         AValues[5] = TrueMT;        AValues[6] = TrueGWW;
         AValues[7] = TrueMW;

         vector<double> UUbarDDbarRatio
            = ListToVector(4, UUbarDDbarRatio_2e2mu, UUbarDDbarRatio_2e2mu,
               UUbarDDbarRatio_4e, UUbarDDbarRatio_4e);

         FitConfiguration Fit("NNNYNNYN", "NNNN",
            AValues, ListToVector(4, TrueFem, 0, TrueFee, 0),
            false, BASIS_LOOP, "NNNNNNNNNNNN", UUbarDDbarRatio);
         Fit.SetVerbose(false);
         
         FitResultSummary ResultTemp = Fits.DoFit(Fit);

         cout << "BestIntYT " << FitCount << " " << ResultTemp.Parameter4 << " " << ResultTemp.Parameter7 << " " << ResultTemp.BestNLL << endl;

         // Step 2 - scan around gww minimizing yt in the process
         double Unit4 = ResultTemp.Parameter4;
         double Unit7 = ResultTemp.Parameter7;
         if(fabs(Unit4) < 2)   Unit4 = 2;
         if(fabs(Unit7) < 2)   Unit7 = 2;
         for(double iX = -10; iX <= 10; iX = iX + 0.25)
         {
            for(double iY = -10; iY <= 10; iY = iY + 0.25)
            {
               double Parameters[12];
               Parameters[0]  = ResultTemp.Parameter1;
               Parameters[1]  = ResultTemp.Parameter2;
               Parameters[2]  = ResultTemp.Parameter3;
               Parameters[3]  = iX * Unit4;
               Parameters[4]  = ResultTemp.Parameter5;
               Parameters[5]  = ResultTemp.Parameter6;
               Parameters[6]  = iY * Unit7;
               Parameters[7]  = ResultTemp.Parameter8;
               Parameters[8]  = ResultTemp.Fem;
               Parameters[9]  = ResultTemp.Fme;
               Parameters[10] = ResultTemp.Fee;
               Parameters[11] = ResultTemp.Fmm;

               double NLL = Fits.CalculateLogLikelihoodAll(Parameters);

               cout << "IntYT " << FitCount << " " << Parameters[3] << " " << Parameters[6] << " " << NLL << endl;
            }
         }
      }
      
      // Do hypothesis testing of lambda = +1 vs. -1/2, integrating out yt
      if(DoHypTest == true)
      {
         // Setup the likelihood with a fake fit
         vector<double> AValues = ListToVector(8, 0, 0, 0, 0, 0, 0, 0);
         AValues[0] = TrueA.A2ZZ;
         AValues[1] = TrueA.A3ZZ;
         AValues[2] = TrueA.A4ZZ;
         AValues[3] = TrueYT;        AValues[4] = TrueYTA;
         AValues[5] = TrueMT;        AValues[6] = TrueGWW;
         AValues[7] = TrueMW;

         vector<double> UUbarDDbarRatio
            = ListToVector(4, UUbarDDbarRatio_2e2mu, UUbarDDbarRatio_2e2mu,
               UUbarDDbarRatio_4e, UUbarDDbarRatio_4e);

         FitConfiguration Fit("NNNNNNNN", "NNNN",
            AValues, ListToVector(4, TrueFem, 0, TrueFee, 0),
            false, BASIS_LOOP, "NNNNNNNNNNNN", UUbarDDbarRatio);
         Fit.SetVerbose(false);
         
         FitResultSummary ResultTemp = Fits.DoFit(Fit);

         // Scan!
         double X[5] = {-1, -0.5, 0, 0.5, 1};

         for(int iX = 0; iX < 5; iX++)
         {
            for(double Y = -5; Y <= 5; Y = Y + 0.1)
            {
               double Parameters[12];
               Parameters[0]  = TrueA.A2ZZ;
               Parameters[1]  = TrueA.A3ZZ;
               Parameters[2]  = TrueA.A4ZZ;
               Parameters[3]  = Y;
               Parameters[4]  = TrueYTA;
               Parameters[5]  = TrueMT;
               Parameters[6]  = X[iX] * 2;
               Parameters[7]  = TrueMW;
               Parameters[8]  = TrueFem;
               Parameters[9]  = TrueFem;
               Parameters[10] = TrueFee;
               Parameters[11] = TrueFee;

               double NLL = Fits.CalculateLogLikelihoodAll(Parameters);

               cout << "HypTest " << FitCount << " " << Parameters[3] << " " << Parameters[6] << " " << NLL << endl;
            }
         }
       }

      FitCount = FitCount + 1;

      Fits.ClearPoints();
   }

   TFile OutputFile("OutputFile.root", "RECREATE");

   string BranchList = "ID";
   BranchList = BranchList + ":EDM:Status:TruthNLL:BestNLL";          // 5
   BranchList = BranchList + ":P1:P1Error";                           // 7
   BranchList = BranchList + ":P2:P2Error";                           // 9
   BranchList = BranchList + ":P3:P3Error";                           // 11
   BranchList = BranchList + ":P4:P4Error";                           // 13    
   BranchList = BranchList + ":P5:P5Error";                           // 15
   BranchList = BranchList + ":P6:P6Error";                           // 17
   BranchList = BranchList + ":P7:P7Error";                           // 19
   BranchList = BranchList + ":P8:P8Error";                           // 21
   BranchList = BranchList + ":Sem:Sme:See:Smm:Bem:Bme:Bee:Bmm";      // 29
   BranchList = BranchList + ":Fem:FemError";                         // 31
   BranchList = BranchList + ":Fme:FmeError";                         // 33
   BranchList = BranchList + ":Fee:FeeError";                         // 35
   BranchList = BranchList + ":Fmm:FmmError";                         // 37
   BranchList = BranchList + ":NoSquareMode:Basis";                   // 39
   BranchList = BranchList + ":Rud_em:Rud_me:Rud_ee:Rud_mm";          // 43
   BranchList = BranchList + ":Prior0:Prior1:Prior2:Prior3";          // 47
   BranchList = BranchList + ":Prior4:Prior5:Prior6:Prior7";          // 51
   BranchList = BranchList + ":Prior8:Prior9:Prior10:Prior11";        // 55
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100] = {0};

      Array[0] = Results[i].ID;

      Array[1] = Results[i].EDM;          Array[2] = Results[i].FitStatus;
      Array[3] = Results[i].TruthNLL;     Array[4] = Results[i].BestNLL;

      Array[5] = Results[i].Parameter1;   Array[6] = Results[i].Parameter1Error;
      Array[7] = Results[i].Parameter2;   Array[8] = Results[i].Parameter2Error;
      Array[9] = Results[i].Parameter3;   Array[10] = Results[i].Parameter3Error;
      Array[11] = Results[i].Parameter4;  Array[12] = Results[i].Parameter4Error;
      Array[13] = Results[i].Parameter5;  Array[14] = Results[i].Parameter5Error;
      Array[15] = Results[i].Parameter6;  Array[16] = Results[i].Parameter6Error;
      Array[17] = Results[i].Parameter7;  Array[18] = Results[i].Parameter7Error;
      Array[19] = Results[i].Parameter8;  Array[20] = Results[i].Parameter8Error;

      Array[21] = Results[i].Sem;         Array[25] = Results[i].Bem;
      Array[22] = Results[i].Sme;         Array[26] = Results[i].Bme;
      Array[23] = Results[i].See;         Array[27] = Results[i].Bee;
      Array[24] = Results[i].Smm;         Array[28] = Results[i].Bmm;

      Array[29] = Results[i].Fem;         Array[30] = Results[i].FemError;
      Array[31] = Results[i].Fme;         Array[32] = Results[i].FmeError;
      Array[33] = Results[i].Fee;         Array[34] = Results[i].FeeError;
      Array[35] = Results[i].Fmm;         Array[36] = Results[i].FmmError;

      Array[37] = Results[i].NoSquareMode;
      Array[38] = Results[i].Basis;
      Array[39] = Results[i].UUbarDDbarRatio[0];
      Array[40] = Results[i].UUbarDDbarRatio[1];
      Array[41] = Results[i].UUbarDDbarRatio[2];
      Array[42] = Results[i].UUbarDDbarRatio[3];

      Array[43] = Results[i].UsedPriors[0];
      Array[44] = Results[i].UsedPriors[1];
      Array[45] = Results[i].UsedPriors[2];
      Array[46] = Results[i].UsedPriors[3];
      Array[47] = Results[i].UsedPriors[4];
      Array[48] = Results[i].UsedPriors[5];
      Array[49] = Results[i].UsedPriors[6];
      Array[50] = Results[i].UsedPriors[7];
      Array[51] = Results[i].UsedPriors[8];
      Array[52] = Results[i].UsedPriors[9];
      Array[53] = Results[i].UsedPriors[10];
      Array[54] = Results[i].UsedPriors[11];

      OutputTree.Fill(Array);
   }

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

FileHandle::~FileHandle()
{
   if(File != NULL)
   {
      File->Close();
      delete File;
   }
}

bool FileHandle::GiveNextEvent(SingleEvent &NewEvent, bool Recycle)
{
   if(Tree == NULL || File == NULL)
      return false;
   if(CurrentIndex >= Tree->GetEntries() && Recycle == false)
      return false;
   if(CurrentIndex >= Tree->GetEntries() && Recycle == true && Tree->GetEntries() == 0)
      return false;
   if(CurrentIndex >= Tree->GetEntries() && Recycle == true && Tree->GetEntries() > 0)
      CurrentIndex = 0;

   string SignalBranch = "TA1";
   string BackgroundBranch = "TA2";

   SignalBranch[1] = CutLabel[0];
   BackgroundBranch[1] = CutLabel[0];

   int iE = CurrentIndex;
   Tree->GetEntry(iE);
   CurrentIndex = CurrentIndex + 1;

   l1id = fabs(l1id);
   l3id = fabs(l3id);

   LeptonVectors Leptons;
   Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
   Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
   Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
   Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

   if(l1id == l3id)
      Leptons = Leptons.ReorderLeptons4e();
   else
      Leptons = Leptons.ReorderLeptons2e2mu();

   EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);
   if(UseStockM4l == true)
   {
      double Ratio = M4l[iE] / Event.HMass;
      Event.HMass = Event.HMass * Ratio;
      Event.ZMass = Event.ZMass * Ratio;
      Event.Z2Mass = Event.Z2Mass * Ratio;
      Leptons = ConvertAnglesToVectorsRoberto(Event);
   }

   // double HACK = Event.HMass / 125;

   if(Event.HMass > 135 || Event.HMass < 115)
      return GiveNextEvent(NewEvent);

   int CutIndex = CutLabel[0] - 'A';
   // cout << "CutLabel = " << CutLabel << endl;
   // cout << "Cut index = " << CutIndex << endl;
   if(PassPairingCuts(Leptons)[CutIndex] == false)
      return GiveNextEvent(NewEvent);

   string State = "";
   if(l1id == l3id)   State = "ee";
   if(l1id != l3id)   State = "em";

   // string DHState = "Cut" + CutLabel;
   string DHState = Energy;

   if(State == "em")
      SignalBranch[0] = 'T', BackgroundBranch[0] = 'T';
   else
      SignalBranch[0] = 'V', BackgroundBranch[0] = 'V';

   if(State == "")   // WTF
      return false;
   else
   {
      string Suffix[16];
      Suffix[0]  = "A1ZZR";
      Suffix[1]  = "A2ZZR";
      Suffix[2]  = "A3ZZR";
      Suffix[3]  = "A4ZZR";
      Suffix[4]  = "A1ZAR";
      Suffix[5]  = "A2ZAR";
      Suffix[6]  = "A3ZAR";
      Suffix[7]  = "A4ZAR";
      Suffix[8]  = "A1AZR";
      Suffix[9]  = "A2AZR";
      Suffix[10] = "A3AZR";
      Suffix[11] = "A4AZR";
      Suffix[12] = "A1AAR";
      Suffix[13] = "A2AAR";
      Suffix[14] = "A3AAR";
      Suffix[15] = "A4AAR";

      for(int i = 0; i < 16; i++)
      {
         for(int j = 0; j < 16; j++)
         {
            string Branch = SignalBranch + "_" + Suffix[i] + "_" + Suffix[j];
            IS[i][j] = DHFile[DHState][Branch].GetDouble();
         }
      }

      IB[0] = DHFile[DHState][BackgroundBranch+"_UUbar"].GetDouble();
      IB[1] = DHFile[DHState][BackgroundBranch+"_DDbar"].GetDouble();
   }

   // bool Good = true;
   // for(int i = 0; i < 16; i++)
   //    if(VS[i][i] > 0.99 || VS[i][i] < 1e-50)
   //       Good = false;
   // if(Good == false)
   //    return GiveNextEvent(NewEvent);

   for(int i = 0; i < 16; i++)
      for(int j = 0; j < 16; j++)
         NewEvent.VS[i][j] = VS[i][j];
   for(int i = 0; i < 16; i++)
      for(int j = 0; j < 16; j++)
         NewEvent.IS[i][j] = IS[i][j];
   for(int i = 0; i < 2; i++)
      NewEvent.VB[i] = VB[i];
   for(int i = 0; i < 2; i++)
      NewEvent.IB[i] = IB[i];
   NewEvent.event = Event;
   NewEvent.state = State;

   return true;
}

FileHandle::FileHandle(string filename, string cutlabel, string energy, bool usestockm4l)
   : M4l(31426, 100000), DHFile("Normalization.dh")
{
   FileName = filename;
   CutLabel = cutlabel;
   Energy = energy;
   UseStockM4l = usestockm4l;
   CurrentIndex = 0;

   File = NULL;
   Tree = NULL;

   File = new TFile(FileName.c_str());
   Tree = (TTree *)File->Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File->Get("Tree");
   if(Tree == NULL)
      return;
   
   Tree->SetBranchAddress("L1ID", &l1id);
   Tree->SetBranchAddress("L3ID", &l3id);
   
   string Suffix[16];
   Suffix[0]  = "A1ZZR";
   Suffix[1]  = "A2ZZR";
   Suffix[2]  = "A3ZZR";
   Suffix[3]  = "A4ZZR";
   Suffix[4]  = "A1ZAR";
   Suffix[5]  = "A2ZAR";
   Suffix[6]  = "A3ZAR";
   Suffix[7]  = "A4ZAR";
   Suffix[8]  = "A1AZR";
   Suffix[9]  = "A2AZR";
   Suffix[10] = "A3AZR";
   Suffix[11] = "A4AZR";
   Suffix[12] = "A1AAR";
   Suffix[13] = "A2AAR";
   Suffix[14] = "A3AAR";
   Suffix[15] = "A4AAR";

   for(int i = 0; i < 16; i++)
      for(int j = 0; j < 16; j++)
         Tree->SetBranchAddress(Form("B1_%s_%s", Suffix[i].c_str(), Suffix[j].c_str()), &VS[i][j]);
   Tree->SetBranchAddress("B2_UUbar", &VB[0]);
   Tree->SetBranchAddress("B2_DDbar", &VB[1]);

   Tree->SetBranchAddress("L1PT",  &l1pt);
   Tree->SetBranchAddress("L1Eta", &l1eta);
   Tree->SetBranchAddress("L1Phi", &l1phi);
   Tree->SetBranchAddress("L2PT",  &l2pt);
   Tree->SetBranchAddress("L2Eta", &l2eta);
   Tree->SetBranchAddress("L2Phi", &l2phi);
   Tree->SetBranchAddress("L3PT",  &l3pt);
   Tree->SetBranchAddress("L3Eta", &l3eta);
   Tree->SetBranchAddress("L3Phi", &l3phi);
   Tree->SetBranchAddress("L4PT",  &l4pt);
   Tree->SetBranchAddress("L4Eta", &l4eta);
   Tree->SetBranchAddress("L4Phi", &l4phi);
}


