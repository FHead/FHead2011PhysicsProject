#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLatex.h"
#include "TStyle.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

#define MAXRECHIT 10000

struct EventID;
struct JRAMessenger;
struct HCALMessenger;
int main();
map<EventID, int> GetHCALTreeIndex(TTree *T);
map<EventID, int> GetJRATreeIndex(TTree *T);
vector<int> JetMatching(JRAMessenger &M1, JRAMessenger &M2);

struct EventID
{
   int Run;
   int Lumi;
   int Event;
   EventID(int run, int lumi, int event)
      : Run(run), Lumi(lumi), Event(event)
   {
   }
   bool operator <(const EventID &other) const
   {
      if(Run < other.Run)   return true;
      if(Run > other.Run)   return false;
      if(Lumi < other.Lumi)   return true;
      if(Lumi > other.Lumi)   return false;
      if(Event < other.Event)   return true;
      if(Event > other.Event)   return false;
   }
};

struct JRAMessenger
{
   TTree *Tree;
   vector<float> *RefPT, *RefEta, *RefPhi;
   vector<float> *JetPT, *JetEta, *JetPhi;
   vector<int> *NPU;
   vector<int> *TPU;
   float PTHat;
   JRAMessenger(TTree *T)
      : Tree(T), RefPT(NULL), RefEta(NULL), RefPhi(NULL), JetPT(NULL), JetEta(NULL), JetPhi(NULL),
        NPU(NULL), TPU(NULL)
   {
      if(T == NULL)
         return;

      Tree->SetBranchAddress("refpt", &RefPT);
      Tree->SetBranchAddress("refeta", &RefEta);
      Tree->SetBranchAddress("refphi", &RefPhi);
      Tree->SetBranchAddress("jtpt", &JetPT);
      Tree->SetBranchAddress("jteta", &JetEta);
      Tree->SetBranchAddress("jtphi", &JetPhi);
      Tree->SetBranchAddress("npus", &NPU);
      Tree->SetBranchAddress("bxns", &TPU);
      Tree->SetBranchAddress("pthat", &PTHat);
   }
   void GetEntry(int Entry)
   {
      if(Tree == NULL)
         return;
      if(Entry >= Tree->GetEntries())
         return;

      Tree->GetEntry(Entry);
   }
};

struct HCALMessenger
{
   TTree *Tree;
   int RecHitCount;
   double RecHitEnergy[MAXRECHIT];
   int RecHitIEta[MAXRECHIT];
   int RecHitIPhi[MAXRECHIT];
   int RecHitADC[MAXRECHIT][8];
   HCALMessenger(TTree *T)
      : Tree(T), RecHitCount(0)
   {
      if(T == NULL)
         return;

      Tree->SetBranchAddress("RecHitCount", &RecHitCount);
      Tree->SetBranchAddress("RecHitEnergy", &RecHitEnergy);
      Tree->SetBranchAddress("RecHitIEta", &RecHitIEta);
      Tree->SetBranchAddress("RecHitIPhi", &RecHitIPhi);
      Tree->SetBranchAddress("RecHitADC", &RecHitADC);
   }
   void GetEntry(int Entry)
   {
      if(Tree == NULL)
         return;
      if(Entry >= Tree->GetEntries())
         return;

      Tree->GetEntry(Entry);
   }
};

