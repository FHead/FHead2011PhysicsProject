#include <iostream>
#include <fstream>
using namespace std;

#include "TH2D.h"
#include "TCanvas.h"

#include "PlotHelper2.h"
#include "SetStyle.h"

int main()
{
   TH2D HEfficiency("HEfficiency", "Efficiency (atlas-like);m0;m12", 50, 0, 1250, 50, 0, 1250);
   TH2D HEfficiencyError("HEfficiencyError", "Efficiency error;m0;m12", 50, 0, 1250, 50, 0, 1250);

   ifstream in("Processed150");

   while(in)
   {
      double m0 = 0;
      double m12 = 0;
      double eff = 0;
      double seff = 0;

      in >> m0 >> m12 >> eff;

      if(m0 == 0)
         continue;

      HEfficiency.Fill(m0, m12, eff);
      HEfficiencyError.Fill(m0, m12, seff);
   }

   in.close();

   HEfficiency.SetMaximum(0.3);
   HEfficiency.SetStats(0);
   HEfficiencyError.SetStats(0);

   PsFileHelper PsFile("Efficiencies150.ps");
   PsFile.AddTextPage("Efficiencies!");

   PsFile.AddPlot(HEfficiency, "colz");
   PsFile.AddPlot(HEfficiencyError, "colz");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}





