#include <iostream>
using namespace std;

#include "TNtuple.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"

int main()
{
   TFile InputFile("HZZ4l_Prophecy4f_125_100K_tree_11521.root");
   TTree *InputTree = (TTree *)InputFile.Get("zz4lTree/probe_tree");

   double L11, L33, L44, L13, L14, L34, LB;
   double I11, I33, I44, I13, I14, I34, IB;
   double L11Up, L33Up, L44Up, L13Up, L14Up, L34Up, LBUp;
   double I11Up, I33Up, I44Up, I13Up, I14Up, I34Up, IBUp;
   double L11Down, L33Down, L44Down, L13Down, L14Down, L34Down, LBDown;
   double I11Down, I33Down, I44Down, I13Down, I14Down, I34Down, IBDown;

   InputTree->SetBranchAddress("Likelihood_ExtSig1", &L11);
   InputTree->SetBranchAddress("Likelihood_ExtSig3", &L33);
   InputTree->SetBranchAddress("Likelihood_ExtSig4", &L44);
   InputTree->SetBranchAddress("Likelihood_ExtSig13", &L13);
   InputTree->SetBranchAddress("Likelihood_ExtSig14", &L14);
   InputTree->SetBranchAddress("Likelihood_ExtSig34", &L34);
   InputTree->SetBranchAddress("Likelihood_EffMEE", &LB);
   InputTree->SetBranchAddress("Likelihood_ExtSig1_Integral", &I11);
   InputTree->SetBranchAddress("Likelihood_ExtSig3_Integral", &I33);
   InputTree->SetBranchAddress("Likelihood_ExtSig4_Integral", &I44);
   InputTree->SetBranchAddress("Likelihood_ExtSig13_Integral", &I13);
   InputTree->SetBranchAddress("Likelihood_ExtSig14_Integral", &I14);
   InputTree->SetBranchAddress("Likelihood_ExtSig34_Integral", &I34);
   InputTree->SetBranchAddress("Likelihood_EffMEE_Integral", &IB);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig1", &L11Up);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig3", &L33Up);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig4", &L44Up);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig13", &L13Up);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig14", &L14Up);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig34", &L34Up);
   InputTree->SetBranchAddress("LikelihoodUp_EffMEE", &LBUp);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig1_Integral", &I11Up);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig3_Integral", &I33Up);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig4_Integral", &I44Up);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig13_Integral", &I13Up);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig14_Integral", &I14Up);
   InputTree->SetBranchAddress("LikelihoodUp_ExtSig34_Integral", &I34Up);
   InputTree->SetBranchAddress("LikelihoodUp_EffMEE_Integral", &IBUp);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig1", &L11Down);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig3", &L33Down);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig4", &L44Down);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig13", &L13Down);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig14", &L14Down);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig34", &L34Down);
   InputTree->SetBranchAddress("LikelihoodDown_EffMEE", &LBDown);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig1_Integral", &I11Down);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig3_Integral", &I33Down);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig4_Integral", &I44Down);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig13_Integral", &I13Down);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig14_Integral", &I14Down);
   InputTree->SetBranchAddress("LikelihoodDown_ExtSig34_Integral", &I34Down);
   InputTree->SetBranchAddress("LikelihoodDown_EffMEE_Integral", &IBDown);

   string BranchList = "V11a:I11a:V33a:I33a:V44a:I44a:V13a:I13a:V14a:I14a:V34a:I34a:VBa:IBa";
   BranchList = BranchList + ":V11b:I11b:V33b:I33b:V44b:I44b:V13b:I13b:V14b:I14b:V34b:I34b:VBb:IBb";
   double V11a, I11a, V33a, I33a, V44a, I44a, V13a, I13a, V14a, I14a, V34a, I34a, VBa, IBa;
   double V11b, I11b, V33b, I33b, V44b, I44b, V13b, I13b, V14b, I14b, V34b, I34b, VBb, IBb;

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
      IB = IB / 10;
      I11 = I11 / 10;
      I33 = I33 / 10;
      I44 = I44 / 10;
      I13 = I13 / 10;
      I14 = I14 / 10;
      I34 = I34 / 10;

      V11a = (L11 * I11 + L11Up * I11Up + L11Down * I11Down) / 3;   V11b = (L11Up * I11Up - L11Down * I11Down) / 2;
      V33a = (L33 * I33 + L33Up * I33Up + L33Down * I33Down) / 3;   V33b = (L33Up * I33Up - L33Down * I33Down) / 2;
      V44a = (L44 * I44 + L44Up * I44Up + L44Down * I44Down) / 3;   V44b = (L44Up * I44Up - L44Down * I44Down) / 2;
      V13a = (L13 * I13 + L13Up * I13Up + L13Down * I13Down) / 3;   V13b = (L13Up * I13Up - L13Down * I13Down) / 2;
      V14a = (L14 * I14 + L14Up * I14Up + L14Down * I14Down) / 3;   V14b = (L14Up * I14Up - L14Down * I14Down) / 2;
      V34a = (L34 * I34 + L34Up * I34Up + L34Down * I34Down) / 3;   V34b = (L34Up * I34Up - L34Down * I34Down) / 2;
      VBa = (LB * IB + LBUp * IBUp + LBDown * IBDown) / 3;          VBb = (LBUp * IBUp - LBDown * IBDown) / 2;
      
      I11a = (I11 + I11Up + I11Down) / 3;   I11b = (I11Up - I11Down) / 2;
      I33a = (I33 + I33Up + I33Down) / 3;   I33b = (I33Up - I33Down) / 2;
      I44a = (I44 + I44Up + I44Down) / 3;   I44b = (I44Up - I44Down) / 2;
      I13a = (I13 + I13Up + I13Down) / 3;   I13b = (I13Up - I13Down) / 2;
      I14a = (I14 + I14Up + I14Down) / 3;   I14b = (I14Up - I14Down) / 2;
      I34a = (I34 + I34Up + I34Down) / 3;   I34b = (I34Up - I34Down) / 2;
      IBa = (IB + IBUp + IBDown) / 3;       IBb = (IBUp - IBDown) / 2;

      Branches[0] = V11a;    Branches[2] = V33a;    Branches[4] = V44a;
      Branches[1] = I11a;    Branches[3] = I33a;    Branches[5] = I44a;

      Branches[6] = V13a;    Branches[8] = V14a;    Branches[10] = V34a;   Branches[12] = VBa;
      Branches[7] = I13a;    Branches[9] = I14a;    Branches[11] = I34a;   Branches[13] = IBa;

      Branches[14] = V11b;   Branches[16] = V33b;   Branches[18] = V44b;
      Branches[15] = I11b;   Branches[17] = I33b;   Branches[19] = I44b;

      Branches[20] = V13b;   Branches[22] = V14b;   Branches[24] = V34b;   Branches[16] = VBb;
      Branches[21] = I13b;   Branches[23] = I14b;   Branches[25] = I34b;   Branches[17] = IBb;

      OutputTree.Fill(Branches);
   }

   OutputFile.cd();
   OutputTree.Write();

   InputFile.Close();

   return 0;
}