int main()
{
   SetThesisStyle();

   gStyle->SetPaintTextFormat("4g");

   PdfFileHelper PdfFile("JetPlots.pdf");
   PdfFile.AddTextPage("Jet comparison");

   TFile F_JRA_NoPU("JRA_NoPUEvents.root");
   TFile F_JRA_WithPU("JRA_WithPUEvents.root");
   TFile F_HCAL_NoPU("HCAL_NoPUEvents.root");
   TFile F_HCAL_WithPU("HCAL_WithPUEvents.root");

   TTree *T_JRA_NoPU = (TTree *)F_JRA_NoPU.Get("ak4pf/t");
   TTree *T_JRA_WithPU = (TTree *)F_JRA_WithPU.Get("ak4pf/t");
   TTree *T_HCAL_NoPU = (TTree *)F_HCAL_NoPU.Get("rechits/RecHitTree");
   TTree *T_HCAL_WithPU = (TTree *)F_HCAL_WithPU.Get("rechits/RecHitTree");

   map<EventID, int> Index_JRA_NoPU = GetJRATreeIndex(T_JRA_NoPU);
   map<EventID, int> Index_JRA_WithPU = GetJRATreeIndex(T_JRA_WithPU);
   map<EventID, int> Index_HCAL_NoPU = GetHCALTreeIndex(T_HCAL_NoPU);
   map<EventID, int> Index_HCAL_WithPU = GetHCALTreeIndex(T_HCAL_WithPU);

   JRAMessenger M_JRA_NoPU(T_JRA_NoPU);
   JRAMessenger M_JRA_WithPU(T_JRA_WithPU);
   HCALMessenger M_HCAL_NoPU(T_HCAL_NoPU);
   HCALMessenger M_HCAL_WithPU(T_HCAL_WithPU);

   for(auto iter : Index_JRA_NoPU)
   {
      EventID ID = iter.first;

      if(Index_JRA_NoPU.find(ID) == Index_JRA_NoPU.end())         continue;
      if(Index_JRA_WithPU.find(ID) == Index_JRA_WithPU.end())     continue;
      if(Index_HCAL_NoPU.find(ID) == Index_HCAL_NoPU.end())       continue;
      if(Index_HCAL_WithPU.find(ID) == Index_HCAL_WithPU.end())   continue;

      M_JRA_NoPU.GetEntry(Index_JRA_NoPU[ID]);
      M_JRA_WithPU.GetEntry(Index_JRA_WithPU[ID]);
      M_HCAL_NoPU.GetEntry(Index_HCAL_NoPU[ID]);
      M_HCAL_WithPU.GetEntry(Index_HCAL_WithPU[ID]);

      string PUString = "(";
      for(int i = 0; i < (int)M_JRA_WithPU.NPU->size(); i++)
      {
         if(i != 0)
            PUString = PUString + ", ";
         if((*M_JRA_WithPU.TPU)[i] == 0)   PUString = PUString + Form("[%d]", (*M_JRA_WithPU.NPU)[i]);
         else                              PUString = PUString + Form("%d", (*M_JRA_WithPU.NPU)[i]);
      }
      PUString = PUString + ")";
      cout << PUString << endl << endl;

      // PdfFile.AddTextPage(Form("(%d %d %d)", ID.Run, ID.Lumi, ID.Event));

      vector<int> JetIndex = JetMatching(M_JRA_NoPU, M_JRA_WithPU);

      TGraph NoPUGenJetLocation, WithPUGenJetLocation;
      TH2D NoPURecHitMap("NoPURecHitMap", ";ieta;iphi", 51, -25.5, 25.5, 144, -35.5, 108.5);
      TH2D WithPURecHitMap("WithPURecHitMap", ";ieta;iphi", 51, -25.5, 25.5, 144, -35.5, 108.5);

      for(int i = 0; i < M_HCAL_NoPU.RecHitCount; i++)
      {
         NoPURecHitMap.Fill(M_HCAL_NoPU.RecHitIEta[i], M_HCAL_NoPU.RecHitIPhi[i], M_HCAL_NoPU.RecHitEnergy[i]);
         NoPURecHitMap.Fill(M_HCAL_NoPU.RecHitIEta[i], M_HCAL_NoPU.RecHitIPhi[i] - 72, M_HCAL_NoPU.RecHitEnergy[i]);
         NoPURecHitMap.Fill(M_HCAL_NoPU.RecHitIEta[i], M_HCAL_NoPU.RecHitIPhi[i] + 72, M_HCAL_NoPU.RecHitEnergy[i]);
      }
      for(int i = 0; i < M_HCAL_WithPU.RecHitCount; i++)
      {
         WithPURecHitMap.Fill(M_HCAL_WithPU.RecHitIEta[i], M_HCAL_WithPU.RecHitIPhi[i], M_HCAL_WithPU.RecHitEnergy[i]);
         WithPURecHitMap.Fill(M_HCAL_WithPU.RecHitIEta[i], M_HCAL_WithPU.RecHitIPhi[i] + 72, M_HCAL_WithPU.RecHitEnergy[i]);
         WithPURecHitMap.Fill(M_HCAL_WithPU.RecHitIEta[i], M_HCAL_WithPU.RecHitIPhi[i] - 72, M_HCAL_WithPU.RecHitEnergy[i]);
      }

      for(int i = 0; i < (int)M_JRA_NoPU.JetPT->size(); i++)
      {
         int j = JetIndex[i];
         if(j < 0)
            continue;

         if((*M_JRA_NoPU.RefPT)[i] < 80)
            continue;
         if(fabs((*M_JRA_NoPU.RefEta)[i]) > 1.5)
            continue;

         double EffectiveIEta = (*M_JRA_NoPU.RefEta)[i] / 0.087;
         double EffectiveIPhi = (*M_JRA_NoPU.RefPhi)[i] / 0.087;
         if(EffectiveIEta > 0)   EffectiveIEta = EffectiveIEta + 0.5;
         if(EffectiveIEta < 0)   EffectiveIEta = EffectiveIEta - 0.5;
         if(EffectiveIPhi < 0)   EffectiveIPhi = EffectiveIPhi + 72;
         NoPUGenJetLocation.SetPoint(NoPUGenJetLocation.GetN(), EffectiveIEta, EffectiveIPhi);

         EffectiveIEta = (*M_JRA_WithPU.RefEta)[i] / 0.087;
         EffectiveIPhi = (*M_JRA_WithPU.RefPhi)[i] / 0.087;
         if(EffectiveIEta > 0)   EffectiveIEta = EffectiveIEta + 0.5;
         if(EffectiveIEta < 0)   EffectiveIEta = EffectiveIEta - 0.5;
         if(EffectiveIPhi < 0)   EffectiveIPhi = EffectiveIPhi + 72;
         WithPUGenJetLocation.SetPoint(WithPUGenJetLocation.GetN(), EffectiveIEta, EffectiveIPhi);

         int BinX = 12, BinY = 12;
         double XMin = EffectiveIEta - BinX * 0.5;
         double XMax = EffectiveIEta + BinX * 0.5;
         double YMin = EffectiveIPhi - BinY * 0.5;
         double YMax = EffectiveIPhi + BinY * 0.5;
         TH2D NoPURecHitMapSmall("NoPURecHitMapSmall", "No PU;i#eta;i#phi",
            BinX, XMin, XMax, BinY, YMin, YMax);
         TH2D WithPURecHitMapSmall("WithPURecHitMapSmall", "With PU;i#eta;i#phi",
            BinX, XMin, XMax, BinY, YMin, YMax);
         TH2D DifferenceRecHitMapSmall("DifferenceRecHitMapSmall", "Difference (NoPU - WithPU);i#eta;i#phi",
            BinX, XMin, XMax, BinY, YMin, YMax);

         map<double, string, greater<double>> NoPUADCs;
         map<double, string, greater<double>> WithPUADCs;

         for(int k = 0; k < M_HCAL_NoPU.RecHitCount; k++)
         {
            int IEta = M_HCAL_NoPU.RecHitIEta[k];
            int IPhi = M_HCAL_NoPU.RecHitIPhi[k];
            double Energy = M_HCAL_NoPU.RecHitEnergy[k];

            if(IEta < XMin || IEta > XMax)
               continue;

            bool PhiInRange = false;
            if(IPhi >= YMin && IPhi <= YMax)              PhiInRange = true;
            if(IPhi - 72 >= YMin && IPhi - 72 <= YMax)    PhiInRange = true;
            if(IPhi + 72 >= YMin && IPhi + 72 <= YMax)    PhiInRange = true;
            if(PhiInRange == false)
               continue;

            NoPURecHitMapSmall.Fill(IEta, IPhi, Energy);
            NoPURecHitMapSmall.Fill(IEta, IPhi - 72, Energy);
            NoPURecHitMapSmall.Fill(IEta, IPhi + 72, Energy);
            DifferenceRecHitMapSmall.Fill(IEta, IPhi, Energy);
            DifferenceRecHitMapSmall.Fill(IEta, IPhi - 72, Energy);
            DifferenceRecHitMapSmall.Fill(IEta, IPhi + 72, Energy);

            string ADCString = "[";
            for(int l = 0; l < 8; l++)
            {
               if(l != 0)   ADCString = ADCString + ", ";
               ADCString = ADCString + Form("%d", M_HCAL_NoPU.RecHitADC[k][l]);
            }
            ADCString = ADCString + "]";
            NoPUADCs.insert(pair<double, string>(Energy, ADCString));
         }
         for(int k = 0; k < M_HCAL_WithPU.RecHitCount; k++)
         {
            int IEta = M_HCAL_WithPU.RecHitIEta[k];
            int IPhi = M_HCAL_WithPU.RecHitIPhi[k];
            double Energy = M_HCAL_WithPU.RecHitEnergy[k];

            if(IEta < XMin || IEta > XMax)
               continue;

            bool PhiInRange = false;
            if(IPhi >= YMin && IPhi <= YMax)              PhiInRange = true;
            if(IPhi - 72 >= YMin && IPhi - 72 <= YMax)    PhiInRange = true;
            if(IPhi + 72 >= YMin && IPhi + 72 <= YMax)    PhiInRange = true;
            if(PhiInRange == false)
               continue;
            
            WithPURecHitMapSmall.Fill(IEta, IPhi, Energy);
            WithPURecHitMapSmall.Fill(IEta, IPhi - 72, Energy);
            WithPURecHitMapSmall.Fill(IEta, IPhi + 72, Energy);
            DifferenceRecHitMapSmall.Fill(IEta, IPhi, -Energy);
            DifferenceRecHitMapSmall.Fill(IEta, IPhi - 72, -Energy);
            DifferenceRecHitMapSmall.Fill(IEta, IPhi + 72, -Energy);
            
            string ADCString = "[";
            for(int l = 0; l < 8; l++)
            {
               if(l != 0)   ADCString = ADCString + ", ";
               ADCString = ADCString + Form("%d", M_HCAL_WithPU.RecHitADC[k][l]);
            }
            ADCString = ADCString + "]";
            WithPUADCs.insert(pair<double, string>(Energy, ADCString));
         }
         
         NoPURecHitMapSmall.SetStats(0);
         WithPURecHitMapSmall.SetStats(0);
         DifferenceRecHitMapSmall.SetStats(0);

         TLatex Latex;
         Latex.SetNDC();
         Latex.SetTextFont(42);
         Latex.SetTextSize(0.035);

         TCanvas Canvas;
         Canvas.Divide(2, 2);

         Canvas.cd(1);
         NoPURecHitMapSmall.Draw("colz text30");
         Canvas.cd(1)->SetLogz();

         Canvas.cd(2);
         WithPURecHitMapSmall.Draw("colz text30");
         Canvas.cd(2)->SetLogz();

         double X = 0.05, Y = 0.95, Offset = 0.05;

         Canvas.cd(3);
         Latex.DrawLatex(X, Y - Offset * 0, Form("(Run: %d, Lumi: %d, Event: %d)", ID.Run, ID.Lumi, ID.Event));
         Latex.DrawLatex(X, Y - Offset * 1, "PU = 0");
         Latex.DrawLatex(X, Y - Offset * 2, Form("Ref PT = %.2f, Eta = %.2f, Phi = %.2f", (*M_JRA_NoPU.RefPT)[i], (*M_JRA_NoPU.RefEta)[i], (*M_JRA_NoPU.RefPhi)[i]));
         Latex.DrawLatex(X, Y - Offset * 3, Form("Jet PT = %.2f, Eta = %.2f, Phi = %.2f", (*M_JRA_NoPU.JetPT)[i], (*M_JRA_NoPU.JetEta)[i], (*M_JRA_NoPU.JetPhi)[i]));
         if(NoPUADCs.size() > 0)
            Latex.DrawLatex(X, Y - Offset * 4, Form("ADC (highest) = %s", NoPUADCs.begin()->second.c_str()));

         Latex.DrawLatex(X, Y - Offset * 7, Form("PU = %s", PUString.c_str()));
         Latex.DrawLatex(X, Y - Offset * 8, Form("Ref PT = %.2f, Eta = %.2f, Phi = %.2f", (*M_JRA_WithPU.RefPT)[j], (*M_JRA_WithPU.RefEta)[j], (*M_JRA_WithPU.RefPhi)[j]));
         Latex.DrawLatex(X, Y - Offset * 9, Form("Jet PT = %.2f, Eta = %.2f, Phi = %.2f", (*M_JRA_WithPU.JetPT)[j], (*M_JRA_WithPU.JetEta)[j], (*M_JRA_WithPU.JetPhi)[j]));
         if(WithPUADCs.size() > 0)
            Latex.DrawLatex(X, Y - Offset * 10, Form("ADC (highest) = %s", WithPUADCs.begin()->second.c_str()));
         
         Canvas.cd(4);
         DifferenceRecHitMapSmall.SetMaximum(+25);
         DifferenceRecHitMapSmall.SetMinimum(-25);
         DifferenceRecHitMapSmall.Draw("colz text30");
         
         if(NoPURecHitMapSmall.GetMaximum() > 10 && WithPURecHitMapSmall.GetMaximum() > 10)
            PdfFile.AddCanvas(Canvas);
      }

      /*
      TCanvas Canvas;

      NoPURecHitMap.SetStats(0);
      WithPURecHitMap.SetStats(0);
      NoPUGenJetLocation.SetMarkerStyle(20);
      WithPUGenJetLocation.SetMarkerStyle(20);
      NoPUGenJetLocation.SetMarkerColor(kMagenta);
      WithPUGenJetLocation.SetMarkerColor(kMagenta);
      
      TH2D HWorldBig("HWorldBig", ";i#eta;i#phi", 51, -25.5, 25.5, 72, 0.5, 72.5);
      HWorldBig.SetStats(0);

      HWorldBig.Draw("axis");
      NoPURecHitMap.Draw("colz same");
      NoPUGenJetLocation.Draw("p");
      PdfFile.AddCanvas(Canvas);
      
      HWorldBig.Draw("axis");
      WithPURecHitMap.Draw("colz same");
      WithPUGenJetLocation.Draw("p");
      PdfFile.AddCanvas(Canvas);
      */
   }

   F_HCAL_WithPU.Close();
   F_HCAL_NoPU.Close();
   F_JRA_WithPU.Close();
   F_JRA_NoPU.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

map<EventID, int> GetHCALTreeIndex(TTree *T)
{
   map<EventID, int> Result;

   if(T == NULL)
      return Result;

   long long Run, Lumi, Event;
   T->SetBranchAddress("Run", &Run);
   T->SetBranchAddress("Lumi", &Lumi);
   T->SetBranchAddress("Event", &Event);

   int EntryCount = T->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);
      Result.insert(pair<EventID, int>(EventID(Run, Lumi, Event), iE));
   }

   return Result;
}

