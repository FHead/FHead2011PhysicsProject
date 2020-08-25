#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "TSpline.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TGraphErrors.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void ProcessPosterior(TFile &F, string Tag, vector<string> &Name, vector<double> &Min, vector<double> &Max, bool DoTransform);
void ProcessQHat(TFile &F, string Tag, int N, string Setting);
vector<vector<double>> ProcessData(TFile &F, string Tag);
void ProcessRAAPosterior(TFile &F, string Tag, vector<vector<double>> Xs,
   vector<double> XMin, vector<double> XMax, vector<double> YMin, vector<double> YMax, bool IsPrior = false);
void ProcessMedian(TFile &F, string Tag, vector<vector<double>> Xs);
void Set1DHistogram(TH1D *H);
void Set2DHistogram(TH2D *H);
double Formula1(double A, double B, double C, double D, double E, double T);
double Formula2(double A, double B, double C, double D, double E, double T, bool LBTOnly);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   // gStyle->SetPalette(51);

   CommandLine CL(argc, argv);

   string FileTag         = CL.Get("tag");
   vector<string> Name    = CL.GetStringVector("name", {"A", "B", "C", "D"});
   vector<double> Min     = CL.GetDoubleVector("min", vector<double>({0, 0, 0, 0}));
   vector<double> Max     = CL.GetDoubleVector("max", vector<double>({2, 20, 2, 20}));
   vector<double> XMin    = CL.GetDoubleVector("xmin", vector<double>({0, 0, 0, 0, 0, 0}));
   vector<double> XMax    = CL.GetDoubleVector("xmax", vector<double>({20, 20, 20, 20, 20, 20}));
   vector<double> YMin    = CL.GetDoubleVector("ymin", vector<double>({0, 0, 0, 0, 0, 0}));
   vector<double> YMax    = CL.GetDoubleVector("ymax", vector<double>({1, 1, 1, 1, 1, 1}));
   bool DoTransform       = CL.GetBool("transform", false);
   string Output          = CL.Get("output", "Scatter.root");
   string Setting         = CL.Get("setting", "Matter");

   TFile OutputFile(Output.c_str(), "RECREATE");

   ProcessPosterior(OutputFile, FileTag, Name, Min, Max, DoTransform);
   ProcessQHat(OutputFile, FileTag, Name.size(), Setting);
   vector<vector<double>> Xs = ProcessData(OutputFile, FileTag);
   ProcessRAAPosterior(OutputFile, FileTag, Xs, XMin, XMax, YMin, YMax, true);
   ProcessRAAPosterior(OutputFile, FileTag, Xs, XMin, XMax, YMin, YMax, false);
   ProcessMedian(OutputFile, FileTag, Xs);

   OutputFile.Close();

   return 0;
}

void ProcessPosterior(TFile &F, string Tag, vector<string> &Name, vector<double> &Min, vector<double> &Max, bool DoTransform)
{
   int N = Name.size();

   F.cd();

   vector<TH1D *> HDiagonal;
   vector<vector<TH2D *>> HScatter;

   int NBin = 100;

   for(int i = 0; i < N; i++)
   {
      HDiagonal.push_back(new TH1D(Form("HPosterior%d", i),
         Form(";%s;", Name[i].c_str()),
         NBin, Min[i], Max[i]));
      Set1DHistogram(HDiagonal[i]);
   }
   for(int i = 0; i < N; i++)
   {
      HScatter.push_back(vector<TH2D *>());
      for(int j = 0; j < N; j++)
      {
         if(i >= j)
            HScatter[i].push_back(nullptr);
         else
         {
            HScatter[i].push_back(new TH2D(Form("HPosterior%d%d", i, j),
               Form(";%s;%s", Name[i].c_str(), Name[j].c_str()),
               NBin, Min[i], Max[i], NBin, Min[j], Max[j]));
            Set2DHistogram(HScatter[i][j]);
         }
      }
   }

   ifstream in("txt/" + Tag + "_MCMCSamples.txt");

   while(in)
   {
      char ch[10240];
      ch[0] = '\0';
      in.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      double Temp[10] = {0};
      for(int i = 0; i < N; i++)
         str >> Temp[i];

      if(DoTransform == true)
      {
         double A = Temp[0];
         double B = Temp[1];

         Temp[0] = A * B;
         Temp[1] = A - A * B;
      }

      for(int i = 0; i < N; i++)
         HDiagonal[i]->Fill(Temp[i]);
      for(int i = 0; i < N; i++)
         for(int j = i + 1; j < N; j++)
            HScatter[i][j]->Fill(Temp[i], Temp[j]);
   }

   in.close();

   F.cd();

   for(int i = 0; i < N; i++)
      HDiagonal[i]->Write();
   for(int i = 0; i < N; i++)
      for(int j = 0; j < N; j++)
         if(HScatter[i][j] != nullptr)
            HScatter[i][j]->Write();
}

