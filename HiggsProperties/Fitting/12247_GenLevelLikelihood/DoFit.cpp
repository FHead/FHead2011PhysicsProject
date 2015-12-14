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
#include "SetStyle.h"
#include "ProgressBar.h"

#include "AngleConversion.h"

#include "ProjectionHelper.h"
#include "FitClass.h"

int main(int argc, char *argv[]);
bool PassBaselineCut(EventParameters Event);
void ReadEvents(vector<SingleEvent> &Events, string FileName, bool ExtraMHWeight = false);

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   SetStyle();

   srand(time(NULL));

   string FileName =  "EventF.root";
   int DatasetSize = 30;
   string BackgroundFileName = "EventF.root";
   int BackgroundDatasetSize = 30;

   if(argc <= 4)
   {
      cerr << "Usage: " << argv[0] << " SignalRootFile SignalDatasetSize BackgroundRootFile BackgroundDatasetSize" << endl;
      return -1;
   }

   FileName = argv[1];
   DatasetSize = atoi(argv[2]);
   BackgroundFileName = argv[3];
   BackgroundDatasetSize = atoi(argv[4]);

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   vector<FitResultSummary> Results;

   PsFileHelper PsFile("FitResultMeow.ps");

   vector<SingleEvent> Signals, Backgrounds;
   ReadEvents(Signals, FileName, false);
   ReadEvents(Backgrounds, BackgroundFileName, false);

   int BackgroundCounter = 0;

   for(int iS = 0; iS < (int)Signals.size(); iS++)
   {
      Fits.AddPoint(Signals[iS]);

      if(Signals[iS].state == "em")   Fits.SignalStateCount[0] = Fits.SignalStateCount[0] + 1;
      if(Signals[iS].state == "me")   Fits.SignalStateCount[1] = Fits.SignalStateCount[1] + 1;
      if(Signals[iS].state == "ee")   Fits.SignalStateCount[2] = Fits.SignalStateCount[2] + 1;
      if(Signals[iS].state == "mm")   Fits.SignalStateCount[3] = Fits.SignalStateCount[3] + 1;

      if(Fits.SampleSize < DatasetSize)
         continue;

      while(Fits.SampleSize < DatasetSize + BackgroundDatasetSize)
      {
         Fits.AddPoint(Backgrounds[BackgroundCounter]);

         if(Backgrounds[BackgroundCounter].state == "em")   Fits.BackgroundStateCount[0] = Fits.BackgroundStateCount[0] + 1;
         if(Backgrounds[BackgroundCounter].state == "me")   Fits.BackgroundStateCount[1] = Fits.BackgroundStateCount[1] + 1;
         if(Backgrounds[BackgroundCounter].state == "ee")   Fits.BackgroundStateCount[2] = Fits.BackgroundStateCount[2] + 1;
         if(Backgrounds[BackgroundCounter].state == "mm")   Fits.BackgroundStateCount[3] = Fits.BackgroundStateCount[3] + 1;

         BackgroundCounter = BackgroundCounter + 1;
         if(BackgroundCounter >= Backgrounds.size())
            BackgroundCounter = 0;
      }

      TH2D HA3A2Likelihood("HA3A2Likelihood", "Likelihood scan;|A3/A1|;|A2/A1|", 100, 0, 25, 100, 0, 15);

      ProgressBar Bar(cerr, HA3A2Likelihood.GetNbinsX());
      Bar.SetStyle(1);

      double Minimum = 9999999, BestA3A1, BestA2A1;
      for(int i = 1; i <= HA3A2Likelihood.GetNbinsX(); i++)
      {
         Bar.Update(i);
         Bar.Print();

         for(int j = 1; j <= HA3A2Likelihood.GetNbinsY(); j++)
         {
            double A3A1 = HA3A2Likelihood.GetXaxis()->GetBinCenter(i);
            double A2A1 = HA3A2Likelihood.GetYaxis()->GetBinCenter(j);

            FitResultSummary ResultTemp = Fits.DoFit(FITMODE_PHASEONLY, A3A1, A2A1);
            // FitResultSummary ResultTemp = Fits.DoFit(FITMODE_ALL);

            double Parameters[10];
            Parameters[0] = ResultTemp.A3A1;
            Parameters[1] = ResultTemp.A3Phase;
            Parameters[2] = ResultTemp.A2A1;
            Parameters[3] = ResultTemp.A2Phase;
            Parameters[4] = ResultTemp.Fem;
            Parameters[5] = ResultTemp.Fme;
            Parameters[6] = ResultTemp.Fee;
            Parameters[7] = ResultTemp.Fmm;
            Parameters[8] = ResultTemp.N1;
            Parameters[9] = ResultTemp.N2;

            double LogLikelihood = Fits.CalculateLogLikelihoodAll(Parameters) * 2;

            HA3A2Likelihood.SetBinContent(i, j, LogLikelihood);

            if(LogLikelihood < Minimum)
            {
               Minimum = LogLikelihood;
               BestA3A1 = A3A1;
               BestA2A1 = A2A1;
            }
         }
      }

      Bar.Update(HA3A2Likelihood.GetNbinsX());
      Bar.Print();
      Bar.PrintLine();

      for(int i = 1; i <= HA3A2Likelihood.GetNbinsX(); i++)
         for(int j = 1; j <= HA3A2Likelihood.GetNbinsY(); j++)
            HA3A2Likelihood.SetBinContent(i, j, HA3A2Likelihood.GetBinContent(i, j) - Minimum);

      HA3A2Likelihood.SetStats(0);
      HA3A2Likelihood.SetMaximum(10);

      TCanvas C;
      HA3A2Likelihood.Draw("colz");
      TGraph G1, G2;
      G1.SetPoint(0, sqrt(200), 6);
      G1.SetMarkerStyle(29);
      G1.SetMarkerSize(2.2);
      G1.SetMarkerColor(kWhite);
      G1.Draw("p");
      G2.SetPoint(0, BestA3A1, BestA2A1);
      G2.SetMarkerStyle(34);
      G2.SetMarkerSize(2.2);
      G2.SetMarkerColor(kWhite);
      G2.Draw("p");

      PsFile.AddCanvas(C);

      // FitResultSummary ResultTemp = Fits.DoFit();
      // Results.push_back(ResultTemp);
      FitCount = FitCount + 1;

      if(FitCount >= 10)
         break;

      Fits.ClearPoints();
   }

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

