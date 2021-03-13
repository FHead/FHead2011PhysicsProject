#include <iostream>
using namespace std;

#include "TF1.h"
#include "TH1D.h"
#include "TFile.h"

#include "Messenger.h"
#include "CommandLine.h"
#include "CustomAssert.h"
#include "Code/DrawRandom.h"
#include "Code/TauHelperFunctions3.h"

#include "RhoCalculator.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("input");

   TFile File(InputFileName.c_str());

   HiEventTreeMessenger MHiEvent(File);
   PFTreeMessenger MPF(File);

   Assert(MHiEvent.Tree != nullptr, "HiEvent not found.");
   Assert(MPF.Tree != nullptr, "PF collection not found.");
   
   RhoModulationCalculator Modulation;

   int EntryCount = MHiEvent.Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      cout << "Processing event " << iE << endl;

      MHiEvent.GetEntry(iE);
      MPF.GetEntry(iE);

      double PionMass = 0.13957;
      vector<FourVector> PF;
      for(int iPF = 0; iPF < (int)MPF.ID->size(); iPF++)
      {
         if((*MPF.ID)[iPF] != 1)
            continue;
         FourVector P;
         P.SetPtEtaPhiMass((*MPF.PT)[iPF], (*MPF.Eta)[iPF], (*MPF.Phi)[iPF], PionMass);
         PF.push_back(P);
      }
      vector<double> ParametersFixPlane = Modulation.DoRhoModulationFit(PF, false, false);
      vector<double> ParametersRandomize = Modulation.DoRhoModulationFit(PF, false, true);

      cout << "Fix ";
      for(int i = 0; i < (int)ParametersFixPlane.size(); i++)
         cout << " " << ParametersFixPlane[i];
      cout << endl;
      cout << "Randomize ";
      for(int i = 0; i < (int)ParametersRandomize.size(); i++)
         cout << " " << ParametersRandomize[i];
      cout << endl;

      double Phi2 = -100, Phi3 = -100;
      int Stats = 0;

      vector<double> Parameters(18);

      double CosPhi2 = 0, SinPhi2 = 0, CosPhi3 = 0, SinPhi3 = 0;
      for(int iPF = 0; iPF < (int)MPF.ID->size(); iPF++)
      {
         if((*MPF.Eta)[iPF] < -1)   continue;
         if((*MPF.Eta)[iPF] > +1)   continue;
         if((*MPF.PT)[iPF] < 0.3)   continue;
         if((*MPF.PT)[iPF] > 3.0)   continue;
         if((*MPF.ID)[iPF] != 1)    continue;

         Stats = Stats + 1;

         CosPhi2 = CosPhi2 + cos(2 * (*MPF.Phi)[iPF]);
         SinPhi2 = SinPhi2 + sin(2 * (*MPF.Phi)[iPF]);
         
         CosPhi3 = CosPhi3 + cos(3 * (*MPF.Phi)[iPF]);
         SinPhi3 = SinPhi3 + sin(3 * (*MPF.Phi)[iPF]);
      }

      Phi2 = atan2(SinPhi2, CosPhi2) / 2;
      Phi3 = atan2(SinPhi3, CosPhi3) / 3;

      cout << "Stats = " << Stats << endl;

      if(Stats >= 100 && Phi2 > -100)
      {
         int BinCount = max(10, Stats / 30);

         TH1D HPhi("HPhi", ";#phi;Count", BinCount, -M_PI, M_PI);
         TH1D HFlatPhi("HFlatPhi", ";#phi;Count", BinCount, -M_PI, M_PI);

         for(int iPF = 0; iPF < (int)MPF.ID->size(); iPF++)
         {
            if((*MPF.Eta)[iPF] < -1)   continue;
            if((*MPF.Eta)[iPF] > +1)   continue;
            if((*MPF.PT)[iPF] < 0.3)   continue;
            if((*MPF.PT)[iPF] > 3.0)   continue;
            if((*MPF.ID)[iPF] != 1)    continue;

            HPhi.Fill((*MPF.Phi)[iPF]);
            HFlatPhi.Fill(DrawRandom(-M_PI, M_PI));
         }

         TF1 FFlow("FFlow", Form("[0]*(1+2*([1]*cos(2*(x-%f))+[2]*cos(3*(x-%f))))", Phi2, Phi3), -M_PI, M_PI);
         TF1 FLine("FLine", "[0]", -M_PI, M_PI);
         TF1 FFlowFull("FFlowFull", "[0]*(1+2*([1]*cos(2*(x-[2]))+[3]*cos(3*(x-[4]))))", -M_PI, M_PI);

         FFlow.SetParameters(10, 0, 0);
         FLine.SetParameter(0, 10);
         FFlowFull.SetParameters(10, 0, Phi2, 0, Phi3);

         for(int i = 0; i < 1; i++)
         {
            HPhi.Fit(&FFlow, "Q", "", -M_PI, M_PI);
            HPhi.Fit(&FLine, "Q", "", -M_PI, M_PI);
            HPhi.Fit(&FFlowFull, "Q", "", -M_PI, M_PI);
         }

         Parameters[0] = FFlow.GetParameter(0);
         Parameters[1] = FFlow.GetParameter(1);
         Parameters[2] = Phi2;
         Parameters[3] = FFlow.GetParameter(2);
         Parameters[4] = Phi3;
         Parameters[5] = FFlow.GetChisquare();
         Parameters[6] = BinCount - 3;
         Parameters[7] = FLine.GetChisquare();
         Parameters[8] = BinCount - 1;

         HFlatPhi.Fit(&FFlow, "Q");
         HFlatPhi.Fit(&FLine, "Q");
         HFlatPhi.Fit(&FFlowFull, "Q");

         Parameters[9]  = FFlow.GetParameter(0);
         Parameters[10] = FFlow.GetParameter(1);
         Parameters[11] = Phi2;
         Parameters[12] = FFlow.GetParameter(2);
         Parameters[13] = Phi3;
         Parameters[14] = FFlow.GetChisquare();
         Parameters[15] = BinCount - 3;
         Parameters[16] = FLine.GetChisquare();
         Parameters[17] = BinCount - 1;
      }

      for(int i = 0; i < (int)Parameters.size(); i++)
         cout << i << " " << Parameters[i] << endl;
   }

   File.Close();

   return 0;
}


