#include <iostream>
#include <sstream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      cerr << "Usage: " << argv[0] << " RootFileName" << endl;
      return -1;
   }

   int Run = -1;
   int Event = -1;
   int Lumi = -1;
   int JetCount = 0;
   double PT[1000] = {0};
   double Eta[1000] = {0};
   double Phi[1000] = {0};

   TFile File(argv[1], "RECREATE");

   TTree Tree("T", "Tree");

   Tree.Branch("Run", &Run, "Run/I");
   Tree.Branch("Event", &Event, "Event/I");
   Tree.Branch("Lumi", &Lumi, "Lumi/I");
   Tree.Branch("JetCount", &JetCount, "JetCount/I");
   Tree.Branch("PT", &PT, "PT[JetCount]/D");
   Tree.Branch("Eta", &Eta, "Eta[JetCount]/D");
   Tree.Branch("Phi", &Phi, "Phi[JetCount]/D");

   while(cin)
   {
      char ch[10240] = "";
      cin.getline(ch, 10239, '\n');

      stringstream str(ch);

      int runtemp, eventtemp, lumitemp;
      str >> runtemp >> eventtemp >> lumitemp;

      if(Run == runtemp && Event == eventtemp && Lumi == lumitemp)
      {
         int temp = 0;
         str >> temp;
         str >> PT[JetCount] >> Eta[JetCount] >> Phi[JetCount];
         JetCount = JetCount + 1;
      }
      else
      {
         Tree.Fill();

         Run = runtemp;
         Event = eventtemp;
         Lumi = lumitemp;
         JetCount = 0;
         for(int i = 0; i < 1000; i++)
         {
            PT[i] = 0;
            Eta[i] = 0;
            Phi[i] = 0;
         }
      }
   }

   if(Run > 0)
      Tree.Fill();

   Tree.Write();

   File.Close();

   return 0;
}




