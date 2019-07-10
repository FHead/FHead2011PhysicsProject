#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#include "CommandLine.h"
#include "CustomAssert.h"

#define Tolerance 0.0001

class Record;
int main(int argc, char *argv[]);
double GetAverage(CommandLine &CL);
double Evaluate(double x, double R0, double XL, double XR);
string FindHeader(string FileName);
string GetFormula(string FileName);
string ModifyFormula(string F1, string F2);
string ToString(int Number);
string GetG(CommandLine &CL);
string GenerateNewHeader(string FileName, string NewFormula);
Record ParseRecord(string Line, int NBin, int NPar);
vector<Record> ParseFile(string FileName);
void SplitUp(vector<Record> &R1, vector<Record> &R2);
void GenerateTextFile(string FileName, string Header, vector<Record> R1, vector<Record> R2);

class Record
{
public:
   int NBin;
   vector<double> BinMin;
   vector<double> BinMax;
   int NPar;
   vector<double> ParMin;
   vector<double> ParMax;
   vector<double> TheRest;
public:
   Record() {}
   ~Record() {}
   bool operator <(const Record &other) const
   {
      if(NBin < other.NBin)   return true;
      if(NBin > other.NBin)   return false;
      
      for(int i = 0; i < NBin; i++)
      {
         if(BinMin[i] < other.BinMin[i])
            return true;
         if(BinMin[i] > other.BinMin[i])
            return false;
         
         if(BinMax[i] < other.BinMax[i])
            return true;
         if(BinMax[i] > other.BinMax[i])
            return false;
      }

      if(NPar < other.NPar)   return true;
      if(NPar > other.NPar)   return false;
      
      for(int i = 0; i < NPar; i++)
      {
         if(ParMin[i] < other.ParMin[i])
            return true;
         if(ParMin[i] > other.ParMin[i])
            return false;
         
         if(ParMax[i] < other.ParMax[i])
            return true;
         if(ParMax[i] > other.ParMax[i])
            return false;
      }

      if(TheRest.size() < other.TheRest.size())
         return true;
      if(TheRest.size() > other.TheRest.size())
         return false;

      for(int i = 0; i < (int)TheRest.size(); i++)
      {
         if(TheRest[i] < other.TheRest[i])   return true;
         if(TheRest[i] > other.TheRest[i])   return false;
      }

      return false;
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string OutsideFileName = CL.Get("OutsideFileName");
   string InsideFileName = CL.Get("InsideFileName");
   string OutputFileName = CL.Get("Output");

   double Average = GetAverage(CL);
   char C[1024];
   sprintf(C, "%.6f", Average);

   string Formula1 = GetFormula(OutsideFileName);
   string Formula2 = GetFormula(InsideFileName);

   cout << "Formula1 = " << Formula1 << endl;
   cout << "Formula2 = " << Formula2 << endl;

   Formula2 = ModifyFormula(Formula1, Formula2);
   
   cout << "Modified formula2 = " << Formula2 << endl;

   string G = GetG(CL);

   string NewFormula = Formula1 + "-" + "(" + Formula2 + "-" + Formula1 + ")/" + C + "*" + G;

   cout << "Combined formula = " << NewFormula << endl;

   string NewHeader = GenerateNewHeader(OutsideFileName, NewFormula);

   cout << "New Header:" << endl;
   cout << NewHeader << endl;

   vector<Record> LinesOutside = ParseFile(OutsideFileName);
   vector<Record> LinesInside = ParseFile(InsideFileName);

   cout << "Number of bins in outside region = " << LinesOutside.size() << endl;
   // cout << "First bin in outside region: " << endl;
   // cout << "   " << LinesOutside[0].NBin << endl;
   // cout << "   " << LinesOutside[0].NPar << endl;
   // cout << "   " << LinesOutside[0].TheRest.size() << endl;
   // cout << "     ";
   // for(int i = 0; i < (int)LinesOutside[0].TheRest.size(); i++)
   //    cout << " " << LinesOutside[0].TheRest[i];
   // cout << endl;
   
   cout << "Number of bins in inside region = " << LinesInside.size() << endl;

   SplitUp(LinesInside, LinesOutside);
   
   cout << "Number of bins in outside region after splitting = " << LinesOutside.size() << endl;
   cout << "Number of bins in inside region after splitting = " << LinesInside.size() << endl;

   double MinEta = CL.GetDouble("MinEta");
   double MaxEta = CL.GetDouble("MaxEta");
   double R0 = CL.GetDouble("R0");

   for(int i = 0; i < (int)LinesInside.size(); i++)
   {
      if(LinesInside[i].BinMin[0] - R0 > MaxEta)
         LinesInside[i] = LinesOutside[i];
      if(LinesInside[i].BinMax[0] + R0 < MinEta)
         LinesInside[i] = LinesOutside[i];
   }

   GenerateTextFile(OutputFileName, NewHeader, LinesOutside, LinesInside);

   return 0;
}

double GetAverage(CommandLine &CL)
{
   double PhiMin = CL.GetDouble("PhiMin", -1.8);
   double PhiMax = CL.GetDouble("PhiMax", -0.4);
   double HEMPhiMin = CL.GetDouble("HEMPhiMin", -1.6);
   double HEMPhiMax = CL.GetDouble("HEMPhiMax", -0.9);
   double R0 = CL.GetDouble("R0", 0.4);
   int N = CL.GetInt("N", 1000000);

   double Sum = 0;

   for(int i = 0; i < N; i++)
   {
      double Phi = (PhiMax - PhiMin) / N * (i + 0.5) + PhiMin;

      // if(i % 10000 == 0)
      //    cout << Phi << " " << Evaluate(Phi, R0, HEMPhiMin, HEMPhiMax) << endl;

      Sum = Sum + Evaluate(Phi, R0, HEMPhiMin, HEMPhiMax);
   }

   cout << "Average is " << Sum / N << endl;

   return Sum / N;
}

double Evaluate(double x, double R0, double XL, double XR)
{
   double Result = -1;

   double R = (XR - x) / R0;
   Result = Result + (acos(max(-1.0, min(1.0, R))) - R * sqrt(1 - min(1.0, R * R))) / M_PI;
   
   R = (x - XL) / R0;
   Result = Result + (acos(max(-1.0, min(1.0, R))) - R * sqrt(1 - min(1.0, R * R))) / M_PI;

   return -Result;
}

string FindHeader(string FileName)
{
   ifstream in(FileName);

   char ch[10240];
   while(in)
   {
      ch[0] = '\0';
      in.getline(ch, 10239, '\n');

      bool Found = false;
      for(int i = 0; ch[i] != '\0' && i < 10240; i++)
      {
         if(ch[i] == ' ')
            continue;
         else if(ch[i] == '{')
            Found = true;
         else
            break;
      }
      if(Found == true)
         break;
   }
   
   in.close();

   for(int i = 0; ch[i] != '\0' && i < 10240; i++)
      if(ch[i] == '{' || ch[i] =='}')
         ch[i] = ' ';

   return ch;
}

string GetFormula(string FileName)
{
   string Header = FindHeader(FileName);
   stringstream str(Header);

   // Assume the two text files have the same dependencies for now
   int NBin = 0, NPar = 0;
   string Dummy = "";

   str >> NBin;
   for(int i = 0; i < NBin; i++)
      str >> Dummy;
   str >> NPar;
   for(int i = 0; i < NPar; i++)
      str >> Dummy;

   string Result = "1";
   str >> Result;

   return "(" + Result + ")";
}

string ModifyFormula(string F1, string F2)
{
   // Count number of parameters in F1
   int N = 0;
   for(int i = 0; i < F1.size(); i++)
      if(F1[i] == ']')
         N = N + 1;

   // Increment parameter in F2
   for(int i = 0; i < F2.size(); i++)
   {
      if(F2[i] != '[')
         continue;

      int Start = i + 1;
      int End = -1;

      for(int j = i + 1; j < F2.size(); j++)
      {
         if(F2[j] == ']')
         {
            End = j;
            break;
         }
      }

      Assert(End != -1, "Something is wrong in modifying formula");

      int Number = atoi(F2.substr(Start, End - Start).c_str()) + N;

      F2.erase(Start, End - Start);
      F2.insert(Start, ToString(Number));
   }

   return F2;
}

string ToString(int Number)
{
   char ch[1024];
   ch[0] = '\0';
   sprintf(ch, "%d", Number);
   return ch;
}

string GetG(CommandLine &CL)
{
   double XL = CL.GetDouble("HEMPhiMin");
   double XR = CL.GetDouble("HEMPhiMax");
   double R0 = CL.GetDouble("R0");

   char R1[1024], R2[1024];
   char G1[1024], G2[1024];

   if(XR > 0)   sprintf(R1, "(%.2f-t)/%.2f", XR, R0);
   else         sprintf(R1, "(%.2f-t)/%.2f", XR, R0);
   sprintf(G1, "(acos(max(-1.0,min(1.0,%s)))-%s*sqrt(1-min(1.0,%s*%s)))/TMath::Pi()", R1, R1, R1, R1);
   if(XL > 0)   sprintf(R2, "(t-%.2f)/%.2f", XL, R0);
   else         sprintf(R2, "(t+%.2f)/%.2f", -XL, R0);
   sprintf(G2, "(acos(max(-1.0,min(1.0,%s)))-%s*sqrt(1-min(1.0,%s*%s)))/TMath::Pi()", R2, R2, R2, R2);

   string G = string("(") + G1 + "+" + G2 + "-1)";

   return G;
}

string GenerateNewHeader(string FileName, string NewFormula)
{
   string Header = FindHeader(FileName);
   stringstream str(Header);
   stringstream Result;
   Result << "{";

   int NBin = 0, NPar = 0;
   string Dummy = "";

   str >> NBin;
   Result << NBin;

   for(int i = 0; i < NBin; i++)
   {
      str >> Dummy;
      Result << " " << Dummy;
   }
   
   str >> NPar;
   Result << " " << NPar + 1;
   
   for(int i = 0; i < NPar; i++)
   {
      str >> Dummy;
      Result << " " << Dummy;
   }
   Result << " " << "JetPhi";

   str >> Dummy;
   Result << " " << NewFormula;

   while(str)
   {
      Dummy = "";
      str >> Dummy;
      if(Dummy != "")
         Result << " " << Dummy;
   }

   Result << "}";

   return Result.str();
}

Record ParseRecord(string Line, int NBin, int NPar)
{
   Record Result;

   Result.NBin = NBin;
   Result.NPar = NPar;

   stringstream str(Line);

   for(int i = 0; i < NBin; i++)
   {
      double Min = -1;
      double Max = -1;
      str >> Min >> Max;

      Result.BinMin.push_back(Min);
      Result.BinMax.push_back(Max);
   }

   int N = 0;
   str >> N;

   for(int i = 0; i < NPar; i++)
   {
      double Min = -1;
      double Max = -1;
      str >> Min >> Max;

      Result.ParMin.push_back(Min);
      Result.ParMax.push_back(Max);
   }

   for(int i = 0; i < N - NPar * 2; i++)
   {
      double Dummy = -1;
      str >> Dummy;

      Result.TheRest.push_back(Dummy);
   }

   return Result;
}

vector<Record> ParseFile(string FileName)
{
   vector<Record> Result;

   ifstream in(FileName);

   int NBin = 0;
   int NPar = 0;

   while(in)
   {
      char ch[10240];
      ch[0] = '\0';

      in.getline(ch, 10239, '\n');

      if(ch[0] == '\0')
         continue;

      bool IsHeader = false;
      for(int i = 0; i < 10240 && ch[i] != '\0'; i++)
         if(ch[i] == '{')
            IsHeader = true;

      if(IsHeader == true)
      {
         for(int i = 0; i < 10240 && ch[i] != '\0'; i++)
            if(ch[i] == '{' || ch[i] == '}')
               ch[i] = ' ';

         stringstream str(ch);
         string Dummy = "";

         str >> NBin;
         for(int i = 0; i < NBin; i++)
            str >> Dummy;
         str >> NPar;
         for(int i = 0; i < NPar; i++)
            str >> Dummy;
         
         continue;
      }

      Result.push_back(ParseRecord(ch, NBin, NPar));
   }

   in.close();

   sort(Result.begin(), Result.end());

   return Result;
}

void SplitUp(vector<Record> &R1, vector<Record> &R2)
{
   Assert(R1.size() > 0 && R2.size() > 0, "No bins to split up?");
   Assert(R1[0].NBin == R2[0].NBin, "Different number of bins.  Don't know how to split up bins.");
   Assert(R1[0].NBin == 1, "More than one bin not supported yet.");

   if(R1[0].NBin >= 1)
   {
      vector<double> Bins;
      for(int i = 0; i < (int)R1.size(); i++)
      {
         Bins.push_back(R1[i].BinMin[0]);
         Bins.push_back(R1[i].BinMax[0]);
      }
      for(int i = 0; i < (int)R2.size(); i++)
      {
         Bins.push_back(R2[i].BinMin[0]);
         Bins.push_back(R2[i].BinMax[0]);
      }
      sort(Bins.begin(), Bins.end());
      auto iter = unique(Bins.begin(), Bins.end(), [](double l, double r) {return fabs(l - r) < Tolerance;});
      Bins.erase(iter, Bins.end());

      cout << "Bin boundary count = " << Bins.size() << endl;

      int J = 0;
      for(int i = 0; i < (int)R1.size(); i++)
      {
         Assert(R1[i].BinMin[0] > Bins[J] - Tolerance, "Bin crawling error");
         
         while(R1[i].BinMin[0] > Bins[J] + Tolerance)
            J = J + 1;
            
         Assert(J + 1 < Bins.size(), "Bin crawling error while checking max");

         if(R1[i].BinMax[0] > Bins[J+1] + Tolerance)
         {
            Record NewRecord = R1[i];
            R1[i].BinMax[0] = Bins[J+1];
            NewRecord.BinMin[0] = Bins[J+1];
            R1.insert(R1.begin() + i, NewRecord);
         }
      }
   
      J = 0;
      for(int i = 0; i < (int)R2.size(); i++)
      {
         Assert(R2[i].BinMin[0] > Bins[J] - Tolerance, "Bin crawling error");
         
         while(R2[i].BinMin[0] > Bins[J] + Tolerance)
            J = J + 1;
            
         Assert(J + 1 < Bins.size(), "Bin crawling error while checking max");

         if(R2[i].BinMax[0] > Bins[J+1] + Tolerance)
         {
            Record NewRecord = R2[i];
            R2[i].BinMax[0] = Bins[J+1];
            NewRecord.BinMin[0] = Bins[J+1];
            R2.insert(R2.begin() + i, NewRecord);
         }
      }

      sort(R1.begin(), R1.end());
      sort(R2.begin(), R2.end());
   }

   if(R1[0].NBin >= 2)
   {
      // ToDo!
   }
}

void GenerateTextFile(string FileName, string Header, vector<Record> R1, vector<Record> R2)
{
   Assert(R1.size() == R2.size(), "Things don't match between inside and outside");

   ofstream out(FileName);

   out << Header << endl;

   for(int i = 0; i < (int)R1.size(); i++)
   {
      for(int j = 0; j < R1[i].NBin; j++)
         out << " " << R1[i].BinMin[j] << " " << R1[i].BinMax[j];

      out << "  " << R1[i].NPar * 2 + 2 + R1[i].TheRest.size() + R2[i].TheRest.size();

      for(int j = 0; j < R1[i].NPar; j++)
         out << " " << R1[i].ParMin[j] << " " << R1[i].ParMax[j];
      out << " " << -6.2832 << " " << 6.2832;

      out << " ";
      for(int j = 0; j < (int)R1[i].TheRest.size(); j++)
         out << " " << R1[i].TheRest[j];
      out << " ";
      for(int j = 0; j < (int)R2[i].TheRest.size(); j++)
         out << " " << R2[i].TheRest[j];
      out << endl;
   }

   out.close();
}


