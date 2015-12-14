//---------------------------------------------------------------------------
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
#include "TTree.h"
#include "TFile.h"
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
#include "M4lSpectrum.h"
#include "FileIO.h"
//---------------------------------------------------------------------------
bool ReadEvents(vector<SingleEvent> &EventsEM, vector<SingleEvent> &EventsME,
   vector<SingleEvent> &EventsEE, vector<SingleEvent> &EventsMM,
   string FileName, bool Capital, int Process,
   double MaxWeight, bool Is7TeV, bool AlternativeWeight, int TargetToyNumber,
   bool EMMETogether, bool ChannelFromID, bool IgnoreWeight, double EventLimitFactor,
   bool FillInJacobian)
{
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("ReducedTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("zz4lTree");
   if(Tree == NULL)
      return true;

   DataHelper DHFile("CombinedNormalization.dh");
   // DataHelper DHFile("OldNormalization.dh");

   int l1id, l3id;
   if(Capital == false)
   {
      Tree->SetBranchAddress("l1id", &l1id);
      Tree->SetBranchAddress("l3id", &l3id);
   }
   else
   {
      Tree->SetBranchAddress("L1ID", &l1id);
      Tree->SetBranchAddress("L3ID", &l3id);
   }

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
   // for(int i = 0; i < 153; i++)
   //    Tree->SetBranchAddress(Form("B11_%s", Suffix[i].c_str()), &Value[i+1][5]);
   // Tree->SetBranchAddress("B12", &Value[0][5]);
   // for(int i = 0; i < 153; i++)
   //    Tree->SetBranchAddress(Form("B13_%s", Suffix[i].c_str()), &Value[i+1][6]);
   // Tree->SetBranchAddress("B14", &Value[0][6]);
   // for(int i = 0; i < 153; i++)
   //    Tree->SetBranchAddress(Form("B15_%s", Suffix[i].c_str()), &Value[i+1][7]);
   // Tree->SetBranchAddress("B16", &Value[0][7]);
   // for(int i = 0; i < 153; i++)
   //    Tree->SetBranchAddress(Form("B17_%s", Suffix[i].c_str()), &Value[i+1][8]);
   // Tree->SetBranchAddress("B18", &Value[0][8]);
   // for(int i = 0; i < 153; i++)
   //    Tree->SetBranchAddress(Form("B21_%s", Suffix[i].c_str()), &Value[i+1][9]);
   // for(int i = 0; i < 153; i++)
   //    Tree->SetBranchAddress(Form("B22_%s", Suffix[i].c_str()), &Value[i+1][10]);
   // for(int i = 0; i < 153; i++)
   //    Tree->SetBranchAddress(Form("B23_%s", Suffix[i].c_str()), &Value[i+1][11]);
   // for(int i = 0; i < 153; i++)
   //    Tree->SetBranchAddress(Form("B24_%s", Suffix[i].c_str()), &Value[i+1][12]);

   Tree->SetBranchAddress("B19", &Value2[0][0]);
   Tree->SetBranchAddress("B20", &Value2[1][0]);

   // float l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   // float l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
   float weight = 1;
   // double L1PT, L1Eta, L1Phi, L2PT, L2Eta, L2Phi;
   // double L3PT, L3Eta, L3Phi, L4PT, L4Eta, L4Phi;
   double Weight = 1;
   if(Capital == false)
   // {
   //    Tree->SetBranchAddress("l1pt",   &l1pt);
   //    Tree->SetBranchAddress("l1eta",  &l1eta);
   //    Tree->SetBranchAddress("l1phi",  &l1phi);
   //    Tree->SetBranchAddress("l2pt",   &l2pt);
   //    Tree->SetBranchAddress("l2eta",  &l2eta);
   //    Tree->SetBranchAddress("l2phi",  &l2phi);
   //    Tree->SetBranchAddress("l3pt",   &l3pt);
   //    Tree->SetBranchAddress("l3eta",  &l3eta);
   //    Tree->SetBranchAddress("l3phi",  &l3phi);
   //    Tree->SetBranchAddress("l4pt",   &l4pt);
   //    Tree->SetBranchAddress("l4eta",  &l4eta);
   //    Tree->SetBranchAddress("l4phi",  &l4phi);
      Tree->SetBranchAddress("weight", &weight);
   // }
   else
   // {
   //    Tree->SetBranchAddress("L1PT",   &L1PT);
   //    Tree->SetBranchAddress("L1Eta",  &L1Eta);
   //    Tree->SetBranchAddress("L1Phi",  &L1Phi);
   //    Tree->SetBranchAddress("L2PT",   &L2PT);
   //    Tree->SetBranchAddress("L2Eta",  &L2Eta);
   //    Tree->SetBranchAddress("L2Phi",  &L2Phi);
   //    Tree->SetBranchAddress("L3PT",   &L3PT);
   //    Tree->SetBranchAddress("L3Eta",  &L3Eta);
   //    Tree->SetBranchAddress("L3Phi",  &L3Phi);
   //    Tree->SetBranchAddress("L4PT",   &L4PT);
   //    Tree->SetBranchAddress("L4Eta",  &L4Eta);
   //    Tree->SetBranchAddress("L4Phi",  &L4Phi);
      Tree->SetBranchAddress("Weight", &Weight);
   // }

   float z1mass, z2mass, zzmass;
   double M1, M2, MH, Theta1, Theta2, Theta0;
   if(Capital == false)
   {
      Tree->SetBranchAddress("z1mass", &z1mass);
      Tree->SetBranchAddress("z2mass", &z2mass);
      Tree->SetBranchAddress("zzmass", &zzmass);
   }
   else
   {
      Tree->SetBranchAddress("M1", &M1);
      Tree->SetBranchAddress("M2", &M2);
      Tree->SetBranchAddress("MH", &MH);
      Tree->SetBranchAddress("Theta0", &Theta0);
      Tree->SetBranchAddress("Theta1", &Theta1);
      Tree->SetBranchAddress("Theta2", &Theta2);
   }

   bool PassEM, PassME, PassEE, PassMM;
   if(Capital == true)
   {
      Tree->SetBranchAddress("PassEM", &PassEM);
      Tree->SetBranchAddress("PassME", &PassME);
      Tree->SetBranchAddress("PassEE", &PassEE);
      Tree->SetBranchAddress("PassMM", &PassMM);
   }

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
      if(TargetToyNumber >= 0 && TargetToyNumber != (int)toy)
         continue;

      if(ChannelFromID == false)
      {
         if(channel == 0)        l1id = 13, l3id = 13;
         else if(channel == 1)   l1id = 11, l3id = 11;
         else if(channel == 2)   l1id = 11, l3id = 13;
         else if(channel == 3)   l1id = 13, l3id = 11;
      }

      if(AlternativeWeight == true)
      {
         double Factor = GetCombinedWeight(Value);
         weight = weight * Factor;
         Weight = Weight * Factor;
      }

      if(EntryCount < 1000 || (iE % (EntryCount / 1000) == 0))
      {
         Bar.Update(iE);
         Bar.Print();
      }

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      if(IgnoreWeight == false)
      {
         if(l1id == 11 && l3id == 11 && EventsEE.size() > EVENTLIMIT * EventLimitFactor)   continue;
         if(l1id == 13 && l3id == 11 && EventsME.size() > EVENTLIMIT * EventLimitFactor)   continue;
         if(l1id == 11 && l3id == 13 && EventsEM.size() > EVENTLIMIT * EventLimitFactor)   continue;
         if(l1id == 13 && l3id == 13 && EventsMM.size() > EVENTLIMIT * EventLimitFactor)   continue;

         if(EventsEE.size() > EVENTLIMIT * EventLimitFactor && EventsME.size() > EVENTLIMIT * EventLimitFactor
            && EventsEM.size() > EVENTLIMIT * EventLimitFactor && EventsMM.size() > EVENTLIMIT * EventLimitFactor)
            break;
      }

      if(Capital == false)
         Weight = weight;
      if(Weight != Weight)
         continue;

      Weight = Weight / MaxWeight;
      
      if(IgnoreWeight == true)
         Weight = 1;
      else if(Weight < 1)
      {
         if(DrawRandom(0, 1) > Weight)
            continue;
         Weight = 1;
      }
      
      if(FillInJacobian == true)
         Weight = Weight * sin(Theta0) * sin(Theta1) * sin(Theta2);

      // LeptonVectors Leptons;
      // Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      // Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      // Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      // Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      // EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      // if(Capital == false)
      //    cout << zzmass << " " << z1mass << " " << z2mass << endl;
      // else
      //    cout << MH << " " << M1 << " " << M2 << endl;

      if(Capital == false && (zzmass > 135 || zzmass < 115))
         continue;
      if(Capital == false && max(z1mass, z2mass) < 40)
         continue;
      if(Capital == false && min(z1mass, z2mass) < 12)
         continue;
      if(Capital == true && (MH > 135 || MH < 115))
         continue;
      if(Capital == true && max(M1, M2) < 40)
         continue;
      if(Capital == true && min(M1, M2) < 12)
         continue;
      // if(PassBaselineCut(Event, l1id, l3id) == false)
      //    continue;
      
      if(Capital == true)
      {
         if(l1id == 11 && l3id == 13 && PassEM == false)   continue;
         if(l1id == 13 && l3id == 11 && PassME == false)   continue;
         if(l1id == 11 && l3id == 11 && PassEE == false)   continue;
         if(l1id == 13 && l3id == 13 && PassMM == false)   continue;
      }

      string State = "";
      if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      if(l1id == 13 && l3id == 11)   State = "me";
      if(l1id == 13 && l3id == 13)   State = "mm";

      char BranchInitial = 'T';
      if(State == "em")   BranchInitial = 'T';
      if(State == "me")   BranchInitial = 'U';
      if(State == "ee")   BranchInitial = 'V';
      if(State == "mm")   BranchInitial = 'W';
      if(EMMETogether == true && State == "em")   BranchInitial = 'X';
      if(EMMETogether == true && State == "me")   BranchInitial = 'X';

      double ZX_S_Offset = 0, ggZZ_S_Offset = 0;
      double S = (Capital ? (MH * MH) : (zzmass * zzmass));

      if(Is7TeV == false && State == "em")   ZX_S_Offset   = log(GetZX8TeV2e2muSpectrum(S))   - 6.80;
      if(Is7TeV == false && State == "me")   ZX_S_Offset   = log(GetZX8TeV2mu2eSpectrum(S))   - 6.60;
      if(Is7TeV == false && State == "ee")   ZX_S_Offset   = log(GetZX8TeV4eSpectrum(S))      - 5.45;
      if(Is7TeV == false && State == "mm")   ZX_S_Offset   = log(GetZX8TeV4muSpectrum(S))     - 5.60;
      if(Is7TeV == true  && State == "em")   ZX_S_Offset   = log(GetZX7TeV2e2muSpectrum(S))   - 6.95;
      if(Is7TeV == true  && State == "me")   ZX_S_Offset   = log(GetZX7TeV2mu2eSpectrum(S))   - 6.60;
      if(Is7TeV == true  && State == "ee")   ZX_S_Offset   = log(GetZX7TeV4eSpectrum(S))      - 5.25;
      if(Is7TeV == true  && State == "mm")   ZX_S_Offset   = log(GetZX7TeV4muSpectrum(S))     - 5.45;

      if(Is7TeV == false && State == "em")   ggZZ_S_Offset = log(GetggZZ8TeV2e2muSpectrum(S)) - 7.05;
      if(Is7TeV == false && State == "me")   ggZZ_S_Offset = log(GetggZZ8TeV2mu2eSpectrum(S)) - 6.60;
      if(Is7TeV == false && State == "ee")   ggZZ_S_Offset = log(GetggZZ8TeV4eSpectrum(S))    - 5.60;
      if(Is7TeV == false && State == "mm")   ggZZ_S_Offset = log(GetggZZ8TeV4muSpectrum(S))   - 5.40;
      if(Is7TeV == true  && State == "em")   ggZZ_S_Offset = log(GetggZZ8TeV2e2muSpectrum(S)) - 6.95;
      if(Is7TeV == true  && State == "me")   ggZZ_S_Offset = log(GetggZZ8TeV2mu2eSpectrum(S)) - 6.60;
      if(Is7TeV == true  && State == "ee")   ggZZ_S_Offset = log(GetggZZ8TeV4eSpectrum(S))    - 5.40;
      if(Is7TeV == true  && State == "mm")   ggZZ_S_Offset = log(GetggZZ8TeV4muSpectrum(S))   - 5.80;

      string DHState = State;
      if(EMMETogether == true && (State == "em" || State == "me"))
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
            if(Is7TeV == false && State == "em")   Integral[0][j] *= 0.795;
            if(Is7TeV == false && State == "me")   Integral[0][j] *= 0.795;
            if(Is7TeV == false && State == "ee")   Integral[0][j] *= 0.855;
            if(Is7TeV == false && State == "mm")   Integral[0][j] *= 0.895;
            if(Is7TeV == true  && State == "em")   Integral[0][j] *= 0.795;
            if(Is7TeV == true  && State == "me")   Integral[0][j] *= 0.795;
            if(Is7TeV == true  && State == "ee")   Integral[0][j] *= 0.765;
            if(Is7TeV == true  && State == "mm")   Integral[0][j] *= 0.620;

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

      for(int j = 5; j <= 12; j++)   // For now!  Disable some systematics!
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
      for(int i = 0; i < 92; i++)
         for(int j = 0; j < 13; j++)
            if(Value[i][j] > 0.99 || (i < 14 && Value[i][j] < 1e-50))
               Good = false;
      if(Value2[0][0] > -1 || Value2[1][0] > -1)
         Good = false;
      if(Good == false)
      {
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
      NewEvent.weight = Weight;
      // NewEvent.ToyNumber = toy;

      if(Is7TeV == true)    NewEvent.energy = "7TeV";
      if(Is7TeV == false)   NewEvent.energy = "8TeV";

      if(State == "em")   EventsEM.push_back(NewEvent);
      if(State == "me")   EventsME.push_back(NewEvent);
      if(State == "ee")   EventsEE.push_back(NewEvent);
      if(State == "mm")   EventsMM.push_back(NewEvent);

      if(IgnoreWeight == false && EventsEM.size() > EVENTLIMIT && EventsME.size() > EVENTLIMIT && EventsEE.size() > EVENTLIMIT && EventsMM.size() > EVENTLIMIT)
         break;
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();

   // random_shuffle(EventsEM.begin(), EventsEM.end());
   // random_shuffle(EventsME.begin(), EventsME.end());
   // random_shuffle(EventsEE.begin(), EventsEE.end());
   // random_shuffle(EventsMM.begin(), EventsMM.end());

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
double PullAndReweightEvents(std::vector<SingleEvent> &Events, std::vector<SingleEvent> &Source, double Mean)
{
   if(Mean <= 0)
      return 0;

   double TotalWeight = 0;
   for(int i = 0; i < (int)Source.size(); i++)
      TotalWeight = TotalWeight + Source[i].weight;
   
   for(int i = 0; i < (int)Source.size(); i++)
      Source[i].weight = Source[i].weight / TotalWeight * Mean;
   
   Events.insert(Events.end(), Source.begin(), Source.end());
   Source.clear();
   
   return Mean;
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
double GetCombinedWeight(double Values[154][13])
{
   // TODO
   
   double A1ZZR     = 1;
   double A2ZZR     = 0;
   double A2ZZI     = 0;
   double A3ZZR     = -5.042;
   double A3ZZI     = 0;
   double A2ZAR     = 0;
   double A2ZAI     = 0;
   double A3ZAR     = 0;
   double A3ZAI     = 0;
   double A2AAR     = 0;
   double A2AAI     = 0;
   double A3AAR     = 0;
   double A3AAI     = 0;

   double N = 6;

   double Answer =
      (A1ZZR * A1ZZR * Values[1][0]
      + A2ZZR * A2ZZR * Values[2][0]
      + A2ZZI * A2ZZI * Values[3][0]
      + A3ZZR * A3ZZR * Values[4][0]
      + A3ZZI * A3ZZI * Values[5][0]
      + A2ZAR * A2ZAR * Values[6][0]
      + A2ZAI * A2ZAI * Values[7][0]
      + A3ZAR * A3ZAR * Values[8][0]
      + A3ZAI * A3ZAI * Values[9][0]
      + A2AAR * A2AAR * Values[10][0]
      + A2AAI * A2AAI * Values[11][0]
      + A3AAR * A3AAR * Values[12][0]
      + A3AAI * A3AAI * Values[13][0]
      + A1ZZR * A2ZZR * Values[14][0]
      + A1ZZR * A2ZZI * Values[15][0]
      + A1ZZR * A3ZZR * Values[16][0]
      + A1ZZR * A3ZZI * Values[17][0]
      + A1ZZR * A2ZAR * Values[18][0]
      + A1ZZR * A2ZAI * Values[19][0]
      + A1ZZR * A3ZAR * Values[20][0]
      + A1ZZR * A3ZAI * Values[21][0]
      + A1ZZR * A2AAR * Values[22][0]
      + A1ZZR * A2AAI * Values[23][0]
      + A1ZZR * A3AAR * Values[24][0]
      + A1ZZR * A3AAI * Values[25][0]
      + A2ZZR * A2ZZI * Values[26][0]
      + A2ZZR * A3ZZR * Values[27][0]
      + A2ZZR * A3ZZI * Values[28][0]
      + A2ZZR * A2ZAR * Values[29][0]
      + A2ZZR * A2ZAI * Values[30][0]
      + A2ZZR * A3ZAR * Values[31][0]
      + A2ZZR * A3ZAI * Values[32][0]
      + A2ZZR * A2AAR * Values[33][0]
      + A2ZZR * A2AAI * Values[34][0]
      + A2ZZR * A3AAR * Values[35][0]
      + A2ZZR * A3AAI * Values[36][0]
      + A2ZZI * A3ZZR * Values[37][0]
      + A2ZZI * A3ZZI * Values[38][0]
      + A2ZZI * A2ZAR * Values[39][0]
      + A2ZZI * A2ZAI * Values[40][0]
      + A2ZZI * A3ZAR * Values[41][0]
      + A2ZZI * A3ZAI * Values[42][0]
      + A2ZZI * A2AAR * Values[43][0]
      + A2ZZI * A2AAI * Values[44][0]
      + A2ZZI * A3AAR * Values[45][0]
      + A2ZZI * A3AAI * Values[46][0]
      + A3ZZR * A3ZZI * Values[47][0]
      + A3ZZR * A2ZAR * Values[48][0]
      + A3ZZR * A2ZAI * Values[49][0]
      + A3ZZR * A3ZAR * Values[50][0]
      + A3ZZR * A3ZAI * Values[51][0]
      + A3ZZR * A2AAR * Values[52][0]
      + A3ZZR * A2AAI * Values[53][0]
      + A3ZZR * A3AAR * Values[54][0]
      + A3ZZR * A3AAI * Values[55][0]
      + A3ZZI * A2ZAR * Values[56][0]
      + A3ZZI * A2ZAI * Values[57][0]
      + A3ZZI * A3ZAR * Values[58][0]
      + A3ZZI * A3ZAI * Values[59][0]
      + A3ZZI * A2AAR * Values[60][0]
      + A3ZZI * A2AAI * Values[61][0]
      + A3ZZI * A3AAR * Values[62][0]
      + A3ZZI * A3AAI * Values[63][0]
      + A2ZAR * A2ZAI * Values[64][0]
      + A2ZAR * A3ZAR * Values[65][0]
      + A2ZAR * A3ZAI * Values[66][0]
      + A2ZAR * A2AAR * Values[67][0]
      + A2ZAR * A2AAI * Values[68][0]
      + A2ZAR * A3AAR * Values[69][0]
      + A2ZAR * A3AAI * Values[70][0]
      + A2ZAI * A3ZAR * Values[71][0]
      + A2ZAI * A3ZAI * Values[72][0]
      + A2ZAI * A2AAR * Values[73][0]
      + A2ZAI * A2AAI * Values[74][0]
      + A2ZAI * A3AAR * Values[75][0]
      + A2ZAI * A3AAI * Values[76][0]
      + A3ZAR * A3ZAI * Values[77][0]
      + A3ZAR * A2AAR * Values[78][0]
      + A3ZAR * A2AAI * Values[79][0]
      + A3ZAR * A3AAR * Values[80][0]
      + A3ZAR * A3AAI * Values[81][0]
      + A3ZAI * A2AAR * Values[82][0]
      + A3ZAI * A2AAI * Values[83][0]
      + A3ZAI * A3AAR * Values[84][0]
      + A3ZAI * A3AAI * Values[85][0]
      + A2AAR * A2AAI * Values[86][0]
      + A2AAR * A3AAR * Values[87][0]
      + A2AAR * A3AAI * Values[88][0]
      + A2AAI * A3AAR * Values[89][0]
      + A2AAI * A3AAI * Values[90][0]
      + A3AAR * A3AAI * Values[91][0]) / (A1ZZR * A1ZZR * Values[1][0]) / N;

   return Answer;
}
//---------------------------------------------------------------------------

