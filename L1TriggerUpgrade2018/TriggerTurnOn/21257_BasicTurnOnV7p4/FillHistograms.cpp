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
   fastjet::ClusterSequence::set_fastjet_banner_stream(NULL);

   CommandLine CL(argc, argv);

   // Some root styling
   SetThesisStyle();

   // Get arguments
   vector<string> InputFileNames = CL.GetStringVector("input", ',');
   string OutputFileName         = CL.Get("output");
   bool UseStoredGen             = CL.GetBool("StoredGen", true);
   bool DoChargedJet             = CL.GetBool("DoCharged", false);
   string ConfigFileName         = CL.Get("config");

   vector<Configuration> Configurations = ReadConfigFile(ConfigFileName);
   int N = Configurations.size();

   // Output File and directories for better organization
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   vector<TDirectory *> Directories;
   for(int i = 0; i < N; i++)
      Directories.push_back(OutputFile.mkdir(Configurations[i].Directory.c_str(), ""));

   // Create histograms
   vector<double> GenThresholds = {0};
   vector<double> JetThresholds = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60,
      75, 80, 85, 90, 100, 125, 150, 175, 200, 225, 250, 275, 300};
   vector<double> MuonThresholds = {0, 3, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30};
   vector<double> TauThresholds = {0, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30, 40, 50, 60, 70, 80, 90, 100};
   vector<double> EGThresholds = {0, 5, 7, 9, 12, 14, 15, 17, 20, 22, 25, 27, 30};
   vector<double> HTThresholds = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 125, 150,
      175, 200, 225, 250, 300, 325, 350, 375, 400, 425, 450, 475, 500};
   
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
      L1PhaseIITreeV7p4Messenger MPhaseII(File, "l1PhaseIITree/L1PhaseIITree");

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

         vector<FourVector> Electrons;
         vector<FourVector> Photons;
         vector<FourVector> Muons;
         vector<int> MuonSigns;
         vector<FourVector> Taus;
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
            if(AbsID == 22)
               Photons.push_back(MGen.GenP[i]);
            if(AbsID == 13)
            {
               Muons.push_back(MGen.GenP[i]);
               MuonSigns.push_back((MGen.GenID[i] > 0) ? -1 : 1);
            }
            if(AbsID == 15)
            {
               FourVector P = GetVisTauAdhoc(MGen, i);
               if(P[0] > 0)
                  Taus.push_back(P);
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
         FourVector GenMETForTk       = (DoChargedJet ? CalculateMHT(ChargedParticles, 2.4, 0) : GenMETForPuppi);

         vector<FourVector> ReferenceObjects;
         vector<int> ReferenceSigns;
         for(int i = 0; i < N; i++)
         {
            FourVector Best(-1, 0, 0, 0);
            int BestSign = -999;

            if(Configurations[i].ReferenceObject == "GenJet")
               Best = BestInRange(GenJets, Configurations[i].AbsEtaMin, Configurations[i].AbsEtaMax);
            else if(Configurations[i].ReferenceObject == "ChargedGenJet")
               Best = BestInRange(ChargedGenJets, Configurations[i].AbsEtaMin, Configurations[i].AbsEtaMax);
            else if(Configurations[i].ReferenceObject == "Electron")
               Best = BestInRange(Electrons, Configurations[i].AbsEtaMin, Configurations[i].AbsEtaMax);
            else if(Configurations[i].ReferenceObject == "Photon")
               Best = BestInRange(Photons, Configurations[i].AbsEtaMin, Configurations[i].AbsEtaMax);
            else if(Configurations[i].ReferenceObject == "Muon")
            {
               Best = BestInRange(Muons, Configurations[i].AbsEtaMin, Configurations[i].AbsEtaMax);
               int BestIndex = BestIndexInRange(Muons, Configurations[i].AbsEtaMin, Configurations[i].AbsEtaMax);
               if(BestIndex < 0)   BestSign = -999;
               else                BestSign = MuonSigns[BestIndex];
            }
            else if(Configurations[i].ReferenceObject == "Tau")
               Best = BestInRange(Taus, Configurations[i].AbsEtaMin, Configurations[i].AbsEtaMax);
            else if(Configurations[i].ReferenceObject == "HT15")
               Best = CalculateHT(GenJets, 2.4, 15);
            else if(Configurations[i].ReferenceObject == "MHT15")
               Best = CalculateMHT(GenJets, 2.4, 15);
            else if(Configurations[i].ReferenceObject == "HT20")
               Best = CalculateHT(GenJets, 2.4, 20);
            else if(Configurations[i].ReferenceObject == "MHT20")
               Best = CalculateMHT(GenJets, 2.4, 20);
            else if(Configurations[i].ReferenceObject == "HT30")
               Best = CalculateHT(GenJets, 2.4, 30);
            else if(Configurations[i].ReferenceObject == "MHT30")
               Best = CalculateMHT(GenJets, 2.4, 30);
            else if(Configurations[i].ReferenceObject == "MET")
               Best = (UseStoredGen ? MGen.GenMETTrue : CalculateMHT(Particles, 2.4, 0));
            else if(Configurations[i].ReferenceObject == "TkHT5")
               Best = CalculateHT((DoChargedJet ? ChargedGenJets : GenJets), 2.4, 5);
            else if(Configurations[i].ReferenceObject == "TkMHT5")
               Best = CalculateMHT((DoChargedJet ? ChargedGenJets : GenJets), 2.4, 5);
            else if(Configurations[i].ReferenceObject == "TkHT10")
               Best = CalculateHT((DoChargedJet ? ChargedGenJets : GenJets), 2.4, 10);
            else if(Configurations[i].ReferenceObject == "TkMHT10")
               Best = CalculateMHT((DoChargedJet ? ChargedGenJets : GenJets), 2.4, 10);
            else if(Configurations[i].ReferenceObject == "TkHT15")
               Best = CalculateHT((DoChargedJet ? ChargedGenJets : GenJets), 2.4, 15);
            else if(Configurations[i].ReferenceObject == "TkMHT15")
               Best = CalculateMHT((DoChargedJet ? ChargedGenJets : GenJets), 2.4, 15);
            else if(Configurations[i].ReferenceObject == "TkHT20")
               Best = CalculateHT((DoChargedJet ? ChargedGenJets : GenJets), 2.4, 20);
            else if(Configurations[i].ReferenceObject == "TkMHT20")
               Best = CalculateMHT((DoChargedJet ? ChargedGenJets : GenJets), 2.4, 20);
            else if(Configurations[i].ReferenceObject == "TkHT30")
               Best = CalculateHT((DoChargedJet ? ChargedGenJets : GenJets), 2.4, 30);
            else if(Configurations[i].ReferenceObject == "TkMHT30")
               Best = CalculateMHT((DoChargedJet ? ChargedGenJets : GenJets), 2.4, 30);
            else if(Configurations[i].ReferenceObject == "TkMET")
               Best = (DoChargedJet ? CalculateMHT(ChargedParticles, 2.4, 0) : GenMETForPuppi);
         
            if(Configurations[i].ReferenceIsolation > 0)
            {
               double Isolation = CalculateGenIsolation(Best, Particles, 0.3);
               if(Isolation > Configurations[i].ReferenceIsolation)
                  Best = FourVector(-1, 0, 0, 0);
            }

            ReferenceObjects.push_back(Best);
            ReferenceSigns.push_back(BestSign);
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
            else if(C.Quality == "TwelveDXYOne")
               Quality = QUAL_12_DXY1;
            else if(C.Quality == "BarrelOddEndcapTwo")
               Quality = QUAL_BARRELODDENDCAP2;
            else if(C.Quality == "BarrelNoneEndcapTwo")
               Quality = QUAL_BARRELNONEENDCAP2;
            else if(C.Quality == "UseFlag")
               Quality = QUAL_USEFLAG;
            else
               Quality = atoi(C.Quality.c_str());

            int Range = atoi(C.Type.c_str());

            GenericObject Best;

            if(C.InputObject == "Gen")
               Best.P = ReferenceObjects[i];
            else if(C.InputObject == "Jet")
               Best = BestInRange(MPhaseII.Jet, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TrackerJet")
               Best = BestInRange(MPhaseII.TrackerJet, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkCaloJet")
               Best = BestInRange(MPhaseII.TkCaloJet, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "PuppiJet")
               Best = BestInRange(MPhaseII.PuppiJet, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "CaloJet")
               Best = BestInRange(MPhaseII.CaloJet, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "GlobalMuon")
               Best = BestInRange(MPhaseII.GlobalMuon, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "StandaloneMuon")
               Best = BestInRange(MPhaseII.StandaloneMuon, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "StandaloneDisplacedMuon")
               Best = BestInRange(MPhaseII.StandaloneDisplacedMuon, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkMuon")
               Best = BestInRange(MPhaseII.TkMuon, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkMuonStub")
               Best = BestInRange(MPhaseII.TkMuonStub, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkGlbMuon")
               Best = BestInRange(MPhaseII.TkGlbMuon, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "PFMuon")
               Best = BestInRange(MPhaseII.PFMuon, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "EG")
            {
               Best = BestInRange(MPhaseII.EG, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
               if(Best.P[0] < 0)
                  Best.Type = ((Ref.GetAbsEta() < 1.5) ? 0 : 1);
            }
            else if(C.InputObject == "EGTrackID")
            {
               Best = BestInRange(MPhaseII.EGTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
               if(Best.P[0] < 0)
                  Best.Type = ((Ref.GetAbsEta() < 1.5) ? 0 : 1);
            }
            else if(C.InputObject == "TkElectron")
            {
               Best = BestInRange(MPhaseII.TkElectron, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
               if(Best.P[0] < 0)
                  Best.Type = ((Ref.GetAbsEta() < 1.5) ? 0 : 1);
            }
            else if(C.InputObject == "TkElectronTrackID")
            {
               Best = BestInRange(MPhaseII.TkElectronTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
               if(Best.P[0] < 0)
                  Best.Type = ((Ref.GetAbsEta() < 1.5) ? 0 : 1);
            }
            else if(C.InputObject == "TkElectronLoose")
            {
               Best = BestInRange(MPhaseII.TkElectronLoose, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
               if(Best.P[0] < 0)
                  Best.Type = ((Ref.GetAbsEta() < 1.5) ? 0 : 1);
            }
            else if(C.InputObject == "TkElectronLooseTrackID")
            {
               Best = BestInRange(MPhaseII.TkElectronLooseTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
               if(Best.P[0] < 0)
                  Best.Type = ((Ref.GetAbsEta() < 1.5) ? 0 : 1);
            }
            else if(C.InputObject == "TkPhoton")
            {
               Best = BestInRange(MPhaseII.TkPhoton, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
               if(Best.P[0] < 0)
                  Best.Type = ((Ref.GetAbsEta() < 1.5) ? 0 : 1);
            }
            else if(C.InputObject == "TkPhotonTrackID")
            {
               Best = BestInRange(MPhaseII.TkPhotonTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
               if(Best.P[0] < 0)
                  Best.Type = ((Ref.GetAbsEta() < 1.5) ? 0 : 1);
            }
            else if(C.InputObject == "TkPhotonPVTrackID")
            {
               Best = BestInRange(MPhaseII.TkPhotonPVTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
               if(Best.P[0] < 0)
                  Best.Type = ((Ref.GetAbsEta() < 1.5) ? 0 : 1);
            }
            else if(C.InputObject == "TkElectronPV")
            {
               double IsoBB, IsoEC;
               IsoBB = (C.IsolationBB < 0) ? -1 : 0.12;
               IsoEC = (C.IsolationEC < 0) ? -1 : 0.40;
               Best = BestInRange(MPhaseII.TkElectronTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, QUAL_USEFLAG, Range, IsoBB, IsoEC);

               if(Best.P[0] < 0)
               {
                  IsoBB = (C.IsolationBB < 0) ? -1 : 0.06;
                  IsoEC = (C.IsolationEC < 0) ? -1 : 0.09;
                  Best = BestInRange(MPhaseII.TkPhotonPVTrackID, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, QUAL_USEFLAG, Range, IsoBB, IsoEC);
               }

               if(Best.P[0] < 0)
                  Best.Type = ((Ref.GetAbsEta() < 1.5) ? 0 : 1);
            }
            else if(C.InputObject == "Tau")
               Best = BestInRange(MPhaseII.Tau, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TkTau")
               Best = BestInRange(MPhaseII.TkTau, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "PFTau")
               Best = BestInRange(MPhaseII.PFTau, Ref, C.AbsEtaMin, C.AbsEtaMax, C.DRCut, Quality, Range, C.IsolationBB, C.IsolationEC);
            else if(C.InputObject == "TrackerHT0")
               Best = MPhaseII.TrackerHT[0];
            else if(C.InputObject == "TrackerMHT0")
               Best = MPhaseII.TrackerMHT[0];
            else if(C.InputObject == "TrackerHT1")
               Best = MPhaseII.TrackerHT[1];
            else if(C.InputObject == "TrackerMHT1")
               Best = MPhaseII.TrackerMHT[1];
            else if(C.InputObject == "TrackerHT2")
               Best = MPhaseII.TrackerHT[2];
            else if(C.InputObject == "TrackerMHT2")
               Best = MPhaseII.TrackerMHT[2];
            else if(C.InputObject == "TrackerHT3")
               Best = MPhaseII.TrackerHT[3];
            else if(C.InputObject == "TrackerMHT3")
               Best = MPhaseII.TrackerMHT[3];
            else if(C.InputObject == "TrackerHT4")
               Best = MPhaseII.TrackerHT[4];
            else if(C.InputObject == "TrackerMHT4")
               Best = MPhaseII.TrackerMHT[4];
            else if(C.InputObject == "TrackerMET")
               Best = MPhaseII.TrackerMET[0];
            else if(C.InputObject == "PuppiHT0")
               Best = MPhaseII.PuppiHT[0];
            else if(C.InputObject == "PuppiMHT0")
               Best = MPhaseII.PuppiMHT[0];
            else if(C.InputObject == "PuppiHT1")
               Best = MPhaseII.PuppiHT[1];
            else if(C.InputObject == "PuppiMHT1")
               Best = MPhaseII.PuppiMHT[1];
            else if(C.InputObject == "PuppiHT2")
               Best = MPhaseII.PuppiHT[2];
            else if(C.InputObject == "PuppiMHT2")
               Best = MPhaseII.PuppiMHT[2];
            else if(C.InputObject == "PuppiMET")
               Best = MPhaseII.PuppiMET[0];

            L1Objects.push_back(Best);
         }

         // for(int i = 0; i < N; i++)
         //    if(Configurations[i].InputObject == "TkMuon")
         //       cerr << ReferenceObjects[i] << " " << ReferenceSigns[i] << " " << L1Objects[i].Charge << endl;

         // Fill Histograms
         for(int i = 0; i < N; i++)
            FillHistograms(ObjectHistograms[i], L1Objects[i].P, ReferenceObjects[i], L1Objects[i].Iso, L1Objects[i].Type, L1Objects[i].DXY);
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