void ProcessQHat(TFile &F, string Tag, int N, string Setting)
{
   vector<vector<double>> Samples;

   ifstream in("txt/" + Tag + "_MCMCSamples.txt");

   while(in)
   {
      char ch[10240];
      ch[0] = '\0';
      in.getline(ch, 10239, '\n');
      if(ch[0] == '\0')
         continue;

      stringstream str(ch);

      double Temp[10] = {0};
      for(int i = 0; i < N; i++)
         str >> Temp[i];

      Samples.push_back(vector<double>(Temp, Temp + N));

      if(Samples.size() >= 250000)
         break;
   }

   in.close();

   cout << "Sample size for QHat = " << Samples.size() << endl;

   if(Setting != "MatterLBT2")
   {
      bool DoTransform = (Setting == "MatterLBT1");

      // T dependence at p = 100 GeV
      {
         int Bin = 200;
         double MinT = 0.17;
         double MaxT = 0.78;
         double E = 100;

         vector<double> TH90, TL90, TH68, TL68, TM;

         vector<double> QHat(Samples.size());

         for(int i = 0; i < Bin; i++)
         {
            double T = MinT + (MaxT - MinT) / Bin * (i + 0.5);

            for(int j = 0; j < (int)Samples.size(); j++)
            {
               double A, B, C, D;
               if(DoTransform == false)
               {
                  A = Samples[j][0];
                  B = Samples[j][1];
                  C = Samples[j][2];
                  D = Samples[j][3];
               }
               else
               {
                  A = Samples[j][0] * Samples[j][1];
                  C = Samples[j][0] - Samples[j][0] * Samples[j][1];
                  B = Samples[j][2];
                  D = Samples[j][3];
               }

               QHat[j] = Formula1(A, B, C, D, E, T);
            }

            sort(QHat.begin(), QHat.end());

            TH90.push_back(QHat[QHat.size()*0.0500]);
            TL90.push_back(QHat[QHat.size()*0.9500]);
            TH68.push_back(QHat[QHat.size()*0.8415]);
            TL68.push_back(QHat[QHat.size()*0.1585]);
            TM.push_back(QHat[QHat.size()*0.5]);
         }

         TGraph QHatT90, QHatT68, QHatTM;
         QHatT90.SetName("QHatT90");
         QHatT68.SetName("QHatT68");
         QHatTM.SetName("QHatTMedian");

         for(int i = 0; i < Bin; i++)
         {
            double T = MinT + (MaxT - MinT) / Bin * (i + 0.5);
            QHatT90.SetPoint(i, T, TL90[i]);
            QHatT90.SetPoint(2 * Bin - i - 1, T, TH90[i]);
            QHatT68.SetPoint(i, T, TL68[i]);
            QHatT68.SetPoint(2 * Bin - i - 1, T, TH68[i]);
            QHatTM.SetPoint(i, T, TM[i]);
         }

         QHatT90.Write();
         QHatT68.Write();
         QHatTM.Write();
      }

      // p dependence at fixed T
      {
         int Bin = 200;
         double MinP = 5;
         double MaxP = 200;
         double T = 0.3;

         vector<double> PH90, PL90, PH68, PL68, PM;

         vector<double> QHat(Samples.size());

         for(int i = 0; i < Bin; i++)
         {
            double P = MinP + (MaxP - MinP) / Bin * (i + 0.5);

            for(int j = 0; j < (int)Samples.size(); j++)
            {
               double A, B, C, D;
               if(DoTransform == false)
               {
                  A = Samples[j][0];
                  B = Samples[j][1];
                  C = Samples[j][2];
                  D = Samples[j][3];
               }
               else
               {
                  A = Samples[j][0] * Samples[j][1];
                  C = Samples[j][0] - Samples[j][0] * Samples[j][1];
                  B = Samples[j][2];
                  D = Samples[j][3];
               }

               QHat[j] = Formula1(A, B, C, D, P, T);
            }

            sort(QHat.begin(), QHat.end());

            PH90.push_back(QHat[QHat.size()*0.0500]);
            PL90.push_back(QHat[QHat.size()*0.9500]);
            PH68.push_back(QHat[QHat.size()*0.8415]);
            PL68.push_back(QHat[QHat.size()*0.1585]);
            PM.push_back(QHat[QHat.size()*0.5]);
         }

         TGraph QHatP90, QHatP68, QHatPM;
         QHatP90.SetName("QHatP90");
         QHatP68.SetName("QHatP68");
         QHatPM.SetName("QHatPMedian");

         for(int i = 0; i < Bin; i++)
         {
            double P = MinP + (MaxP - MinP) / Bin * (i + 0.5);
            QHatP90.SetPoint(i, P, PL90[i]);
            QHatP90.SetPoint(2 * Bin - i - 1, P, PH90[i]);
            QHatP68.SetPoint(i, P, PL68[i]);
            QHatP68.SetPoint(2 * Bin - i - 1, P, PH68[i]);
            QHatPM.SetPoint(i, P, PM[i]);
         }

         QHatP90.Write();
         QHatP68.Write();
         QHatPM.Write();
      }
   }
   else
   {
      // T dependence at p = 100 GeV
      {
         int Bin = 200;
         double MinT = 0.17;
         double MaxT = 0.78;
         double E = 100;

         vector<double> TMH90, TML90, TMH68, TML68, TMM;
         vector<double> TLH90, TLL90, TLH68, TLL68, TLM;

         vector<double> QHatM(Samples.size());
         vector<double> QHatL(Samples.size());

         for(int i = 0; i < Bin; i++)
         {
            double T = MinT + (MaxT - MinT) / Bin * (i + 0.5);

            for(int j = 0; j < (int)Samples.size(); j++)
            {
               double A, C, D, Q;
               A = Samples[j][0] * Samples[j][1];
               C = Samples[j][0] - Samples[j][0] * Samples[j][1];
               D = Samples[j][2];
               Q = Samples[j][3];

               QHatM[j] = Formula2(A, C, D, Q, E, T, false);
               QHatL[j] = Formula2(A, C, D, Q, E, T, true);
            }

            sort(QHatM.begin(), QHatM.end());
            sort(QHatL.begin(), QHatL.end());

            TMH90.push_back(QHatM[QHatM.size()*0.0500]);
            TML90.push_back(QHatM[QHatM.size()*0.9500]);
            TMH68.push_back(QHatM[QHatM.size()*0.8415]);
            TML68.push_back(QHatM[QHatM.size()*0.1585]);
            TMM.push_back(  QHatM[QHatM.size()*0.5000]);
            TLH90.push_back(QHatL[QHatL.size()*0.0500]);
            TLL90.push_back(QHatL[QHatL.size()*0.9500]);
            TLH68.push_back(QHatL[QHatL.size()*0.8415]);
            TLL68.push_back(QHatL[QHatL.size()*0.1585]);
            TLM.push_back(  QHatL[QHatL.size()*0.5000]);
         }

         TGraph QHatTM90, QHatTM68, QHatTMM;
         TGraph QHatTL90, QHatTL68, QHatTLM;
         QHatTM90.SetName("QHatTM90");
         QHatTM68.SetName("QHatTM68");
         QHatTMM.SetName("QHatTMMedian");
         QHatTL90.SetName("QHatTL90");
         QHatTL68.SetName("QHatTL68");
         QHatTLM.SetName("QHatTLMedian");

         for(int i = 0; i < Bin; i++)
         {
            double T = MinT + (MaxT - MinT) / Bin * (i + 0.5);
            QHatTM90.SetPoint(i, T, TML90[i]);
            QHatTM90.SetPoint(2 * Bin - i - 1, T, TMH90[i]);
            QHatTM68.SetPoint(i, T, TML68[i]);
            QHatTM68.SetPoint(2 * Bin - i - 1, T, TMH68[i]);
            QHatTMM.SetPoint(i, T, TMM[i]);
            QHatTL90.SetPoint(i, T, TLL90[i]);
            QHatTL90.SetPoint(2 * Bin - i - 1, T, TLH90[i]);
            QHatTL68.SetPoint(i, T, TLL68[i]);
            QHatTL68.SetPoint(2 * Bin - i - 1, T, TLH68[i]);
            QHatTLM.SetPoint(i, T, TLM[i]);
         }

         QHatTM90.Write();
         QHatTM68.Write();
         QHatTMM.Write();
         QHatTL90.Write();
         QHatTL68.Write();
         QHatTLM.Write();
      }

      // P dependence at T = 0.3 GeV
      {
         int Bin = 200;
         double MinP = 5;
         double MaxP = 200;
         double T = 0.3;

         vector<double> PMH90, PML90, PMH68, PML68, PMM;
         vector<double> PLH90, PLL90, PLH68, PLL68, PLM;

         vector<double> QHatM(Samples.size());
         vector<double> QHatL(Samples.size());

         for(int i = 0; i < Bin; i++)
         {
            double P = MinP + (MaxP - MinP) / Bin * (i + 0.5);

            for(int j = 0; j < (int)Samples.size(); j++)
            {
               double A, C, D, Q;
               A = Samples[j][0] * Samples[j][1];
               C = Samples[j][0] - Samples[j][0] * Samples[j][1];
               D = Samples[j][2];
               Q = Samples[j][3];

               QHatM[j] = Formula2(A, C, D, Q, P, T, false);
               QHatL[j] = Formula2(A, C, D, Q, P, T, true);
            }

            sort(QHatM.begin(), QHatM.end());
            sort(QHatL.begin(), QHatL.end());

            PMH90.push_back(QHatM[QHatM.size()*0.0500]);
            PML90.push_back(QHatM[QHatM.size()*0.9500]);
            PMH68.push_back(QHatM[QHatM.size()*0.8415]);
            PML68.push_back(QHatM[QHatM.size()*0.1585]);
            PMM.push_back(  QHatM[QHatM.size()*0.5000]);
            PLH90.push_back(QHatL[QHatL.size()*0.0500]);
            PLL90.push_back(QHatL[QHatL.size()*0.9500]);
            PLH68.push_back(QHatL[QHatL.size()*0.8415]);
            PLL68.push_back(QHatL[QHatL.size()*0.1585]);
            PLM.push_back(  QHatL[QHatL.size()*0.5000]);
         }

         TGraph QHatPM90, QHatPM68, QHatPMM;
         TGraph QHatPL90, QHatPL68, QHatPLM;
         QHatPM90.SetName("QHatPM90");
         QHatPM68.SetName("QHatPM68");
         QHatPMM.SetName("QHatPMMedian");
         QHatPL90.SetName("QHatPL90");
         QHatPL68.SetName("QHatPL68");
         QHatPLM.SetName("QHatPLMedian");

         for(int i = 0; i < Bin; i++)
         {
            double P = MinP + (MaxP - MinP) / Bin * (i + 0.5);
            QHatPM90.SetPoint(i, P, PML90[i]);
            QHatPM90.SetPoint(2 * Bin - i - 1, P, PMH90[i]);
            QHatPM68.SetPoint(i, P, PML68[i]);
            QHatPM68.SetPoint(2 * Bin - i - 1, P, PMH68[i]);
            QHatPMM.SetPoint(i, P, PMM[i]);
            QHatPL90.SetPoint(i, P, PLL90[i]);
            QHatPL90.SetPoint(2 * Bin - i - 1, P, PLH90[i]);
            QHatPL68.SetPoint(i, P, PLL68[i]);
            QHatPL68.SetPoint(2 * Bin - i - 1, P, PLH68[i]);
            QHatPLM.SetPoint(i, P, PLM[i]);
         }

         QHatPM90.Write();
         QHatPM68.Write();
         QHatPMM.Write();
         QHatPL90.Write();
         QHatPL68.Write();
         QHatPLM.Write();
      }
   }
}

