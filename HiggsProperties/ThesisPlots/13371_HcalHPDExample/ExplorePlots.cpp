#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TStyle.h"

#include "SetStyle.h"
#include "PlotHelper2.h"
#include "HPDViewHelper.h"

int main();
void MakePulsePlot(TH1D &H, string OutputBase);
void MakeEventPlot(TH2D &H, string OutputBase);
void MakeHPDPlot(HPDViewHelper &H, string OutputBase);

int main()
{
   gStyle->SetPaintTextFormat(".2g");

   SetThesisStyle();

   HPDViewHelper HPDView;
      
   TFile File("NoiseTree_532.root");

   TTree *Tree = (TTree *)File.Get("ExportTree/HcalNoiseTree");

   PsFileHelper PsFile1("Displays.ps");
   PsFile1.AddTextPage("Events!");
   
   PsFileHelper PsFile2("PulsesDisplays.ps");
   PsFile2.AddTextPage("HPDs!");

   int PulseCount;
   int IEta[5184], IPhi[5184], Depth[5184];
   double Energy[5184], Charge[5184][10], RBXEnergy[72];
   Tree->SetBranchAddress("PulseCount", &PulseCount);
   Tree->SetBranchAddress("IEta", IEta);
   Tree->SetBranchAddress("IPhi", IPhi);
   Tree->SetBranchAddress("Depth", Depth);
   Tree->SetBranchAddress("Energy", Energy);
   Tree->SetBranchAddress("Charge", Charge);
   Tree->SetBranchAddress("RBXEnergy", RBXEnergy);

   int EntryCount = Tree->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      HPDView.CleanHistograms();

      TH2D H(Form("H%06d", iE), Form("Event %06d;ieta;iphi", iE), 61, -30, 30, 72, 1, 73);
      H.SetStats(0);

      for(int iP = 0; iP < PulseCount; iP++)
      {
         HPDView.Fill(IEta[iP], IPhi[iP], Depth[iP], Energy[iP]);
         H.Fill(IEta[iP], IPhi[iP], Energy[iP]);
      }

      PsFile1.AddPlot(H, "colz", false, true);

      PsFile2.AddTextPage(Form("Event %d", iE));
      for(int i = 0; i < 72; i++)
         for(int j = 0; j < 4; j++)
            if(HPDView[i][j].GetMaximum() > 10)
               PsFile2.AddPlot(HPDView[i][j], "colz text00");

      if(iE == 175 || iE == 101 || iE == 170 || iE == 203 || iE == 355 || iE == 389 || iE == 398 || iE == 436
         || iE == 439 || iE == 451 || iE == 475 || iE == 477 || iE == 488)
      {
         MakeEventPlot(H, Form("Plots/Event%06d", iE));
         MakeHPDPlot(HPDView, Form("Plots/HPD%06d", iE));
      }

      if(iE >= 500)
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

   TCanvas C;

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
   H.GetZaxis()->SetTitle("Energy (GeV)");
   H.SetMinimum(0);

   TCanvas C;

   H.Draw("lego20z");

   C.SaveAs(Form("%s.png", OutputBase.c_str()));
   C.SaveAs(Form("%s.C",   OutputBase.c_str()));
   C.SaveAs(Form("%s.eps", OutputBase.c_str()));
   C.SaveAs(Form("%s.pdf", OutputBase.c_str()));
}

void MakeHPDPlot(HPDViewHelper &H, string OutputBase)
{
   for(int i = 0; i < 72; i++)
   {
      for(int j = 0; j < 4; j++)
      {
         if(H[i][j].GetMaximum() < 10)
            continue;

         H[i][j].SetTitle("");
         H[i][j].GetXaxis()->SetTickLength(0.0);
         H[i][j].GetYaxis()->SetTickLength(0.0);
         H[i][j].GetXaxis()->SetLabelSize(0.0);
         H[i][j].GetYaxis()->SetLabelSize(0.0);
         H[i][j].SetMinimum(0);
         H[i][j].GetZaxis()->SetTitle("Energy (GeV)");

         TCanvas C;

         H[i][j].Draw("colz text");

         C.SaveAs(Form("%s-%02d-%d.png", OutputBase.c_str(), i, j));
         C.SaveAs(Form("%s-%02d-%d.C",   OutputBase.c_str(), i, j));
         C.SaveAs(Form("%s-%02d-%d.eps", OutputBase.c_str(), i, j));
         C.SaveAs(Form("%s-%02d-%d.pdf", OutputBase.c_str(), i, j));
      }
   }
}



