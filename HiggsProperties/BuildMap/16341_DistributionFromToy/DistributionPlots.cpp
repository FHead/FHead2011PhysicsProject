#include <iostream>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TTree.h"
#include "TDirectory.h"

#include "SetStyle.h"

#include "AngleConversion.h"
#include "ProgressBar.h"

class Histograms;
int main();

class Histograms
{
public:
   TH1D *HZ1;
   TH1D *HZ2;
   TH1D *HCosTheta0;
   TH1D *HPhi0;
   TH1D *HCosTheta1;
   TH1D *HCosTheta2;
   TH1D *HPhi;
public:
   Histograms(string Tag)
      : HZ1(NULL), HZ2(NULL), HCosTheta0(NULL)
   {
      HZ1 = new TH1D(Form("HZ1_%s", Tag.c_str()), "", 1000, 0, 20);
      HZ2 = new TH1D(Form("HZ2_%s", Tag.c_str()), "", 1000, 0, 10);
      HCosTheta0 = new TH1D(Form("HCosTheta0_%s", Tag.c_str()), "", 1000, -1, 1);
      HPhi0 = new TH1D(Form("HPhi0_%s", Tag.c_str()), "", 1000, 0, 2 * M_PI);
      HCosTheta1 = new TH1D(Form("HCosTheta1_%s", Tag.c_str()), "", 1000, -1, 1);
      HCosTheta2 = new TH1D(Form("HCosTheta2_%s", Tag.c_str()), "", 1000, -1, 1);
      HPhi = new TH1D(Form("HPhi_%s", Tag.c_str()), "", 1000, 0, 2 * M_PI);
   }
   ~Histograms()
   {
      // We don't own the histograms?
      // if(HZ1 != NULL)   delete HZ1;
      // if(HZ2 != NULL)   delete HZ2;
      // if(HCosTheta0 != NULL)   delete HCosTheta0;
      // if(HPhi0 != NULL)   delete HPhi0;
      // if(HCosTheta1 != NULL)   delete HCosTheta1;
      // if(HCosTheta2 != NULL)   delete HCosTheta2;
      // if(HPhi != NULL)   delete HPhi;
   }
   void Fill(EventParameters Event, double Weight)
   {
      HZ1->Fill(Event.ZMass, Weight);
      HZ2->Fill(Event.Z2Mass, Weight);
      HCosTheta0->Fill(cos(Event.Theta0), Weight);
      HPhi0->Fill(Event.Phi0, Weight);
      HCosTheta1->Fill(cos(Event.Theta1), Weight);
      HCosTheta2->Fill(cos(Event.Theta2), Weight);
      HPhi->Fill(Event.Phi, Weight);
   }
   void Write(TDirectory *Directory = NULL)
   {
      cout << Directory << endl;

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
      
      if(HPhi0 != NULL)
      {
         if(Directory != NULL)
            HPhi0->SetDirectory(Directory);
         HPhi0->Write();
      }
      
      if(HCosTheta1 != NULL)
      {
         if(Directory != NULL)
            HCosTheta1->SetDirectory(Directory);
         HCosTheta1->Write();
      }
      
      if(HCosTheta2 != NULL)
      {
         if(Directory != NULL)
            HCosTheta2->SetDirectory(Directory);
         HCosTheta2->Write();
      }
      
      if(HPhi != NULL)
      {
         if(Directory != NULL)
            HPhi->SetDirectory(Directory);
         HPhi->Write();
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

   TDirectory *A1VVEMPDirectory    = OutputFile.mkdir("A1VVEMP",    "A1VV, P cut, 2e2mu");
   TDirectory *A2VVEMPDirectory    = OutputFile.mkdir("A2VVEMP",    "A2VV, P cut, 2e2mu");
   TDirectory *A3VVEMPDirectory    = OutputFile.mkdir("A3VVEMP",    "A3VV, P cut, 2e2mu");
   TDirectory *A1VVEEPDirectory    = OutputFile.mkdir("A1VVEEP",    "A1VV, P cut, 4e");
   TDirectory *A2VVEEPDirectory    = OutputFile.mkdir("A2VVEEP",    "A2VV, P cut, 4e");
   TDirectory *A3VVEEPDirectory    = OutputFile.mkdir("A3VVEEP",    "A3VV, P cut, 4e");

   Histograms HA1VVEMP("A1VVEMP");
   Histograms HA2VVEMP("A2VVEMP");
   Histograms HA3VVEMP("A3VVEMP");
   Histograms HA1VVEEP("A1VVEEP");
   Histograms HA2VVEEP("A2VVEEP");
   Histograms HA3VVEEP("A3VVEEP");

   int EntryCount = T->GetEntries() * 1.0;

   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(4);

   for(int iE = 0; iE < EntryCount; iE++)
   {
      T->GetEntry(iE);

      Bar.Update(iE);
      Bar.PrintWithMod(200);

      LeptonVectors Leptons;
      if(EMPassP == true || EEPassP == true)
         Leptons = ConvertAnglesToVectorsRoberto(Event);

      if(EMPassP == true)
      {
         EventParameters EMEvent = ConvertVectorsToAnglesRoberto(Leptons.ReorderLeptons2e2mu());

         HA1VVEMP.Fill(EMEvent, Weight * EMA1VV);
         HA2VVEMP.Fill(EMEvent, Weight * EMA2VV);
         HA3VVEMP.Fill(EMEvent, Weight * EMA3VV);
      }
      if(EEPassP == true)
      {
         EventParameters EEEvent = ConvertVectorsToAnglesRoberto(Leptons.ReorderLeptons4e());

         if(EEA1VV < 11e-6)
            HA1VVEEP.Fill(EEEvent, Weight * EEA1VV);
         if(EEA2VV < 1.1e-9)
            HA2VVEEP.Fill(EEEvent, Weight * EEA2VV);
         if(EEA3VV < 0.2e-9)
            HA3VVEEP.Fill(EEEvent, Weight * EEA3VV);
      }
   }

   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   HA1VVEMP.Write(A1VVEMPDirectory);
   HA2VVEMP.Write(A2VVEMPDirectory);
   HA3VVEMP.Write(A3VVEMPDirectory);
   HA1VVEEP.Write(A1VVEEPDirectory);
   HA2VVEEP.Write(A2VVEEPDirectory);
   HA3VVEEP.Write(A3VVEEPDirectory);

   OutputFile.Close();

   File.Close();

   return 0;
}