vector<vector<double>> ProcessData(TFile &F, string Tag)
{
   vector<vector<double>> Xs;

   F.cd();

   ifstream inX("txt/" + Tag + "_X.txt");
   ifstream inY("txt/" + Tag + "_Y.txt");
   ifstream inE("txt/" + Tag + "_E.txt");
   ifstream inS("txt/" + Tag + "_S.txt");

   int Count = 0;

   while(inX && inY && inE && inS)
   {
      char chX[10240] = "";
      char chY[10240] = "";
      char chE[10240] = "";
      char chS[10240] = "";

      inX.getline(chX, 10239, '\n');
      inY.getline(chY, 10239, '\n');
      inE.getline(chE, 10239, '\n');
      inS.getline(chS, 10239, '\n');

      if(chX[0] == '\0')   continue;
      if(chY[0] == '\0')   continue;
      if(chE[0] == '\0')   continue;
      if(chS[0] == '\0')   continue;

      stringstream strX(chX);
      stringstream strY(chY);
      stringstream strE(chE);
      stringstream strS(chS);

      TGraphErrors G, GS;
      G.SetName(Form("Data%d", Count));
      GS.SetName(Form("DataS%d", Count));

      vector<double> X;

      while(strX && strY && strE && strS)
      {
         double TempX = -1, TempY = -1, TempE = -1, TempS = -1;
         strX >> TempX;
         strY >> TempY;
         strE >> TempE;
         strS >> TempS;

         if(TempX < 0 || TempY < 0 || TempE < 0 || TempS < 0)
            continue;

         int i = G.GetN();
         G.SetPoint(i, TempX, TempY);
         G.SetPointError(i, 0, TempE);

         GS.SetPoint(i, TempX, TempY);
         GS.SetPointError(i, 0, TempS);

         X.push_back(TempX);
      }

      Xs.push_back(X);

      G.Write();
      GS.Write();
      
      Count = Count + 1;
   }

   inS.close();
   inE.close();
   inY.close();
   inX.close();

   return Xs;
}

