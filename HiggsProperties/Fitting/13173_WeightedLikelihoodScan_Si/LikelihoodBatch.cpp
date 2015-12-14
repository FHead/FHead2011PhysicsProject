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
//---------------------------------------------------------------------------
#include "AngleConversion.h"
#include "Lists.h"
#include "Cuts.h"
//---------------------------------------------------------------------------
#include "FileIO.h"
#include "FitClass.h"
#include "M4lSpectrum.h"
//---------------------------------------------------------------------------
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

//---------------------------------------------------------------------------
int main(int argc, char *argv[]);
vector<double> SumVector(vector<double> &V1, vector<double> &V2);
vector<double> ScaleVector(vector<double> &V1, double Factor);
void SetAlias(TTree &ResultTree);
//---------------------------------------------------------------------------
#define PI 3.14159265358979323846264338327950288479716939937510
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   srand(31426);

   string SignalFileName[2]     = {"EventF.root", "Dummy.root"};
   string BackgroundFileName[2] = {"EventF.root", "Dummy.root"};
   string ZJFileName[2]         = {"EventF.root", "Dummy.root"};
   string ggZZFileName[2]       = {"EventF.root", "Dummy.root"};

   int Factor = 1;

   if(argc < 14)
   {
      cerr << "Usage: " << argv[0]
         << " File NEventsPerJob JobNumber Energy Process Channel"
         << " A2ZZ A3ZZ A2ZA A3ZA A2AA A3AA A1L1ZZ"
         << endl;
      return -1;
   }

   string FileName  = argv[1];
   int NEventsPerJob = atoi(argv[2]);
   int JobNumber = atoi(argv[3]);
   int Energy       = atoi(argv[4]);
   int Process      = atoi(argv[5]);
   int Channel      = atoi(argv[6]);
   if(!(Channel >= 0 && Channel <= 3)) {
     cout << "Channel " << Channel << " is invalid.\n";
     return -1;
   }

   double A2ZZ = atof(argv[7]);
   double A3ZZ = atof(argv[8]);
   double A2ZA = atof(argv[9]);
   double A3ZA = atof(argv[10]);
   double A2AA = atof(argv[11]);
   double A3AA = atof(argv[12]);
   double A1L1ZZ = atof(argv[13]);
   double A1LQZZ = 0;

   FitClass Fits;
   Fits.ClearPoints();

   vector<FitResultSummary> Results;

   vector<SingleEvent> Events;

   bool HasBadEvent = 0;
   
   int P = DEFAULT_PROCESS;

   if (Energy == 7) {
     if (Process == -1) {
       HasBadEvent = ReadEventsSeparate(Events, FileName, NEventsPerJob, JobNumber, true, P, true, Channel, false, false);
     } else if (Process == 0) {
       HasBadEvent = ReadEventsSeparate(Events, FileName, NEventsPerJob, JobNumber, true, P, true, Channel, false, false);
     } else if (Process == 1) {
       HasBadEvent = ReadEventsSeparate(Events, FileName, NEventsPerJob, JobNumber, false, P, true, Channel, false, false);
     } else if (Process == 2) {
       HasBadEvent = ReadEventsSeparate(Events, FileName, NEventsPerJob, JobNumber, false, P, true, Channel, false, false);
     }
   } else {
     if (Process == -1) {
       HasBadEvent = ReadEventsSeparate(Events, FileName, NEventsPerJob, JobNumber, true, P, false, Channel, false, false);
     } else if (Process == 0) {
       HasBadEvent = ReadEventsSeparate(Events, FileName, NEventsPerJob, JobNumber, true, P, false, Channel, false, false);
     } else if (Process == 1) {
       HasBadEvent = ReadEventsSeparate(Events, FileName, NEventsPerJob, JobNumber, false, P, false, Channel, false, false);
     } else if (Process == 2) {
       HasBadEvent = ReadEventsSeparate(Events, FileName, NEventsPerJob, JobNumber, false, P, false, Channel, false, false);
     }
   }



   double MySumWeight = 0;
   for(int i = 0; i < (int)Events.size(); i++) {
      MySumWeight = MySumWeight + Events[i].weight;
   }
   

   //************************************************************************
   //Nominal Expected Yields
   //************************************************************************
   // 8 TeV Yield
   vector<double> NS8 = ListToVector(4, 4.359, 3.385, 3.066, 5.983);
   vector<double> NSSigma8 = ListToVector(4, 0.11, 0.11, 0.11, 0.11);
   vector<double> NB8 = ListToVector(4, 3.523, 2.018, 1.785, 4.635);
   vector<double> NBSigma8 = ListToVector(4, 0.048, 0.048, 0.047, 0.047);
   vector<double> NZJ8 = ListToVector(4, 0.721, 2.077, 1.691, 0.823);
   vector<double> NZJSigma8 = ListToVector(4, 0.40, 0.40, 0.40, 0.40);
   vector<double> NggZZ8 = ListToVector(4, 0.185, 0.149, 0.120, 0.250);
   vector<double> NggZZSigma8 = ListToVector(4, 0.25, 0.25, 0.25, 0.25);

   // 7 TeV Yield
   vector<double> NS7 = ListToVector(4, 0.946, 0.743, 0.701, 1.127);
   vector<double> NSSigma7 = ListToVector(4, 0.11, 0.11, 0.11, 0.11);
   vector<double> NB7 = ListToVector(4, 0.873, 0.547, 0.518, 1.075);
   vector<double> NBSigma7 = ListToVector(4, 0.048, 0.048, 0.047, 0.047);
   vector<double> NZJ7 = ListToVector(4, 0.110, 0.583, 0.406, 0.167);
   vector<double> NZJSigma7 = ListToVector(4, 0.40, 0.40, 0.40, 0.40);
   vector<double> NggZZ7 = ListToVector(4, 0.0271, 0.0205, 0.0210, 0.0367);
   vector<double> NggZZSigma7 = ListToVector(4, 0.25, 0.25, 0.25, 0.25);

   //no 2e2mu
   // vector<double> NS8 = ListToVector(4, 0, 0, 3.066, 5.983);
   // vector<double> NB8 = ListToVector(4, 0, 0, 1.785, 4.635);
   // vector<double> NS7 = ListToVector(4, 0, 0, 0.701, 1.127);
   // vector<double> NB7 = ListToVector(4, 0, 0, 0.518, 1.075);
