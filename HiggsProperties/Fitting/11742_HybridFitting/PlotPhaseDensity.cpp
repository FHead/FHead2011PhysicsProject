#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TF1.h"

#include "PlotHelper2.h"

int main()
{
   double PI = 3.14159265358979323846;

   TFile File("OutputFile.root");
   TTree *ResultTree = (TTree *)File.Get("ResultTree");

   float A2Phase = 0, A2PhaseError = 0;
   float A3Phase = 0, A3PhaseError = 0;

   ResultTree->SetBranchAddress("A2Phase", &A2Phase);
   ResultTree->SetBranchAddress("A2PhaseError", &A2PhaseError);
   ResultTree->SetBranchAddress("A3Phase", &A3Phase);
   ResultTree->SetBranchAddress("A3PhaseError", &A3PhaseError);
   
   int entry = ResultTree->GetEntries();
   
   string function2 = "0";
   string function3 = "0";
   for(int i = 0; i < entry; i++)
   {
      ResultTree->GetEntry(i);
      
      double A2PrimaryPhase = A2Phase - (int)(A2Phase / 2 / PI) * 2 * PI;
      double A3PrimaryPhase = A3Phase - (int)(A3Phase / 2 / PI) * 2 * PI;
      
      if(A2PrimaryPhase < 0)
         A2PrimaryPhase = A2PrimaryPhase + 2 * PI;
      if(A3PrimaryPhase < 0)
         A3PrimaryPhase = A3PrimaryPhase + 2 * PI;
      
      function2 = function2 + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A2PhaseError, A2PrimaryPhase)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A2PhaseError, A2PrimaryPhase + 2 * PI)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A2PhaseError, A2PrimaryPhase - 2 * PI)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A2PhaseError, A2PrimaryPhase + 4 * PI)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A2PhaseError, A2PrimaryPhase - 4 * PI)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A2PhaseError, A2PrimaryPhase + 6 * PI)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A2PhaseError, A2PrimaryPhase - 6 * PI);
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A2PhaseError, A2PrimaryPhase + 8 * PI);
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A2PhaseError, A2PrimaryPhase - 8 * PI);
      function3 = function3 + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A3PhaseError, A3PrimaryPhase)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A3PhaseError, A3PrimaryPhase + 2 * PI)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A3PhaseError, A3PrimaryPhase - 2 * PI)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A3PhaseError, A3PrimaryPhase + 4 * PI)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A3PhaseError, A3PrimaryPhase - 4 * PI)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A3PhaseError, A3PrimaryPhase + 6 * PI)
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A3PhaseError, A3PrimaryPhase - 6 * PI);
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A3PhaseError, A3PrimaryPhase + 8 * PI);
         + Form("+ROOT::Math::normal_pdf(x,%f,%f)", A3PhaseError, A3PrimaryPhase - 8 * PI);
   }

   TF1 Function2("Function2", function2.c_str(), 0, 2 * PI);
   TF1 Function3("Function3", function3.c_str(), 0, 2 * PI);

   PsFileHelper PsFile("PhasePlots.ps");
   PsFile.AddTextPage("Phase plots");

   TCanvas C;
   ResultTree->Draw("A3PrimaryPhase>>X3(100,0,6.2831853071)", "100/(6.2831853071-0)", "");
   Function3.Draw("same");
   PsFile.AddCanvas(C);
   
   ResultTree->Draw("A2PrimaryPhase>>X2(100,0,6.2831853071)", "100/(6.2831853071-0)", "");
   Function2.Draw("same");
   PsFile.AddCanvas(C);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   File.Close();
}


