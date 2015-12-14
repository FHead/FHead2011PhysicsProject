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
void FillHistograms(TTree *T, TH1D &HR, TH1D &HC);

int main()
{
   SetStyle();

   TFile F1("SingleMu.root");
   TFile F2("MET.root");

   TTree *T1 = (TTree *)F1.Get("ExportTree/HcalNoiseTree");
   TTree *T2 = (TTree *)F2.Get("ExportTree/HcalNoiseTree");

   TH1D H1C("H1C", ";Charge - true charge (fC);a.u.", 100, -10, 25);
   TH1D H1R("H1R", ";Charge - true charge (fC);a.u.", 100, -10, 25);
   TH1D H2C("H2C", ";Charge - true charge (fC);a.u.", 100, -10, 25);
   TH1D H2R("H2R", ";Charge - true charge (fC);a.u.", 100, -10, 25);

   FillHistograms(T1, H1R, H1C);
   FillHistograms(T2, H2R, H2C);

   TLegend Legend(0.50, 0.85, 0.85, 0.70);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H1R, "Before correction", "l");
   Legend.AddEntry(&H1C, "After correction", "l");

   TCanvas C("C", "C", 1024, 1024);
   // C.SetLogy();

   H1C.Draw("");
   H1R.Draw("same");
   Legend.Draw();
   C.SaveAs("HcalNoise-25nsData-CorrectedEnergy.png");
   C.SaveAs("HcalNoise-25nsData-CorrectedEnergy.C");
   C.SaveAs("HcalNoise-25nsData-CorrectedEnergy.eps");
   C.SaveAs("HcalNoise-25nsData-CorrectedEnergy.pdf");

   H2C.Draw("");
   H2R.Draw("same");
   Legend.Draw();
   C.SaveAs("HcalNoise-25nsData-CorrectedEnergy2.png");
   C.SaveAs("HcalNoise-25nsData-CorrectedEnergy2.C");
   C.SaveAs("HcalNoise-25nsData-CorrectedEnergy2.eps");
   C.SaveAs("HcalNoise-25nsData-CorrectedEnergy2.pdf");

   F2.Close();
   F1.Close();

   return 0;
}

void FillHistograms(TTree *T, TH1D &HR, TH1D &HC)
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

         HR.Fill(Charge[iP][4]);
         HC.Fill(CorrectedCharge[5]);
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   HR.SetStats(0);
   HR.GetXaxis()->SetTitleOffset(1.1);
   HR.GetYaxis()->SetTitleOffset(1.2);
   HR.SetLineWidth(2);

   HC.SetStats(0);
   HC.GetXaxis()->SetTitleOffset(1.1);
   HC.GetYaxis()->SetTitleOffset(1.2);
   HC.SetLineWidth(2);
   
   HR.SetLineColor(kRed);
   HC.SetLineColor(kBlack);
}




