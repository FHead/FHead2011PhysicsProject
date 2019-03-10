#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "TF1.h"
#include "TF2.h"
#include "TF3.h"

class JetCorrector
{
private:
   enum Type { TypeNone, TypeJetPT, TypeJetEta, TypeJetPhi, TypeJetArea, TypeRho };
   bool Initialized;
   double JetPT, JetEta, JetPhi, JetArea, Rho;
   std::vector<std::string> Formulas;
   std::vector<std::vector<double>> Parameters;
   std::vector<std::vector<Type>> BinTypes;
   std::vector<std::vector<double>> BinRanges;
   std::vector<std::vector<Type>> Dependencies;
   std::vector<std::vector<double>> DependencyRanges;
public:
   JetCorrector()                  { Initialized = false; }
   JetCorrector(std::string File)  { Initialized = false; Initialize(File); }
   ~JetCorrector()                 {}
   void SetJetPT(double value)     { JetPT = value; }
   void SetJetEta(double value)    { JetEta = value; }
   void SetJetPhi(double value)    { JetPhi = value; }
   void SetJetArea(double value)   { JetArea = value; }
   void SetRho(double value)       { Rho = value; }
   void Initialize(std::string FileName);
   std::vector<std::string> BreakIntoParts(std::string Line);
   bool CheckDefinition(std::string Line);
   std::string StripBracket(std::string Line);
   JetCorrector::Type ToType(std::string Line);
   double GetCorrection();
   double GetCorrectedPT();
   double GetValue(Type T);
};

void JetCorrector::Initialize(std::string FileName)
{
   int nvar = 0, npar = 0;
   std::string CurrentFormula = "";
   std::vector<Type> CurrentDependencies;
   std::vector<Type> CurrentBinTypes;

   std::ifstream in(FileName.c_str());

   while(in)
   {
      char ch[1048576];
      ch[0] = '\0';
      in.getline(ch, 1048577, '\n');

      if(ch[0] == '\0')
         continue;

      bool IsDefinition = CheckDefinition(ch);
      std::vector<std::string> Parts = BreakIntoParts(StripBracket(ch));

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

         CurrentFormula = Parts[nvar+1+npar+1];
         
         CurrentBinTypes.clear();
         for(int i = 0; i < nvar; i++)
            CurrentBinTypes.push_back(ToType(Parts[1+i]));

         CurrentDependencies.clear();
         for(int i = 0; i < npar; i++)
            CurrentDependencies.push_back(ToType(Parts[nvar+2+i]));
      }
      else
      {
         if(Parts.size() <= nvar * 2 + npar * 2 + 1)
            continue;

         Formulas.push_back(CurrentFormula);

         std::vector<double> Parameter;
         for(int i = nvar * 2 + npar * 2 + 1; i < (int)Parts.size(); i++)
            Parameter.push_back(atof(Parts[i].c_str()));
         Parameters.push_back(Parameter);

         Dependencies.push_back(CurrentDependencies);

         std::vector<double> Ranges;
         for(int i = nvar * 2 + 1; i < nvar * 2 + 1 + npar * 2; i++)
            Ranges.push_back(atof(Parts[i].c_str()));
         for(int i = 0; i + 1 < (int)Ranges.size(); i = i + 2)
            if(Ranges[i] > Ranges[i+1])
               std::swap(Ranges[i], Ranges[i+1]);
         DependencyRanges.push_back(Ranges);

         BinTypes.push_back(CurrentBinTypes);

         Ranges.clear();
         for(int i = 0; i < nvar * 2; i++)
            Ranges.push_back(atof(Parts[i].c_str()));
         for(int i = 0; i + 1 < (int)Ranges.size(); i = i + 2)
            if(Ranges[i] > Ranges[i+1])
               std::swap(Ranges[i], Ranges[i+1]);
         BinRanges.push_back(Ranges);
      }
   }

   in.close();

   Initialized = true;
}

std::vector<std::string> JetCorrector::BreakIntoParts(std::string Line)
{
   std::stringstream str(Line);

   std::vector<std::string> Result;

   while(str)
   {
      std::string Temp = "";
      str >> Temp;
      if(Temp == "")
         continue;
      Result.push_back(Temp);
   }

   return Result;
}

bool JetCorrector::CheckDefinition(std::string Line)
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

std::string JetCorrector::StripBracket(std::string Line)
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

JetCorrector::Type JetCorrector::ToType(std::string Line)
{
   if(Line == "JetPt")    return TypeJetPT;
   if(Line == "JetEta")   return TypeJetEta;
   if(Line == "JetPhi")   return TypeJetPhi;
   if(Line == "JetA")     return TypeJetArea;
   if(Line == "Rho")      return TypeRho;

   std::cerr << "[JetCorrector] Warning: variable type " << Line << " not found!" << std::endl;

   return TypeNone;
}

double JetCorrector::GetCorrection()
{
   if(Initialized == false)
      return -1;

   int N = Formulas.size();

   for(int iE = 0; iE < N; iE++)
   {
      bool InBin = true;

      for(int iB = 0; iB < (int)BinTypes[iE].size(); iB++)
      {
         double Value = GetValue(BinTypes[iE][iB]);
         if(Value < BinRanges[iE][iB*2] || Value > BinRanges[iE][iB*2+1])
            InBin = false;
      }

      if(InBin == false)
         continue;

      if(Dependencies[iE].size() == 0)
         return -1;   // huh?
      if(Dependencies[iE].size() > 3)
      {
         std::cerr << "[JetCorrector] There are " << Dependencies[iE].size() << " parameters!" << std::endl;
         return -1;   // huh?
      }

      double V[3] = {0, 0, 0};
      for(int i = 0; i < 3; i++)
      {
         if(Dependencies[iE].size() <= i)
            continue;
         
         double Value = GetValue(Dependencies[iE][i]);
         if(Value < DependencyRanges[iE][i*2])
            Value = DependencyRanges[iE][i*2];
         if(Value > DependencyRanges[iE][i*2+1])
            Value = DependencyRanges[iE][i*2+1];
         V[i] = Value;
      }

      TF1 *Function = NULL;
      
      if(Dependencies[iE].size() == 1)
         Function = new TF1("Function", Formulas[iE].c_str());
      if(Dependencies[iE].size() == 2)
         Function = new TF2("Function", Formulas[iE].c_str());
      if(Dependencies[iE].size() == 3)
         Function = new TF3("Function", Formulas[iE].c_str());
         
      for(int i = 0; i < (int)Parameters[iE].size(); i++)
         Function->SetParameter(i, Parameters[iE][i]);
      double Result = Function->EvalPar(V);

      delete Function;
      return Result;
   }

   return -1;
}

double JetCorrector::GetCorrectedPT()
{
   double Correction = GetCorrection();

   if(Correction < 0)
      return -1;

   return JetPT * Correction;
}

double JetCorrector::GetValue(Type T)
{
   if(T == TypeNone)      return 0;
   if(T == TypeJetPT)     return JetPT;
   if(T == TypeJetEta)    return JetEta;
   if(T == TypeJetPhi)    return JetPhi;
   if(T == TypeJetArea)   return JetArea;
   if(T == TypeRho)       return Rho;

   return -1;
}


