#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLatex.h"

int main(int argc, char *argv[])
{
   if(argc == 1)
   {
      cerr << "Usage: " << argv[0] << " OutputBase" << endl;
      return -1;
   }

   string OutputBase = argv[1];

   vector<string> Label;
   vector<double> PerEventMean;
   vector<double> PerEventRMS;
   vector<double> PerVisitMean;
   vector<double> PerVisitRMS;

   vector<string> Black;
   string BlackList = "ModulesToExclude";
   ifstream in(BlackList.c_str());
   while(in)
   {
      string label = "";
      in >> label;
      if(label == "")
         continue;
      Black.push_back(label);
   }
   in.close();

   while(cin)
   {
      string label = "";
      double mean1 = 0, rms1 = 0;
      double mean2 = 0, rms2 = 0;
      
      cin >> label >> mean1 >> rms1 >> mean2 >> rms2;

      if(label == "")
         continue;

      if(find(Black.begin(), Black.end(), label) != Black.end())
         continue;

      Label.push_back(label);
      PerEventMean.push_back(mean1);
      PerEventRMS.push_back(rms1);
      PerVisitMean.push_back(mean2);
      PerVisitRMS.push_back(rms2);
   }

   cout << "Module count: " << Label.size() << endl;

   TH1D H("H", ";;Time (s)", Label.size(), 0, Label.size());
   for(int i = 1; i <= (int)Label.size(); i++)
      H.GetXaxis()->SetBinLabel(i, Label[i-1].c_str());

   for(int i = 1; i <= (int)Label.size(); i++)
   {
      H.SetBinContent(i, PerVisitMean[i-1]);
      H.SetBinError(i, PerVisitRMS[i-1]);
   }

   H.SetStats(0);
   H.SetFillColor(kCyan);

   gStyle->SetPadBottomMargin(0.35);

   TCanvas C;
   C.SetCanvasSize(4096, 800);

   H.Draw("bar");
   H.Draw("error same");

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetTextAlign(32);
   Latex.SetNDC();
   Latex.DrawLatex(0.90, 0.92, Form("Integral = %.2e", H.Integral()));

   C.SetGridx();
   C.SetGridy();

   C.Update();

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C", OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));

   return 0;
}