void ProcessRAAPosterior(TFile &F, string Tag, vector<vector<double>> Xs,
   vector<double> XMin, vector<double> XMax, vector<double> YMin, vector<double> YMax, bool IsPrior)
{
   vector<TH2D *> H;

   F.cd();

   int N = Xs.size();
   for(int i = 0; i < N; i++)
   {
      string Name = Form("HRAA%s%d", (IsPrior ? "Prior" : "Posterior"), i);
      H.push_back(new TH2D(Name.c_str(), ";p_{T};R_{AA}", 500, XMin[i], XMax[i], 500, YMin[i], YMax[i]));
   }

   string FileName = "txt/" + Tag + (IsPrior ? "_Prior" : "_Posterior");

   for(int i = 0; i < N; i++)
   {
      cout << i + 1 << "/" << N << endl;

      ifstream in(FileName + Form("%d", i + 1) + ".txt");

      int Count = 0;

      while(in)
      {
         char ch[10240] = "";
         in.getline(ch, 10239, '\n');
         if(ch[0] == '\0')
            continue;
         
         stringstream str(ch);

         TGraph G;
         for(int j = 0; j < (int)Xs[i].size(); j++)
         {
            double Temp = -1;
            str >> Temp;
            if(Temp < 0)
               continue;

            G.SetPoint(j, Xs[i][j], Temp);
         }

         TSpline3 L("L", &G);

         for(int j = 0; j < (int)H[i]->GetNbinsX(); j++)
         {
            double X = H[i]->GetXaxis()->GetBinCenter(j);
            double Y = L.Eval(X);
            H[i]->Fill(X, Y);
         }

         Count = Count + 1;
      }

      in.close();
   }

   for(int i = 0; i < N; i++)
      H[i]->Write();
}

