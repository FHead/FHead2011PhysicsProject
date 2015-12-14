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

#include "FitClass.h"

int main(int argc, char *argv[]);
bool PassBaselineCut(EventParameters Event);
void ReadEvents(vector<SingleEvent> &Events, string FileName);

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   srand(time(NULL));

   string FileName =  "EventF.root";
   int DatasetSize = 30;

   if(argc <= 7)
   {
      cerr << "Usage: " << argv[0]
         << " SignalRootFile SignalDatasetSize"
         << " eq/el gL/el gR/gL gqL/gL gqR/gqL"
         << endl;
      return -1;
   }

   FileName = argv[1];
   DatasetSize = atoi(argv[2]);

   double EQEL = atof(argv[3]);
   double GLEL = atof(argv[4]);
   double GRGL = atof(argv[5]);
   double GQLGL = atof(argv[6]);
   double GQRGQL = atof(argv[7]);

   FitClass Fits;
   Fits.ClearPoints();
   int FitCount = 0;

   vector<FitResultSummary> Results;

   vector<SingleEvent> Signals;
   ReadEvents(Signals, FileName);

   vector<FitConfiguration> Configurations;
   for(int i = 1; i <= 31; i++)
   {
      if(i != 3)
         continue;

      string Gs = "NNNNNN";
      if((i / 1) % 2 == 1)    Gs[0] = 'Y';
      if((i / 2) % 2 == 1)    Gs[1] = 'Y';
      if((i / 4) % 2 == 1)    Gs[2] = 'Y';
      if((i / 8) % 2 == 1)    Gs[3] = 'Y';
      if((i / 16) % 2 == 1)   Gs[4] = 'Y';

      vector<double> GValues = ListToVector(6, 0, 0, 0, 0, 0, 0);
      /*if(Gs[0] == 'N')*/   GValues[0] = EQEL;
      /*if(Gs[1] == 'N')*/   GValues[1] = GLEL;
      /*if(Gs[2] == 'N')*/   GValues[2] = GRGL;
      /*if(Gs[3] == 'N')*/   GValues[3] = GQLGL;
      /*if(Gs[4] == 'N')*/   GValues[4] = GQRGQL;

      Configurations.push_back(FitConfiguration(Gs, GValues));
   }

   int BackgroundCounter = 0;

   ProgressBar Bar(cout, Signals.size());
   Bar.SetStyle(5);

   for(int iS = 0; iS < (int)Signals.size(); iS++)
   {
      if((iS % (Signals.size() / 300)) == 0)
      {
         Bar.Update(iS);
         Bar.Print();
      }

      Fits.AddPoint(Signals[iS]);

      if(Signals[iS].state == "em")   Fits.SignalStateCount[0] = Fits.SignalStateCount[0] + 1;
      if(Signals[iS].state == "me")   Fits.SignalStateCount[1] = Fits.SignalStateCount[1] + 1;
      if(Signals[iS].state == "ee")   Fits.SignalStateCount[2] = Fits.SignalStateCount[2] + 1;
      if(Signals[iS].state == "mm")   Fits.SignalStateCount[3] = Fits.SignalStateCount[3] + 1;
      
      if(Fits.SampleSize < DatasetSize)
         continue;

      for(int iC = 0; iC < (int)Configurations.size(); iC++)
      {
         FitResultSummary ResultTemp = Fits.DoFit(Configurations[iC]);
         Results.push_back(ResultTemp);
      }
      FitCount = FitCount + 1;

      Fits.ClearPoints();
   }

   Bar.Update(Signals.size());
   Bar.Print();
   Bar.PrintLine();

   // PsFile.AddTimeStampPage();
   // PsFile.Close();

   TFile OutputFile("OutputFile.root", "RECREATE");

   string BranchList = "";
   BranchList = BranchList + "EQEL:GLEL:GRGL:GQLGL:GQRGQL";
   BranchList = BranchList + ":EQELError:GLELError:GRGLError:GQLGLError:GQRGQLError";
   BranchList = BranchList + ":EDM:Status:Sem:Sme:See:Smm";
   BranchList = BranchList + ":RatioFloats:NFloats";
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());

   for(int i = 0; i < (int)Results.size(); i++)
   {
      float Array[100];
      Array[0] = Results[i].EQEL;      Array[5] = Results[i].EQELError;
      Array[1] = Results[i].GLEL;      Array[6] = Results[i].GLELError;
      Array[2] = Results[i].GRGL;      Array[7] = Results[i].GRGLError;
      Array[3] = Results[i].GQLGL;     Array[8] = Results[i].GQLGLError;
      Array[4] = Results[i].GQRGQL;    Array[9] = Results[i].GQRGQLError;

      Array[10] = Results[i].EDM;
      Array[11] = Results[i].FitStatus;

      Array[12] = Results[i].Sem;
      Array[13] = Results[i].Sme;
      Array[14] = Results[i].See;
      Array[15] = Results[i].Smm;

      Array[16] = 0;
      Array[17] = 0;
      
      OutputTree.Fill(Array);
   }

   OutputTree.SetMarkerStyle(20);

   OutputTree.Write();

   OutputFile.Close();

   return 0;
}

