#include <fstream>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "PlotHelper.h"
#include "GenparticleTree.h"

#define PI 3.14159265358979323846264338327950288479716939937510

// Categories:
//    -1. not final tau (goes into tau gamma)
//    1. mu nu nu
//    2. e nu nu
//    3. nu pi-
//    4. nu pi0 pi-
//    5. nu pi0 pi0 pi-
//    6. nu pi+ pi- pi-
//    7. nu pi+ pi- pi- pi0
//    8. otherwise

void PlotDistributions();
bool HasTau(GenParticleTree &Tree);
int FindCategory(GenParticleTree &Tree, int index);

double GetMass(double P[4]);
double GetP(double P[4]);
double GetPT(double P[4]);
double GetEta(double P[4]);
double GetPhi(double P[4]);
double GetAngle(double P1[4], double P2[4]);
double GetDR(double P1[4], double P2[4]);

void PlotDistributions()
{
   PsFileHelper PsFile("ChannelDistributions.ps");
   PsFile.AddTextPage("Channel-by-channel distribution comparison");

   vector<string> CategoryString;
   CategoryString.push_back("Everything together");
   CategoryString.push_back("Muon + neutrinos");
   CategoryString.push_back("Electron + neutrinos");
   CategoryString.push_back("pi- nu");
   CategoryString.push_back("pi0 pi- nu");
   CategoryString.push_back("pi0 pi0 pi- nu");
   CategoryString.push_back("pi- pi- pi+ nu");
   CategoryString.push_back("pi0 pi- pi- pi+ nu");
   CategoryString.push_back("otherwise");

   vector<TH1D *> HTauPT;
   vector<TH1D *> HTauPhi;
   vector<TH1D *> HTauEta;
   vector<TH1D *> HNuTauPT;
   vector<TH1D *> HNuTauPhi;
   vector<TH1D *> HNuTauEta;
   vector<TH1D *> HTauNuAngle;
   vector<TH1D *> HTauNuDR;
   vector<TH1D *> HNuTauPTFraction;
   vector<TH2D *> HTauNuAngleVsTauP;
   vector<TH2D *> HTauNuDRVsTauP;
   vector<TH2D *> HNuTauPTFractionVsTauP;
   vector<TH1D *> HVisiblePT;
   vector<TH1D *> HVisiblePhi;
   vector<TH1D *> HVisibleEta;
   vector<TH1D *> HVisibleMass;
   vector<TH1D *> HTauVisibleAngle;
   vector<TH1D *> HTauVisibleDR;
   vector<TH1D *> HVisiblePTFraction;
   vector<TH2D *> HTauVisibleAngleVsTauP;
   vector<TH2D *> HTauVisibleDRVsTauP;
   vector<TH2D *> HVisiblePTFractionVsTauP;

   for(int i = 0; i <= 8; i++)
   {
      HTauPT.push_back(new TH1D(Form("HTauPT_%d", i),
         Form("Tau PT distribution for category %d", i), 100, 0, 100));
      HTauPhi.push_back(new TH1D(Form("HTauPhi_%d", i),
         Form("Tau phi distribution for category %d", i), 100, -3.2, 3.2));
      HTauEta.push_back(new TH1D(Form("HTauEta_%d", i),
         Form("Tau Eta distribution for category %d", i), 100, -5, 5));

      HNuTauPT.push_back(new TH1D(Form("HNuTauPT_%d", i),
         Form("Nu_tau PT distribution for category %d", i), 100, 0, 100));
      HNuTauPhi.push_back(new TH1D(Form("HNuTauPhi_%d", i),
         Form("Nu_tau phi distribution for category %d", i), 100, -3.2, 3.2));
      HNuTauEta.push_back(new TH1D(Form("HNuTauEta_%d", i),
         Form("Nu_tau Eta distribution for category %d", i), 100, -5, 5));

      HTauNuAngle.push_back(new TH1D(Form("HTauNuAngle_%d", i),
         Form("Angle between tau and nu_tau, category %d", i), 100, -0.05, 0.55));
      HTauNuDR.push_back(new TH1D(Form("HTauNuDR_%d", i),
         Form("DR between tau and nu_tau, category %d", i), 100, -0.05, 0.55));
      HNuTauPTFraction.push_back(new TH1D(Form("HNuTauPTFraction_%d", i),
         Form("Fraction of PT carried by neutrino in category %d", i), 100, -0.05, 1.05));

      HTauNuAngleVsTauP.push_back(new TH2D(Form("HTauNuAngleVsTauP_%d", i),
         Form("Angle between tau and nu_tau vs. tau momentum, category %d;Angle;Momentum", i),
         100, -0.05, 0.55, 100, 0, 100));
      HTauNuDRVsTauP.push_back(new TH2D(Form("HTauNuDRVsTauP_%d", i),
         Form("DR between tau and nu_tau vs. tau momentum, category %d;DR;Momentum", i),
         100, -0.05, 0.55, 100, 0, 100));
      HNuTauPTFractionVsTauP.push_back(new TH2D(Form("HNuTauPTFractionVsTauP_%d", i),
         Form("Fraction of PT carried by neutrino vs. tau momentum, in category %d;Fraction;Momentum", i),
         100, -0.1, 1.1, 100, 0, 100));
      
      HVisiblePT.push_back(new TH1D(Form("HVisiblePT_%d", i),
         Form("Visible PT distribution for category %d", i), 100, 0, 100));
      HVisiblePhi.push_back(new TH1D(Form("HVisiblePhi_%d", i),
         Form("Visible phi distribution for category %d", i), 100, -3.2, 3.2));
      HVisibleEta.push_back(new TH1D(Form("HVisibleEta_%d", i),
         Form("Visible Eta distribution for category %d", i), 100, -5, 5));
      HVisibleMass.push_back(new TH1D(Form("HVisibleMass_%d", i),
         Form("Visible Mass distribution for category %d", i), 100, 0, 2));

      HTauVisibleAngle.push_back(new TH1D(Form("HTauVisibleAngle_%d", i),
         Form("Angle between tau and visible, category %d", i), 100, -0.05, 0.55));
      HTauVisibleDR.push_back(new TH1D(Form("HTauVisibleDR_%d", i),
         Form("DR between tau and visible, category %d", i), 100, -0.05, 0.55));
      HVisiblePTFraction.push_back(new TH1D(Form("HVisiblePTFraction_%d", i),
         Form("Fraction of PT carried by visible in category %d", i), 100, -0.05, 1.05));

      HTauVisibleAngleVsTauP.push_back(new TH2D(Form("HTauVisibleAngleVsTauP_%d", i),
         Form("Angle between tau and visible vs. tau momentum, category %d;Angle;Momentum", i),
         100, -0.05, 0.55, 100, 0, 100));
      HTauVisibleDRVsTauP.push_back(new TH2D(Form("HTauVisibleDRVsTauP_%d", i),
         Form("DR between tau and visible vs. tau momentum, category %d;DR;Momentum", i),
         100, -0.05, 0.55, 100, 0, 100));
      HVisiblePTFractionVsTauP.push_back(new TH2D(Form("HVisiblePTFractionVsTauP_%d", i),
         Form("Fraction of PT carried by visible vs. tau momentum, in category %d;Fraction;Momentum", i),
         100, -0.1, 1.1, 100, 0, 100));
   }

   ifstream in("Samples/6553TauEnrichedWSample");
   
   int Size = 0;
   in >> Size;

   for(int i = 0; i < Size; i++)
   {
      if((i + 1) % 5000 == 0)
         cout << "Processing entry " << i + 1 << "/" << Size << endl;

      GenParticleTree Tree;
      Tree.LoadFromStream(in);

      if(HasTau(Tree) == false)
         continue;

      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].PDGID != 15)
            continue;

         int Category = FindCategory(Tree, j);
         if(Category < 0)
            continue;

         vector<int> Daughters = Tree[j].Daughters;
         for(int k = 0; k < (int)Daughters.size(); k++)
         {
            if(Tree[Daughters[k]].PDGID == 213 || Tree[Daughters[k]].PDGID == 223
               || Tree[Daughters[k]].PDGID == -213 || Tree[Daughters[k]].PDGID == 113)
            {
               Daughters.insert(Daughters.end(), Tree[Daughters[k]].Daughters.begin(),
                  Tree[Daughters[k]].Daughters.end());

               Daughters.erase(Daughters.begin() + k);
               k = k - 1;
            }
         }
         
         int NuTauIndex = 0;
         for(int k = 0; k < (int)Daughters.size(); k++)
            if(Tree[Daughters[k]].PDGID == 16)   // tau neutrino
               NuTauIndex = Daughters[k];

         double VisibleP[4] = {0};
         for(int k = 0; k < (int)Daughters.size(); k++)
         {
            if(Tree[Daughters[k]].PDGID == 12 || Tree[Daughters[k]].PDGID == -12)
               continue;
            if(Tree[Daughters[k]].PDGID == 14 || Tree[Daughters[k]].PDGID == -14)
               continue;
            if(Tree[Daughters[k]].PDGID == 16 || Tree[Daughters[k]].PDGID == -16)
               continue;

            VisibleP[0] = VisibleP[0] + Tree[Daughters[k]].P[0];
            VisibleP[1] = VisibleP[1] + Tree[Daughters[k]].P[1];
            VisibleP[2] = VisibleP[2] + Tree[Daughters[k]].P[2];
            VisibleP[3] = VisibleP[3] + Tree[Daughters[k]].P[3];
         }

         double TauP = GetP(Tree[j].P);
         double TauPT = GetPT(Tree[j].P);
         double TauPhi = GetPhi(Tree[j].P);
         double TauEta = GetEta(Tree[j].P);
         
         double NuTauPT = GetPT(Tree[NuTauIndex].P);
         double NuTauPhi = GetPhi(Tree[NuTauIndex].P);
         double NuTauEta = GetEta(Tree[NuTauIndex].P);

         double TauNuAngle = GetAngle(Tree[j].P, Tree[NuTauIndex].P);
         double TauNuDR = GetDR(Tree[j].P, Tree[NuTauIndex].P);
         double NuTauPTFraction = NuTauPT / TauPT;

         double VisiblePT = GetPT(VisibleP);
         double VisiblePhi = GetPhi(VisibleP);
         double VisibleEta = GetEta(VisibleP);
         double VisibleMass = GetMass(VisibleP);

         double TauVisibleAngle = GetAngle(Tree[j].P, VisibleP);
         double TauVisibleDR = GetDR(Tree[j].P, VisibleP);
         double VisiblePTFraction = VisiblePT / TauPT;

         HTauPT[0]->Fill(TauPT);
         HTauPT[Category]->Fill(TauPT);
         HTauPhi[0]->Fill(TauPhi);
         HTauPhi[Category]->Fill(TauPhi);
         HTauEta[0]->Fill(TauEta);
         HTauEta[Category]->Fill(TauEta);

         HNuTauPT[0]->Fill(NuTauPT);
         HNuTauPT[Category]->Fill(NuTauPT);
         HNuTauPhi[0]->Fill(NuTauPhi);
         HNuTauPhi[Category]->Fill(NuTauPhi);
         HNuTauEta[0]->Fill(NuTauEta);
         HNuTauEta[Category]->Fill(NuTauEta);

         HTauNuAngle[0]->Fill(TauNuAngle);
         HTauNuAngle[Category]->Fill(TauNuAngle);
         HTauNuDR[0]->Fill(TauNuDR);
         HTauNuDR[Category]->Fill(TauNuDR);
         HNuTauPTFraction[0]->Fill(NuTauPTFraction);
         HNuTauPTFraction[Category]->Fill(NuTauPTFraction);
         
         HTauNuAngleVsTauP[0]->Fill(TauNuAngle, TauP);
         HTauNuAngleVsTauP[Category]->Fill(TauNuAngle, TauP);
         HTauNuDRVsTauP[0]->Fill(TauNuDR, TauP);
         HTauNuDRVsTauP[Category]->Fill(TauNuDR, TauP);
         HNuTauPTFractionVsTauP[0]->Fill(NuTauPTFraction, TauP);
         HNuTauPTFractionVsTauP[Category]->Fill(NuTauPTFraction, TauP);
         
         HVisiblePT[0]->Fill(VisiblePT);
         HVisiblePT[Category]->Fill(VisiblePT);
         HVisiblePhi[0]->Fill(VisiblePhi);
         HVisiblePhi[Category]->Fill(VisiblePhi);
         HVisibleEta[0]->Fill(VisibleEta);
         HVisibleEta[Category]->Fill(VisibleEta);
         HVisibleMass[0]->Fill(VisibleMass);
         HVisibleMass[Category]->Fill(VisibleMass);

         HTauVisibleAngle[0]->Fill(TauVisibleAngle);
         HTauVisibleAngle[Category]->Fill(TauVisibleAngle);
         HTauVisibleDR[0]->Fill(TauVisibleDR);
         HTauVisibleDR[Category]->Fill(TauVisibleDR);
         HVisiblePTFraction[0]->Fill(VisiblePTFraction);
         HVisiblePTFraction[Category]->Fill(VisiblePTFraction);
         
         HTauVisibleAngleVsTauP[0]->Fill(TauVisibleAngle, TauP);
         HTauVisibleAngleVsTauP[Category]->Fill(TauVisibleAngle, TauP);
         HTauVisibleDRVsTauP[0]->Fill(TauVisibleDR, TauP);
         HTauVisibleDRVsTauP[Category]->Fill(TauVisibleDR, TauP);
         HVisiblePTFractionVsTauP[0]->Fill(VisiblePTFraction, TauP);
         HVisiblePTFractionVsTauP[Category]->Fill(VisiblePTFraction, TauP);
      }
   }

   in.close();

   for(int i = 0; i <= 8; i++)
   {
      PsFile.AddTextPage(string("Category: ") + CategoryString[i]);

      PsFile.AddPlot(HTauPT[i], "");
      PsFile.AddPlot(HTauPhi[i], "");
      PsFile.AddPlot(HTauEta[i], "");
      
      PsFile.AddPlot(HNuTauPT[i], "");
      PsFile.AddPlot(HNuTauPhi[i], "");
      PsFile.AddPlot(HNuTauEta[i], "");

      PsFile.AddPlot(HTauNuAngle[i], "");
      PsFile.AddPlot(HTauNuDR[i], "");
      PsFile.AddPlot(HNuTauPTFraction[i], "");

      PsFile.AddPlot(HTauNuAngleVsTauP[i], "colz");
      PsFile.AddPlot(HTauNuDRVsTauP[i], "colz");
      PsFile.AddPlot(HNuTauPTFractionVsTauP[i], "colz");
      
      PsFile.AddPlot(HVisiblePT[i], "");
      PsFile.AddPlot(HVisiblePhi[i], "");
      PsFile.AddPlot(HVisibleEta[i], "");
      PsFile.AddPlot(HVisibleMass[i], "");

      PsFile.AddPlot(HTauVisibleAngle[i], "");
      PsFile.AddPlot(HTauVisibleDR[i], "");
      PsFile.AddPlot(HVisiblePTFraction[i], "");

      PsFile.AddPlot(HTauVisibleAngleVsTauP[i], "colz");
      PsFile.AddPlot(HTauVisibleDRVsTauP[i], "colz");
      PsFile.AddPlot(HVisiblePTFractionVsTauP[i], "colz");
   }

   TCanvas CTauPT("CTauPT", "", 0, 0, 1024, 768);
   TCanvas CTauPhi("CTauPhi", "", 0, 0, 1024, 768);
   TCanvas CTauEta("CTauEta", "", 0, 0, 1024, 768);
   
   TCanvas CNuTauPT("CNuTauPT", "", 0, 0, 1024, 768);
   TCanvas CNuTauPhi("CNuTauPhi", "", 0, 0, 1024, 768);
   TCanvas CNuTauEta("CNuTauEta", "", 0, 0, 1024, 768);

   TCanvas CTauNuAngle("CTauNuAngle", "", 0, 0, 1024, 768);
   TCanvas CTauNuDR("CTauNuDR", "", 0, 0, 1024, 768);
   TCanvas CNuTauPTFraction("CNuTauPTFraction", "", 0, 0, 1024, 768);
   
   TCanvas CVisiblePT("CVisiblePT", "", 0, 0, 1024, 768);
   TCanvas CVisiblePhi("CVisiblePhi", "", 0, 0, 1024, 768);
   TCanvas CVisibleEta("CVisibleEta", "", 0, 0, 1024, 768);
   TCanvas CVisibleMass("CVisibleMass", "", 0, 0, 1024, 768);

   TCanvas CTauVisibleAngle("CTauVisibleAngle", "", 0, 0, 1024, 768);
   TCanvas CTauVisibleDR("CTauVisibleDR", "", 0, 0, 1024, 768);
   TCanvas CVisiblePTFraction("CVisiblePTFraction", "", 0, 0, 1024, 768);

   int Rebinning = 5;

   for(int i = 1; i <= 8; i++)
   {
      string Option = "";
      if(i != 1)
         Option = "same";

      CTauPT.cd();
      HTauPT[i]->Rebin(Rebinning);
      HTauPT[i]->SetStats(0);
      HTauPT[i]->SetLineColor(i + 1);
      HTauPT[i]->DrawNormalized(Option.c_str());

      CTauPhi.cd();
      HTauPhi[i]->Rebin(Rebinning);
      HTauPhi[i]->SetStats(0);
      HTauPhi[i]->SetLineColor(i + 1);
      HTauPhi[i]->DrawNormalized(Option.c_str());
      
      CTauEta.cd();
      HTauEta[i]->Rebin(Rebinning);
      HTauEta[i]->SetStats(0);
      HTauEta[i]->SetLineColor(i + 1);
      HTauEta[i]->DrawNormalized(Option.c_str());

      CNuTauPT.cd();
      HNuTauPT[i]->Rebin(Rebinning);
      HNuTauPT[i]->SetStats(0);
      HNuTauPT[i]->SetLineColor(i + 1);
      HNuTauPT[i]->DrawNormalized(Option.c_str());
      
      CNuTauPhi.cd();
      HNuTauPhi[i]->Rebin(Rebinning);
      HNuTauPhi[i]->SetStats(0);
      HNuTauPhi[i]->SetLineColor(i + 1);
      HNuTauPhi[i]->DrawNormalized(Option.c_str());
      
      CNuTauEta.cd();
      HNuTauEta[i]->Rebin(Rebinning);
      HNuTauEta[i]->SetStats(0);
      HNuTauEta[i]->SetLineColor(i + 1);
      HNuTauEta[i]->DrawNormalized(Option.c_str());

      CTauNuAngle.cd();
      HTauNuAngle[i]->Rebin(Rebinning);
      HTauNuAngle[i]->SetStats(0);
      HTauNuAngle[i]->SetLineColor(i + 1);
      HTauNuAngle[i]->DrawNormalized(Option.c_str());
      
      CTauNuDR.cd();
      HTauNuDR[i]->Rebin(Rebinning);
      HTauNuDR[i]->SetStats(0);
      HTauNuDR[i]->SetLineColor(i + 1);
      HTauNuDR[i]->DrawNormalized(Option.c_str());
      
      CNuTauPTFraction.cd();
      HNuTauPTFraction[i]->Rebin(Rebinning);
      HNuTauPTFraction[i]->SetStats(0);
      HNuTauPTFraction[i]->SetLineColor(i + 1);
      HNuTauPTFraction[i]->DrawNormalized(Option.c_str());

      CVisiblePT.cd();
      HVisiblePT[i]->Rebin(Rebinning);
      HVisiblePT[i]->SetStats(0);
      HVisiblePT[i]->SetLineColor(i + 1);
      HVisiblePT[i]->DrawNormalized(Option.c_str());
      
      CVisiblePhi.cd();
      HVisiblePhi[i]->Rebin(Rebinning);
      HVisiblePhi[i]->SetStats(0);
      HVisiblePhi[i]->SetLineColor(i + 1);
      HVisiblePhi[i]->DrawNormalized(Option.c_str());
      
      CVisibleEta.cd();
      HVisibleEta[i]->Rebin(Rebinning);
      HVisibleEta[i]->SetStats(0);
      HVisibleEta[i]->SetLineColor(i + 1);
      HVisibleEta[i]->DrawNormalized(Option.c_str());

      CVisibleMass.cd();
      HVisibleMass[i]->Rebin(Rebinning);
      HVisibleMass[i]->SetStats(0);
      HVisibleMass[i]->SetLineColor(i + 1);
      HVisibleMass[i]->DrawNormalized(Option.c_str());

      CTauVisibleAngle.cd();
      HTauVisibleAngle[i]->Rebin(Rebinning);
      HTauVisibleAngle[i]->SetStats(0);
      HTauVisibleAngle[i]->SetLineColor(i + 1);
      HTauVisibleAngle[i]->DrawNormalized(Option.c_str());
      
      CTauVisibleDR.cd();
      HTauVisibleDR[i]->Rebin(Rebinning);
      HTauVisibleDR[i]->SetStats(0);
      HTauVisibleDR[i]->SetLineColor(i + 1);
      HTauVisibleDR[i]->DrawNormalized(Option.c_str());
      
      CVisiblePTFraction.cd();
      HVisiblePTFraction[i]->Rebin(Rebinning);
      HVisiblePTFraction[i]->SetStats(0);
      HVisiblePTFraction[i]->SetLineColor(i + 1);
      HVisiblePTFraction[i]->DrawNormalized(Option.c_str());
   }
  
   TLegend legend(0.65, 0.95, 0.95, 0.75);
   legend.SetFillColor(0);
   for(int i = 1; i <= 8; i++)
      legend.AddEntry(HTauPT[i], CategoryString[i].c_str(), "l");

   CTauPT.cd();   legend.Draw();
   CTauPhi.cd();   legend.Draw();
   CTauEta.cd();   legend.Draw();
   CNuTauPT.cd();   legend.Draw();
   CNuTauPhi.cd();   legend.Draw();
   CNuTauEta.cd();   legend.Draw();
   CTauNuAngle.cd();   legend.Draw();
   CTauNuDR.cd();   legend.Draw();
   CNuTauPTFraction.cd();   legend.Draw();
   CVisiblePT.cd();   legend.Draw();
   CVisiblePhi.cd();   legend.Draw();
   CVisibleEta.cd();   legend.Draw();
   CVisibleMass.cd();   legend.Draw();
   CTauVisibleAngle.cd();   legend.Draw();
   CTauVisibleDR.cd();   legend.Draw();
   CVisiblePTFraction.cd();   legend.Draw();

   PsFile.AddTextPage("Comparison between different categories");

   PsFile.AddCanvas(CTauPT);
   PsFile.AddCanvas(CTauPhi);
   PsFile.AddCanvas(CTauEta);

   PsFile.AddCanvas(CNuTauPT);
   PsFile.AddCanvas(CNuTauPhi);
   PsFile.AddCanvas(CNuTauEta);

   PsFile.AddCanvas(CTauNuAngle);
   PsFile.AddCanvas(CTauNuDR);
   PsFile.AddCanvas(CNuTauPTFraction);

   PsFile.AddCanvas(CVisiblePT);
   PsFile.AddCanvas(CVisiblePhi);
   PsFile.AddCanvas(CVisibleEta);
   PsFile.AddCanvas(CVisibleMass);

   PsFile.AddCanvas(CTauVisibleAngle);
   PsFile.AddCanvas(CTauVisibleDR);
   PsFile.AddCanvas(CVisiblePTFraction);

   for(int i = 0; i <= 8; i++)
   {
      delete HTauPT[i];
      delete HTauPhi[i];
      delete HTauEta[i];
      
      delete HNuTauPT[i];
      delete HNuTauPhi[i];
      delete HNuTauEta[i];

      delete HTauNuAngle[i];
      delete HTauNuDR[i];
      delete HNuTauPTFraction[i];
      
      delete HTauNuAngleVsTauP[i];
      delete HTauNuDRVsTauP[i];
      delete HNuTauPTFractionVsTauP[i];
      
      delete HVisiblePT[i];
      delete HVisiblePhi[i];
      delete HVisibleEta[i];
      delete HVisibleMass[i];

      delete HTauVisibleAngle[i];
      delete HTauVisibleDR[i];
      delete HVisiblePTFraction[i];
      
      delete HTauVisibleAngleVsTauP[i];
      delete HTauVisibleDRVsTauP[i];
      delete HVisiblePTFractionVsTauP[i];
   }
      
   PsFile.AddTimeStampPage();
   PsFile.Close();
}

