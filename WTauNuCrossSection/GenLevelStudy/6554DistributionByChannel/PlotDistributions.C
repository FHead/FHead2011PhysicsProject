#include <fstream>
#include <vector>
#include <sstream>
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
double GetDPhi(double P1[4], double P2[4]);
double GetDR(double P1[4], double P2[4]);
double GetMT(double P1[4], double P2[4]);
double GetMinRadius(double P1[4], double P2[4], double P3[4]);   // in eta-phi space
double GetMinRadius(double X1, double Y1, double X2, double Y2, double X3, double Y3);

void PlotDistributions()
{
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

   PsFileHelper *PsFile[9];
   for(int i = 0; i <= 8; i++)
   {
      stringstream str;
      str << "ChannelDistributions" << i << ".ps";
      PsFile[i] = new PsFileHelper(str.str());

      PsFile[i]->AddTextPage("Channel-by-channel distribution comparison (" + CategoryString[i] + ")");
   }

   PsFileHelper PsFileSummary("ComparisonChannelDistributions.ps");
   PsFileSummary.AddTextPage("Channel-by-channel distribution comparison");

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
   vector<TH1D *> HInvisiblePTFromW;
   vector<TH1D *> HInvisiblePhiFromW;
   vector<TH1D *> HInvisibleEtaFromW;
   vector<TH1D *> HTauNuMT;
   vector<TH1D *> HVisibleInvisibleAngle;
   vector<TH1D *> HVisibleInvisibleDPhi;
   vector<TH1D *> HVisibleInvisibleMT;
   vector<TH1D *> HThreeProngSpread;
   vector<TH2D *> HThreeProngSpreadVsPT;
   vector<TH1D *> HIsolation03;   // Excluding self - cone of 0.3 around visible center
   vector<TH1D *> HIsolation04;
   vector<TH1D *> HIsolation05;
   vector<TH1D *> HRelativeIsolation03;
   vector<TH1D *> HRelativeIsolation04;
   vector<TH1D *> HRelativeIsolation05;
   vector<TH1D *> HPiZeroPT;
   vector<TH1D *> HPiChargedPT;
   vector<TH1D *> HPiZeroPTFraction;   // with respect to all visible parts
   vector<TH1D *> HPiChargedPTFraction;

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

      HInvisiblePTFromW.push_back(new TH1D(Form("HInvisiblePTFromW_%d", i),
         Form("Invisible (from W) PT distribution for category %d", i), 100, 0, 100));
      HInvisiblePhiFromW.push_back(new TH1D(Form("HInvisiblePhiFromW_%d", i),
         Form("Invisible (from W) phi distribution for category %d", i), 100, -3.2, 3.2));
      HInvisibleEtaFromW.push_back(new TH1D(Form("HInvisibleEtaFromW_%d", i),
         Form("Invisible (from W) Eta distribution for category %d", i), 100, -5, 5));

      HTauNuMT.push_back(new TH1D(Form("HTauNuMT_%d", i),
         Form("MT distribution of W, category %d", i), 100, 0, 100));
      HVisibleInvisibleAngle.push_back(new TH1D(Form("HVisibleInvisibleAngle_%d", i),
         Form("angle between visible and invisible parts of W decay, category %d", i), 100, 0, 3.2));
      HVisibleInvisibleDPhi.push_back(new TH1D(Form("HVisibleInvisibleDPhi_%d", i),
         Form("Delta phi between visible and invisible parts of W decay, category %d", i), 100, -3.2, 3.2));
      HVisibleInvisibleMT.push_back(new TH1D(Form("HVisibleInvisibleMT_%d", i),
         Form("MT formed from visible and invisible parts of W decay, category %d", i), 100, 0, 100));

      HThreeProngSpread.push_back(new TH1D(Form("HThreeProngSpread_%d", i),
         Form("Spread (in eta-phi) of the only three charged pions (category %d)", i), 100, 0, 0.25));
      HThreeProngSpreadVsPT.push_back(new TH2D(Form("HThreeProngSpreadVsPT_%d", i),
         Form("Spread (in eta-phi) of the only three charged pions (category %d) vs. PT;Spread;PT", i),
         100, 0, 0.25, 100, 0, 100));

      HIsolation03.push_back(new TH1D(Form("HIsolation03_%d", i),
         Form("Isolation (excluding self) around visible center, dR 0.3, category %d", i), 100, 0, 30));
      HIsolation04.push_back(new TH1D(Form("HIsolation04_%d", i),
         Form("Isolation (excluding self) around visible center, dR 0.4, category %d", i), 100, 0, 30));
      HIsolation05.push_back(new TH1D(Form("HIsolation05_%d", i),
         Form("Isolation (excluding self) around visible center, dR 0.5, category %d", i), 100, 0, 30));
      
      HRelativeIsolation03.push_back(new TH1D(Form("HRelativeIsolation03_%d", i),
         Form("Relative isolation (excluding self) around visible center, dR 0.3, category %d", i), 100, 0, 1));
      HRelativeIsolation04.push_back(new TH1D(Form("HRelativeIsolation04_%d", i),
         Form("Relative isolation (excluding self) around visible center, dR 0.4, category %d", i), 100, 0, 1));
      HRelativeIsolation05.push_back(new TH1D(Form("HRelativeIsolation05_%d", i),
         Form("Relative isolation (excluding self) around visible center, dR 0.5, category %d", i), 100, 0, 1));

      HPiZeroPT.push_back(new TH1D(Form("HPiZeroPT_%d", i),
         Form("Pi0 total PT spectrum, category %d", i), 100, 0, 100));
      HPiChargedPT.push_back(new TH1D(Form("HPiChargedPT_%d", i),
         Form("Pi+ Pi- total PT spectrum, category %d", i), 100, 0, 100));
      HPiZeroPTFraction.push_back(new TH1D(Form("HPiZeroPTFraction_%d", i),
         Form("Pi0 PT fraction, category %d", i), 100, 0, 1.2));
      HPiChargedPTFraction.push_back(new TH1D(Form("HPiChargedPTFraction_%d", i),
         Form("Pi+ Pi- PT fraction, category %d", i), 100, 0, 1.2));
   }

   ifstream in("Samples/6554TauEnrichedWSample");
   
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

      int Category = -1;

      int TauIndex = -1;
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].PDGID != 15)
            continue;

         Category = FindCategory(Tree, j);
         if(Category > 0)
         {
            TauIndex = j;
            break;
         }
      }

      if(TauIndex < 0)
         continue;

      int WIndex = -1;   // W-: -24
      for(int j = 0; j < Tree.ParticleCount(); j++)
      {
         if(Tree[j].PDGID != -24)
            continue;
         
         bool ExistTauDaughter = false;
         for(int k = 0; k < (int)Tree[j].Daughters.size(); k++)
            if(Tree[Tree[j].Daughters[k]].PDGID == 15)
               ExistTauDaughter = true;

         if(ExistTauDaughter == true)
         {
            WIndex = j;
            break;
         }
      }

      if(WIndex < 0)
         continue;

      vector<int> WDaughters = Tree[WIndex].Daughters;
      int NuTauFromW = -1;
      for(int k = 0; k < (int)WDaughters.size(); k++)
         if(Tree[WDaughters[k]].PDGID == -16)
            NuTauFromW = WDaughters[k];

      if(NuTauFromW < 0)
         continue;

      vector<int> Daughters = Tree[TauIndex].Daughters;
      for(int k = 0; k < (int)Daughters.size(); k++)
      {
         // if(Tree[Daughters[k]].PDGID == 213 || Tree[Daughters[k]].PDGID == 223
         //       || Tree[Daughters[k]].PDGID == -213 || Tree[Daughters[k]].PDGID == 113)
         if(Tree[Daughters[k]].StatusCode != 1 && Tree[Daughters[k]].PDGID != 111)
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

      double InvisiblePFromW[4] = {0};
      InvisiblePFromW[0] = Tree[NuTauFromW].P[0];
      InvisiblePFromW[1] = Tree[NuTauFromW].P[1];
      InvisiblePFromW[2] = Tree[NuTauFromW].P[2];
      InvisiblePFromW[3] = Tree[NuTauFromW].P[3];

      for(int k = 0; k < (int)Daughters.size(); k++)
      {
         if(Tree[Daughters[k]].PDGID == 12 || Tree[Daughters[k]].PDGID == -12
            || Tree[Daughters[k]].PDGID == 14 || Tree[Daughters[k]].PDGID == -14
            || Tree[Daughters[k]].PDGID == 16 || Tree[Daughters[k]].PDGID == -16)
         {
            InvisiblePFromW[0] = InvisiblePFromW[0] + Tree[Daughters[k]].P[0];
            InvisiblePFromW[1] = InvisiblePFromW[1] + Tree[Daughters[k]].P[1];
            InvisiblePFromW[2] = InvisiblePFromW[2] + Tree[Daughters[k]].P[2];
            InvisiblePFromW[3] = InvisiblePFromW[3] + Tree[Daughters[k]].P[3];
         }
      }

      vector<int> ChargedPionDaughters;
      for(int k = 0; k < (int)Daughters.size(); k++)
         if(Tree[Daughters[k]].PDGID == 211 || Tree[Daughters[k]].PDGID == -211)
            ChargedPionDaughters.push_back(Daughters[k]);

      double VisibleSumPT = 0;
      double Isolation03 = 0;
      double Isolation04 = 0;
      double Isolation05 = 0;
      
      for(int k = 0; k < (int)Daughters.size(); k++)
      {
         if(Tree[Daughters[k]].PDGID == 12 || Tree[Daughters[k]].PDGID == -12)
            continue;
         if(Tree[Daughters[k]].PDGID == 14 || Tree[Daughters[k]].PDGID == -14)
            continue;
         if(Tree[Daughters[k]].PDGID == 16 || Tree[Daughters[k]].PDGID == -16)
            continue;

         VisibleSumPT = VisibleSumPT + GetPT(Tree[Daughters[k]].P);
      }

      for(int k = 0; k < Tree.ParticleCount(); k++)
      {
         // final particles and not neutrinos
         if(Tree[k].PDGID == 12 || Tree[k].PDGID == -12)
            continue;
         if(Tree[k].PDGID == 14 || Tree[k].PDGID == -14)
            continue;
         if(Tree[k].PDGID == 16 || Tree[k].PDGID == -16)
            continue;

         if(Tree[k].Daughters.size() > 0)   // has children: not final
            continue;
         if(Tree[k].StatusCode != 1)   // not final (?)
            continue;

         double DR = GetDR(VisibleP, Tree[k].P);

         if(DR < 0.3)
            Isolation03 = Isolation03 + GetPT(Tree[k].P);
         if(DR < 0.4)
            Isolation04 = Isolation04 + GetPT(Tree[k].P);
         if(DR < 0.5)
            Isolation05 = Isolation05 + GetPT(Tree[k].P);
      }

      Isolation03 = Isolation03 - VisibleSumPT;
      Isolation04 = Isolation04 - VisibleSumPT;
      Isolation05 = Isolation05 - VisibleSumPT;

      double PiZeroSumPT = 0;
      double PiChargedSumPT = 0;
      for(int j = 0; j < (int)Daughters.size(); j++)
      {
         if(Tree[Daughters[j]].PDGID == 111)   // pizero!
            PiZeroSumPT = PiZeroSumPT + GetPT(Tree[Daughters[j]].P);
         if(Tree[Daughters[j]].PDGID == 211 || Tree[Daughters[j]].PDGID == -211)   // pi+/pi-
            PiChargedSumPT = PiChargedSumPT + GetPT(Tree[Daughters[j]].P);
      }

      double TauP = GetP(Tree[TauIndex].P);
      double TauPT = GetPT(Tree[TauIndex].P);
      double TauPhi = GetPhi(Tree[TauIndex].P);
      double TauEta = GetEta(Tree[TauIndex].P);

      double NuTauPT = GetPT(Tree[NuTauIndex].P);
      double NuTauPhi = GetPhi(Tree[NuTauIndex].P);
      double NuTauEta = GetEta(Tree[NuTauIndex].P);

      double TauNuAngle = GetAngle(Tree[TauIndex].P, Tree[NuTauIndex].P);
      double TauNuDR = GetDR(Tree[TauIndex].P, Tree[NuTauIndex].P);
      double NuTauPTFraction = NuTauPT / TauPT;

      double VisiblePT = GetPT(VisibleP);
      double VisiblePhi = GetPhi(VisibleP);
      double VisibleEta = GetEta(VisibleP);
      double VisibleMass = GetMass(VisibleP);

      double TauVisibleAngle = GetAngle(Tree[TauIndex].P, VisibleP);
      double TauVisibleDR = GetDR(Tree[TauIndex].P, VisibleP);
      double VisiblePTFraction = VisiblePT / TauPT;

      double InvisiblePTFromW = GetPT(InvisiblePFromW);
      double InvisiblePhiFromW = GetPhi(InvisiblePFromW);
      double InvisibleEtaFromW = GetEta(InvisiblePFromW);

      double TauNuMT = GetMT(Tree[TauIndex].P, Tree[NuTauFromW].P);
      double VisibleInvisibleAngle = GetAngle(VisibleP, InvisiblePFromW);
      double VisibleInvisibleDPhi = GetDPhi(VisibleP, InvisiblePFromW);
      double VisibleInvisibleMT = GetMT(VisibleP, InvisiblePFromW);

      /*
      if(Category == 6)
      {
         cout << "Visible: " << VisibleP[0] << " " << VisibleP[1] << " "
            << VisibleP[2] << " " << VisibleP[3] << endl;
         cout << "Invisible (From W): " << InvisiblePFromW[0] << " " << InvisiblePFromW[1] << " "
            << InvisiblePFromW[2] << " " << InvisiblePFromW[3] << endl;
         cout << "Angle: " << VisibleInvisibleAngle << endl;
      }
      */
      
      double ThreeProngSpread = 0;
      double PiPiPiP[4] = {0};
      if(ChargedPionDaughters.size() == 3)
      {
         ThreeProngSpread = GetMinRadius(Tree[ChargedPionDaughters[0]].P,
            Tree[ChargedPionDaughters[1]].P,
            Tree[ChargedPionDaughters[2]].P);
         PiPiPiP[0] = Tree[ChargedPionDaughters[0]].P[0]
            + Tree[ChargedPionDaughters[1]].P[0]
            + Tree[ChargedPionDaughters[2]].P[0];
         PiPiPiP[1] = Tree[ChargedPionDaughters[0]].P[1]
            + Tree[ChargedPionDaughters[1]].P[1]
            + Tree[ChargedPionDaughters[2]].P[1];
         PiPiPiP[2] = Tree[ChargedPionDaughters[0]].P[2]
            + Tree[ChargedPionDaughters[1]].P[2]
            + Tree[ChargedPionDaughters[2]].P[2];
         PiPiPiP[3] = Tree[ChargedPionDaughters[0]].P[3]
            + Tree[ChargedPionDaughters[1]].P[3]
            + Tree[ChargedPionDaughters[2]].P[3];
      }

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

      HInvisiblePTFromW[0]->Fill(InvisiblePTFromW);
      HInvisiblePTFromW[Category]->Fill(InvisiblePTFromW);
      HInvisiblePhiFromW[0]->Fill(InvisiblePhiFromW);
      HInvisiblePhiFromW[Category]->Fill(InvisiblePhiFromW);
      HInvisibleEtaFromW[0]->Fill(InvisibleEtaFromW);
      HInvisibleEtaFromW[Category]->Fill(InvisibleEtaFromW);

      HTauNuMT[0]->Fill(TauNuMT);
      HTauNuMT[Category]->Fill(TauNuMT);
      HVisibleInvisibleAngle[0]->Fill(VisibleInvisibleAngle);
      HVisibleInvisibleAngle[Category]->Fill(VisibleInvisibleAngle);
      HVisibleInvisibleDPhi[0]->Fill(VisibleInvisibleDPhi);
      HVisibleInvisibleDPhi[Category]->Fill(VisibleInvisibleDPhi);
      HVisibleInvisibleMT[0]->Fill(VisibleInvisibleMT);
      HVisibleInvisibleMT[Category]->Fill(VisibleInvisibleMT);
      
      HThreeProngSpread[0]->Fill(ThreeProngSpread);
      HThreeProngSpread[Category]->Fill(ThreeProngSpread);
      HThreeProngSpreadVsPT[0]->Fill(ThreeProngSpread, GetPT(PiPiPiP));
      HThreeProngSpreadVsPT[Category]->Fill(ThreeProngSpread, GetPT(PiPiPiP));

      HIsolation03[0]->Fill(Isolation03);
      HIsolation03[Category]->Fill(Isolation03);
      HIsolation04[0]->Fill(Isolation04);
      HIsolation04[Category]->Fill(Isolation04);
      HIsolation05[0]->Fill(Isolation05);
      HIsolation05[Category]->Fill(Isolation05);
      
      HRelativeIsolation03[0]->Fill(Isolation03 / VisibleSumPT);
      HRelativeIsolation03[Category]->Fill(Isolation03 / VisibleSumPT);
      HRelativeIsolation04[0]->Fill(Isolation04 / VisibleSumPT);
      HRelativeIsolation04[Category]->Fill(Isolation04 / VisibleSumPT);
      HRelativeIsolation05[0]->Fill(Isolation05 / VisibleSumPT);
      HRelativeIsolation05[Category]->Fill(Isolation05 / VisibleSumPT);

      HPiZeroPT[0]->Fill(PiZeroSumPT);
      HPiZeroPT[Category]->Fill(PiZeroSumPT);
      HPiChargedPT[0]->Fill(PiChargedSumPT);
      HPiChargedPT[Category]->Fill(PiChargedSumPT);
      HPiZeroPTFraction[0]->Fill(PiZeroSumPT / VisibleSumPT);
      HPiZeroPTFraction[Category]->Fill(PiZeroSumPT / VisibleSumPT);
      HPiChargedPTFraction[0]->Fill(PiChargedSumPT / VisibleSumPT);
      HPiChargedPTFraction[Category]->Fill(PiChargedSumPT / VisibleSumPT);
   }

   in.close();

   for(int i = 0; i <= 8; i++)
   {
      PsFile[i]->AddPlot(HTauPT[i], "");
      // PsFile[i]->AddPlot(HTauPhi[i], "");
      PsFile[i]->AddPlot(HTauEta[i], "");

      PsFile[i]->AddPlot(HNuTauPT[i], "");
      // PsFile[i]->AddPlot(HNuTauPhi[i], "");
      PsFile[i]->AddPlot(HNuTauEta[i], "");

      PsFile[i]->AddPlot(HTauNuAngle[i], "");
      PsFile[i]->AddPlot(HTauNuDR[i], "");
      PsFile[i]->AddPlot(HNuTauPTFraction[i], "");

      PsFile[i]->AddPlot(HTauNuAngleVsTauP[i], "colz");
      PsFile[i]->AddPlot(HTauNuDRVsTauP[i], "colz");
      PsFile[i]->AddPlot(HNuTauPTFractionVsTauP[i], "colz");

      PsFile[i]->AddPlot(HVisiblePT[i], "");
      // PsFile[i]->AddPlot(HVisiblePhi[i], "");
      PsFile[i]->AddPlot(HVisibleEta[i], "");
      PsFile[i]->AddPlot(HVisibleMass[i], "");

      PsFile[i]->AddPlot(HTauVisibleAngle[i], "");
      PsFile[i]->AddPlot(HTauVisibleDR[i], "");
      PsFile[i]->AddPlot(HVisiblePTFraction[i], "");

      PsFile[i]->AddPlot(HTauVisibleAngleVsTauP[i], "colz");
      PsFile[i]->AddPlot(HTauVisibleDRVsTauP[i], "colz");
      PsFile[i]->AddPlot(HVisiblePTFractionVsTauP[i], "colz");

      PsFile[i]->AddPlot(HInvisiblePTFromW[i], "");
      PsFile[i]->AddPlot(HInvisibleEtaFromW[i], "");
      // PsFile[i]->AddPlot(HInvisiblePhiFromW[i], "");

      PsFile[i]->AddPlot(HTauNuMT[i], "");
      PsFile[i]->AddPlot(HVisibleInvisibleAngle[i], "");
      PsFile[i]->AddPlot(HVisibleInvisibleDPhi[i], "");
      PsFile[i]->AddPlot(HVisibleInvisibleMT[i], "");

      PsFile[i]->AddPlot(HThreeProngSpread[i], "", true);
      PsFile[i]->AddPlot(HThreeProngSpreadVsPT[i], "colz", false, true);

      PsFile[i]->AddPlot(HIsolation03[i], "", true);
      PsFile[i]->AddPlot(HIsolation04[i], "", true);
      PsFile[i]->AddPlot(HIsolation05[i], "", true);
      
      PsFile[i]->AddPlot(HRelativeIsolation03[i], "", true);
      PsFile[i]->AddPlot(HRelativeIsolation04[i], "", true);
      PsFile[i]->AddPlot(HRelativeIsolation05[i], "", true);

      PsFile[i]->AddPlot(HPiZeroPT[i], "", false);
      PsFile[i]->AddPlot(HPiChargedPT[i], "", false);
      PsFile[i]->AddPlot(HPiZeroPTFraction[i], "", false);
      PsFile[i]->AddPlot(HPiChargedPTFraction[i], "", false);
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

   TCanvas CInvisiblePTFromW("CInvisiblePTFromW", "", 0, 0, 1024, 768);
   TCanvas CInvisiblePhiFromW("CInvisiblePhiFromW", "", 0, 0, 1024, 768);
   TCanvas CInvisibleEtaFromW("CInvisibleEtaFromW", "", 0, 0, 1024, 768);

   TCanvas CTauNuMT("CTauNuMT", "", 0, 0, 1024, 768);
   TCanvas CVisibleInvisibleAngle("CVisibleInvisibleAngle", "", 0, 0, 1024, 768);
   TCanvas CVisibleInvisibleDPhi("CVisibleInvisibleDPhi", "", 0, 0, 1024, 768);
   TCanvas CVisibleInvisibleMT("CVisibleInvisibleMT", "", 0, 0, 1024, 768);

   TCanvas CThreeProngSpread("CThreeProngSpread", "", 0, 0, 1024, 768);

   TCanvas CIsolation03("CIsolation03", "", 0, 0, 1024, 768);
   TCanvas CIsolation04("CIsolation04", "", 0, 0, 1024, 768);
   TCanvas CIsolation05("CIsolation05", "", 0, 0, 1024, 768);
   
   TCanvas CRelativeIsolation03("CRelativeIsolation03", "", 0, 0, 1024, 768);
   TCanvas CRelativeIsolation04("CRelativeIsolation04", "", 0, 0, 1024, 768);
   TCanvas CRelativeIsolation05("CRelativeIsolation05", "", 0, 0, 1024, 768);

   TCanvas CPiZeroPT("CPiZeroPT", "", 0, 0, 1024, 768);
   TCanvas CPiChargedPT("CPiChargedPT", "", 0, 0, 1024, 768);
   TCanvas CPiZeroPTFraction("CPiZeroPTFraction", "", 0, 0, 1024, 768);
   TCanvas CPiChargedPTFraction("CPiChargedPTFraction", "", 0, 0, 1024, 768);

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

      CInvisiblePTFromW.cd();
      HInvisiblePTFromW[i]->Rebin(Rebinning);
      HInvisiblePTFromW[i]->SetStats();
      HInvisiblePTFromW[i]->SetLineColor(i + 1);
      HInvisiblePTFromW[i]->DrawNormalized(Option.c_str());

      CInvisiblePhiFromW.cd();
      HInvisiblePhiFromW[i]->Rebin(Rebinning);
      HInvisiblePhiFromW[i]->SetStats();
      HInvisiblePhiFromW[i]->SetLineColor(i + 1);
      HInvisiblePhiFromW[i]->DrawNormalized(Option.c_str());

      CInvisibleEtaFromW.cd();
      HInvisibleEtaFromW[i]->Rebin(Rebinning);
      HInvisibleEtaFromW[i]->SetStats();
      HInvisibleEtaFromW[i]->SetLineColor(i + 1);
      HInvisibleEtaFromW[i]->DrawNormalized(Option.c_str());

      CTauNuMT.cd();
      HTauNuMT[i]->Rebin(Rebinning);
      HTauNuMT[i]->SetStats();
      HTauNuMT[i]->SetLineColor(i + 1);
      HTauNuMT[i]->DrawNormalized(Option.c_str());

      CVisibleInvisibleAngle.cd();
      HVisibleInvisibleAngle[i]->Rebin(Rebinning);
      HVisibleInvisibleAngle[i]->SetStats();
      HVisibleInvisibleAngle[i]->SetLineColor(i + 1);
      HVisibleInvisibleAngle[i]->DrawNormalized(Option.c_str());
      
      CVisibleInvisibleDPhi.cd();
      HVisibleInvisibleDPhi[i]->Rebin(Rebinning);
      HVisibleInvisibleDPhi[i]->SetStats();
      HVisibleInvisibleDPhi[i]->SetLineColor(i + 1);
      HVisibleInvisibleDPhi[i]->DrawNormalized(Option.c_str());
      
      CVisibleInvisibleMT.cd();
      HVisibleInvisibleMT[i]->Rebin(Rebinning);
      HVisibleInvisibleMT[i]->SetStats();
      HVisibleInvisibleMT[i]->SetLineColor(i + 1);
      HVisibleInvisibleMT[i]->DrawNormalized(Option.c_str());
      
      CThreeProngSpread.cd();
      HThreeProngSpread[i]->Rebin(Rebinning);
      HThreeProngSpread[i]->SetStats();
      HThreeProngSpread[i]->SetLineColor(i + 1);
      HThreeProngSpread[i]->DrawNormalized(Option.c_str());
      
      CIsolation03.cd();
      HIsolation03[i]->Rebin(Rebinning);
      HIsolation03[i]->SetStats();
      HIsolation03[i]->SetLineColor(i + 1);
      HIsolation03[i]->DrawNormalized(Option.c_str());
      
      CIsolation04.cd();
      HIsolation04[i]->Rebin(Rebinning);
      HIsolation04[i]->SetStats();
      HIsolation04[i]->SetLineColor(i + 1);
      HIsolation04[i]->DrawNormalized(Option.c_str());

      CIsolation05.cd();
      HIsolation05[i]->Rebin(Rebinning);
      HIsolation05[i]->SetStats();
      HIsolation05[i]->SetLineColor(i + 1);
      HIsolation05[i]->DrawNormalized(Option.c_str());
      
      CRelativeIsolation03.cd();
      HRelativeIsolation03[i]->Rebin(Rebinning);
      HRelativeIsolation03[i]->SetStats();
      HRelativeIsolation03[i]->SetLineColor(i + 1);
      HRelativeIsolation03[i]->DrawNormalized(Option.c_str());
      
      CRelativeIsolation04.cd();
      HRelativeIsolation04[i]->Rebin(Rebinning);
      HRelativeIsolation04[i]->SetStats();
      HRelativeIsolation04[i]->SetLineColor(i + 1);
      HRelativeIsolation04[i]->DrawNormalized(Option.c_str());
      
      CRelativeIsolation05.cd();
      HRelativeIsolation05[i]->Rebin(Rebinning);
      HRelativeIsolation05[i]->SetStats();
      HRelativeIsolation05[i]->SetLineColor(i + 1);
      HRelativeIsolation05[i]->DrawNormalized(Option.c_str());
      
      CPiZeroPT.cd();
      HPiZeroPT[i]->Rebin(Rebinning);
      HPiZeroPT[i]->SetStats(0);
      HPiZeroPT[i]->SetLineColor(i + 1);
      HPiZeroPT[i]->DrawNormalized(Option.c_str());
      
      CPiChargedPT.cd();
      HPiChargedPT[i]->Rebin(Rebinning);
      HPiChargedPT[i]->SetStats(0);
      HPiChargedPT[i]->SetLineColor(i + 1);
      HPiChargedPT[i]->DrawNormalized(Option.c_str());
      
      CPiZeroPTFraction.cd();
      HPiZeroPTFraction[i]->Rebin(Rebinning);
      HPiZeroPTFraction[i]->SetStats(0);
      HPiZeroPTFraction[i]->SetLineColor(i + 1);
      HPiZeroPTFraction[i]->DrawNormalized(Option.c_str());
      
      CPiChargedPTFraction.cd();
      HPiChargedPTFraction[i]->Rebin(Rebinning);
      HPiChargedPTFraction[i]->SetStats(0);
      HPiChargedPTFraction[i]->SetLineColor(i + 1);
      HPiChargedPTFraction[i]->DrawNormalized(Option.c_str());
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
   CInvisiblePTFromW.cd();   legend.Draw();
   CInvisiblePhiFromW.cd();   legend.Draw();
   CInvisibleEtaFromW.cd();   legend.Draw();
   CTauNuMT.cd();   legend.Draw();
   CVisibleInvisibleAngle.cd();   legend.Draw();
   CVisibleInvisibleDPhi.cd();   legend.Draw();
   CVisibleInvisibleMT.cd();   legend.Draw();
   CThreeProngSpread.cd();   legend.Draw();
   CIsolation03.cd();   legend.Draw();
   CIsolation04.cd();   legend.Draw();
   CIsolation05.cd();   legend.Draw();
   CRelativeIsolation03.cd();   legend.Draw();
   CRelativeIsolation04.cd();   legend.Draw();
   CRelativeIsolation05.cd();   legend.Draw();
   CPiZeroPT.cd();   legend.Draw();
   CPiChargedPT.cd();   legend.Draw();
   CPiZeroPTFraction.cd();   legend.Draw();
   CPiChargedPTFraction.cd();   legend.Draw();

   PsFileSummary.AddTextPage("Comparison between different categories");

   PsFileSummary.AddCanvas(CTauPT);
   // PsFileSummary.AddCanvas(CTauPhi);
   PsFileSummary.AddCanvas(CTauEta);

   PsFileSummary.AddCanvas(CNuTauPT);
   // PsFileSummary.AddCanvas(CNuTauPhi);
   PsFileSummary.AddCanvas(CNuTauEta);

   PsFileSummary.AddCanvas(CTauNuAngle);
   PsFileSummary.AddCanvas(CTauNuDR);
   PsFileSummary.AddCanvas(CNuTauPTFraction);

   PsFileSummary.AddCanvas(CVisiblePT);
   // PsFileSummary.AddCanvas(CVisiblePhi);
   PsFileSummary.AddCanvas(CVisibleEta);
   PsFileSummary.AddCanvas(CVisibleMass);

   PsFileSummary.AddCanvas(CTauVisibleAngle);
   PsFileSummary.AddCanvas(CTauVisibleDR);
   PsFileSummary.AddCanvas(CVisiblePTFraction);

   PsFileSummary.AddCanvas(CInvisiblePTFromW);
   PsFileSummary.AddCanvas(CInvisibleEtaFromW);
   // PsFileSummary.AddCanvas(CInvisiblePhiFromW);

   PsFileSummary.AddCanvas(CTauNuMT);
   PsFileSummary.AddCanvas(CVisibleInvisibleAngle);
   PsFileSummary.AddCanvas(CVisibleInvisibleDPhi);
   PsFileSummary.AddCanvas(CVisibleInvisibleMT);
  
   CThreeProngSpread.SetLogy();
   PsFileSummary.AddCanvas(CThreeProngSpread);
   
   CIsolation03.SetLogy();
   PsFileSummary.AddCanvas(CIsolation03);
   CIsolation04.SetLogy();
   PsFileSummary.AddCanvas(CIsolation04);
   CIsolation05.SetLogy();
   PsFileSummary.AddCanvas(CIsolation05);
   
   CRelativeIsolation03.SetLogy();
   PsFileSummary.AddCanvas(CRelativeIsolation03);
   CRelativeIsolation04.SetLogy();
   PsFileSummary.AddCanvas(CRelativeIsolation04);
   CRelativeIsolation05.SetLogy();
   PsFileSummary.AddCanvas(CRelativeIsolation05);

   PsFileSummary.AddCanvas(CPiZeroPT);
   PsFileSummary.AddCanvas(CPiChargedPT);
   PsFileSummary.AddCanvas(CPiZeroPTFraction);
   PsFileSummary.AddCanvas(CPiChargedPTFraction);

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

      delete HInvisiblePTFromW[i];
      delete HInvisiblePhiFromW[i];
      delete HInvisibleEtaFromW[i];
      
      delete HTauNuMT[i];
      delete HVisibleInvisibleAngle[i];
      delete HVisibleInvisibleDPhi[i];
      delete HVisibleInvisibleMT[i];
      
      delete HThreeProngSpread[i];
      
      delete HIsolation03[i];
      delete HIsolation04[i];
      delete HIsolation05[i];

      delete HRelativeIsolation03[i];
      delete HRelativeIsolation04[i];
      delete HRelativeIsolation05[i];
      
      delete HPiZeroPT[i];
      delete HPiChargedPT[i];
      delete HPiZeroPTFraction[i];
      delete HPiChargedPTFraction[i];
   }
      
   PsFileSummary.AddTimeStampPage();
   PsFileSummary.Close();

   for(int i = 0; i <= 8; i++)
   {
      PsFile[i]->AddTimeStampPage();
      PsFile[i]->Close();
      delete PsFile[i];
   }
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

