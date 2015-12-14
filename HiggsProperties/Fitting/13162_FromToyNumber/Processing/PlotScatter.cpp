#include <iostream>
using namespace std;

#include "TChain.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH2D.h"
#include "TH1D.h"

int main(int argc, char *argv[])
{
   string JHUFileName = "Sync_0_noSys.root";
   string OurFileName = "All_0_noSys.root";
   string ResultBase = "SM_AllFinalState";

   if(argc < 4)
   {
      cerr << "Usage: " << argv[0] << " JHUFile OurFile ResultNameBase" << endl;
      return -1;
   }

   JHUFileName = argv[1];
   OurFileName = argv[2];
   ResultBase = argv[3];

   TH1D HJHU("HJHU", ";f_{a3}", 30, -1, 1);   HJHU.Sumw2();
   TH1D HUs("HUs", ";f_{a3}", 30, -1, 1);     HUs.Sumw2();

   double JHU[1000] = {0};
   TChain JHUTree("limit", "limit");
   JHUTree.AddFile(JHUFileName.c_str());
   int iToy;
   float CMS_zz4l_fg4;
   JHUTree.SetBranchAddress("iToy", &iToy);
   JHUTree.SetBranchAddress("CMS_zz4l_fg4", &CMS_zz4l_fg4);
   int JHUEntryCount = JHUTree.GetEntries();
   for(int iE = 0; iE < JHUEntryCount; iE++)
   {
      JHUTree.GetEntry(iE);
      JHU[iE] = CMS_zz4l_fg4;

      HJHU.Fill(CMS_zz4l_fg4);
   }

   double Us[1000] = {0};
   for(int i = 0; i < 1000; i++)
      Us[i] = -1000;
   TChain UsTree("ResultTree", "ResultTree");
   UsTree.AddFile(OurFileName.c_str());
   float Toy;
   float A3ZZA1ZZ;
   float Good;
   UsTree.SetBranchAddress("Toy", &Toy);
   UsTree.SetBranchAddress("A3ZZA1ZZ", &A3ZZA1ZZ);
   UsTree.SetBranchAddress("Good", &Good);
   int UsEntryCount = UsTree.GetEntries();
   for(int iE = 0; iE < UsEntryCount; iE++)
   {
      UsTree.GetEntry(iE);
      // if(Good < 0.5)
      //    continue;
      double S3 = A3ZZA1ZZ * A3ZZA1ZZ / 5.042 / 5.042;
      double FA3 = S3 / (1 + S3);
      if(A3ZZA1ZZ > 0)
         FA3 = -FA3;
      Us[(int)(Toy+0.0001)] = FA3;

      HUs.Fill(FA3);
   }

   TGraph G;
   for(int i = 0; i < 1000; i++)
   {
      if(Us[i] < -1)
         continue;

      // cout << i << " " << Us[i] << " " << JHU[i] << endl;

      G.SetPoint(G.GetN(), Us[i], JHU[i]);
   }
   G.SetMarkerStyle(11);

   TH2D HWorld("HWorld", ";Caltech;JHU", 10, -1, 1, 10, -1, 1);
   HWorld.SetStats(0);

   TGraph G2;
   G2.SetPoint(0, -1, -1);
   G2.SetPoint(1, +1, +1);
   TGraph G3;
   G3.SetPoint(0, -1, +1);
   G3.SetPoint(1, +1, -1);
   G3.SetLineStyle(kDashed);

   TCanvas C("C", "C", 1024, 1024);
   HWorld.Draw();
   G.Draw("p");
   G2.Draw("l");
   G3.Draw("l");
   C.SaveAs((ResultBase + ".png").c_str());
   C.SaveAs((ResultBase + ".C"  ).c_str());
   C.SaveAs((ResultBase + ".pdf").c_str());
   C.SaveAs((ResultBase + ".eps").c_str());

   HJHU.SetMinimum(0);
   HJHU.Scale(1 / HJHU.Integral());
   HUs.Scale(1 / HUs.Integral());

   HJHU.SetStats(0);
   HJHU.SetLineWidth(2);
   HJHU.SetLineColor(kRed);

   HUs.SetStats(0);
   HUs.SetLineWidth(2);
   HUs.SetLineColor(kBlue);

   TLegend Legend(0.15, 0.8, 0.4, 0.65);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&HJHU, "JHU", "l");
   Legend.AddEntry(&HUs, "Caltech", "l");

   HJHU.Draw("error");
   HUs.Draw("same error");
   Legend.Draw();
   C.SaveAs((ResultBase + "_1D.png").c_str());
   C.SaveAs((ResultBase + "_1D.C"  ).c_str());
   C.SaveAs((ResultBase + "_1D.pdf").c_str());
   C.SaveAs((ResultBase + "_1D.eps").c_str());

   return 0;
}