bool PassBaselineCut(EventParameters Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(Event.ZMass < 40)    return false;
   if(Event.Z2Mass < 12)   return false;
   
   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 20)   return false;
   if(LPTs[2] < 10)   return false;
   if(LPTs[1] < 7)    return false;
   if(LPTs[0] < 7)    return false;

   if((Leptons.Lepton11 + Leptons.Lepton12).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton11 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton21).GetMass() < 4)   return false;
   if((Leptons.Lepton12 + Leptons.Lepton22).GetMass() < 4)   return false;
   if((Leptons.Lepton21 + Leptons.Lepton22).GetMass() < 4)   return false;
   
   return true;
}

void ReadEvents(vector<SingleEvent> &Events, string FileName, bool ExtraMHWeight)
{
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      return;

   DataHelper DHFile("Normalization.dh");

   int l1id, l3id;
   Tree->SetBranchAddress("l1id", &l1id);
   Tree->SetBranchAddress("l3id", &l3id);

   string SignalBranch[] = {"T1", "T3", "T5", "T7", "T9"};
   string BackgroundBranch[] = {"T2", "T4", "T6", "T8", "T10"};

   double Value[16][5] = {{0}};
   double Integral[16][5] = {{0}};

   string suffix[15] = {"A1RA1R", "A2RA2R", "A2IA2I", "A3RA3R", "A3IA3I",
      "A1RA2R", "A1RA2I", "A1RA3R", "A1RA3I", "A2RA2I",
      "A2RA3R", "A2RA3I", "A2IA3R", "A2IA3I", "A3RA3I"};
   vector<string> Suffix(suffix, suffix + 15);

   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B1_%s", Suffix[i].c_str()), &Value[i+1][0]);
   Tree->SetBranchAddress("B2", &Value[0][0]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B3_%s", Suffix[i].c_str()), &Value[i+1][1]);
   Tree->SetBranchAddress("B4", &Value[0][1]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B5_%s", Suffix[i].c_str()), &Value[i+1][2]);
   Tree->SetBranchAddress("B6", &Value[0][2]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B7_%s", Suffix[i].c_str()), &Value[i+1][3]);
   Tree->SetBranchAddress("B8", &Value[0][3]);
   for(int i = 0; i < 15; i++)
      Tree->SetBranchAddress(Form("B9_%s", Suffix[i].c_str()), &Value[i+1][4]);
   Tree->SetBranchAddress("B10", &Value[0][4]);

   float Weight;
   Tree->SetBranchAddress("weight", &Weight);

   float l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   float l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
   Tree->SetBranchAddress("l1pt", &l1pt);
   Tree->SetBranchAddress("l1eta", &l1eta);
   Tree->SetBranchAddress("l1phi", &l1phi);
   Tree->SetBranchAddress("l2pt", &l2pt);
   Tree->SetBranchAddress("l2eta", &l2eta);
   Tree->SetBranchAddress("l2phi", &l2phi);
   Tree->SetBranchAddress("l3pt", &l3pt);
   Tree->SetBranchAddress("l3eta", &l3eta);
   Tree->SetBranchAddress("l3phi", &l3phi);
   Tree->SetBranchAddress("l4pt", &l4pt);
   Tree->SetBranchAddress("l4eta", &l4eta);
   Tree->SetBranchAddress("l4phi", &l4phi);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      if(Event.HMass > 135 || Event.HMass < 115)
         continue;
      if(DrawRandom(0, 1) > Weight)   // killed by efficiency
         continue;
      if(ExtraMHWeight == true)
      {
         double Height = 10.4077 - 0.157571 * Event.HMass + 0.000656893 * Event.HMass * Event.HMass;
         double HMax = 10.4077 - 0.157571 * 135 + 0.000656893 * 135 * 135;
         double HMin = 10.4077 + 0.157571 * 0.157571 / 0.000656893 / 0.000656893 / 4;

         // cout << Event.HMass << " " << Height / HMax << endl;
         if(DrawRandom(0, 1) > HMin / Height)
            continue;
      }

      if(PassBaselineCut(Event) == false)
         continue;

      for(int j = 0; j < 5; j++)
      {
         Value[10][j] = 0;
         Value[15][j] = 0;
      }

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      string State = "";
      // if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      // if(l1id == 13 && l3id == 11)   State = "me";
      // if(l1id == 13 && l3id == 13)   State = "mm";

      if(State == "")   // WTF
         continue;
      else
      {
         for(int j = 0; j < 5; j++)
         {
            Integral[0][j] = DHFile[State][BackgroundBranch[j]].GetDouble();
            for(int i = 1; i < 16; i++)
            {
               char BranchSuffix[2] = "A";
               BranchSuffix[0] = char('A' + (i - 1));
               string Branch = SignalBranch[j] + BranchSuffix;
               Integral[i][j] = DHFile[State][Branch].GetDouble();

               if(i == 10 || i == 15)
                  Integral[i][j] = 0;
            }
         }
      }

      bool Good = true;
      for(int i = 0; i < 16; i++)
         for(int j = 0; j < 5; j++)
            if(Value[i][j] > 0.99 || (i <= 5 && Value[i][j] < 1e-35))
               Good = false;
      if(Good == false)
         continue;

      SingleEvent NewEvent;

      for(int i = 0; i < 16; i++)
         for(int j = 0; j < 5; j++)
            NewEvent.v[i][j] = Value[i][j];
      for(int i = 0; i < 16; i++)
         for(int j = 0; j < 5; j++)
            NewEvent.i[i][j] = Integral[i][j];
      NewEvent.event = Event;
      NewEvent.state = State;

      Events.push_back(NewEvent);
   }
   
   File.Close();

   random_shuffle(Events.begin(), Events.end());
}