void ProcessMedian(TFile &F, string Tag, vector<vector<double>> Xs)
{
   ifstream in("txt/" + Tag + "_MedianPrediction.txt");

   int Count = 0;

   while(in)
   {
      char ch[10240] = "";

      in.getline(ch, 10239, '\n');

      if(ch[0] == '\0')   continue;

      stringstream str(ch);

      TGraphErrors G;
      G.SetName(Form("MedianGraph%d", Count));

      while(str)
      {
         double Temp = -1;
         str >> Temp;

         if(Temp < 0)
            continue;

         int i = G.GetN();
         G.SetPoint(i, Xs[Count][i], Temp);
      }

      TSpline3 L("", &G);
      L.SetName(Form("Median%d", Count));

      L.Write();
      
      Count = Count + 1;
   }

   in.close();
}

void Set1DHistogram(TH1D *H)
{
   H->SetStats(0);
   H->SetLineColor(kBlack);
   H->SetLineWidth(2);
   H->GetXaxis()->SetNdivisions(305);
   H->SetTickLength(0, "y");
}

void Set2DHistogram(TH2D *H)
{
   H->SetStats(0);
   H->GetXaxis()->SetNdivisions(305);
   H->GetYaxis()->SetNdivisions(305);
   // H->SetTickLength(0, "y");
   // H->SetTickLength(0, "x");
}

