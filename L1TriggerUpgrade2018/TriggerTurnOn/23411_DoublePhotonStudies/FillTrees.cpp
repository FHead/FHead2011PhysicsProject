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

#include "HelperFunctions.h"

int main(int argc, char *argv[]);
bool SortByPT(const FourVector &V1, const FourVector &V2);

int main(int argc, char *argv[])
{
   fastjet::ClusterSequence::set_fastjet_banner_stream(NULL);

   CommandLine CL(argc, argv);

   // Some root styling
   SetThesisStyle();

   // Get arguments
   vector<string> InputFileNames = CL.GetStringVector("input", ',');
   string OutputFileName         = CL.Get("output");

   string L1PhaseIITreeName      = CL.Get("tree", "l1PhaseIITree/L1PhaseIITree");

   // Output File and directories for better organization
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   // create tree!
   TTree OutputTree("ObjectTree", "");
   GenericObject TreeObjectNonPV1, TreeObjectNonPV2, TreeObjectPV1, TreeObjectPV2;
   FourVector TreeReference1;
   FourVector TreeReference2;
   double TreeObjectNonPV1PT;
   double TreeObjectNonPV1Eta;
   double TreeObjectNonPV1Phi;
   double TreeObjectNonPV2PT;
   double TreeObjectNonPV2Eta;
   double TreeObjectNonPV2Phi;
   double TreeObjectPV1PT;
   double TreeObjectPV1Eta;
   double TreeObjectPV1Phi;
   double TreeObjectPV2PT;
   double TreeObjectPV2Eta;
   double TreeObjectPV2Phi;
   double TreeReference1PT;
   double TreeReference1Eta;
   double TreeReference1Phi;
   double TreeReference2PT;
   double TreeReference2Eta;
   double TreeReference2Phi;
      
   OutputTree.Branch("Reference1P",   &TreeReference1.P,  "Reference1P[4]/D");
   OutputTree.Branch("Reference1PT",  &TreeReference1PT,  "Reference1PT/D");
   OutputTree.Branch("Reference1Eta", &TreeReference1Eta, "Reference1Eta/D");
   OutputTree.Branch("Reference1Phi", &TreeReference1Phi, "Reference1Phi/D");
   OutputTree.Branch("Reference2P",   &TreeReference2.P,  "Reference2P[4]/D");
   OutputTree.Branch("Reference2PT",  &TreeReference2PT,  "Reference2PT/D");
   OutputTree.Branch("Reference2Eta", &TreeReference2Eta, "Reference2Eta/D");
   OutputTree.Branch("Reference2Phi", &TreeReference2Phi, "Reference2Phi/D");
   OutputTree.Branch("ObjectNonPV1P",       &TreeObjectNonPV1.P.P,    "ObjectNonPV1P[4]/D");
   OutputTree.Branch("ObjectNonPV1PT",      &TreeObjectNonPV1PT,      "ObjectNonPV1PT/D");
   OutputTree.Branch("ObjectNonPV1Eta",     &TreeObjectNonPV1Eta,     "ObjectNonPV1Eta/D");
   OutputTree.Branch("ObjectNonPV1Phi",     &TreeObjectNonPV1Phi,     "ObjectNonPV1Phi/D");
   OutputTree.Branch("ObjectNonPV1Bx",      &TreeObjectNonPV1.Bx,     "ObjectNonPV1Bx/I");
   OutputTree.Branch("ObjectNonPV1Iso",     &TreeObjectNonPV1.Iso,    "ObjectNonPV1Iso/D");
   OutputTree.Branch("ObjectNonPV1VZ",      &TreeObjectNonPV1.VZ,     "ObjectNonPV1VZ/D");
   OutputTree.Branch("ObjectNonPV1PET",     &TreeObjectNonPV1.PET,    "ObjectNonPV1PET/D");
   OutputTree.Branch("ObjectNonPV1ID",      &TreeObjectNonPV1.ID,     "ObjectNonPV1ID/I");
   OutputTree.Branch("ObjectNonPV1Qual",    &TreeObjectNonPV1.Qual,   "ObjectNonPV1Qual/I");
   OutputTree.Branch("ObjectNonPV1Type",    &TreeObjectNonPV1.Type,   "ObjectNonPV1Type/D");
   OutputTree.Branch("ObjectNonPV1Flag",    &TreeObjectNonPV1.Flag,   "ObjectNonPV1Flag/I");
   OutputTree.Branch("ObjectNonPV1Charge",  &TreeObjectNonPV1.Charge, "ObjectNonPV1Charge/I");
   OutputTree.Branch("ObjectNonPV1DXY",     &TreeObjectNonPV1.DXY,    "ObjectNonPV1DXY/D");
   OutputTree.Branch("ObjectNonPV2P",       &TreeObjectNonPV2.P.P,    "ObjectNonPV2P[4]/D");
   OutputTree.Branch("ObjectNonPV2PT",      &TreeObjectNonPV2PT,      "ObjectNonPV2PT/D");
   OutputTree.Branch("ObjectNonPV2Eta",     &TreeObjectNonPV2Eta,     "ObjectNonPV2Eta/D");
   OutputTree.Branch("ObjectNonPV2Phi",     &TreeObjectNonPV2Phi,     "ObjectNonPV2Phi/D");
   OutputTree.Branch("ObjectNonPV2Bx",      &TreeObjectNonPV2.Bx,     "ObjectNonPV2Bx/I");
   OutputTree.Branch("ObjectNonPV2Iso",     &TreeObjectNonPV2.Iso,    "ObjectNonPV2Iso/D");
   OutputTree.Branch("ObjectNonPV2VZ",      &TreeObjectNonPV2.VZ,     "ObjectNonPV2VZ/D");
   OutputTree.Branch("ObjectNonPV2PET",     &TreeObjectNonPV2.PET,    "ObjectNonPV2PET/D");
   OutputTree.Branch("ObjectNonPV2ID",      &TreeObjectNonPV2.ID,     "ObjectNonPV2ID/I");
   OutputTree.Branch("ObjectNonPV2Qual",    &TreeObjectNonPV2.Qual,   "ObjectNonPV2Qual/I");
   OutputTree.Branch("ObjectNonPV2Type",    &TreeObjectNonPV2.Type,   "ObjectNonPV2Type/D");
   OutputTree.Branch("ObjectNonPV2Flag",    &TreeObjectNonPV2.Flag,   "ObjectNonPV2Flag/I");
   OutputTree.Branch("ObjectNonPV2Charge",  &TreeObjectNonPV2.Charge, "ObjectNonPV2Charge/I");
   OutputTree.Branch("ObjectNonPV2DXY",     &TreeObjectNonPV2.DXY,    "ObjectNonPV2DXY/D");
   OutputTree.Branch("ObjectPV1P",       &TreeObjectPV1.P.P,    "ObjectPV1P[4]/D");
   OutputTree.Branch("ObjectPV1PT",      &TreeObjectPV1PT,      "ObjectPV1PT/D");
   OutputTree.Branch("ObjectPV1Eta",     &TreeObjectPV1Eta,     "ObjectPV1Eta/D");
   OutputTree.Branch("ObjectPV1Phi",     &TreeObjectPV1Phi,     "ObjectPV1Phi/D");
   OutputTree.Branch("ObjectPV1Bx",      &TreeObjectPV1.Bx,     "ObjectPV1Bx/I");
   OutputTree.Branch("ObjectPV1Iso",     &TreeObjectPV1.Iso,    "ObjectPV1Iso/D");
   OutputTree.Branch("ObjectPV1VZ",      &TreeObjectPV1.VZ,     "ObjectPV1VZ/D");
   OutputTree.Branch("ObjectPV1PET",     &TreeObjectPV1.PET,    "ObjectPV1PET/D");
   OutputTree.Branch("ObjectPV1ID",      &TreeObjectPV1.ID,     "ObjectPV1ID/I");
   OutputTree.Branch("ObjectPV1Qual",    &TreeObjectPV1.Qual,   "ObjectPV1Qual/I");
   OutputTree.Branch("ObjectPV1Type",    &TreeObjectPV1.Type,   "ObjectPV1Type/D");
   OutputTree.Branch("ObjectPV1Flag",    &TreeObjectPV1.Flag,   "ObjectPV1Flag/I");
   OutputTree.Branch("ObjectPV1Charge",  &TreeObjectPV1.Charge, "ObjectPV1Charge/I");
   OutputTree.Branch("ObjectPV1DXY",     &TreeObjectPV1.DXY,    "ObjectPV1DXY/D");
   OutputTree.Branch("ObjectPV2P",       &TreeObjectPV2.P.P,    "ObjectPV2P[4]/D");
   OutputTree.Branch("ObjectPV2PT",      &TreeObjectPV2PT,      "ObjectPV2PT/D");
   OutputTree.Branch("ObjectPV2Eta",     &TreeObjectPV2Eta,     "ObjectPV2Eta/D");
   OutputTree.Branch("ObjectPV2Phi",     &TreeObjectPV2Phi,     "ObjectPV2Phi/D");
   OutputTree.Branch("ObjectPV2Bx",      &TreeObjectPV2.Bx,     "ObjectPV2Bx/I");
   OutputTree.Branch("ObjectPV2Iso",     &TreeObjectPV2.Iso,    "ObjectPV2Iso/D");
   OutputTree.Branch("ObjectPV2VZ",      &TreeObjectPV2.VZ,     "ObjectPV2VZ/D");
   OutputTree.Branch("ObjectPV2PET",     &TreeObjectPV2.PET,    "ObjectPV2PET/D");
   OutputTree.Branch("ObjectPV2ID",      &TreeObjectPV2.ID,     "ObjectPV2ID/I");
   OutputTree.Branch("ObjectPV2Qual",    &TreeObjectPV2.Qual,   "ObjectPV2Qual/I");
   OutputTree.Branch("ObjectPV2Type",    &TreeObjectPV2.Type,   "ObjectPV2Type/D");
   OutputTree.Branch("ObjectPV2Flag",    &TreeObjectPV2.Flag,   "ObjectPV2Flag/I");
   OutputTree.Branch("ObjectPV2Charge",  &TreeObjectPV2.Charge, "ObjectPV2Charge/I");
   OutputTree.Branch("ObjectPV2DXY",     &TreeObjectPV2.DXY,    "ObjectPV2DXY/D");

   // Now starting the loop
   for(string InputFileName : InputFileNames)
   {
      cout << "Processing file " << InputFileName << endl;

      // Input File
      TFile File(InputFileName.c_str());

      // Messengers
      L1GenMessenger MGen(File, "genTree/L1GenTree");
      L1PhaseIITreeV11p2Messenger MPhaseII(File, L1PhaseIITreeName);

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

         vector<FourVector> Photons;

         // Collect gen-particles
         for(int i = 0; i < (int)MGen.GenP.size(); i++)
         {
            int AbsID = MGen.GenID[i];
            if(AbsID < 0)
               AbsID = -AbsID;
            if(AbsID == 22)
            {
               // if(MGen.GenP[i].GetAbsEta() > 1.479)
               //    continue;
               Photons.push_back(MGen.GenP[i]);
            }
         }

         // sort by PT
         sort(Photons.begin(), Photons.end(), SortByPT);

         TreeReference1[0] = -1;
         TreeReference2[0] = -1;
         if(Photons.size() > 0)
            TreeReference1 = Photons[0];
         if(Photons.size() > 1)
            TreeReference2 = Photons[1];

         // Find best L1 objects
         int Quality = QUAL_UseFlag;
         int Index = -1;
            
         GenericObject BestNonPV1, BestNonPV2;
         Index = BestIndexInRange(MPhaseII.TkPhotonTrackID, TreeReference1, 0, 1.479, -1, 0.15, Quality, -1, 0.20, 0.20);
         if(Index >= 0 && Index < (int)MPhaseII.TkPhotonTrackID.size())
         {
            BestNonPV1 = MPhaseII.TkPhotonTrackID[Index];
            MPhaseII.TkPhotonTrackID.erase(MPhaseII.TkPhotonTrackID.begin() + Index);
         }
         else
            BestNonPV1.P[0] = -1;
         Index = BestIndexInRange(MPhaseII.TkPhotonTrackID, TreeReference2, 0, 1.479, -1, 0.15, Quality, -1, 0.20, 0.20);
         if(Index >= 0 && Index < (int)MPhaseII.TkPhotonTrackID.size())
            BestNonPV2 = MPhaseII.TkPhotonTrackID[Index];
         else
            BestNonPV2.P[0] = -1;
         
         GenericObject BestPV1, BestPV2;
         Index = BestIndexInRange(MPhaseII.TkPhotonPVTrackID, TreeReference1, 0, 1.479, -1, 0.15, Quality, -1, 0.20, 0.20);
         if(Index >= 0 && Index < (int)MPhaseII.TkPhotonPVTrackID.size())
         {
            BestPV1 = MPhaseII.TkPhotonPVTrackID[Index];
            MPhaseII.TkPhotonPVTrackID.erase(MPhaseII.TkPhotonPVTrackID.begin() + Index);
         }
         else
            BestPV1.P[0] = -1;
         Index = BestIndexInRange(MPhaseII.TkPhotonPVTrackID, TreeReference2, 0, 1.479, -1, 0.15, Quality, -1, 0.20, 0.20);
         if(Index >= 0 && Index < (int)MPhaseII.TkPhotonPVTrackID.size())
            BestPV2 = MPhaseII.TkPhotonPVTrackID[Index];
         else
            BestPV2.P[0] = -1;

         
         // Fill output tree
         TreeReference1PT     = TreeReference1.GetPT();
         TreeReference1Eta    = TreeReference1.GetEta();
         TreeReference1Phi    = TreeReference1.GetPhi();
         TreeReference2PT     = TreeReference2.GetPT();
         TreeReference2Eta    = TreeReference2.GetEta();
         TreeReference2Phi    = TreeReference2.GetPhi();
         
         TreeObjectNonPV1 = BestNonPV1;
         TreeObjectNonPV2 = BestNonPV2;
         TreeObjectPV1 = BestPV1;
         TreeObjectPV2 = BestPV2;
         
         TreeObjectNonPV1PT   = TreeObjectNonPV1.P.GetPT();
         TreeObjectNonPV1Eta  = TreeObjectNonPV1.P.GetEta();
         TreeObjectNonPV1Phi  = TreeObjectNonPV1.P.GetPhi();
         TreeObjectNonPV2PT   = TreeObjectNonPV2.P.GetPT();
         TreeObjectNonPV2Eta  = TreeObjectNonPV2.P.GetEta();
         TreeObjectNonPV2Phi  = TreeObjectNonPV2.P.GetPhi();
         TreeObjectPV1PT      = TreeObjectPV1.P.GetPT();
         TreeObjectPV1Eta     = TreeObjectPV1.P.GetEta();
         TreeObjectPV1Phi     = TreeObjectPV1.P.GetPhi();
         TreeObjectPV2PT      = TreeObjectPV2.P.GetPT();
         TreeObjectPV2Eta     = TreeObjectPV2.P.GetEta();
         TreeObjectPV2Phi     = TreeObjectPV2.P.GetPhi();

         OutputTree.Fill();
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      File.Close();
   }

   // Output tree
   OutputFile.cd();
   OutputTree.Write();

   // Clean up
   OutputFile.Close();

   // Yay
   return 0;
}

bool SortByPT(const FourVector &V1, const FourVector &V2)
{
   return V1.InnerGetPT() > V2.InnerGetPT();
}