double GetDPhi(double P1[4], double P2[4])
{
   double DPhi = GetPhi(P1) - GetPhi(P2);

   if(DPhi > PI)
      DPhi = 2 * PI - DPhi;
   if(DPhi < -PI)
      DPhi = DPhi + 2 * PI;

   return DPhi;
}

double GetMT(double P1[4], double P2[4])
{
   double PT1 = GetPT(P1);
   double PT2 = GetPT(P2);

   // cout << "P1 = " << P1[0] << " " << P1[1] << " " << P1[2] << " " << P1[3] << endl;
   // cout << "P2 = " << P2[0] << " " << P2[1] << " " << P2[2] << " " << P2[3] << endl;
   // cout << "MT = " << 2 * (PT1 * PT2 - P1[1] * P2[1] - P1[2] * P2[2]) << endl;

   return sqrt(2 * (PT1 * PT2 - P1[1] * P2[1] - P1[2] * P2[2]));
}

double GetMinRadius(double P1[4], double P2[4], double P3[4])   // in eta-phi space
{
   double Eta1 = GetEta(P1);
   double Phi1 = GetPhi(P1);
   double Eta2 = GetEta(P2);
   double Phi2 = GetPhi(P2);
   double Eta3 = GetEta(P3);
   double Phi3 = GetPhi(P3);

   double BestResidual2 = 9999999;
   double Best1 = 0;
   double Best2 = 0;
   double Best3 = 0;
   for(int i1 = 0; i1 <= 1; i1++)
   {
      for(int i2 = 0; i2 <= 1; i2++)
      {
         for(int i3 = 0; i3 <= 1; i3++)
         {
            double AveragePhi = (Phi1 + Phi2 + Phi3 + (i1 + i2 + i3) * 2 * PI) / 3;

            double Residual2 = (AveragePhi - Phi1 - i1 * 2 * PI) * (AveragePhi - Phi1 - i1 * 2 * PI)
               + (AveragePhi - Phi2 - i2 * 2 * PI) * (AveragePhi - Phi2 - i2 * 2 * PI)
               + (AveragePhi - Phi3 - i3 * 2 * PI) * (AveragePhi - Phi3 - i3 * 2 * PI);

            if(Residual2 < BestResidual2)
            {
               Best1 = i1;
               Best2 = i2;
               Best3 = i3;

               BestResidual2 = Residual2;
            }
         }
      }
   }

   return GetMinRadius(Eta1, Phi1 + Best1 * 2 * PI, Eta2, Phi2 + Best2 * 2 * PI, Eta3, Phi3 + Best3 * 2 * PI);
}

