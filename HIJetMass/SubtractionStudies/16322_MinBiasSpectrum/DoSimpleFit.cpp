#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"

#include "SetStyle.h"
#include "DataHelper.h"

#define TYPE_NEUTRAL 0
#define TYPE_CHARGED 1
#define TYPE_ALL -1

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   double AbsEtaMin = 0;
   double AbsEtaMax = 0.5;
   double RhoMin = 0;
   double RhoMax = 50;
   int Type = TYPE_NEUTRAL;

   if(argc != 6)
   {
      cerr << "Usage: " << argv[0] << " Type AbsEtaMin AbsEtaMax RhoMin RhoMax" << endl;
      return -1;
   }

   Type = atoi(argv[1]);
   AbsEtaMin = atof(argv[2]);
   AbsEtaMax = atof(argv[3]);
   RhoMin = atof(argv[4]);
   RhoMax = atof(argv[5]);

   string TypeString;
   if(Type == TYPE_ALL)
      TypeString = "(ID > 0)";
   else if(Type == TYPE_CHARGED)
      TypeString = "(ID == 1 || ID == 2 || ID == 3)";
   else if(Type == TYPE_NEUTRAL)
      TypeString = "(ID == 4 || ID == 5 || ID == 6 || ID == 7)";

   // DataHelper DHFile("SimpleFitParameters.dh");
   DataHelper DHFile("SimpleFitParametersMBCymbal.dh");
   // DataHelper DHFile("SimpleFitParametersAADataMBDragos.dh");

   SetThesisStyle();

   // TFile File("Result/HydjetMBDragos_0.root");
   TFile File("CombinedResult/MBCymbal.root");
   // TFile File("CombinedResult/AADataMBDragos.root");

   TTree *Tree = (TTree *)File.Get("Tree");

   TH1D HPT("HPT", ";PT;", 500, 0, 20);
   Tree->Draw("PT>>HPT",
      Form("abs(Eta) < %f && abs(Eta) >= %f && Rho < %f && Rho >= %f && %s", AbsEtaMax, AbsEtaMin, RhoMax, RhoMin, TypeString.c_str()));
   cout << "Number of entries = " << HPT.GetEntries() << endl;
   
   TF1 FTail("FTail", "expo(0)+expo(2)", 2.0, 20);
   HPT.Fit(&FTail, "", "", 2.0, 20);
   HPT.Fit(&FTail, "", "", 2.0, 20);
   HPT.Fit(&FTail, "", "", 2.0, 20);
   
   TF1 FTail2("FTail2", "expo(0)+expo(2)+expo(4)", 2.0, 20);
   FTail2.SetParameters(FTail.GetParameter(0), FTail.GetParameter(1), FTail.GetParameter(2), FTail.GetParameter(3),
      0.0, -0.001);
   HPT.Fit(&FTail2, "L", "", 2.0, 20);
   HPT.Fit(&FTail2, "L", "", 2.0, 20);
   HPT.Fit(&FTail2, "L", "", 2.0, 20);

   // string Model = "([0]*TMath::Max(tanh([1]*(x-[2])),0.00)+TMath::Max(tanh([1]*(x-[3]))))*([4]*exp(-[5]*x)+[6]*exp(-[7]*x)+[8]*exp(-[9]*x))";
   string Model = "[0]*TMath::Max(tanh([1]*(x-[2])),0.00)*(exp(-[3]*x)+[4]*exp(-[5]*x)+[6]*exp(-[7]*x)+[8]*exp(-[9]*x))";
   TF1 F("F", Model.c_str(), 0, 20);
   F.SetParameter(0, 1);
   F.SetParameter(1, 10);
   F.SetParameter(2, 0.25);
   F.FixParameter(3, 999999);
   F.FixParameter(4, exp(FTail2.GetParameter(0)));
   F.FixParameter(5, -FTail2.GetParameter(1));
   F.FixParameter(6, exp(FTail2.GetParameter(2)));
   F.FixParameter(7, -FTail2.GetParameter(3));
   F.FixParameter(8, exp(FTail2.GetParameter(4)));
   F.FixParameter(9, -FTail2.GetParameter(5));
   HPT.Fit(&F);
   HPT.Fit(&F);
   HPT.Fit(&F);
   HPT.Fit(&F);

   // F.SetParLimits(2, 0.00, 0.25);
   // F.SetParLimits(6, 0.001, 0.002);
   // F.SetParLimits(7, 0.4, 0.7);
   // F.SetParLimits(8, 0.0001, 0.0008);
   // F.SetParLimits(9, 0.1, 10.0);
   // HPT.Fit(&F);
   // HPT.Fit(&F);
   // HPT.Fit(&F);
  
   /*
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
   HPT.Fit(&F);
   HPT.Fit(&F);
   */

   TCanvas Canvas;
   Canvas.SetLogy();

   HPT.Draw();

   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%d_%.1f_%.1f_%.0f_%.0f.png", Type, AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%d_%.1f_%.1f_%.0f_%.0f.C"  , Type, AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%d_%.1f_%.1f_%.0f_%.0f.eps", Type, AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResult_%d_%.1f_%.1f_%.0f_%.0f.pdf", Type, AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));

   HPT.GetXaxis()->SetRangeUser(0.0, 2.0);
   HPT.SetStats(0);
   HPT.Draw();
   
   Canvas.SaveAs(Form("FitPlots/SimpleFitResultZoomed_%d_%.1f_%.1f_%.0f_%.0f.png", Type, AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResultZoomed_%d_%.1f_%.1f_%.0f_%.0f.C"  , Type, AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResultZoomed_%d_%.1f_%.1f_%.0f_%.0f.eps", Type, AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));
   Canvas.SaveAs(Form("FitPlots/SimpleFitResultZoomed_%d_%.1f_%.1f_%.0f_%.0f.pdf", Type, AbsEtaMin, AbsEtaMax, RhoMin, RhoMax));
   
   cerr << "FITRESULT";
   for(int i = 0; i < 10; i++)
      cerr << " " << F.GetParameter(i);
   cerr << endl;

   string State = Form("SimpleFit_%.2f_%.2f_%.0f_%.0f", AbsEtaMin, AbsEtaMax, RhoMin, RhoMax);

   string TypeSuffix = "";
   if(Type == TYPE_NEUTRAL)
      TypeSuffix = "N";
   if(Type == TYPE_CHARGED)
      TypeSuffix = "C";

   DHFile[State]["Model"+TypeSuffix] = Model;
   DHFile[State]["FitMin"+TypeSuffix] = 0;
   DHFile[State]["FitMax"+TypeSuffix] = 20;

   for(int i = 0; i < 10; i++)
   {
      string Key = Form("P%d", i);
      DHFile[State][Key+TypeSuffix] = F.GetParameter(i);

      Key = Form("ErrorP%d", i);
      DHFile[State][Key+TypeSuffix] = F.GetParError(i);
   }

   File.Close();

   // DHFile.SaveToFile("SimpleFitParameters.dh");
   DHFile.SaveToFile("SimpleFitParametersMBCymbal.dh");
   // DHFile.SaveToFile("SimpleFitParametersAADataMBDragos.dh");

   return 0;
}




