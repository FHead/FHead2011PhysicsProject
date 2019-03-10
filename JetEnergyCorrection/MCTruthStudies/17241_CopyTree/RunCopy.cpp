#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

int main(int argc, char *argv[])
{
   string InputFileName = "/eos/cms/store/group/phys_jetmet/magda/AK4chs_noPU_GT/QCD_Pt-15to7000_TuneCP5_Flat2017_13TeV_pythia8/noPU2017/180306_140439//0001/JRA_1313.root";
   string OutputFileName = "OutputFile.root";
   string Algorithm = "ak4pfchs";
   int Lumi = 1;

   if(argc != 5)
   {
      cerr << "Usage: " << argv[0] << " InputFile OutputFile Algorithm Lumi" << endl;
      return -1;
   }

   InputFileName = argv[1];
   OutputFileName = argv[2];
   Algorithm = argv[3];
   Lumi = atoi(argv[4]);

   TFile InputFile(InputFileName.c_str());

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   OutputFile.mkdir(Algorithm.c_str());
   OutputFile.cd(Algorithm.c_str());

   TTree *InputTree = (TTree *)InputFile.Get("ak4pfchs/t");

   TTree *OutputTree = InputTree->CopyTree(Form("lumi == %d", Lumi));

   OutputTree->Write();

   OutputFile.Close();

   InputFile.Close();

   return 0;
}




