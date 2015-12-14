#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;

#include "TNtuple.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"

#include "Code/TauHelperFunctions2.h"

int main();
map<double, vector<double> > ReadIntegral(string FileName);
double GetIntegral(const map<double, vector<double> > &Integrals, double Mass, int Component);

int main()
{
   map<double, vector<double> > Integrals = ReadIntegral("AllIntegrals");

   TFile InputFile("HZZ4l_Prophecy4f_125_100K_tree_11521.root");
   TTree *InputTree = (TTree *)InputFile.Get("zz4lTree/probe_tree");

   float l1pt, l1eta, l1phi;
   float l2pt, l2eta, l2phi;
   float l3pt, l3eta, l3phi;
   float l4pt, l4eta, l4phi;

   InputTree->SetBranchAddress("l1pt", &l1pt);
   InputTree->SetBranchAddress("l1eta", &l1eta);
   InputTree->SetBranchAddress("l1phi", &l1phi);
   InputTree->SetBranchAddress("l2pt", &l2pt);
   InputTree->SetBranchAddress("l2eta", &l2eta);
   InputTree->SetBranchAddress("l2phi", &l2phi);
   InputTree->SetBranchAddress("l3pt", &l3pt);
   InputTree->SetBranchAddress("l3eta", &l3eta);
   InputTree->SetBranchAddress("l3phi", &l3phi);
   InputTree->SetBranchAddress("l4pt", &l4pt);
   InputTree->SetBranchAddress("l4eta", &l4eta);
   InputTree->SetBranchAddress("l4phi", &l4phi);

   double L11, L22, L33, L44, L55, L12, L13, L14, L15, L23, L24, L25, L34, L35, L45, LB;
   double I11, I22, I33, I44, I55, I12, I13, I14, I15, I23, I24, I25, I34, I35, I45, IB;
   float Mass = 125;

   InputTree->SetBranchAddress("Hybrid_A1RA1R_1e6", &L11);
   InputTree->SetBranchAddress("Hybrid_A2RA2R_1e6", &L22);
   InputTree->SetBranchAddress("Hybrid_A3RA3R_1e6", &L33);
   InputTree->SetBranchAddress("Hybrid_A3RI3I_1e6", &L44);
   InputTree->SetBranchAddress("Hybrid_A2RI2I_1e6", &L55);
   InputTree->SetBranchAddress("Hybrid_A1RA2R_1e6", &L12);
   InputTree->SetBranchAddress("Hybrid_A1RA3R_1e6", &L13);
   InputTree->SetBranchAddress("Hybrid_A1RA3I_1e6", &L14);
   InputTree->SetBranchAddress("Hybrid_A1RA2I_1e6", &L15);
   InputTree->SetBranchAddress("Hybrid_A2RA3R_1e6", &L23);
   InputTree->SetBranchAddress("Hybrid_A2IA3R_1e6", &L24);   // [hic]
   InputTree->SetBranchAddress("Hybrid_A2RA2I_1e6", &L25);
   InputTree->SetBranchAddress("Hybrid_A3RA3I_1e6", &L34);
   InputTree->SetBranchAddress("Hybrid_A2RA3I_1e6", &L35);   // [hic]
   InputTree->SetBranchAddress("Hybrid_A2IA3I_1e6", &L45);
   InputTree->SetBranchAddress("Hybrid_Background_1e6", &LB);
   // InputTree->SetBranchAddress("mass", &Mass);

   string BranchList = "";
   BranchList = BranchList + "V11a:V22a:V33a:V44a:V55a:V12a:V13a:V14a:V15a:V23a:V24a:V25a:V34a:V35a:V45a:VBa";
   BranchList = BranchList + ":I11a:I22a:I33a:I44a:I55a:I12a:I13a:I14a:I15a:I23a:I24a:I25a:I34a:I35a:I45a:IBa";
   BranchList = BranchList + ":V11b:V22b:V33b:V44b:V55b:V12b:V13b:V14b:V15b:V23b:V24b:V25b:V34b:V35b:V45b:VBb";
   BranchList = BranchList + ":I11b:I22b:I33b:I44b:I55b:I12b:I13b:I14b:I15b:I23b:I24b:I25b:I34b:I35b:I45b:IBb";
   BranchList = BranchList + ":Mass";
   
   double V11a, V22a, V33a, V44a, V55a, V12a, V13a, V14a, V15a, V23a, V24a, V25a, V34a, V35a, V45a, VBa;
   double I11a, I22a, I33a, I44a, I55a, I12a, I13a, I14a, I15a, I23a, I24a, I25a, I34a, I35a, I45a, IBa;
   double V11b, V22b, V33b, V44b, V55b, V12b, V13b, V14b, V15b, V23b, V24b, V25b, V34b, V35b, V45b, VBb;
   double I11b, I22b, I33b, I44b, I55b, I12b, I13b, I14b, I15b, I23b, I24b, I25b, I34b, I35b, I45b, IBb;

   TFile OutputFile("FitTree.root", "RECREATE");
   TNtuple OutputTree("OutputTree", "OutputTree", BranchList.c_str());

   float Branches[100] = {0};

   int EntryCount = InputTree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      InputTree->GetEntry(iE);

      FourVector L1, L2, L3, L4;
      L1.SetPtEtaPhi(l1pt, l1eta, l1phi);
      L2.SetPtEtaPhi(l2pt, l2eta, l2phi);
      L3.SetPtEtaPhi(l3pt, l3eta, l3phi);
      L4.SetPtEtaPhi(l4pt, l4eta, l4phi);
      Mass = (L1 + L2 + L3 + L4).GetMass();

      V11a = L11;   V11b = 0;
      V22a = L22;   V22b = 0;
      V33a = L33;   V33b = 0;
      V44a = L44;   V44b = 0;
      V55a = L55;   V55b = 0;
      V12a = L12;   V12b = 0;
      V13a = L13;   V13b = 0;
      V14a = L14;   V14b = 0;
      V15a = L15;   V15b = 0;
      V23a = L23;   V23b = 0;
      V24a = L24;   V24b = 0;
      V25a = L25;   V25b = 0;   V25a = 0;
      V34a = L34;   V34b = 0;   V34a = 0;
      V35a = L35;   V35b = 0;
      V45a = L45;   V45b = 0;
      VBa = LB;     VBb = 0;

      I11a = GetIntegral(Integrals, Mass, 1);    I11b = 0;
      I22a = GetIntegral(Integrals, Mass, 2);    I22b = 0;
      I33a = GetIntegral(Integrals, Mass, 4);    I33b = 0;
      I44a = GetIntegral(Integrals, Mass, 5);    I44b = 0;
      I55a = GetIntegral(Integrals, Mass, 3);    I55b = 0;
      I12a = GetIntegral(Integrals, Mass, 6);    I12b = 0;
      I13a = GetIntegral(Integrals, Mass, 8);    I13b = 0;
      I14a = GetIntegral(Integrals, Mass, 9);    I14b = 0;
      I15a = GetIntegral(Integrals, Mass, 7);    I15b = 0;
      I23a = GetIntegral(Integrals, Mass, 11);   I23b = 0;
      I24a = GetIntegral(Integrals, Mass, 13);   I24b = 0;   // [hic]
      I25a = GetIntegral(Integrals, Mass, 10);   I25b = 0;
      I34a = GetIntegral(Integrals, Mass, 15);   I34b = 0;
      I35a = GetIntegral(Integrals, Mass, 12);   I35b = 0;   // [hic]
      I45a = GetIntegral(Integrals, Mass, 14);   I45b = 0;
      IBa = GetIntegral(Integrals, Mass, 0);     IBb = 0;

      if(V11a == 0 && V22a == 0 && V33a == 0 && V44a == 0 && V55a == 0 && VBa == 0)
         continue;
      if(V11a > 0.9 || V22a > 0.9 || V33a > 0.9 || V44a > 0.9 || V55a > 0.9 || VBa > 0.9)
         continue;
      if(Mass >= 160 || Mass <= 100)
         continue;

      Branches[0] = V11a;   Branches[1] = V22a;   Branches[2] = V33a;   Branches[3] = V44a;   Branches[4] = V55a;
      Branches[5] = V12a;   Branches[6] = V13a;   Branches[7] = V14a;   Branches[8] = V15a;   Branches[9] = V23a;
      Branches[10] = V24a;  Branches[11] = V25a;  Branches[12] = V34a;  Branches[13] = V35a;  Branches[14] = V45a;
      Branches[15] = VBa;

      Branches[16] = I11a;  Branches[17] = I22a;  Branches[18] = I33a;  Branches[19] = I44a;  Branches[20] = I55a;
      Branches[21] = I12a;  Branches[22] = I13a;  Branches[23] = I14a;  Branches[24] = I15a;  Branches[25] = I23a;
      Branches[26] = I24a;  Branches[27] = I25a;  Branches[28] = I34a;  Branches[29] = I35a;  Branches[30] = I45a;
      Branches[31] = IBa;

      Branches[32] = V11b;  Branches[33] = V22b;  Branches[34] = V33b;  Branches[35] = V44b;  Branches[36] = V55b;
      Branches[37] = V12b;  Branches[38] = V13b;  Branches[39] = V14b;  Branches[40] = V15b;  Branches[41] = V23b;
      Branches[42] = V24b;  Branches[43] = V25b;  Branches[44] = V34b;  Branches[45] = V35b;  Branches[46] = V45b;
      Branches[47] = VBb;

      Branches[48] = I11b;  Branches[49] = I22b;  Branches[50] = I33b;  Branches[51] = I44b;  Branches[52] = I55b;
      Branches[53] = I12b;  Branches[54] = I13b;  Branches[55] = I14b;  Branches[56] = I15b;  Branches[57] = I23b;
      Branches[58] = I24b;  Branches[59] = I25b;  Branches[60] = I34b;  Branches[61] = I35b;  Branches[62] = I45b;
      Branches[63] = IBb;

      Branches[64] = Mass;

      OutputTree.Fill(Branches);
   }

   OutputFile.cd();
   OutputTree.Write();

   InputFile.Close();

   return 0;
}