bool HasTau(GenParticleTree &Tree)
{
   for(int i = 0; i < Tree.ParticleCount(); i++)
      if(Tree[i].PDGID == 15)
         return true;

   return false;
}

int FindCategory(GenParticleTree &Tree, int index)
{
   vector<int> Daughters = Tree[index].Daughters;

   int PiZeroCount = 0;
   int PiPlusCount = 0;
   int PiMinusCount = 0;

   for(int i = 0; i < (int)Daughters.size(); i++)
   {
      if(Tree[Daughters[i]].PDGID == 13 || Tree[Daughters[i]].PDGID == -13)   // detect muon
         return 1;
      if(Tree[Daughters[i]].PDGID == 11 || Tree[Daughters[i]].PDGID == -11)   // detect electron
         return 2;
      if(Tree[Daughters[i]].PDGID == 15 || Tree[Daughters[i]].PDGID == -15)   // detect tau
         return -1;

      if(Tree[Daughters[i]].PDGID == 111)   // pi0
         PiZeroCount = PiZeroCount + 1;
      if(Tree[Daughters[i]].PDGID == 211)   // pi+
         PiPlusCount = PiPlusCount + 1;
      if(Tree[Daughters[i]].PDGID == -211)   // pi-
         PiMinusCount = PiMinusCount + 1;

      // rho, omega => look at their decays
      if(Tree[Daughters[i]].PDGID == 223 || Tree[Daughters[i]].PDGID == 213
         || Tree[Daughters[i]].PDGID == 113 || Tree[Daughters[i]].PDGID == -213)
      {
         vector<int> DaughterList = Tree[Daughters[i]].Daughters;

         for(int j = 0; j < (int)DaughterList.size(); j++)
         {
            if(Tree[DaughterList[j]].PDGID == 111)   // pi0
               PiZeroCount = PiZeroCount + 1;
            if(Tree[DaughterList[j]].PDGID == 211)   // pi+
               PiPlusCount = PiPlusCount + 1;
            if(Tree[DaughterList[j]].PDGID == -211)   // pi-
               PiMinusCount = PiMinusCount + 1;
         }
      }
   }

   if(PiMinusCount == 1 && PiZeroCount == 0 && PiPlusCount == 0)
      return 3;
   if(PiMinusCount == 1 && PiZeroCount == 1 && PiPlusCount == 0)
      return 4;
   if(PiMinusCount == 1 && PiZeroCount == 2 && PiPlusCount == 0)
      return 5;
   if(PiMinusCount == 2 && PiZeroCount == 0 && PiPlusCount == 1)
      return 6;
   if(PiMinusCount == 2 && PiZeroCount == 1 && PiPlusCount == 1)
      return 7;

   return 8;
}

