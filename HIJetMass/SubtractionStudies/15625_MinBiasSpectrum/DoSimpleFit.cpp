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
   double RhoMin = 0;
   double RhoMax = 50;

   if(argc != 5)
   {
      cerr << "Usage: " << argv[0] << " AbsEtaMin AbsEtaMax RhoMin RhoMax" << endl;
      return -1;
   }

   AbsEtaMin = atof(argv[1]);
   AbsEtaMax = atof(argv[2]);
   RhoMin = atof(argv[3]);
   RhoMax = atof(argv[4]);

   // DataHelper DHFile("SimpleFitParameters.dh");
   DataHelper DHFile("SimpleFitParametersMBCymbal.dh");

   SetThesisStyle();

   // TFile File("Result/HydjetMBDragos_0.root");
   TFile File("CombinedResult/MBCymbal.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   string Model = "[0]*max(tanh([1]*(x-[2])),0)*(exp(-[3]*x)+[4]*exp(-[5]*x)+[6]*exp(-[7]*x)+[8]*exp(-[9]*x))";
   TF1 F("F", Model.c_str(), 0, 20);
   F.SetParameter(0, 1e6);
   F.SetParameter(1, 50);             F.FixParameter(1, 50);
   F.SetParameter(2, 0.135);          // F.FixParameter(2, 0.158);
   F.SetParameter(3, 2.239);
   F.SetParameter(4, -1.027);
   F.SetParameter(5, 2.449);
   F.SetParameter(6, 0.001346);
   F.SetParameter(7, 0.559);
   F.SetParameter(8, 0.0004049);
   F.SetParameter(9, 0.5874);

   TH1D HPT("HPT", ";PT;", 500, 0, 20);
   Tree->Draw("PT>>HPT",
      Form("abs(Eta) < %f && abs(Eta) >= %f && Rho < %f && Rho >= %f", AbsEtaMax, AbsEtaMin, RhoMax, RhoMin));

   F.SetParLimits(2, 0.00, 0.25);
   F.SetParLimits(6, 0.001, 0.002);
   F.SetParLimits(7, 0.4, 0.7);
   F.SetParLimits(8, 0.0001, 0.0008);
   F.SetParLimits(9, 0.1, 10.0);
   HPT.Fit(&F);
   HPT.Fit(&F);
   HPT.Fit(&F);
   
   F.SetParLimits(2, 0.00, 0.25);
   F.SetParLimits(6, 0.0, 0.10);
   F.SetParLimits(7, 0.0, 10.0);
   HPT.Fit(&F);
   HPT.Fit(&F);
   
   F.SetParLimits(2, 0.00, 0.25);
   F.SetParLimits(8, 0.0000001, 0.001);
   F.SetParLimits(9, 0.0, 10.6);
   HPT.Fit(&F);
   HPT.Fit(&F);
   
   TCanvas Canvas;
   Canvas.SetLogy();

   HPT.Draw();

   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%.1f_%.1f_%.0f_%.0f.png", AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%.1f_%.1f_%.0f_%.0f.C"  , AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%.1f_%.1f_%.0f_%.0f.eps", AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%.1f_%.1f_%.0f_%.0f.pdf", AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));

   cerr << "FITRESULT";
   for(int i = 0; i < 10; i++)
      cerr << " " << F.GetParameter(i);
   cerr << endl;

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

   File.Close();

   // DHFile.SaveToFile("SimpleFitParameters.dh");
   DHFile.SaveToFile("SimpleFitParametersMBCymbal.dh");

   return 0;
}