bool PassBaselineCut(EventParameters Event)
{
   LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

   if(fabs(Leptons.Lepton11.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton12.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton21.GetEta()) > 2.4)   return false;
   if(fabs(Leptons.Lepton22.GetEta()) > 2.4)   return false;

   if(max(Event.ZMass, Event.Z2Mass) < 40)   return false;
   if(min(Event.ZMass, Event.Z2Mass) < 12)   return false;

   // if(Event.ZMass < Event.Z2Mass) return false;
   
   vector<double> LPTs;
   LPTs.push_back(Leptons.Lepton11.GetPT());
   LPTs.push_back(Leptons.Lepton12.GetPT());
   LPTs.push_back(Leptons.Lepton21.GetPT());
   LPTs.push_back(Leptons.Lepton22.GetPT());
   sort(LPTs.begin(), LPTs.end());
   if(LPTs[3] < 20)    return false;
   if(LPTs[2] < 10)    return false;
   if(LPTs[1] < 7)    return false;
   if(LPTs[0] < 7)    return false;

   return true;
}

void ReadEvents(vector<SingleEvent> &Events, string FileName)
{
   TFile File(FileName.c_str());
   TTree *Tree = (TTree *)File.Get("MCTree");
   if(Tree == NULL)
      Tree = (TTree *)File.Get("Tree");
   if(Tree == NULL)
      return;

   DataHelper DHFile("Normalization.dh");

   int l1id, l3id;
   Tree->SetBranchAddress("l1id", &l1id);
   Tree->SetBranchAddress("l3id", &l3id);

   string SignalBranch[] = {"T1", "T3", "T5", "T7", "T9"};
   string BackgroundBranch[] = {"T2", "T4", "T6", "T8", "T10"};

   double Value[214] = {0};
   double Integral[214] = {0};

   string suffix[214] = {
      "000404",
      "000413",
      "000422",
      "000431",
      "000440",
      "000503",
      "000512",
      "000521",
      "000530",
      "000602",
      "000611",
      "000620",
      "001304",
      "001313",
      "001322",
      "001331",
      "001340",
      "001403",
      "001412",
      "001421",
      "001430",
      "001502",
      "001511",
      "001520",
      "002204",
      "002213",
      "002222",
      "002231",
      "002240",
      "002303",
      "002312",
      "002321",
      "002330",
      "002402",
      "002411",
      "002420",
      "003104",
      "003113",
      "003122",
      "003131",
      "003140",
      "003203",
      "003212",
      "003221",
      "003230",
      "003302",
      "003311",
      "003320",
      "004004",
      "004013",
      "004022",
      "004031",
      "004040",
      "004103",
      "004112",
      "004121",
      "004130",
      "004202",
      "004211",
      "004220",
      "005003",
      "005012",
      "005021",
      "005030",
      "005102",
      "005111",
      "005120",
      "006002",
      "006011",
      "006020",
      "110303",
      "110312",
      "110321",
      "110330",
      "110402",
      "110411",
      "110420",
      "110501",
      "110510",
      "111203",
      "111212",
      "111221",
      "111230",
      "111302",
      "111311",
      "111320",
      "111401",
      "111410",
      "112103",
      "112112",
      "112121",
      "112130",
      "112202",
      "112211",
      "112220",
      "112301",
      "112310",
      "113003",
      "113012",
      "113021",
      "113030",
      "113102",
      "113111",
      "113120",
      "113201",
      "113210",
      "114002",
      "114011",
      "114020",
      "114101",
      "114110",
      "115001",
      "115010",
      "200303",
      "200312",
      "200321",
      "200330",
      "200402",
      "200411",
      "200420",
      "201203",
      "201212",
      "201221",
      "201230",
      "201302",
      "201311",
      "201320",
      "202103",
      "202112",
      "202121",
      "202130",
      "202202",
      "202211",
      "202220",
      "203003",
      "203012",
      "203021",
      "203030",
      "203102",
      "203111",
      "203120",
      "204002",
      "204011",
      "204020",
      "220202",
      "220211",
      "220220",
      "220301",
      "220310",
      "220400",
      "221102",
      "221111",
      "221120",
      "221201",
      "221210",
      "221300",
      "222002",
      "222011",
      "222020",
      "222101",
      "222110",
      "222200",
      "223001",
      "223010",
      "223100",
      "224000",
      "310202",
      "310211",
      "310220",
      "310301",
      "310310",
      "311102",
      "311111",
      "311120",
      "311201",
      "311210",
      "312002",
      "312011",
      "312020",
      "312101",
      "312110",
      "313001",
      "313010",
      "330101",
      "330110",
      "330200",
      "331001",
      "331010",
      "331100",
      "332000",
      "400202",
      "400211",
      "400220",
      "401102",
      "401111",
      "401120",
      "402002",
      "402011",
      "402020",
      "420101",
      "420110",
      "420200",
      "421001",
      "421010",
      "421100",
      "422000",
      "440000",
      "510101",
      "510110",
      "511001",
      "511010",
      "530000",
      "620000",
      "ALL"
   };
   vector<string> Suffix(suffix, suffix + 214);

   for(int i = 0; i < 214; i++)
      Tree->SetBranchAddress(Form("Vff_%s", Suffix[i].c_str()), &Value[i]);

   double l1pt, l1eta, l1phi, l2pt, l2eta, l2phi;
   double l3pt, l3eta, l3phi, l4pt, l4eta, l4phi;
   double Weight;
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
   Tree->SetBranchAddress("Weight", &Weight);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      // if(DrawRandom(0, 1) > Weight)
      //    continue;

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      EventParameters Event = ConvertVectorsToAnglesRoberto(Leptons);

      if(Event.HMass > 135 || Event.HMass < 115)
         continue;
      if(PassBaselineCut(Event) == false)
         continue;

      if(l1id < 0)   l1id = -l1id;
      if(l3id < 0)   l3id = -l3id;

      string State = "";
      // if(l1id == 11 && l3id == 11)   State = "ee";
      if(l1id == 11 && l3id == 13)   State = "em";
      if(l1id == 13 && l3id == 11)   State = "em";
      // if(l1id == 13 && l3id == 13)   State = "mm";
      
      string DHState = State;
      if(State == "em")
         DHState = "TightCutEM";

      if(State == "")   // WTF
         continue;
      else
      {
         for(int i = 0; i < 214; i++)
         {
            char BranchSuffix[100] = "";
            sprintf(BranchSuffix, "_%03d", i + 1);
            string Branch = SignalBranch[0] + BranchSuffix;
            Integral[i] = DHFile[DHState][Branch].GetDouble();

            // cout << i << " " << Value[i] << " " << Integral[i] << endl;
         }
      }
      // cout << Value[213] << endl;

      bool Good = true;
      for(int i = 0; i < 214; i++)
         if(Value[i] != Value[i] || Value[i] > 0.99)
            Good = false;
      if(Good == false)
         continue;

      SingleEvent NewEvent;

      for(int i = 0; i < 214; i++)
         NewEvent.v[i] = Value[i];
      for(int i = 0; i < 214; i++)
         NewEvent.i[i] = Integral[i];
      NewEvent.event = Event;
      NewEvent.state = State;

      Events.push_back(NewEvent);
   }
   
   File.Close();

   random_shuffle(Events.begin(), Events.end());

   cout << "Events read: " << Events.size() << endl;
}



