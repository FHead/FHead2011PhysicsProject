#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "ProgressBar.h"
#include "SetStyle.h"

#include "Shapes.h"

int main();
void FillHistograms(TTree *T, TH1D &H4, TH1D &H5, TH1D &H6);

int main()
{
   SetStyle();

   TFile F1("SingleMu.root");
   TFile F2("MET.root");

   TTree *T1 = (TTree *)F1.Get("ExportTree/HcalNoiseTree");
   TTree *T2 = (TTree *)F2.Get("ExportTree/HcalNoiseTree");

   TH1D H14("H14", ";TS4';a.u.", 100, -500, 200);
   TH1D H15("H15", ";TS5';a.u.", 100, -500, 200);
   TH1D H16("H16", ";TS6';a.u.", 100, -500, 200);
   TH1D H24("H24", ";TS4';a.u.", 100, -500, 200);
   TH1D H25("H25", ";TS5';a.u.", 100, -500, 200);
   TH1D H26("H26", ";TS6';a.u.", 100, -500, 200);

   FillHistograms(T1, H14, H15, H16);
   FillHistograms(T2, H24, H25, H26);

   H14.SetLineColor(kBlack);
   H15.SetLineColor(kBlack);
   H16.SetLineColor(kBlack);
   H24.SetLineColor(kRed);
   H25.SetLineColor(kRed);
   H26.SetLineColor(kRed);

   TLegend Legend(0.20, 0.80, 0.55, 0.65);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H14, "SingleMu dataset", "l");
   Legend.AddEntry(&H24, "MET dataset", "l");

   TCanvas C("C", "C", 1024, 1024);
   C.SetLogy();

   H14.Draw();
   H24.Draw("same");
   Legend.Draw();
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy1.png");
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy1.C");
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy1.eps");
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy1.pdf");

   H15.Draw();
   H25.Draw("same");
   Legend.Draw();
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy2.png");
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy2.C");
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy2.eps");
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy2.pdf");

   H16.Draw();
   H26.Draw("same");
   Legend.Draw();
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy3.png");
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy3.C");
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy3.eps");
   C.SaveAs("HcalNoise-25nsData-NegativeEnergy3.pdf");

   F2.Close();
   F1.Close();

   return 0;
}

void FillHistograms(TTree *T, TH1D &H4, TH1D &H5, TH1D &H6)
{
   int PulseCount;
   int IEta[5184];
   double Charge[5184][10];

   T->SetBranchAddress("PulseCount", &PulseCount);
   T->SetBranchAddress("IEta", IEta);
   T->SetBranchAddress("Charge", Charge);

   int EntryCount = T->GetEntries();

   ProgressBar Bar(cerr, EntryCount);
   Bar.SetStyle(3);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      if(iE % (EntryCount / 300) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      double (*a1)(double);
      double (*a2)(double);
      double (*a3)(double);

      for(int iP = 0; iP < PulseCount; iP++)
      {
         if(IEta[iP] < 0)
            IEta[iP] = -IEta[iP];

         switch(IEta[iP])
         {
         case 1:   case 2:   case 3:   case 4:   case 5:
         case 6:   case 7:   case 8:   case 9:   case 10:
         case 11:  case 12:  case 13:  case 14:  case 15:
         case 16:  default:
            a1 = a1_HB;
            a2 = a2_HB;
            a3 = a3_HB;
            break;
         case 17:  case 18:  case 19:  case 20:
            a1 = a1_1720;
            a2 = a2_1720;
            a3 = a3_1720;
            break;
         case 21:  case 22:  case 23:
            a1 = a1_2123;
            a2 = a2_2123;
            a3 = a3_2123;
            break;
         case 24:  case 25:
            a1 = a1_2425;
            a2 = a2_2425;
            a3 = a3_2425;
            break;
         case 26:  case 27:
            a1 = a1_2627;
            a2 = a2_2627;
            a3 = a3_2627;
            break;
         case 28:  case 29:
            a1 = a1_28;
            a2 = a2_28;
            a3 = a3_28;
            break;
         }

         double CorrectedCharge[10] = {0};

         CorrectedCharge[0] = Charge[iP][0];
         CorrectedCharge[1] = Charge[iP][1] - a1(CorrectedCharge[0]);
         CorrectedCharge[2] = Charge[iP][2] - a1(CorrectedCharge[1]) - a2(CorrectedCharge[0]);
         CorrectedCharge[3] = Charge[iP][3] - a1(CorrectedCharge[2]) - a2(CorrectedCharge[1]) - a3(CorrectedCharge[0]);
         CorrectedCharge[4] = Charge[iP][4] - a1(CorrectedCharge[3]) - a2(CorrectedCharge[2]) - a3(CorrectedCharge[1]);
         CorrectedCharge[5] = Charge[iP][5] - a1(CorrectedCharge[4]) - a2(CorrectedCharge[3]) - a3(CorrectedCharge[2]);
         CorrectedCharge[6] = Charge[iP][6] - a1(CorrectedCharge[5]) - a2(CorrectedCharge[4]) - a3(CorrectedCharge[3]);
         CorrectedCharge[7] = Charge[iP][7] - a1(CorrectedCharge[6]) - a2(CorrectedCharge[5]) - a3(CorrectedCharge[4]);
         CorrectedCharge[8] = Charge[iP][8] - a1(CorrectedCharge[7]) - a2(CorrectedCharge[6]) - a3(CorrectedCharge[5]);
         CorrectedCharge[9] = Charge[iP][9] - a1(CorrectedCharge[8]) - a2(CorrectedCharge[7]) - a3(CorrectedCharge[6]);

         H4.Fill(CorrectedCharge[4]);
         H5.Fill(CorrectedCharge[5]);
         H6.Fill(CorrectedCharge[6]);
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   H4.SetStats(0);
   H4.GetXaxis()->SetTitleOffset(1.1);
   H4.GetYaxis()->SetTitleOffset(1.2);
   H4.SetLineWidth(2);

   H5.SetStats(0);
   H5.GetXaxis()->SetTitleOffset(1.1);
   H5.GetYaxis()->SetTitleOffset(1.2);
   H5.SetLineWidth(2);

   H6.SetStats(0);
   H6.GetXaxis()->SetTitleOffset(1.1);
   H6.GetYaxis()->SetTitleOffset(1.2);
   H6.SetLineWidth(2);
}




