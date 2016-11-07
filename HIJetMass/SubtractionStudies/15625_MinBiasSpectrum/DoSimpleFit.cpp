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

   DataHelper DHFile("SimpleFitParameters.dh");

   SetThesisStyle();

   TFile File("Result/HydjetMBDragos_0.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   string Model = "[0]*max(tanh([1]*(x-[2])),0)*(exp(-[3]*x)+[4]*exp(-[5]*x)+[6]*exp(-[7]*x)+[8]*exp(-[9]*x))";
   TF1 F("F", Model.c_str(), 0, 20);
   F.SetParameter(0, 1e6);
   F.SetParameter(1, 50);             F.FixParameter(1, 50);
   F.SetParameter(2, 0.258);          F.FixParameter(2, 0.258);
   F.SetParameter(3, 1.5);
   F.SetParameter(4, -1);
   F.SetParameter(5, 4.5);
   F.SetParameter(6, 0.003);
   F.SetParameter(7, 0.5);
   F.SetParameter(8, 0.0003);
   F.SetParameter(9, 0.3);

   TH1D HPT("HPT", ";PT;", 500, 0, 20);
   Tree->Draw("PT>>HPT",
      Form("abs(Eta) < %f && abs(Eta) >= %f && Rho < %f && Rho >= %f", AbsEtaMax, AbsEtaMin, RhoMax, RhoMin));

   F.SetParLimits(6, 0.003, 0.003);
   F.SetParLimits(7, 0.5, 0.5);
   F.SetParLimits(8, 0.0003, 0.0003);
   F.SetParLimits(9, 0.3, 0.3);
   F.SetParLimits(10, 0.00003, 0.00003);
   F.SetParLimits(11, 0.1, 0.1);
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

   DHFile.SaveToFile("SimpleFitParameters.dh");

   return 0;
}