//    vector<double> NZJ8 = ListToVector(4, 0, 0, 1.691, 0.823);
//    vector<double> NggZZ8 = ListToVector(4, 0, 0, 0.120, 0.250);
//    vector<double> NZJ7 = ListToVector(4, 0, 0, 0.406, 0.167);
//    vector<double> NggZZ7 = ListToVector(4, 0, 0, 0.0210, 0.0367);

   //no ZJ, ggZZ
//    vector<double> NZJ8 = ListToVector(4, 0, 0, 0, 0);
//    vector<double> NggZZ8 = ListToVector(4, 0, 0, 0, 0);
//    vector<double> NZJ7 = ListToVector(4, 0, 0, 0, 0);
//    vector<double> NggZZ7 = ListToVector(4, 0, 0, 0, 0);


   vector<double> NS8Prime = NS8;
   vector<double> NB8Prime = NB8;
   vector<double> NZJ8Prime = NZJ8;
   vector<double> NggZZ8Prime = NggZZ8;
   
   vector<double> NS7Prime = NS7;
   vector<double> NB7Prime = NB7;
   vector<double> NZJ7Prime = NZJ7;
   vector<double> NggZZ7Prime = NggZZ7;


   string As = "NNNNNN";
   string Phases = "NNNNNN";
   string Counts = "NNNN";
   string Fs = "NNNNNNNNNNNN";


   FitConfiguration Configuration("Y",                                            /* Do weighted dataset */
      As, Phases, Counts, Counts,
      Fs, Fs, "NNNNNNN", "N",                                                     /* What to float */
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
      1);                                                                         /* Mu */

   cout << "\nFit Configuration Summary\n";
   cout << "Model Parameters Floated : " << As << "\n";
   cout << "Model Complex Phases Floated : " << Phases << "\n";
   cout << "\n\n";

   TFile OutputFile("LikelihoodFile.root", "RECREATE");

   
   Fits.SignalStateCount[1][0]      = NS7[0];
   Fits.SignalStateCount[1][1]      = NS7[1];
   Fits.SignalStateCount[1][2]      = NS7[2];
   Fits.SignalStateCount[1][3]      = NS7[3];
   Fits.SignalStateCount[0][0]      = NS8[0];
   Fits.SignalStateCount[0][1]      = NS8[1];
   Fits.SignalStateCount[0][2]      = NS8[2];
   Fits.SignalStateCount[0][3]      = NS8[3];
   Fits.BackgroundStateCount[1][0]  = NB7[0];
   Fits.BackgroundStateCount[1][1]  = NB7[1];
   Fits.BackgroundStateCount[1][2]  = NB7[2];
   Fits.BackgroundStateCount[1][3]  = NB7[3];
   Fits.BackgroundStateCount[0][0]  = NB8[0];
   Fits.BackgroundStateCount[0][1]  = NB8[1];
   Fits.BackgroundStateCount[0][2]  = NB8[2];
   Fits.BackgroundStateCount[0][3]  = NB8[3];
   Fits.ZJStateCount[1][0]          = NZJ7[0];
   Fits.ZJStateCount[1][1]          = NZJ7[1];
   Fits.ZJStateCount[1][2]          = NZJ7[2];
   Fits.ZJStateCount[1][3]          = NZJ7[3];
   Fits.ZJStateCount[0][0]          = NZJ8[0];
   Fits.ZJStateCount[0][1]          = NZJ8[1];
   Fits.ZJStateCount[0][2]          = NZJ8[2];
   Fits.ZJStateCount[0][3]          = NZJ8[3];
   Fits.ggZZStateCount[1][0]        = NggZZ7[0];
   Fits.ggZZStateCount[1][1]        = NggZZ7[1];
   Fits.ggZZStateCount[1][2]        = NggZZ7[2];
   Fits.ggZZStateCount[1][3]        = NggZZ7[3];
   Fits.ggZZStateCount[0][0]        = NggZZ8[0];
   Fits.ggZZStateCount[0][1]        = NggZZ8[1];
   Fits.ggZZStateCount[0][2]        = NggZZ8[2];
   Fits.ggZZStateCount[0][3]        = NggZZ8[3];

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



   FitResultSummary ResultTemp;
