#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#include "CommandLine.h"
// #include "CustomAssert.h"

#define Tolerance 0.0001
#define NONE -10000

#define Verbose false

class Record;
int main(int argc, char *argv[]);
string FindHeader(string FileName);
string GetFormula(string FileName);
string ModifyFormula(string F1, string F2);
string ToString(int Number);
Record ParseRecord(string Line, int NBin, int NPar);
vector<Record> ParseFile(string FileName);
string FillUp(vector<Record> &R1, vector<Record> &R2, string Header1, string Header2);
void EnlargeBin(vector<Record> &R1, vector<Record> &R2, int B);
void SplitUp(vector<Record> &R1, vector<Record> &R2);
void GenerateTextFile(string FileName, string Header, vector<Record> R1, vector<Record> R2);
void Print(vector<Record> &R);

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

   string JERSFFileName = CL.Get("JERSFFileName");
   string JERFileName = CL.Get("JERFileName");
   string OutputFileName = CL.Get("Output");

   string HeaderJER = FindHeader(JERFileName);
   string HeaderJERSF = FindHeader(JERSFFileName);

   string FormulaJER = GetFormula(JERFileName);
   string FormulaJERSF = GetFormula(JERSFFileName);

   cout << "Formula (JER) = " << FormulaJER << endl;
   cout << "Formula (SF)  = " << FormulaJERSF << endl;

   FormulaJERSF = ModifyFormula(FormulaJER, FormulaJERSF);
   
   cout << "Modified formula (SF)  = " << FormulaJERSF << endl;

   string NewFormula = FormulaJER + "*" + FormulaJERSF;

   cout << "Combined formula = " << NewFormula << endl;

   vector<Record> LinesJER = ParseFile(JERFileName);
   vector<Record> LinesJERSF = ParseFile(JERSFFileName);
   
   cout << "Number of bins in JER = " << LinesJER.size() << endl;
   cout << "Number of bins in JERSF = " << LinesJERSF.size() << endl;

   string NewBinning = FillUp(LinesJER, LinesJERSF, HeaderJER, HeaderJERSF);

   cout << "New initial header = " << NewBinning << endl;

   cout << "LinesJER[0]: " << LinesJER[0].NBin << endl;
   for(int i = 0; i < LinesJER[0].NBin; i++)
      cout << "   " << LinesJER[0].BinMin[i] << " " << LinesJER[0].BinMax[i] << endl;
   cout << "LinesJERSF[0]: " << LinesJERSF[0].NBin << endl;
   for(int i = 0; i < LinesJERSF[0].NBin; i++)
      cout << "   " << LinesJERSF[0].BinMin[i] << " " << LinesJERSF[0].BinMax[i] << endl;

   EnlargeBin(LinesJER, LinesJERSF, 0);

   cout << "LinesJER[0]: " << LinesJER[0].NBin << endl;
   for(int i = 0; i < LinesJER[0].NBin; i++)
      cout << "   " << LinesJER[0].BinMin[i] << " " << LinesJER[0].BinMax[i] << endl;
   cout << "LinesJERSF[0]: " << LinesJERSF[0].NBin << endl;
   for(int i = 0; i < LinesJERSF[0].NBin; i++)
      cout << "   " << LinesJERSF[0].BinMin[i] << " " << LinesJERSF[0].BinMax[i] << endl;

   SplitUp(LinesJER, LinesJERSF);
   
   cout << "Number of bins in JER after splitting = " << LinesJER.size() << endl;
   cout << "Number of bins in SF  after splitting = " << LinesJERSF.size() << endl;

   string NewHeader = "{" + NewBinning + " 1 JetPt " + NewFormula + " Resolution}";
   cout << "New Header: " << NewHeader << endl;

   GenerateTextFile(OutputFileName, NewHeader, LinesJER, LinesJERSF);

   return 0;
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

   if(Result == "None")
      Result = "[0]";

   return "(" + Result + ")";
}

