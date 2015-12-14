#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TGraph.h"

void PlotTwoColumnFile(char *filename, char *outputfilename)
{
   ifstream in(filename);

   TFile out(outputfilename, "RECREATE");

   vector<double> xData;
   vector<double> yData;

   while(in)
   {
      double xTemp = 0;
      double yTemp = 0;

      in >> xTemp >> yTemp;

      xData.push_back(xTemp);
      yData.push_back(yTemp);
   }

   double *xArray = new double[xData.size()];
   double *yArray = new double[yData.size()];

   for(int i = 0; i < (int)xData.size(); i++)
   {
      xArray[i] = xData[i];
      yArray[i] = yData[i];
   }

   TGraph graph(xData.size(), xArray, yArray);
   graph.Write();

   delete[] yArray;
   delete[] xArray;

   out.Close();

   in.close();
}