//    int B = 1;
//    for(int i2 = 0; i2 < B; i2++)
//    {
//       for(int i3 = 0; i3 < B; i3++)
//       {
//          Configuration.PhaseInitialValue[0] = (i2) * 2 * PI / B;
//          Configuration.PhaseInitialValue[1] = (i3) * 2 * PI / B;
//          ResultTemp = Fits.DoFit(Configuration);
//          Results.push_back(ResultTemp);
//       }
//    }

   // TH1D HScanFA3("HScanFA3", "FA3Scan", 100, -1, 1);   
   // for(int iB = 1; iB <= HScanFA3.GetNbinsX(); iB++)
   // {
   //   double FA3 = HScanFA3.GetXaxis()->GetBinCenter(iB);
   //   double A2A1 = Configuration.AAInitialValue[0];
   //   double S2 = A2A1 * A2A1 / 3.276 / 3.276;
   //   double A3A1 = sqrt((1 + S2) / (1 - fabs(FA3)) * fabs(FA3) * 5.042 * 5.042);
   //   if(FA3 > 0)
   //     A3A1 = -A3A1;

   //   cout << "Before Evaluation : Scan fa3 = " << FA3 << " : " << currentDateTime()  << "\n";

   //   Configuration.AAInitialValue[1] = A3A1;
   //   ResultTemp = Fits.DoFit(Configuration);

   //   if (ResultTemp.BestNLL == ResultTemp.BestNLL) {
   //     Results.push_back(ResultTemp);
   //   }

   //   cout << "After Evaluation : Scan fa3 = " << FA3 << " : " << ResultTemp.BestNLL << " : " << currentDateTime() << "\n";
   // }



   // TH1D HScanFA2("HScanFA2", "FA2Scan", 100, -1, 1);   
   // for(int iB = 1; iB <= HScanFA2.GetNbinsX(); iB++)
   // {
   //   double FA2 = HScanFA2.GetXaxis()->GetBinCenter(iB);
   //   double A3A1 = Configuration.AAInitialValue[1];
   //   double S3 = A3A1 * A3A1 / 5.042 / 5.042;
   //   double A2A1 = sqrt((1 + S3) / (1 - fabs(FA2)) * fabs(FA2) * 3.276 * 3.276);
   //   if(FA2 > 0)
   //     A2A1 = -A2A1;

   //   cout << "Before Evaluation : Scan fa2 = " << FA2 << " : " << currentDateTime()  << "\n";

   //   Configuration.AAInitialValue[0] = A2A1;
   //   ResultTemp = Fits.DoFit(Configuration);

   //   if (ResultTemp.BestNLL == ResultTemp.BestNLL)
   //     Results.push_back(ResultTemp);

   //   cout << "After Evaluation : Scan fa2 = " << FA2 << " : " << ResultTemp.BestNLL << " : " << currentDateTime() << "\n";
   // }

   if(Events.size() > 0)
   {
      for(int iB1 = 0; iB1 < 101; iB1++)
      {
         for(int iB2 = 0; iB2 < 101; iB2++)
         {
            double FA2 = iB1 * 0.01;
            double FA3 = iB2 * 0.01;

            double FA1 = 1 - fabs(FA2) - fabs(FA3);
            if(FA1 <= 0)
               continue;

            double S2 = fabs(FA2 / FA1);
            double S3 = fabs(FA3 / FA1);

            double A2A1 = sqrt(S2) * 3.276;
            double A3A1 = sqrt(S3) * 5.042;

            if(FA2 > 0)   A2A1 = -A2A1;
            if(FA3 > 0)   A3A1 = -A3A1;

            // cout << "Before Evaluation : Scan fa2 = " << FA2 << ", fa3 = " << FA3 << " : " << currentDateTime()  << "\n";

            for(int iP1 = 0; iP1 < 20; iP1++)
            {
               for(int iP2 = 0; iP2 < 20; iP2++)
               {
                  double PhaseA2 = iP1 * 2 * PI / 20;
                  double PhaseA3 = iP2 * 2 * PI / 20;

                  Configuration.AAInitialValue[0] = A2A1;
                  Configuration.AAInitialValue[1] = A3A1;
                  Configuration.PhaseInitialValue[0] = PhaseA2;
                  Configuration.PhaseInitialValue[1] = PhaseA3;
                  ResultTemp = Fits.DoFit(Configuration);

                  if(ResultTemp.BestNLL == ResultTemp.BestNLL)
                     Results.push_back(ResultTemp);
               }
            }

            // cout << "After Evaluation : Scan fa2 = " << FA2 << ", fa3 = " << FA3 << " : " << ResultTemp.BestNLL << " : " << currentDateTime() << "\n";
         }
      }
   }



   Fits.ClearPoints();

   string BranchList = "";
   BranchList = BranchList + "A2ZZA1ZZ:A2ZZPhase:A3ZZA1ZZ:A3ZZPhase";                          // 4
   BranchList = BranchList + ":A2ZAA1ZZ:A2ZAPhase:A3ZAA1ZZ:A3ZAPhase";                         // 8
   BranchList = BranchList + ":A2AAA1ZZ:A2AAPhase:A3AAA1ZZ:A3AAPhase";                         // 12
   BranchList = BranchList + ":A1L1ZZ:A1L1ZZPhase:A1LQZZ:A1LQZZPhase";                         // 16
   BranchList = BranchList + ":TruthNLL:BestNLL";                                              // 18
   BranchList = BranchList + ":SumWeight";                                                     // 19
   BranchList = BranchList + ":energy:process:channel";                                        // 22
   
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[150];
      Array[0]   = Results[i].AA[0];          
      Array[1]   = Results[i].Phase[0];      
      Array[2]   = Results[i].AA[1];         
      Array[3]   = Results[i].Phase[1];      
      Array[4]   = Results[i].AA[2];         
      Array[5]   = Results[i].Phase[2];      
      Array[6]   = Results[i].AA[3];         
      Array[7]   = Results[i].Phase[3];      
      Array[8]   = Results[i].AA[4];         
      Array[9]   = Results[i].Phase[4];      
      Array[10]  = Results[i].AA[5];         
      Array[11]  = Results[i].Phase[5];      
      Array[12] = Results[i].AA[6];        
      Array[13] = Results[i].Phase[6];     
      Array[14] = Results[i].AA[7];        
      Array[15] = Results[i].Phase[7];     
      Array[16] = Results[i].TruthNLL;
      Array[17] = Results[i].BestNLL;
      Array[18] = float(MySumWeight);
      Array[19] = Energy;
      Array[20] = Process;
      Array[21] = Channel;

      OutputTree.Fill(Array);
   }

   SetAlias(OutputTree);

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
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








