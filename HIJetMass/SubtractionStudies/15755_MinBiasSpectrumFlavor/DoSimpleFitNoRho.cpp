#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"

#include "SetStyle.h"
#include "DataHelper.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   double AbsEtaMin = 0;
   double AbsEtaMax = 0.5;

   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " AbsEtaMin AbsEtaMax" << endl;
      return -1;
   }

   AbsEtaMin = atof(argv[1]);
   AbsEtaMax = atof(argv[2]);

   DataHelper DHFile("SimpleFitParametersData.dh");

   SetThesisStyle();

   TFile File("Result/HydjetMBDragos2_0.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   string Model = "[0]*max(tanh([1]*(x-[2])),0)*(exp(-[3]*x)+[4]*exp(-[5]*x)+[6]*exp(-[7]*x)+[8]*exp(-[9]*x))";
   TF1 F("F", Model.c_str(), 0, 20);
   F.SetParameter(0, 1e6);
   F.SetParameter(1, 50);             F.FixParameter(1, 70);
   F.SetParameter(2, 0.158);          // F.FixParameter(2, 0.158);
   F.SetParameter(3, 1.5);
   F.SetParameter(4, -1);
   F.SetParameter(5, 4.5);
   F.SetParameter(6, 0.003);
   F.SetParameter(7, 0.5);
   F.SetParameter(8, 0.0003);
   F.SetParameter(9, 0.3);

   TH1D HPT("HPT", ";PT;", 500, 0, 20);
   Tree->Draw("PT>>HPT", Form("abs(Eta) < %f && abs(Eta) >= %f", AbsEtaMax, AbsEtaMin));

   F.SetParLimits(6, 0.003, 0.003);
   F.SetParLimits(7, 0.5, 0.5);
   F.SetParLimits(8, 0.0003, 0.0003);
   F.SetParLimits(9, 0.3, 0.3);
   HPT.Fit(&F);
   
   F.SetParLimits(6, 0.0001, 0.01);
   F.SetParLimits(7, 0.1, 1.0);
   HPT.Fit(&F);
   
   F.SetParLimits(8, 0.00001, 0.001);
   F.SetParLimits(9, 0.2, 0.6);
   HPT.Fit(&F);
   
   TCanvas Canvas;
   Canvas.SetLogy();

   HPT.Draw();

   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%.1f_%.1f.png", AbsEtaMin, AbsEtaMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%.1f_%.1f.C"  , AbsEtaMin, AbsEtaMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%.1f_%.1f.eps", AbsEtaMin, AbsEtaMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%.1f_%.1f.pdf", AbsEtaMin, AbsEtaMax));

   cerr << "FITRESULT";
   for(int i = 0; i < 10; i++)
      cerr << " " << F.GetParameter(i);
   cerr << endl;

   double RhoBin[6+1] = {0, 50, 100, 150, 200, 250, 350};

   for(int i = 0; i < 6; i++)
   {
      double RhoMin = RhoBin[i];
      double RhoMax = RhoBin[i+1];

      string State = Form("SimpleFit_%.2f_%.2f_%.0f_%.0f", AbsEtaMin, AbsEtaMax, RhoMin, RhoMax);

      DHFile[State]["Model"] = Model;
      DHFile[State]["FitMin"] = 0;
      DHFile[State]["FitMax"] = 20;

      for(int i = 0; i < 10; i++)
      {
         string Key = Form("P%d", i);
         DHFile[State][Key] = F.GetParameter(i);

         Key = Form("ErrorP%d", i);
         DHFile[State][Key] = F.GetParError(i);
      }
   }

   File.Close();

   DHFile.SaveToFile("SimpleFitParametersData.dh");

   return 0;
}




