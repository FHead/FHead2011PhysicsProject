#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"

#include "CommandLine.h"
#include "CustomAssert.h"
#include "SignificantDigit.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   // Command line inputs
   CommandLine CL(argc, argv);
   string InputFileName     = CL.Get("input");
   string OutputFileName    = CL.Get("output");
   vector<string> GName     = CL.GetStringVector("graph");
   vector<string> GSysName  = CL.GetStringVector("graphsys");
   string XLabel            = CL.Get("x");
   string YLabel            = CL.Get("y");
   vector<string> Qualifier = CL.GetStringVector("qualifier");
   vector<string> Type      = CL.GetStringVector("type");
   vector<string> PTBin     = CL.GetStringVector("ptbin");
   vector<string> CBin      = CL.GetStringVector("cbin");
   vector<string> SD        = CL.GetStringVector("sd");

   int N = GName.size();
   Assert(N != 0,                     "No graph provided, nothing is done to the output");
   Assert(N == (int)Qualifier.size(), "Number of labels not equal to number of graphs");
   Assert(N == (int)Type.size(),      "Number in Type list not equal to number of graphs");
   Assert(N == (int)PTBin.size(),     "Number in PTBin list not equal to number of graphs");
   Assert(N == (int)CBin.size(),      "Number in CBin list not equal to number of graphs");
   Assert(N == (int)SD.size(),        "Number in SD list not equal to number of graphs");

   /*
   cout << "0.0010406" << " " << FindFirstSignificantDigit(0.0010406) << endl;
   cout << "CountDigit(1023.230, -2)"     << " " << CountDigit(1023.230, -2) << endl;
   cout << "RoundToDigit(1023.23503, -2)" << " " << setprecision(CountDigit(1023.23503, -2)) << RoundToDigit(1023.23503, -2) << endl;
   cout << "RoundToDigit(1023.23503, -3)" << " " << setprecision(CountDigit(1023.23503, -3)) << RoundToDigit(1023.23503, -3) << endl;
   cout << "RoundToDigit(1023.23499, -2)" << " " << setprecision(CountDigit(1023.23499, -2)) << RoundToDigit(1023.23499, -2) << endl;
   cout << "RoundToDigit(1023.23503, -1)" << " " << setprecision(CountDigit(1023.23503, -1)) << RoundToDigit(1023.23503, -1) << endl;
   cout << "RoundToDigit(1023.23503, 0)"  << " " << setprecision(CountDigit(1023.23503, 0)) << RoundToDigit(1023.23503, 0)  << endl;
   cout << "RoundToDigit(1023.23503, 1)"  << " " << setprecision(CountDigit(1023.23503, 1)) << RoundToDigit(1023.23503, 1)  << endl;
   cout << "RoundToDigit(1023.23503, 2)"  << " " << setprecision(CountDigit(1023.23503, 2)) << RoundToDigit(1023.23503, 2)  << endl;
   */
   
   // Preparation
   TFile File(InputFileName.c_str());
   ofstream out(OutputFileName);

   // Get graphs from file
   vector<TGraphAsymmErrors *> G, GSys;
   for(int i = 0; i < N; i++)
   {
      G.push_back((TGraphAsymmErrors *)File.Get(GName[i].c_str()));

      if(i < (int)GSysName.size() && GSysName[i] != "")
         GSys.push_back((TGraphAsymmErrors *)File.Get(GSysName[i].c_str()));
      else
         GSys.push_back(NULL);
   }

   Assert(G[0] != NULL, "First graph is NULL, can't access x axis bins");

   // Write x ranges: taking from the first one
   out << "independent_variables:" << endl;
   out << "- header: {" << XLabel << "}" << endl;
   out << "  values:" << endl;

   int BinCount = G[0]->GetN();
   vector<bool> Valid(BinCount);
   for(int i = 0; i < BinCount; i++)
   {
      double X, Y, EXL, EXH;
      G[0]->GetPoint(i, X, Y);
      EXL = G[0]->GetErrorXlow(i);
      EXH = G[0]->GetErrorXhigh(i);

      double L = X - EXL;
      double R = X + EXH;

      if(L == L && R == R)
         Valid[i] = true;
      else
         Valid[i] = false;

      if(Valid[i] == true)
         out << "  - {low: " << RoundToDigit(L, -5) << ", high: " << RoundToDigit(R, -5) << "}" << endl;
   }

   // Loop over graphs and write y ranges
   out << "dependent_variables:" << endl;

   for(int i = 0; i < N; i++)
   {
      out << "- header: {" << YLabel << "}" << endl;
      
      out << "  qualifiers:" << endl;

      if(Type[i] == "PP")        out << "  - {name: RE, value: P P --> JET X}" << endl;
      else if(Type[i] == "AA")   out << "  - {name: RE, value: PB PB --> JET X}" << endl;
      else                       out << "  - {name: RE, value: P P --> JET X and PB PB --> JET X}" << endl;
      
      out << "  - {name: SQRT(S)/NUCLEON, units: TEV, value: 5.02}" << endl;
      out << "  - {name: JET ALGO, value: ANTI-K_T R = 0.4}" << endl;
      out << "  - {name: '|ETAJET|', value: '< 1.3'}" << endl;

      if(PTBin[i] == "0")   out << "  - {name: PTJET, units: GEV, value: 120-140}" << endl;
      if(PTBin[i] == "1")   out << "  - {name: PTJET, units: GEV, value: 140-160}" << endl;
      if(PTBin[i] == "2")   out << "  - {name: PTJET, units: GEV, value: 160-180}" << endl;
      if(PTBin[i] == "3")   out << "  - {name: PTJET, units: GEV, value: 180-200}" << endl;
      if(PTBin[i] == "4")   out << "  - {name: PTJET, units: GEV, value: 200-300}" << endl;
      if(PTBin[i] == "5")   out << "  - {name: PTJET, units: GEV, value: 300-500}" << endl;
      
      if(CBin[i] == "0")   out << "  - {name: CENTRALITY, units: PERCENTILE, value: 0-10}" << endl;
      if(CBin[i] == "1")   out << "  - {name: CENTRALITY, units: PERCENTILE, value: 10-30}" << endl;
      if(CBin[i] == "2")   out << "  - {name: CENTRALITY, units: PERCENTILE, value: 30-50}" << endl;
      if(CBin[i] == "3")   out << "  - {name: CENTRALITY, units: PERCENTILE, value: 50-80}" << endl;
      if(CBin[i] == "4")   out << "  - {name: CENTRALITY, units: PERCENTILE, value: 80-100}" << endl;

      if(SD[i] == "0")   out << "  - {name: Soft Drop beta, value: 0.0}" << endl;
      if(SD[i] == "7")   out << "  - {name: Soft Drop beta, value: 1.5}" << endl;
      if(SD[i] == "0")   out << "  - {name: Soft Drop z_cut, value: 0.1}" << endl;
      if(SD[i] == "7")   out << "  - {name: Soft Drop z_cut, value: 0.5}" << endl;

      out << "  - {name: Delta R_12, value: '> 0.1'}" << endl;

      if(Qualifier[i] != "NONE")   out << "  - {name: LABEL, value: '" << Qualifier[i] << "'}" << endl;

      out << "  values:" << endl;

      for(int j = 0; j < BinCount; j++)
      {
         if(Valid[j] == false)
            continue;

         if(j < G[i]->GetN())
         {
            double X, Y, EYL, EYH, SYL, SYH;
            G[i]->GetPoint(j, X, Y);
            EYL = G[i]->GetErrorYlow(j);
            EYH = G[i]->GetErrorYhigh(j);

            int D = -10000;
            D = max(D, FindFirstSignificantDigit(EYL));
            D = max(D, FindFirstSignificantDigit(EYH));
            
            if(GSys[i] != NULL)
            {
               SYL = GSys[i]->GetErrorYlow(j);
               SYH = GSys[i]->GetErrorYhigh(j);
               
               D = max(D, FindFirstSignificantDigit(SYL));
               D = max(D, FindFirstSignificantDigit(SYH));
            }

            D = D - 1;

            /*
            cout << setprecision(-1) << EYH << " " << EYL << endl;
            cout << D << endl;
            cout << RoundToDigit(EYH, D) << endl;
            cout << CountDigit(EYH, D) << endl;
            */

            int Digit = 0;
            if(D < 0)
               Digit = -D;
            if(Digit > 100)
               Digit = 0;

            out << fixed << setprecision(Digit);
            out << "  - value: " << RoundToDigit(Y, D) << endl;
            out << "    errors:" << endl;
            out << "    - {asymerror: {plus: " << RoundToDigit(EYH, D)
               << ", minus: " << -RoundToDigit(EYL, D) << "}, label: stat}" << endl;
            if(GSys[i] != NULL)
               out << "    - {asymerror: {plus: " << RoundToDigit(SYH, D)
                  << ", minus: " << -RoundToDigit(SYL, D) << "}, label: sys}" << endl;
         }
         else
         {
            out << "  - value: ''" << endl;
            out << "    errors:" << endl;
            out << "    - {symerror: ''}" << endl;
         }
      }
   }

   // Cleanup
   out.close();
   File.Close();

   return 0;
}