double GetMinRadius(double X1, double Y1, double X2, double Y2, double X3, double Y3)
{
   // compare two radii:
   //    - common circle radius
   //    - maximum of edge length (divided by two)
   // return the smaller of the two

   // calculate common circle radius
   double C1X0 = 2 * (X1 - X2);
   double C1Y0 = 2 * (Y1 - Y2);
   double C1 = X1 * X1 + Y1 * Y1 - X2 * X2 - Y2 * Y2;
   
   double C2X0 = 2 * (X1 - X3);
   double C2Y0 = 2 * (Y1 - Y3);
   double C2 = X1 * X1 + Y1 * Y1 - X3 * X3 - Y3 * Y3;

   double Distance2 = 99999999;

   if(fabs(C1X0 * C2Y0 - C2X0 * C1Y0) > 1e-8)   // otherwise three points too close to a straight line
   {
      double M = C1X0 * C2Y0 - C2X0 * C1Y0;
      double MX = C1 * C2Y0 - C2 * C1Y0;
      double MY = C1X0 * C2 - C2X0 * C1;

      double X0 = MX / M;
      double Y0 = MY / M;

      Distance2 = (X1 - X0) * (X1 - X0) + (Y1 - Y0) * (Y1 - Y0);
   }

   // calculate max of edge
   double MaxEdge2 = 0;
   if(MaxEdge2 < (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2))
      MaxEdge2 = (X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2);
   if(MaxEdge2 < (X2 - X3) * (X2 - X3) + (Y2 - Y3) * (Y2 - Y3))
      MaxEdge2 = (X2 - X3) * (X2 - X3) + (Y2 - Y3) * (Y2 - Y3);
   if(MaxEdge2 < (X3 - X1) * (X3 - X1) + (Y3 - Y1) * (Y3 - Y1))
      MaxEdge2 = (X3 - X1) * (X3 - X1) + (Y3 - Y1) * (Y3 - Y1);
   MaxEdge2 = MaxEdge2 / 4;

   // minimum of the two
   return sqrt(min(MaxEdge2, Distance2));
}





