#include <iostream>
using namespace std;

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"

#include "Code/DrawRandom.h"
#include <assert.h>
#include "FitClass.h"

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " Input NJobst Output" << endl;
      return -1;
   }



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


   string fileLabel = argv[1];
   string outputfilename = argv[2];


   vector<string> processLabels;
   processLabels.push_back("Signal");
   processLabels.push_back("Background");
   processLabels.push_back("ZJets");
   // processLabels.push_back("ggZZ");

   int EntryCount = -1; 
   TTree *referenceTree = 0;
   vector<vector<vector< TTree*> > > trees;
   for (int i=0; i<processLabels.size(); ++i) {
     vector<vector< TTree*> > tmptmptrees;
     for (int j=7; j<=8; j++) {
       vector< TTree*> tmptrees;

       for (int k=0; k<4;++k) {
         TFile *tmpfile = new TFile(Form("%s_%s%dTeV_%dTeV_channel%d_combined.root",fileLabel.c_str(),processLabels[i].c_str(),j,j,k),"READ");
         TTree *tmpTree = 0;
         if (tmpfile) {
           tmpTree = (TTree*)tmpfile->Get("ResultTree");
           if (tmpTree && EntryCount < 0) {
             referenceTree = tmpTree;
             EntryCount = tmpTree->GetEntries();
           }
         }
         tmptrees.push_back(tmpTree);         
       }
       cout << i << " " << j << " : " << tmptrees.size() << "\n";
       tmptmptrees.push_back(tmptrees);
     }
     cout << i << " : " << tmptmptrees.size() << "\n";
     trees.push_back(tmptmptrees);
   }

   cout << " here1 " << trees.size() << "\n";


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

   for (int i=0; i<processLabels.size(); ++i) {      
     for (int j=0; j<2; j++) {
       for (int k=0; k<4;++k) {  
         cout << i << " " << j << " " << k << "\n";
         if (!trees[i][j][k]) continue;
         trees[i][j][k]->SetBranchAddress("A2ZZA1ZZ", &A2ZZA1ZZ);                        
         trees[i][j][k]->SetBranchAddress("A2ZZPhase", &A2ZZPhase);                        
         trees[i][j][k]->SetBranchAddress("A3ZZA1ZZ", &A3ZZA1ZZ);                        
         trees[i][j][k]->SetBranchAddress("A3ZZPhase", &A3ZZPhase);                        
         trees[i][j][k]->SetBranchAddress("A2ZAA1ZZ", &A2ZAA1ZZ);                        
         trees[i][j][k]->SetBranchAddress("A2ZAPhase", &A2ZAPhase);                        
         trees[i][j][k]->SetBranchAddress("A3ZAA1ZZ", &A3ZAA1ZZ);                        
         trees[i][j][k]->SetBranchAddress("A3ZAPhase", &A3ZAPhase);                        
         trees[i][j][k]->SetBranchAddress("A2AAA1ZZ", &A2AAA1ZZ);                        
         trees[i][j][k]->SetBranchAddress("A2AAPhase", &A2AAPhase);                        
         trees[i][j][k]->SetBranchAddress("A3AAA1ZZ", &A3AAA1ZZ);                        
         trees[i][j][k]->SetBranchAddress("A3AAPhase", &A3AAPhase);                        
         trees[i][j][k]->SetBranchAddress("A1L1ZZ", &A1L1ZZ);                        
         trees[i][j][k]->SetBranchAddress("A1L1ZZPhase", &A1L1ZZPhase);                        
         trees[i][j][k]->SetBranchAddress("A1LQZZ", &A1LQZZ);                        
         trees[i][j][k]->SetBranchAddress("A1LQZZPhase", &A1LQZZPhase);                        
         trees[i][j][k]->SetBranchAddress("TruthNLL", &TruthNLL);
         trees[i][j][k]->SetBranchAddress("BestNLL", &BestNLL);
         trees[i][j][k]->SetBranchAddress("SumWeight", &SumWeight);
         trees[i][j][k]->SetBranchAddress("energy", &energy);
         trees[i][j][k]->SetBranchAddress("process", &process);
         trees[i][j][k]->SetBranchAddress("channel", &channel);
       }
     }
   }


   for(int b = 0; b < EntryCount; b++)
   {
     cout << "Process " << b << " / " << EntryCount << "\n";

     referenceTree->GetEntry(b);
     
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

     double bestnll = 0;

     for (int i=0; i<processLabels.size(); ++i) {      
       for (int j=7; j<=8; j++) {
         for (int k=0; k<4;++k) {           
           if (trees[i][j-7][k]) {
             trees[i][j-7][k]->GetEntry(b);
             double mean;
             if (i == 0) {
               if (j==7) {
                 mean = NS7[k];
               } else {
                 mean = NS8[k];
               }
             } else if (i == 1) {
               if (j==7) {
                 mean = NB7[k];
               } else {
                 mean = NB8[k];
               }
             } else if (i == 2) {
               if (j==7) {
                 mean = NZJ7[k];
               } else {
                 mean = NZJ8[k];
               }
             } else if (i == 3) {
               if (j==7) {
                 mean = NggZZ7[k];
               } else {
                 mean = NggZZ8[k];
               }
             }
             cout << j << " " << k << " : " << BestNLL << " / " << SumWeight << " * " << mean << " " << BestNLL/SumWeight * mean << "\n";
             bestnll += BestNLL/SumWeight * mean ;
           }
         }
       }
     }
     
     cout << "bin " << b << " : " << bestnll << "\n";

     Array[17] = bestnll;

     OutputTree.Fill(Array);
   }


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

                     OutputTree.SetAlias(S1.c_str(), S2.c_str());
                  }
               }
            }
         }
      }
   }

   OutputTree.SetAlias("A2ZZ", "A2ZZA1ZZ");
   OutputTree.SetAlias("A3ZZ", "A3ZZA1ZZ");
   OutputTree.SetAlias("A2ZA", "A2ZAA1ZZ");
   OutputTree.SetAlias("A3ZA", "A3ZAA1ZZ");
   OutputTree.SetAlias("A2AA", "A2AAA1ZZ");
   OutputTree.SetAlias("A3AA", "A3AAA1ZZ");

   OutputTree.SetAlias("ZZ", "sqrt(A2ZZ*A2ZZ+A3ZZ*A3ZZ+1)");
   OutputTree.SetAlias("ZA", "sqrt(A2ZA*A2ZA+A3ZA*A3ZA)");
   OutputTree.SetAlias("AA", "sqrt(A2AA*A2AA+A3AA*A3AA)");

   OutputTree.SetAlias("S1", "1");
   OutputTree.SetAlias("S2", "(A2ZZ*A2ZZ/3.276/3.276)");
   OutputTree.SetAlias("S3", "(A3ZZ*A3ZZ/5.042/5.042)");

   OutputTree.SetAlias("FA1", "(1/(1+S2+S3))");
   OutputTree.SetAlias("FA2", "(-S2/(1+S2+S3)*sign(A2ZZ))");
   OutputTree.SetAlias("FA3", "(-S3/(1+S2+S3)*sign(A3ZZ))");

   OutputTree.SetAlias("eFA2", "(A2ZZ*A2ZZ/9/(1+A2ZZ*A2ZZ/9)*sign(A2ZZ))");
   OutputTree.SetAlias("eFA3", "(A3ZZ*A3ZZ/25/(1+A3ZZ*A3ZZ/25)*sign(A3ZZ))");

   OutputTree.SetAlias("Nem7", "(Sem7+Bem7+ZJem7+ggZZem7)");
   OutputTree.SetAlias("Nme7", "(Sme7+Bme7+ZJme7+ggZZme7)");
   OutputTree.SetAlias("Nee7", "(See7+Bee7+ZJee7+ggZZee7)");
   OutputTree.SetAlias("Nmm7", "(Smm7+Bmm7+ZJmm7+ggZZmm7)");
   OutputTree.SetAlias("Nem8", "(Sem8+Bem8+ZJem8+ggZZem8)");
   OutputTree.SetAlias("Nme8", "(Sme8+Bme8+ZJme8+ggZZme8)");
   OutputTree.SetAlias("Nee8", "(See8+Bee8+ZJee8+ggZZee8)");
   OutputTree.SetAlias("Nmm8", "(Smm8+Bmm8+ZJmm8+ggZZmm8)");
   OutputTree.SetAlias("NBem7", "Fem7*Nem7");
   OutputTree.SetAlias("NBme7", "Fme7*Nem7");
   OutputTree.SetAlias("NBee7", "Fee7*Nem7");
   OutputTree.SetAlias("NBmm7", "Fmm7*Nem7");
   OutputTree.SetAlias("NBem8", "Fem8*Nem8");
   OutputTree.SetAlias("NBme8", "Fme8*Nem8");
   OutputTree.SetAlias("NBee8", "Fee8*Nem8");
   OutputTree.SetAlias("NBmm8", "Fmm8*Nem8");
   OutputTree.SetAlias("NZJem7", "FZJem7*Nem7");
   OutputTree.SetAlias("NZJme7", "FZJme7*Nme7");
   OutputTree.SetAlias("NZJee7", "FZJee7*Nee7");
   OutputTree.SetAlias("NZJmm7", "FZJmm7*Nmm7");
   OutputTree.SetAlias("NZJem8", "FZJem8*Nem8");
   OutputTree.SetAlias("NZJme8", "FZJme8*Nme8");
   OutputTree.SetAlias("NZJee8", "FZJee8*Nee8");
   OutputTree.SetAlias("NZJmm8", "FZJmm8*Nmm8");
   OutputTree.SetAlias("NggZZem7", "FggZZem7*Nem7");
   OutputTree.SetAlias("NggZZme7", "FggZZme7*Nme7");
   OutputTree.SetAlias("NggZZee7", "FggZZee7*Nee7");
   OutputTree.SetAlias("NggZZmm7", "FggZZmm7*Nmm7");
   OutputTree.SetAlias("NggZZem8", "FggZZem8*Nem8");
   OutputTree.SetAlias("NggZZme8", "FggZZme8*Nme8");
   OutputTree.SetAlias("NggZZee8", "FggZZee8*Nee8");
   OutputTree.SetAlias("NggZZmm8", "FggZZmm8*Nmm8");
   OutputTree.SetAlias("NB7", "(NBem7+NBme7+NBee7+NBmm7)");
   OutputTree.SetAlias("NB8", "(NBem8+NBme8+NBee8+NBmm8)");
   OutputTree.SetAlias("NZJ7", "(NZJem7+NZJme7+NZJee7+NZJmm7)");
   OutputTree.SetAlias("NZJ8", "(NZJem8+NZJme8+NZJee8+NZJmm8)");
   OutputTree.SetAlias("NggZZ7", "(NggZZem7+NggZZme7+NggZZee+NggZZmm7)");
   OutputTree.SetAlias("NggZZ8", "(NggZZem8+NggZZme8+NggZZee+NggZZmm8)");

   OutputTree.SetAlias("A3ZZPhase1", "(A3ZZPhase+(A3ZZA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A3ZZPhase2", "(A3ZZPhase1-int(A3ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3ZZPrimaryPhase", "(A3ZZPhase2+(A3ZZPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2ZZPhase1", "(A2ZZPhase+(A2ZZA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A2ZZPhase2", "(A2ZZPhase1-int(A2ZZPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2ZZPrimaryPhase", "(A2ZZPhase2+(A2ZZPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A3ZAPhase1", "(A3ZAPhase+(A3ZAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A3ZAPhase2", "(A3ZAPhase1-int(A3ZAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3ZAPrimaryPhase", "(A3ZAPhase2+(A3ZAPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2ZAPhase1", "(A2ZAPhase+(A2ZAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A2ZAPhase2", "(A2ZAPhase1-int(A2ZAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2ZAPrimaryPhase", "(A2ZAPhase2+(A2ZAPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A3AAPhase1", "(A3AAPhase+(A3AAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A3AAPhase2", "(A3AAPhase1-int(A3AAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A3AAPrimaryPhase", "(A3AAPhase2+(A3AAPhase2<0)*2*3.1415926535)");
   OutputTree.SetAlias("A2AAPhase1", "(A2AAPhase+(A2AAA1ZZ<0)*3.1415926535)");
   OutputTree.SetAlias("A2AAPhase2", "(A2AAPhase1-int(A2AAPhase1/(2*3.1415926535))*2*3.1415926535)");
   OutputTree.SetAlias("A2AAPrimaryPhase", "(A2AAPhase2+(A2AAPhase2<0)*2*3.1415926535)");


   OutputTree.Write();
   File.Close();

   return 0;
}





