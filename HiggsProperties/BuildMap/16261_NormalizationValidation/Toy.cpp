#include <iostream>
using namespace std;

#include "TH1D.h"

#include "Code/DrawRandom.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   SetThesisStyle();

   double A1A1 = 7.43795e-11;
   double A1A2 = -6.60496e-13;
   double A2A2 = 6.49895e-15;

   double EA1A1 = 1.21634e-13;
   double EA1A2 = 1.09149e-15;
   double EA2A2 = 1.07071e-17;

   TH1D H("H", "H", 100, -1, 1);

   for(int i = 0; i < 100000; i++)
   {
      // suppose the above is the correct answer.
      // Now we vary things and attempt to solve for A2 that makes the right answer.
      
      double TestA1A1 = DrawGaussian(A1A1, EA1A1);
      double TestA1A2 = DrawGaussian(A1A2, EA1A2);
      double TestA2A2 = DrawGaussian(A2A2, EA2A2);

      // TestA1A1 + 2 * TestA1A2 * A2 + TestA2A2 * A2 * A2 = A1A1

      double A = TestA2A2;
      double B = 2 * TestA1A2;
      double C = TestA1A1 - A1A1;

      double A2_1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
      double A2_2 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);

      // cout << TestA1A1 << " " << TestA1A2 << " " << TestA2A2 << endl;
      // cout << A << " " << B << " " << C << endl;
      // cout << A2_1 << " " << A2_2 << endl;
      // cout << A1A1 << " " << TestA1A1 + 2 * TestA1A2 * A2_2 + TestA2A2 * A2_2 * A2_2 << endl;
      // cout << endl;

      H.Fill(A2_2);
   }

   PdfFileHelper PdfFile("Toy.pdf");

   PdfFile.AddPlot(H);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




