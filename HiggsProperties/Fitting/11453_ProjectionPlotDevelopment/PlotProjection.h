#include <iostream>
#include <vector>

#include "TFile.h"
#include "TGraph.h"
#include "TTree.h"

#include "PlotHelper2.h"

std::string GetName(std::string Component, std::string Type, std::string Range, bool LogX = false, bool XWeight = false);
void FillBackgroundGraph(TGraph &Graph, TFile &File, std::string Component, double DURatio);
void FillSignalGraph(TGraph &Graph, TFile &File, std::string Component, std::string Type);
void ScaleGraph(TGraph &Graph, double Factor);
void AddGraph(TGraph &Graph1, TGraph &Graph2, double Factor = 1);
void NormalizeGraph(TGraph &Graph);
double GraphFindMaximum(TGraph &Graph);
double IntegrateGraph(TGraph &Graph);
void FillToHistogram(TH1D &H, TTree &T, std::string BranchName, std::vector<int> Indices);

void ProduceOverlayPlots_BA1A3(PsFileHelper &PsFile, TH1D *Data, std::string Component,
   TFile &BackgroundFile, TFile &SignalFile, double Fraction, double A1, double A3);






