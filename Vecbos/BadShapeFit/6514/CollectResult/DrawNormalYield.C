#include <string>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

#include "RooRealVar.h"
#include "RooFitResult.h"
using namespace RooFit;

#include "PlotHelper.h"
#include "DataHelper.h"

void DrawNormalYield(string InputFile = "XD.root", int Start = 0, int End = 999, string OutputBase = "Meow")
{
   TFile F(InputFile.c_str());

   PsFileHelper PsFile(OutputBase + ".ps");

   TH1D PullDistribution("PullDistribution", "Pull distrtbution", 100, -5, 5);
   TH1D YieldDistribution("YieldDistribution", "Yield distrtbution", 100, 2600, 3400);
   TH1D ErrorDistribution("ErrorDistribution", "Error distrtbution", 100, 0, 100);

   for(int i = Start; i <= End; i++)
   {
      RooFitResult *result = (RooFitResult *)F.Get(Form("Result%d", i));

      if(result == NULL)
         continue;
      if(result->covQual() != 3)
         continue;

      double Yield = ((RooRealVar *)(result->floatParsFinal().find("SignalYield")))->getVal();
      double Error = ((RooRealVar *)(result->floatParsFinal().find("SignalYield")))->getError();

      YieldDistribution.Fill(Yield);
      ErrorDistribution.Fill(Error);
      PullDistribution.Fill((Yield - 3000) / Error);
   }

   YieldDistribution.Fit("gaus");
   PullDistribution.Fit("gaus");

   PsFile.AddPlot(YieldDistribution);
   PsFile.AddPlot(ErrorDistribution);
   PsFile.AddPlot(PullDistribution);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   TCanvas C("C", "C", 1024, 768);
   YieldDistribution.Draw();
   C.SaveAs((OutputBase + "_Yield.png").c_str());
   C.SaveAs((OutputBase + "_Yield.C").c_str());
   C.SaveAs((OutputBase + "_Yield.eps").c_str());

   TF1 *PullFunction = PullDistribution.GetFunction("gaus");
   TF1 *YieldFunction = YieldDistribution.GetFunction("gaus");

   DataHelper DHFile("Database.dh");

   DHFile[OutputBase]["Constant"] = PullFunction->GetParameter(0);
   DHFile[OutputBase]["ConstantError"] = PullFunction->GetParError(0);
   DHFile[OutputBase]["Mean"] = PullFunction->GetParameter(1);
   DHFile[OutputBase]["MeanError"] = PullFunction->GetParError(1);
   DHFile[OutputBase]["Sigma"] = PullFunction->GetParameter(2);
   DHFile[OutputBase]["SigmaError"] = PullFunction->GetParError(2);
   DHFile[OutputBase]["YieldMean"] = YieldFunction->GetParameter(1);
   DHFile[OutputBase]["YieldMeanError"] = YieldFunction->GetParError(1);
   DHFile[OutputBase]["YieldSigma"] = YieldFunction->GetParameter(2);
   DHFile[OutputBase]["YieldSigmaError"] = YieldFunction->GetParError(2);

   DHFile.SaveToFile("Database.dh");

   F.Close();
}



