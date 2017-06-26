#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "SetStyle.h"
#include "PlotHelper3.h"

int main()
{
   SetThesisStyle();

   PdfFileHelper PdfFile("Distributions.pdf");
   PdfFile.AddTextPage("Distribution");

   TFile File("Result/FitResult_A1UU_F_3.root");

   TTree *Tree = (TTree *)File.Get("OutputTree");

   PdfFile.AddTextPage("Float everything, 2e2mu+4e");
   PdfFile.AddPlot(Tree, "A1VV", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 0", "", ";A1VV;", 100, 0, 2);
   PdfFile.AddPlot(Tree, "A2VV", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 0", "", ";A2VV;", 100, -100, 100);
   PdfFile.AddPlot(Tree, "A3VV", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 0", "", ";A3VV;", 100, -100, 100);
   PdfFile.AddPlot(Tree, "A1VZ", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 0", "", ";A1VZ;", 100, -100, 100);
   PdfFile.AddPlot(Tree, "A2VZ", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 0", "", ";A2VZ;", 100, -5000, 5000);
   PdfFile.AddPlot(Tree, "A3VZ", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 0", "", ";A3VZ;", 100, -5000, 5000);
   PdfFile.AddPlot(Tree, "A1VA", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 0", "", ";A1VA;", 100, -10, 10);
   PdfFile.AddPlot(Tree, "A2VA", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 0", "", ";A2VA;", 100, -10, 10);
   PdfFile.AddPlot(Tree, "A3VA", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 0", "", ";A3VA;", 100, -10, 10);
   
   PdfFile.AddTextPage("Float individually (2e2mu+4e)");
   PdfFile.AddPlot(Tree, "A2VV", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 1", "", ";A2VV;", 100, -100, 100);
   PdfFile.AddPlot(Tree, "A3VV", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 2", "", ";A3VV;", 100, -100, 100);
   PdfFile.AddPlot(Tree, "A1VZ", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 3", "", ";A1VZ;", 100, -20, 20);
   PdfFile.AddPlot(Tree, "A2VZ", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 4", "", ";A2VZ;", 100, -1000, 1000);
   PdfFile.AddPlot(Tree, "A3VZ", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 5", "", ";A3VZ;", 100, -1000, 1000);
   PdfFile.AddPlot(Tree, "A1VA", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 6", "", ";A1VA;", 100, -0.01, 0.01);
   PdfFile.AddPlot(Tree, "A2VA", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 7", "", ";A2VA;", 100, -10, 10);
   PdfFile.AddPlot(Tree, "A3VA", "ExpectedSEM == 1000 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 8", "", ";A3VA;", 100, -10, 10);
   
   PdfFile.AddTextPage("Float individually (2e2mu)");
   PdfFile.AddPlot(Tree, "A2VV", "ExpectedSEM == 1000 && ExpectedSEE < 0 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 1", "", ";A2VV;", 100, -100, 100);
   PdfFile.AddPlot(Tree, "A3VV", "ExpectedSEM == 1000 && ExpectedSEE < 0 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 2", "", ";A3VV;", 100, -100, 100);
   PdfFile.AddPlot(Tree, "A1VZ", "ExpectedSEM == 1000 && ExpectedSEE < 0 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 3", "", ";A1VZ;", 100, -20, 20);
   PdfFile.AddPlot(Tree, "A2VZ", "ExpectedSEM == 1000 && ExpectedSEE < 0 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 4", "", ";A2VZ;", 100, -1000, 1000);
   PdfFile.AddPlot(Tree, "A3VZ", "ExpectedSEM == 1000 && ExpectedSEE < 0 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 5", "", ";A3VZ;", 100, -1000, 1000);
   PdfFile.AddPlot(Tree, "A1VA", "ExpectedSEM == 1000 && ExpectedSEE < 0 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 6", "", ";A1VA;", 100, -0.01, 0.01);
   PdfFile.AddPlot(Tree, "A2VA", "ExpectedSEM == 1000 && ExpectedSEE < 0 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 7", "", ";A2VA;", 100, -10, 10);
   PdfFile.AddPlot(Tree, "A3VA", "ExpectedSEM == 1000 && ExpectedSEE < 0 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 8", "", ";A3VA;", 100, -10, 10);
   
   PdfFile.AddTextPage("Float individually (4e)");
   PdfFile.AddPlot(Tree, "A2VV", "ExpectedSEM < 0 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 1", "", ";A2VV;", 100, -100, 100);
   PdfFile.AddPlot(Tree, "A3VV", "ExpectedSEM < 0 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 2", "", ";A3VV;", 100, -100, 100);
   PdfFile.AddPlot(Tree, "A1VZ", "ExpectedSEM < 0 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 3", "", ";A1VZ;", 100, -20, 20);
   PdfFile.AddPlot(Tree, "A2VZ", "ExpectedSEM < 0 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 4", "", ";A2VZ;", 100, -1000, 1000);
   PdfFile.AddPlot(Tree, "A3VZ", "ExpectedSEM < 0 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 5", "", ";A3VZ;", 100, -1000, 1000);
   PdfFile.AddPlot(Tree, "A1VA", "ExpectedSEM < 0 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 6", "", ";A1VA;", 100, -0.01, 0.01);
   PdfFile.AddPlot(Tree, "A2VA", "ExpectedSEM < 0 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 7", "", ";A2VA;", 100, -10, 10);
   PdfFile.AddPlot(Tree, "A3VA", "ExpectedSEM < 0 && ExpectedSEE == 1000 && ExpectedBEM < 0 && Mode == 0 && FloatMode == 8", "", ";A3VA;", 100, -10, 10);

   File.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}
