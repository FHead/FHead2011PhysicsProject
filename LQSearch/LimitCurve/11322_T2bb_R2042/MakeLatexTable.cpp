#include <iostream>
#include <iomanip>
using namespace std;

#include "TFile.h"
#include "TH2D.h"

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage: " << argv[0] << " File HistogramName" << endl;
      return -1;
   }

   TFile F(argv[1]);
   TH2D *H = (TH2D *)F.Get(argv[2]);

   if(H == NULL)
   {
      cerr << "Error opening the file/histogram";
      return -1;
   }

   cout << "\\begin{table}[!ht]" << endl;
   cout << "\\begin{center}" << endl;

   cout << "\\begin{tabular}{|c|";
   for(int i = 150; i <= 500; i = i + 25)
      cout << "c|";
   cout << "}" << endl;

   cout << "\\hline" << endl;
   cout << "\\neutralino mass & \\multicolumn{15}{|c|}{\\sbottom mass (GeV)} \\\\" << endl;
   cout << "\\cline{2-16}" << endl;

   cout << " (GeV) ";
   for(int i = 150; i <= 500; i = i + 25)
      cout << " & " << i;
   cout << " \\\\" << endl;

   cout << "\\hline" << endl;

   for(int i = 100; i <= 200; i = i + 25)
   {
      cout << i << " ";
      for(int j = 150; j <= 500; j = j + 25)
      {
         int Bin = H->FindBin(j, i);
         double Value = H->GetBinContent(Bin);

         cout << " & ";
         if(Value > 0)
            cout << setprecision(2) << Value;
      }
      cout << " \\\\" << endl;
   }

   cout << "\\hline" << endl;
   cout << "\\end{tabular}" << endl;
   cout << "\\end{center}" << endl;
   cout << "\\caption{FILL ME IN\\label{Table:FILLMEIN}}" << endl;
   cout << "\\end{table}" << endl;

   return 0;
}






