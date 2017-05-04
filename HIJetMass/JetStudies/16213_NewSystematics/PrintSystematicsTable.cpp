#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[])
{
   if(argc != 4)
   {
      cerr << "Usage: " << argv[0] << " FileName0 FileName7 Location" << endl;
      return -1;
   }

   string FileName0 = argv[1];
   string FileName7 = argv[2];
   double Location = atof(argv[3]);

   double Uncertainty0[5][6] = {{0}};
   double Uncertainty7[5][6] = {{0}};

   int Bin = (Location - 0.0) / (0.4 - 0.0) * 160;

   TFile File0(FileName0.c_str());
   TFile File7(FileName7.c_str());

   for(int iC = 0; iC <= 4; iC++)
   {
      for(int iPT = 0; iPT <= 5; iPT++)
      {
         TGraphAsymmErrors *G0 = (TGraphAsymmErrors *)File0.Get(Form("GRatio_C%d_P%d", iC, iPT));
         TGraphAsymmErrors *G7 = (TGraphAsymmErrors *)File7.Get(Form("GRatio_C%d_P%d", iC, iPT));

         Uncertainty0[iC][iPT] = G0->GetErrorYhigh(Bin);
         Uncertainty7[iC][iPT] = G7->GetErrorYhigh(Bin);
      }
   }

   File7.Close();
   File0.Close();

   double PTBin[] = {120, 140, 160, 180, 200, 300, 500};

   cout << "\\begin{table}[htbp!]" << endl;
   cout << "   \\caption{Summary of systematics at 0.15 in different jet PT and centrality bins.}" << endl;
   cout << "   \\centering" << endl;
   cout << "   \\begin{tabular}{|c|c|c|c|c|c|c|c|c|}" << endl;
   cout << "      \\hline" << endl;
   cout << "       & \\multicolumn{4}{|c|}{SD $(0.1,0.0)$} & \\multicolumn{4}{|c|}{SD $(0.5,1.5)$} \\\\" << endl;
   cout << "      \\hline" << endl;
   cout << "       & 0-10\\% & 10-30\\% & 30-50\\% & 50-80\\% & 0-10\\% & 10-30\\% & 30-50\\% & 50-80\\% \\\\" << endl;
   cout << "      \\hline\\hline" << endl;
   for(int iPT = 0; iPT <= 5; iPT++)
   {
      cout << "      ";
      if(iPT == 0 || iPT == 5)
         cout << "% ";
      cout << setprecision(6) << PTBin[iPT] << "-" << PTBin[iPT+1] << " GeV";
      for(int iC = 0; iC <= 3; iC++)
         cout << " & " << setprecision(2) << setfill('0') << Uncertainty0[iC][iPT] * 100 << "\\%";
      for(int iC = 0; iC <= 3; iC++)
         cout << " & " << setprecision(2) << setfill('0') << Uncertainty7[iC][iPT] * 100 << "\\%";
      cout << " \\\\" << endl;
      cout << "      ";
      if(iPT == 0 || iPT == 5)
         cout << "% ";
      cout << "\\hline" << endl;
   }
   cout << "   \\end{tabular}" << endl;
   cout << "   \\label{Table:Systematics-ToBeChanged}" << endl;
   cout << "\\end{table}" << endl;

   return 0;
}



