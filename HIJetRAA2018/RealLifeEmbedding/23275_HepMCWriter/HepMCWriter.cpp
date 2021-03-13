#include <map>
#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "Code/DrawRandom.h"
#include "CommandLine.h"

#define MAX 10000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string Input = CL.Get("input");
   string Output = CL.Get("output");
   double Fraction = CL.GetDouble("fraction", 0.01);

   TFile File(Input.c_str());
   TTree *Tree = (TTree *)File.Get("MorphedTree");

   int N = 0;
   double E[MAX], PX[MAX], PY[MAX], PZ[MAX];
   int PID[MAX], Status[MAX];
   Tree->SetBranchAddress("N", &N);
   Tree->SetBranchAddress("PX", &PX);
   Tree->SetBranchAddress("PY", &PY);
   Tree->SetBranchAddress("PZ", &PZ);
   Tree->SetBranchAddress("PID", &PID);
   Tree->SetBranchAddress("Status", &Status);

   ofstream out(Output);

   out << "HepMC::Version 2.06.05" << endl;
   out << "HepMC::IO_GenEvent-START_EVENT_LISTING" << endl;

   map<int, double> Mass;
   Mass[11] = 0.000510998910;
   Mass[12] = 0;
   Mass[13] = 0.1056583688;
   Mass[14] = 0;
   Mass[15] = 1.77684;
   Mass[16] = 0;
   Mass[22] = 0;
   Mass[111] = 0.1349766;   // pi0
   Mass[211] = 0.13957018;  // pi+
   Mass[299] = 0.15;        // Grass
   Mass[130] = 0.497611;    // K_L
   Mass[310] = 0.497611;    // K_S
   Mass[321] = 0.493677;    // K+
   Mass[2112] = 0.939565;   // neutron
   Mass[2212] = 0.93827;    // proton
   Mass[3112] = 1.197449;   // sigma-
   Mass[3122] = 1.115683;   // Lambda
   Mass[3312] = 1.32171;    // Xi-
   Mass[3322] = 1.31486;    // Xi0
   Mass[3212] = 1.192642;   // sigma0
   Mass[3222] = 1.18937;    // sigma+
   Mass[3334] = 1.67245;    // Omega

   int EntryCount = Tree->GetEntries() * Fraction;
   for(int iE = 0; iE < EntryCount; iE++)
   {
      Tree->GetEntry(iE);
   
      int NParticle = 0;
      for(int i = 0; i < N; i++)
         if(Status[i] == 1)
            NParticle = NParticle + 1;

      out << "E " << iE + 1 << " -1  0 0 0  0 0 1  1 2  0 1 1" << endl;
      out << "N 1 \"0\"" << endl;
      out << "U GEV MM" << endl;
      out << "C 1000000 0" << endl;
      out << "H 0 0 0 0 0 0 0 0 0 0 0 0 0" << endl;
      out << "F 0 0 0.1 0.1 100 0.1 0.1 0 0" << endl;
      out << "V -1 0  0 0 0 0  2 " << NParticle << " 0" << endl;
      out << "P 1  2212  0 0  2510 2510 0.938300E+00 2 0 0 -1 0" << endl;
      out << "P 2  2212  0 0 -2510 2510 0.938300E+00 2 0 0 -1 0" << endl;

      int Index = 3;
      for(int i = 0; i < N; i++)
      {
         if(Status[i] != 1)
            continue;

         if(PID[i] == 299 || PID[i] == -299)
         {
            double Check = DrawRandom(0, 3);
            if(Check < 1)
               PID[i] = 211;
            else if(Check < 2)
               PID[i] = -211;
            else
               PID[i] = 111;
         }

         if(Mass.find(abs(PID[i])) == Mass.end())
            cout << "PID " << PID[i] << " need mass!" << endl;

         out << "P " << Index << " " << PID[i];
         out << " " << PX[i] << " " << PY[i] << " " << PZ[i] << " " << E[i];
         out << " " << Mass[abs(PID[i])];
         out << " 1 0 0 0 0" << endl;

         Index = Index + 1;
      }
   }

   out << "HepMC::IO_GenEvent-END_EVENT_LISTING" << endl;

   File.Close();

   return 0;
}



