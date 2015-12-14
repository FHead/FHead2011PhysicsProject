#include <cmath>
#include <string>
#include <map>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TColor.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"

#include "PlotHelper2.h"
#include "SetStyle.h"
#include "ReadLQ3Tree.h"

int main(int argc, char *argv[]);
void JetPTThresholdEfficiency(string InputFileName, string OutputBase);
void Get1DCumulativeHistogram(TH1D &Source, TH1D &Destination);
double DeterminePT(multimap<double, int, greater<double> > &List);
double DeterminePT(multimap<double, int, greater<double> > &List1, multimap<double, int, greater<double> > &List2);

int main(int argc, char *argv[])
{
   SetStyle();

   string Tag = "LQ450";
   if(argc > 1)
      Tag = argv[1];

   string InputFileName = "Samples/" + Tag + ".root";
   string OutputBase = Tag;

   JetPTThresholdEfficiency(InputFileName, OutputBase);
}

void JetPTThresholdEfficiency(string InputFileName, string OutputBase)
{
   TH1D HPTPassTCHEL("HPTPassTCHEL", "PT passing TCHEL", 400, 0, 200);
   TH1D HPTPassTCHEM("HPTPassTCHEM", "PT passing TCHEM", 400, 0, 200);
   TH1D HPTPassTCHET("HPTPassTCHET", "PT passing TCHET", 400, 0, 200);
   TH1D HPTPassTCHPL("HPTPassTCHPL", "PT passing TCHPL", 400, 0, 200);
   TH1D HPTPassTCHPM("HPTPassTCHPM", "PT passing TCHPM", 400, 0, 200);
   TH1D HPTPassTCHPT("HPTPassTCHPT", "PT passing TCHPT", 400, 0, 200);

   TH1D HPTPassTCHELTCHEL("HPTPassTCHELTCHEL", "PT passing TCHEL x TCHEL", 400, 0, 200);
   TH1D HPTPassTCHELTCHEM("HPTPassTCHELTCHEM", "PT passing TCHEL x TCHEM", 400, 0, 200);
   TH1D HPTPassTCHELTCHET("HPTPassTCHELTCHET", "PT passing TCHEL x TCHET", 400, 0, 200);
   TH1D HPTPassTCHELTCHPL("HPTPassTCHELTCHPL", "PT passing TCHEL x TCHPL", 400, 0, 200);
   TH1D HPTPassTCHELTCHPM("HPTPassTCHELTCHPM", "PT passing TCHEL x TCHPM", 400, 0, 200);
   TH1D HPTPassTCHELTCHPT("HPTPassTCHELTCHPT", "PT passing TCHEL x TCHPT", 400, 0, 200);
   TH1D HPTPassTCHEMTCHEM("HPTPassTCHEMTCHEM", "PT passing TCHEM x TCHEM", 400, 0, 200);
   TH1D HPTPassTCHEMTCHET("HPTPassTCHEMTCHET", "PT passing TCHEM x TCHET", 400, 0, 200);
   TH1D HPTPassTCHEMTCHPL("HPTPassTCHEMTCHPL", "PT passing TCHEM x TCHPL", 400, 0, 200);
   TH1D HPTPassTCHEMTCHPM("HPTPassTCHEMTCHPM", "PT passing TCHEM x TCHPM", 400, 0, 200);
   TH1D HPTPassTCHEMTCHPT("HPTPassTCHEMTCHPT", "PT passing TCHEM x TCHPT", 400, 0, 200);
   TH1D HPTPassTCHETTCHET("HPTPassTCHETTCHET", "PT passing TCHET x TCHET", 400, 0, 200);
   TH1D HPTPassTCHETTCHPL("HPTPassTCHETTCHPL", "PT passing TCHET x TCHPL", 400, 0, 200);
   TH1D HPTPassTCHETTCHPM("HPTPassTCHETTCHPM", "PT passing TCHET x TCHPM", 400, 0, 200);
   TH1D HPTPassTCHETTCHPT("HPTPassTCHETTCHPT", "PT passing TCHET x TCHPT", 400, 0, 200);
   TH1D HPTPassTCHPLTCHPL("HPTPassTCHPLTCHPL", "PT passing TCHPL x TCHPL", 400, 0, 200);
   TH1D HPTPassTCHPLTCHPM("HPTPassTCHPLTCHPM", "PT passing TCHPL x TCHPM", 400, 0, 200);
   TH1D HPTPassTCHPLTCHPT("HPTPassTCHPLTCHPT", "PT passing TCHPL x TCHPT", 400, 0, 200);
   TH1D HPTPassTCHPMTCHPM("HPTPassTCHPMTCHPM", "PT passing TCHPM x TCHPM", 400, 0, 200);
   TH1D HPTPassTCHPMTCHPT("HPTPassTCHPMTCHPT", "PT passing TCHPM x TCHPT", 400, 0, 200);
   TH1D HPTPassTCHPTTCHPT("HPTPassTCHPTTCHPT", "PT passing TCHPT x TCHPT", 400, 0, 200);

   TFile F(InputFileName.c_str());
   TTree *Tree = (TTree *)F.Get("LQ3Tree");
   if(Tree == NULL)
      return;

   TreeRecord M;
   M.SetBranchAddress(Tree);

   int EntryCount = Tree->GetEntries();   cout << "Total entry = " << EntryCount << endl;
   for(int iEntry = 1; iEntry <= EntryCount; iEntry++)
   {
      if(iEntry % 500000 == 0)
         cout << "Processing entry " << iEntry << "/" << EntryCount << endl;

      M.Clear();
      Tree->GetEntry(iEntry - 1);

      multimap<double, int, greater<double> > JetPassTCHEL;
      multimap<double, int, greater<double> > JetPassTCHEM;
      multimap<double, int, greater<double> > JetPassTCHET;
      multimap<double, int, greater<double> > JetPassTCHPL;
      multimap<double, int, greater<double> > JetPassTCHPM;
      multimap<double, int, greater<double> > JetPassTCHPT;

      for(int i = 0; i < M.CaloJetCount; i++)
      {
         if(M.CaloJetEta[i] < -3 || M.CaloJetEta[i] > 3)
            continue;

         if(M.CaloJetTCHETag[i] > 1.7)
            JetPassTCHEL.insert(pair<double, int>(M.CaloJetPT[i], i));
         if(M.CaloJetTCHETag[i] > 3.3)
            JetPassTCHEM.insert(pair<double, int>(M.CaloJetPT[i], i));
         if(M.CaloJetTCHETag[i] > 10.2)
            JetPassTCHET.insert(pair<double, int>(M.CaloJetPT[i], i));
         if(M.CaloJetTCHPTag[i] > 1.19)
            JetPassTCHPL.insert(pair<double, int>(M.CaloJetPT[i], i));
         if(M.CaloJetTCHPTag[i] > 1.93)
            JetPassTCHPM.insert(pair<double, int>(M.CaloJetPT[i], i));
         if(M.CaloJetTCHPTag[i] > 3.41)
            JetPassTCHPT.insert(pair<double, int>(M.CaloJetPT[i], i));
      }

      HPTPassTCHEL.Fill(DeterminePT(JetPassTCHEL));
      HPTPassTCHEM.Fill(DeterminePT(JetPassTCHEM));
      HPTPassTCHET.Fill(DeterminePT(JetPassTCHET));
      HPTPassTCHPL.Fill(DeterminePT(JetPassTCHPL));
      HPTPassTCHPM.Fill(DeterminePT(JetPassTCHPM));
      HPTPassTCHPT.Fill(DeterminePT(JetPassTCHPT));

      HPTPassTCHELTCHEL.Fill(DeterminePT(JetPassTCHEL, JetPassTCHEL));
      HPTPassTCHELTCHEM.Fill(DeterminePT(JetPassTCHEL, JetPassTCHEM));
      HPTPassTCHELTCHET.Fill(DeterminePT(JetPassTCHEL, JetPassTCHET));
      HPTPassTCHELTCHPL.Fill(DeterminePT(JetPassTCHEL, JetPassTCHPL));
      HPTPassTCHELTCHPM.Fill(DeterminePT(JetPassTCHEL, JetPassTCHPM));
      HPTPassTCHELTCHPT.Fill(DeterminePT(JetPassTCHEL, JetPassTCHPT));
      HPTPassTCHEMTCHEM.Fill(DeterminePT(JetPassTCHEM, JetPassTCHEM));
      HPTPassTCHEMTCHET.Fill(DeterminePT(JetPassTCHEM, JetPassTCHET));
      HPTPassTCHEMTCHPL.Fill(DeterminePT(JetPassTCHEM, JetPassTCHPL));
      HPTPassTCHEMTCHPM.Fill(DeterminePT(JetPassTCHEM, JetPassTCHPM));
      HPTPassTCHEMTCHPT.Fill(DeterminePT(JetPassTCHEM, JetPassTCHPT));
      HPTPassTCHETTCHET.Fill(DeterminePT(JetPassTCHET, JetPassTCHET));
      HPTPassTCHETTCHPL.Fill(DeterminePT(JetPassTCHET, JetPassTCHPL));
      HPTPassTCHETTCHPM.Fill(DeterminePT(JetPassTCHET, JetPassTCHPM));
      HPTPassTCHETTCHPT.Fill(DeterminePT(JetPassTCHET, JetPassTCHPT));
      HPTPassTCHPLTCHPL.Fill(DeterminePT(JetPassTCHPL, JetPassTCHPL));
      HPTPassTCHPLTCHPM.Fill(DeterminePT(JetPassTCHPL, JetPassTCHPM));
      HPTPassTCHPLTCHPT.Fill(DeterminePT(JetPassTCHPL, JetPassTCHPT));
      HPTPassTCHPMTCHPM.Fill(DeterminePT(JetPassTCHPM, JetPassTCHPM));
      HPTPassTCHPMTCHPT.Fill(DeterminePT(JetPassTCHPM, JetPassTCHPT));
      HPTPassTCHPTTCHPT.Fill(DeterminePT(JetPassTCHPT, JetPassTCHPT));
   }

   TH1D HPercentagePassTCHEL("HPercentagePassTCHEL",
      "Percentage remaining passing TCHEL as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHEM("HPercentagePassTCHEM",
      "Percentage remaining passing TCHEM as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHET("HPercentagePassTCHET",
      "Percentage remaining passing TCHET as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHPL("HPercentagePassTCHPL",
      "Percentage remaining passing TCHPL as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHPM("HPercentagePassTCHPM",
      "Percentage remaining passing TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHPT("HPercentagePassTCHPT",
      "Percentage remaining passing TCHPT as a function of threshold;PT", 400, 0, 200);
   
   TH1D HPercentagePassTCHELTCHEL("HPercentagePassTCHELTCHEL",
      "Percentage remaining passing TCHEL x TCHEL as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHELTCHEM("HPercentagePassTCHELTCHEM",
      "Percentage remaining passing TCHEL x TCHEM as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHELTCHET("HPercentagePassTCHELTCHET",
      "Percentage remaining passing TCHEL x TCHET as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHELTCHPL("HPercentagePassTCHELTCHPL",
      "Percentage remaining passing TCHEL x TCHPL as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHELTCHPM("HPercentagePassTCHELTCHPM",
      "Percentage remaining passing TCHEL x TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHELTCHPT("HPercentagePassTCHELTCHPT",
      "Percentage remaining passing TCHEL x TCHPT as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHEMTCHEM("HPercentagePassTCHEMTCHEM",
      "Percentage remaining passing TCHEM x TCHEM as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHEMTCHET("HPercentagePassTCHEMTCHET",
      "Percentage remaining passing TCHEM x TCHET as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHEMTCHPL("HPercentagePassTCHEMTCHPL",
      "Percentage remaining passing TCHEM x TCHPL as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHEMTCHPM("HPercentagePassTCHEMTCHPM",
      "Percentage remaining passing TCHEM x TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHEMTCHPT("HPercentagePassTCHEMTCHPT",
      "Percentage remaining passing TCHEM x TCHPT as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHETTCHET("HPercentagePassTCHETTCHET",
      "Percentage remaining passing TCHET x TCHET as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHETTCHPL("HPercentagePassTCHETTCHPL",
      "Percentage remaining passing TCHET x TCHPL as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHETTCHPM("HPercentagePassTCHETTCHPM",
      "Percentage remaining passing TCHET x TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHETTCHPT("HPercentagePassTCHETTCHPT",
      "Percentage remaining passing TCHET x TCHPT as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHPLTCHPL("HPercentagePassTCHPLTCHPL",
      "Percentage remaining passing TCHPL x TCHPL as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHPLTCHPM("HPercentagePassTCHPLTCHPM",
      "Percentage remaining passing TCHPL x TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHPLTCHPT("HPercentagePassTCHPLTCHPT",
      "Percentage remaining passing TCHPL x TCHPT as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHPMTCHPM("HPercentagePassTCHPMTCHPM",
      "Percentage remaining passing TCHPM x TCHPM as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHPMTCHPT("HPercentagePassTCHPMTCHPT",
      "Percentage remaining passing TCHPM x TCHPT as a function of threshold;PT", 400, 0, 200);
   TH1D HPercentagePassTCHPTTCHPT("HPercentagePassTCHPTTCHPT",
      "Percentage remaining passing TCHPT x TCHPT as a function of threshold;PT", 400, 0, 200);

   Get1DCumulativeHistogram(HPTPassTCHEL, HPercentagePassTCHEL);
   Get1DCumulativeHistogram(HPTPassTCHEM, HPercentagePassTCHEM);
   Get1DCumulativeHistogram(HPTPassTCHET, HPercentagePassTCHET);
   Get1DCumulativeHistogram(HPTPassTCHPL, HPercentagePassTCHPL);
   Get1DCumulativeHistogram(HPTPassTCHPM, HPercentagePassTCHPM);
   Get1DCumulativeHistogram(HPTPassTCHPT, HPercentagePassTCHPT);
   
   Get1DCumulativeHistogram(HPTPassTCHELTCHEL, HPercentagePassTCHELTCHEL);
   Get1DCumulativeHistogram(HPTPassTCHELTCHEM, HPercentagePassTCHELTCHEM);
   Get1DCumulativeHistogram(HPTPassTCHELTCHET, HPercentagePassTCHELTCHET);
   Get1DCumulativeHistogram(HPTPassTCHELTCHPL, HPercentagePassTCHELTCHPL);
   Get1DCumulativeHistogram(HPTPassTCHELTCHPM, HPercentagePassTCHELTCHPM);
   Get1DCumulativeHistogram(HPTPassTCHELTCHPT, HPercentagePassTCHELTCHPT);
   Get1DCumulativeHistogram(HPTPassTCHEMTCHEM, HPercentagePassTCHEMTCHEM);
   Get1DCumulativeHistogram(HPTPassTCHEMTCHET, HPercentagePassTCHEMTCHET);
   Get1DCumulativeHistogram(HPTPassTCHEMTCHPL, HPercentagePassTCHEMTCHPL);
   Get1DCumulativeHistogram(HPTPassTCHEMTCHPM, HPercentagePassTCHEMTCHPM);
   Get1DCumulativeHistogram(HPTPassTCHEMTCHPT, HPercentagePassTCHEMTCHPT);
   Get1DCumulativeHistogram(HPTPassTCHETTCHET, HPercentagePassTCHETTCHET);
   Get1DCumulativeHistogram(HPTPassTCHETTCHPL, HPercentagePassTCHETTCHPL);
   Get1DCumulativeHistogram(HPTPassTCHETTCHPM, HPercentagePassTCHETTCHPM);
   Get1DCumulativeHistogram(HPTPassTCHETTCHPT, HPercentagePassTCHETTCHPT);
   Get1DCumulativeHistogram(HPTPassTCHPLTCHPL, HPercentagePassTCHPLTCHPL);
   Get1DCumulativeHistogram(HPTPassTCHPLTCHPM, HPercentagePassTCHPLTCHPM);
   Get1DCumulativeHistogram(HPTPassTCHPLTCHPT, HPercentagePassTCHPLTCHPT);
   Get1DCumulativeHistogram(HPTPassTCHPMTCHPM, HPercentagePassTCHPMTCHPM);
   Get1DCumulativeHistogram(HPTPassTCHPMTCHPT, HPercentagePassTCHPMTCHPT);
   Get1DCumulativeHistogram(HPTPassTCHPTTCHPT, HPercentagePassTCHPTTCHPT);

   HPercentagePassTCHEL.Scale(1.0 / EntryCount);
   HPercentagePassTCHEM.Scale(1.0 / EntryCount);
   HPercentagePassTCHET.Scale(1.0 / EntryCount);
   HPercentagePassTCHPL.Scale(1.0 / EntryCount);
   HPercentagePassTCHPM.Scale(1.0 / EntryCount);
   HPercentagePassTCHPT.Scale(1.0 / EntryCount);
   
   HPercentagePassTCHELTCHEL.Scale(1.0 / EntryCount);
   HPercentagePassTCHELTCHEM.Scale(1.0 / EntryCount);
   HPercentagePassTCHELTCHET.Scale(1.0 / EntryCount);
   HPercentagePassTCHELTCHPL.Scale(1.0 / EntryCount);
   HPercentagePassTCHELTCHPM.Scale(1.0 / EntryCount);
   HPercentagePassTCHELTCHPT.Scale(1.0 / EntryCount);
   HPercentagePassTCHEMTCHEM.Scale(1.0 / EntryCount);
   HPercentagePassTCHEMTCHET.Scale(1.0 / EntryCount);
   HPercentagePassTCHEMTCHPL.Scale(1.0 / EntryCount);
   HPercentagePassTCHEMTCHPM.Scale(1.0 / EntryCount);
   HPercentagePassTCHEMTCHPT.Scale(1.0 / EntryCount);
   HPercentagePassTCHETTCHET.Scale(1.0 / EntryCount);
   HPercentagePassTCHETTCHPL.Scale(1.0 / EntryCount);
   HPercentagePassTCHETTCHPM.Scale(1.0 / EntryCount);
   HPercentagePassTCHETTCHPT.Scale(1.0 / EntryCount);
   HPercentagePassTCHPLTCHPL.Scale(1.0 / EntryCount);
   HPercentagePassTCHPLTCHPM.Scale(1.0 / EntryCount);
   HPercentagePassTCHPLTCHPT.Scale(1.0 / EntryCount);
   HPercentagePassTCHPMTCHPM.Scale(1.0 / EntryCount);
   HPercentagePassTCHPMTCHPT.Scale(1.0 / EntryCount);
   HPercentagePassTCHPTTCHPT.Scale(1.0 / EntryCount);

   PsFileHelper PsFile(OutputBase + ".ps");
   PsFile.AddTextPage("Jet PT threshold efficiency plots for " + OutputBase);

   vector<string> Explanations;
   Explanations.push_back("Where can we best set the jet pt threshold for counting b-jets?");
   Explanations.push_back("Set a threshold, evaluate efficiency on different samples for");
   Explanations.push_back("      both 1-tag and 2-tag cases, using all TCH working points");
   PsFile.AddTextPage(Explanations);

   vector<string> TableOfContentItems;
   TableOfContentItems.push_back("Jet PT distribution - single tag");
   TableOfContentItems.push_back("Efficiencies - single tag");
   TableOfContentItems.push_back("Jet PT distribution - double tag");
   TableOfContentItems.push_back("Efficiencies - double tag");

   vector<string> Destinations;
   Destinations.push_back("PTSingleTag");
   Destinations.push_back("EfficiencySingleTag");
   Destinations.push_back("PTDoubleTag");
   Destinations.push_back("EfficiencyDoubleTag");

   PsFile.AddTableOfContentPage(TableOfContentItems, Destinations);
   PsFile.InsertNamedDestination("TableOfContentPage");
   PsFile.SetAutomaticHomeButton(true, "TableOfContentPage");

   PsFile.AddTextPage("Jet PT distributions - single tag");
   PsFile.InsertNamedDestination("PTSingleTag");
   PsFile.AddPlot(HPTPassTCHEL, "", true);
   PsFile.AddPlot(HPTPassTCHEM, "", true);
   PsFile.AddPlot(HPTPassTCHET, "", true);
   PsFile.AddPlot(HPTPassTCHPL, "", true);
   PsFile.AddPlot(HPTPassTCHPM, "", true);
   PsFile.AddPlot(HPTPassTCHPT, "", true);
   
   PsFile.AddTextPage("EFficiency cutting on b-tagging - single tag");
   PsFile.InsertNamedDestination("EfficiencySingleTag");
   PsFile.AddPlot(HPercentagePassTCHEL, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHEM, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHET, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHPL, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHPM, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHPT, "", true, false, true);
   
   PsFile.AddTextPage("Jet PT distributions - double tag");
   PsFile.InsertNamedDestination("PTDoubleTag");
   PsFile.AddPlot(HPTPassTCHELTCHEL, "", true);
   PsFile.AddPlot(HPTPassTCHELTCHEM, "", true);
   PsFile.AddPlot(HPTPassTCHELTCHET, "", true);
   PsFile.AddPlot(HPTPassTCHELTCHPL, "", true);
   PsFile.AddPlot(HPTPassTCHELTCHPM, "", true);
   PsFile.AddPlot(HPTPassTCHELTCHPT, "", true);
   PsFile.AddPlot(HPTPassTCHEMTCHEM, "", true);
   PsFile.AddPlot(HPTPassTCHEMTCHET, "", true);
   PsFile.AddPlot(HPTPassTCHEMTCHPL, "", true);
   PsFile.AddPlot(HPTPassTCHEMTCHPM, "", true);
   PsFile.AddPlot(HPTPassTCHEMTCHPT, "", true);
   PsFile.AddPlot(HPTPassTCHETTCHET, "", true);
   PsFile.AddPlot(HPTPassTCHETTCHPL, "", true);
   PsFile.AddPlot(HPTPassTCHETTCHPM, "", true);
   PsFile.AddPlot(HPTPassTCHETTCHPT, "", true);
   PsFile.AddPlot(HPTPassTCHPLTCHPL, "", true);
   PsFile.AddPlot(HPTPassTCHPLTCHPM, "", true);
   PsFile.AddPlot(HPTPassTCHPLTCHPT, "", true);
   PsFile.AddPlot(HPTPassTCHPMTCHPM, "", true);
   PsFile.AddPlot(HPTPassTCHPMTCHPT, "", true);
   PsFile.AddPlot(HPTPassTCHPTTCHPT, "", true);

   PsFile.AddTextPage("Efficiency cutting on b-tag - double tags");
   PsFile.InsertNamedDestination("EfficiencyDoubleTag");
   PsFile.AddPlot(HPercentagePassTCHELTCHEL, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHELTCHEM, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHELTCHET, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHELTCHPL, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHELTCHPM, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHELTCHPT, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHEMTCHEM, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHEMTCHET, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHEMTCHPL, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHEMTCHPM, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHEMTCHPT, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHETTCHET, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHETTCHPL, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHETTCHPM, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHETTCHPT, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHPLTCHPL, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHPLTCHPM, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHPLTCHPT, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHPMTCHPM, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHPMTCHPT, "", true, false, true);
   PsFile.AddPlot(HPercentagePassTCHPTTCHPT, "", true, false, true);

   PsFile.AddTimeStampPage();
   PsFile.Close();

   F.Close();
}

