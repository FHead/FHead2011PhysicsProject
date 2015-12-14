#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"

#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooPlot.h"
using namespace RooFit;

#include "DataHelper.h"

int main(int argc, char *argv[])
{
   if(argc < 3)
   {
      cerr << "Usage " << argv[0] << " InputFile OutputBase" << endl;
      return -1;
   }

   string InputFileName = argv[1];
   string OutputBase = argv[2];

   TFile InputFile(InputFileName.c_str());
   TTree *Tree = (TTree *)InputFile.Get("ReducedTree");

   DataHelper DHFile(OutputBase + ".dh");
   TFile OutputFile((OutputBase + ".root").c_str(), "RECREATE");

   double R2Cuts[] = {0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50};
            
   RooRealVar MR("MR", "M_{R}", 400, 3500);
   RooRealVar R("R", "R", 0, 1.5);
   RooRealVar LooseBTagCount("LooseBTagCount", "LooseBTagCount", 0, 9999);
   RooRealVar MediumBTagCount("MediumBTagCount", "MediumBTagCount", 0, 9999);
   RooRealVar TightBTagCount("TightBTagCount", "TightBTagCount", 0, 9999);
   RooRealVar GoodMuonCountLoose("GoodMuonCountLoose", "GoodMuonCountLoose", 0, 9999);
   RooRealVar GoodMuonCountTight("GoodMuonCountTight", "GoodMuonCountTight", 0, 9999);
   RooRealVar GoodElectronCountLoose("GoodElectronCountLoose", "GoodElectronCountLoose", 0, 9999);
   RooRealVar GoodElectronCountTight("GoodElectronCountTight", "GoodElectronCountTight", 0, 9999);
   RooArgSet TreeArgSet(MR, R, LooseBTagCount, MediumBTagCount, TightBTagCount,
      GoodMuonCountLoose, GoodMuonCountTight, GoodElectronCountLoose, GoodElectronCountTight);

   RooDataSet DataSet("DataSet", "DataSet", Tree, TreeArgSet, Form("MR > 350 && R * R > %f", R2Cuts[0]));

   for(int iSelection = 0; iSelection < 5; iSelection++)
   {
      for(int iTagging = 0; iTagging < 8; iTagging++)
      {
         for(int iR2Cut = 0; iR2Cut < 9; iR2Cut++)
         {
            double R2Cut = R2Cuts[iR2Cut];

            // File format for individual fits: TTbar_0.20_Had_All.png
            // DHFile format: ["0.20_Had_All"]["S1"] = -0.02
            //    Items: S1, S1Error, S2, S2Error, Correlation

            string CutString = Form("R * R > %f", R2Cut);

            if(iSelection == 0)   CutString = CutString + " && GoodMuonCountLoose == 0 && GoodElectronCountLoose == 0";
            if(iSelection == 1)   CutString = CutString + " && GoodMuonCountLoose == 1";
            if(iSelection == 2)   CutString = CutString + " && GoodMuonCountTight == 1";
            if(iSelection == 3)   CutString = CutString + " && GoodElectronCountLoose == 1";
            if(iSelection == 4)   CutString = CutString + " && GoodElectronCountTight == 1";

            if(iTagging == 1)   CutString = CutString + " && LooseBTagCount == 0";
            if(iTagging == 2)   CutString = CutString + " && LooseBTagCount == 1";
            if(iTagging == 3)   CutString = CutString + " && LooseBTagCount > 1";
            if(iTagging == 4)   CutString = CutString + " && MediumBTagCount == 1";
            if(iTagging == 5)   CutString = CutString + " && MediumBTagCount > 1";
            if(iTagging == 6)   CutString = CutString + " && TightBTagCount == 1";
            if(iTagging == 7)   CutString = CutString + " && TightBTagCount > 1";

            RooDataSet *ReducedDataSet = (RooDataSet *)DataSet.reduce(CutString.c_str());

            RooRealVar S1("S1", "S1", -0.014, -10.0, 0.0);
            RooExponential Model1("Model1", "Model1", MR, S1);
            RooRealVar S2("S2", "S2", -0.0066, -10.0, 0.0);
            RooExponential Model2("Model2", "Model2", MR, S2);
            RooRealVar Fraction("Fraction", "Fraction", 0.5, 0.0, 1.0);
            RooAddPdf Model("Model", "Model", Model1, Model2, Fraction);

            Model.fitTo(*ReducedDataSet, NumCPU(3));
            Model.fitTo(*ReducedDataSet, NumCPU(3));
            Model.fitTo(*ReducedDataSet, NumCPU(3));
            Model.fitTo(*ReducedDataSet, NumCPU(3));
            RooFitResult *FitResult = Model.fitTo(*ReducedDataSet, Save(true), NumCPU(3));

            string SelectionString = "";
            if(iSelection == 0)   SelectionString = "Had";
            if(iSelection == 1)   SelectionString = "LooseMuon";
            if(iSelection == 2)   SelectionString = "TightMuon";
            if(iSelection == 3)   SelectionString = "LooseElectron";
            if(iSelection == 4)   SelectionString = "TightElectron";

            string TaggingString = "";
            if(iTagging == 0)   TaggingString = "All";
            if(iTagging == 1)   TaggingString = "NoTag";
            if(iTagging == 2)   TaggingString = "OneLoose";
            if(iTagging == 3)   TaggingString = "TwoLoose";
            if(iTagging == 4)   TaggingString = "OneMedium";
            if(iTagging == 5)   TaggingString = "TwoMedium";
            if(iTagging == 6)   TaggingString = "OneTight";
            if(iTagging == 7)   TaggingString = "TwoTight";

            RooPlot *MRPlot = MR.frame(Bins(50), Name("MRPlot"),
               Title(Form("Fit to MR with R^{2} cut %.2f, %s, %s",
                  R2Cut, SelectionString.c_str(), TaggingString.c_str())),
               Range(400, 2000));
            ReducedDataSet->plotOn(MRPlot, MarkerSize(1.4));
            Model.plotOn(MRPlot, LineColor(kRed), Components(Model1));
            Model.plotOn(MRPlot, LineColor(kRed), Components(Model2));
            Model.plotOn(MRPlot, LineColor(kBlue));

            string Identifier = Form("%.2f_%s_%s", R2Cut, SelectionString.c_str(), TaggingString.c_str());

            TCanvas C("C", "C", 800, 800);
            MRPlot->SetMinimum(0.5);
            MRPlot->Draw();
            C.SetLogy();
            C.SaveAs(Form("%s_%s.png", OutputBase.c_str(), Identifier.c_str()));

            DHFile[Identifier]["R2Cut"] = Form("%.2f", R2Cut);
            DHFile[Identifier]["Selection"] = SelectionString;
            DHFile[Identifier]["Tagging"] = TaggingString;
            DHFile[Identifier]["S1"] = S1.getVal();
            DHFile[Identifier]["S1Error"] = S1.getError();
            DHFile[Identifier]["S2"] = S2.getVal();
            DHFile[Identifier]["S2Error"] = S2.getError();
            DHFile[Identifier]["Fraction"] = Fraction.getVal();
            DHFile[Identifier]["FractionError"] = Fraction.getError();
            DHFile[Identifier]["Correlation"] = FitResult->correlation("S1", "S2");
            DHFile[Identifier]["Stats"] = ReducedDataSet->sumEntries();
         }
      }
   }

   OutputFile.Close();
   DHFile.SaveToFile(OutputBase + ".dh");

   InputFile.Close();

   return 0;
}




