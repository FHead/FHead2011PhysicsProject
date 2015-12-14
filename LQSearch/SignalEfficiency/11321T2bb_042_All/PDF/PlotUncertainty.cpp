#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "TH2D.h"

#include "SetStyle.h"
#include "PlotHelper2.h"

class MassPoint;
int main();
vector<MassPoint> ReadFile(string FileName);

class MassPoint
{
public:
   int M0;
   int M12;
   double Up;
   double Down;
};

int main()
{
   SetStyle();

   vector<MassPoint> CTEQResult = ReadFile("CTEQResult");
   vector<MassPoint> MRSTResult = ReadFile("MRSTResult");
   vector<MassPoint> NNPDFResult = ReadFile("NNPDFResult");

   TH2D HCTEQUp("HCTEQUp", "CTEQ PDF set, (+);sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);   
   TH2D HCTEQDown("HCTEQDown", "CTEQ PDF set, (-);sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);
   TH2D HCTEQAverage("HCTEQAverage", "CTEQ PDF set;sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);
   TH2D HMRSTUp("HMRSTUp", "MRST PDF set, (+);sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);   
   TH2D HMRSTDown("HMRSTDown", "MRST PDF set, (-);sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);
   TH2D HMRSTAverage("HMRSTAverage", "MRST PDF set;sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);
   TH2D HNNPDFUp("HNNPDFUp", "NNPDF PDF set, (+);sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);   
   TH2D HNNPDFDown("HNNPDFDown", "NNPDF PDF set, (-);sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);
   TH2D HNNPDFAverage("HNNPDFAverage", "NNPDF PDF set;sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);
   TH2D HMax("HMax", "Max variation;sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);
   TH2D HMin("HMin", "Min variation;sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);
   TH2D HCenter("HCenter", "Center;sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);
   TH2D HVariation("HVariation", "Variation;sbottom;neutralino", 50, 0, 1250, 50, 0, 1250);

   for(int i = 0; i < (int)CTEQResult.size(); i++)
   {
      HCTEQUp.Fill(CTEQResult[i].M0, CTEQResult[i].M12, CTEQResult[i].Up);
      HCTEQDown.Fill(CTEQResult[i].M0, CTEQResult[i].M12, CTEQResult[i].Down);
      HCTEQAverage.Fill(CTEQResult[i].M0, CTEQResult[i].M12, (CTEQResult[i].Down + CTEQResult[i].Up) / 2);
   }
   for(int i = 0; i < (int)MRSTResult.size(); i++)
   {
      HMRSTUp.Fill(MRSTResult[i].M0, MRSTResult[i].M12, MRSTResult[i].Up);
      HMRSTDown.Fill(MRSTResult[i].M0, MRSTResult[i].M12, MRSTResult[i].Down);
      HMRSTAverage.Fill(MRSTResult[i].M0, MRSTResult[i].M12, (MRSTResult[i].Down + MRSTResult[i].Up) / 2);
   }
   for(int i = 0; i < (int)NNPDFResult.size(); i++)
   {
      HNNPDFUp.Fill(NNPDFResult[i].M0, NNPDFResult[i].M12, NNPDFResult[i].Up);
      HNNPDFDown.Fill(NNPDFResult[i].M0, NNPDFResult[i].M12, NNPDFResult[i].Down);
      HNNPDFAverage.Fill(NNPDFResult[i].M0, NNPDFResult[i].M12, (NNPDFResult[i].Down + NNPDFResult[i].Up) / 2);
   }

   HCTEQUp.SetStats(0);
   HCTEQDown.SetStats(0);
   HCTEQAverage.SetStats(0);
   HMRSTUp.SetStats(0);
   HMRSTDown.SetStats(0);
   HMRSTAverage.SetStats(0);
   HNNPDFUp.SetStats(0);
   HNNPDFDown.SetStats(0);
   HNNPDFAverage.SetStats(0);

   HCTEQUp.SetMaximum(1);
   HCTEQDown.SetMaximum(1);
   HCTEQAverage.SetMaximum(1);
   HMRSTUp.SetMaximum(1);
   HMRSTDown.SetMaximum(1);
   HMRSTAverage.SetMaximum(1);
   HNNPDFUp.SetMaximum(1);
   HNNPDFDown.SetMaximum(1);
   HNNPDFAverage.SetMaximum(1);
   
   HCTEQUp.SetMinimum(0.0001);
   HCTEQDown.SetMinimum(0.0001);
   HCTEQAverage.SetMinimum(0.0001);
   HMRSTUp.SetMinimum(0.0001);
   HMRSTDown.SetMinimum(0.0001);
   HMRSTAverage.SetMinimum(0.0001);
   HNNPDFUp.SetMinimum(0.0001);
   HNNPDFDown.SetMinimum(0.0001);
   HNNPDFAverage.SetMinimum(0.0001);

   PsFileHelper PsFile("PDFShit.ps");
   PsFile.AddTextPage("PDF for T2bb models - acceptance, not cross section");

   vector<string> Explanations;
   Explanations.push_back("Starting from T2bb sample, take the weights stored in vecbos ntuple");
   Explanations.push_back("Follow same calculation as ElectroWeakAnalysis/Utilities/PdfSystematicsAnalyzer");
   Explanations.push_back("Calculate acceptance uncertainty due to PDF");
   Explanations.push_back("Repeat with CTEQ66, MRST2006NNLO and NNPDF10100");
   Explanations.push_back("");
   Explanations.push_back("Close to diagonal where we need ISR uncertainty goes up");
   Explanations.push_back("However in the region of sbottom - neutralino mass ~ 200 and sbottom heavy");
   Explanations.push_back("      that feature (maybe slight dip) is not well-understood");
   Explanations.push_back("Also what's wrong with NNPDF... (red means >= 100%)");
   Explanations.push_back("");
   Explanations.push_back("Color indicate relative uncertainty; green = 0.01 = 1\% relative to acceptance");
   Explanations.push_back("Uncertainty comes as +x / -y");
   Explanations.push_back("x is plotted on (+) histogram, y plotted on (-).  The third one is (x+y)/2");
   PsFile.AddTextPage(Explanations);

   PsFile.AddPlot(HCTEQUp, "colz", false, true);
   PsFile.AddPlot(HCTEQDown, "colz", false, true);
   PsFile.AddPlot(HCTEQAverage, "colz", false, true);
   PsFile.AddPlot(HMRSTUp, "colz", false, true);
   PsFile.AddPlot(HMRSTDown, "colz", false, true);
   PsFile.AddPlot(HMRSTAverage, "colz", false, true);
   PsFile.AddPlot(HNNPDFUp, "colz", false, true);
   PsFile.AddPlot(HNNPDFDown, "colz", false, true);
   PsFile.AddPlot(HNNPDFAverage, "colz", false, true);

   vector<string> Questions;
   Questions.push_back("Now I have a few questions on this:");
   Questions.push_back("");
   Questions.push_back("1. which one do we apply to the sample?  max(PDF sets) per point?");
   Questions.push_back("2. fluctuations are large across points within PDF set");
   Questions.push_back("      any suggestions on how to smooth it?");
   Questions.push_back("3. do we see similar structure in the SUSY result?");
   PsFile.AddTextPage(Questions);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   return 0;
}

vector<MassPoint> ReadFile(string FileName)
{
   vector<MassPoint> Result;

   ifstream in(FileName.c_str());

   while(in)
   {
      MassPoint Point;

      Point.M0 = -100;
      Point.M12 = -100;
      Point.Up = 0;
      Point.Down = 0;

      in >> Point.M0 >> Point.M12 >> Point.Up >> Point.Down;

      Result.push_back(Point);
   }

   in.close();

   return Result;
}