void Get1DCumulativeHistogram(TH1D &Source, TH1D &Destination)
{
   Destination.SetBinContent(Source.GetNbinsX(), Source.GetBinContent(Source.GetNbinsX()));
   for(int i = Destination.GetNbinsX() - 1; i >= 1; i--)
      Destination.SetBinContent(i, Destination.GetBinContent(i + 1) + Source.GetBinContent(i));
}

double DeterminePT(multimap<double, int, greater<double> > &List)
{
   if(List.size() > 0)
      return min(List.begin()->first, 199.9);
   return 0;
}

double DeterminePT(multimap<double, int, greater<double> > &List1, multimap<double, int, greater<double> > &List2)
{
   if(List1.size() == 0 || List2.size() == 0)
      return 0;

   if(List1.size() >= 1 && List2.size() >= 1 && List1.begin()->second != List2.begin()->second)
      return min(min(List1.begin()->first, List2.begin()->first), 199.9);
   
   if(List1.size() == 1 && List2.size() == 1 && List1.begin()->second == List2.begin()->second)
      return 0;

   if(List1.size() == 1 && List2.size() > 1)
      return min(min(List1.begin()->first, (++(List2.begin()))->first), 199.9);
   if(List1.size() > 1 && List2.size() == 1)
      return min(min((++(List1.begin()))->first, List2.begin()->first), 199.9);

   // otherwise: both lists have more than 1 entry, and the first entry is the same
   double Min1 = min(List1.begin()->first, (++(List2.begin()))->first);
   double Min2 = min((++(List1.begin()))->first, List2.begin()->first);
   return min(max(Min1, Min2), 199.9);
}




