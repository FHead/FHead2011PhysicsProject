//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
//---------------------------------------------------------------------------
#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TH2D.h"
//---------------------------------------------------------------------------
#include "Code/DrawRandom.h"
#include "DataHelper.h"
#include "PlotHelper2.h"
#include "ProgressBar.h"
//---------------------------------------------------------------------------
#include "AngleConversion.h"
#include "Lists.h"
#include "Cuts.h"
//---------------------------------------------------------------------------
#include "FitClass.h"
#include "M4lSpectrum.h"
//---------------------------------------------------------------------------
#define DEFAULT_PROCESS 153332
//---------------------------------------------------------------------------
int main(int argc, char *argv[]);
bool ReadEvents(vector<SingleEvent> &EventsEM, vector<SingleEvent> &EventsME,
   vector<SingleEvent> &EventsEE, vector<SingleEvent> &EventsMM,
   string FileName, int Process = DEFAULT_PROCESS,
   double MaxWeight = 1, bool Is7TeV = false, int ToyNumber = -1);
int GetEventCount(double Mean, double Sigma);
int PullEvents(vector<SingleEvent> &Events, vector<SingleEvent> &Source, double Mean, double Sigma,
      bool Recycle = false);
int PullToyEvents(vector<SingleEvent> &Events, vector<SingleEvent> &Source, int ToyNumber);
vector<double> SumVector(vector<double> &V1, vector<double> &V2);
vector<double> ScaleVector(vector<double> &V1, double Factor);
void SetAlias(TTree &ResultTree);
//---------------------------------------------------------------------------
#define EVENTLIMIT 1000
#define PI 3.14159265358979323846264338327950288479716939937510
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   srand(time(NULL));

   string SignalFileName[2]     = {"EventF.root", "Dummy.root"};
   string BackgroundFileName[2] = {"EventF.root", "Dummy.root"};
   string ZJFileName[2]         = {"EventF.root", "Dummy.root"};
   string ggZZFileName[2]       = {"EventF.root", "Dummy.root"};

   int Factor = 10;

   if(argc < 19)
   {
      cerr << "Usage: " << argv[0]
         << " SignalRootFile7TeV BackgroundRootFile7TeV ZJRootFile7TeV ggZZRootFile7TeV"
         << " SignalRootFile8TeV BackgroundRootFile8TeV ZJRootFile8TeV ggZZRootFile8TeV"
         << " A2ZZ A3ZZ A2ZA A3ZA A2AA A3AA A1L1ZZ ToyNumber FloatParameters FloatPhases"
         << endl;
      return -1;
   }

   SignalFileName[1]     = argv[1];
   BackgroundFileName[1] = argv[2];
   ZJFileName[1]         = argv[3];
   ggZZFileName[1]       = argv[4];
   SignalFileName[0]     = argv[5];
   BackgroundFileName[0] = argv[6];
   ZJFileName[0]         = argv[7];
   ggZZFileName[0]       = argv[8];

   double A2ZZ = atof(argv[9]);
   double A3ZZ = atof(argv[10]);
   double A2ZA = atof(argv[11]);
   double A3ZA = atof(argv[12]);
   double A2AA = atof(argv[13]);
   double A3AA = atof(argv[14]);
   double A1L1ZZ = atof(argv[15]);
   double A1LQZZ = 0;
   int TargetToyNumber = atoi(argv[16]);
   string FloatParameterConfigString = argv[17];
   string FloatPhasesConfigString = argv[18];

   FitClass Fits;
   Fits.ClearPoints();

   vector<FitResultSummary> Results;

   PsFileHelper PsFile("FitResult.ps");

   vector<SingleEvent> SignalEM[2],     SignalME[2],     SignalEE[2],     SignalMM[2];
   vector<SingleEvent> BackgroundEM[2], BackgroundME[2], BackgroundEE[2], BackgroundMM[2];
   vector<SingleEvent> ZJEM[2],         ZJME[2],         ZJEE[2],         ZJMM[2];
   vector<SingleEvent> ggZZEM[2],       ggZZME[2],       ggZZEE[2],       ggZZMM[2];

   bool HasBadEvent[8] = {0};
   HasBadEvent[0] = ReadEvents(SignalEM[1],     SignalME[1],     SignalEE[1],     SignalMM[1],     SignalFileName[1],     DEFAULT_PROCESS, 1, true,  TargetToyNumber);
   HasBadEvent[1] = ReadEvents(BackgroundEM[1], BackgroundME[1], BackgroundEE[1], BackgroundMM[1], BackgroundFileName[1], 0,               1, true,  TargetToyNumber);
   HasBadEvent[2] = ReadEvents(ggZZEM[1],       ggZZME[1],       ggZZEE[1],       ggZZMM[1],       ggZZFileName[1],       1,               1, true,  TargetToyNumber);
   HasBadEvent[3] = ReadEvents(ZJEM[1],         ZJME[1],         ZJEE[1],         ZJMM[1],         ZJFileName[1],         2,               1, true,  TargetToyNumber);
   HasBadEvent[4] = ReadEvents(SignalEM[0],     SignalME[0],     SignalEE[0],     SignalMM[0],     SignalFileName[0],     DEFAULT_PROCESS, 1, false, TargetToyNumber);
   HasBadEvent[5] = ReadEvents(BackgroundEM[0], BackgroundME[0], BackgroundEE[0], BackgroundMM[0], BackgroundFileName[0], 0,               1, false, TargetToyNumber);
   HasBadEvent[6] = ReadEvents(ggZZEM[0],       ggZZME[0],       ggZZEE[0],       ggZZMM[0],       ggZZFileName[0],       1,               1, false, TargetToyNumber);
   HasBadEvent[7] = ReadEvents(ZJEM[0],         ZJME[0],         ZJEE[0],         ZJMM[0],         ZJFileName[0],         2,               1, false, TargetToyNumber);

   bool AnyHasBadEvent = false;
   for(int i = 0; i < 8; i++)
      if(HasBadEvent[i] == true)
         AnyHasBadEvent = true;

   // 8 TeV Yield
   vector<double> NS8 = ListToVector(4, 4.359, 3.385, 3.066, 5.983);
   // vector<double> NS8 = ListToVector(4, 0, 0, 3.066, 5.983);
   vector<double> NSSigma8 = ListToVector(4, 0.11, 0.11, 0.11, 0.11);
   vector<double> NB8 = ListToVector(4, 3.523, 2.018, 1.785, 4.635);
   // vector<double> NB8 = ListToVector(4, 0, 0, 1.785, 4.635);
   vector<double> NBSigma8 = ListToVector(4, 0.048, 0.048, 0.047, 0.047);
   vector<double> NZJ8 = ListToVector(4, 0.721, 2.077, 1.691, 0.823);
   // vector<double> NZJ8 = ListToVector(4, 0, 0, 1.691, 0.823);
   vector<double> NZJSigma8 = ListToVector(4, 0.40, 0.40, 0.40, 0.40);
   vector<double> NggZZ8 = ListToVector(4, 0.185, 0.149, 0.120, 0.250);
   // vector<double> NggZZ8 = ListToVector(4, 0, 0, 0.120, 0.250);
   vector<double> NggZZSigma8 = ListToVector(4, 0.25, 0.25, 0.25, 0.25);

   NS8 = ScaleVector(NS8, Factor);
   NB8 = ScaleVector(NB8, Factor);
   NZJ8 = ScaleVector(NZJ8, Factor);
   NggZZ8 = ScaleVector(NggZZ8, Factor);

   vector<double> NS8Prime = NS8;
   vector<double> NB8Prime = NB8;
   vector<double> NZJ8Prime = NZJ8;
   vector<double> NggZZ8Prime = NggZZ8;

   NS8Prime[0] = NS8[0] + NS8[1];            NS8Prime[1] = 0;
   NB8Prime[0] = NB8[0] + NB8[1];            NB8Prime[1] = 0;
   NZJ8Prime[0] = NZJ8[0] + NZJ8[1];         NZJ8Prime[1] = 0;
   NggZZ8Prime[0] = NggZZ8[0] + NggZZ8[1];   NggZZ8Prime[1] = 0;

   // 7 TeV Yield
   vector<double> NS7 = ListToVector(4, 0.946, 0.743, 0.701, 1.127);
   // vector<double> NS7 = ListToVector(4, 0, 0, 0.701, 1.127);
   vector<double> NSSigma7 = ListToVector(4, 0.11, 0.11, 0.11, 0.11);
   vector<double> NB7 = ListToVector(4, 0.873, 0.547, 0.518, 1.075);
   // vector<double> NB7 = ListToVector(4, 0, 0, 0.518, 1.075);
   vector<double> NBSigma7 = ListToVector(4, 0.048, 0.048, 0.047, 0.047);
   vector<double> NZJ7 = ListToVector(4, 0.110, 0.583, 0.406, 0.167);
   // vector<double> NZJ7 = ListToVector(4, 0, 0, 0.406, 0.167);
   vector<double> NZJSigma7 = ListToVector(4, 0.40, 0.40, 0.40, 0.40);
   vector<double> NggZZ7 = ListToVector(4, 0.0271, 0.0205, 0.0210, 0.0367);
   // vector<double> NggZZ7 = ListToVector(4, 0, 0, 0.0210, 0.0367);
   vector<double> NggZZSigma7 = ListToVector(4, 0.25, 0.25, 0.25, 0.25);

   NS7 = ScaleVector(NS7, Factor);
   NB7 = ScaleVector(NB7, Factor);
   NZJ7 = ScaleVector(NZJ7, Factor);
   NggZZ7 = ScaleVector(NggZZ7, Factor);

   vector<double> NS7Prime = NS7;
   vector<double> NB7Prime = NB7;
   vector<double> NZJ7Prime = NZJ7;
   vector<double> NggZZ7Prime = NggZZ7;

   NS7Prime[0] = NS7[0] + NS7[1];            NS7Prime[1] = 0;
   NB7Prime[0] = NB7[0] + NB7[1];            NB7Prime[1] = 0;
   NZJ7Prime[0] = NZJ7[0] + NZJ7[1];         NZJ7Prime[1] = 0;
   NggZZ7Prime[0] = NggZZ7[0] + NggZZ7[1];   NggZZ7Prime[1] = 0;

   string As = FloatParameterConfigString;
   string Phases = FloatPhasesConfigString;
   string Counts = "NNNN";
   string Fs = "NNNNNNNNNNNN";

   FitConfiguration Configuration(
      As, Phases, Counts, Counts,
      Fs, Fs, "NNNNNNN", "N",                                                  /* What to float */
      ListToVector(8, A2ZZ, A3ZZ, A2ZA, A3ZA, A2AA, A3AA, A1L1ZZ, A1LQZZ),        /* Ratios */
      ListToVector(8, 0, 0, 0, 0, 0, 0, 0, 0),                                    /* Phases */
      ListToVector(4, NS7Prime[0] + NB7Prime[0] + NZJ7Prime[0] + NggZZ7Prime[0], NS7Prime[1] + NB7Prime[1] + NZJ7Prime[1] + NggZZ7Prime[1],
         NS7Prime[2] + NB7Prime[2] + NZJ7Prime[2] + NggZZ7Prime[2], NS7Prime[3] + NB7Prime[3] + NZJ7Prime[3] + NggZZ7Prime[3]),   /* Event Counts */
      ListToVector(4, NS8Prime[0] + NB8Prime[0] + NZJ8Prime[0] + NggZZ8Prime[0], NS8Prime[1] + NB8Prime[1] + NZJ8Prime[1] + NggZZ8Prime[1],
         NS8Prime[2] + NB8Prime[2] + NZJ8Prime[2] + NggZZ8Prime[2], NS8Prime[3] + NB8Prime[3] + NZJ8Prime[3] + NggZZ8Prime[3]),   /* Event Counts */
      ListToVector(12, ((Fs[0] == 'Y') ? 0.5 : 0), ((Fs[1] == 'Y') ? 0.5 : 0),
         ((Fs[2] == 'Y') ? 0.5 : 0), ((Fs[3] == 'Y') ? 0.5 : 0),
         ((Fs[4] == 'Y') ? 0.15 : 0), ((Fs[5] == 'Y') ? 0.25 : 0),
         ((Fs[6] == 'Y') ? 0.25 : 0), ((Fs[7] == 'Y') ? 0.15 : 0),
         ((Fs[8] == 'Y') ? 0.12 : 0), ((Fs[9] == 'Y') ? 0.12 : 0),
         ((Fs[10] == 'Y') ? 0.12 : 0), ((Fs[11] == 'Y') ? 0.12 : 0)),             /* Background fraction */
      ListToVector(12, ((Fs[0] == 'Y') ? 0.5 : 0), ((Fs[1] == 'Y') ? 0.5 : 0),
         ((Fs[2] == 'Y') ? 0.5 : 0), ((Fs[3] == 'Y') ? 0.5 : 0),
         ((Fs[4] == 'Y') ? 0.15 : 0), ((Fs[5] == 'Y') ? 0.25 : 0),
         ((Fs[6] == 'Y') ? 0.25 : 0), ((Fs[7] == 'Y') ? 0.15 : 0),
         ((Fs[8] == 'Y') ? 0.12 : 0), ((Fs[9] == 'Y') ? 0.12 : 0),
         ((Fs[10] == 'Y') ? 0.12 : 0), ((Fs[11] == 'Y') ? 0.12 : 0)),             /* Background fraction */
      ListToVector(7, 0, 0, 0, 0, 0, 0, 0),                                       /* Systematics */
      NS7Prime, NS8Prime, NSSigma7, NSSigma8,
      NB7Prime, NB8Prime, NBSigma7, NBSigma8,
      NZJ7Prime, NZJ8Prime, NZJSigma7, NZJSigma8,
      NggZZ7Prime, NggZZ8Prime, NggZZSigma7, NggZZSigma8,                         /* Constraints */
      1);                                                                        /* Mu */

   cout << "\nFit Configuration Summary\n";
   cout << "Model Parameters Floated : " << As << "\n";
   cout << "Model Complex Phases Floated : " << Phases << "\n";
   cout << "\n\n";

   TFile OutputFile("LikelihoodFile.root", "RECREATE");

   vector<SingleEvent> Events;
   
   Fits.SignalStateCount[1][0]      = PullEvents(Events, SignalEM[1],     NS7[0],    NSSigma7[0],    false);
   Fits.SignalStateCount[1][0]     += PullEvents(Events, SignalEM[1],     NS7[1],    NSSigma7[1],    false);
   Fits.SignalStateCount[1][1]      = 0;
   Fits.SignalStateCount[1][2]      = PullEvents(Events, SignalEE[1],     NS7[2],    NSSigma7[2],    false);
   Fits.SignalStateCount[1][3]      = PullEvents(Events, SignalMM[1],     NS7[3],    NSSigma7[3],    false);
   Fits.SignalStateCount[0][0]      = PullEvents(Events, SignalEM[0],     NS8[0],    NSSigma8[0],    false);
   Fits.SignalStateCount[0][0]     += PullEvents(Events, SignalEM[0],     NS8[1],    NSSigma8[1],    false);
   Fits.SignalStateCount[0][1]      = 0;
   Fits.SignalStateCount[0][2]      = PullEvents(Events, SignalEE[0],     NS8[2],    NSSigma8[2],    false);
   Fits.SignalStateCount[0][3]      = PullEvents(Events, SignalMM[0],     NS8[3],    NSSigma8[3],    false);
   Fits.BackgroundStateCount[1][0]  = PullEvents(Events, BackgroundEM[1], NB7[0],    NBSigma7[0],    false);
   Fits.BackgroundStateCount[1][0] += PullEvents(Events, BackgroundEM[1], NB7[1],    NBSigma7[1],    false);
   Fits.BackgroundStateCount[1][1]  = 0;
   Fits.BackgroundStateCount[1][2]  = PullEvents(Events, BackgroundEE[1], NB7[2],    NBSigma7[2],    false);
   Fits.BackgroundStateCount[1][3]  = PullEvents(Events, BackgroundMM[1], NB7[3],    NBSigma7[3],    false);
   Fits.BackgroundStateCount[0][0]  = PullEvents(Events, BackgroundEM[0], NB8[0],    NBSigma8[0],    false);
   Fits.BackgroundStateCount[0][0] += PullEvents(Events, BackgroundEM[0], NB8[1],    NBSigma8[1],    false);
   Fits.BackgroundStateCount[0][1]  = 0;
   Fits.BackgroundStateCount[0][2]  = PullEvents(Events, BackgroundEE[0], NB8[2],    NBSigma8[2],    false);
   Fits.BackgroundStateCount[0][3]  = PullEvents(Events, BackgroundMM[0], NB8[3],    NBSigma8[3],    false);
   Fits.ZJStateCount[1][0]          = PullEvents(Events, ZJEM[1],         NZJ7[0],   NZJSigma7[0],   true);
   Fits.ZJStateCount[1][0]         += PullEvents(Events, ZJEM[1],         NZJ7[1],   NZJSigma7[1],   true);
   Fits.ZJStateCount[1][1]          = 0;
   Fits.ZJStateCount[1][2]          = PullEvents(Events, ZJEE[1],         NZJ7[2],   NZJSigma7[2],   true);
   Fits.ZJStateCount[1][3]          = PullEvents(Events, ZJMM[1],         NZJ7[3],   NZJSigma7[3],   true);
   Fits.ZJStateCount[0][0]          = PullEvents(Events, ZJEM[0],         NZJ8[0],   NZJSigma8[0],   true);
   Fits.ZJStateCount[0][0]         += PullEvents(Events, ZJEM[0],         NZJ8[1],   NZJSigma8[1],   true);
   Fits.ZJStateCount[0][1]          = 0;
   Fits.ZJStateCount[0][2]          = PullEvents(Events, ZJEE[0],         NZJ8[2],   NZJSigma8[2],   true);
   Fits.ZJStateCount[0][3]          = PullEvents(Events, ZJMM[0],         NZJ8[3],   NZJSigma8[3],   true);
   Fits.ggZZStateCount[1][0]        = PullEvents(Events, ggZZEM[1],       NggZZ7[0], NggZZSigma7[0], true);
   Fits.ggZZStateCount[1][0]       += PullEvents(Events, ggZZEM[1],       NggZZ7[1], NggZZSigma7[1], true);
   Fits.ggZZStateCount[1][1]        = 0;
   Fits.ggZZStateCount[1][2]        = PullEvents(Events, ggZZEE[1],       NggZZ7[2], NggZZSigma7[2], true);
   Fits.ggZZStateCount[1][3]        = PullEvents(Events, ggZZMM[1],       NggZZ7[3], NggZZSigma7[3], true);
   Fits.ggZZStateCount[0][0]        = PullEvents(Events, ggZZEM[0],       NggZZ8[0], NggZZSigma8[0], true);
   Fits.ggZZStateCount[0][0]       += PullEvents(Events, ggZZEM[0],       NggZZ8[1], NggZZSigma8[1], true);
   Fits.ggZZStateCount[0][1]        = 0;
   Fits.ggZZStateCount[0][2]        = PullEvents(Events, ggZZEE[0],       NggZZ8[2], NggZZSigma8[2], true);
   Fits.ggZZStateCount[0][3]        = PullEvents(Events, ggZZMM[0],       NggZZ8[3], NggZZSigma8[3], true);

   cout << "S8 = " << Fits.SignalStateCount[0][0] << " " << Fits.SignalStateCount[0][1]
      << " " << Fits.SignalStateCount[0][2] << " " << Fits.SignalStateCount[0][3] << endl;
   cout << "B8 = " << Fits.BackgroundStateCount[0][0] << " " << Fits.BackgroundStateCount[0][1]
      << " " << Fits.BackgroundStateCount[0][2] << " " << Fits.BackgroundStateCount[0][3] << endl;
   cout << "Z8 = " << Fits.ZJStateCount[0][0] << " " << Fits.ZJStateCount[0][1]
      << " " << Fits.ZJStateCount[0][2] << " " << Fits.ZJStateCount[0][3] << endl;
   cout << "G8 = " << Fits.ggZZStateCount[0][0] << " " << Fits.ggZZStateCount[0][1]
      << " " << Fits.ggZZStateCount[0][2] << " " << Fits.ggZZStateCount[0][3] << endl;
   cout << "S7 = " << Fits.SignalStateCount[1][0] << " " << Fits.SignalStateCount[1][1]
      << " " << Fits.SignalStateCount[1][2] << " " << Fits.SignalStateCount[1][3] << endl;
   cout << "B7 = " << Fits.BackgroundStateCount[1][0] << " " << Fits.BackgroundStateCount[1][1]
      << " " << Fits.BackgroundStateCount[1][2] << " " << Fits.BackgroundStateCount[1][3] << endl;
   cout << "Z7 = " << Fits.ZJStateCount[1][0] << " " << Fits.ZJStateCount[1][1]
      << " " << Fits.ZJStateCount[1][2] << " " << Fits.ZJStateCount[1][3] << endl;
   cout << "G7 = " << Fits.ggZZStateCount[1][0] << " " << Fits.ggZZStateCount[1][1]
      << " " << Fits.ggZZStateCount[1][2] << " " << Fits.ggZZStateCount[1][3] << endl;

   for(int i = 0; i < (int)Events.size(); i++)
      Fits.AddPoint(Events[i]);

   /*
   double TrueParameters[56] = {0};
   TrueParameters[0] = Configuration.AAInitialValue[0];
   TrueParameters[1] = Configuration.PhaseInitialValue[0];
   TrueParameters[2] = Configuration.AAInitialValue[1];
   TrueParameters[3] = Configuration.PhaseInitialValue[1];
   TrueParameters[4] = Configuration.AAInitialValue[2];
   TrueParameters[5] = Configuration.PhaseInitialValue[2];
   TrueParameters[6] = Configuration.AAInitialValue[3];
   TrueParameters[7] = Configuration.PhaseInitialValue[3];
   TrueParameters[8] = Configuration.AAInitialValue[4];
   TrueParameters[9] = Configuration.PhaseInitialValue[4];
   TrueParameters[10] = Configuration.AAInitialValue[5];
   TrueParameters[11] = Configuration.PhaseInitialValue[5];
   TrueParameters[12] = Configuration.AAInitialValue[6];
   TrueParameters[13] = Configuration.PhaseInitialValue[6];
   TrueParameters[14] = Configuration.AAInitialValue[7];
   TrueParameters[15] = Configuration.PhaseInitialValue[7];
   TrueParameters[16] = Fits.SignalStateCount[0][0] + Fits.BackgroundStateCount[0][0] + Fits.ZJStateCount[0][0] + Fits.ggZZStateCount[0][0];
   TrueParameters[17] = Fits.SignalStateCount[0][1] + Fits.BackgroundStateCount[0][1] + Fits.ZJStateCount[0][1] + Fits.ggZZStateCount[0][1];
   TrueParameters[18] = Fits.SignalStateCount[0][2] + Fits.BackgroundStateCount[0][2] + Fits.ZJStateCount[0][2] + Fits.ggZZStateCount[0][2];
   TrueParameters[19] = Fits.SignalStateCount[0][3] + Fits.BackgroundStateCount[0][3] + Fits.ZJStateCount[0][3] + Fits.ggZZStateCount[0][3];
   TrueParameters[20] = Fits.SignalStateCount[1][0] + Fits.BackgroundStateCount[1][0] + Fits.ZJStateCount[1][0] + Fits.ggZZStateCount[1][0];
   TrueParameters[21] = Fits.SignalStateCount[1][1] + Fits.BackgroundStateCount[1][1] + Fits.ZJStateCount[1][1] + Fits.ggZZStateCount[1][1];
   TrueParameters[22] = Fits.SignalStateCount[1][2] + Fits.BackgroundStateCount[1][2] + Fits.ZJStateCount[1][2] + Fits.ggZZStateCount[1][2];
   TrueParameters[23] = Fits.SignalStateCount[1][3] + Fits.BackgroundStateCount[1][3] + Fits.ZJStateCount[1][3] + Fits.ggZZStateCount[1][3];
   TrueParameters[24] = ((TrueParameters[16] > 0) ? (Fits.BackgroundStateCount[0][0] / TrueParameters[16]) : 0);
   TrueParameters[25] = ((TrueParameters[17] > 0) ? (Fits.BackgroundStateCount[0][1] / TrueParameters[17]) : 0);
   TrueParameters[26] = ((TrueParameters[18] > 0) ? (Fits.BackgroundStateCount[0][2] / TrueParameters[18]) : 0);
   TrueParameters[27] = ((TrueParameters[19] > 0) ? (Fits.BackgroundStateCount[0][3] / TrueParameters[19]) : 0);
   TrueParameters[28] = ((TrueParameters[20] > 0) ? (Fits.BackgroundStateCount[1][0] / TrueParameters[20]) : 0);
   TrueParameters[29] = ((TrueParameters[21] > 0) ? (Fits.BackgroundStateCount[1][1] / TrueParameters[21]) : 0);
   TrueParameters[30] = ((TrueParameters[22] > 0) ? (Fits.BackgroundStateCount[1][2] / TrueParameters[22]) : 0);
   TrueParameters[31] = ((TrueParameters[23] > 0) ? (Fits.BackgroundStateCount[1][3] / TrueParameters[23]) : 0);
   TrueParameters[32] = ((TrueParameters[16] > 0) ? (Fits.ZJStateCount[0][0] / TrueParameters[16]) : 0);
   TrueParameters[33] = ((TrueParameters[17] > 0) ? (Fits.ZJStateCount[0][1] / TrueParameters[17]) : 0);
   TrueParameters[34] = ((TrueParameters[18] > 0) ? (Fits.ZJStateCount[0][2] / TrueParameters[18]) : 0);
   TrueParameters[35] = ((TrueParameters[19] > 0) ? (Fits.ZJStateCount[0][3] / TrueParameters[19]) : 0);
   TrueParameters[36] = ((TrueParameters[20] > 0) ? (Fits.ZJStateCount[1][0] / TrueParameters[20]) : 0);
   TrueParameters[37] = ((TrueParameters[21] > 0) ? (Fits.ZJStateCount[1][1] / TrueParameters[21]) : 0);
   TrueParameters[38] = ((TrueParameters[22] > 0) ? (Fits.ZJStateCount[1][2] / TrueParameters[22]) : 0);
   TrueParameters[39] = ((TrueParameters[23] > 0) ? (Fits.ZJStateCount[1][3] / TrueParameters[23]) : 0);
   TrueParameters[40] = ((TrueParameters[16] > 0) ? (Fits.ggZZStateCount[0][0] / TrueParameters[16]) : 0);
   TrueParameters[41] = ((TrueParameters[17] > 0) ? (Fits.ggZZStateCount[0][1] / TrueParameters[17]) : 0);
   TrueParameters[42] = ((TrueParameters[18] > 0) ? (Fits.ggZZStateCount[0][2] / TrueParameters[18]) : 0);
   TrueParameters[43] = ((TrueParameters[19] > 0) ? (Fits.ggZZStateCount[0][3] / TrueParameters[19]) : 0);
   TrueParameters[44] = ((TrueParameters[20] > 0) ? (Fits.ggZZStateCount[1][0] / TrueParameters[20]) : 0);
   TrueParameters[45] = ((TrueParameters[21] > 0) ? (Fits.ggZZStateCount[1][1] / TrueParameters[21]) : 0);
   TrueParameters[46] = ((TrueParameters[22] > 0) ? (Fits.ggZZStateCount[1][2] / TrueParameters[22]) : 0);
   TrueParameters[47] = ((TrueParameters[23] > 0) ? (Fits.ggZZStateCount[1][3] / TrueParameters[23]) : 0);
   TrueParameters[48] = 0;
   TrueParameters[49] = 0;
   TrueParameters[50] = 0;
   TrueParameters[51] = 0;
   TrueParameters[52] = 0;
   TrueParameters[53] = 0;
   TrueParameters[54] = 0;
   TrueParameters[55] = 1;
   */

   for(int i = 0; i < 5; i++)
     ResultTemp[i] = Fits.DoFit(Configuration);
   
   int Best = 0;
   for(int i = 0; i < 5; i++)
      if(ResultTemp[i].BestNLL < ResultTemp[Best].BestNLL)
         Best = i;
   Results.push_back(ResultTemp[Best]);

   Fits.ClearPoints();

   PsFile.AddTimeStampPage();
   PsFile.Close();

   string BranchList = "";
   BranchList = BranchList + "A2ZZA1ZZ:A2ZZPhase:A3ZZA1ZZ:A3ZZPhase";                          // 4
   BranchList = BranchList + ":A2ZAA1ZZ:A2ZAPhase:A3ZAA1ZZ:A3ZAPhase";                         // 8
   BranchList = BranchList + ":A2AAA1ZZ:A2AAPhase:A3AAA1ZZ:A3AAPhase";                         // 12
   BranchList = BranchList + ":N1:N2:N3:N4:N5:N6:N7";                                          // 19
   BranchList = BranchList + ":Fem7:Fme7:Fee7:Fmm7";                                           // 23
   BranchList = BranchList + ":Fem8:Fme8:Fee8:Fmm8";                                           // 27
   BranchList = BranchList + ":FZJem7:FZJme7:FZJee7:FZJmm7";                                   // 31
   BranchList = BranchList + ":FZJem8:FZJme8:FZJee8:FZJmm8";                                   // 35
   BranchList = BranchList + ":FggZZem7:FggZZme7:FggZZee7:FggZZmm7";                           // 39
   BranchList = BranchList + ":FggZZem8:FggZZme8:FggZZee8:FggZZmm8";                           // 43
   BranchList = BranchList + ":A2ZZA1ZZError:A2ZZPhaseError:A3ZZA1ZZError:A3ZZPhaseError";     // 47
   BranchList = BranchList + ":A2ZAA1ZZError:A2ZAPhaseError:A3ZAA1ZZError:A3ZAPhaseError";     // 51
   BranchList = BranchList + ":A2AAA1ZZError:A2AAPhaseError:A3AAA1ZZError:A3AAPhaseError";     // 55
   BranchList = BranchList + ":N1Error:N2Error:N3Error:N4Error:N5Error:N6Error:N7Error";       // 62
   BranchList = BranchList + ":FemError7:FmeError7:FeeError7:FmmError7";                       // 66
   BranchList = BranchList + ":FemError8:FmeError8:FeeError8:FmmError8";                       // 70
   BranchList = BranchList + ":FZJemError7:FZJmeError7:FZJeeError7:FZJmmError7";               // 74
   BranchList = BranchList + ":FZJemError8:FZJmeError8:FZJeeError8:FZJmmError8";               // 78
   BranchList = BranchList + ":FggZZemError7:FggZZmeError7:FggZZeeError7:FggZZmmError7";       // 82
   BranchList = BranchList + ":FggZZemError8:FggZZmeError8:FggZZeeError8:FggZZmmError8";       // 86
   BranchList = BranchList + ":EDM:Status";                                                    // 88
   BranchList = BranchList + ":Sem7:Sme7:See7:Smm7";                                           // 92
   BranchList = BranchList + ":Sem8:Sme8:See8:Smm8";                                           // 96
   BranchList = BranchList + ":Bem7:Bme7:Bee7:Bmm7";                                           // 100
   BranchList = BranchList + ":Bem8:Bme8:Bee8:Bmm8";                                           // 104
   BranchList = BranchList + ":ZJem7:ZJme7:ZJee7:ZJmm7";                                       // 108
   BranchList = BranchList + ":ZJem8:ZJme8:ZJee8:ZJmm8";                                       // 112
   BranchList = BranchList + ":ggZZem7:ggZZme7:ggZZee7:ggZZmm7";                               // 116
   BranchList = BranchList + ":ggZZem8:ggZZme8:ggZZee8:ggZZmm8";                               // 120
   BranchList = BranchList + ":RatioFloats:NFloats:TruthNLL:BestNLL";                          // 124
   BranchList = BranchList + ":Mu:MuError";                                                    // 126
   BranchList = BranchList + ":A1L1ZZ:A1L1ZZPhase:A1LQZZ:A1LQZZPhase";                         // 130
   BranchList = BranchList + ":A1L1ZZError:A1L1ZZPhaseError:A1LQZZError:A1LQZZPhaseError";     // 134
   BranchList = BranchList + ":Toy:Good";                                                      // 136
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[150];
      Array[0]   = Results[i].AA[0];          Array[43]  = Results[i].AAError[0];
      Array[1]   = Results[i].Phase[0];       Array[44]  = Results[i].PhaseError[0];
      Array[2]   = Results[i].AA[1];          Array[45]  = Results[i].AAError[1];
      Array[3]   = Results[i].Phase[1];       Array[46]  = Results[i].PhaseError[1];
      Array[4]   = Results[i].AA[2];          Array[47]  = Results[i].AAError[2];
      Array[5]   = Results[i].Phase[2];       Array[48]  = Results[i].PhaseError[2];
      Array[6]   = Results[i].AA[3];          Array[49]  = Results[i].AAError[3];
      Array[7]   = Results[i].Phase[3];       Array[50]  = Results[i].PhaseError[3];
      Array[8]   = Results[i].AA[4];          Array[51]  = Results[i].AAError[4];
      Array[9]   = Results[i].Phase[4];       Array[52]  = Results[i].PhaseError[4];
      Array[10]  = Results[i].AA[5];          Array[53]  = Results[i].AAError[5];
      Array[11]  = Results[i].Phase[5];       Array[54]  = Results[i].PhaseError[5];
      Array[12]  = Results[i].N[0];           Array[55]  = Results[i].NError[0];
      Array[13]  = Results[i].N[1];           Array[56]  = Results[i].NError[1];
      Array[14]  = Results[i].N[2];           Array[57]  = Results[i].NError[2];
      Array[15]  = Results[i].N[3];           Array[58]  = Results[i].NError[3];
      Array[16]  = Results[i].N[4];           Array[59]  = Results[i].NError[4];
      Array[17]  = Results[i].N[5];           Array[60]  = Results[i].NError[5];
      Array[18]  = Results[i].N[6];           Array[61]  = Results[i].NError[6];
      Array[19]  = Results[i].F[1][0];        Array[62]  = Results[i].FError[1][0];
      Array[20]  = Results[i].F[1][1];        Array[63]  = Results[i].FError[1][1];
      Array[21]  = Results[i].F[1][2];        Array[64]  = Results[i].FError[1][2];
      Array[22]  = Results[i].F[1][3];        Array[65]  = Results[i].FError[1][3];
      Array[23]  = Results[i].F[0][0];        Array[66]  = Results[i].FError[0][0];
      Array[24]  = Results[i].F[0][1];        Array[67]  = Results[i].FError[0][1];
      Array[25]  = Results[i].F[0][2];        Array[68]  = Results[i].FError[0][2];
      Array[26]  = Results[i].F[0][3];        Array[69]  = Results[i].FError[0][3];
      Array[27]  = Results[i].FZJ[1][0];      Array[70]  = Results[i].FZJError[1][0];
      Array[28]  = Results[i].FZJ[1][1];      Array[71]  = Results[i].FZJError[1][1];
      Array[29]  = Results[i].FZJ[1][2];      Array[72]  = Results[i].FZJError[1][2];
      Array[30]  = Results[i].FZJ[1][3];      Array[73]  = Results[i].FZJError[1][3];
      Array[31]  = Results[i].FZJ[0][0];      Array[74]  = Results[i].FZJError[0][0];
      Array[32]  = Results[i].FZJ[0][1];      Array[75]  = Results[i].FZJError[0][1];
      Array[33]  = Results[i].FZJ[0][2];      Array[76]  = Results[i].FZJError[0][2];
      Array[34]  = Results[i].FZJ[0][3];      Array[77]  = Results[i].FZJError[0][3];
      Array[35]  = Results[i].FggZZ[1][0];    Array[78]  = Results[i].FggZZError[1][0];
      Array[36]  = Results[i].FggZZ[1][1];    Array[79]  = Results[i].FggZZError[1][1];
      Array[37]  = Results[i].FggZZ[1][2];    Array[80]  = Results[i].FggZZError[1][2];
      Array[38]  = Results[i].FggZZ[1][3];    Array[81]  = Results[i].FggZZError[1][3];
      Array[39]  = Results[i].FggZZ[0][0];    Array[82]  = Results[i].FggZZError[0][0];
      Array[40]  = Results[i].FggZZ[0][1];    Array[83]  = Results[i].FggZZError[0][1];
      Array[41]  = Results[i].FggZZ[0][2];    Array[84]  = Results[i].FggZZError[0][2];
      Array[42]  = Results[i].FggZZ[0][3];    Array[85]  = Results[i].FggZZError[0][3];

      Array[86]  = Results[i].EDM;
      Array[87]  = Results[i].FitStatus;

      Array[88]  = Results[i].S[1][0];        Array[92]  = Results[i].S[0][0];
      Array[89]  = Results[i].S[1][1];        Array[93]  = Results[i].S[0][1];
      Array[90]  = Results[i].S[1][2];        Array[94]  = Results[i].S[0][2];
      Array[91]  = Results[i].S[1][3];        Array[95]  = Results[i].S[0][3];

      Array[96]  = Results[i].B[1][0];        Array[100] = Results[i].B[0][0];
      Array[97]  = Results[i].B[1][1];        Array[101] = Results[i].B[0][1];
      Array[98]  = Results[i].B[1][2];        Array[102] = Results[i].B[0][2];
      Array[99]  = Results[i].B[1][3];        Array[103] = Results[i].B[0][3];

      Array[104] = Results[i].ZJ[1][0];       Array[108] = Results[i].ZJ[0][0];
      Array[105] = Results[i].ZJ[1][1];       Array[109] = Results[i].ZJ[0][1];
      Array[106] = Results[i].ZJ[1][2];       Array[110] = Results[i].ZJ[0][2];
      Array[107] = Results[i].ZJ[1][3];       Array[111] = Results[i].ZJ[0][3];

      Array[112] = Results[i].ggZZ[1][0];     Array[116] = Results[i].ggZZ[0][0];
      Array[113] = Results[i].ggZZ[1][1];     Array[117] = Results[i].ggZZ[0][1];
      Array[114] = Results[i].ggZZ[1][2];     Array[118] = Results[i].ggZZ[0][2];
      Array[115] = Results[i].ggZZ[1][3];     Array[119] = Results[i].ggZZ[0][3];

      Array[120] = 0;
      Array[121] = 0;

      Array[122] = Results[i].TruthNLL;
      Array[123] = Results[i].BestNLL;

      Array[124] = Results[i].Mu;
      Array[125] = Results[i].MuError;

      Array[126] = Results[i].AA[6];          Array[130] = Results[i].AAError[6];
      Array[127] = Results[i].Phase[6];       Array[131] = Results[i].PhaseError[6];
      Array[128] = Results[i].AA[7];          Array[132] = Results[i].AAError[7];
      Array[129] = Results[i].Phase[7];       Array[133] = Results[i].PhaseError[7];

      Array[134] = TargetToyNumber;
      Array[135] = !AnyHasBadEvent;

      OutputTree.Fill(Array);
   }

   SetAlias(OutputTree);

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}
//---------------------------------------------------------------------------
bool ReadEvents(vector<SingleEvent> &EventsEM, vector<SingleEvent> &EventsME,
      vector<SingleEvent> &EventsEE, vector<SingleEvent> &EventsMM,
      string FileName, int Process,
      double MaxWeight, bool Is7TeV, int TargetToyNumber)
{
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("zz4lTree");
   if(Tree == NULL)
      return true;

   DataHelper DHFile("CombinedNormalization.dh");

   int l1id, l3id;
   Tree->SetBranchAddress("l1id", &l1id);
   Tree->SetBranchAddress("l3id", &l3id);

   string SignalBranch[] = {"T1", "T3", "T5", "T7", "T9", "T11", "T13", "T15", "T17", "T21", "T22", "T23", "T24"};
   string BackgroundBranch[] = {"T2Total", "T4Total", "T6Total", "T8Total", "T10Total", "T12Total", "T14Total", "T16Total", "T18Total",
      "T2Total", "T2Total", "T2Total", "T2Total"};

   double Value[154][13] = {{0}};
   double Integral[154][13] = {{0}};
   float Value2[2][13] = {{0}};
   double Integral2[2][13] = {{0}};

   vector<string> Suffix = GetHLLSignalSuffixList();

   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &Value[i+1][0]);
   Tree->SetBranchAddress("B2", &Value[0][0]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B3_%s", Suffix[i].c_str()), &Value[i+1][1]);
   Tree->SetBranchAddress("B4", &Value[0][1]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B5_%s", Suffix[i].c_str()), &Value[i+1][2]);
   Tree->SetBranchAddress("B6", &Value[0][2]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B7_%s", Suffix[i].c_str()), &Value[i+1][3]);
   Tree->SetBranchAddress("B8", &Value[0][3]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B9_%s", Suffix[i].c_str()), &Value[i+1][4]);
   Tree->SetBranchAddress("B10", &Value[0][4]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B11_%s", Suffix[i].c_str()), &Value[i+1][5]);
   Tree->SetBranchAddress("B12", &Value[0][5]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B13_%s", Suffix[i].c_str()), &Value[i+1][6]);
   Tree->SetBranchAddress("B14", &Value[0][6]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B15_%s", Suffix[i].c_str()), &Value[i+1][7]);
   Tree->SetBranchAddress("B16", &Value[0][7]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B17_%s", Suffix[i].c_str()), &Value[i+1][8]);
   Tree->SetBranchAddress("B18", &Value[0][8]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B21_%s", Suffix[i].c_str()), &Value[i+1][9]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B22_%s", Suffix[i].c_str()), &Value[i+1][10]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B23_%s", Suffix[i].c_str()), &Value[i+1][11]);
   for(int i = 0; i < 153; i++)
      Tree->SetBranchAddress(Form("B24_%s", Suffix[i].c_str()), &Value[i+1][12]);

   Tree->SetBranchAddress("B19", &Value2[0][0]);
   Tree->SetBranchAddress("B20", &Value2[1][0]);

   float weight = 1;
   Tree->SetBranchAddress("weight", &weight);

   float z1mass, z2mass, zzmass;
   Tree->SetBranchAddress("z1mass", &z1mass);
   Tree->SetBranchAddress("z2mass", &z2mass);
   Tree->SetBranchAddress("zzmass", &zzmass);

   int process, channel;
   unsigned int toy;
   Tree->SetBranchAddress("process", &process);
   Tree->SetBranchAddress("channel", &channel);
   Tree->SetBranchAddress("toy", &toy);

   bool HasBadEvent = false;

   int EntryCount = Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(0);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      process = DEFAULT_PROCESS;
      channel = -1;

      Tree->GetEntry(iE);

      if(Process != DEFAULT_PROCESS && Process != process)
         continue;

      if(channel == 0)        l1id = 13, l3id = 13;
      else if(channel == 1)   l1id = 11, l3id = 11;
      else if(channel == 2)   l1id = 11, l3id = 13;
      else if(channel == 3)   l1id = 13, l3id = 11;

      if(EntryCount < 1000 || (iE % (EntryCount / 1000) == 0))
      {
         Bar.Update(iE);
         Bar.Print();
      }

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      if(l1id == 11 && l3id == 11 && EventsEE.size() > EVENTLIMIT)   continue;
      if(l1id == 13 && l3id == 11 && EventsME.size() > EVENTLIMIT)   continue;
      if(l1id == 11 && l3id == 13 && EventsEM.size() > EVENTLIMIT)   continue;
      if(l1id == 13 && l3id == 13 && EventsMM.size() > EVENTLIMIT)   continue;

      if(EventsEE.size() > EVENTLIMIT && EventsME.size() > EVENTLIMIT
            && EventsEM.size() > EVENTLIMIT && EventsMM.size() > EVENTLIMIT)
         break;

      if(zzmass > 135 || zzmass < 115)
         continue;
      if(max(z1mass, z2mass) < 40)
         continue;
      if(min(z1mass, z2mass) < 12)
         continue;

      string State = "";
      if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      if(l1id == 13 && l3id == 11)   State = "me";
      if(l1id == 13 && l3id == 13)   State = "mm";

      char BranchInitial = 'T';
      if(State == "em")   BranchInitial = 'X';
      if(State == "me")   BranchInitial = 'X';
      if(State == "ee")   BranchInitial = 'V';
      if(State == "mm")   BranchInitial = 'W';

      double ZX_S_Offset = 0, ggZZ_S_Offset = 0;
      double S = zzmass * zzmass;

      if(Is7TeV == false && State == "em")   ZX_S_Offset   = log(GetZX8TeV2e2muSpectrum(S))   - 7.05;
      if(Is7TeV == false && State == "me")   ZX_S_Offset   = log(GetZX8TeV2mu2eSpectrum(S))   - 6.60;
      if(Is7TeV == false && State == "ee")   ZX_S_Offset   = log(GetZX8TeV4eSpectrum(S))      - 5.60;
      if(Is7TeV == false && State == "mm")   ZX_S_Offset   = log(GetZX8TeV4muSpectrum(S))     - 5.40;
      if(Is7TeV == true  && State == "em")   ZX_S_Offset   = log(GetZX7TeV2e2muSpectrum(S))   - 6.95;
      if(Is7TeV == true  && State == "me")   ZX_S_Offset   = log(GetZX7TeV2mu2eSpectrum(S))   - 6.60;
      if(Is7TeV == true  && State == "ee")   ZX_S_Offset   = log(GetZX7TeV4eSpectrum(S))      - 5.40;
      if(Is7TeV == true  && State == "mm")   ZX_S_Offset   = log(GetZX7TeV4muSpectrum(S))     - 5.80;

      if(Is7TeV == false && State == "em")   ggZZ_S_Offset = log(GetggZZ8TeV2e2muSpectrum(S)) - 7.05;
      if(Is7TeV == false && State == "me")   ggZZ_S_Offset = log(GetggZZ8TeV2mu2eSpectrum(S)) - 6.60;
      if(Is7TeV == false && State == "ee")   ggZZ_S_Offset = log(GetggZZ8TeV4eSpectrum(S))    - 5.60;
      if(Is7TeV == false && State == "mm")   ggZZ_S_Offset = log(GetggZZ8TeV4muSpectrum(S))   - 5.40;
      if(Is7TeV == true  && State == "em")   ggZZ_S_Offset = log(GetggZZ8TeV2e2muSpectrum(S)) - 6.95;
      if(Is7TeV == true  && State == "me")   ggZZ_S_Offset = log(GetggZZ8TeV2mu2eSpectrum(S)) - 6.60;
      if(Is7TeV == true  && State == "ee")   ggZZ_S_Offset = log(GetggZZ8TeV4eSpectrum(S))    - 5.40;
      if(Is7TeV == true  && State == "mm")   ggZZ_S_Offset = log(GetggZZ8TeV4muSpectrum(S))   - 5.80;

      string DHState = State;
      if(State == "em" || State == "me")
         DHState = "emme";
      if(Is7TeV == true)
         DHState = DHState + "7TeV";
      else
         DHState = DHState + "8TeV";

      if(State == "")   // WTF
         continue;
      else
      {
         for(int j = 0; j < 13; j++)
         {
            BackgroundBranch[j][0] = BranchInitial;

            Integral[0][j] = DHFile[DHState][BackgroundBranch[j]].GetDouble() / 2;
            if(Is7TeV == false && State == "em")   Integral[0][j] /= 1.18;
            if(Is7TeV == false && State == "me")   Integral[0][j] /= 1.18;
            if(Is7TeV == false && State == "ee")   Integral[0][j] /= 1.28;
            if(Is7TeV == false && State == "mm")   Integral[0][j] /= 1.15;
            if(Is7TeV == true  && State == "em")   Integral[0][j] /= 1.18;
            if(Is7TeV == true  && State == "me")   Integral[0][j] /= 1.18;
            if(Is7TeV == true  && State == "ee")   Integral[0][j] /= 1.20;
            if(Is7TeV == true  && State == "mm")   Integral[0][j] /= 1.20;

            for(int i = 1; i < 154; i++)
            {
               SignalBranch[j][0] = BranchInitial;

               char BranchSuffix[200] = "";
               sprintf(BranchSuffix, "_%03d", i);
               string Branch = SignalBranch[j] + BranchSuffix;
               Integral[i][j] = DHFile[DHState][Branch].GetDouble();
            }
         }

         string ZXBranch = "X19";
         ZXBranch[0] = BranchInitial;
         Integral2[0][0] = DHFile[DHState][ZXBranch].GetDouble();

         // Use the same one for ggZZ for now
         Integral2[1][0] = DHFile[DHState][ZXBranch].GetDouble();
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

      for(int j = 1; j <= 12; j++)   // For now!  Disable some systematics!
      {
         for(int i = 0; i < 154; i++)
         {
            Value[i][j] = Value[i][0];
            Integral[i][j] = Integral[i][0];
         }
      }

      for(int j = 0; j < 13; j++)   // MH Spectrum for Z+X and ggZZ
      {
         Value2[0][j] = Value2[0][j] + ZX_S_Offset;
         Value2[1][j] = Value2[1][j] + ggZZ_S_Offset;
      }

      // for(int i = 0; i < 154; i++)
      //    cout << i << " " << Value[i][0] << " " << Integral[i][0] << endl;
      // for(int i = 0; i < 2; i++)
      //    cout << i << " " << Value2[i][0] << " " << Integral2[i][0] << endl;

      bool Good = true;
      for(int i = 0; i < 92; i++) {
         for(int j = 0; j < 13; j++) {
            if(Value[i][j] > 0.99 || (i < 14 && Value[i][j] < 1e-50)) {
               Good = false;
               //cout << FileName << " : Event "  << iE << " Bad L : " << i << " " << j << " : " << Value[i][j] << "\n";
            }
         }
      }

      if(Value2[0][0] > -1 || Value2[1][0] > -1) {
         //cout << "Bad L ...\n";
         Good = false;
      }
      if(Good == false) {
         //cout << "BadEvent: " << iE << "\n";
         HasBadEvent = true;
         continue;
      }

      SingleEvent NewEvent;

      for(int i = 0; i < 154; i++)
         for(int j = 0; j < 13; j++)
            NewEvent.v[i][j] = Value[i][j];
      for(int i = 0; i < 154; i++)
         for(int j = 0; j < 13; j++)
            NewEvent.i[i][j] = Integral[i][j];
      for(int i = 0; i < 2; i++)
         for(int j = 0; j < 13; j++)
            NewEvent.v2[i][j] = exp(Value2[i][j]);
      for(int i = 0; i < 2; i++)
         for(int j = 0; j < 13; j++)
            NewEvent.i2[i][j] = Integral2[i][j];
      // NewEvent.event = Event;
      NewEvent.state = State;
      NewEvent.weight = weight;
      NewEvent.ToyNumber = toy;

      if(Is7TeV == true)    NewEvent.energy = "7TeV";
      if(Is7TeV == false)   NewEvent.energy = "8TeV";

      if(State == "em")   EventsEM.push_back(NewEvent);
      if(State == "me")   EventsME.push_back(NewEvent);
      if(State == "ee")   EventsEE.push_back(NewEvent);
      if(State == "mm")   EventsMM.push_back(NewEvent);

      if(EventsEM.size() > EVENTLIMIT && EventsME.size() > EVENTLIMIT && EventsEE.size() > EVENTLIMIT && EventsMM.size() > EVENTLIMIT)
         break;
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();

   random_shuffle(EventsEM.begin(), EventsEM.end());
   random_shuffle(EventsME.begin(), EventsME.end());
   random_shuffle(EventsEE.begin(), EventsEE.end());
   random_shuffle(EventsMM.begin(), EventsMM.end());

   cout << "Events read: " << EventsEM.size()
      << ", " << EventsME.size()
      << ", " << EventsEE.size()
      << ", " << EventsMM.size()
      << endl;

   return HasBadEvent;
}
//---------------------------------------------------------------------------
int GetEventCount(double Mean, double Sigma)
{
   if(Mean == 0)
      return 0;
   return Mean;

   double LogNormalMu = log(Mean) - log(1 + Sigma * Sigma) / 2;
   double LogNormalSigma = sqrt(log(1 + Sigma * Sigma));

   double PoissonMean = DrawLogNormal(LogNormalMu, LogNormalSigma);

   return DrawPoisson(PoissonMean);
}
//---------------------------------------------------------------------------
int PullEvents(vector<SingleEvent> &Events, vector<SingleEvent> &Source, double Mean, double Sigma, bool Recycle)
{
   int EventCount = GetEventCount(Mean, Sigma);

   vector<SingleEvent> NewEvents;

   while(NewEvents.size() < EventCount && Source.size() > 0)
   {
      SingleEvent Event = Source[Source.size()-1];
      Source.pop_back();
      if(Recycle == true)
         Source.push_back(Event);

      // if(DrawRandom(0, 1) > Event.weight)
      //    continue;

      NewEvents.push_back(Event);
   }

   if(NewEvents.size() < EventCount)
      return -1;

   Events.insert(Events.end(), NewEvents.begin(), NewEvents.end());

   return EventCount;
}
//---------------------------------------------------------------------------
int PullToyEvents(vector<SingleEvent> &Events, vector<SingleEvent> &Source, int ToyNumber)
{
   int Count = 0;
   int Size = Source.size();

   for(int i = 0; i < Size; i++)
   {
      if(Source[i].ToyNumber == ToyNumber)
      {
         Events.push_back(Source[i]);
         Count = Count + 1;
      }
   }

   return Count;
}
//---------------------------------------------------------------------------
vector<double> SumVector(vector<double> &V1, vector<double> &V2)
{
   vector<double> Answer(min(V1.size(), V2.size()));
   for(int i = 0; i < (int)Answer.size(); i++)
      Answer[i] = V1[i] + V2[i];
   return Answer;
}
//---------------------------------------------------------------------------
vector<double> ScaleVector(vector<double> &V1, double Factor)
{
   vector<double> Answer(V1.size());
   for(int i = 0; i < (int)Answer.size(); i++)
      Answer[i] = V1[i] * Factor;
   return Answer;
}
//---------------------------------------------------------------------------
void SetAlias(TTree &ResultTree)
{
   for(int i1 = 0; i1 < 2; i1++)
   {
      for(int i2 = 0; i2 < 2; i2++)
      {
         for(int i3 = 0; i3 < 2; i3++)
         {
            for(int i4 = 0; i4 < 2; i4++)
            {
               for(int i5 = 0; i5 < 2; i5++)
               {
                  for(int i6 = 0; i6 < 2; i6++)
                  {
                     string S1 = "NNNNNN";
                     if(i1 == 1)   S1[0] = 'Y';
                     if(i2 == 1)   S1[1] = 'Y';
                     if(i3 == 1)   S1[2] = 'Y';
                     if(i4 == 1)   S1[3] = 'Y';
                     if(i5 == 1)   S1[4] = 'Y';
                     if(i6 == 1)   S1[5] = 'Y';

                     string S2 = "(";
                     if(i1 == 1)   S2 = S2 + "A2ZZA1ZZError > 0";
                     else          S2 = S2 + "A2ZZA1ZZError == 0";
                     if(i2 == 1)   S2 = S2 + " && A3ZZA1ZZError > 0";
                     else          S2 = S2 + " && A3ZZA1ZZError == 0";
                     if(i3 == 1)   S2 = S2 + " && A2ZAA1ZZError > 0";
                     else          S2 = S2 + " && A2ZAA1ZZError == 0";
                     if(i4 == 1)   S2 = S2 + " && A3ZAA1ZZError > 0";
                     else          S2 = S2 + " && A3ZAA1ZZError == 0";
                     if(i5 == 1)   S2 = S2 + " && A2AAA1ZZError > 0";
                     else          S2 = S2 + " && A2AAA1ZZError == 0";
                     if(i6 == 1)   S2 = S2 + " && A3AAA1ZZError > 0";
                     else          S2 = S2 + " && A3AAA1ZZError == 0";
                     S2 = S2 + ")";

                     ResultTree.SetAlias(S1.c_str(), S2.c_str());
                  }
               }
            }
         }
      }
   }

   ResultTree.SetAlias("A2ZZ", "A2ZZA1ZZ");
   ResultTree.SetAlias("A3ZZ", "A3ZZA1ZZ");
   ResultTree.SetAlias("A2ZA", "A2ZAA1ZZ");
   ResultTree.SetAlias("A3ZA", "A3ZAA1ZZ");
   ResultTree.SetAlias("A2AA", "A2AAA1ZZ");
   ResultTree.SetAlias("A3AA", "A3AAA1ZZ");

   ResultTree.SetAlias("ZZ", "sqrt(A2ZZ*A2ZZ+A3ZZ*A3ZZ+1)");
   ResultTree.SetAlias("ZA", "sqrt(A2ZA*A2ZA+A3ZA*A3ZA)");
   ResultTree.SetAlias("AA", "sqrt(A2AA*A2AA+A3AA*A3AA)");

   ResultTree.SetAlias("S1", "1");
   ResultTree.SetAlias("S2", "(A2ZZ*A2ZZ/3.276/3.276)");
   ResultTree.SetAlias("S3", "(A3ZZ*A3ZZ/5.042/5.042)");

   ResultTree.SetAlias("FA1", "(1/(1+S2+S3))");
   ResultTree.SetAlias("FA2", "(-S2/(1+S2+S3)*sign(A2ZZ))");
   ResultTree.SetAlias("FA3", "(-S3/(1+S2+S3)*sign(A3ZZ))");

   ResultTree.SetAlias("eFA2", "(A2ZZ*A2ZZ/9/(1+A2ZZ*A2ZZ/9)*sign(A2ZZ))");
   ResultTree.SetAlias("eFA3", "(A3ZZ*A3ZZ/25/(1+A3ZZ*A3ZZ/25)*sign(A3ZZ))");

   ResultTree.SetAlias("Nem7", "(Sem7+Bem7+ZJem7+ggZZem7)");
   ResultTree.SetAlias("Nme7", "(Sme7+Bme7+ZJme7+ggZZme7)");
   ResultTree.SetAlias("Nee7", "(See7+Bee7+ZJee7+ggZZee7)");
   ResultTree.SetAlias("Nmm7", "(Smm7+Bmm7+ZJmm7+ggZZmm7)");
   ResultTree.SetAlias("Nem8", "(Sem8+Bem8+ZJem8+ggZZem8)");
   ResultTree.SetAlias("Nme8", "(Sme8+Bme8+ZJme8+ggZZme8)");
   ResultTree.SetAlias("Nee8", "(See8+Bee8+ZJee8+ggZZee8)");
   ResultTree.SetAlias("Nmm8", "(Smm8+Bmm8+ZJmm8+ggZZmm8)");
   ResultTree.SetAlias("NBem7", "Fem7*Nem7");
   ResultTree.SetAlias("NBme7", "Fme7*Nem7");
   ResultTree.SetAlias("NBee7", "Fee7*Nem7");
   ResultTree.SetAlias("NBmm7", "Fmm7*Nem7");
   ResultTree.SetAlias("NBem8", "Fem8*Nem8");
   ResultTree.SetAlias("NBme8", "Fme8*Nem8");
   ResultTree.SetAlias("NBee8", "Fee8*Nem8");
   ResultTree.SetAlias("NBmm8", "Fmm8*Nem8");
   ResultTree.SetAlias("NZJem7", "FZJem7*Nem7");
   ResultTree.SetAlias("NZJme7", "FZJme7*Nme7");
   ResultTree.SetAlias("NZJee7", "FZJee7*Nee7");
   ResultTree.SetAlias("NZJmm7", "FZJmm7*Nmm7");
   ResultTree.SetAlias("NZJem8", "FZJem8*Nem8");
   ResultTree.SetAlias("NZJme8", "FZJme8*Nme8");
   ResultTree.SetAlias("NZJee8", "FZJee8*Nee8");
   ResultTree.SetAlias("NZJmm8", "FZJmm8*Nmm8");
   ResultTree.SetAlias("NggZZem7", "FggZZem7*Nem7");
   ResultTree.SetAlias("NggZZme7", "FggZZme7*Nme7");
   ResultTree.SetAlias("NggZZee7", "FggZZee7*Nee7");
   ResultTree.SetAlias("NggZZmm7", "FggZZmm7*Nmm7");
   ResultTree.SetAlias("NggZZem8", "FggZZem8*Nem8");
   ResultTree.SetAlias("NggZZme8", "FggZZme8*Nme8");
   ResultTree.SetAlias("NggZZee8", "FggZZee8*Nee8");
   ResultTree.SetAlias("NggZZmm8", "FggZZmm8*Nmm8");
   ResultTree.SetAlias("NB7", "(NBem7+NBme7+NBee7+NBmm7)");
   ResultTree.SetAlias("NB8", "(NBem8+NBme8+NBee8+NBmm8)");
   ResultTree.SetAlias("NZJ7", "(NZJem7+NZJme7+NZJee7+NZJmm7)");
   ResultTree.SetAlias("NZJ8", "(NZJem8+NZJme8+NZJee8+NZJmm8)");
   ResultTree.SetAlias("NggZZ7", "(NggZZem7+NggZZme7+NggZZee+NggZZmm7)");
   ResultTree.SetAlias("NggZZ8", "(NggZZem8+NggZZme8+NggZZee+NggZZmm8)");

   ResultTree.SetAlias("A3ZZPhase1", "(A3ZZPhase+(A3ZZA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A3ZZPhase2", "(A3ZZPhase1-int(A3ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A3ZZPrimaryPhase", "(A3ZZPhase2+(A3ZZPhase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A2ZZPhase1", "(A2ZZPhase+(A2ZZA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A2ZZPhase2", "(A2ZZPhase1-int(A2ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A2ZZPrimaryPhase", "(A2ZZPhase2+(A2ZZPhase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A3ZAPhase1", "(A3ZAPhase+(A3ZAA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A3ZAPhase2", "(A3ZAPhase1-int(A3ZAPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A3ZAPrimaryPhase", "(A3ZAPhase2+(A3ZAPhase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A2ZAPhase1", "(A2ZAPhase+(A2ZAA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A2ZAPhase2", "(A2ZAPhase1-int(A2ZAPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A2ZAPrimaryPhase", "(A2ZAPhase2+(A2ZAPhase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A3AAPhase1", "(A3AAPhase+(A3AAA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A3AAPhase2", "(A3AAPhase1-int(A3AAPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A3AAPrimaryPhase", "(A3AAPhase2+(A3AAPhase2<0)*2*3.1415926535)");
   ResultTree.SetAlias("A2AAPhase1", "(A2AAPhase+(A2AAA1ZZ<0)*3.1415926535)");
   ResultTree.SetAlias("A2AAPhase2", "(A2AAPhase1-int(A2AAPhase1/(2*3.1415926535))*2*3.1415926535)");
   ResultTree.SetAlias("A2AAPrimaryPhase", "(A2AAPhase2+(A2AAPhase2<0)*2*3.1415926535)");
}
//---------------------------------------------------------------------------








