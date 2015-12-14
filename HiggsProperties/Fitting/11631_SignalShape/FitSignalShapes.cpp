#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooModifiedBreitWigner.hh"
#include "RooDoubleSidedCBShape.hh"
#include "RooFFTConvPdf.h"
#include "RooPlot.h"
using namespace RooFit;

#include "PlotHelper2.h"

int main(int argc, char *argv[]);
double GetHiggsWidth(double Mass, const vector<pair<double, double> > &Widths);
vector<double> ReadFile(string FileName, int Col);

int main(int argc, char *argv[])
{
   string Mass = "125";
   if(argc > 1)
      Mass = argv[1];

   vector<double> Masses = ReadFile("HiggsWidths.txt", 1);
   vector<double> Widths = ReadFile("HiggsWidths.txt", 2);
   vector<double> BrGG = ReadFile("HiggsWidths.txt", 3);
   vector<double> BrZZ = ReadFile("HiggsWidths.txt", 4);

   TFile File(Form("Samples/hzzTree_id1%s.root", Mass.c_str()));
   TTree *Tree = (TTree *)File.Get("zz4lTree/probe_tree");

   RooRealVar m4l("m4l", "m4l", atof(Mass.c_str()), atof(Mass.c_str()) * 0.7, atof(Mass.c_str()) * 1.3);
   RooRealVar mean("mean", "mean", atof(Mass.c_str()));
   RooRealVar m0("m0", "m0", 0.3, -1000, 1000);
   RooRealVar sigma("sigma", "sigma", atof(Mass.c_str()) / 100 * 1.5, 0, 1000);
   RooRealVar alphal("alphal", "alphal", 1.5, 0, 1000);
   RooRealVar alphar("alphar", "alphar", 2, 0, 1000);
   RooRealVar nl("nl", "nl", 2, 0, 1000);
   RooRealVar nr("nr", "nr", 20);

   RooDataSet DataSet("DataSet", "DataSet", Tree, RooArgSet(m4l));

   RooModifiedBreitWigner FunctionA("FunctionA", "FunctionA", m4l, mean);
   RooDoubleSidedCBShape FunctionB("FunctionB", "FunctionB", m4l, m0, sigma, alphal, alphar, nl, nr);
   RooFFTConvPdf Model("Model", "Model", m4l, FunctionA, FunctionB);

   FunctionA.SetSpectra(Masses, Widths, BrGG, BrZZ);

   Model.fitTo(DataSet);

   PsFileHelper PsFile(Form("RooFitResult_%s.ps", Mass.c_str()));
   PsFile.AddTextPage("Fit result!");

   RooPlot *FitResultPlot = m4l.frame(Bins(40), Name("Result"), Title(Form("Fit result for MH = %s", Mass.c_str())));
   DataSet.plotOn(FitResultPlot, MarkerSize(0.9));
   Model.plotOn(FitResultPlot, LineColor(kBlue));
   PsFile.AddPlot(FitResultPlot, "", false);
   PsFile.AddPlot(FitResultPlot, "", true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   cout << "FinalFitResult " << Mass
      << " " << m0.getVal() << " " << m0.getError()
      << " " << sigma.getVal() << " " << sigma.getError()
      << " " << alphal.getVal() << " " << alphal.getError()
      << " " << alphar.getVal() << " " << alphar.getError()
      << " " << nl.getVal() << " " << nl.getError()
      << " " << nr.getVal() << " " << nr.getError() << endl;

   File.Close();

   return 0;
}

vector<double> ReadFile(string FileName, int Col)
{
   vector<double> Result;

   ifstream in(FileName.c_str());

   while(in)
   {
      double Temp = -999;
      
      char ch[10240] = "";
      in.getline(ch, 10239, '\n');
      stringstream str(ch);

      for(int i = 1; i <= Col; i++)
      {
         double temp = -999;
         str >> temp;

         if(i == Col)
            Temp = temp;
      }

      if(Temp <= 0)
         continue;

      Result.push_back(Temp);
   }

   in.close();

   return Result;
}






