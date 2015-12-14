#include <iostream>
#include <cmath>
using namespace std;

#include "TGraphErrors.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[]);
void SetAlias(TTree *Tree);

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
   TGraphErrors GYT1, GYT2, GYT3, GYT4;
   TGraphErrors GYTPhase1, GYTPhase2, GYTPhase3, GYTPhase4;
   TGraphErrors GMT1, GMT2, GMT3, GMT4;
   TGraphErrors GGWW1, GGWW2, GGWW3, GGWW4;
   TGraphErrors GMW1, GMW2, GMW3, GMW4;
   GA2ZZ1.SetNameTitle(Form("A2ZZ_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GA2ZZ2.SetNameTitle(Form("A2ZZ_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GA2ZZ3.SetNameTitle(Form("A2ZZ_%s_%s_Count_FloatSingle", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Single float", Type.c_str(), Cut.c_str()));
   GA2ZZ4.SetNameTitle(Form("A2ZZ_%s_%s_Lumi_FloatSingle", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Single float", Type.c_str(), Cut.c_str()));
   GA3ZZ1.SetNameTitle(Form("A3ZZ_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GA3ZZ2.SetNameTitle(Form("A3ZZ_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GA3ZZ3.SetNameTitle(Form("A3ZZ_%s_%s_Count_FloatSingle", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Single float", Type.c_str(), Cut.c_str()));
   GA3ZZ4.SetNameTitle(Form("A3ZZ_%s_%s_Lumi_FloatSingle", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Single float", Type.c_str(), Cut.c_str()));
   GA4ZZ1.SetNameTitle(Form("A4ZZ_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GA4ZZ2.SetNameTitle(Form("A4ZZ_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GA4ZZ3.SetNameTitle(Form("A4ZZ_%s_%s_Count_FloatSingle", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Single float", Type.c_str(), Cut.c_str()));
   GA4ZZ4.SetNameTitle(Form("A4ZZ_%s_%s_Lumi_FloatSingle", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Single float", Type.c_str(), Cut.c_str()));
   GYT1.SetNameTitle(Form("YT_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GYT2.SetNameTitle(Form("YT_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GYT3.SetNameTitle(Form("YT_%s_%s_Count_FloatSingle", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Single float", Type.c_str(), Cut.c_str()));
   GYT4.SetNameTitle(Form("YT_%s_%s_Lumi_FloatSingle", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Single float", Type.c_str(), Cut.c_str()));
   GYTPhase1.SetNameTitle(Form("YTPhase_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GYTPhase2.SetNameTitle(Form("YTPhase_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GYTPhase3.SetNameTitle(Form("YTPhase_%s_%s_Count_FloatSingle", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Single float", Type.c_str(), Cut.c_str()));
   GYTPhase4.SetNameTitle(Form("YTPhase_%s_%s_Lumi_FloatSingle", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Single float", Type.c_str(), Cut.c_str()));
   GMT1.SetNameTitle(Form("MT_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GMT2.SetNameTitle(Form("MT_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GMT3.SetNameTitle(Form("MT_%s_%s_Count_FloatSingle", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Single float", Type.c_str(), Cut.c_str()));
   GMT4.SetNameTitle(Form("MT_%s_%s_Lumi_FloatSingle", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Single float", Type.c_str(), Cut.c_str()));
   GGWW1.SetNameTitle(Form("GWW_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GGWW2.SetNameTitle(Form("GWW_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GGWW3.SetNameTitle(Form("GWW_%s_%s_Count_FloatSingle", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Single float", Type.c_str(), Cut.c_str()));
   GGWW4.SetNameTitle(Form("GWW_%s_%s_Lumi_FloatSingle", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Single float", Type.c_str(), Cut.c_str()));
   GMW1.SetNameTitle(Form("MW_%s_%s_Count_FloatAll", Type.c_str(), Cut.c_str()),  Form("%s, %s, N, Float all", Type.c_str(), Cut.c_str()));
   GMW2.SetNameTitle(Form("MW_%s_%s_Lumi_FloatAll", Type.c_str(), Cut.c_str()),   Form("%s, %s, N/#epsilon, Float all", Type.c_str(), Cut.c_str()));
   GMW3.SetNameTitle(Form("MW_%s_%s_Count_FloatSingle", Type.c_str(), Cut.c_str()), Form("%s, %s, N, Single float", Type.c_str(), Cut.c_str()));
   GMW4.SetNameTitle(Form("MW_%s_%s_Lumi_FloatSingle", Type.c_str(), Cut.c_str()),  Form("%s, %s, N/#epsilon, Single float", Type.c_str(), Cut.c_str()));

   for(int i = 0; i < Count; i++)
   {
      TFile IndividualFile(Form("Trees/Result%s_SM_%s_%d.root", Type.c_str(), Cut.c_str(), N[i]));

      TTree *Tree = (TTree *)IndividualFile.Get("ResultTree");

      SetAlias(Tree);

      TH1D H("H", "", 100, -100, 100);

      Tree->Draw("abs(A2ZZA1ZZ-0.005)*2>>H", "Status == 3 && YYYYYYYN");
      GA2ZZ1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA2ZZ1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA2ZZ2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA2ZZ2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(A2ZZA1ZZ-0.005)*2>>H", "Status == 3 && YNNNNNNN");
      GA2ZZ3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA2ZZ3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA2ZZ4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA2ZZ4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(A3ZZA1ZZ)*2>>H", "Status == 3 && YYYYYYYN");
      GA3ZZ1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA3ZZ1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA3ZZ2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA3ZZ2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(A3ZZA1ZZ)*2>>H", "Status == 3 && NYNNNNNN");
      GA3ZZ3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA3ZZ3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA3ZZ4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA3ZZ4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(A4ZZA1ZZ-0.0045)*2>>H", "Status == 3 && YYYYYYYN");
      GA4ZZ1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA4ZZ1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA4ZZ2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA4ZZ2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(A4ZZA1ZZ-0.0045)*2>>H", "Status == 3 && NNYNNNNN");
      GA4ZZ3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GA4ZZ3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GA4ZZ4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GA4ZZ4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(YT-0.9)>>H", "Status == 3 && YYYYYYYN");
      GYT1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GYT1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GYT2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GYT2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(YT-0.9)>>H", "Status == 3 && NNNYNNNN");
      GYT3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GYT3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GYT4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GYT4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(YTPhase)>>H", "Status == 3 && YYYYYYYN");
      GYTPhase1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GYTPhase1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GYTPhase2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GYTPhase2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(YTPhase)>>H", "Status == 3 && NNNNYNNN");
      GYTPhase3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GYTPhase3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GYTPhase4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GYTPhase4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(MT-172)>>H", "Status == 3 && YYYYYYYN");
      GMT1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GMT1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GMT2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GMT2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(MT-172)>>H", "Status == 3 && NNNNNYNN");
      GMT3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GMT3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GMT4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GMT4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(GWW-2)>>H", "Status == 3 && YYYYYYYN");
      GGWW1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GGWW1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GGWW2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GGWW2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(GWW-2)>>H", "Status == 3 && NNNNNNYN");
      GGWW3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GGWW3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GGWW4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GGWW4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

      Tree->Draw("abs(MW-80)>>H", "Status == 3 && YYYYYYYN");
      GMW1.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GMW1.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GMW2.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GMW2.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      Tree->Draw("abs(MW-80)>>H", "Status == 3 && NNNNNNNY");
      GMW3.SetPoint(i, N[i] * 2, H.GetMean() * sqrt(PI / 2));
      GMW3.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      GMW4.SetPoint(i, N[i] * 2 / Efficiency, H.GetMean() * sqrt(PI / 2));
      GMW4.SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

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
   GYT1.Write();
   GYT2.Write();
   GYT3.Write();
   GYT4.Write();
   GYTPhase1.Write();
   GYTPhase2.Write();
   GYTPhase3.Write();
   GYTPhase4.Write();
   GMT1.Write();
   GMT2.Write();
   GMT3.Write();
   GMT4.Write();
   GGWW1.Write();
   GGWW2.Write();
   GGWW3.Write();
   GGWW4.Write();
   GMW1.Write();
   GMW2.Write();
   GMW3.Write();
   GMW4.Write();

   File.Close();

   return 0;
}

void SetAlias(TTree *Tree)
{
   if(Tree == NULL)
      return;

   for(int i1 = 0; i1 < 2; i1++)
   {
      for(int i2 = 0; i2 < 2; i2++)
      {
         for(int i3 = 0; i3 < 2; i3++)
         {
            for(int i4 = 0; i4 < 2; i4++)
            {
               for(int i5 = 0; i5 < 2; i5++)
               {
                  for(int i6 = 0; i6 < 2; i6++)
                  {
                     for(int i7 = 0; i7 < 2; i7++)
                     {
                        for(int i8 = 0; i8 < 2; i8++)
                        {
                           string S1 = "NNNNNNNN";
                           if(i1 == 1)   S1[0] = 'Y';
                           if(i2 == 1)   S1[1] = 'Y';
                           if(i3 == 1)   S1[2] = 'Y';
                           if(i4 == 1)   S1[3] = 'Y';
                           if(i5 == 1)   S1[4] = 'Y';
                           if(i6 == 1)   S1[5] = 'Y';
                           if(i7 == 1)   S1[6] = 'Y';
                           if(i8 == 1)   S1[7] = 'Y';

                           string S2 = "(";
                           if(i1 == 1)   S2 = S2 + "A2ZZA1ZZError > 0";
                           else          S2 = S2 + "A2ZZA1ZZError == 0";
                           if(i2 == 1)   S2 = S2 + " && A3ZZA1ZZError > 0";
                           else          S2 = S2 + " && A3ZZA1ZZError == 0";
                           if(i3 == 1)   S2 = S2 + " && A4ZZA1ZZError > 0";
                           else          S2 = S2 + " && A4ZZA1ZZError == 0";
                           if(i4 == 1)   S2 = S2 + " && YTError > 0";
                           else          S2 = S2 + " && YTError == 0";
                           if(i5 == 1)   S2 = S2 + " && YTPhaseError > 0";
                           else          S2 = S2 + " && YTPhaseError == 0";
                           if(i6 == 1)   S2 = S2 + " && MTError > 0";
                           else          S2 = S2 + " && MTError == 0";
                           if(i7 == 1)   S2 = S2 + " && GWWError > 0";
                           else          S2 = S2 + " && GWWError == 0";
                           if(i8 == 1)   S2 = S2 + " && MWError > 0";
                           else          S2 = S2 + " && MWError == 0";
                           S2 = S2 + ")";

                           Tree->SetAlias(S1.c_str(), S2.c_str());
                        }
                     }
                  }
               }
            }
         }
      }
   }
}

