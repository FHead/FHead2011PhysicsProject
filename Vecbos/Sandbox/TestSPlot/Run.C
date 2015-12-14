{
   gSystem->Load("MLSPlot_cc.so");
   gROOT->ProcessLine(".L PlotSPlot.C+");
   gROOT->ProcessLine("PlotSPlot()");
}
