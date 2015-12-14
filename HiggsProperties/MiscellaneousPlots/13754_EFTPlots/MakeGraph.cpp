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
   double TrueGWW = 2;
   double TrueA2ZZ = 0.01;
   double TrueA3ZZ = 0;
   double TrueA4ZZ = 0.007;
   double TrueA2ZA = 0.014;
   double TrueA3ZA = 0;
   double TrueA4ZA = 0;
   double TrueA2AA = -0.008;
   double TrueA3AA = 0;

   if(argc < 14)
   {
      cerr << "Usage: " << argv[0] << " FileName Type Cut Efficiency  Point TrueA2ZZ TrueA3ZZ TrueA4ZZ TrueA2ZA TrueA3ZA TrueA4ZA TrueA2AA TrueA3AA" << endl;
      cerr << "   Example: " << argv[0] << " Graph.root Both A 1  A 0.01 0 0.007 0.014 0 0 -0.008 0" << endl;
      return -1;
   }

   FileName = argv[1];
   Type = argv[2];
   Cut = argv[3];
   Efficiency = atof(argv[4]);
   Point = argv[5];
   TrueA2ZZ = atof(argv[6]);
   TrueA3ZZ = atof(argv[7]);
   TrueA4ZZ = atof(argv[8]);
   TrueA2ZA = atof(argv[9]);
   TrueA3ZA = atof(argv[10]);
   TrueA4ZA = atof(argv[11]);
   TrueA2AA = atof(argv[12]);
   TrueA3AA = atof(argv[13]);

   int Count = 10;
   int N[] = {50, 100, 200, 400, 600, 1000, 2000, 4000, 7000, 10000};

   TFile File(FileName.c_str(), "RECREATE");

   vector<TGraphErrors *> GA2ZZ, GA3ZZ, GA4ZZ, GA2ZA, GA3ZA, GA4ZA, GA2AA, GA3AA, GFEM, GFEE;
   vector<TGraphErrors *> GA2ZZLumi, GA3ZZLumi, GA4ZZLumi, GA2ZALumi, GA3ZALumi, GA4ZALumi, GA2AALumi, GA3AALumi, GFEMLumi, GFEELumi;

   for(int i = 1; i <= 255; i++)
   {
      string Float = "NNNNNNNN";
      if(i % 2 == 1)          Float[0] = 'Y';
      if((i / 2) % 2 == 1)    Float[1] = 'Y';
      if((i / 4) % 2 == 1)    Float[2] = 'Y';
      if((i / 8) % 2 == 1)    Float[3] = 'Y';
      if((i / 16) % 2 == 1)   Float[4] = 'Y';
      if((i / 32) % 2 == 1)   Float[5] = 'Y';
      if((i / 64) % 2 == 1)   Float[6] = 'Y';
      if((i / 128) % 2 == 1)  Float[7] = 'Y';

      GA2ZZ.push_back(new TGraphErrors);
      GA3ZZ.push_back(new TGraphErrors);
      GA4ZZ.push_back(new TGraphErrors);
      GA2ZA.push_back(new TGraphErrors);
      GA3ZA.push_back(new TGraphErrors);
      GA4ZA.push_back(new TGraphErrors);
      GA2AA.push_back(new TGraphErrors);
      GA3AA.push_back(new TGraphErrors);
      GFEM.push_back(new TGraphErrors);
      GFEE.push_back(new TGraphErrors);
      GA2ZZLumi.push_back(new TGraphErrors);
      GA3ZZLumi.push_back(new TGraphErrors);
      GA4ZZLumi.push_back(new TGraphErrors);
      GA2ZALumi.push_back(new TGraphErrors);
      GA3ZALumi.push_back(new TGraphErrors);
      GA4ZALumi.push_back(new TGraphErrors);
      GA2AALumi.push_back(new TGraphErrors);
      GA3AALumi.push_back(new TGraphErrors);
      GFEMLumi.push_back(new TGraphErrors);
      GFEELumi.push_back(new TGraphErrors);

      string ID = Type + "_" + Cut + "_Count_" + Float + "_Point" + Point;

      GA2ZZ[i-1]->SetNameTitle(Form("A2ZZ_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA3ZZ[i-1]->SetNameTitle(Form("A3ZZ_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA4ZZ[i-1]->SetNameTitle(Form("A4ZZ_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA2ZA[i-1]->SetNameTitle(Form("A2ZA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA3ZA[i-1]->SetNameTitle(Form("A3ZA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA4ZA[i-1]->SetNameTitle(Form("A4ZA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA2AA[i-1]->SetNameTitle(Form("A2AA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA3AA[i-1]->SetNameTitle(Form("A3AA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GFEM[i-1]->SetNameTitle(Form("FEM_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GFEE[i-1]->SetNameTitle(Form("FEE_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));

      ID = Type + "_" + Cut + "_Lumi_" + Float + "_Point" + Point;

      GA2ZZLumi[i-1]->SetNameTitle(Form("A2ZZ_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA3ZZLumi[i-1]->SetNameTitle(Form("A3ZZ_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA4ZZLumi[i-1]->SetNameTitle(Form("A4ZZ_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA2ZALumi[i-1]->SetNameTitle(Form("A2ZA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA3ZALumi[i-1]->SetNameTitle(Form("A3ZA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA4ZALumi[i-1]->SetNameTitle(Form("A4ZA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA2AALumi[i-1]->SetNameTitle(Form("A2AA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GA3AALumi[i-1]->SetNameTitle(Form("A3AA_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GFEMLumi[i-1]->SetNameTitle(Form("FEM_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GFEELumi[i-1]->SetNameTitle(Form("FEE_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
   }

   ProgressBar Bar(cout, Count * 255);
   Bar.SetStyle(5);

   for(int i = 0; i < Count; i++)
   {
      TFile IndividualFile(Form("Trees/Result%s_Point%s_%s_%d.root", Type.c_str(), Point.c_str(), Cut.c_str(), N[i]));

      TTree *Tree = (TTree *)IndividualFile.Get("ResultTree");
      if(Tree == NULL)
         continue;

      double Factor = 2;
      if(Type != "BothS" && Type != "Both" && Type != "BothF" && Type != "BothHalf")
         Factor = 1;

      TH1D H("H", "", 100, -100, 100);

      for(int j = 1; j <= 255; j++)
      {
         Bar.Update(i * 255 + j - 1);
         Bar.Print();

         //                   0         1         2         3         4         5         6         7         8         9         0
         //                   01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
         string CutString1 = "Status == 3 && A2ZZError == 0 && A3ZZError == 0 && A4ZZError == 0";
         string CutString2 = "            && A2ZAError == 0 && A3ZAError == 0 && A4ZAError == 0";
         string CutString3 = "            && A2AAError == 0 && A3AAError == 0";

         if((j / 1) % 2 == 1)     CutString1[25] = '>', CutString1[26] = ' ';
         if((j / 2) % 2 == 1)     CutString1[43] = '>', CutString1[44] = ' ';
         if((j / 4) % 2 == 1)     CutString1[61] = '>', CutString1[62] = ' ';
         if((j / 8) % 2 == 1)     CutString2[25] = '>', CutString2[26] = ' ';
         if((j / 16) % 2 == 1)    CutString2[43] = '>', CutString2[44] = ' ';
         if((j / 32) % 2 == 1)    CutString2[61] = '>', CutString2[62] = ' ';
         if((j / 64) % 2 == 1)    CutString3[25] = '>', CutString3[26] = ' ';
         if((j / 128) % 2 == 1)   CutString3[43] = '>', CutString3[44] = ' ';

         string CutString = CutString1 + CutString2 + CutString3;

         string Float = "NNNNNNNN";
         if(j % 2 == 1)           Float[0] = 'Y';
         if((j / 2) % 2 == 1)     Float[1] = 'Y';
         if((j / 4) % 2 == 1)     Float[2] = 'Y';
         if((j / 8) % 2 == 1)     Float[3] = 'Y';
         if((j / 16) % 2 == 1)    Float[4] = 'Y';
         if((j / 32) % 2 == 1)    Float[5] = 'Y';
         if((j / 64) % 2 == 1)    Float[6] = 'Y';
         if((j / 128) % 2 == 1)   Float[7] = 'Y';

         Tree->Draw(Form("abs(A2ZZ-%f)>>H", TrueA2ZZ), CutString.c_str());
         if(H.Integral() == 0)
            continue;
         
         Tree->Draw(Form("abs(A2ZZ-%f)>>H", TrueA2ZZ), CutString.c_str());
         GA2ZZ[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA2ZZ[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA2ZZLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA2ZZLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(A3ZZ-%f)>>H", TrueA3ZZ), CutString.c_str());
         GA3ZZ[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA3ZZ[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA3ZZLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA3ZZLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(A4ZZ-%f)>>H", TrueA4ZZ), CutString.c_str());
         GA4ZZ[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA4ZZ[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA4ZZLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA4ZZLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(A2ZA-%f)>>H", TrueA2ZA), CutString.c_str());
         GA2ZA[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA2ZA[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA2ZALumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA2ZALumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(A3ZA-%f)>>H", TrueA3ZA), CutString.c_str());
         GA3ZA[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA3ZA[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA3ZALumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA3ZALumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(A4ZA-%f)>>H", TrueA4ZA), CutString.c_str());
         GA4ZA[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA4ZA[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA4ZALumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA4ZALumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(A2AA-%f)>>H", TrueA2AA), CutString.c_str());
         GA2AA[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA2AA[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA2AALumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA2AALumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(A3AA-%f)>>H", TrueA3AA), CutString.c_str());
         GA3AA[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GA3AA[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GA3AALumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GA3AALumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw("abs(Fem-Bem/(Sem+Bem))>>H", CutString.c_str());
         GFEM[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GFEM[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GFEMLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GFEMLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw("abs(Fee-Bee/(See+Bee))>>H", CutString.c_str());
         GFEE[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GFEE[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GFEELumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GFEELumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
      }

      IndividualFile.Close();
   }

   Bar.Update(Count * 255);
   Bar.Print();
   Bar.PrintLine();

   File.cd();

   for(int i = 0; i < (int)GA2ZZ.size(); i++)
   {
      if(GA2ZZ[i]     != NULL && GA2ZZ[i]->GetN()     > 0)   GA2ZZ[i]->Write();
      if(GA3ZZ[i]     != NULL && GA3ZZ[i]->GetN()     > 0)   GA3ZZ[i]->Write();
      if(GA4ZZ[i]     != NULL && GA4ZZ[i]->GetN()     > 0)   GA4ZZ[i]->Write();
      if(GA2ZA[i]     != NULL && GA2ZA[i]->GetN()     > 0)   GA2ZA[i]->Write();
      if(GA3ZA[i]     != NULL && GA3ZA[i]->GetN()     > 0)   GA3ZA[i]->Write();
      if(GA4ZA[i]     != NULL && GA4ZA[i]->GetN()     > 0)   GA4ZA[i]->Write();
      if(GA2AA[i]     != NULL && GA2AA[i]->GetN()     > 0)   GA2AA[i]->Write();
      if(GA3AA[i]     != NULL && GA3AA[i]->GetN()     > 0)   GA3AA[i]->Write();
      if(GFEM[i]      != NULL && GFEM[i]->GetN()      > 0)   GFEM[i]->Write();
      if(GFEE[i]      != NULL && GFEE[i]->GetN()      > 0)   GFEE[i]->Write();
      if(GA2ZZLumi[i] != NULL && GA2ZZLumi[i]->GetN() > 0)   GA2ZZLumi[i]->Write();
      if(GA3ZZLumi[i] != NULL && GA3ZZLumi[i]->GetN() > 0)   GA3ZZLumi[i]->Write();
      if(GA4ZZLumi[i] != NULL && GA4ZZLumi[i]->GetN() > 0)   GA4ZZLumi[i]->Write();
      if(GA2ZALumi[i] != NULL && GA2ZALumi[i]->GetN() > 0)   GA2ZALumi[i]->Write();
      if(GA3ZALumi[i] != NULL && GA3ZALumi[i]->GetN() > 0)   GA3ZALumi[i]->Write();
      if(GA4ZALumi[i] != NULL && GA4ZALumi[i]->GetN() > 0)   GA4ZALumi[i]->Write();
      if(GA2AALumi[i] != NULL && GA2AALumi[i]->GetN() > 0)   GA2AALumi[i]->Write();
      if(GA3AALumi[i] != NULL && GA3AALumi[i]->GetN() > 0)   GA3AALumi[i]->Write();
      if(GFEMLumi[i]  != NULL && GFEMLumi[i]->GetN()  > 0)   GFEMLumi[i]->Write();
      if(GFEELumi[i]  != NULL && GFEELumi[i]->GetN()  > 0)   GFEELumi[i]->Write();
   }

   File.Close();

   return 0;
}