map<double, vector<double> > ReadIntegral(string FileName)
{
   map<double, vector<double> > Integrals;

   ifstream in(FileName.c_str());

   while(in)
   {
      char line[10240] = "";
      in.getline(line, 10239, '\n');
      if(line[0] == '\0')
         continue;

      stringstream str(line);

      double Mass = -1;
      int Count = -1;
      str >> Mass >> Count;

      if(Mass < 0 || Count < 0)
         continue;

      vector<double> Temp;
      while(str)
      {
         double value = -999;
         str >> value;
         if(value < -998)
            continue;

         Temp.push_back(value);
      }

      Integrals.insert(pair<double, vector<double> >(Mass, Temp));
   }

   in.close();

   return Integrals;
}

double GetIntegral(const map<double, vector<double> > &Integrals, double Mass, int Component)
{
   if(Mass < Integrals.begin()->first)
      return 10000000000;

   double PreviousMass = -1;
   double PreviousValue = -1;
   for(map<double, vector<double> >::const_iterator iter = Integrals.begin(); iter != Integrals.end(); iter++)
   {
      if(iter->second.size() <= Component)
         return 10000000000;

      if(Mass >= iter->first)
      {
         PreviousMass = iter->first;
         PreviousValue = iter->second[Component];
         continue;
      }

      double CurrentMass = iter->first;
      double CurrentValue = iter->second[Component];

      return (Mass - PreviousMass) / (CurrentMass - PreviousMass) * (CurrentValue - PreviousValue) + PreviousValue;
   }

   return 10000000000;
}







