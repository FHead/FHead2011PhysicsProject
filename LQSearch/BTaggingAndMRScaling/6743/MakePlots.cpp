#include <string>
#include <vector>
using namespace std;

#include "TROOT.h"
#include "TStyle.h"
#include "TGraphErrors.h"

#include "DataHelper.h"
#include "PlotHelper2.h"

int main()
{
   gROOT->SetStyle("Plain");

   DataHelper DHFile("CollectResult.dh");

   PsFileHelper PsFile("ParameterDependenceOnBTag.ps");
   PsFile.AddTextPage("Parameter dependence on b-tagging");

   TGraphErrors GB, GMROffset, GR2Offset;

   GB.SetNameTitle("ParameterB", "Parameter B");
   GMROffset.SetNameTitle("ParameterMROffset", "Parameter MROffset");
   GR2Offset.SetNameTitle("ParameterR2Offset", "Parameter R2Offset");

   const vector<string> States = DHFile.GetListOfKeys();
   for(int i = 0; i < (int)States.size(); i++)
   {
      double Jet1TCHELimit = DHFile[States[i]]["Jet1TCHELimit"].GetDouble();
      double B = DHFile[States[i]]["B"].GetDouble();
      double BError = DHFile[States[i]]["BError"].GetDouble();
      double MROffset = DHFile[States[i]]["MROffset"].GetDouble();
      double MROffsetError = DHFile[States[i]]["MROffsetError"].GetDouble();
      double R2Offset = DHFile[States[i]]["R2Offset"].GetDouble();
      double R2OffsetError = DHFile[States[i]]["R2OffsetError"].GetDouble();

      if(Jet1TCHELimit < -500)
         Jet1TCHELimit = -1;
      
      GB.SetPoint(i, Jet1TCHELimit, B);
      GB.SetPointError(i, 0, BError);
      GMROffset.SetPoint(i, Jet1TCHELimit, MROffset);
      GMROffset.SetPointError(i, 0, MROffsetError);
      GR2Offset.SetPoint(i, Jet1TCHELimit, R2Offset);
      GR2Offset.SetPointError(i, 0, R2OffsetError);
   }

   TCanvas CB;
   GB.Draw("ape");
   GB.GetHistogram()->GetXaxis()->SetTitle("Cut position (TCHE) on leading jet");
   PsFile.AddCanvas(CB);

   TCanvas CMROffset;
   GMROffset.Draw("ape");
   GMROffset.GetHistogram()->GetXaxis()->SetTitle("Cut position (TCHE) on leading jet");
   PsFile.AddCanvas(CMROffset);

   TCanvas CR2Offset;
   GR2Offset.Draw("ape");
   GR2Offset.GetHistogram()->GetXaxis()->SetTitle("Cut position (TCHE) on leading jet");
   PsFile.AddCanvas(CR2Offset);

   PsFile.AddTimeStampPage();
   PsFile.Close();
}