map<EventID, int> GetJRATreeIndex(TTree *T)
{
   map<EventID, int> Result;

   if(T == NULL)
      return Result;
   
   long long Run, Lumi, Event;
   T->SetBranchAddress("run", &Run);
   T->SetBranchAddress("lumi", &Lumi);
   T->SetBranchAddress("evt", &Event);

   int EntryCount = T->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);
      Result.insert(pair<EventID, int>(EventID(Run, Lumi, Event), iE));
   }

   return Result;
}

vector<int> JetMatching(JRAMessenger &M1, JRAMessenger &M2)
{
   if(M1.RefPT == NULL)
      return vector<int>();

   vector<int> Result(M1.RefPT->size(), -1);

   for(int i = 0; i < (int)M1.RefPT->size(); i++)
   {
      double BestDR = -1;
      int BestIndex = -1;

      for(int j = 0; j < (int)M2.RefPT->size(); j++)
      {
         double DEta = (*M1.RefEta)[i] - (*M2.RefEta)[j];
         double DPhi = (*M1.RefPhi)[i] - (*M2.RefPhi)[j];
         if(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
         if(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;

         double DR = sqrt(DEta * DEta + DPhi * DPhi);
         if(BestDR < 0 || DR < BestDR)
         {
            BestIndex = j;
            BestDR = DR;
         }
      }

      if(BestDR < 0.01)
         Result[i] = BestIndex;
   }

   return Result;
}





