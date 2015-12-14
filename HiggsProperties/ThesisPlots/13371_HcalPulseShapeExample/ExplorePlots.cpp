#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "PlotHelper2.h"

int main();
void MakePulsePlot(TH1D &H, string OutputBase);
void MakeEventPlot(TH2D &H, string OutputBase);

int main()
{
   SetStyle();

   TFile File("MET/NoiseTree_532.root");

   TTree *Tree = (TTree *)File.Get("ExportTree/HcalNoiseTree");

   PsFileHelper PsFile1("Displays.ps");
   PsFile1.AddTextPage("Events!");
   
   PsFileHelper PsFile2("PulsesDisplays.ps");
   PsFile2.AddTextPage("Pulses!");

   int PulseCount;
   int IEta[5184], IPhi[5184];
   double Energy[5184], Charge[5184][10];
   Tree->SetBranchAddress("PulseCount", &PulseCount);
   Tree->SetBranchAddress("IEta", IEta);
   Tree->SetBranchAddress("IPhi", IPhi);
   Tree->SetBranchAddress("Energy", Energy);
   Tree->SetBranchAddress("Charge", Charge);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      TH2D H(Form("H%06d", iE), Form("Event %06d;ieta;iphi", iE), 61, -30, 30, 72, 1, 73);
      H.SetStats(0);

      for(int iP = 0; iP < PulseCount; iP++)
         H.Fill(IEta[iP], IPhi[iP], Energy[iP]);

      if(iE == 101 || iE == 52 || iE == 125 || iE == 169 || iE == 170 || iE == 175
         || iE == 324 || iE == 334 || iE == 355 || iE == 358 || iE == 359 || iE == 370 || iE == 375
         || iE == 389 || iE == 398)
      {
         for(int iP = 0; iP < PulseCount; iP++)
         {
            if(Energy[iP] < 5)
               continue;
      
            TH1D HP(Form("H%06d%06d", iE, iP), Form("Event %06d, pulse %06d;TS (25ns);Charge (fC)", iE, iP), 10, 0, 10);
            HP.SetStats(0);

            for(int iT = 0; iT < 10; iT++)
               HP.Fill(iT, Charge[iP][iT]);

            for(int iT = 0; iT < 10; iT++)
               HP.GetXaxis()->SetBinLabel(iT + 1, Form("TS%d", iT));
            if(HP.GetMinimum() > 0)
               HP.SetMinimum(0);

            PsFile2.AddPlot(HP);

            if((iE == 389 && iP == 22) || (iE == 175 && iP == 0) || (iE == 175 && iP == 3) || (iE == 389 && iP == 529)
               || (iE == 324 && iP == 1) || (iE == 334 && iP == 0))
               MakePulsePlot(HP, Form("Plots/Pulse%06d%06d", iE, iP));
         }
      
         PsFile1.AddPlot(H, "colz", false, true);

         MakeEventPlot(H, Form("Plots/Event%06d", iE));
      }

      if(iE >= 1000)
         break;
   }

   PsFile2.AddTimeStampPage();
   PsFile2.Close();
   
   PsFile1.AddTimeStampPage();
   PsFile1.Close();

   return 0;
}

void MakePulsePlot(TH1D &H, string OutputBase)
{
   for(int iT = 0; iT < 10; iT++)
      H.GetXaxis()->SetBinLabel(iT + 1, Form("TS%d", iT));
   if(H.GetMinimum() > 0)
      H.SetMinimum(0);

   H.SetLineWidth(2);
   H.SetTitle("");
   H.GetXaxis()->SetTitleOffset(1.1);
   H.GetYaxis()->SetTitleOffset(1.35);
   H.GetXaxis()->SetLabelSize(0.05);

   TCanvas C("C", "C", 1024, 1024);

   H.Draw();

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C",   OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));
}

void MakeEventPlot(TH2D &H, string OutputBase)
{
   H.SetTitle("");
   H.GetXaxis()->SetTitleOffset(1.8);
   H.GetYaxis()->SetTitleOffset(2.0);
   H.GetXaxis()->SetTitle("i#eta   ");
   H.GetYaxis()->SetTitle("i#phi");
   H.SetMinimum(0);

   TCanvas C("C", "C", 1024, 1024);

   H.Draw("lego20z");

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C",   OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));
}




