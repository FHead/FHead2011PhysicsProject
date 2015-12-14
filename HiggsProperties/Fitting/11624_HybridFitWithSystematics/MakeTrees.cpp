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
   map<double, vector<double> > Integrals = ReadIntegral("AllIntegralsCentral");
   map<double, vector<double> > IntegralsUp = ReadIntegral("AllIntegralsLeptonUp");
   map<double, vector<double> > IntegralsDown = ReadIntegral("AllIntegralsLeptonDown");

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
   double L11Up, L22Up, L33Up, L44Up, L55Up, L12Up, L13Up, L14Up, L15Up, L23Up, L24Up, L25Up, L34Up, L35Up, L45Up, LBUp;
   double I11Up, I22Up, I33Up, I44Up, I55Up, I12Up, I13Up, I14Up, I15Up, I23Up, I24Up, I25Up, I34Up, I35Up, I45Up, IBUp;
   double L11Down, L22Down, L33Down, L44Down, L55Down, L12Down, L13Down, L14Down, L15Down, L23Down, L24Down, L25Down, L34Down, L35Down, L45Down, LBDown;
   double I11Down, I22Down, I33Down, I44Down, I55Down, I12Down, I13Down, I14Down, I15Down, I23Down, I24Down, I25Down, I34Down, I35Down, I45Down, IBDown;
   float Mass = 125;

   InputTree->SetBranchAddress("Hybrid_A1RA1R", &L11);
   InputTree->SetBranchAddress("Hybrid_A2RA2R", &L22);
   InputTree->SetBranchAddress("Hybrid_A3RA3R", &L33);
   InputTree->SetBranchAddress("Hybrid_A3RI3I", &L44);
   InputTree->SetBranchAddress("Hybrid_A2RI2I", &L55);
   InputTree->SetBranchAddress("Hybrid_A1RA2R", &L12);
   InputTree->SetBranchAddress("Hybrid_A1RA3R", &L13);
   InputTree->SetBranchAddress("Hybrid_A1RA3I", &L14);
   InputTree->SetBranchAddress("Hybrid_A1RA2I", &L15);
   InputTree->SetBranchAddress("Hybrid_A2RA3R", &L23);
   InputTree->SetBranchAddress("Hybrid_A2IA3R", &L24);   // [hic]
   InputTree->SetBranchAddress("Hybrid_A2RA2I", &L25);
   InputTree->SetBranchAddress("Hybrid_A3RA3I", &L34);
   InputTree->SetBranchAddress("Hybrid_A2RA3I", &L35);   // [hic]
   InputTree->SetBranchAddress("Hybrid_A2IA3I", &L45);
   InputTree->SetBranchAddress("Hybrid_Background", &LB);
   InputTree->SetBranchAddress("Hybrid_A1RA1R_LeptonUp", &L11Up);
   InputTree->SetBranchAddress("Hybrid_A2RA2R_LeptonUp", &L22Up);
   InputTree->SetBranchAddress("Hybrid_A3RA3R_LeptonUp", &L33Up);
   InputTree->SetBranchAddress("Hybrid_A3RI3I_LeptonUp", &L44Up);
   InputTree->SetBranchAddress("Hybrid_A2RI2I_LeptonUp", &L55Up);
   InputTree->SetBranchAddress("Hybrid_A1RA2R_LeptonUp", &L12Up);
   InputTree->SetBranchAddress("Hybrid_A1RA3R_LeptonUp", &L13Up);
   InputTree->SetBranchAddress("Hybrid_A1RA3I_LeptonUp", &L14Up);
   InputTree->SetBranchAddress("Hybrid_A1RA2I_LeptonUp", &L15Up);
   InputTree->SetBranchAddress("Hybrid_A2RA3R_LeptonUp", &L23Up);
   InputTree->SetBranchAddress("Hybrid_A2RA3I_LeptonUp", &L24Up);
   InputTree->SetBranchAddress("Hybrid_A2RA2I_LeptonUp", &L25Up);
   InputTree->SetBranchAddress("Hybrid_A3RA3I_LeptonUp", &L34Up);
   InputTree->SetBranchAddress("Hybrid_A2IA3R_LeptonUp", &L35Up);
   InputTree->SetBranchAddress("Hybrid_A2IA3I_LeptonUp", &L45Up);
   InputTree->SetBranchAddress("Hybrid_Background_LeptonUp", &LBUp);
   InputTree->SetBranchAddress("Hybrid_A1RA1R_LeptonDown", &L11Down);
   InputTree->SetBranchAddress("Hybrid_A2RA2R_LeptonDown", &L22Down);
   InputTree->SetBranchAddress("Hybrid_A3RA3R_LeptonDown", &L33Down);
   InputTree->SetBranchAddress("Hybrid_A3RI3I_LeptonDown", &L44Down);
   InputTree->SetBranchAddress("Hybrid_A2RI2I_LeptonDown", &L55Down);
   InputTree->SetBranchAddress("Hybrid_A1RA2R_LeptonDown", &L12Down);
   InputTree->SetBranchAddress("Hybrid_A1RA3R_LeptonDown", &L13Down);
   InputTree->SetBranchAddress("Hybrid_A1RA3I_LeptonDown", &L14Down);
   InputTree->SetBranchAddress("Hybrid_A1RA2I_LeptonDown", &L15Down);
   InputTree->SetBranchAddress("Hybrid_A2RA3R_LeptonDown", &L23Down);
   InputTree->SetBranchAddress("Hybrid_A2RA3I_LeptonDown", &L24Down);
   InputTree->SetBranchAddress("Hybrid_A2RA2I_LeptonDown", &L25Down);
   InputTree->SetBranchAddress("Hybrid_A3RA3I_LeptonDown", &L34Down);
   InputTree->SetBranchAddress("Hybrid_A2IA3R_LeptonDown", &L35Down);
   InputTree->SetBranchAddress("Hybrid_A2IA3I_LeptonDown", &L45Down);
   InputTree->SetBranchAddress("Hybrid_Background_LeptonDown", &LBDown);
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

      double I11 = GetIntegral(Integrals, Mass, 1); 
      double I22 = GetIntegral(Integrals, Mass, 2); 
      double I33 = GetIntegral(Integrals, Mass, 4); 
      double I44 = GetIntegral(Integrals, Mass, 5); 
      double I55 = GetIntegral(Integrals, Mass, 3); 
      double I12 = GetIntegral(Integrals, Mass, 6); 
      double I13 = GetIntegral(Integrals, Mass, 8); 
      double I14 = GetIntegral(Integrals, Mass, 9); 
      double I15 = GetIntegral(Integrals, Mass, 7); 
      double I23 = GetIntegral(Integrals, Mass, 11);
      double I24 = GetIntegral(Integrals, Mass, 13);
      double I25 = GetIntegral(Integrals, Mass, 10);
      double I34 = GetIntegral(Integrals, Mass, 15);
      double I35 = GetIntegral(Integrals, Mass, 12);
      double I45 = GetIntegral(Integrals, Mass, 14);
      double IB = GetIntegral(Integrals, Mass, 0);  
      
      double I11Up = GetIntegral(IntegralsUp, Mass, 1); 
      double I22Up = GetIntegral(IntegralsUp, Mass, 2); 
      double I33Up = GetIntegral(IntegralsUp, Mass, 4); 
      double I44Up = GetIntegral(IntegralsUp, Mass, 5); 
      double I55Up = GetIntegral(IntegralsUp, Mass, 3); 
      double I12Up = GetIntegral(IntegralsUp, Mass, 6); 
      double I13Up = GetIntegral(IntegralsUp, Mass, 8); 
      double I14Up = GetIntegral(IntegralsUp, Mass, 9); 
      double I15Up = GetIntegral(IntegralsUp, Mass, 7); 
      double I23Up = GetIntegral(IntegralsUp, Mass, 11);
      double I24Up = GetIntegral(IntegralsUp, Mass, 13);
      double I25Up = GetIntegral(IntegralsUp, Mass, 15);
      double I34Up = GetIntegral(IntegralsUp, Mass, 10);
      double I35Up = GetIntegral(IntegralsUp, Mass, 12);
      double I45Up = GetIntegral(IntegralsUp, Mass, 14);
      double IBUp = GetIntegral(IntegralsUp, Mass, 0);  
      
      double I11Down = GetIntegral(IntegralsDown, Mass, 1); 
      double I22Down = GetIntegral(IntegralsDown, Mass, 2); 
      double I33Down = GetIntegral(IntegralsDown, Mass, 4); 
      double I44Down = GetIntegral(IntegralsDown, Mass, 5); 
      double I55Down = GetIntegral(IntegralsDown, Mass, 3); 
      double I12Down = GetIntegral(IntegralsDown, Mass, 6); 
      double I13Down = GetIntegral(IntegralsDown, Mass, 8); 
      double I14Down = GetIntegral(IntegralsDown, Mass, 9); 
      double I15Down = GetIntegral(IntegralsDown, Mass, 7); 
      double I23Down = GetIntegral(IntegralsDown, Mass, 11);
      double I24Down = GetIntegral(IntegralsDown, Mass, 13);
      double I25Down = GetIntegral(IntegralsDown, Mass, 15);
      double I34Down = GetIntegral(IntegralsDown, Mass, 10);
      double I35Down = GetIntegral(IntegralsDown, Mass, 12);
      double I45Down = GetIntegral(IntegralsDown, Mass, 14);
      double IBDown = GetIntegral(IntegralsDown, Mass, 0);  

      FourVector L1, L2, L3, L4;
      L1.SetPtEtaPhi(l1pt, l1eta, l1phi);
      L2.SetPtEtaPhi(l2pt, l2eta, l2phi);
      L3.SetPtEtaPhi(l3pt, l3eta, l3phi);
      L4.SetPtEtaPhi(l4pt, l4eta, l4phi);
      Mass = (L1 + L2 + L3 + L4).GetMass();

      V11a = (L11 + L11Up + L11Down) / 3;   V11b = (L11Up - L11Down) / 2;
      V22a = (L22 + L22Up + L22Down) / 3;   V22b = (L22Up - L22Down) / 2;
      V33a = (L33 + L33Up + L33Down) / 3;   V33b = (L33Up - L33Down) / 2;
      V44a = (L44 + L44Up + L44Down) / 3;   V44b = (L44Up - L44Down) / 2;
      V55a = (L55 + L55Up + L55Down) / 3;   V55b = (L55Up - L55Down) / 2;
      V12a = (L12 + L12Up + L12Down) / 3;   V12b = (L12Up - L12Down) / 2;
      V13a = (L13 + L13Up + L13Down) / 3;   V13b = (L13Up - L13Down) / 2;
      V14a = (L14 + L14Up + L14Down) / 3;   V14b = (L14Up - L14Down) / 2;
      V15a = (L15 + L15Up + L15Down) / 3;   V15b = (L15Up - L15Down) / 2;
      V23a = (L23 + L23Up + L23Down) / 3;   V23b = (L23Up - L23Down) / 2;
      V24a = (L24 + L24Up + L24Down) / 3;   V24b = (L24Up - L24Down) / 2;
      V25a = (L25 + L25Up + L25Down) / 3;   V25b = (L25Up - L25Down) / 2;   V25a = 0;   V25b = 0;
      V34a = (L34 + L34Up + L34Down) / 3;   V34b = (L34Up - L34Down) / 2;   V34a = 0;   V34b = 0;
      V35a = (L35 + L35Up + L35Down) / 3;   V35b = (L35Up - L35Down) / 2;
      V45a = (L45 + L45Up + L45Down) / 3;   V45b = (L45Up - L45Down) / 2;
      VBa = (LB + LBUp + LBDown) / 3;       VBb = (LBUp - LBDown) / 2;

      I11a = (I11 + I11Up + I11Down) / 3;   I11b = (I11Up - I11Down) / 2;
      I22a = (I22 + I22Up + I22Down) / 3;   I22b = (I22Up - I22Down) / 2;
      I33a = (I33 + I33Up + I33Down) / 3;   I33b = (I33Up - I33Down) / 2;
      I44a = (I44 + I44Up + I44Down) / 3;   I44b = (I44Up - I44Down) / 2;
      I55a = (I55 + I55Up + I55Down) / 3;   I55b = (I55Up - I55Down) / 2;
      I12a = (I12 + I12Up + I12Down) / 3;   I12b = (I12Up - I12Down) / 2;
      I13a = (I13 + I13Up + I13Down) / 3;   I13b = (I13Up - I13Down) / 2;
      I14a = (I14 + I14Up + I14Down) / 3;   I14b = (I14Up - I14Down) / 2;
      I15a = (I15 + I15Up + I15Down) / 3;   I15b = (I15Up - I15Down) / 2;
      I23a = (I23 + I23Up + I23Down) / 3;   I23b = (I23Up - I23Down) / 2;
      I24a = (I24 + I24Up + I24Down) / 3;   I24b = (I24Up - I24Down) / 2;
      I25a = (I25 + I25Up + I25Down) / 3;   I25b = (I25Up - I25Down) / 2;
      I34a = (I34 + I34Up + I34Down) / 3;   I34b = (I34Up - I34Down) / 2;
      I35a = (I35 + I35Up + I35Down) / 3;   I35b = (I35Up - I35Down) / 2;
      I45a = (I45 + I45Up + I45Down) / 3;   I45b = (I45Up - I45Down) / 2;
      IBa = (IB + IBUp + IBDown) / 3;       IBb = (IBUp - IBDown) / 2;

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







