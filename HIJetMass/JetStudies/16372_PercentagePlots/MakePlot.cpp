#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "TGraph.h"
#include "TCanvas.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

class Event;
int main(int argc, char *argv[]);
void ReadData(string FileName, vector<Event> &Data, vector<Event> &Smear, vector<Event> &SmearNoCorrection);
vector<Event> BinSelection(vector<Event> &Data, double PTMin, double PTMax, double CMin, double CMax);
void DoPlot(PdfFileHelper &PdfFile, vector<Event> &Data, vector<Event> &Smear,
   double PTMin, double PTMax, double CMin, double CMax);
double FindMass(vector<pair<double, double>> &C, double P);

class Event
{
public:
   bool IsData;
   double Centrality;
   double PT;
   double MassRatio;
   double ZG;
   double DR;
   double PTPT;
   double Weight;
public:
   Event() : IsData(false), Centrality(-1), PT(-1), MassRatio(-1), ZG(-1), DR(-1), PTPT(-1), Weight(-1)
   {
   }
   Event(string input)
      : IsData(false), Centrality(-1), PT(-1), MassRatio(-1), ZG(-1), DR(-1), PTPT(-1), Weight(-1)
   {
      stringstream str(input);

      string temp = "";
      str >> temp;

      if(temp == "Data")
         IsData = true;
      else
         IsData = false;

      str >> Centrality >> PT >> MassRatio >> ZG >> DR >> PTPT >> Weight;
   }
   bool operator <(const Event &other) const
   {
      if(MassRatio < other.MassRatio)   return true;
      if(MassRatio > other.MassRatio)   return false;

      if(Centrality < other.Centrality)   return true;
      if(Centrality > other.Centrality)   return false;

      if(PT < other.PT)   return true;
      if(PT > other.PT)   return false;

      if(ZG < other.ZG)   return true;
      if(ZG > other.ZG)   return false;

      if(DR < other.DR)   return true;
      if(DR > other.DR)   return false;

      if(PTPT < other.PTPT)   return true;
      if(PTPT > other.PTPT)   return false;

      if(Weight < other.Weight)   return true;
      if(Weight > other.Weight)   return false;

      return false;
   }
};

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
      cerr << "Usage: " << argv[0] << " Input Tag" << endl;
      return -1;
   }

   SetThesisStyle();

   vector<Event> Data;
   vector<Event> Smear;
   vector<Event> SmearNoCorrection;
   ReadData(argv[1], Data, Smear, SmearNoCorrection);

   PdfFileHelper PdfFile(string("Result") + argv[2] + ".pdf");
   PdfFile.AddTextPage("Diagonal plots");

   DoPlot(PdfFile, Data, Smear, 140, 160, 0, 10);
   DoPlot(PdfFile, Data, Smear, 160, 180, 0, 10);
   DoPlot(PdfFile, Data, Smear, 180, 200, 0, 10);
   DoPlot(PdfFile, Data, Smear, 200, 300, 0, 10);
   DoPlot(PdfFile, Data, Smear, 140, 160, 10, 30);
   DoPlot(PdfFile, Data, Smear, 160, 180, 10, 30);
   DoPlot(PdfFile, Data, Smear, 180, 200, 10, 30);
   DoPlot(PdfFile, Data, Smear, 200, 300, 10, 30);
   DoPlot(PdfFile, Data, Smear, 140, 160, 30, 50);
   DoPlot(PdfFile, Data, Smear, 160, 180, 30, 50);
   DoPlot(PdfFile, Data, Smear, 180, 200, 30, 50);
   DoPlot(PdfFile, Data, Smear, 200, 300, 30, 50);
   DoPlot(PdfFile, Data, Smear, 140, 160, 50, 80);
   DoPlot(PdfFile, Data, Smear, 160, 180, 50, 80);
   DoPlot(PdfFile, Data, Smear, 180, 200, 50, 80);
   DoPlot(PdfFile, Data, Smear, 200, 300, 50, 80);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void ReadData(string FileName, vector<Event> &Data, vector<Event> &Smear, vector<Event> &SmearNoCorrection)
{
   ifstream in(FileName.c_str());

   char ch[10240] = "";
   while(in)
   {
      in.getline(ch, 10239, '\n');
      Event X(ch);

      if(X.Weight < 0)
         continue;
      if(X.DR < 0.1)
         continue;

      if(X.IsData == true)
         Data.push_back(X);
      if(X.IsData == false)
      {
         Smear.push_back(X);
         X.MassRatio = X.MassRatio / (1.01 - X.DR * 0.075);
         SmearNoCorrection.push_back(X);
      }
   }

   cout << Data.size() << " " << Smear.size() << " " << SmearNoCorrection.size() << endl;

   in.close();
}

