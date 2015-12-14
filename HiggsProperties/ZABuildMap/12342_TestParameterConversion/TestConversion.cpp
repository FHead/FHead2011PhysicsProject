// Testing code for checking whether the lepton <=> angle conversion makes sense
// Author: Yi Chen 11223

#include <iostream>
#include <fstream>
using namespace std;

#include "ProgressBar.h"

#include "AngleConversion.h"

int main()
{
   ZAEventParameters TestParameters;
   TestParameters.Phi0 = 0.524;
   TestParameters.Theta0 = 0.653;
   TestParameters.ThetaLL = 2.1123;
   TestParameters.HMass = 126.5235;
   TestParameters.ZMass = 91.186;
   TestParameters.PhiH = 0.61253;
   TestParameters.PhiOffset = 0.25;
   TestParameters.YH = -0.25;
   TestParameters.PTH = 20;

   cout << "===== Input parameters =====" << endl;
   cout << TestParameters << endl;

   ZALeptonVectors Leptons = ConvertAnglesToVectorsRoberto(TestParameters);

   cout << "===== Lepton vectors =====" << endl;
   cout << Leptons << endl;

   ZAEventParameters OutputParameter = ConvertVectorsToAnglesRoberto(Leptons);

   cout << endl;
   cout << "===== Output parameters =====" << endl;
   cout << OutputParameter << endl;
   cout << endl;

   cout << endl;
   cout << "==> Now the program will loop over all angles (10 bins each), and verify" << endl;
   cout << "   that for ALL cases the output parameter is the same as input parameter" << endl;
   cout << "   In case of mismatch, they will be summarized in the file \"MisMatch.txt\"" << endl;
   cout << "   and also at the end of this program" << endl;
   cout << "   This part should run for 1-2 minutes" << endl;
   cout << endl;

   // now the real deal

   ProgressBar Bar(cout, 100);
   Bar.SetStyle(1);

   ofstream out("MisMatch.txt");

   int FailCount = 0;

   for(double Phi0 = 0; Phi0 < 2 * PI; Phi0 = Phi0 + PI / 5)
   {
      for(double Theta0 = PI / 40; Theta0 < PI; Theta0 = Theta0 + PI / 10)
      {
         Bar.Update(Phi0 * 5 / PI * 10 + Theta0 * 10 / PI);
         Bar.Print();

         for(double ThetaLL = PI / 40; ThetaLL < PI; ThetaLL = ThetaLL + PI / 10)
         {
            TestParameters.Phi0 = Phi0;
            TestParameters.Theta0 = Theta0;
            TestParameters.ThetaLL = ThetaLL;

            Leptons = ConvertAnglesToVectorsRoberto(TestParameters);

            OutputParameter = ConvertVectorsToAnglesRoberto(Leptons);

            if(!(OutputParameter == TestParameters))
            {
               out << "Mismatch:" << endl;
               out << endl;
               out << TestParameters << endl;
               out << OutputParameter << endl;
               out << endl;
               out << endl;

               FailCount = FailCount + 1;
            }
         }
      }
   }

   out.close();

   Bar.Update(100);
   Bar.Print();
   Bar.PrintLine();

   if(FailCount > 0)
      cout << "Failed count = " << FailCount << ".  Contact Yi to debug." << endl;
   else
      cout << "All tests cleared.  Everything matches." << endl;
   cout << endl;

   return 0;
}






