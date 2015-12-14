#include <iostream>
using namespace std;

#include "Pythia.h"
using namespace Pythia8;

int main()
{
   Pythia pythia;

   pythia.init("run_01_events.lhe");

   pythia.readString("ProcessLevel:all = off");

   int EventIndex = 0;
   while(pythia.next())
   {
      EventIndex = EventIndex + 1;

      if(EventIndex == 0)
      {
         pythia.process.list();
         pythia.event.list();
      }
   }

   cout << "Total number of events: " << EventIndex << endl;

   return 0;
}



