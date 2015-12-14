#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

#include "TLatex.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TGraph.h"

#include "RooEllipse.h"
using namespace RooFit;

#include "DataHelper.h"

struct SingleFit;
int main(int argv, char *argv[]);

struct SingleFit
{
public:
   string R2Cut;
   string Selection;
   string Tagging;
   double S1, S1Error;
   double S2, S2Error;
   double Fraction, FractionError;
   double Correlation;
   double Stats;
public:
   bool operator <(const SingleFit &Other) const
   {
      if(R2Cut < Other.R2Cut)   return true;
      if(R2Cut > Other.R2Cut)   return false;

      if(Tagging < Other.Tagging)   return true;
      if(Tagging > Other.Tagging)   return false;

      if(Selection < Other.Selection)   return true;
      if(Selection > Other.Selection)   return false;

      return false;   // lazy: we'll only have one result for one fit setting - upgrade this in the future if needed
   }
};

int main(int argc, char *argv[])
{
   string Base = "IndividualPlots/TTbar";
   if(argc > 1)
      Base = argv[1];

   string InputFile = Base + ".dh";

   map<string, vector<SingleFit> > Results;

   DataHelper DHFile(InputFile);

   vector<string> Keys = DHFile.GetListOfKeys();
   for(int i = 0; i < (int)Keys.size(); i++)
   {
      string State = Keys[i];

      SingleFit NewResult;

      NewResult.R2Cut = DHFile[Keys[i]]["R2Cut"].GetString();
      NewResult.Selection = DHFile[Keys[i]]["Selection"].GetString();
      NewResult.Tagging = DHFile[Keys[i]]["Tagging"].GetString();
      NewResult.S1 = DHFile[Keys[i]]["S1"].GetDouble();
      NewResult.S1Error = DHFile[Keys[i]]["S1Error"].GetDouble();
      NewResult.S2 = DHFile[Keys[i]]["S2"].GetDouble();
      NewResult.S2Error = DHFile[Keys[i]]["S2Error"].GetDouble();
      NewResult.Fraction = DHFile[Keys[i]]["Fraction"].GetDouble();
      NewResult.FractionError = DHFile[Keys[i]]["FractionError"].GetDouble();
      NewResult.Correlation = DHFile[Keys[i]]["Correlation"].GetDouble();
      NewResult.Stats = DHFile[Keys[i]]["Stats"].GetDouble();

      if(Results.find(NewResult.R2Cut) == Results.end())
         Results.insert(pair<string, vector<SingleFit> >(NewResult.R2Cut, vector<SingleFit>()));
      Results[NewResult.R2Cut].push_back(NewResult);
   }

   for(map<string, vector<SingleFit> >::iterator iter = Results.begin(); iter != Results.end(); iter++)
   {
      vector<SingleFit> SameRCutResults = iter->second;

      sort(SameRCutResults.begin(), SameRCutResults.end());

      TGraphErrors SlopeSummary;
      for(int i = 0; i < (int)SameRCutResults.size(); i++)
      {
         SlopeSummary.SetPoint(i * 2, SameRCutResults[i].S1, i + 0.4);
         SlopeSummary.SetPointError(i * 2, SameRCutResults[i].S1Error, 0);
         
         SlopeSummary.SetPoint(i * 2 + 1, SameRCutResults[i].S2, i + 0.5);
         SlopeSummary.SetPointError(i * 2 + 1, SameRCutResults[i].S2Error, 0);
      }
      SlopeSummary.SetLineWidth(2);

      TGraphErrors StatBox;
      TGraphErrors StatBox2;
      TGraphErrors StatBox3;
      for(int i = 0; i < (int)SameRCutResults.size(); i++)
      {
         if(SameRCutResults[i].Stats < 1000)
         {
            int index = StatBox.GetN();
            StatBox.SetPoint(index, 0, i + 0.5);
            StatBox.SetPointError(index, 1000, 0.5);
         }
         else if(SameRCutResults[i].Stats < 3000)
         {
            int index = StatBox2.GetN();
            StatBox2.SetPoint(index, 0, i + 0.5);
            StatBox2.SetPointError(index, 1000, 0.5);
         }
         else if(SameRCutResults[i].Stats < 10000)
         {
            int index = StatBox3.GetN();
            StatBox3.SetPoint(index, 0, i + 0.5);
            StatBox3.SetPointError(index, 1000, 0.5);
         }
      }
      StatBox.SetFillColor(kRed);
      StatBox.SetFillStyle(3001);
      StatBox2.SetFillColor(kOrange);
      StatBox2.SetFillStyle(3001);
      StatBox3.SetFillColor(kYellow);
      StatBox3.SetFillStyle(3001);

      TH2D HWorld("HWorld", Form("Summary of fits with R^{2} > %s", iter->first.c_str()),
         10, -0.02, 0, SameRCutResults.size(), 0, SameRCutResults.size());
      HWorld.SetStats(0);

      for(int i = 0; i < (int)SameRCutResults.size(); i++)
         HWorld.GetYaxis()->SetBinLabel(i + 1,
            Form("%s, %s", SameRCutResults[i].Selection.c_str(), SameRCutResults[i].Tagging.c_str()));
      HWorld.GetXaxis()->SetNdivisions(505);

      TGraph G[10];
      for(int i = 0; i < 10; i++)
      {
         G[i].SetPoint(0, -10, i * 5 + 5);
         G[i].SetPoint(1, 10, i * 5 + 5);
      }

      TLatex latex;
      latex.SetNDC();
      latex.SetTextFont(42);
      latex.SetTextSize(0.03);

      TCanvas C("C", "C", 800, 1600);
      C.SetLeftMargin(0.25);
      HWorld.Draw();
      StatBox.Draw("2");
      StatBox2.Draw("2");
      StatBox3.Draw("2");
      SlopeSummary.Draw("p");
      for(int i = 0; i < 10; i++)
         G[i].Draw("l");
      C.SetGridx();
      latex.DrawLatex(0.05, 0.025, "Stats - Red: < 1000, Orange: 1000-3000, Yellow: 3000-10000, White: > 10000");
      C.SaveAs(Form("%s_%s_Summary_Summary.png", Base.c_str(), iter->first.c_str()));

      TGraph Diagonal;
      Diagonal.SetPoint(0, 1, 1);
      Diagonal.SetPoint(1, -1, -1);

      vector<string> Selections;
      vector<string> Taggings;
      map<pair<string, string>, RooEllipse *> EllipsesA;
      map<pair<string, string>, RooEllipse *> EllipsesB;
      for(int i = 0; i < (int)SameRCutResults.size(); i++)
      {
         string Selection = SameRCutResults[i].Selection;
         string Tagging = SameRCutResults[i].Tagging;
         double x = SameRCutResults[i].S1;
         double ex = SameRCutResults[i].S1Error;
         double y = SameRCutResults[i].S2;
         double ey = SameRCutResults[i].S2Error;
         double rho = SameRCutResults[i].Correlation;

         if(x < y)
         {
            swap(x, y);
            swap(ex, ey);
         }

         RooEllipse *ContourA = new RooEllipse(Form("DataEllipse%d", i), x, y, ex, ey, rho);
         RooEllipse *ContourB = new RooEllipse(Form("DataEllipse%d", i), y, x, ey, ex, rho);

         ContourA->SetLineWidth(2);
         ContourA->SetLineColor(kBlue);

         ContourB->SetLineWidth(1);
         ContourB->SetLineColor(kBlue);

         Selections.push_back(Selection);
         Taggings.push_back(Tagging);

         EllipsesA.insert(pair<pair<string, string>, RooEllipse *>(pair<string, string>(Selection, Tagging), ContourA));
         EllipsesB.insert(pair<pair<string, string>, RooEllipse *>(pair<string, string>(Selection, Tagging), ContourB));
      }

      sort(Selections.begin(), Selections.end());
      Selections.erase(unique(Selections.begin(), Selections.end()), Selections.end());
      sort(Taggings.begin(), Taggings.end());
      Taggings.erase(unique(Taggings.begin(), Taggings.end()), Taggings.end());

      for(int i = 0; i < (int)Selections.size(); i++)
      {
         TLegend Legend(0.15, 0.15, 0.35, 0.45);
         Legend.SetBorderSize(0);
         Legend.SetFillStyle(0);
         Legend.SetTextFont(42);

         TCanvas C2("C2", "C2", 800, 800);

         double minx = 99999;
         double maxx = -99999;
         double miny = 99999;
         double maxy = -99999;
         for(int j = 0; j < (int)SameRCutResults.size(); j++)
         {
            if(SameRCutResults[j].Selection != Selections[i])
               continue;

            double x = SameRCutResults[j].S1;
            double ex = SameRCutResults[j].S1Error;
            double y = SameRCutResults[j].S2;
            double ey = SameRCutResults[j].S2Error;
            double rho = SameRCutResults[j].Correlation;
            if(x < y)
            {
               swap(x, y);
               swap(ex, ey);
            }

            if(minx > x)   minx = x;
            if(maxx < x)   maxx = x;
            if(miny > y)   miny = y;
            if(maxy < y)   maxy = y;
         }

         if(minx < miny)   miny = minx;
         if(miny < minx)   minx = miny;
         if(maxx > maxy)   maxy = maxx;
         if(maxy > maxx)   maxx = maxy;

         TH2D HWorld2("HWorld2",
            Form("Summary of fits with %s;Slope of slower component;Slope of faster component", Selections[i].c_str()),
            10, minx - (maxx - minx), maxx + (maxx - minx), 10, miny - (maxy - miny), maxy + (maxy - miny));
         HWorld2.SetStats(0);
         HWorld2.Draw();

         int ItemCount = 0;
         for(map<pair<string, string>, RooEllipse *>::iterator iter2 = EllipsesA.begin(); iter2 != EllipsesA.end(); iter2++)
         {
            if(iter2->first.first != Selections[i])
               continue;

            string Tagging = iter2->first.second;

            iter2->second->SetLineColor(ItemCount + 1);
            EllipsesB[iter2->first]->SetLineColor(ItemCount + 1);

            iter2->second->Draw("l");
            EllipsesB[iter2->first]->Draw("l");

            Legend.AddEntry(iter2->second, Tagging.c_str(), "l");

            ItemCount = ItemCount + 1;
         }

         Legend.Draw();

         Diagonal.Draw("l");
         C2.SaveAs(Form("%s_%s_%s_Summary.png", Base.c_str(), iter->first.c_str(), Selections[i].c_str()));
      }
      
      for(int i = 0; i < (int)Taggings.size(); i++)
      {
         TLegend Legend(0.15, 0.15, 0.35, 0.45);
         Legend.SetBorderSize(0);
         Legend.SetFillStyle(0);
         Legend.SetTextFont(42);

         TCanvas C2("C2", "C2", 800, 800);

         double minx = 99999;
         double maxx = -99999;
         double miny = 99999;
         double maxy = -99999;
         for(int j = 0; j < (int)SameRCutResults.size(); j++)
         {
            if(SameRCutResults[j].Tagging != Taggings[i])
               continue;

            double x = SameRCutResults[j].S1;
            double ex = SameRCutResults[j].S1Error;
            double y = SameRCutResults[j].S2;
            double ey = SameRCutResults[j].S2Error;
            double rho = SameRCutResults[j].Correlation;
            if(x < y)
            {
               swap(x, y);
               swap(ex, ey);
            }

            if(minx > x)   minx = x;
            if(maxx < x)   maxx = x;
            if(miny > y)   miny = y;
            if(maxy < y)   maxy = y;
         }
         
         if(minx < miny)   miny = minx;
         if(miny < minx)   minx = miny;
         if(maxx > maxy)   maxy = maxx;
         if(maxy > maxx)   maxx = maxy;

         TH2D HWorld2("HWorld2",
            Form("Summary of fits with %s tag;Slope of slower component;Slope of faster component", Taggings[i].c_str()),
            10, minx - (maxx - minx), maxx + (maxx - minx), 10, miny - (maxy - miny), maxy + (maxy - miny));
         HWorld2.SetStats(0);
         HWorld2.Draw();

         int ItemCount = 0;
         for(map<pair<string, string>, RooEllipse *>::iterator iter2 = EllipsesA.begin(); iter2 != EllipsesA.end(); iter2++)
         {
            if(iter2->first.second != Taggings[i])
               continue;

            string Selection = iter2->first.first;

            iter2->second->SetLineColor(ItemCount + 1);
            EllipsesB[iter2->first]->SetLineColor(ItemCount + 1);

            iter2->second->Draw("l");
            EllipsesB[iter2->first]->Draw("l");

            Legend.AddEntry(iter2->second, Selection.c_str(), "l");

            ItemCount = ItemCount + 1;
         }

         Legend.Draw();

         Diagonal.Draw("l");
         C2.SaveAs(Form("%s_%s_Summary_%s.png", Base.c_str(), iter->first.c_str(), Taggings[i].c_str()));
      }

      for(map<pair<string, string>, RooEllipse *>::iterator iter2 = EllipsesA.begin(); iter2 != EllipsesA.end(); iter2++)
         if(iter2->second != NULL)
            delete iter2->second;
      for(map<pair<string, string>, RooEllipse *>::iterator iter2 = EllipsesB.begin(); iter2 != EllipsesB.end(); iter2++)
         if(iter2->second != NULL)
            delete iter2->second;
   }

   return 0;
}



