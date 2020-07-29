#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#include "TH1D.h"
#include "TFile.h"

int main(int argc, char *argv[])
{
   TFile File("RAA_Smooth.root");

   int R[] = {2, 3, 4, 6, 8, 10};
   string C[] = {"0to10", "10to30", "30to50", "50to90"};
   string Cent[] = {"0-10%", "10-30%", "30-50%", "50-90%"};
   double TAALumi[] = {0.018646, 0.025341, 0.051233, 0.100719};
   for(int i = 0; i < 4; i++)
      TAALumi[i] = sqrt(TAALumi[i] * TAALumi[i] + 0.023 * 0.023);

   for(int iR = 0; iR < 6; iR++)
   {
      for(int iC = 0; iC < 4; iC++)
      {
         TH1D *H1 = (TH1D *)File.Get(Form("akCs%dPU3PFFlowJetAnalyzer_Cent%s_1", R[iR], C[iC].c_str()));
         TH1D *H2 = (TH1D *)File.Get(Form("akCs%dPU3PFFlowJetAnalyzer_Cent%s_2", R[iR], C[iC].c_str()));

         cout << H1 << " " << H2 << endl;

         ofstream out(Form("CMSJetRAA2020-%d-%d.json", iR, iC));

         out << "{" << endl;
         out << "   \"System\": \"PbPb\"," << endl;
         out << "   \"Energy\": \"5.02 TeV\"," << endl;
         out << "   \"Subject\": \"JetR" << R[iR] << "\"," << endl;
         out << "   \"Observable\": \"RAA\"," << endl;
         out << "   \"Dependency\": \"PT\"," << endl;
         out << "   \"Centrality\": \"" << Cent[iC] << "\"," << endl;
         out << "   \"Record\": \"CMS 2020\"," << endl;
         out << "   \"Selection\": \"eta < 2.0\"," << endl;
         out << "   \"Comment\": \"Preliminary, 2015 data\"," << endl;

         out << "   \"X\": [";
         for(int i = 1; i <= H1->GetNbinsX(); i++)
         {
            if(i != 1)
               out << ",";
            out << H1->GetXaxis()->GetBinCenter(i);
         }
         out << "]," << endl;

         out << "   \"EXLow\": [";
         for(int i = 1; i <= H1->GetNbinsX(); i++)
         {
            if(i != 1)
               out << ",";
            out << H1->GetXaxis()->GetBinCenter(i) - H1->GetXaxis()->GetBinLowEdge(i);
         }
         out << "]," << endl;

         out << "   \"EXHigh\": [";
         for(int i = 1; i <= H1->GetNbinsX(); i++)
         {
            if(i != 1)
               out << ",";
            out << H1->GetXaxis()->GetBinUpEdge(i) - H1->GetXaxis()->GetBinCenter(i);
         }
         out << "]," << endl;

         out << "   \"Y\": [";
         for(int i = 1; i <= H1->GetNbinsX(); i++)
         {
            if(i != 1)
               out << ",";
            out << H1->GetBinContent(i);
         }
         out << "]," << endl;

         out << "   \"EYStatLow\": [";
         for(int i = 1; i <= H1->GetNbinsX(); i++)
         {
            if(i != 1)
               out << ",";
            out << H1->GetBinError(i);
         }
         out << "]," << endl;

         out << "   \"EYStatHigh\": [";
         for(int i = 1; i <= H1->GetNbinsX(); i++)
         {
            if(i != 1)
               out << ",";
            out << H1->GetBinError(i);
         }
         out << "]," << endl;

         out << "   \"EYSysLow\": [";
         for(int i = 1; i <= H1->GetNbinsX(); i++)
         {
            if(i != 1)
               out << ",";
            out << H2->GetBinError(i);
         }
         out << "]," << endl;

         out << "   \"EYSysHigh\": [";
         for(int i = 1; i <= H1->GetNbinsX(); i++)
         {
            if(i != 1)
               out << ",";
            out << H2->GetBinError(i);
         }
         out << "]," << endl;

         out << "   \"GlobalUncertainty\": " << TAALumi[iC] << endl;
         out << "}," << endl;

         out.close();
      }
   }

   File.Close();

   return 0;
}



