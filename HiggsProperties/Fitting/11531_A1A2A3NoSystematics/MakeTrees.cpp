#include <iostream>
using namespace std;

#include "TNtuple.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"

int main()
{
   bool WithSystematics = true;

   TFile InputFile("HZZ4l_Prophecy4f_125_100K_tree_11521_BigSmeared.root");
   TTree *InputTree = (TTree *)InputFile.Get("zz4lTree/probe_tree");

   double L11, L22, L33, L44, L55, L12, L13, L14, L15, L23, L24, L25, L34, L35, L45, LB;
   double I11, I22, I33, I44, I55, I12, I13, I14, I15, I23, I24, I25, I34, I35, I45, IB;
   double L11Up, L22Up, L33Up, L44Up, L55Up, L12Up, L13Up, L14Up, L15Up, L23Up, L24Up, L25Up, L34Up, L35Up, L45Up, LBUp;
   double I11Up, I22Up, I33Up, I44Up, I55Up, I12Up, I13Up, I14Up, I15Up, I23Up, I24Up, I25Up, I34Up, I35Up, I45Up, IBUp;
   double L11Down, L22Down, L33Down, L44Down, L55Down, L12Down, L13Down, L14Down, L15Down, L23Down, L24Down, L25Down, L34Down, L35Down, L45Down, LBDown;
   double I11Down, I22Down, I33Down, I44Down, I55Down, I12Down, I13Down, I14Down, I15Down, I23Down, I24Down, I25Down, I34Down, I35Down, I45Down, IBDown;

   InputTree->SetBranchAddress("Likelihood_ExtSig1", &L11);
   InputTree->SetBranchAddress("Likelihood_ExtSig2", &L22);
   InputTree->SetBranchAddress("Likelihood_ExtSig3", &L33);
   InputTree->SetBranchAddress("Likelihood_ExtSig4", &L44);
   InputTree->SetBranchAddress("Likelihood_ExtSig5", &L55);
   InputTree->SetBranchAddress("Likelihood_ExtSig12", &L12);
   InputTree->SetBranchAddress("Likelihood_ExtSig13", &L13);
   InputTree->SetBranchAddress("Likelihood_ExtSig14", &L14);
   InputTree->SetBranchAddress("Likelihood_ExtSig15", &L15);
   InputTree->SetBranchAddress("Likelihood_ExtSig23", &L23);
   InputTree->SetBranchAddress("Likelihood_ExtSig24", &L24);
   InputTree->SetBranchAddress("Likelihood_ExtSig25", &L25);
   InputTree->SetBranchAddress("Likelihood_ExtSig34", &L34);
   InputTree->SetBranchAddress("Likelihood_ExtSig35", &L35);
   InputTree->SetBranchAddress("Likelihood_ExtSig45", &L45);
   InputTree->SetBranchAddress("Likelihood_EffMEE", &LB);
   InputTree->SetBranchAddress("Likelihood_ExtSig1_Integral", &I11);
   InputTree->SetBranchAddress("Likelihood_ExtSig2_Integral", &I22);
   InputTree->SetBranchAddress("Likelihood_ExtSig3_Integral", &I33);
   InputTree->SetBranchAddress("Likelihood_ExtSig4_Integral", &I44);
   InputTree->SetBranchAddress("Likelihood_ExtSig5_Integral", &I55);
   InputTree->SetBranchAddress("Likelihood_ExtSig12_Integral", &I12);
   InputTree->SetBranchAddress("Likelihood_ExtSig13_Integral", &I13);
   InputTree->SetBranchAddress("Likelihood_ExtSig14_Integral", &I14);
   InputTree->SetBranchAddress("Likelihood_ExtSig15_Integral", &I15);
   InputTree->SetBranchAddress("Likelihood_ExtSig23_Integral", &I23);
   InputTree->SetBranchAddress("Likelihood_ExtSig24_Integral", &I24);
   InputTree->SetBranchAddress("Likelihood_ExtSig25_Integral", &I25);
   InputTree->SetBranchAddress("Likelihood_ExtSig34_Integral", &I34);
   InputTree->SetBranchAddress("Likelihood_ExtSig35_Integral", &I35);
   InputTree->SetBranchAddress("Likelihood_ExtSig45_Integral", &I45);
   InputTree->SetBranchAddress("Likelihood_EffMEE_Integral", &IB);
   if(WithSystematics == true)
   {
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig1", &L11Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig2", &L22Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig3", &L33Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig4", &L44Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig5", &L55Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig12", &L12Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig13", &L13Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig14", &L14Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig15", &L15Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig23", &L23Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig24", &L24Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig25", &L25Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig34", &L34Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig35", &L35Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig45", &L45Up);
      InputTree->SetBranchAddress("LikelihoodUp_EffMEE", &LBUp);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig1_Integral", &I11Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig2_Integral", &I22Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig3_Integral", &I33Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig4_Integral", &I44Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig5_Integral", &I55Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig12_Integral", &I12Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig13_Integral", &I13Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig14_Integral", &I14Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig15_Integral", &I15Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig23_Integral", &I23Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig24_Integral", &I24Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig25_Integral", &I25Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig34_Integral", &I34Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig35_Integral", &I35Up);
      InputTree->SetBranchAddress("LikelihoodUp_ExtSig45_Integral", &I45Up);
      InputTree->SetBranchAddress("LikelihoodUp_EffMEE_Integral", &IBUp);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig1", &L11Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig2", &L22Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig3", &L33Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig4", &L44Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig5", &L55Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig12", &L12Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig13", &L13Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig14", &L14Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig15", &L15Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig23", &L23Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig24", &L24Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig25", &L25Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig34", &L34Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig35", &L35Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig45", &L45Down);
      InputTree->SetBranchAddress("LikelihoodDown_EffMEE", &LBDown);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig1_Integral", &I11Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig2_Integral", &I22Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig3_Integral", &I33Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig4_Integral", &I44Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig5_Integral", &I55Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig12_Integral", &I12Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig13_Integral", &I13Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig14_Integral", &I14Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig15_Integral", &I15Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig23_Integral", &I23Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig24_Integral", &I24Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig25_Integral", &I25Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig34_Integral", &I34Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig35_Integral", &I35Down);
      InputTree->SetBranchAddress("LikelihoodDown_ExtSig45_Integral", &I45Down);
      InputTree->SetBranchAddress("LikelihoodDown_EffMEE_Integral", &IBDown);
   }

   string BranchList = "";
   BranchList = BranchList + "V11a:V22a:V33a:V44a:V55a:V12a:V13a:V14a:V15a:V23a:V24a:V25a:V34a:V35a:V45a:VBa";
   BranchList = BranchList + ":I11a:I22a:I33a:I44a:I55a:I12a:I13a:I14a:I15a:I23a:I24a:I25a:I34a:I35a:I45a:IBa";
   BranchList = BranchList + ":V11b:V22b:V33b:V44b:V55b:V12b:V13b:V14b:V15b:V23b:V24b:V25b:V34b:V35b:V45b:VBb";
   BranchList = BranchList + ":I11b:I22b:I33b:I44b:I55b:I12b:I13b:I14b:I15b:I23b:I24b:I25b:I34b:I35b:I45b:IBb";
   
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

      LB = LB / 4;
      LBUp = LBUp / 4;
      LBDown = LBDown / 4;

      if(WithSystematics == true)
      {
         V11a = (L11 * I11 + L11Up * I11Up + L11Down * I11Down) / 3; V11b = (L11Up * I11Up - L11Down * I11Down) / 2;
         V22a = (L22 * I22 + L22Up * I22Up + L22Down * I22Down) / 3; V22b = (L22Up * I22Up - L22Down * I22Down) / 2;
         V33a = (L33 * I33 + L33Up * I33Up + L33Down * I33Down) / 3; V33b = (L33Up * I33Up - L33Down * I33Down) / 2;
         V44a = (L44 * I44 + L44Up * I44Up + L44Down * I44Down) / 3; V44b = (L44Up * I44Up - L44Down * I44Down) / 2;
         V55a = (L55 * I55 + L55Up * I55Up + L55Down * I55Down) / 3; V55b = (L55Up * I55Up - L55Down * I55Down) / 2;
         V12a = (L12 * I12 + L12Up * I12Up + L12Down * I12Down) / 3; V12b = (L12Up * I12Up - L12Down * I12Down) / 2;
         V13a = (L13 * I13 + L13Up * I13Up + L13Down * I13Down) / 3; V13b = (L13Up * I13Up - L13Down * I13Down) / 2;
         V14a = (L14 * I14 + L14Up * I14Up + L14Down * I14Down) / 3; V14b = (L14Up * I14Up - L14Down * I14Down) / 2;
         V15a = (L15 * I15 + L15Up * I15Up + L15Down * I15Down) / 3; V15b = (L15Up * I15Up - L15Down * I15Down) / 2;
         V23a = (L23 * I23 + L23Up * I23Up + L23Down * I23Down) / 3; V23b = (L23Up * I23Up - L23Down * I23Down) / 2;
         V24a = (L24 * I24 + L24Up * I24Up + L24Down * I24Down) / 3; V24b = (L24Up * I24Up - L24Down * I24Down) / 2;
         V25a = (L25 * I25 + L25Up * I25Up + L25Down * I25Down) / 3; V25b = (L25Up * I25Up - L25Down * I25Down) / 2;
         V34a = (L34 * I34 + L34Up * I34Up + L34Down * I34Down) / 3; V34b = (L34Up * I34Up - L34Down * I34Down) / 2;
         V35a = (L35 * I35 + L35Up * I35Up + L35Down * I35Down) / 3; V35b = (L35Up * I35Up - L35Down * I35Down) / 2;
         V45a = (L45 * I45 + L45Up * I45Up + L45Down * I45Down) / 3; V45b = (L45Up * I45Up - L45Down * I45Down) / 2;
         VBa = (LB * IB + LBUp * IBUp + LBDown * IBDown) / 3;        VBb = (LBUp * IBUp - LBDown * IBDown) / 2;

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
      }
      else
      {
         V11a = L11 * I11;   V11b = 0;
         V22a = L22 * I22;   V22b = 0;
         V33a = L33 * I33;   V33b = 0;
         V44a = L44 * I44;   V44b = 0;
         V55a = L55 * I55;   V55b = 0;
         V12a = L12 * I12;   V12b = 0;
         V13a = L13 * I13;   V13b = 0;
         V14a = L14 * I14;   V14b = 0;
         V15a = L15 * I15;   V15b = 0;
         V23a = L23 * I23;   V23b = 0;
         V24a = L24 * I24;   V24b = 0;
         V25a = L25 * I25;   V25b = 0;
         V34a = L34 * I34;   V34b = 0;
         V35a = L35 * I35;   V35b = 0;
         V45a = L45 * I45;   V45b = 0;
         VBa = LB * IB;      VBb = 0;

         I11a = I11;   I11b = 0;
         I22a = I22;   I22b = 0;
         I33a = I33;   I33b = 0;
         I44a = I44;   I44b = 0;
         I55a = I55;   I55b = 0;
         I12a = I12;   I12b = 0;
         I13a = I13;   I13b = 0;
         I14a = I14;   I14b = 0;
         I15a = I15;   I15b = 0;
         I23a = I23;   I23b = 0;
         I24a = I24;   I24b = 0;
         I25a = I25;   I25b = 0;
         I34a = I34;   I34b = 0;
         I35a = I35;   I35b = 0;
         I45a = I45;   I45b = 0;
         IBa = IB;     IBb = 0;
      }

      if(V11a == 0 && V22a == 0 && V33a == 0 && V44a == 0 && V55a == 0 && VBa == 0)
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

      OutputTree.Fill(Branches);
   }

   OutputFile.cd();
   OutputTree.Write();

   InputFile.Close();

   return 0;
}








