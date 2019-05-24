#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TDirectory.h"

#include "Code/TauHelperFunctions3.h"
#include "SetStyle.h"
#include "CommandLine.h"
#include "ProgressBar.h"
#include "CustomAssert.h"

#include "Messenger.h"

class Configuration;
int main(int argc, char *argv[]);
vector<Configuration> ReadConfigFile(string FileName);

class Configuration
{
public:
   string InputObject;
   string Directory;
   string ReferenceObject;
   double AbsEtaMin;
   double AbsEtaMax;
   double ReferenceIsolation;
   string Quality;
   double DRCut;
   string Type;
   double IsolationBB, IsolationEC;
   string HistogramName;
   int Bin1, Bin2, Bin3, Bin4;
   double Min1, Min2, Min3, Min4;
   double Max1, Max2, Max3, Max4;
   string ThresholdPreset;
   bool Valid;
public:
   Configuration()
   {
      Valid = false;
   }
   Configuration(string Input)
   {
      Valid = false;
      Parse(Input);
   }
   vector<string> BreakIntoPieces(string Input)
   {
      stringstream str(Input);
      vector<string> Result;

      while(str)
      {
         string Temp = "";
         str >> Temp;
         if(Temp == "")
            continue;
         Result.push_back(Temp);
      }

      return Result;
   }
   void Parse(string Input)
   {
      Valid = false;

      vector<string> Parts = BreakIntoPieces(Input);

      if(Parts.size() != 25)
         return;
      if(Parts[0] == "Input")
         return;
      if(Parts[0] == "Comment")
         return;
      if(Parts[0] == "")
         return;
      if(Parts[0][0] == '#')
         return;

      Valid = true;

      InputObject = Parts[0];
      Directory = Parts[1];
      ReferenceObject = Parts[2];
      AbsEtaMin = atof(Parts[3].c_str());
      AbsEtaMax = atof(Parts[4].c_str());
      ReferenceIsolation = atof(Parts[5].c_str());
      Quality = Parts[6];
      DRCut = atof(Parts[7].c_str());
      Type = Parts[8];
      IsolationBB = atof(Parts[9].c_str());
      IsolationEC = atof(Parts[10].c_str());
      HistogramName = Parts[11];
      Bin1 = atoi(Parts[12].c_str());
      Min1 = atof(Parts[13].c_str());
      Max1 = atof(Parts[14].c_str());
      Bin2 = atoi(Parts[15].c_str());
      Min2 = atof(Parts[16].c_str());
      Max2 = atof(Parts[17].c_str());
      Bin3 = atoi(Parts[18].c_str());
      Min3 = atof(Parts[19].c_str());
      Max3 = atof(Parts[20].c_str());
      Bin4 = atoi(Parts[21].c_str());
      Min4 = atof(Parts[22].c_str());
      Max4 = atof(Parts[23].c_str());
      ThresholdPreset = Parts[24];
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   // Some root styling
   SetThesisStyle();

   // Get arguments
   vector<string> InputFileNames = CL.GetStringVector("input", ',');
   string OutputFileName         = CL.Get("output");

   // Output file
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree OutputTree("Tree", "Tree");
   
   double TreeMuonPT, TreeMuonEta, TreeMuonPhi, TreeMuonDxy;
   OutputTree.Branch("MuonPT", &TreeMuonPT, "MuonPT/D");
   OutputTree.Branch("MuonEta", &TreeMuonEta, "MuonEta/D");
   OutputTree.Branch("MuonPhi", &TreeMuonPhi, "MuonPhi/D");
   OutputTree.Branch("MuonDxy", &TreeMuonDxy, "MuonDxy/D");
   
   double TreeL1PT, TreeL1Eta, TreeL1Phi, TreeL1Dxy;
   OutputTree.Branch("L1PT", &TreeL1PT, "L1PT/D");
   OutputTree.Branch("L1Eta", &TreeL1Eta, "L1Eta/D");
   OutputTree.Branch("L1Phi", &TreeL1Phi, "L1Phi/D");
   OutputTree.Branch("L1Dxy", &TreeL1Dxy, "L1Dxy/D");

   for(string InputFileName : InputFileNames)
   {
      cout << "Processing file " << InputFileName << endl;

      // Input File
      TFile File(InputFileName.c_str());

      // Messengers
      L1GenMessenger MGen(File, "genTree/L1GenTree");
      L1PhaseIITreeV7p52Messenger MPhaseII(File, "l1PhaseIITree/L1PhaseIITree");

      if(MGen.Tree == nullptr || MPhaseII.Tree == nullptr)
         continue;

      // Loop over events
      int EntryCount = MGen.Tree->GetEntries();
      ProgressBar Bar(cout, EntryCount);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Bar.Update(iE);
         Bar.Print();

         MGen.GetEntry(iE);
         MPhaseII.GetEntry(iE);

         vector<int> MuonIndex;

         for(int i = 0; i < MGen.GenP.size(); i++)
         {
            // We want a gen muon to start with
            if(MGen.GenID[i] != 13 && MGen.GenID[i] != -13)
               continue;

            MuonIndex.push_back(i);
         }

         if(MuonIndex.size() == 0)
            continue;

         int BestMuonIndex = MuonIndex[0];
         for(int i = 1; i < (int)MuonIndex.size(); i++)
            if(MGen.GenP[MuonIndex[i]].GetPT() > MGen.GenP[BestMuonIndex].GetPT())
               BestMuonIndex = i;

         TreeMuonPT = MGen.GenP[BestMuonIndex].GetPT();
         TreeMuonEta = MGen.GenP[BestMuonIndex].GetEta();
         TreeMuonPhi = MGen.GenP[BestMuonIndex].GetPhi();
         TreeMuonDxy = MGen.GenDxy[BestMuonIndex];

         if(MPhaseII.StandaloneDisplacedMuon.size() == 0)
            continue;

         GenericObject BestL1Muon;
         BestL1Muon.P[0] = -1;
         for(int i = 0; i < (int)MPhaseII.StandaloneDisplacedMuon.size(); i++)
         {
            GenericObject M = MPhaseII.StandaloneDisplacedMuon[i];

            if(GetDR(M.P, MGen.GenP[BestMuonIndex]) > 0.3)
               continue;

            if(BestL1Muon.P[0] < 0 || BestL1Muon.P.GetPT() < M.P.GetPT())
               BestL1Muon = M;
         }

         TreeL1PT = BestL1Muon.P.GetPT();
         TreeL1Eta = BestL1Muon.P.GetEta();
         TreeL1Phi = BestL1Muon.P.GetPhi();
         TreeL1Dxy = BestL1Muon.DXY;

         OutputTree.Fill();
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   // Close stuff
   OutputFile.cd();
   OutputTree.Write();
   OutputFile.Close();

   // Yay
   return 0;
}

vector<Configuration> ReadConfigFile(string FileName)
{
   vector<Configuration> Result;

   ifstream in(FileName);

   while(in)
   {
      char ch[10240];
      ch[0] = '\0';
      in.getline(ch, 10239, '\n');

      Configuration C(ch);
      if(C.Valid == true)
         Result.push_back(C);
   }

   in.close();

   return Result;
}





