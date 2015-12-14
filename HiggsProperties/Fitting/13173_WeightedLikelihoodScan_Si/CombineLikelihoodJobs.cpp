#include <iostream>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"

#include "Code/DrawRandom.h"
#include <assert.h>

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " Input NJobst Output" << endl;
      return -1;
   }

   string fileLabel = argv[1];
   int njobs = atoi(argv[2]);
   string outputfilename = argv[3];


   int EntryCount = -1; 
   vector<TTree*> trees;
   for (int i=0; i < njobs; ++i) {
     TFile *tmpfile = new TFile(Form("%s_Job%d.root",fileLabel.c_str(), i),"READ");
     TTree *tmpTree = 0;
     if (tmpfile) {
       tmpTree = (TTree*)tmpfile->Get("ResultTree");
       if (tmpTree && EntryCount < 0) {
         EntryCount = tmpTree->GetEntries();
       }
     }
     trees.push_back(tmpTree);
   }


   TFile File(outputfilename.c_str(), "RECREATE");
   string BranchList = "";
   BranchList = BranchList + "A2ZZA1ZZ:A2ZZPhase:A3ZZA1ZZ:A3ZZPhase";                          // 4
   BranchList = BranchList + ":A2ZAA1ZZ:A2ZAPhase:A3ZAA1ZZ:A3ZAPhase";                         // 8
   BranchList = BranchList + ":A2AAA1ZZ:A2AAPhase:A3AAA1ZZ:A3AAPhase";                         // 12
   BranchList = BranchList + ":A1L1ZZ:A1L1ZZPhase:A1LQZZ:A1LQZZPhase";                         // 16
   BranchList = BranchList + ":TruthNLL:BestNLL";                                              // 18
   BranchList = BranchList + ":SumWeight";                                                     // 19
   BranchList = BranchList + ":energy:process:channel";                                        // 22
   
   TNtuple OutputTree("ResultTree", "", BranchList.c_str());


   Float_t A2ZZA1ZZ;
   Float_t A2ZZPhase;
   Float_t A3ZZA1ZZ;
   Float_t A3ZZPhase;
   Float_t A2ZAA1ZZ;
   Float_t A2ZAPhase;
   Float_t A3ZAA1ZZ;
   Float_t A3ZAPhase;
   Float_t A2AAA1ZZ;
   Float_t A2AAPhase;
   Float_t A3AAA1ZZ;
   Float_t A3AAPhase;
   Float_t A1L1ZZ;
   Float_t A1L1ZZPhase;
   Float_t A1LQZZ;
   Float_t A1LQZZPhase;
   Float_t TruthNLL;
   Float_t BestNLL;
   Float_t SumWeight;
   Float_t energy;
   Float_t process;
   Float_t channel;

   for (int i=0; i<njobs; ++i) {
     if (!trees[i]) continue;
     trees[i]->SetBranchAddress("A2ZZA1ZZ", &A2ZZA1ZZ);                        
     trees[i]->SetBranchAddress("A2ZZPhase", &A2ZZPhase);                        
     trees[i]->SetBranchAddress("A3ZZA1ZZ", &A3ZZA1ZZ);                        
     trees[i]->SetBranchAddress("A3ZZPhase", &A3ZZPhase);                        
     trees[i]->SetBranchAddress("A2ZAA1ZZ", &A2ZAA1ZZ);                        
     trees[i]->SetBranchAddress("A2ZAPhase", &A2ZAPhase);                        
     trees[i]->SetBranchAddress("A3ZAA1ZZ", &A3ZAA1ZZ);                        
     trees[i]->SetBranchAddress("A3ZAPhase", &A3ZAPhase);                        
     trees[i]->SetBranchAddress("A2AAA1ZZ", &A2AAA1ZZ);                        
     trees[i]->SetBranchAddress("A2AAPhase", &A2AAPhase);                        
     trees[i]->SetBranchAddress("A3AAA1ZZ", &A3AAA1ZZ);                        
     trees[i]->SetBranchAddress("A3AAPhase", &A3AAPhase);                        
     trees[i]->SetBranchAddress("A1L1ZZ", &A1L1ZZ);                        
     trees[i]->SetBranchAddress("A1L1ZZPhase", &A1L1ZZPhase);                        
     trees[i]->SetBranchAddress("A1LQZZ", &A1LQZZ);                        
     trees[i]->SetBranchAddress("A1LQZZPhase", &A1LQZZPhase);                        
     trees[i]->SetBranchAddress("TruthNLL", &TruthNLL);
     trees[i]->SetBranchAddress("BestNLL", &BestNLL);
     trees[i]->SetBranchAddress("SumWeight", &SumWeight);
     trees[i]->SetBranchAddress("energy", &energy);
     trees[i]->SetBranchAddress("process", &process);
     trees[i]->SetBranchAddress("channel", &channel);
   }


   for(int i = 0; i < EntryCount; i++)
   {
     cout << "Process " << i << " / " << EntryCount << "\n";

     TTree *tmpTree = 0;
     for(int t=0; t<njobs; ++t) {
       if (!tmpTree) {
         if (trees[t]) tmpTree = trees[t];
       } else {
         break;
       }
     }
     tmpTree->GetEntry(i);
     
     float Array[22];
     Array[0]   = A2ZZA1ZZ;
     Array[1]   = A2ZZPhase;
     Array[2]   = A3ZZA1ZZ;
     Array[3]   = A3ZZPhase;
     Array[4]   = A2ZAA1ZZ;
     Array[5]   = A2ZAPhase;
     Array[6]   = A3ZAA1ZZ;
     Array[7]   = A3ZAPhase;
     Array[8]   = A2AAA1ZZ;
     Array[9]   = A2AAPhase;
     Array[10]  = A3AAA1ZZ;
      Array[11]  = A3AAPhase;
      Array[12] = A1L1ZZ;
      Array[13] = A1L1ZZPhase;
      Array[14] = A1LQZZ;
      Array[15] = A1LQZZPhase;
      Array[16] = TruthNLL;
      Array[19] = energy;
      Array[20] = process;
      Array[21] = channel;

     double sumweight = 0;
     double bestnll = 0;

     for(int t=0; t<njobs; ++t) {
       if (trees[t]) {
         trees[t]->GetEntry(i);
         sumweight += SumWeight;
         bestnll += BestNLL;
       }
     }

     Array[17] = bestnll;
     Array[18] = sumweight;

     OutputTree.Fill(Array);
   }

   OutputTree.Write();
   File.Close();

   return 0;
}





