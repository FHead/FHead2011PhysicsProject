#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

int main()
{
   Pythia pythia;
   
   pythia.readString("WeakSingleBoson:all = on");       // turn on vector bosons: we want some tau particles
   pythia.readString("WeakDoubleBoson:all = on");
   pythia.readString("WeakBosonAndParton:all = on");

   pythia.readString("24:oneChannel = 1 1 0 -15 16");   // force W to decay to tau nu
   pythia.readString("23:oneChannel = 1 1 0 16 -16");   // force Z to decay to tau tau

   pythia.readString("Random:setSeed = on");
   pythia.readString("Random:seed = 0");
   
   pythia.init(2212, 2212, 7000);

   map<string, double> DecayProductCounts;
   double TotalCount = 0;

   for(int iEvent = 0; iEvent < 100000; iEvent++)
   {
      if(!pythia.next())
         continue;

      for(int iParticle = 0; iParticle < pythia.event.size(); iParticle++)
      {
         if(pythia.event[iParticle].id() == 15)   // tau
         {
            vector<int> Daughters = pythia.event.daughterList(iParticle);

            bool TauInDaughter = false;
            for(int i = 0; i < (int)Daughters.size(); i++)
               if(pythia.event[Daughters[i]].id() == 15)
                  TauInDaughter = true;

            if(TauInDaughter == true)
               continue;

            vector<string> DaughterNames;
            for(int i = 0; i < (int)Daughters.size(); i++)
               DaughterNames.push_back(pythia.particleData.name(pythia.event[Daughters[i]].id()));

            sort(DaughterNames.begin(), DaughterNames.end());

            stringstream Products;
            for(int i = 0; i < (int)DaughterNames.size(); i++)
               Products << " " << DaughterNames[i];

            DecayProductCounts[Products.str()] = DecayProductCounts[Products.str()] + 1;

            TotalCount = TotalCount + 1;
         }
      }
   }

   multimap<double, string, greater<double> > SortProducts;
   for(map<string, double>::iterator iter = DecayProductCounts.begin(); iter != DecayProductCounts.end(); iter++)
      SortProducts.insert(pair<double, string>(iter->second / TotalCount, iter->first));

   cout << "Tau decay modes (percentage, mode): " << endl;
   for(multimap<double, string, greater<double> >::iterator iter = SortProducts.begin(); iter != SortProducts.end(); iter++)
      cout << setprecision(4) << iter->first << ": " << iter->second << endl;

   return 0;
}


