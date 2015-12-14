#include <iostream>
#include <iomanip>
#include <fstream>
#include <deque>
#include <map>
#include <cmath>

using namespace std;


int main(int argc, char **argv)
{
   // some housekeeping...
   if(argc != 4)
   {
      cout << "Usage: exe preamp_on_cdf preamp_off_cdf output_filename" << endl;
      return -1;
   }

   // the plan
   // 1. open the relevant files for reading and writing
   // 2. read in all the cdf's
   // 3. for every non-repetitive number in the preamp on cdf, find and
   //    interpolate to get the closest adc value in the preamp off cdf, then output
   // 4. close the files


   // 1. file i/o
   ifstream in_on(argv[1]);
   ifstream in_off(argv[2]);
   ofstream out(argv[3]);

   // read in all the cdf's
   double lastone = -1;
   map<int, double> PreampOnCdf;
   while(in_on)
   {
      int adc = -1;
      double percentage = -1;

      in_on >> adc >> percentage;

      if(adc > 0 && percentage > 0)
      {
         if(fabs(lastone - percentage) > 1e-8)
         {
            PreampOnCdf.insert(pair<int, double>(adc, percentage));
            lastone = percentage;
         }
      }
      else
         break;
   }

   lastone = -1;
   map<int, double> PreampOffCdf;
   while(in_off)
   {
      int adc = -1;
      double percentage = -1;

      in_off >> adc >> percentage;

      if(adc > 0 && percentage > 0)
      {
         if(fabs(lastone - percentage) > 1e-8)
         {
            PreampOffCdf.insert(pair<int, double>(adc, percentage));
            lastone = percentage;
         }
      }
      else
         break;
   }

   // 3. for every non-repetitive number in the preamp on cdf, find and
   //    interpolate to get the closest adc value in the preamp off cdf, then output
   map<int, double>::iterator currentAdc = PreampOffCdf.begin();
   map<int, double>::iterator previousAdc = PreampOffCdf.begin();
   for(map<int, double>::iterator iter = PreampOnCdf.begin(); iter != PreampOnCdf.end(); iter++)
   {
      // if(iter->second > 0.99998)
      //    break;

      while(currentAdc != PreampOffCdf.end() && currentAdc->second < iter->second)
      {
         previousAdc = currentAdc;
         currentAdc++;
      }

      if(currentAdc == previousAdc)
         continue;

      // for now just use linear interpolation
      double target_adc = currentAdc->first -
         (currentAdc->second - iter->second) /
         (currentAdc->second - previousAdc->second) *
         (currentAdc->first - previousAdc->first);

      out << iter->first << " " << setprecision(10) << target_adc << endl;
   }

   // 4. file i/o
   out.close();
   in_off.close();
   in_on.close();

   return 0;
}


