#include <iostream>
#include <cmath>
using namespace std;

#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "ProgressBar.h"

#define PI 3.14159265358979323846264338327950288479716939937510

int main(int argc, char *argv[])
{
   TCanvas C;

   string FileName = "Graph.root";
   string Type = "Both";
   string Cut = "A";
   double Efficiency = 1;
   string Point = "A";
   double TrueYT = 1;
   double TrueYTA = 0;
   double TrueGWW = 2;
   double TrueA2 = 0.01;
   double TrueA3 = 0;
   double TrueA4 = 0.007;

   if(argc < 12)
   {
      cerr << "Usage: " << argv[0] << " FileName Type Cut Efficiency  Point TrueYT TrueYTA TrueGWW TrueA2 TrueA3 TrueA4" << endl;
      cerr << "   Example: " << argv[0] << " Graph.root Both A 1  A 1 0 2 0.01 0 0.007" << endl;
      return -1;
   }

   FileName = argv[1];
   Type = argv[2];
   Cut = argv[3];
   Efficiency = atof(argv[4]);
   Point = argv[5];
   TrueYT = atof(argv[6]);
   TrueYTA = atof(argv[7]);
   TrueGWW = atof(argv[8]);
   TrueA2 = atof(argv[9]);
   TrueA3 = atof(argv[10]);
   TrueA4 = atof(argv[11]);

   int Count = 10;
   int N[] = {50, 100, 200, 400, 600, 1000, 2000, 4000, 7000, 10000};

   TFile File(FileName.c_str(), "RECREATE");

   vector<TGraphErrors *> GYT, GYTA, GGWW, GA2, GA3, GA4;   // NNN***, *** = YNN, NYN, YYN, NNY, YNY, NYY, YYY
   vector<TGraphErrors *> GYTLumi, GYTALumi, GGWWLumi, GA2Lumi, GA3Lumi, GA4Lumi;

   for(int i = 1; i <= 63; i++)
   {
      string Float = "NNNNNN";
      if(i % 2 == 1)         Float[3] = 'Y';
      if((i / 2) % 2 == 1)   Float[4] = 'Y';
      if((i / 4) % 2 == 1)   Float[5] = 'Y';
      if((i / 8) % 2 == 1)   Float[0] = 'Y';
      if((i / 16) % 2 == 1)  Float[1] = 'Y';
      if((i / 32) % 2 == 1)  Float[2] = 'Y';

      GYT.push_back(new TGraphErrors);
      GYTA.push_back(new TGraphErrors);
      GGWW.push_back(new TGraphErrors);
      GA2.push_back(new TGraphErrors);
      GA3.push_back(new TGraphErrors);
      GA4.push_back(new TGraphErrors);
      GYTLumi.push_back(new TGraphErrors);
      GYTALumi.push_back(new TGraphErrors);
      GGWWLumi.push_back(new TGraphErrors);
      GA2Lumi.push_back(new TGraphErrors);
      GA3Lumi.push_back(new TGraphErrors);
      GA4Lumi.push_back(new TGraphErrors);

      string ID = Type + "_" + Cut + "_Count_" + Float + "_Point" + Point;

      GYT[i-1]->SetNameTitle(Form("YT_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GYTA[i-1]->SetNameTitle(Form("YTA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GGWW[i-1]->SetNameTitle(Form("GWW_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA2[i-1]->SetNameTitle(Form("A2_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA3[i-1]->SetNameTitle(Form("A3_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA4[i-1]->SetNameTitle(Form("A4_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));

      ID = Type + "_" + Cut + "_Lumi_" + Float + "_Point" + Point;

      GYTLumi[i-1]->SetNameTitle(Form("YT_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GYTALumi[i-1]->SetNameTitle(Form("YTA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GGWWLumi[i-1]->SetNameTitle(Form("GWW_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA2Lumi[i-1]->SetNameTitle(Form("A2_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA3Lumi[i-1]->SetNameTitle(Form("A3_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA4Lumi[i-1]->SetNameTitle(Form("A4_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
   }

   ProgressBar Bar(cout, Count * 63);
   Bar.SetStyle(5);

   for(int i = 0; i < Count; i++)
   {
      TFile IndividualFile(Form("Trees/Result%s_Point%s_%s_%d.root", Type.c_str(), Point.c_str(), Cut.c_str(), N[i]));

      TTree *Tree = (TTree *)IndividualFile.Get("ResultTree");

      double Factor = 2;
      if(Type != "BothS" && Type != "Both" && Type != "BothF")
         Factor = 1;

      TH1D H("H", "", 100, -100, 100);

      for(int j = 1; j <= 63; j++)
      {
         Bar.Update(i * 63 + j - 1);
         Bar.Print();

         //                  0         1         2         3         4         5         6         7         8         9         0         1         2
         //                  01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
         string CutString = "Status == 3 && YTError == 0 && YTAError == 0 && GWWError == 0 && A2ZZA1ZZError == 0 && A3ZZA1ZZError == 0 && A4ZZA1ZZError == 0";

         if((j / 1) % 2 == 1)   CutString[23] = '>', CutString[24] = ' ';
         if((j / 2) % 2 == 1)   CutString[40] = '>', CutString[41] = ' ';
         if((j / 4) % 2 == 1)   CutString[57] = '>', CutString[58] = ' ';
         if((j / 8) % 2 == 1)   CutString[79] = '>', CutString[80] = ' ';
         if((j / 16) % 2 == 1)  CutString[101] = '>', CutString[102] = ' ';
         if((j / 32) % 2 == 1)  CutString[123] = '>', CutString[124] = ' ';

         string Float = "NNNNNN";
         if(j % 2 == 1)         Float[3] = 'Y';
         if((j / 2) % 2 == 1)   Float[4] = 'Y';
         if((j / 4) % 2 == 1)   Float[5] = 'Y';
         if((j / 8) % 2 == 1)   Float[0] = 'Y';
         if((j / 16) % 2 == 1)  Float[1] = 'Y';
         if((j / 32) % 2 == 1)  Float[2] = 'Y';

         string ZZSector = Float.substr(0, 3);
         string FFSector = Float.substr(3, 3);

         if(ZZSector != "YNN" && ZZSector != "NYN" && ZZSector != "NNY" && ZZSector != "YYY" && ZZSector != "NNN")
            continue;
         if((ZZSector == "YNN" || ZZSector == "NYN" || ZZSector == "NNY") && (FFSector != "NNN" && FFSector != "YYY"))
            continue;

         // cout << Float << endl;

         Tree->Draw(Form("abs(YT-%f)>>H", TrueYT), CutString.c_str());
         if(H.Integral() == 0)
            continue;
         
         Tree->Draw(Form("abs(YT-%f)>>H", TrueYT), CutString.c_str());
         GYT[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GYT[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GYTLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GYTLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(YTA-%f)>>H", TrueYTA), CutString.c_str());
         GYTA[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GYTA[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GYTALumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GYTALumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

         Tree->Draw(Form("abs(GWW-%f)>>H", TrueGWW), CutString.c_str());
         GGWW[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GGWW[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GGWWLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GGWWLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

         Tree->Draw(Form("abs(A2ZZA1ZZ*2-%f)>>H", TrueA2), CutString.c_str());
         GA2[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA2[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA2Lumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA2Lumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

         Tree->Draw(Form("abs(A3ZZA1ZZ*2-%f)>>H", TrueA3), CutString.c_str());
         GA3[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA3[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA3Lumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA3Lumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));

         Tree->Draw(Form("abs(A4ZZA1ZZ*2-%f)>>H", TrueA4), CutString.c_str());
         GA4[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA4[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA4Lumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA4Lumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      }

      IndividualFile.Close();
   }

   Bar.Update(Count * 63);
   Bar.Print();
   Bar.PrintLine();

   File.cd();

   for(int i = 0; i < (int)GYT.size(); i++)
   {
      GYT[i]->Write();
      GYTA[i]->Write();
      GGWW[i]->Write();
      GA2[i]->Write();
      GA3[i]->Write();
      GA4[i]->Write();
      GYTLumi[i]->Write();
      GYTALumi[i]->Write();
      GGWWLumi[i]->Write();
      GA2Lumi[i]->Write();
      GA3Lumi[i]->Write();
      GA4Lumi[i]->Write();
   }

   File.Close();

   return 0;
}




