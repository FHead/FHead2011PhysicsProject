//---------------------------------------------------------------------------
// AttachLikelihood.cpp
// Author: Yi Chen (11231)
//
// This program reads in a file, get tree named "probe_tree",
// evaluate likelihood using a 6D map and make a new branch with
// the log likelihood for each entry
//
//
// To run it, compile as usual
//
// > g++ AttachLikelihood.cpp -o AttachBranch -I/Path/To/Header/Files \
//    `root-config --cflags` `root-config --glibs`
//
//
// And then execute the program
//
// > time ./AttachBranch RootFile.root MapFileBase logLikelihood
//
// where the arguments are the root file containing probe_tree,
// the 6D map we want to use, and last one is the new name of the
// branch we want to create.
//---------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
//---------------------------------------------------------------------------
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
//---------------------------------------------------------------------------
#include "Code/TauHelperFunctions2.h"
#include "ProgressBar.h"
//---------------------------------------------------------------------------
#include "AngleConversion.h"
//---------------------------------------------------------------------------
class Index;
int main(int argc, char *argv[]);
//---------------------------------------------------------------------------
class Index
{
public:
   double HiggsMass;
   int Indices[7];
public:
   Index();
   ~Index() {}
   bool operator <(const Index &other) const;
   bool operator ==(const Index &other) const;
   void Print();
};
//---------------------------------------------------------------------------
Index::Index()
{
   HiggsMass = 0;
   for(int i = 0; i < 7; i++)
      Indices[i] = 0;
}
//---------------------------------------------------------------------------
bool Index::operator <(const Index &other) const
{
   for(int i = 0; i < 7; i++)
   {
      if(Indices[i] < other.Indices[i])   return true;
      if(Indices[i] > other.Indices[i])   return false;
   }

   if(HiggsMass < other.HiggsMass)   return true;
   if(HiggsMass > other.HiggsMass)   return false;

   return false;
}
//---------------------------------------------------------------------------
bool Index::operator ==(const Index &other) const
{
   for(int i = 0; i < 7; i++)
      if(Indices[i] != other.Indices[i])
         return false;
   return true;
}
//---------------------------------------------------------------------------
void Index::Print()
{
   cout << "(";
   for(int i = 0; i < 6; i++)
      cout << Indices[i] << " ";
   cout << Indices[6] << ")";
}
//---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
   if(argc < 4)
   {
      cerr << "Usage:" << argv[0] << " FileWithTree MapFileBase BranchName" << endl;
      return -1;
   }

   // Input parameters
   string TreeFile = "HZZEventNtuple_HZZ125.root";
   string MapFileBase = "All_PseudoScalar";
   string BranchName = "logLikelihood_pseudoscalar";

   TreeFile = argv[1];
   MapFileBase = argv[2];
   BranchName = argv[3];

   // Open file in update mode, and get tree
   TFile File(TreeFile.c_str(), "UPDATE");
   TDirectoryFile *Directory = (TDirectoryFile *)File.Get("zz4lTree");
   TTree *Tree = (TTree *)Directory->Get("probe_tree");

   // Set branch addresses
   float l1pt, l1eta, l1phi;
   float l2pt, l2eta, l2phi;
   float l3pt, l3eta, l3phi;
   float l4pt, l4eta, l4phi;
   float pho1pt, pho1eta, pho1phi;
   float pho2pt, pho2eta, pho2phi;
   // bool passFullSelection;
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
   Tree->SetBranchAddress("pho1pt", &pho1pt);
   Tree->SetBranchAddress("pho1eta", &pho1eta);
   Tree->SetBranchAddress("pho1phi", &pho1phi);
   Tree->SetBranchAddress("pho2pt", &pho2pt);
   Tree->SetBranchAddress("pho2eta", &pho2eta);
   Tree->SetBranchAddress("pho2phi", &pho2phi);
   // Tree->SetBranchAddress("passFullSelection", &passFullSelection);

   // Get ranges and bin counts from map
   double HMass = -1;
   int NBinsPhi0 = -1, NBinsTheta0 = -1, NBinsPhi = -1, NBinsTheta1 = -1, NBinsTheta2 = -1;
   int NBinsMass1 = -1, NBinsMass2 = -1;
   double Phi0Min = 0, Phi0Max = 0;
   double Theta0Min = 0, Theta0Max = 0;
   double PhiMin = 0, PhiMax = 0;
   double Theta1Min = 0, Theta1Max = 0;
   double Theta2Min = 0, Theta2Max = 0;
   double Mass1Min = 0, Mass1Max = 0;
   double Mass2Min = 0, Mass2Max = 0;
  
   int NBinsHiggs = 10;
   int HiggsMass[] = {100, 110, 120, 125, 130, 140, 160, 200, 300, 400};
   string HiggsMassString[] = {"100", "110", "120", "125", "130",
      "140", "160", "200", "300", "400"};

   vector<ifstream *> in;
   for(int i = 0; i < NBinsHiggs; i++)
   {
      in.push_back(new ifstream((MapFileBase + "_" + HiggsMassString[i] + ".map7").c_str()));
      *(in[i]) >> HMass;
      *(in[i]) >> NBinsPhi0 >> NBinsTheta0 >> NBinsPhi >> NBinsTheta1 >> NBinsTheta2 >> NBinsMass1 >> NBinsMass2;
      *(in[i]) >> Phi0Min >> Phi0Max;
      *(in[i]) >> Theta0Min >> Theta0Max;
      *(in[i]) >> PhiMin >> PhiMax;
      *(in[i]) >> Theta1Min >> Theta1Max;
      *(in[i]) >> Theta2Min >> Theta2Max;
      *(in[i]) >> Mass1Min >> Mass1Max;
      *(in[i]) >> Mass2Min >> Mass2Max;

      Mass1Min = Mass1Min / HMass;
      Mass1Max = Mass1Max / HMass;
      Mass2Min = Mass2Min / HMass;
      Mass2Max = Mass2Max / HMass;
   }

   cout << NBinsPhi0 << " " << NBinsTheta0 << " " << NBinsPhi << endl;
   cout << NBinsMass2 << " " << Mass2Min << " " << Mass2Max << endl;

   // First loop over the entries and create index
   map<int, Index> EventIndices;
   vector<Index> AvailableIndices;
   map<Index, vector<double> > Likelihoods;

   int EntryCount = Tree->GetEntries();

   cout << "Loop over tree and collect indices" << endl;
   ProgressBar Bar1(cout, EntryCount);
   Bar1.SetStyle(1);

   for(int iEvent = 0; iEvent < EntryCount; iEvent++)
   {
      Tree->GetEntry(iEvent);

      if(iEvent % 1000 == 0)
      {
         Bar1.Update(iEvent + 1);
         Bar1.Print();
      }

      // if(passFullSelection == false)
      //    continue;

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(l1pt, l1eta, l1phi);
      Leptons.Lepton12.SetPtEtaPhi(l2pt, l2eta, l2phi);
      Leptons.Lepton21.SetPtEtaPhi(l3pt, l3eta, l3phi);
      Leptons.Lepton22.SetPtEtaPhi(l4pt, l4eta, l4phi);

      if(pho1pt > 1)   // photon for Z1 found
      {
         FourVector Photon;
         Photon.SetPtEtaPhi(pho1pt, pho1eta, pho1phi);

         if(GetDR(Photon, Leptons.Lepton11) < GetDR(Photon, Leptons.Lepton12))
            Leptons.Lepton11 = Leptons.Lepton11 + Photon;
         else
            Leptons.Lepton12 = Leptons.Lepton12 + Photon;
      }
      if(pho2pt > 1)   // photon for Z2 found
      {
         FourVector Photon;
         Photon.SetPtEtaPhi(pho2pt, pho2eta, pho2phi);

         if(GetDR(Photon, Leptons.Lepton21) < GetDR(Photon, Leptons.Lepton22))
            Leptons.Lepton21 = Leptons.Lepton21 + Photon;
         else
            Leptons.Lepton22 = Leptons.Lepton22 + Photon;
      }

      EventParameters Angles = ConvertVectorsToAngles(Leptons, true);
      // cout << Angles << endl;

      Index index;
      index.Indices[0] = (Angles.Phi0 - Phi0Min) / (Phi0Max - Phi0Min) * NBinsPhi0;
      index.Indices[1] = (cos(Angles.Theta0) - Theta0Min) / (Theta0Max - Theta0Min) * NBinsTheta0;
      index.Indices[2] = (Angles.Phi - PhiMin) / (PhiMax - PhiMin) * NBinsPhi;
      index.Indices[3] = (cos(Angles.Theta1) - Theta1Min) / (Theta1Max - Theta1Min) * NBinsTheta1;
      index.Indices[4] = (cos(Angles.Theta2) - Theta2Min) / (Theta2Max - Theta2Min) * NBinsTheta2;
      index.Indices[5] = (Angles.ZMass/Angles.HMass - Mass1Min) / (Mass1Max - Mass1Min) * NBinsMass1;
      index.Indices[6] = (Angles.Z2Mass/Angles.HMass - Mass2Min) / (Mass2Max - Mass2Min) * NBinsMass2;
      index.HiggsMass = Angles.HMass;

      // index.Print();
      // cout << endl;

      if(index.Indices[0] >= NBinsPhi0)
         index.Indices[0] = NBinsPhi0 - 1;
      if(index.Indices[1] >= NBinsTheta0)
         index.Indices[1] = NBinsTheta0 - 1;
      if(index.Indices[2] >= NBinsPhi)
         index.Indices[2] = NBinsPhi - 1;
      if(index.Indices[3] >= NBinsTheta1)
         index.Indices[3] = NBinsTheta1 - 1;
      if(index.Indices[4] >= NBinsTheta2)
         index.Indices[4] = NBinsTheta2 - 1;
      if(index.Indices[5] >= NBinsMass1)
         index.Indices[5] = NBinsMass1 - 1;
      if(index.Indices[6] >= NBinsMass2)
         index.Indices[6] = NBinsMass2 - 1;

      EventIndices.insert(pair<int, Index>(iEvent, index));

      AvailableIndices.push_back(index);
      if(iEvent % 10000 == 0)
      {
         sort(AvailableIndices.begin(), AvailableIndices.end());
         AvailableIndices.erase(unique(AvailableIndices.begin(), AvailableIndices.end()), AvailableIndices.end());
      }
   }

   Bar1.Update(EntryCount);
   Bar1.Print();
   Bar1.PrintLine();
   cout << endl;

   sort(AvailableIndices.begin(), AvailableIndices.end());
   AvailableIndices.erase(unique(AvailableIndices.begin(), AvailableIndices.end()), AvailableIndices.end());

   // Evaluate likelihoods - calculate integral along the way
   bool ErrorMessagePrinted = false;
   vector<double> Integral;
   int VectorCount = 0;

   for(int i = 0; i < NBinsHiggs; i++)
      Integral.push_back(0);

   cout << "Starting evaluating likelihoods..." << endl;
   ProgressBar Bar2(cout, NBinsPhi0 * NBinsTheta0);
   Bar2.SetStyle(1);

   for(int iPhi0 = 0; iPhi0 < NBinsPhi0; iPhi0++)
   {
      for(int iTheta0 = 0; iTheta0 < NBinsTheta0; iTheta0++)
      {
         Bar2.Update(iPhi0 * NBinsTheta0 + iTheta0 + 1);
         Bar2.Print();

         for(int iPhi = 0; iPhi < NBinsPhi; iPhi++)
         {
            for(int iTheta1 = 0; iTheta1 < NBinsTheta1; iTheta1++)
            {
               for(int iTheta2 = 0; iTheta2 < NBinsTheta2; iTheta2++)
               {
                  for(int iZ1Mass = 0; iZ1Mass < NBinsMass1; iZ1Mass++)
                  {
                     for(int iZ2Mass = 0; iZ2Mass < NBinsMass2; iZ2Mass++)
                     {
                        bool BadBin = false;
                        vector<double> Temp(NBinsHiggs);
                        for(int i = 0; i < NBinsHiggs; i++)
                        {
                           string TempString = "";
                           *(in[i]) >> TempString;
                           if(TempString == "nan" || TempString == "inf" || TempString == "-inf")
                           {
                              BadBin = true;
                              continue;
                           }
                        
                           double TempValue = -1;
                           stringstream TempStream(TempString);
                           TempStream >> TempValue;
                           Temp[i] = TempValue;
                        }
                        if(BadBin == true)
                           continue;

                        // if(iZ2Mass == 0)
                        //    continue;

                        for(int i = 0; i < NBinsHiggs; i++)
                           Integral[i] = Integral[i] + Temp[i] * HiggsMass[i] * HiggsMass[i];

                        Index ThisEntry;
                        ThisEntry.Indices[0] = iPhi0;
                        ThisEntry.Indices[1] = iTheta0;
                        ThisEntry.Indices[2] = iPhi;
                        ThisEntry.Indices[3] = iTheta1;
                        ThisEntry.Indices[4] = iTheta2;
                        ThisEntry.Indices[5] = iZ1Mass;
                        ThisEntry.Indices[6] = iZ2Mass;
                        ThisEntry.HiggsMass = 0;

                        if(VectorCount >= AvailableIndices.size())
                           continue;

                        if(ThisEntry == AvailableIndices[VectorCount])
                        {
                           Likelihoods.insert(pair<Index, vector<double> >(ThisEntry, Temp));
                           VectorCount = VectorCount + 1;

                           /*
                           if(Temp < 1e-10)
                           {
                              cout << "Likelihood is zero for this set of parameters: ";
                              ThisEntry.Print();
                              cout << endl;

                              cout << "What do we do??" << endl;
                           }
                           */
                        }
                        else if(AvailableIndices[VectorCount] < ThisEntry && ErrorMessagePrinted == false)
                        {
                           cerr << "This should not happen!  Contact Yi for more detail and to debug!" << endl;
                           ThisEntry.Print();
                           cout << " ";
                           AvailableIndices[VectorCount].Print();
                           cout << endl;
                           ErrorMessagePrinted = true;
                        }
                     }
                  }
               }
            }
         }
      }
   }
   AvailableIndices.erase(AvailableIndices.begin(), AvailableIndices.end());

   Bar2.Update(NBinsPhi0 * NBinsTheta0);
   Bar2.Print();
   Bar2.PrintLine();
   cout << endl;

   // Add a new branch to tree
   float logLikelihood = 0;
   TBranch *bLikelihood = Tree->Branch(BranchName.c_str(), &logLikelihood, (BranchName + "/F").c_str());

   // Loop over entries and include the new branch
   cout << "Attaching a new branch" << endl;

   for(int iEntry = 0; iEntry < EntryCount; iEntry++)
   {
      if(iEntry % 1000 == 0)
      {
         Bar1.Update(iEntry + 1);
         Bar1.Print();
      }
      
      if(EventIndices.find(iEntry) == EventIndices.end())
         logLikelihood = 0;
      else
      {
         logLikelihood = 0;

         Index index = EventIndices[iEntry];
         double EventHMass = index.HiggsMass;
         index.HiggsMass = 0;
         vector<double> &LikelihoodVector = Likelihoods[index];

         // cout << LikelihoodVector.size() << endl;

         // cout << HMass << endl;

         if(Likelihoods.find(index) == Likelihoods.end())
            logLikelihood = 0;
         else if(Likelihoods[index].size() < NBinsHiggs)
            logLikelihood = 0;
         else if(EventHMass < HiggsMass[0])
            logLikelihood = 0;
         else if(EventHMass >= HiggsMass[NBinsHiggs-1])
            logLikelihood = 0;
         else
         {
            for(int i = 0; i < NBinsHiggs - 1; i++)
            {
               if(EventHMass < HiggsMass[i] || EventHMass >= HiggsMass[i+1])
                  continue;

               double likelihood = LikelihoodVector[i] / Integral[i]
                  * (HiggsMass[i+1] * HiggsMass[i+1] - EventHMass * EventHMass)
                  + LikelihoodVector[i+1] / Integral[i+1]
                  * (EventHMass * EventHMass - HiggsMass[i] * HiggsMass[i]);
               likelihood = likelihood / (HiggsMass[i+1] * HiggsMass[i+1] - HiggsMass[i] * HiggsMass[i]);

               logLikelihood = log(likelihood);
            }
         }

         // do the interpolation
         // logLikelihood = log(Likelihoods[EventIndices[iEntry]]) - log(Integral);
      }
         
      bLikelihood->Fill();
   }

   Bar1.Update(EntryCount);
   Bar1.Print();
   Bar1.PrintLine();
   cout << endl;

   // Overwrite the tree
   Directory->cd();
   Tree->Write("", TObject::kOverwrite);
   File.cd();

   // Clean-up
   for(int i = 0; i < NBinsHiggs; i++)
   {
      if(in[i] == NULL)
         continue;

      in[i]->close();
      delete in[i];
      in[i] = NULL;
   }

   File.Close();

   return 0;
}
//---------------------------------------------------------------------------





