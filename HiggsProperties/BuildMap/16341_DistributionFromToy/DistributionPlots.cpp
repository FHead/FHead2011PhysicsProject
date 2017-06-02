#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TDirectory.h"

#include "SetStyle.h"

#include "AngleConversion.h"

class Histograms;
int main();

class Histograms
{
public:
   TH1D *HZ1;
   TH1D *HZ2;
   TH1D *HCosTheta0;
public:
   Histograms(string Tag)
      : HZ1(NULL), HZ2(NULL), HCosTheta0(NULL)
   {
      HZ1 = new TH1D(Form("HZ1_%s", Tag.c_str()), "", 50, 0, 20);
      HZ2 = new TH1D(Form("HZ2_%s", Tag.c_str()), "", 50, 0, 20);
      HCosTheta0 = new TH1D(Form("HCosTheta0_%s", Tag.c_str()), "", 50, -1, 1);
   }
   ~Histograms()
   {
      // We don't own the histograms?
      // if(HZ1 != NULL)   delete HZ1;
      // if(HZ2 != NULL)   delete HZ2;
      // if(HCosTheta0 != NULL)   delete HCosTheta0;
   }
   void Fill(EventParameters Event, double Weight)
   {
      HZ1->Fill(Event.ZMass, Weight);
      HZ2->Fill(Event.Z2Mass, Weight);
      HCosTheta0->Fill(cos(Event.Theta0), Weight);
   }
   void Write(TDirectory *Directory = NULL)
   {
      if(HZ1 != NULL)
      {
         if(Directory != NULL)
            HZ1->SetDirectory(Directory);
         HZ1->Write();
      }
      
      if(HZ2 != NULL)
      {
         if(Directory != NULL)
            HZ2->SetDirectory(Directory);
         HZ2->Write();
      }
      
      if(HCosTheta0 != NULL)
      {
         if(Directory != NULL)
            HCosTheta0->SetDirectory(Directory);
         HCosTheta0->Write();
      }
   }
};

int main()
{
   SetThesisStyle();

   TFile File("Result/CombinedResult.root");

   TTree *T = (TTree *)File.Get("T");

   EventParameters Event;
   T->SetBranchAddress("HMass", &Event.HMass);
   T->SetBranchAddress("ZMass", &Event.ZMass);
   T->SetBranchAddress("Z2Mass", &Event.Z2Mass);
   T->SetBranchAddress("Theta0", &Event.Theta0);
   T->SetBranchAddress("Phi0", &Event.Phi0);
   T->SetBranchAddress("Theta1", &Event.Theta1);
   T->SetBranchAddress("Theta2", &Event.Theta2);
   T->SetBranchAddress("Phi", &Event.Phi);

   double Weight, EMA1VV, EMA2VV, EMA3VV, EEA1VV, EEA2VV, EEA3VV;
   T->SetBranchAddress("Weight", &Weight);
   T->SetBranchAddress("EMA1VV", &EMA1VV);
   T->SetBranchAddress("EMA2VV", &EMA2VV);
   T->SetBranchAddress("EMA3VV", &EMA3VV);
   T->SetBranchAddress("EEA1VV", &EEA1VV);
   T->SetBranchAddress("EEA2VV", &EEA2VV);
   T->SetBranchAddress("EEA3VV", &EEA3VV);

   bool EMPassP, EMPassF, EEPassP, EEPassF;
   T->SetBranchAddress("EMPassP", &EMPassP);
   T->SetBranchAddress("EMPassF", &EMPassF);
   T->SetBranchAddress("EEPassP", &EEPassP);
   T->SetBranchAddress("EEPassF", &EEPassF);

   TFile OutputFile("Histograms.root", "RECREATE");

   TDirectory *A1VVPDirectory    = OutputFile.mkdir("A1VVP",    "A1VV, P cut");

   Histograms HA1VVP("A1VVP");

   int EntryCount = T->GetEntries();
   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      if(EMPassP == true)
         HA1VVP.Fill(Event, Weight * EMA1VV);
   }

   HA1VVP.Write(A1VVPDirectory);

   OutputFile.Close();

   File.Close();

   return 0;
}