vector<Event> BinSelection(vector<Event> &Data, double PTMin, double PTMax, double CMin, double CMax)
{
   vector<Event> Result;

   for(int i = 0; i < (int)Data.size(); i++)
   {
      if(Data[i].PT < PTMax && Data[i].PT >= PTMin && Data[i].Centrality < CMax && Data[i].Centrality >= CMin)
         Result.push_back(Data[i]);
   }

   return Result;
}

void DoPlot(PdfFileHelper &PdfFile, vector<Event> &Data, vector<Event> &Smear,
   double PTMin, double PTMax, double CMin, double CMax)
{
   vector<Event> ReducedData = BinSelection(Data, PTMin, PTMax, CMin, CMax);
   vector<Event> ReducedSmear = BinSelection(Smear, PTMin, PTMax, CMin, CMax);

   sort(ReducedData.begin(), ReducedData.end());
   sort(ReducedSmear.begin(), ReducedSmear.end());

   vector<pair<double, double>> CumulativeData(ReducedData.size());   // first one is mass, second one is weight
   vector<pair<double, double>> CumulativeSmear(ReducedSmear.size());

   CumulativeData[0] = pair<double, double>(ReducedData[0].MassRatio, ReducedData[0].Weight);
   for(int i = 1; i < (int)ReducedData.size(); i++)
      CumulativeData[i] = pair<double, double>(ReducedData[i].MassRatio, ReducedData[i].Weight + CumulativeData[i-1].second);
   CumulativeSmear[0] = pair<double, double>(ReducedSmear[0].MassRatio, ReducedSmear[0].Weight);
   for(int i = 1; i < (int)ReducedSmear.size(); i++)
      CumulativeSmear[i] = pair<double, double>(ReducedSmear[i].MassRatio, ReducedSmear[i].Weight + CumulativeSmear[i-1].second);

   double Total = 0;

   Total = CumulativeData[ReducedData.size()-1].second;
   for(int i = 0; i < (int)ReducedData.size(); i++)
      CumulativeData[i].second = CumulativeData[i].second / Total;
   Total = CumulativeSmear[ReducedSmear.size()-1].second;
   for(int i = 0; i < (int)ReducedSmear.size(); i++)
      CumulativeSmear[i].second = CumulativeSmear[i].second / Total;

   TGraph G;

   for(double P = 0; P <= 1; P = P + 0.001)
   {
      double x = FindMass(CumulativeData, P);
      double y = x - FindMass(CumulativeSmear, P);

      G.SetPoint(G.GetN(), x, y);
   }

   TH2D HWorld("HWorld", ";PbPb Mass/PT;PbPb - pp", 100, 0, 0.26, 100, -0.03, 0.03);
   HWorld.SetStats(0);
   HWorld.SetTitle(Form("Jet PT = %.0f-%.0f, Centrality = %.2f-%.2f", PTMin, PTMax, CMin * 0.01, CMax * 0.01));

   TGraph GLine;
   GLine.SetPoint(0, 0, 0);
   GLine.SetPoint(1, 1, 1);
   GLine.SetPoint(2, 0, 1);
   GLine.SetPoint(3, 1, 1);
   GLine.SetPoint(4, 1, 0);
   GLine.SetPoint(5, 0, 0);

   TCanvas Canvas;

   HWorld.Draw("axis");
   G.Draw("p");
   GLine.Draw("l");

   PdfFile.AddCanvas(Canvas);
}

double FindMass(vector<pair<double, double>> &C, double P)
{
   int N = C.size();

   if(P <= 0)       return C[0].first;
   if(P >= N - 1)   return C[N-1].first;

   int L = 0, R = N - 1;
   while(R - L > 1)
   {
      int X = (L + R) / 2;
      if(C[X].second <= P)
         L = X;
      else
         R = X;
   }

   return (P - C[L].second) / (C[R].second - C[L].second) * (C[R].first - C[L].first) + C[L].first;
}









