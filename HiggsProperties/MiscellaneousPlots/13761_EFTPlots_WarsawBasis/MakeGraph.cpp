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
   double TrueDeltaCZ = 0;
   double TrueDeltaCW = 0;
   double TrueDeltaM  = 0;
   double TrueCWW     = 0;
   double TrueCWWD    = 0;
   double TrueCWB     = 0;
   double TrueCWBD    = 0;
   double TrueCBB     = 0;
   double TrueCBBD    = 0;

   if(argc < 15)
   {
      cerr << "Usage: " << argv[0] << " FileName Type Cut Efficiency  Point DeltaCZ DeltaCW DeltaM  CWW CWWD CWB CWBD CBB CBBD" << endl;
      cerr << "   Example: " << argv[0] << " Graph.root Both A 1  0   0 0 0   0 0 0 0 0 0" << endl;
      return -1;
   }

   FileName = argv[1];
   Type = argv[2];
   Cut = argv[3];
   Efficiency = atof(argv[4]);
   Point = argv[5];
   TrueDeltaCZ = atof(argv[6]);
   TrueDeltaCW = atof(argv[7]);
   TrueDeltaM = atof(argv[8]);
   TrueCWW = atof(argv[9]);
   TrueCWWD = atof(argv[10]);
   TrueCWB = atof(argv[11]);
   TrueCWBD = atof(argv[12]);
   TrueCBB = atof(argv[13]);
   TrueCBBD = atof(argv[14]);

   int Count = 10;
   int N[] = {50, 100, 200, 400, 600, 1000, 2000, 4000, 7000, 10000};

   TFile File(FileName.c_str(), "RECREATE");

   vector<TGraphErrors *> GDeltaCZ, GDeltaCW, GDeltaM, GCWW, GCWWD, GCWB, GCWBD, GCBB, GCBBD, GFEM, GFEE;
   vector<TGraphErrors *> GDeltaCZLumi, GDeltaCWLumi, GDeltaMLumi, GCWWLumi, GCWWDLumi, GCWBLumi, GCWBDLumi, GCBBLumi, GCBBDLumi, GFEMLumi, GFEELumi;

   for(int i = 1; i <= 1023; i++)
   {
      string Float = "NNNNNNNNN";
      if(i % 2 == 1)          Float[0] = 'Y';
      if((i / 2) % 2 == 1)    Float[1] = 'Y';
      if((i / 4) % 2 == 1)    Float[2] = 'Y';
      if((i / 8) % 2 == 1)    Float[3] = 'Y';
      if((i / 16) % 2 == 1)   Float[4] = 'Y';
      if((i / 32) % 2 == 1)   Float[5] = 'Y';
      if((i / 64) % 2 == 1)   Float[6] = 'Y';
      if((i / 128) % 2 == 1)  Float[7] = 'Y';
      if((i / 256) % 2 == 1)  Float[8] = 'Y';

      string Square = "WithSquare";
      if((i / 512) % 2 == 1)  Square = "NoSquare";

      GDeltaCZ.push_back(new TGraphErrors);
      GDeltaCW.push_back(new TGraphErrors);
      GDeltaM.push_back(new TGraphErrors);
      GCWW.push_back(new TGraphErrors);
      GCWWD.push_back(new TGraphErrors);
      GCWB.push_back(new TGraphErrors);
      GCWBD.push_back(new TGraphErrors);
      GCBB.push_back(new TGraphErrors);
      GCBBD.push_back(new TGraphErrors);
      GFEM.push_back(new TGraphErrors);
      GFEE.push_back(new TGraphErrors);

      GDeltaCZLumi.push_back(new TGraphErrors);
      GDeltaCWLumi.push_back(new TGraphErrors);
      GDeltaMLumi.push_back(new TGraphErrors);
      GCWWLumi.push_back(new TGraphErrors);
      GCWWDLumi.push_back(new TGraphErrors);
      GCWBLumi.push_back(new TGraphErrors);
      GCWBDLumi.push_back(new TGraphErrors);
      GCBBLumi.push_back(new TGraphErrors);
      GCBBDLumi.push_back(new TGraphErrors);
      GFEMLumi.push_back(new TGraphErrors);
      GFEELumi.push_back(new TGraphErrors);

      string ID = Type + "_" + Cut + "_Count_" + Float + "_" + Square + "_Point" + Point;

      GDeltaCZ[i-1]->SetNameTitle(Form("DeltaCZ_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GDeltaCW[i-1]->SetNameTitle(Form("DeltaCW_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GDeltaM[i-1]->SetNameTitle(Form("DeltaM_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCWW[i-1]->SetNameTitle(Form("CWW_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCWWD[i-1]->SetNameTitle(Form("CWWD_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCWB[i-1]->SetNameTitle(Form("CWB_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCWBD[i-1]->SetNameTitle(Form("CWBD_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCBB[i-1]->SetNameTitle(Form("CBB_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCBBD[i-1]->SetNameTitle(Form("CBBD_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GFEM[i-1]->SetNameTitle(Form("FEM_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GFEE[i-1]->SetNameTitle(Form("FEE_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));

      ID = Type + "_" + Cut + "_Lumi_" + Float + "_" + Square + "_Point" + Point;

      GDeltaCZLumi[i-1]->SetNameTitle(Form("DeltaCZ_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GDeltaCWLumi[i-1]->SetNameTitle(Form("DeltaCW_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GDeltaMLumi[i-1]->SetNameTitle(Form("DeltaM_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCWWLumi[i-1]->SetNameTitle(Form("CWW_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCWWDLumi[i-1]->SetNameTitle(Form("CWWD_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCWBLumi[i-1]->SetNameTitle(Form("CWB_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCWBDLumi[i-1]->SetNameTitle(Form("CWBD_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCBBLumi[i-1]->SetNameTitle(Form("CBB_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GCBBDLumi[i-1]->SetNameTitle(Form("CBBD_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GFEMLumi[i-1]->SetNameTitle(Form("FEM_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
      GFEELumi[i-1]->SetNameTitle(Form("FEE_%s", ID.c_str()), Form("%s, %s, N, %s (Point%s)", Type.c_str(), Cut.c_str(), Float.c_str(), Point.c_str()));
   }

   ProgressBar Bar(cout, Count * 1023);
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

      for(int j = 1; j <= 1023; j++)
      {
         Bar.Update(i * 1023 + j - 1);
         Bar.Print();

         //                   0         1         2         3         4         5         6         7         8         9         0
         //                   01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
         string CutString1 = "Status == 3 && DeltaCZError == 0 && DeltaCWError == 0 && DeltaMError == 0";
         string CutString2 = "            && CWWError == 0 && CWWDError == 0";
         string CutString3 = "            && CWBError == 0 && CWBDError == 0";
         string CutString4 = "            && CBBError == 0 && CBBDError == 0";
         string CutString5 = "            && NoSquareMode == 0";

         if((j / 1) % 2 == 1)     CutString1[28] = '>', CutString1[29] = ' ';
         if((j / 2) % 2 == 1)     CutString1[49] = '>', CutString1[50] = ' ';
         if((j / 4) % 2 == 1)     CutString1[69] = '>', CutString1[70] = ' ';
         if((j / 8) % 2 == 1)     CutString2[24] = '>', CutString2[25] = ' ';
         if((j / 16) % 2 == 1)    CutString2[42] = '>', CutString2[43] = ' ';
         if((j / 32) % 2 == 1)    CutString3[24] = '>', CutString3[25] = ' ';
         if((j / 64) % 2 == 1)    CutString3[42] = '>', CutString3[43] = ' ';
         if((j / 128) % 2 == 1)   CutString4[24] = '>', CutString4[25] = ' ';
         if((j / 256) % 2 == 1)   CutString4[42] = '>', CutString4[43] = ' ';
         if((j / 512) % 2 == 1)   CutString5[28] = '>', CutString5[29] = ' ';

         string CutString = CutString1 + CutString2 + CutString3 + CutString4 + CutString5;

         Tree->Draw(Form("abs(DeltaCZ-%f)>>H", TrueDeltaCZ), CutString.c_str());
         if(H.Integral() == 0)
            continue;
         
         Tree->Draw(Form("abs(DeltaCZ-%f)>>H", TrueDeltaCZ), CutString.c_str());
         GDeltaCZ[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GDeltaCZ[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GDeltaCZLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GDeltaCZLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(DeltaCW-%f)>>H", TrueDeltaCW), CutString.c_str());
         GDeltaCW[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GDeltaCW[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GDeltaCWLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GDeltaCWLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(DeltaM-%f)>>H", TrueDeltaM), CutString.c_str());
         GDeltaM[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GDeltaM[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GDeltaMLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GDeltaMLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(CWW-%f)>>H", TrueCWW), CutString.c_str());
         GCWW[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GCWW[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GCWWLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GCWWLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(CWWD-%f)>>H", TrueCWWD), CutString.c_str());
         GCWWD[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GCWWD[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GCWWDLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GCWWDLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(CWB-%f)>>H", TrueCWB), CutString.c_str());
         GCWB[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GCWB[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GCWBLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GCWBLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(CWBD-%f)>>H", TrueCWBD), CutString.c_str());
         GCWBD[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GCWBD[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GCWBDLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GCWBDLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(CBB-%f)>>H", TrueCBB), CutString.c_str());
         GCBB[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GCBB[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GCBBLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GCBBLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
         Tree->Draw(Form("abs(CBBD-%f)>>H", TrueCBBD), CutString.c_str());
         GCBBD[j-1]->SetPoint(i, N[i] * Factor, H.GetMean() * sqrt(PI / 2));
         GCBBD[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         GCBBDLumi[j-1]->SetPoint(i, N[i] * Factor / Efficiency, H.GetMean() * sqrt(PI / 2));
         GCBBDLumi[j-1]->SetPointError(i, 0, H.GetMeanError() * sqrt(PI / 2));
         
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

   Bar.Update(Count * 1023);
   Bar.Print();
   Bar.PrintLine();

   File.cd();

   for(int i = 0; i < (int)GDeltaCZ.size(); i++)
   {
      if(GDeltaCZ[i]     != NULL && GDeltaCZ[i]->GetN()     > 0)   GDeltaCZ[i]->Write();
      if(GDeltaCW[i]     != NULL && GDeltaCW[i]->GetN()     > 0)   GDeltaCW[i]->Write();
      if(GDeltaM[i]      != NULL && GDeltaM[i]->GetN()      > 0)   GDeltaM[i]->Write();
      if(GCWW[i]         != NULL && GCWW[i]->GetN()         > 0)   GCWW[i]->Write();
      if(GCWWD[i]        != NULL && GCWWD[i]->GetN()        > 0)   GCWWD[i]->Write();
      if(GCWB[i]         != NULL && GCWB[i]->GetN()         > 0)   GCWB[i]->Write();
      if(GCWBD[i]        != NULL && GCWBD[i]->GetN()        > 0)   GCWBD[i]->Write();
      if(GCBB[i]         != NULL && GCBB[i]->GetN()         > 0)   GCBB[i]->Write();
      if(GCBBD[i]        != NULL && GCBBD[i]->GetN()        > 0)   GCBBD[i]->Write();
      if(GFEM[i]         != NULL && GFEM[i]->GetN()         > 0)   GFEM[i]->Write();
      if(GFEE[i]         != NULL && GFEE[i]->GetN()         > 0)   GFEE[i]->Write();
      if(GDeltaCZLumi[i] != NULL && GDeltaCZLumi[i]->GetN() > 0)   GDeltaCZLumi[i]->Write();
      if(GDeltaCWLumi[i] != NULL && GDeltaCWLumi[i]->GetN() > 0)   GDeltaCWLumi[i]->Write();
      if(GDeltaMLumi[i]  != NULL && GDeltaMLumi[i]->GetN()  > 0)   GDeltaMLumi[i]->Write();
      if(GCWWLumi[i]     != NULL && GCWWLumi[i]->GetN()     > 0)   GCWWLumi[i]->Write();
      if(GCWWDLumi[i]    != NULL && GCWWDLumi[i]->GetN()    > 0)   GCWWDLumi[i]->Write();
      if(GCWBLumi[i]     != NULL && GCWBLumi[i]->GetN()     > 0)   GCWBLumi[i]->Write();
      if(GCWBDLumi[i]    != NULL && GCWBDLumi[i]->GetN()    > 0)   GCWBDLumi[i]->Write();
      if(GCBBLumi[i]     != NULL && GCBBLumi[i]->GetN()     > 0)   GCBBLumi[i]->Write();
      if(GCBBDLumi[i]    != NULL && GCBBDLumi[i]->GetN()    > 0)   GCBBDLumi[i]->Write();
      if(GFEMLumi[i]     != NULL && GFEMLumi[i]->GetN()     > 0)   GFEMLumi[i]->Write();
      if(GFEELumi[i]     != NULL && GFEELumi[i]->GetN()     > 0)   GFEELumi[i]->Write();
   }

   File.Close();

   return 0;
}




