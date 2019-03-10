#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "CustomAssert.h"
#include "CommandLine.h"

#define MAX 1024

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> Files  = CL.GetStringVector("File");
   vector<int> Indices   = CL.GetIntVector("Index");

   Assert(Files.size() == Indices.size(), "Number of files is not the same as number of indices");

   string TreeName       = CL.Get("Tree", "OutputTree");
   string OutputFileName = CL.Get("OutputFileName", "Merged.root");

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree OutputTree(TreeName.c_str(), "Merged tree");

   int TreeIndex;
   int NJet;
   double RefPT[MAX], RefEta[MAX], RefPhi[MAX];
   double PUPT[MAX], PUEta[MAX], PUPhi[MAX];
   double NoPUPT[MAX], NoPUEta[MAX], NoPUPhi[MAX];
   double RecoDR[MAX], OOA[MAX];
   double NPU[MAX], Rho[MAX], Weight[MAX], PTHat[MAX];
   int Run[MAX], Lumi[MAX], Event[MAX];

   OutputTree.Branch("Index", &TreeIndex, "Index/I");
   OutputTree.Branch("NJet", &NJet, "NJet/I");
   OutputTree.Branch("RefPT", &RefPT, "RefPT[NJet]/D");
   OutputTree.Branch("RefEta", &RefEta, "RefEta[NJet]/D");
   OutputTree.Branch("RefPhi", &RefPhi, "RefPhi[NJet]/D");
   OutputTree.Branch("PUPT", &PUPT, "PUPT[NJet]/D");
   OutputTree.Branch("PUEta", &PUEta, "PUEta[NJet]/D");
   OutputTree.Branch("PUPhi", &PUPhi, "PUPhi[NJet]/D");
   OutputTree.Branch("NoPUPT", &NoPUPT, "NoPUPT[NJet]/D");
   OutputTree.Branch("NoPUEta", &NoPUEta, "NoPUEta[NJet]/D");
   OutputTree.Branch("NoPUPhi", &NoPUPhi, "NoPUPhi[NJet]/D");
   OutputTree.Branch("RecoDR", &RecoDR, "RecoDR[NJet]/D");
   OutputTree.Branch("OOA", &OOA, "OOA[NJet]/D");
   OutputTree.Branch("NPU", &NPU, "NPU[NJet]/D");
   OutputTree.Branch("Rho", &Rho, "Rho[NJet]/D");
   OutputTree.Branch("Weight", &Weight, "Weight[NJet]/D");
   OutputTree.Branch("PTHat", &PTHat, "PTHat[NJet]/D");
   OutputTree.Branch("Run", &Run, "Run[NJet]/I");
   OutputTree.Branch("Lumi", &Lumi, "Lumi[NJet]/I");
   OutputTree.Branch("Event", &Event, "Event[NJet]/I");

   double tRefPT, tRefEta, tRefPhi;
   double tPUPT, tPUEta, tPUPhi;
   double tNoPUPT, tNoPUEta, tNoPUPhi;
   double tRecoDR, tOOA;
   double tNPU, tRho, tWeight, tPTHat;
   int tRun, tLumi, tEvent;

   for(int i = 0; i < (int)Files.size(); i++)
   {
      TFile File(Files[i].c_str());

      TTree *Tree = (TTree *)File.Get(TreeName.c_str());
      if(Tree == NULL)
      {
         File.Close();
         continue;
      }

      Tree->SetBranchAddress("RefPT", &tRefPT);
      Tree->SetBranchAddress("RefEta", &tRefEta);
      Tree->SetBranchAddress("RefPhi", &tRefPhi);
      Tree->SetBranchAddress("PUPT", &tPUPT);
      Tree->SetBranchAddress("PUEta", &tPUEta);
      Tree->SetBranchAddress("PUPhi", &tPUPhi);
      Tree->SetBranchAddress("NoPUPT", &tNoPUPT);
      Tree->SetBranchAddress("NoPUEta", &tNoPUEta);
      Tree->SetBranchAddress("NoPUPhi", &tNoPUPhi);
      Tree->SetBranchAddress("RecoDR", &tRecoDR);
      Tree->SetBranchAddress("OOA", &tOOA);
      Tree->SetBranchAddress("NPU", &tNPU);
      Tree->SetBranchAddress("Rho", &tRho);
      Tree->SetBranchAddress("Weight", &tWeight);
      Tree->SetBranchAddress("PTHat", &tPTHat);
      Tree->SetBranchAddress("Run", &tRun);
      Tree->SetBranchAddress("Lumi", &tLumi);
      Tree->SetBranchAddress("Event", &tEvent);

      int EntryCount = Tree->GetEntries();

      if(EntryCount == 0)
      {
         File.Close();
         continue;
      }

      Tree->GetEntry(0);
   
      TreeIndex = Indices[i];
      NJet = EntryCount;

      for(int iE = 0; iE < EntryCount; iE++)
      {
         Tree->GetEntry(iE);
      
         NPU[iE] = tNPU;
         Rho[iE] = tRho;
         Weight[iE] = tWeight;
         PTHat[iE] = tPTHat;
         Run[iE] = tRun;
         Lumi[iE] = tLumi;
         Event[iE] = tEvent;

         RefPT[iE] = tRefPT;
         RefEta[iE] = tRefEta;
         RefPhi[iE] = tRefPhi;
         PUPT[iE] = tPUPT;
         PUEta[iE] = tPUEta;
         PUPhi[iE] = tPUPhi;
         NoPUPT[iE] = tNoPUPT;
         NoPUEta[iE] = tNoPUEta;
         NoPUPhi[iE] = tNoPUPhi;
         OOA[iE] = tOOA;
         RecoDR[iE] = tRecoDR;
      }

      OutputTree.Fill();

      File.Close();
   }

   OutputFile.cd();
   OutputTree.Write();
   OutputFile.Close();

   return 0;
}





