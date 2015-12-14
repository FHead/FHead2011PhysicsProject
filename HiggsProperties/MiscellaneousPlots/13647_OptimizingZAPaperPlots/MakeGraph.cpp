#include <iostream>
#include <cmath>
using namespace std;

#include "TGraphErrors.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   string FileName = "Graph.root";
   string Type = "Both";
   string Cut = "A";
   double Efficiency = 1;

   if(argc < 5)
   {
      cerr << "Usage: " << argv[0] << " FileName Type Cut Efficiency" << endl;
      cerr << "   Example: " << argv[0] << " Graph.root Both A 1" << endl;
      return -1;
   }

   FileName = argv[1];
   Type = argv[2];
   Cut = argv[3];
   Efficiency = atof(argv[4]);

   int Count = 10;
   int N[] = {50, 100, 200, 400, 600, 1000, 2000, 4000, 7000, 10000};

   TFile File(FileName.c_str(), "RECREATE");

   TGraphErrors GA2ZZ1, GA2ZZ2, GA2ZZ3, GA2ZZ4;
   TGraphErrors GA3ZZ1, GA3ZZ2, GA3ZZ3, GA3ZZ4;
   TGraphErrors GA4ZZ1, GA4ZZ2, GA4ZZ3, GA4ZZ4;
   TGraphErrors GA2ZA1, GA2ZA2, GA2ZA3, GA2ZA4;
   TGraphErrors GA3ZA1, GA3ZA2, GA3ZA3, GA3ZA4;
   TGraphErrors GA2AA1, GA2AA2, GA2AA3, GA2AA4;
   TGraphErrors GA3AA1, GA3AA2, GA3AA3, GA3AA4;
   GA2ZZ1.SetNameTitle(Form("A2ZZ_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GA2ZZ2.SetNameTitle(Form("A2ZZ_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GA2ZZ3.SetNameTitle(Form("A2ZZ_%s_%s_Count_FloatA2A3", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA2ZZ4.SetNameTitle(Form("A2ZZ_%s_%s_Lumi_FloatA2A3", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA3ZZ1.SetNameTitle(Form("A3ZZ_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GA3ZZ2.SetNameTitle(Form("A3ZZ_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GA3ZZ3.SetNameTitle(Form("A3ZZ_%s_%s_Count_FloatA2A3", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA3ZZ4.SetNameTitle(Form("A3ZZ_%s_%s_Lumi_FloatA2A3", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA4ZZ1.SetNameTitle(Form("A4ZZ_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GA4ZZ2.SetNameTitle(Form("A4ZZ_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GA4ZZ3.SetNameTitle(Form("A4ZZ_%s_%s_Count_FloatA2A3", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA4ZZ4.SetNameTitle(Form("A4ZZ_%s_%s_Lumi_FloatA2A3", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA2ZA1.SetNameTitle(Form("A2ZA_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GA2ZA2.SetNameTitle(Form("A2ZA_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GA2ZA3.SetNameTitle(Form("A2ZA_%s_%s_Count_FloatA2A3", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA2ZA4.SetNameTitle(Form("A2ZA_%s_%s_Lumi_FloatA2A3", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA3ZA1.SetNameTitle(Form("A3ZA_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GA3ZA2.SetNameTitle(Form("A3ZA_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GA3ZA3.SetNameTitle(Form("A3ZA_%s_%s_Count_FloatA2A3", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA3ZA4.SetNameTitle(Form("A3ZA_%s_%s_Lumi_FloatA2A3", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA2AA1.SetNameTitle(Form("A2AA_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GA2AA2.SetNameTitle(Form("A2AA_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GA2AA3.SetNameTitle(Form("A2AA_%s_%s_Count_FloatA2A3", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA2AA4.SetNameTitle(Form("A2AA_%s_%s_Lumi_FloatA2A3", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA3AA1.SetNameTitle(Form("A3AA_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GA3AA2.SetNameTitle(Form("A3AA_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GA3AA3.SetNameTitle(Form("A3AA_%s_%s_Count_FloatA2A3", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Float only A2A3", Type.c_str(), Cut.c_str()));
   GA3AA4.SetNameTitle(Form("A3AA_%s_%s_Lumi_FloatA2A3", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Float only A2A3", Type.c_str(), Cut.c_str()));

   for(int i = 0; i < Count; i++)
   {
      TFile IndividualFile(Form("Trees/Result%s_A1ZZ_%s_%d.root", Type.c_str(), Cut.c_str(), N[i]));

      TTree *Tree = (TTree *)IndividualFile.Get("ResultTree");

      TH1D H("H", "", 100, -100, 100);

      Tree->Draw("abs(A2ZZA1ZZ)*2>>H", "A2ZZA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError > 0");
      GA2ZZ1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA2ZZ1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA2ZZ2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA2ZZ2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(A2ZZA1ZZ)*2>>H", "A2ZZA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
      GA2ZZ3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA2ZZ3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA2ZZ4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA2ZZ4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(A3ZZA1ZZ)*2>>H", "A3ZZA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError > 0");
      GA3ZZ1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA3ZZ1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA3ZZ2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA3ZZ2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(A3ZZA1ZZ)*2>>H", "A3ZZA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
      GA3ZZ3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA3ZZ3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA3ZZ4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA3ZZ4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(A4ZZA1ZZ)*2>>H", "A4ZZA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError > 0");
      GA4ZZ1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA4ZZ1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA4ZZ2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA4ZZ2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(A4ZZA1ZZ)*2>>H", "A4ZZA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
      GA4ZZ3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA4ZZ3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA4ZZ4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA4ZZ4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(A2ZAA1ZZ)*2>>H", "A2ZAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError > 0");
      GA2ZA1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA2ZA1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA2ZA2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA2ZA2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(A2ZAA1ZZ)*2>>H", "A2ZAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
      GA2ZA3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA2ZA3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA2ZA4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA2ZA4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(A3ZAA1ZZ)*2>>H", "A3ZAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError > 0");
      GA3ZA1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA3ZA1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA3ZA2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA3ZA2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(A3ZAA1ZZ)*2>>H", "A3ZAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
      GA3ZA3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA3ZA3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA3ZA4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA3ZA4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(A2AAA1ZZ)*2>>H", "A2AAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError > 0");
      GA2AA1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA2AA1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA2AA2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA2AA2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(A2AAA1ZZ)*2>>H", "A2AAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
      GA2AA3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA2AA3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA2AA4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA2AA4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(A3AAA1ZZ)*2>>H", "A3AAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError > 0");
      GA3AA1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA3AA1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA3AA2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA3AA2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(A3AAA1ZZ)*2>>H", "A3AAA1ZZError > 0 && Status == 3 && A2AAA1ZZError < 0.2 && A4ZZA1ZZError == 0");
      GA3AA3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA3AA3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA3AA4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA3AA4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      IndividualFile.Close();
   }

   File.cd();

   GA2ZZ1.Write();
   GA2ZZ2.Write();
   GA2ZZ3.Write();
   GA2ZZ4.Write();
   GA3ZZ1.Write();
   GA3ZZ2.Write();
   GA3ZZ3.Write();
   GA3ZZ4.Write();
   GA4ZZ1.Write();
   GA4ZZ2.Write();
   GA4ZZ3.Write();
   GA4ZZ4.Write();
   GA2ZA1.Write();
   GA2ZA2.Write();
   GA2ZA3.Write();
   GA2ZA4.Write();
   GA3ZA1.Write();
   GA3ZA2.Write();
   GA3ZA3.Write();
   GA3ZA4.Write();
   GA2AA1.Write();
   GA2AA2.Write();
   GA2AA3.Write();
   GA2AA4.Write();
   GA3AA1.Write();
   GA3AA2.Write();
   GA3AA3.Write();
   GA3AA4.Write();

   File.Close();

   return 0;
}




