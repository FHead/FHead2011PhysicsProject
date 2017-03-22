#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " FileName Location" << endl;
      return -1;
   }

   string FileName = argv[1];
   double Location = atof(argv[2]);

   double Uncertainty[5][6] = {{0}};

   int Bin = (Location - 0.0) / (0.4 - 0.0) * 160;

   TFile File(FileName.c_str());

   for(int iC = 0; iC <= 4; iC++)
   {
      for(int iPT = 0; iPT <= 5; iPT++)
      {
         TGraphAsymmErrors *G = (TGraphAsymmErrors *)File.Get(Form("GRatio_C%d_P%d", iC, iPT));

         Uncertainty[iC][iPT] = G->GetErrorYhigh(Bin);
      }
   }

   File.Close();

   double PTBin[] = {120, 140, 160, 180, 200, 300, 500};

   cout << "\\begin{table}[htbp!]" << endl;
   cout << "   \\caption{Summary of systematics in the bulk in different jet PT and centrality bins.}" << endl;
   cout << "   \\centering" << endl;
   cout << "   \\begin{tabular}{|c|c|c|c|c|}" << endl;
   cout << "      \\hline" << endl;
   cout << "       & 0-10\\% & 10-30\\% & 30-50\\% & 50-80\\% \\\\" << endl;
   cout << "      \\hline" << endl;
   for(int iPT = 0; iPT <= 5; iPT++)
   {
      cout << "      " << setprecision(6) << PTBin[iPT] << "-" << PTBin[iPT+1] << " GeV";
      for(int iC = 0; iC <= 3; iC++)
         cout << " & " << setprecision(2) << setfill('0') << Uncertainty[iC][iPT] * 100 << "\\%";
      cout << " \\\\" << endl;
      cout << "      \\hline" << endl;
   }
   cout << "   \\end{tabular}" << endl;
   cout << "   \\label{Table:Systematics-ToBeChanged}" << endl;
   cout << "\\end{table}" << endl;

   return 0;
}



