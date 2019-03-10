#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TChain.h"
#include "TCanvas.h"

#include "PlotHelper3.h"
#include "SetStyle.h"

int main();
void AddPlot(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string Plot, string Selection, string Title, int N, double Min, double Max, bool LogY = false);

int main()
{
   string TreeName = "ak4PFJetAnalyzer/t";
   string TreeName2 = "ak4CaloJetAnalyzer/t";
   string TreeName3 = "akCs4PFJetAnalyzer/t";

   SetThesisStyle();

   PdfFileHelper PdfFile("Plots.pdf");
   PdfFile.AddTextPage("Prompt reco vs relval");

   TChain T1("T1");
   TChain T2("T2");
   TChain T3("T3");
   TChain T4("T4");
   TChain T5("T5");
   TChain T6("T6");

   T1.AddFile("92X/HiForestAOD_100.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_101.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_102.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_103.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_104.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_105.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_106.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_107.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_108.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_109.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_110.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_112.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_113.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_114.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_115.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_116.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_117.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_118.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_119.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_120.root", TTree::kMaxEntries, TreeName.c_str());
   /*
   T1.AddFile("92X/HiForestAOD_121.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_122.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_123.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_124.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_125.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_126.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_128.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_129.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_130.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_131.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_132.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_133.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_134.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_135.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_136.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_137.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_138.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_139.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_140.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_141.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_142.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_143.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_144.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_145.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_146.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_147.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_148.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_149.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_150.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_151.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_152.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_153.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_154.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_155.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_156.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_157.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_158.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_159.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_160.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_161.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_27.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_28.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_29.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_30.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_31.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_32.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_33.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_34.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_35.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_36.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_37.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_38.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_39.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_40.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_41.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_42.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_43.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_44.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_45.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_46.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_47.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_48.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_49.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_50.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_51.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_52.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_53.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_54.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_55.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_57.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_58.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_59.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_60.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_61.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_62.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_63.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_64.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_65.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_66.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_67.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_68.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_70.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_71.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_72.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_73.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_74.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_75.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_76.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_77.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_78.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_79.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_80.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_81.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_82.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_83.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_84.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_85.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_86.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_87.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_88.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_89.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_90.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_91.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_92.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_93.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_94.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_95.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_97.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_98.root", TTree::kMaxEntries, TreeName.c_str());
   T1.AddFile("92X/HiForestAOD_99.root", TTree::kMaxEntries, TreeName.c_str());
   */
   
   T2.AddFile("94X/HiForest_0.root", TTree::kMaxEntries, TreeName.c_str());
   T2.AddFile("94X/HiForest_1.root", TTree::kMaxEntries, TreeName.c_str());
   T2.AddFile("94X/HiForest_2.root", TTree::kMaxEntries, TreeName.c_str());
   T2.AddFile("94X/HiForest_5.root", TTree::kMaxEntries, TreeName.c_str());
   T2.AddFile("94X/HiForest_6.root", TTree::kMaxEntries, TreeName.c_str());
   T2.AddFile("94X/HiForest_7.root", TTree::kMaxEntries, TreeName.c_str());
   T2.AddFile("94X/HiForest_8.root", TTree::kMaxEntries, TreeName.c_str());
   T2.AddFile("94X/HiForest_9.root", TTree::kMaxEntries, TreeName.c_str());
   T2.AddFile("94X/HiForest_10.root", TTree::kMaxEntries, TreeName.c_str());

   T3.AddFile("92X/HiForestAOD_100.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_101.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_102.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_103.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_104.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_105.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_106.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_107.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_108.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_109.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_110.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_112.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_113.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_114.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_115.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_116.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_117.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_118.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_119.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_120.root", TTree::kMaxEntries, TreeName2.c_str());
   /*
   T3.AddFile("92X/HiForestAOD_121.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_122.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_123.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_124.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_125.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_126.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_128.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_129.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_130.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_131.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_132.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_133.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_134.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_135.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_136.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_137.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_138.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_139.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_140.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_141.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_142.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_143.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_144.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_145.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_146.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_147.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_148.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_149.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_150.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_151.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_152.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_153.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_154.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_155.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_156.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_157.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_158.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_159.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_160.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_161.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_27.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_28.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_29.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_30.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_31.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_32.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_33.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_34.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_35.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_36.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_37.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_38.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_39.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_40.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_41.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_42.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_43.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_44.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_45.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_46.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_47.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_48.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_49.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_50.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_51.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_52.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_53.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_54.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_55.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_57.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_58.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_59.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_60.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_61.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_62.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_63.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_64.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_65.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_66.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_67.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_68.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_70.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_71.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_72.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_73.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_74.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_75.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_76.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_77.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_78.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_79.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_80.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_81.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_82.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_83.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_84.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_85.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_86.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_87.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_88.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_89.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_90.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_91.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_92.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_93.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_94.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_95.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_97.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_98.root", TTree::kMaxEntries, TreeName2.c_str());
   T3.AddFile("92X/HiForestAOD_99.root", TTree::kMaxEntries, TreeName2.c_str());
   */
   
   T4.AddFile("94X/HiForest_0.root", TTree::kMaxEntries, TreeName2.c_str());
   T4.AddFile("94X/HiForest_1.root", TTree::kMaxEntries, TreeName2.c_str());
   T4.AddFile("94X/HiForest_2.root", TTree::kMaxEntries, TreeName2.c_str());
   T4.AddFile("94X/HiForest_5.root", TTree::kMaxEntries, TreeName2.c_str());
   T4.AddFile("94X/HiForest_6.root", TTree::kMaxEntries, TreeName2.c_str());
   T4.AddFile("94X/HiForest_7.root", TTree::kMaxEntries, TreeName2.c_str());
   T4.AddFile("94X/HiForest_8.root", TTree::kMaxEntries, TreeName2.c_str());
   T4.AddFile("94X/HiForest_9.root", TTree::kMaxEntries, TreeName2.c_str());
   T4.AddFile("94X/HiForest_10.root", TTree::kMaxEntries, TreeName2.c_str());

   T5.AddFile("92X/HiForestAOD_100.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_101.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_102.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_103.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_104.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_105.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_106.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_107.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_108.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_109.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_110.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_112.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_113.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_114.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_115.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_116.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_117.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_118.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_119.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_120.root", TTree::kMaxEntries, TreeName3.c_str());
   /*
   T5.AddFile("92X/HiForestAOD_121.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_122.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_123.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_124.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_125.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_126.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_128.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_129.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_130.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_131.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_132.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_133.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_134.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_135.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_136.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_137.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_138.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_139.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_140.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_141.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_142.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_143.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_144.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_145.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_146.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_147.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_148.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_149.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_150.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_151.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_152.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_153.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_154.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_155.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_156.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_157.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_158.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_159.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_160.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_161.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_27.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_28.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_29.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_30.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_31.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_32.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_33.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_34.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_35.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_36.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_37.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_38.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_39.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_40.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_41.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_42.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_43.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_44.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_45.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_46.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_47.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_48.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_49.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_50.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_51.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_52.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_53.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_54.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_55.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_57.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_58.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_59.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_60.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_61.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_62.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_63.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_64.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_65.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_66.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_67.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_68.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_70.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_71.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_72.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_73.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_74.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_75.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_76.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_77.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_78.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_79.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_80.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_81.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_82.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_83.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_84.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_85.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_86.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_87.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_88.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_89.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_90.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_91.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_92.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_93.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_94.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_95.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_97.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_98.root", TTree::kMaxEntries, TreeName3.c_str());
   T5.AddFile("92X/HiForestAOD_99.root", TTree::kMaxEntries, TreeName3.c_str());
   */
   
   T6.AddFile("94X/HiForest_0.root", TTree::kMaxEntries, TreeName3.c_str());
   T6.AddFile("94X/HiForest_1.root", TTree::kMaxEntries, TreeName3.c_str());
   T6.AddFile("94X/HiForest_2.root", TTree::kMaxEntries, TreeName3.c_str());
   T6.AddFile("94X/HiForest_5.root", TTree::kMaxEntries, TreeName3.c_str());
   T6.AddFile("94X/HiForest_6.root", TTree::kMaxEntries, TreeName3.c_str());
   T6.AddFile("94X/HiForest_7.root", TTree::kMaxEntries, TreeName3.c_str());
   T6.AddFile("94X/HiForest_8.root", TTree::kMaxEntries, TreeName3.c_str());
   T6.AddFile("94X/HiForest_9.root", TTree::kMaxEntries, TreeName3.c_str());
   T6.AddFile("94X/HiForest_10.root", TTree::kMaxEntries, TreeName3.c_str());
   
   PdfFile.AddTextPage("PF Jet Plots");

   AddPlot(PdfFile, &T1, &T2, "jteta", "jtpt > 0", "All jets;eta", 100, -4.5, 4.5, false);
   AddPlot(PdfFile, &T1, &T2, "jteta", "jtpt > 50", "PT > 50;eta", 100, -4.5, 4.5, false);
   AddPlot(PdfFile, &T1, &T2, "jteta", "jtpt > 100", "PT > 100;eta", 100, -4.5, 4.5, false);
   
   AddPlot(PdfFile, &T1, &T2, "jtpt", "", "All jets;PT", 50, 0, 400, true);
   AddPlot(PdfFile, &T1, &T2, "jtpt", "abs(jteta) < 1.5", "|eta| < 1.5;PT", 50, 0, 400, true);
   AddPlot(PdfFile, &T1, &T2, "jtpt", "abs(jteta) < 3.0 && abs(jteta) > 1.5", "1.5 < |eta| < 3.0;PT", 50, 0, 400, true);
   AddPlot(PdfFile, &T1, &T2, "jtpt", "abs(jteta) > 3.0", "|eta| > 3.0;PT", 50, 0, 400, true);

   AddPlot(PdfFile, &T1, &T2, "jteta", "rawpt > 50", "Raw PT > 50;eta", 100, -4.5, 4.5, false);
   AddPlot(PdfFile, &T1, &T2, "jteta", "rawpt > 100", "Raw PT > 100;eta", 100, -4.5, 4.5, false);
   
   AddPlot(PdfFile, &T1, &T2, "rawpt", "", "All jets;Raw PT", 50, 0, 400, true);
   AddPlot(PdfFile, &T1, &T2, "rawpt", "abs(jteta) < 1.5", "|eta| < 1.5;Raw PT", 50, 0, 400, true);
   AddPlot(PdfFile, &T1, &T2, "rawpt", "abs(jteta) < 3.0 && abs(jteta) > 1.5", "1.5 < |eta| < 3.0;Raw PT", 50, 0, 400, true);
   AddPlot(PdfFile, &T1, &T2, "rawpt", "abs(jteta) > 3.0", "|eta| > 3.0;Raw PT", 50, 0, 400, true);

   PdfFile.AddTextPage("Calo Jet Plots");

   AddPlot(PdfFile, &T3, &T4, "jteta", "jtpt > 0", "All jets;eta", 100, -4.5, 4.5, false);
   AddPlot(PdfFile, &T3, &T4, "jteta", "jtpt > 50", "PT > 50;eta", 100, -4.5, 4.5, false);
   AddPlot(PdfFile, &T3, &T4, "jteta", "jtpt > 100", "PT > 100;eta", 100, -4.5, 4.5, false);
   
   AddPlot(PdfFile, &T3, &T4, "jtpt", "", "All jets;PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T3, &T4, "jtpt", "abs(jteta) < 1.5", "|eta| < 1.5;PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T3, &T4, "jtpt", "abs(jteta) < 3.0 && abs(jteta) > 1.5", "1.5 < |eta| < 3.0;PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T3, &T4, "jtpt", "abs(jteta) > 3.0", "|eta| > 3.0;PT", 50, 0, 200, true);

   AddPlot(PdfFile, &T3, &T4, "jteta", "rawpt > 50", "Raw PT > 50;eta", 100, -4.5, 4.5, false);
   AddPlot(PdfFile, &T3, &T4, "jteta", "rawpt > 100", "Raw PT > 100;eta", 100, -4.5, 4.5, false);
   
   AddPlot(PdfFile, &T3, &T4, "rawpt", "", "All jets;Raw PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T3, &T4, "rawpt", "abs(jteta) < 1.5", "|eta| < 1.5;Raw PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T3, &T4, "rawpt", "abs(jteta) < 3.0 && abs(jteta) > 1.5", "1.5 < |eta| < 3.0;Raw PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T3, &T4, "rawpt", "abs(jteta) > 3.0", "|eta| > 3.0;Raw PT", 50, 0, 200, true);

   PdfFile.AddTextPage("CS PF Jet Plots");

   AddPlot(PdfFile, &T5, &T6, "jteta", "jtpt > 0", "All jets;eta", 100, -4.5, 4.5, false);
   AddPlot(PdfFile, &T5, &T6, "jteta", "jtpt > 50", "PT > 50;eta", 100, -4.5, 4.5, false);
   AddPlot(PdfFile, &T5, &T6, "jteta", "jtpt > 100", "PT > 100;eta", 100, -4.5, 4.5, false);
   
   AddPlot(PdfFile, &T5, &T6, "jtpt", "", "All jets;PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T5, &T6, "jtpt", "abs(jteta) < 1.5", "|eta| < 1.5;PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T5, &T6, "jtpt", "abs(jteta) < 3.0 && abs(jteta) > 1.5", "1.5 < |eta| < 3.0;PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T5, &T6, "jtpt", "abs(jteta) > 3.0", "|eta| > 3.0;PT", 50, 0, 200, true);

   AddPlot(PdfFile, &T5, &T6, "jteta", "rawpt > 50", "Raw PT > 50;eta", 100, -4.5, 4.5, false);
   AddPlot(PdfFile, &T5, &T6, "jteta", "rawpt > 100", "Raw PT > 100;eta", 100, -4.5, 4.5, false);
   
   AddPlot(PdfFile, &T5, &T6, "rawpt", "", "All jets;Raw PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T5, &T6, "rawpt", "abs(jteta) < 1.5", "|eta| < 1.5;Raw PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T5, &T6, "rawpt", "abs(jteta) < 3.0 && abs(jteta) > 1.5", "1.5 < |eta| < 3.0;Raw PT", 50, 0, 200, true);
   AddPlot(PdfFile, &T5, &T6, "rawpt", "abs(jteta) > 3.0", "|eta| > 3.0;Raw PT", 50, 0, 200, true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}

void AddPlot(PdfFileHelper &PdfFile, TTree *T1, TTree *T2, string Plot, string Selection, string Title, int N, double Min, double Max, bool LogY)
{
   cout << "Start plotting \"" << Plot << "\" with selection \"" << Selection << "\"" << endl;

   TH1D H1("H1", Title.c_str(), N, Min, Max);
   TH1D H2("H2", Title.c_str(), N, Min, Max);

   if(T1 != NULL)   T1->Draw((Plot + ">>H1").c_str(), Selection.c_str());
   if(T2 != NULL)   T2->Draw((Plot + ">>H2").c_str(), Selection.c_str());

   if(H1.Integral() > 0)   H1.Scale(1 / H1.Integral());
   if(H2.Integral() > 0)   H2.Scale(1 / H2.Integral());

   H1.SetStats(0);
   H2.SetStats(0);

   H2.SetLineColor(kRed);
   H2.SetMarkerColor(kRed);

   TCanvas C;

   H1.Draw();   
   H2.Draw("same");

   if(LogY == true)
      C.SetLogy();

   PdfFile.AddCanvas(C);

   C.SetLogy(false);

   H2.Divide(&H1);

   H2.SetMaximum(2);
   H2.SetMinimum(0);

   H2.GetYaxis()->SetTitle("RelVal / Prompt");

   H2.Draw();

   PdfFile.AddCanvas(C);
}