double GetMass(double P[4])
{
   return sqrt(P[0] * P[0] - P[1] * P[1] - P[2] * P[2] - P[3] * P[3]);
}

double GetP(double P[4])
{
   return sqrt(P[1] * P[1] + P[2] * P[2] + P[3] * P[3]);
}

double GetPT(double P[4])
{
   return sqrt(P[1] * P[1] + P[2] * P[2]);
}

double GetEta(double P[4])
{
   double Momentum = GetP(P);

   return 0.5 * log((Momentum - P[3]) / (Momentum + P[3]));
}

double GetPhi(double P[4])
{
   double PT = GetPT(P);

   double Angle = acos(P[1] / PT);
   if(P[2] < 0)
      Angle = -Angle;

   return Angle;
}

double GetAngle(double P1[4], double P2[4])
{
   return acos((P1[1] * P2[1] + P1[2] * P2[2] + P1[3] * P2[3]) / GetP(P1) / GetP(P2));
}

double GetDR(double P1[4], double P2[4])
{
   double DEta = GetEta(P1) - GetEta(P2);
   double DPhi = GetPhi(P1) - GetPhi(P2);

   if(DPhi > PI)
      DPhi = 2 * PI - DPhi;
   if(DPhi < -PI)
      DPhi = DPhi + 2 * PI;

   return sqrt(DPhi * DPhi + DEta * DEta);
}