double Formula1(double A, double B, double C, double D, double E, double T)
{
   double CR = 1.3333;
   double Zeta3 = 1.2020569031595942;
   double Lambda = 0.2;

   double Prefactor = 42 * CR * Zeta3 / M_PI * (4 * M_PI / 9) * (4 * M_PI / 9);
   double Part1 = A * (log(E / Lambda) - log(B)) / (log(E / Lambda) * log(E / Lambda));
   double Part2 = C * (log(E / T) - log(D)) / (log(E * T / Lambda / Lambda) * log(E * T / Lambda / Lambda));

   return Prefactor * (Part1 + Part2);
}

double Formula2(double A, double C, double D, double Q0, double E, double T, bool LBTOnly)
{
   double CR = 1.3333;
   double Zeta3 = 1.2020569031595942;
   double Lambda = 0.2;
   double Q = E;   // for now

   double Prefactor = 42 * CR * Zeta3 / M_PI * (4 * M_PI / 9) * (4 * M_PI / 9);
   double Part1 = A * (log(Q / Lambda) - log(Q0 / Lambda)) / (log(Q / Lambda) * log(Q / Lambda));
   double Part2 = C * (log(E / T) - log(D)) / (log(E * T / Lambda / Lambda) * log(E * T / Lambda / Lambda));

   if(LBTOnly)
      Part1 = 0;
   return Prefactor * (Part1 + Part2);
}


