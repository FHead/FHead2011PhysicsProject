#include "TFile.h"
#include "TH1D.h"
#include "TF1.h"

#include <iostream>
using namespace std;

void GeneratePedestalMean(char *rootfile)
{
   TFile f(rootfile);

   for(int iphi = 2; iphi <= 4; iphi++)
   {
      // if(iphi == 3)
      //    continue;

      for(int ieta = 7; ieta <= 9; ieta++)
      {
         for(int layergroup = 0; layergroup <= 3; layergroup++)
         {
            TString name = Form("ChannelEnergy_iphi%d_ieta%d_layergroup%d", iphi, ieta, layergroup);
            TH1D *histogram = (TH1D *)f.Get(name);
            if(histogram == 0)
               continue;

            /*
            int maxbin = histogram->GetMaximumBin();

            double sum = 0;
            double weight = 0;
            for(int iBin = maxbin - 2; iBin <= maxbin + 2; iBin++)
            {
               sum = sum + histogram->GetBinCenter(iBin) * histogram->GetBinContent(iBin);
               weight = weight + histogram->GetBinContent(iBin);
            }
            */

            // TF1 gaussian("gaus", "gaus");
            // histogram->Fit(&gaussian);

            // cout << "[Result] " << ieta << " " << (layergroup + 1) * 10 + iphi << " " << gaussian.GetParameter(1) << endl;
            cout << "[Result] " << ieta << " " << (layergroup + 1) * 10 + iphi << " " << histogram->GetMean() << endl;
         }
      }
   }

   f.Close();
}
