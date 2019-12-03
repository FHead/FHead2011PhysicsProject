#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TF1.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"
#include "ProgressBar.h"

int main(int argc, char *argv[]);
void Fill(vector<vector<TProfile *>> &P, vector<double> &PTBins, vector<double> &RhoBins, string FileName, string TreeName, double EtaMin, double EtaMax);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> FileNames = CL.GetStringVector("input");
   vector<string> GoodNames = CL.GetStringVector("goodinput");
   string OutputFileName    = CL.Get("output");
   double EtaMin            = CL.GetDouble("etamin", -3.0);
   double EtaMax            = CL.GetDouble("etamax", -1.5);
   vector<double> PTBins    = CL.GetDoubleVector("pt", vector<double>({10, 15, 20, 30, 50, 70, 100, 150, 200, 300, 500, 1000}));
   vector<double> RhoBins   = CL.GetDoubleVector("rho", vector<double>({0, 10, 20, 30, 40, 50, 60}));

   string TreeName          = CL.Get("tree", "OutputTree");
   int NP = PTBins.size() - 1;
   int NR = RhoBins.size() - 1;

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("L1 studies");

   vector<vector<TProfile *>> POffsetVsPhi;
   vector<vector<TProfile *>> GOffsetVsPhi;
   for(int iP = 0; iP < NP; iP++)
   {
      POffsetVsPhi.push_back(vector<TProfile *>());
      GOffsetVsPhi.push_back(vector<TProfile *>());
      for(int iR = 0; iR < NR; iR++)
      {
         string Title = Form("PT %.1f-%.1f, Rho %.1f-%.1f;RefPhi",
            PTBins[iP], PTBins[iP+1], RhoBins[iR], RhoBins[iR+1]);
         POffsetVsPhi[iP].push_back(new TProfile(Form("P_%d_%d", iP, iR), Title.c_str(), 40, -M_PI, M_PI));
         GOffsetVsPhi[iP].push_back(new TProfile(Form("G_%d_%d", iP, iR), Title.c_str(), 40, -M_PI, M_PI));
      }
   }

   double *PP = &PTBins[0];
   double *PR = &RhoBins[0];
   TH2D HDepth("HDepth", ";PT;Rho", NP, PP, NR, PR);

   for(string FileName : FileNames)
      Fill(POffsetVsPhi, PTBins, RhoBins, FileName, TreeName, EtaMin, EtaMax);
   for(string FileName : GoodNames)
      Fill(GOffsetVsPhi, PTBins, RhoBins, FileName, TreeName, EtaMin, EtaMax);

   for(int iP = 0; iP < NP; iP++)
   {
      for(int iR = 0; iR < NR; iR++)
      {
         POffsetVsPhi[iP][iR]->SetMarkerColor(kRed);
         POffsetVsPhi[iP][iR]->SetLineColor(kRed);

         TCanvas Canvas;
         POffsetVsPhi[iP][iR]->Draw();
         GOffsetVsPhi[iP][iR]->Draw("same");
         PdfFile.AddCanvas(Canvas);

         TH1D H("H", "Offset difference;RefPhi", 40, -M_PI, M_PI);
         for(int i = 1; i <= 40; i++)
         {
            double V1 = POffsetVsPhi[iP][iR]->GetBinContent(i);
            double V2 = GOffsetVsPhi[iP][iR]->GetBinContent(i);
            double E1 = POffsetVsPhi[iP][iR]->GetBinError(i);
            double E2 = GOffsetVsPhi[iP][iR]->GetBinError(i);
            H.SetBinContent(i, V1 - V2);
            H.SetBinError(i, sqrt(E1 * E1 + E2 * E2));
         }

         TF1 F("F", "[0]+[1]/2*erf((x-[2])/[4])+[1]/2*erf(([3]-x)/[4])");
         F.SetParameters(0, 0.1, -0.9, -1.6, 0.2828);
         F.FixParameter(0, 0);
         F.FixParameter(2, -0.872665);
         F.FixParameter(3, -1.570796);
         F.FixParameter(4, 0.2828);
         H.Fit(&F);

         HDepth.SetBinContent(iP + 1, iR + 1, F.GetParameter(1));
         HDepth.SetBinError(iP + 1, iR + 1, F.GetParError(1));

         PdfFile.AddPlot(H);
      }
   }

   gStyle->SetPaintTextFormat(".3g");
   HDepth.SetStats(0);
   PdfFile.AddPlot(HDepth, "colz text15 error", false, false, false, true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   for(auto V : POffsetVsPhi)
      for(auto P : V)
         delete P;

   return 0;
}

void Fill(vector<vector<TProfile *>> &P, vector<double> &PTBins, vector<double> &RhoBins, string FileName, string TreeName, double EtaMin, double EtaMax)
{
   int NP = PTBins.size() - 1;
   int NR = RhoBins.size() - 1;
   
   TFile File(FileName.c_str());

   TTree *Tree = (TTree *)File.Get(TreeName.c_str());

   double PTHat, Rho;
   double RefPT, RefEta, RefPhi;
   double PUPT, PUEta, PUPhi;
   double NoPUPT, NoPUEta, NoPUPhi;
   double RecoDR;

   Tree->SetBranchAddress("PTHat",   &PTHat);
   Tree->SetBranchAddress("Rho",     &Rho);
   Tree->SetBranchAddress("RefPT",   &RefPT);
   Tree->SetBranchAddress("RefEta",  &RefEta);
   Tree->SetBranchAddress("RefPhi",  &RefPhi);
   Tree->SetBranchAddress("PUPT",    &PUPT);
   Tree->SetBranchAddress("PUEta",   &PUEta);
   Tree->SetBranchAddress("PUPhi",   &PUPhi);
   Tree->SetBranchAddress("NoPUPT",  &NoPUPT);
   Tree->SetBranchAddress("NoPUEta", &NoPUEta);
   Tree->SetBranchAddress("NoPUPhi", &NoPUPhi);
   Tree->SetBranchAddress("RecoDR",  &RecoDR);

   int EntryCount = Tree->GetEntries();
   ProgressBar Bar(cout, EntryCount);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);

      Bar.Update(iE);
      if(EntryCount < 300 || (iE % (EntryCount / 200)) == 0)
         Bar.Print();

      if(PTHat > 1000)   // crazy event
         continue;

      // if(RecoDR > 0.1)
      //    continue;

      if(RefEta < EtaMin || RefEta >= EtaMax)
         continue;

      int IP = -1, IR = -1;
      for(int iP = 0; iP < NP; iP++)
         if(RefPT >= PTBins[iP] && RefPT < PTBins[iP+1])
            IP = iP;
      for(int iR = 0; iR < NR; iR++)
         if(Rho >= RhoBins[iR] && Rho < RhoBins[iR+1])
            IR = iR;

      if(IP < 0 || IR < 0)   // we don't have this bin
         continue;

      P[IP][IR]->Fill(RefPhi, PUPT - NoPUPT);
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   File.Close();
}



