#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "fastjet/ClusterSequence.hh"

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

#include "Histograms.h"
#include "HelperFunctions.h"

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
   double PTMin;
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

      if(Parts.size() != 26)
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
      PTMin = atof(Parts[5].c_str());
      ReferenceIsolation = atof(Parts[6].c_str());
      Quality = Parts[7];
      DRCut = atof(Parts[8].c_str());
      Type = Parts[9];
      IsolationBB = atof(Parts[10].c_str());
      IsolationEC = atof(Parts[11].c_str());
      HistogramName = Parts[12];
      Bin1 = atoi(Parts[13].c_str());
      Min1 = atof(Parts[14].c_str());
      Max1 = atof(Parts[15].c_str());
      Bin2 = atoi(Parts[16].c_str());
      Min2 = atof(Parts[17].c_str());
      Max2 = atof(Parts[18].c_str());
      Bin3 = atoi(Parts[19].c_str());
      Min3 = atof(Parts[20].c_str());
      Max3 = atof(Parts[21].c_str());
      Bin4 = atoi(Parts[22].c_str());
      Min4 = atof(Parts[23].c_str());
      Max4 = atof(Parts[24].c_str());
      ThresholdPreset = Parts[25];
   }
};

int main(int argc, char *argv[])
{
   fastjet::ClusterSequence::set_fastjet_banner_stream(NULL);

   CommandLine CL(argc, argv);

   // Some root styling
   SetThesisStyle();

   // Get arguments
   vector<string> InputFileNames = CL.GetStringVector("input", ',');
   string OutputFileName         = CL.Get("output");
   bool UseStoredGen             = CL.GetBool("StoredGen", true);
   string ConfigFileName         = CL.Get("config");
   bool LDROnly                  = CL.GetBool("LDROnly", false);
   bool RejectLeptonicW          = CL.GetBool("RejectLeptonicW", false);

   vector<Configuration> Configurations = ReadConfigFile(ConfigFileName);
   int N = Configurations.size();

   if(LDROnly == true)
   {
      for(int i = 0; i < (int)Configurations.size(); i++)
      {
         if(Configurations[i].Directory.find("LDR") == string::npos)
         {
            Configurations.erase(Configurations.begin() + i);
            i = i - 1;
         }
      }
      N = Configurations.size();
   }

   // Output File and directories for better organization
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   vector<TDirectory *> Directories;
   for(int i = 0; i < N; i++)
      Directories.push_back(OutputFile.mkdir(Configurations[i].Directory.c_str(), ""));

   // Create histograms
   vector<double> GenThresholds = {0};
   vector<double> JetThresholds = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70,
      75, 80, 85, 90, 100, 120, 125, 130, 140, 150, 175, 200, 225, 250, 275, 300};
   vector<double> MuonThresholds = {0, 2, 3, 4, 5, 7, 9, 10, 12, 14, 15, 17, 20, 22, 25, 27, 30};
   vector<double> TauThresholds = {0, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30, 33, 35, 36, 40, 46, 50, 58, 60, 70, 80, 90, 100};
   vector<double> EGThresholds = {0, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30, 40, 50};
   vector<double> HTThresholds = {0, 10, 20, 30, 40, 50, 60, 70, 80, 82, 90, 100, 112, 125, 150,
      175, 184, 200, 225, 250, 300, 325, 326, 350, 370, 375, 400, 425, 450, 475, 500, 550, 600, 650};
   
   vector<Histograms *> ObjectHistograms;
   for(int i = 0; i < N; i++)
   {
      vector<double> Thresholds;
      if(Configurations[i].ThresholdPreset == "Gen")
         Thresholds = GenThresholds;
      if(Configurations[i].ThresholdPreset == "Jet")
         Thresholds = JetThresholds;
      if(Configurations[i].ThresholdPreset == "Muon")
         Thresholds = MuonThresholds;
      if(Configurations[i].ThresholdPreset == "Tau")
         Thresholds = TauThresholds;
      if(Configurations[i].ThresholdPreset == "EG")
         Thresholds = EGThresholds;
      if(Configurations[i].ThresholdPreset == "HT")
         Thresholds = HTThresholds;

      Histograms *H = new Histograms
         (Configurations[i].Bin1, Configurations[i].Min1, Configurations[i].Max1,
          Configurations[i].Bin2, Configurations[i].Min2, Configurations[i].Max2,
          Configurations[i].Bin3, Configurations[i].Min3, Configurations[i].Max3,
          Configurations[i].Bin4, Configurations[i].Min4, Configurations[i].Max4,
          Thresholds, Configurations[i].HistogramName);
      ObjectHistograms.push_back(H);
   }

   for(string InputFileName : InputFileNames)
   {
      cout << "Processing file " << InputFileName << endl;

      // Input File
      TFile File(InputFileName.c_str());

      // Messengers
      L1GenMessenger MGen(File, "genTree/L1GenTree");
      L1PhaseIITreeV11p1Messenger MPhaseII(File, "l1PhaseIITree/L1PhaseIITree");

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

         bool LeptonicW = CheckLeptonicW(MGen);
         if(RejectLeptonicW == true && LeptonicW == true)
            continue;

         vector<FourVector> Electrons;
         vector<FourVector> ZElectrons;
         vector<FourVector> Photons;
         vector<FourVector> Muons;
         vector<int> MuonSigns;
         vector<double> MuonDXY;
         vector<FourVector> MuonLxy1000s;
         vector<int> MuonSignLxy1000s;
         vector<double> MuonDXYLxy1000;
         vector<FourVector> Taus, VisTaus;
         vector<FourVector> ChargedParticles;
         vector<FourVector> Particles;

         // Collect gen-particles
         for(int i = 0; i < (int)MGen.GenP.size(); i++)
         {
            int AbsID = MGen.GenID[i];
            if(AbsID < 0)
               AbsID = -AbsID;

            if(AbsID == 12 || AbsID == 14 || AbsID == 16)
               continue;

            if(AbsID == 11)
               Electrons.push_back(MGen.GenP[i]);
            if(AbsID == 11 && MGen.GenParent[i] == 23)   // electron from Z
               ZElectrons.push_back(MGen.GenP[i]);
            if(AbsID == 22)
               Photons.push_back(MGen.GenP[i]);
            if(AbsID == 13)
            {
               Muons.push_back(MGen.GenP[i]);
               MuonSigns.push_back((MGen.GenID[i] > 0) ? -1 : 1);
               MuonDXY.push_back(fabs(MGen.GenDxy[i]));

               if(fabs(MGen.GenLxy[i]) < 100)   // 1 meter
               {
                  MuonLxy1000s.push_back(MGen.GenP[i]);
                  MuonSignLxy1000s.push_back((MGen.GenID[i] > 0) ? -1 : 1);
                  MuonDXYLxy1000.push_back(fabs(MGen.GenDxy[i]));
               }
            }
            if(AbsID == 15)
            {
               FourVector P = GetVisTauAdhoc(MGen, i);
               if(P[0] > 0)
                  VisTaus.push_back(P);
               Taus.push_back(MGen.GenP[i]);
            }

            if(MGen.GenStatus[i] == 1)   // we only want final state particles here
               Particles.push_back(MGen.GenP[i]);
            if(MGen.GenStatus[i] == 1 && MGen.GenCharge[i] != 0)
               ChargedParticles.push_back(MGen.GenP[i]);
         }

         // Cluster jets
         vector<FourVector> GenJets        = (UseStoredGen ? MGen.GenJet : ClusterJets(Particles));
         vector<FourVector> ChargedGenJets = ClusterJets(ChargedParticles);
         
         // Gather MET
         FourVector GenMETForPuppi    = (UseStoredGen ? MGen.GenMETTrue : CalculateMHT(Particles, 2.4, 0));
         FourVector GenMETForTk       = CalculateMHT(ChargedParticles, 2.4, 0);

         vector<FourVector> ReferenceObjects;
         vector<double> ReferenceDXY;
         vector<int> ReferenceSigns;
         for(int i = 0; i < N; i++)
         {
            FourVector Best(-1, 0, 0, 0);
            int BestSign = -999;
            int BestDXY = 0;

            Configuration &C = Configurations[i];

            if(C.ReferenceObject == "GenJet")
               Best = BestInRange(GenJets, C.AbsEtaMin, C.AbsEtaMax, -1);
            else if(C.ReferenceObject == "ChargedGenJet")
               Best = BestInRange(ChargedGenJets, C.AbsEtaMin, C.AbsEtaMax, -1);
            else if(C.ReferenceObject == "Electron")
               Best = BestInRange(Electrons, C.AbsEtaMin, C.AbsEtaMax, -1);
            else if(C.ReferenceObject == "ZElectron")
               Best = BestInRange(ZElectrons, C.AbsEtaMin, C.AbsEtaMax, -1);
            else if(C.ReferenceObject == "Photon")
               Best = BestInRange(Photons, C.AbsEtaMin, C.AbsEtaMax, -1);
            else if(C.ReferenceObject == "Muon")
            {
               Best = BestInRange(Muons, C.AbsEtaMin, C.AbsEtaMax, -1);
               int BestIndex = BestIndexInRange(Muons, C.AbsEtaMin, C.AbsEtaMax, -1);
               if(BestIndex < 0)   BestSign = -999;
               else                BestSign = MuonSigns[BestIndex];
               if(BestIndex < 0)   BestDXY = 0;
               else                BestDXY = MuonDXY[BestIndex];
            }
            else if(C.ReferenceObject == "MuonLxy1000")
            {
               Best = BestInRange(MuonLxy1000s, C.AbsEtaMin, C.AbsEtaMax, -1);
               int BestIndex = BestIndexInRange(MuonLxy1000s, C.AbsEtaMin, C.AbsEtaMax, -1);
               if(BestIndex < 0)   BestSign = -999;
               else                BestSign = MuonSignLxy1000s[BestIndex];
               if(BestIndex < 0)   BestDXY = 0;
               else                BestDXY = MuonDXYLxy1000[BestIndex];
            }
            else if(C.ReferenceObject == "VisTau")
               Best = BestInRange(VisTaus, C.AbsEtaMin, C.AbsEtaMax, -1);
            else if(C.ReferenceObject == "Tau")
               Best = BestInRange(Taus, C.AbsEtaMin, C.AbsEtaMax, -1);
            else if(C.ReferenceObject == "HT5")
               Best = CalculateHT(GenJets, 2.4, 5);
            else if(C.ReferenceObject == "MHT5")
               Best = CalculateMHT(GenJets, 2.4, 5);
            else if(C.ReferenceObject == "HT10")
               Best = CalculateHT(GenJets, 2.4, 10);
            else if(C.ReferenceObject == "MHT10")
               Best = CalculateMHT(GenJets, 2.4, 10);
            else if(C.ReferenceObject == "HT15")
               Best = CalculateHT(GenJets, 2.4, 15);
            else if(C.ReferenceObject == "HT15Eta35")
               Best = CalculateHT(GenJets, 3.5, 15);
            else if(C.ReferenceObject == "MHT15")
               Best = CalculateMHT(GenJets, 2.4, 15);
            else if(C.ReferenceObject == "MHT15Eta35")
               Best = CalculateMHT(GenJets, 3.5, 15);
            else if(C.ReferenceObject == "HT20")
               Best = CalculateHT(GenJets, 2.4, 20);
            else if(C.ReferenceObject == "HT20Eta35")
               Best = CalculateHT(GenJets, 3.5, 20);
            else if(C.ReferenceObject == "MHT20")
               Best = CalculateMHT(GenJets, 2.4, 20);
            else if(C.ReferenceObject == "MHT20Eta35")
               Best = CalculateMHT(GenJets, 3.5, 20);
            else if(C.ReferenceObject == "HT30")
               Best = CalculateHT(GenJets, 2.4, 30);
            else if(C.ReferenceObject == "HT30Eta35")
               Best = CalculateHT(GenJets, 3.5, 30);
            else if(C.ReferenceObject == "MHT30")
               Best = CalculateMHT(GenJets, 2.4, 30);
            else if(C.ReferenceObject == "MHT30Eta35")
               Best = CalculateMHT(GenJets, 3.5, 30);
            else if(C.ReferenceObject == "MET")
               Best = (UseStoredGen ? MGen.GenMETTrue : CalculateMHT(Particles, 2.4, 0));
            else if(C.ReferenceObject == "ChargedHT5")
               Best = CalculateHT(ChargedGenJets, 2.4, 5);
            else if(C.ReferenceObject == "ChargedMHT5")
               Best = CalculateMHT(ChargedGenJets, 2.4, 5);
            else if(C.ReferenceObject == "ChargedHT10")
               Best = CalculateHT(ChargedGenJets, 2.4, 10);
            else if(C.ReferenceObject == "ChargedMHT10")
               Best = CalculateMHT(ChargedGenJets, 2.4, 10);
            else if(C.ReferenceObject == "ChargedHT15")
               Best = CalculateHT(ChargedGenJets, 2.4, 15);
            else if(C.ReferenceObject == "ChargedMHT15")
               Best = CalculateMHT(ChargedGenJets, 2.4, 15);
            else if(C.ReferenceObject == "ChargedHT20")
               Best = CalculateHT(ChargedGenJets, 2.4, 20);
            else if(C.ReferenceObject == "ChargedMHT20")
               Best = CalculateMHT(ChargedGenJets, 2.4, 20);
            else if(C.ReferenceObject == "ChargedHT30")
               Best = CalculateHT(ChargedGenJets, 2.4, 30);
            else if(C.ReferenceObject == "ChargedMHT30")
               Best = CalculateMHT(ChargedGenJets, 2.4, 30);
            else if(C.ReferenceObject == "ChargedMET")
               Best = CalculateMHT(ChargedParticles, 2.4, 0);
         
            if(C.ReferenceIsolation > 0)
            {
               double Isolation = CalculateGenIsolation(Best, Particles, 0.3);
               if(Isolation > C.ReferenceIsolation)
                  Best = FourVector(-1, 0, 0, 0);
            }

            ReferenceObjects.push_back(Best);
            ReferenceSigns.push_back(BestSign);
            ReferenceDXY.push_back(BestDXY);
         }

         // Find best L1 objects
         vector<GenericObject> L1Objects;

         for(int i = 0; i < N; i++)
         {
            Configuration &C = Configurations[i];
            FourVector &Ref = ReferenceObjects[i];

            int Quality = QUAL_NONE;
            if(C.Quality == "None")
               Quality = QUAL_NONE;
            else if(C.Quality == "Odd")
               Quality = QUAL_ODD;
            else if(C.Quality == "Twelve")
               Quality = QUAL_12;
            else if(C.Quality == "OverlapTwelve")
               Quality = QUAL_OVERLAP12;
            else if(C.Quality == "OverlapTwelveEndcapOne")
               Quality = QUAL_OVERLAP12ENDCAP1;
            else if(C.Quality == "EndcapOne")
               Quality = QUAL_ENDCAP1;
            else if(C.Quality == "TwelveDXYOne")
               Quality = QUAL_12_DXY1;
            else if(C.Quality == "DXYOne")
               Quality = QUAL_DXY1;
            else if(C.Quality == "BarrelOddEndcapTwo")
               Quality = QUAL_BARRELODDENDCAP2;
            else if(C.Quality == "BarrelNoneEndcapTwo")
               Quality = QUAL_BARRELNONEENDCAP2;
            else if(C.Quality == "BarrelNoneEndcapThree")
               Quality = QUAL_BARRELNONEENDCAP3;
            else if(C.Quality == "BarrelNoneEndcapFive")
               Quality = QUAL_BARRELNONEENDCAP5;
            else if(C.Quality == "UseFlag")
               Quality = QUAL_USEFLAG;
            else if(C.Quality == "RegionNotFour")
               Quality = QUAL_REGIONNOTFOUR;
            else
               Quality = atoi(C.Quality.c_str());

            int Range = atoi(C.Type.c_str());

            GenericObject Best;

            if(C.InputObject == "Gen")
               Best.P = ReferenceObjects[i];
            else if(C.InputObject == "CaloTau")
               Best = BestInRange(MPhaseII.CaloTau, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "PFPhase1Jet")
               Best = BestInRange(MPhaseII.PFPhase1Jet, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "PFPhase1HT0" && MPhaseII.PFPhase1HT.size() > 0)
               Best = MPhaseII.PFPhase1HT[0];
            else if(C.InputObject == "PFPhase1MHT0" && MPhaseII.PFPhase1MHT.size() > 0)
               Best = MPhaseII.PFPhase1MHT[0];
            else if(C.InputObject == "EG")
               Best = BestInRange(MPhaseII.EG, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "EGTrackID")
               Best = BestInRange(MPhaseII.EGTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkElectron")
               Best = BestInRange(MPhaseII.TkElectron, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkElectronTrackID")
               Best = BestInRange(MPhaseII.TkElectronTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkPhoton")
               Best = BestInRange(MPhaseII.TkPhoton, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkPhotonTrackID")
               Best = BestInRange(MPhaseII.TkPhotonTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkPhotonPVTrackID")
               Best = BestInRange(MPhaseII.TkPhotonPVTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "StandaloneMuon")
               Best = BestInRange(MPhaseII.StandaloneMuon, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkMuon")
               Best = BestInRange(MPhaseII.TkMuon, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "PuppiMET" && MPhaseII.PuppiMET.size() > 0)
               Best = MPhaseII.PuppiMET[0];
            else if(C.InputObject == "NNTau")
               Best = BestInRange(MPhaseII.NNTau, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "NNTauLoose")
               Best = BestInRange(MPhaseII.NNTauLoose, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "NNTauPF")
               Best = BestInRange(MPhaseII.NNTauPF, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "NNTauLoosePF")
               Best = BestInRange(MPhaseII.NNTauLoosePF, Ref, C.AbsEtaMin, C.AbsEtaMax, C.PTMin, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);

            L1Objects.push_back(Best);
         }

         // for(int i = 0; i < N; i++)
         //    if(Configurations[i].InputObject == "TkMuon")
         //       cerr << ReferenceObjects[i] << " " << ReferenceSigns[i] << " " << L1Objects[i].Charge << endl;

         // Fill Histograms
         for(int i = 0; i < N; i++)
            FillHistograms(ObjectHistograms[i], L1Objects[i].P, ReferenceObjects[i], L1Objects[i].Iso, L1Objects[i].Type, ReferenceDXY[i]);
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   // Write result to file
   for(int i = 0; i < N; i++)
      ObjectHistograms[i]->Write(Directories[i]);

   // Clean up
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





