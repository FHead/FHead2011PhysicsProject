#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TH2D.h"

#include "DataHelper.h"
#include "ProgressBar.h"
#include "PlotHelper3.h"
#include "SetStyle.h"

#include "AngleConversion.h"
#include "Cuts.h"

struct Likelihood;
int main();
vector<Likelihood> ReadTree(string FileName);

struct Likelihood
{
   double V[3][3];
   double I[3][3];
};

int main()
{
   SetThesisStyle();

   vector<Likelihood> S = ReadTree("Phto2e2mu_A1UUpA2UURI_18p4GeV_NoPDF_GenCuts_1.root");

   PdfFileHelper PdfFile("ParameterScan.pdf");
   PdfFile.AddTextPage("Check signal extraction");

   vector<string> Explanation(10);
   Explanation[0] = "Take different number of signal events";
   Explanation[1] = "";
   Explanation[2] = "";
   Explanation[3] = "Scan through different parameter point and plot";
   Explanation[4] = "-log(likelihood)";
   Explanation[5] = "";
   Explanation[6] = "";
   Explanation[7] = "";
   Explanation[8] = "";
   Explanation[9] = "";
   PdfFile.AddTextPage(Explanation);

   int NS[] = {2, 6, 20, 60, 200, 600, 2000, 6000, 20000, 60000};
   for(int iS = 0; iS < 10; iS++)
   {
      cout << "Start running with NS = " << NS[iS] << endl;

      int Bin = 200;
      TH2D HScan("HScan", Form("NS = %d;A2UUR/A1UU;A2UUI/A1UU", NS[iS]), Bin, -400, 400, Bin, -400, 400);
      TH2D HScan2("HScan2", Form("NS = %d;A2UUR/A1UU;A2UUI/A1UU", NS[iS]), Bin, 50, 150, Bin, 150, 250);

      for(int i = 1; i <= Bin; i++)
      {
         for(int j = 1; j <= Bin; j++)
         {
            double A2R = HScan.GetXaxis()->GetBinCenter(i);
            double A2I = HScan.GetYaxis()->GetBinCenter(j);

            double LL = 0;
            for(int iE = 0; iE < NS[iS]; iE++)
            {
               double VS = 0, IS = 0;
               
               VS = VS + S[iE].V[0][0] *   1 *   1 + S[iE].V[0][1] *   1 * A2R + S[iE].V[0][2] *   1 * A2I;
               VS = VS + S[iE].V[1][0] * A2R *   1 + S[iE].V[1][1] * A2R * A2R + S[iE].V[1][2] * A2R * A2I;
               VS = VS + S[iE].V[2][0] * A2I *   1 + S[iE].V[2][1] * A2I * A2R + S[iE].V[2][2] * A2I * A2I;
               
               IS = IS + S[iE].I[0][0] *   1 *   1 + S[iE].I[0][1] *   1 * A2R + S[iE].I[0][2] *   1 * A2I;
               IS = IS + S[iE].I[1][0] * A2R *   1 + S[iE].I[1][1] * A2R * A2R + S[iE].I[1][2] * A2R * A2I;
               IS = IS + S[iE].I[2][0] * A2I *   1 + S[iE].I[2][1] * A2I * A2R + S[iE].I[2][2] * A2I * A2I;

               LL = LL + log(VS / IS);
            }

            HScan.SetBinContent(i, j, -LL);
            
            A2R = HScan2.GetXaxis()->GetBinCenter(i);
            A2I = HScan2.GetYaxis()->GetBinCenter(j);

            LL = 0;
            for(int iE = 0; iE < NS[iS]; iE++)
            {
               double VS = 0, IS = 0;
               
               VS = VS + S[iE].V[0][0] *   1 *   1 + S[iE].V[0][1] *   1 * A2R + S[iE].V[0][2] *   1 * A2I;
               VS = VS + S[iE].V[1][0] * A2R *   1 + S[iE].V[1][1] * A2R * A2R + S[iE].V[1][2] * A2R * A2I;
               VS = VS + S[iE].V[2][0] * A2I *   1 + S[iE].V[2][1] * A2I * A2R + S[iE].V[2][2] * A2I * A2I;
               
               IS = IS + S[iE].I[0][0] *   1 *   1 + S[iE].I[0][1] *   1 * A2R + S[iE].I[0][2] *   1 * A2I;
               IS = IS + S[iE].I[1][0] * A2R *   1 + S[iE].I[1][1] * A2R * A2R + S[iE].I[1][2] * A2R * A2I;
               IS = IS + S[iE].I[2][0] * A2I *   1 + S[iE].I[2][1] * A2I * A2R + S[iE].I[2][2] * A2I * A2I;

               LL = LL + log(VS / IS);
            }

            HScan2.SetBinContent(i, j, -LL);
         }
      }

      HScan.SetStats(0);
      HScan2.SetStats(0);

      HScan.SetMaximum(HScan.GetMinimum() + 10);
      HScan2.SetMaximum(HScan2.GetMinimum() + 10);

      TGraph GTruth;
      GTruth.SetPoint(0, 67 / 0.5448, 100 / 0.5448);
      GTruth.SetMarkerColor(kMagenta);
      GTruth.SetMarkerStyle(20);

      TCanvas C;

      HScan.Draw("colz");
      GTruth.Draw("p");

      PdfFile.AddCanvas(C);
      
      HScan2.Draw("colz");
      GTruth.Draw("p");
      
      PdfFile.AddCanvas(C);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<Likelihood> ReadTree(string FileName)
{
   // we need A1UUR, A2UUR, A2UUI and cross terms...so 3x3

   vector<Likelihood> Result;

   TFile F(FileName.c_str());

   TTree *T = (TTree *)F.Get("Tree");

   Likelihood L;
   double L1PT, L1Eta, L1Phi;
   double L2PT, L2Eta, L2Phi;
   double L3PT, L3Eta, L3Phi;
   double L4PT, L4Eta, L4Phi;

   T->SetBranchAddress("B1_A1VVR_A1VVR", &L.V[0][0]);
   T->SetBranchAddress("B1_A1VVR_A2VVR", &L.V[0][1]);
   T->SetBranchAddress("B1_A1VVR_A2VVI", &L.V[0][2]);
   T->SetBranchAddress("B1_A2VVR_A1VVR", &L.V[1][0]);
   T->SetBranchAddress("B1_A2VVR_A2VVR", &L.V[1][1]);
   T->SetBranchAddress("B1_A2VVR_A2VVI", &L.V[1][2]);
   T->SetBranchAddress("B1_A2VVI_A1VVR", &L.V[2][0]);
   T->SetBranchAddress("B1_A2VVI_A2VVR", &L.V[2][1]);
   T->SetBranchAddress("B1_A2VVI_A2VVI", &L.V[2][2]);
   T->SetBranchAddress("L1PT", &L1PT);
   T->SetBranchAddress("L1Eta", &L1Eta);
   T->SetBranchAddress("L1Phi", &L1Phi);
   T->SetBranchAddress("L2PT", &L2PT);
   T->SetBranchAddress("L2Eta", &L2Eta);
   T->SetBranchAddress("L2Phi", &L2Phi);
   T->SetBranchAddress("L3PT", &L3PT);
   T->SetBranchAddress("L3Eta", &L3Eta);
   T->SetBranchAddress("L3Phi", &L3Phi);
   T->SetBranchAddress("L4PT", &L4PT);
   T->SetBranchAddress("L4Eta", &L4Eta);
   T->SetBranchAddress("L4Phi", &L4Phi);

   DataHelper DHFile("Normalization.dh");
   L.I[0][0] = DHFile["0TeV"]["TF1_A1VVR_A1VVR"].GetDouble();
   L.I[0][1] = DHFile["0TeV"]["TF1_A1VVR_A2VVR"].GetDouble();
   L.I[0][2] = DHFile["0TeV"]["TF1_A1VVR_A2VVI"].GetDouble();
   L.I[1][0] = DHFile["0TeV"]["TF1_A2VVR_A1VVR"].GetDouble();
   L.I[1][1] = DHFile["0TeV"]["TF1_A2VVR_A2VVR"].GetDouble();
   L.I[1][2] = DHFile["0TeV"]["TF1_A2VVR_A2VVI"].GetDouble();
   L.I[2][0] = DHFile["0TeV"]["TF1_A2VVI_A1VVR"].GetDouble();
   L.I[2][1] = DHFile["0TeV"]["TF1_A2VVI_A2VVR"].GetDouble();
   L.I[2][2] = DHFile["0TeV"]["TF1_A2VVI_A2VVI"].GetDouble();

   int EntryCount = T->GetEntries();
   ProgressBar Bar(cout, EntryCount);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(iE % 500 == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      T->GetEntry(iE);

      LeptonVectors Leptons;
      Leptons.Lepton11.SetPtEtaPhi(L1PT, L1Eta, L1Phi);
      Leptons.Lepton12.SetPtEtaPhi(L2PT, L2Eta, L2Phi);
      Leptons.Lepton21.SetPtEtaPhi(L3PT, L3Eta, L3Phi);
      Leptons.Lepton22.SetPtEtaPhi(L4PT, L4Eta, L4Phi);

      Leptons = Leptons.GoToRest();

      if(PassPairingCuts(Leptons)[5] == false)   // F cut
         continue;

      Result.push_back(L);
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   F.Close();

   cout << "File " << FileName << ": " << Result.size() << "/" << EntryCount << " selected" << endl;

   return Result;
}





