#include "TFile.h"
#include "TGraph.h"

#include <iostream>

void FitScale2(char *input)
{
   TFile f(input);

   TGraph *gr = (TGraph *)f.Get("Graph");

   double a0 = 0;
   double a1 = 0;
   int ifail = 0;

   gr->LeastSquareLinearFit(1, a0, a1, ifail, 2000, 4000);

   std::cout << 1.0 / a1 << std::endl;

   f.Close();
}
