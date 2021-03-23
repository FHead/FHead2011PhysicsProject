#include <cmath>
#include <fstream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"

#include "CommandLine.h"
#include "Code/DrawRandom.h"

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string FileName       = CL.Get("Input", "RAA_Smooth.root");
   string NameBase       = CL.Get("Name", "akCs2PU3PFFlowJetAnalyzer_Cent10to30");
   string OutputFileName = CL.Get("Output", "RAA.txt");
   double Smearing       = CL.GetDouble("Smearing", 0.02);
   double Lumi           = CL.GetDouble("Lumi", 0.03);
   double TAA            = CL.GetDouble("TAA", 0.02);

   TFile File(FileName.c_str());

   TH1D *H1 = (TH1D *)File.Get(Form("%s_1", NameBase.c_str()));
   TH1D *H2 = (TH1D *)File.Get(Form("%s_2", NameBase.c_str()));

   ofstream out(OutputFileName);

   for(int i = 1; i <= H1->GetNbinsX(); i++)
   {
      double X      = H1->GetBinCenter(i);
      double Y      = H1->GetBinContent(i);
      double EX     = H1->GetXaxis()->GetBinUpEdge(i) - X;
      double EYStat = H1->GetBinError(i);
      double EYSys  = H2->GetBinError(i);

      // if(Smearing > 0)
      //    Y = Y * DrawGaussian(1, Smearing);

      EYSys = sqrt(EYSys * EYSys + Lumi * Lumi * Y * Y + TAA * TAA * Y * Y);

      out << X << " " << Y << "\t" << EX << " " << EX << "\t" << EYStat << " " << EYStat
         << "\t" << EYSys << " " << EYSys << endl;
   }

   out.close();

   File.Close();

   return 0;
}