string ModifyFormula(string F1, string F2)
{
   // Count number of parameters in F1
   int N = 0;
   for(int i = 0; i < F1.size(); i++)
   {
      if(F1[i] == '[')
      {
         for(int j = i + 1; j < F1.size(); j++)
         {
            if(F1[j] == ']')
            {
               N = max(N, atoi(F1.substr(i + 1, j - i).c_str()) + 1);
               break;
            }
         }
      }
   }

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

      // Assert(End != -1, "Something is wrong in modifying formula");

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

      if(NPar == 0)   // "None" - take only one for now
         break;
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

string FillUp(vector<Record> &R1, vector<Record> &R2, string Header1, string Header2)
{
   vector<string> Bin1;
   vector<string> Bin2;

   stringstream str1(Header1);
   int N1;
   str1 >> N1;
   for(int i = 0; i < N1; i++)
   {
      string Temp = "";
      str1 >> Temp;
      Bin1.push_back(Temp);
   }
   
   stringstream str2(Header2);
   int N2;
   str2 >> N2;
   for(int i = 0; i < N2; i++)
   {
      string Temp = "";
      str2 >> Temp;
      Bin2.push_back(Temp);
   }

   vector<string> AllBin;
   AllBin.insert(AllBin.end(), Bin1.begin(), Bin1.end());
   AllBin.insert(AllBin.end(), Bin2.begin(), Bin2.end());
   sort(AllBin.begin(), AllBin.end());
   auto Iter = unique(AllBin.begin(), AllBin.end());
   AllBin.erase(Iter, AllBin.end());

   int N = AllBin.size();
   for(int i = 0; i < (int)R1.size(); i++)
   {
      R1[i].NBin = N;
      vector<double> Min;
      vector<double> Max;

      for(int j = 0; j < N; j++)
      {
         int I = -1;
         for(int k = 0; k < N1; k++)
            if(AllBin[j] == Bin1[k])
               I = k;

         if(I == -1)
         {
            Min.push_back(NONE);
            Max.push_back(NONE);
         }
         else
         {
            Min.push_back(R1[i].BinMin[I]);
            Max.push_back(R1[i].BinMax[I]);
         }
      }

      R1[i].BinMin = Min;
      R1[i].BinMax = Max;
   }
   for(int i = 0; i < (int)R2.size(); i++)
   {
      R2[i].NBin = N;
      vector<double> Min;
      vector<double> Max;

      for(int j = 0; j < N; j++)
      {
         int I = -1;
         for(int k = 0; k < N2; k++)
            if(AllBin[j] == Bin2[k])
               I = k;

         if(I == -1)
         {
            Min.push_back(NONE);
            Max.push_back(NONE);
         }
         else
         {
            Min.push_back(R2[i].BinMin[I]);
            Max.push_back(R2[i].BinMax[I]);
         }
      }

      R2[i].BinMin = Min;
      R2[i].BinMax = Max;
   }

   string NewBinning = to_string(N) + " ";
   for(int i = 0; i < N; i++)
      NewBinning = NewBinning + " " + AllBin[i];

   return NewBinning;
}

void EnlargeBin(vector<Record> &R1, vector<Record> &R2, int B)
{
   double Min1 = NONE;
   double Max1 = NONE;
   double Min2 = NONE;
   double Max2 = NONE;

   for(Record &R : R1)
   {
      if(R.BinMin[B] > NONE && (Min1 < NONE + Tolerance || R.BinMin[B] < Min1))
         Min1 = R.BinMin[B];
      if(R.BinMax[B] > NONE && (Max1 < NONE + Tolerance || R.BinMax[B] > Max1))
         Max1 = R.BinMax[B];
   }
   for(Record &R : R2)
   {
      if(R.BinMin[B] > NONE && (Min2 < NONE + Tolerance || R.BinMin[B] < Min2))
         Min2 = R.BinMin[B];
      if(R.BinMax[B] > NONE && (Max2 < NONE + Tolerance || R.BinMax[B] > Max2))
         Max2 = R.BinMax[B];
   }

   double Min = min(Min1, Min2);
   double Max = max(Max1, Max2);   // TODO: protect against NONE cases

   for(Record &R : R1)
   {
      if(fabs(R.BinMin[B] - Min1) < Tolerance)   R.BinMin[B] = Min;
      if(fabs(R.BinMax[B] - Max1) < Tolerance)   R.BinMax[B] = Max;
   }
   for(Record &R : R2)
   {
      if(fabs(R.BinMin[B] - Min2) < Tolerance)   R.BinMin[B] = Min;
      if(fabs(R.BinMax[B] - Max2) < Tolerance)   R.BinMax[B] = Max;
   }
}

void SplitUp(vector<Record> &R1, vector<Record> &R2)
{
   // Assert(R1.size() > 0 && R2.size() > 0, "No bins to split up?");
   // Assert(R1[0].NBin == R2[0].NBin, "Different number of bins.  Don't know how to split up bins.");
   // Assert(R1[0].NBin == 1, "More than one bin not supported yet.");

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

   if(R1[0].NBin >= 1)
   {
      int J = 0;
      for(int i = 0; i < (int)R1.size(); i++)
      {
         // Assert(R1[i].BinMin[0] > Bins[J] - Tolerance, "Bin crawling error");

         J = 0;
         while(R1[i].BinMin[0] > Bins[J] + Tolerance)
            J = J + 1;
            
         // Assert(J + 1 < Bins.size(), "Bin crawling error while checking max");

         if(R1[i].BinMax[0] > Bins[J+1] + Tolerance)
         {
            Record NewRecord = R1[i];
            R1[i].BinMax[0] = Bins[J+1];
            NewRecord.BinMin[0] = Bins[J+1];
            R1.insert(R1.begin() + i + 1, NewRecord);
         }
      }
   
      J = 0;
      for(int i = 0; i < (int)R2.size(); i++)
      {
         // Assert(R2[i].BinMin[0] > Bins[J] - Tolerance, "Bin crawling error");
         
         J = 0;
         while(R2[i].BinMin[0] > Bins[J] + Tolerance)
            J = J + 1;
            
         // Assert(J + 1 < Bins.size(), "Bin crawling error while checking max");

         if(R2[i].BinMax[0] > Bins[J+1] + Tolerance)
         {
            Record NewRecord = R2[i];
            R2[i].BinMax[0] = Bins[J+1];
            NewRecord.BinMin[0] = Bins[J+1];
            R2.insert(R2.begin() + i + 1, NewRecord);
         }
      }

      sort(R1.begin(), R1.end());
      sort(R2.begin(), R2.end());
   }
   
   cout << "JetEta Splitting Done" << endl;
   Print(R1);
   Print(R2);

   int B = 1;
   if(R1[0].NBin >= 2)   // Now do the cases where one of them is NONE
   {
      int I = 0, J = 0;

      while(I < (int)R1.size() && J < (int)R2.size())
      {
         double IX = (R1[I].BinMin[0] + R1[I].BinMax[0]) / 2;
         double JX = (R2[J].BinMin[0] + R2[J].BinMax[0]) / 2;

         if(IX < JX - Tolerance)
         {
            I = I + 1;
            continue;
         }
         if(JX < IX - Tolerance)
         {
            J = J + 1;
            continue;
         }
         
         bool NoneInR1 = false;
         if(R1[I].BinMin[B] < NONE + Tolerance && R1[I].BinMax[B] < NONE + Tolerance)
            NoneInR1 = true;

         Record R;
         if(NoneInR1 == true)
         {
            R = R1[I];
            R1.erase(R1.begin() + I);

            int Inserted = 0;
            for(int K = J; K < (int)R2.size(); K++)
            {
               double x = (R2[K].BinMin[0] + R2[K].BinMax[0]) / 2;
               if(fabs(x - JX) < Tolerance)
               {
                  R.BinMin[B] = R2[K].BinMin[B];
                  R.BinMax[B] = R2[K].BinMax[B];
                  R1.insert(R1.begin() + I, R);
                  Inserted = Inserted + 1;
               }
               else
                  break;
            }
            I = I + Inserted;
         }
         else
         {
            R = R2[J];
            R2.erase(R2.begin() + J);

            int Inserted = 0;
            for(int K = I; K < (int)R1.size(); K++)
            {
               double x = (R1[K].BinMin[0] + R1[K].BinMax[0]) / 2;
               if(fabs(x - IX) < Tolerance)
               {
                  R.BinMin[B] = R1[K].BinMin[B];
                  R.BinMax[B] = R1[K].BinMax[B];
                  R2.insert(R2.begin() + I, R);
                  Inserted = Inserted + 1;
               }
               else
                  break;
            }
            J = J + Inserted;
         }
      }

      sort(R1.begin(), R1.end());
      sort(R2.begin(), R2.end());
   }

   cout << "Bin1 Splitting Done" << endl;
   Print(R1);
   Print(R2);

   B = 2;
   if(R1[0].NBin >= 3)   // Now do the cases where one of them is NONE
   {
      int I = 0, J = 0;

      while(I < R1.size() && J < (int)R2.size())
      {
         double IX = (R1[I].BinMin[0] + R1[I].BinMax[0]) / 2;
         double IY = (R1[I].BinMin[1] + R1[I].BinMax[1]) / 2;
         double JX = (R2[J].BinMin[0] + R2[J].BinMax[0]) / 2;
         double JY = (R2[J].BinMin[1] + R2[J].BinMax[1]) / 2;
         
         if(IX < JX - Tolerance)
         {
            I = I + 1;
            continue;
         }
         if(JX < IX - Tolerance)
         {
            J = J + 1;
            continue;
         }
         if(IY < JY - Tolerance)
         {
            I = I + 1;
            continue;
         }
         if(JY < IY - Tolerance)
         {
            J = J + 1;
            continue;
         }

         bool NoneInR1 = false;
         if(R1[I].BinMin[B] < NONE + Tolerance && R1[I].BinMax[B] < NONE + Tolerance)
            NoneInR1 = true;

         Record R;
         if(NoneInR1 == true)
         {
            R = R1[I];
            R1.erase(R1.begin() + I);

            int Inserted = 0;
            for(int K = J; K < (int)R2.size(); K++)
            {
               double x = (R2[K].BinMin[0] + R2[K].BinMax[0]) / 2;
               double y = (R2[K].BinMin[1] + R2[K].BinMax[1]) / 2;
               if(fabs(x - JX) < Tolerance && fabs(y - JY) < Tolerance)
               {
                  R.BinMin[B] = R2[K].BinMin[B];
                  R.BinMax[B] = R2[K].BinMax[B];
                  R1.insert(R1.begin() + I, R);
                  Inserted = Inserted + 1;
               }
               else
                  break;
            }
            I = I + Inserted;
            J = J + Inserted;
         }
         else
         {
            R = R2[J];
            R2.erase(R2.begin() + J);

            int Inserted = 0;
            for(int K = I; K < (int)R1.size(); K++)
            {
               double x = (R1[K].BinMin[0] + R1[K].BinMax[0]) / 2;
               double y = (R1[K].BinMin[1] + R1[K].BinMax[1]) / 2;
               if(fabs(x - IX) < Tolerance && fabs(y - IY) < Tolerance)
               {
                  R.BinMin[B] = R1[K].BinMin[B];
                  R.BinMax[B] = R1[K].BinMax[B];
                  R2.insert(R2.begin() + I, R);
                  Inserted = Inserted + 1;
               }
               else
                  break;
            }
            I = I + Inserted;
            J = J + Inserted;
         }
      }

      sort(R1.begin(), R1.end());
      sort(R2.begin(), R2.end());
   }
   
   cout << "Bin2 Splitting Done" << endl;
   Print(R1);
   Print(R2);
}

void GenerateTextFile(string FileName, string Header, vector<Record> R1, vector<Record> R2)
{
   // Assert(R1.size() == R2.size(), "Things don't match between inside and outside");

   ofstream out(FileName);

   out << Header << endl;

   for(int i = 0; i < (int)R1.size(); i++)
   {
      for(int j = 0; j < R1[i].NBin; j++)
         out << " " << R1[i].BinMin[j] << " " << R1[i].BinMax[j];

      out << "  " << R1[i].NPar * 2 + R1[i].TheRest.size() + R2[i].TheRest.size();

      for(int j = 0; j < R1[i].NPar; j++)
         out << " " << R1[i].ParMin[j] << " " << R1[i].ParMax[j];

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

void Print(vector<Record> &R)
{
   if(Verbose == false)
      return;

   cout << "Record content: " << endl;
   for(int i = 0; i < (int)R.size(); i++)
   {
      cout << "[" << i << "]  " << R[i].NBin << " - ";
      for(int j = 0; j < R[i].NBin; j++)
         cout << " (" << R[i].BinMin[j] << ", " << R[i].BinMax[j] << ")";
      cout << endl;
   }
}

