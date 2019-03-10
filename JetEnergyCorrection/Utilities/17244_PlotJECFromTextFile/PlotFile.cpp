#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

#include "TF1.h"
#include "TCanvas.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main(int argc, char *argv[]);
vector<string> BreakIntoParts(string Line);
bool CheckDefinition(string Line);
string StripBracket(string Line);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   /*
   string FileName = "Simple_L1FastJet_AK4PFchs.txt";
   int ParameterCount = 3;
   char ToReplace[] = {'x', 'y', 'z'};
   string DefaultParameters[] = {"20", "100", "1"};
   int ToPlotIndex = 1;
   */
   
   string FileName = "MC2017_L2Relative_AK4PFchsl1.txt";
   int ParameterCount = 1;
   char ToReplace[] = {'x'};
   string DefaultParameters[] = {"1"};
   int ToPlotIndex = 0;
   
   double XMin = 1;
   double XMax = 1000;

   vector<string> Labels;
   vector<string> Formulas;
   vector<vector<double>> Parameters;
   int nvar = 0, npar = 0;
   string CurrentFormula = "";

   ifstream in(FileName.c_str());

   while(in)
   {
      char ch[1048576];
      ch[0] = '\0';
      in.getline(ch, 1048577, '\n');

      if(ch[0] == '\0')
         continue;

      bool IsDefinition = CheckDefinition(ch);
      vector<string> Parts = BreakIntoParts(StripBracket(ch));

      if(Parts.size() == 0)
         continue;

      if(IsDefinition == true)
      {
         nvar = atoi(Parts[0].c_str());
         if(Parts.size() <= nvar + 1)
            continue;
         npar = atoi(Parts[nvar+1].c_str());
         if(Parts.size() <= nvar + 1 + npar + 1)
            continue;

         cout << ch << endl;
         cout << nvar << " " << npar << " " << Parts[nvar+1+npar+1] << endl;

         CurrentFormula = Parts[nvar+1+npar+1];

         for(int i = 0; i < (int)CurrentFormula.size(); i++)
         {
            for(int j = 0; j < ParameterCount; j++)
            {
               if(CurrentFormula[i] == ToReplace[j])
               {
                  if(i != 0 && CurrentFormula[i-1] >= 'A' && CurrentFormula[i-1] <= 'Z')
                     continue;
                  if(i != 0 && CurrentFormula[i-1] >= 'a' && CurrentFormula[i-1] <= 'z')
                     continue;
                  if(i != CurrentFormula.size() - 1 && CurrentFormula[i+1] >= 'A' && CurrentFormula[i+1] <= 'Z')
                     continue;
                  if(i != CurrentFormula.size() - 1 && CurrentFormula[i+1] >= 'a' && CurrentFormula[i+1] <= 'z')
                     continue;

                  CurrentFormula.erase(CurrentFormula.begin() + i);
                  string ReplaceTo = "x";
                  if(j != ToPlotIndex)
                     ReplaceTo = DefaultParameters[j];
                  CurrentFormula.insert(i, ReplaceTo);
               }
            }
         }
      }
      else
      {
         if(Parts.size() <= nvar * 2 + npar * 2 + 1)
            continue;

         Formulas.push_back(CurrentFormula);
         vector<double> Parameter;
         for(int i = nvar * 2 + npar * 2 + 1; i < (int)Parts.size(); i++)
            Parameter.push_back(atof(Parts[i].c_str()));
         Parameters.push_back(Parameter);

         string Label = "Bin: ";
         for(int i = 0; i < nvar * 2; i = i + 2)
            Label = Label + " (" + Parts[i] + " - " + Parts[i+1] + ")";
         Labels.push_back(Label);
      }
   }

   in.close();

   PdfFileHelper PdfFile("AllCurves.pdf");
   PdfFile.AddTextPage(FileName);

   vector<TF1 *> Functions;

   for(int i = 0; i < (int)Formulas.size(); i++)
   {
      Functions.push_back(new TF1(Form("Function%d", i), Formulas[i].c_str(), XMin, XMax));
      for(int j = 0; j < (int)Parameters[i].size(); j++)
         Functions[i]->SetParameter(j, Parameters[i][j]);
      Functions[i]->SetTitle(Labels[i].c_str());

      PdfFile.AddPlot(Functions[i], "", false, false, true, true);
   }

   for(int i = 0; i < (int)Functions.size(); i++)
      delete Functions[i];

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

vector<string> BreakIntoParts(string Line)
{
   stringstream str(Line);

   vector<string> Result;

   while(str)
   {
      string Temp = "";
      str >> Temp;
      if(Temp == "")
         continue;
      Result.push_back(Temp);
   }

   return Result;
}

bool CheckDefinition(string Line)
{
   for(int i = 0; i < (int)Line.size(); i++)
   {
      if(Line[i] == '{')
         return true;
      if(Line[i] == ' ')
         continue;
      return false;
   }

   return false;
}

string StripBracket(string Line)
{
   for(int i = 0; i < (int)Line.size(); i++)
   {
      if(Line[i] == '{' || Line[i] == '}')
      {
         Line.erase(Line.begin() + i);
         i = i - 1;
      }
   }

   return Line;
}

