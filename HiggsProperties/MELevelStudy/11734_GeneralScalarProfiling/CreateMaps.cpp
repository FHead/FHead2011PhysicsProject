#include <iostream>
using namespace std;

#include "TH2D.h"

#include "Code/TauHelperFunctions2.h"
#include "PlotHelper2.h"
#include "Code/DrawRandom.h"

#include "AngleConversion.h"
#include "CalculateME.h"

int main();

void FillHistogram(TH2D &H, double (*F)(LeptonVectors &, const GeneralScalarParameters &));
void IncrementParameter(GeneralScalarParameters &parameters, int index);
void EmptyParameter(GeneralScalarParameters &parameters);
void SetLabel(TH2D &H);

int main()
{
   vector<TH2D *> Parts;

   TH2D HPart2("HPart2", "Part2", 14, 0, 14, 14, 0, 14);      Parts.push_back(&HPart2); 
   TH2D HPart3("HPart3", "Part3", 14, 0, 14, 14, 0, 14);      Parts.push_back(&HPart3);
   TH2D HPart5("HPart5", "Part5", 14, 0, 14, 14, 0, 14);      Parts.push_back(&HPart5);
   TH2D HPart7("HPart7", "Part7", 14, 0, 14, 14, 0, 14);      Parts.push_back(&HPart7);
   TH2D HPart8("HPart8", "Part8", 14, 0, 14, 14, 0, 14);      Parts.push_back(&HPart8);
   TH2D HPart9("HPart9", "Part9", 14, 0, 14, 14, 0, 14);      Parts.push_back(&HPart9);
   TH2D HPart10("HPart10", "Part10", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart10); 
   TH2D HPart11("HPart11", "Part11", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart11);
   TH2D HPart12("HPart12", "Part12", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart12);
   TH2D HPart14("HPart14", "Part14", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart14);
   TH2D HPart15("HPart15", "Part15", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart15);
   TH2D HPart17("HPart17", "Part17", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart17);
   TH2D HPart20("HPart20", "Part20", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart20); 
   TH2D HPart21("HPart21", "Part21", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart21);
   TH2D HPart22("HPart22", "Part22", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart22);
   TH2D HPart23("HPart23", "Part23", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart23);
   TH2D HPart24("HPart24", "Part24", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart24);
   TH2D HPart26("HPart26", "Part26", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart26);
   TH2D HPart27("HPart27", "Part27", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart27); 
   TH2D HPart29("HPart29", "Part29", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart29);
   TH2D HPart32("HPart32", "Part32", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart32);
   TH2D HPart33("HPart33", "Part33", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart33);
   TH2D HPart34("HPart34", "Part34", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart34);
   TH2D HPart35("HPart35", "Part35", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart35);
   TH2D HPart36("HPart36", "Part36", 14, 0, 14, 14, 0, 14);   Parts.push_back(&HPart36);

   FillHistogram(HPart2, GetGeneralScalar4e_Part2);
   FillHistogram(HPart3, GetGeneralScalar4e_Part3);
   FillHistogram(HPart5, GetGeneralScalar4e_Part5);
   FillHistogram(HPart7, GetGeneralScalar4e_Part7);
   FillHistogram(HPart8, GetGeneralScalar4e_Part8);
   FillHistogram(HPart9, GetGeneralScalar4e_Part9);
   FillHistogram(HPart10, GetGeneralScalar4e_Part10);
   FillHistogram(HPart11, GetGeneralScalar4e_Part11);
   FillHistogram(HPart12, GetGeneralScalar4e_Part12);
   FillHistogram(HPart14, GetGeneralScalar4e_Part14);
   FillHistogram(HPart15, GetGeneralScalar4e_Part15);
   FillHistogram(HPart17, GetGeneralScalar4e_Part17);
   FillHistogram(HPart20, GetGeneralScalar4e_Part20);
   FillHistogram(HPart21, GetGeneralScalar4e_Part21);
   FillHistogram(HPart22, GetGeneralScalar4e_Part22);
   FillHistogram(HPart23, GetGeneralScalar4e_Part23);
   FillHistogram(HPart24, GetGeneralScalar4e_Part24);
   FillHistogram(HPart26, GetGeneralScalar4e_Part26);
   FillHistogram(HPart27, GetGeneralScalar4e_Part27);
   FillHistogram(HPart29, GetGeneralScalar4e_Part29);
   FillHistogram(HPart32, GetGeneralScalar4e_Part32);
   FillHistogram(HPart33, GetGeneralScalar4e_Part33);
   FillHistogram(HPart34, GetGeneralScalar4e_Part34);
   FillHistogram(HPart35, GetGeneralScalar4e_Part35);
   FillHistogram(HPart36, GetGeneralScalar4e_Part36);

   PsFileHelper PsFile("Meow.ps");
   PsFile.AddTextPage("Meow!");

   PsFile.AddPlot(HPart2, "colz");
   PsFile.AddPlot(HPart3, "colz");
   PsFile.AddPlot(HPart5, "colz");
   PsFile.AddPlot(HPart7, "colz");
   PsFile.AddPlot(HPart8, "colz");
   PsFile.AddPlot(HPart9, "colz");
   PsFile.AddPlot(HPart10, "colz");
   PsFile.AddPlot(HPart11, "colz");
   PsFile.AddPlot(HPart12, "colz");
   PsFile.AddPlot(HPart14, "colz");
   PsFile.AddPlot(HPart15, "colz");
   PsFile.AddPlot(HPart17, "colz");
   PsFile.AddPlot(HPart20, "colz");
   PsFile.AddPlot(HPart21, "colz");
   PsFile.AddPlot(HPart22, "colz");
   PsFile.AddPlot(HPart23, "colz");
   PsFile.AddPlot(HPart24, "colz");
   PsFile.AddPlot(HPart26, "colz");
   PsFile.AddPlot(HPart27, "colz");
   PsFile.AddPlot(HPart29, "colz");
   PsFile.AddPlot(HPart32, "colz");
   PsFile.AddPlot(HPart33, "colz");
   PsFile.AddPlot(HPart34, "colz");
   PsFile.AddPlot(HPart35, "colz");
   PsFile.AddPlot(HPart36, "colz");

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

void FillHistogram(TH2D &H, double (*F)(LeptonVectors &, const GeneralScalarParameters &))
{
   SetLabel(H);
   H.SetStats(0);

   srand(31426);

   for(int iEntry = 0; iEntry < 10000; iEntry++)
   {
      EventParameters Event;
      Event.HMass = 125;
      Event.ZMass = DrawRandom(80, 100);
      Event.Z2Mass = DrawRandom(10, 25);
      Event.Phi0 = DrawRandom(-PI, PI);
      Event.Theta0 = acos(DrawRandom(-1, 1));
      Event.Phi = DrawRandom(-PI, PI);
      Event.Theta1 = acos(DrawRandom(-1, 1));
      Event.Theta2 = acos(DrawRandom(-1, 1));

      LeptonVectors Leptons = ConvertAnglesToVectorsRoberto(Event);

      for(int i = 0; i < 14; i++)
      {
         GeneralScalarParameters parameter;
         EmptyParameter(parameter);
         IncrementParameter(parameter, i);

         H.Fill(i, i, fabs(F(Leptons, parameter)) * 1e10);
      }

      for(int i = 0; i < 14; i++)
      {
         for(int j = i + 1; j < 14; j++)
         {
            GeneralScalarParameters parameterA, parameterB, parameterC;
            EmptyParameter(parameterA);
            EmptyParameter(parameterB);
            EmptyParameter(parameterC);

            IncrementParameter(parameterA, i);
            IncrementParameter(parameterA, j);
            IncrementParameter(parameterB, i);
            IncrementParameter(parameterC, j);
         
            double Value = fabs(F(Leptons, parameterA) - F(Leptons, parameterB) - F(Leptons, parameterC)) * 1e10;
            H.Fill(i, j, Value);
            H.Fill(j, i, Value);
         }
      }
   }
}

void IncrementParameter(GeneralScalarParameters &parameters, int index)
{
   switch(index)
   {
      case 0:
         parameters.ahR = parameters.ahR + 1;
         break;
      case 1:
         parameters.ahI = parameters.ahI + 1;
         break;
      case 2:
         parameters.aZR = parameters.aZR + 1;
         break;
      case 3:
         parameters.aZI = parameters.aZI + 1;
         break;
      case 4:
         parameters.aZdR = parameters.aZdR + 1;
         break;
      case 5:
         parameters.aZdI = parameters.aZdI + 1;
         break;
      case 6:
         parameters.aZAR = parameters.aZAR + 1;
         break;
      case 7:
         parameters.aZAI = parameters.aZAI + 1;
         break;
      case 8:
         parameters.aZAdR = parameters.aZAdR + 1;
         break;
      case 9:
         parameters.aZAdI = parameters.aZAdI + 1;
         break;
      case 10:
         parameters.aAR = parameters.aAR + 1;
         break;
      case 11:
         parameters.aAI = parameters.aAI + 1;
         break;
      case 12:
         parameters.aAdR = parameters.aAdR + 1;
         break;
      case 13:
         parameters.aAdI = parameters.aAdI + 1;
         break;
      default:
         break;
   }
}

void EmptyParameter(GeneralScalarParameters &parameters)
{
   parameters.ahR = 0;     parameters.ahI = 0;
   parameters.aZR = 0;     parameters.aZI = 0;
   parameters.aZdR = 0;    parameters.aZdI = 0;
   parameters.aZAR = 0;    parameters.aZAI = 0;
   parameters.aZAdR = 0;   parameters.aZAdI = 0;
   parameters.aAR = 0;     parameters.aAI = 0;
   parameters.aAdR = 0;    parameters.aAdI = 0;
}

void SetLabel(TH2D &H)
{
   string Labels[] = {"A1ZZR", "A1ZZI", "A2ZZR", "A2ZZI", "A3ZZR", "A3ZZI",
      "A2ZAR", "A2ZAI", "A3ZAR", "A3ZAI", "A2AAR", "A2AAI", "A3AAR", "A3AAI"};

   for(int i = 1; i <= 14; i++)
   {
      H.GetXaxis()->SetBinLabel(i, Labels[i-1].c_str());
      H.GetYaxis()->SetBinLabel(i, Labels[i-1].c_str());
   }
}

