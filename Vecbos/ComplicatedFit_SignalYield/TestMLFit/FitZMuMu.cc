#include <string>
using namespace std;

#include "MLFit.hh"

int main()
{
   return 0;
}

// Set Fit Options
MLOptions GetDefaultOptions()
{
   MLOptions Options;
   // Fit configuration
   Options.addBoolOption("FitCaloJets",      "Fit calojets, trackjets otherwise",   kFALSE);
   Options.addBoolOption("AlternativeBackground",           "Use ModExp instead of Poly2",         kTRUE);
   Options.addBoolOption("FitRatio",         "FitRatio directly",                   kTRUE);
   Options.addRealOption("NJetsMin",          "smallest jet number to consider",     1);
   Options.addRealOption("NJetsMax",          "largest jet number to consider",      4);

   return Options;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit MainFit;

void ZRatioFit()
{
   MLFit MainFit;

   // Various fit options...
   MLOptions Options = GetDefaultOptions();

   // define the structure of the dataset
   RooRealVar* ZMass = new RooRealVar("ZMass",  "Mass [GeV/c^{2}]" , 60., 120.);
   RooRealVar* Weight = new RooRealVar("Weight", "Weight", 1);
   RooRealVar* NJets;
   if(Options.getBoolVal("FitCaloJets") == true)
      NJets = new RooRealVar("NCaloJet", "Calo Jet Count", 0.5, 20.5);
   else
      NJets = new RooRealVar("NPFJet", "PF Jet Count", 0.5, 20.5);

   MainFit.AddFlatFileColumn(Mass);
   MainFit.AddFlatFileColumn(NJets);

   // define a fit model
   MainFit.addModel("ZRatioFit", "Ratio Z to MuMu");

   // define species
   MLStrList SpeciesList;
   for(int N = Options.getRealVal("NJetsMin"); N <= Options.getRealVal("NJetsMax"); N++)
   {
      // signal
      char SpeciesLabel[50], SpeciesDescription[200];

      sprintf(SpeciesLabel, "Z%dj", N);
      sprintf(SpeciesDescription, "Signal %dj Component", N);
      MainFit.addSpecies("ZRatioFit", SpeciesLabel, SpeciesDescription);
      SpeciesList.Add(SpeciesLabel);

      // background
      sprintf(SpeciesLabel, "B%dj", N);
      sprintf(SpeciesDescription,"Background %dj Component",N);
      MainFit.addSpecies("ZRatioFit", SpeciesLabel, SpeciesDescription);
   }

   if(Options.getBoolVal("FitRatio") == true)
      MainFit.fitInclusiveRatioPoly(SpeciesList, "Zincl", 1);
   else
      MainFit.fitInclusive(SpeciesList, "Zincl");

   // mLL PDF
   bool first = true;
   char SpeciesLabel[50], PDFName[200], FirstSpecies[50];
   for(int nj = Options.getRealVal("NJetsMin"); nj <=Options.getRealVal("NJetsMax"); nj++)
   {
      char jetlabel[200];
      if(Options.getBoolVal("FitCaloJets") == true)
         sprintf(jetlabel, "NCaloJet");
      else
         sprintf(jetlabel, "NPFJet");

      //signal
      sprintf(SpeciesLabel,"Z%dj",nj);
      if(first)
      {
         MainFit.addPdfWName("ZRatioFit", SpeciesLabel, "ZMass",  "Cruijff", "sig_Mass");
         first = false;
         strcpy(FirstSpecies,SpeciesLabel);
      }
      else
         MainFit.addPdfCopy("ZRatioFit", SpeciesLabel, "ZMass", FirstSpecies);

      sprintf(PDFName, "%dj", nj);
      MainFit.addPdfWName("ZRatioFit", SpeciesLabel, jetlabel, "ExclJet", PDFName);

      //background
      sprintf(SpeciesLabel,"B%dj",nj);
      sprintf(PDFName,"bkg_Mass%d",nj);   
      if(Options.getBoolVal("AlternativeBackground") == true)
         MainFit.addPdfWName("ZRatioFit", SpeciesLabel, "ZMass", "ModExp", PDFName);
      else
         MainFit.addPdfWName("ZRatioFit", SpeciesLabel, "ZMass", "Poly2", PDFName);

      sprintf(PDFName, "%dj", nj);
      MainFit.addPdfWName("ZRatioFit", SpeciesLabel, jetlabel, "ExclJet", PDFName);
   }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitZMuons(const char* scale,int order = 1)
{  
   ZRatioFit();

   // Various fit options...
   MLOptions Options = GetDefaultOptions();

   char jetflavour[200] = "";
   if(Options.getBoolVal("FitCaloJets") == true)
      sprintf(jetflavour, "calojets");
   else
      sprintf(jetflavour, "PFjets");

   char funclabel[200] = "";
   if(Options.getBoolVal("AlternativeBackground") == true)
      sprintf(funclabel, "modexp");
   else
      sprintf(funclabel, "poly2");

   // Load the data
   char datasetname[200];
   sprintf(datasetname, "Samples/ZJetsAll.root");

   char treename[100] = "outTree";
   char cutstring[100] = "";

   MainFit.addDataSetFromRootFile(treename, treename, datasetname);
   RooDataSet *data = MainFit.getDataSet(treename);

   string jetcount;
   if(Options.getBoolVal("FitCaloJets") == true)
      jetcount = "NCaloJet";
   else
      jetcount = "NPFJet";

   sprintf(cutstring, "(%s > (%d - 0.5)) && (%s < (%d + 0.5))",
      jetcount, Options.getRealVal("NJetsMin"),
      jetcount, Options.getRealVal("NJetsMax"));

   data = (RooDataSet *)data->reduce(cutstring);
   data->Print("v");

   // build the fit likelihood
   RooAbsPdf *MainPDF = MainFit.buildModel("ZRatioFit");

   // Initialize the fit...
   // char configname[200];
   // sprintf(configname, "toy-%d%s.config", 1, jetflavour);
   // MainFit.initialize(configname);

   // which order polynomial
   char parname[100];
   for(int i = order + 1; i < 5; i++)
   {
      sprintf(parname, "alpha%d_Zincl", i);
      MainFit.getRealPar(parname)->setConstant(kTRUE);
      MainFit.getRealPar(parname)->setVal(0);
   }

   // Print Fit configuration 
   MainPDF->getParameters(data)->selectByAttrib("Constant", kTRUE)->Print("V");  
   MainPDF->getParameters(data)->selectByAttrib("Constant", kFALSE)->Print("V");

   // MainPDF->plotOn(testplot);
   // testplot = new RooPlot(*mass,*njets);

   RooFitResult *FitResult = MainPDF->fitTo(*data, RooFit::FitOptions("MHTER"));
   FitResult->Print("V");

   // write the config file corresponding to the fit minimum
   char configfilename[200];
   sprintf(configfilename, "fitMinimum-Data-%s%s_%s.config",jetflavour,scale,funclabel);
   MainFit.writeConfigFile(configfilename);  

   /*
   //redo fit without constraints.
   sprintf(configname,"toy-%d%s.config",1,jetflavour);
   MainFit.initialize(configname);
   for(int i = Options.getRealVal("NJetsMax") - Options.getRealVal("NJetsMin") ; i < 5 ; i++)
   {
      sprintf(parname,"alpha%d_Zincl",i);
      MainFit.getRealPar(parname)->setConstant(kTRUE);
      MainFit.getRealPar(parname)->setVal(0);
   }

   RooFitResult *FitResultFree = MainPDF->fitTo(*data,RooFit::FitOptions("MHTER"));
   char configfilename[200];
   sprintf(configfilename, "fitMinimumFree-Data-%s%s_%s.config",jetflavour,scale,funclabel);
   MainFit.writeConfigFile(configfilename);  

   double llratio = fitres->minNll() - fitresFree->minNll();
   double deltandf= Options.getRealVal("NJetsMax") - Options.getRealVal("NJetsMin") - order -1;
   double pvalue = ROOT::Math::chisquared_cdf_c(llratio, deltandf);
   std::cout << deltandf <<std::endl;
   std::cout << "log likelihood ratio: " << llratio << " P-value: " << pvalue  << std::endl;
   std::cout << "significane of deviation from linearity: " << sqrt(llratio)<< std::endl;
   std::cout <<  2*ROOT::Math::normal_cdf_c(sqrt(llratio))  <<  " " << ROOT::Math::gaussian_quantile_c(0.5*pvalue,1.) << std::endl;	
   */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotZElectrons(int njets, int nbins = 19, const char* scale, bool plotMass = true)
{
   /*
   ZRatioFit();

   // Various fit options...
   MLOptions Options = GetDefaultOptions();

   char jetflavour[200];
   if(Options.getBoolVal("FitCaloJets")) sprintf(jetflavour, "calojets");
   else sprintf(jetflavour, "PFjets");

   char funclabel[200];
   if(Options.getBoolVal("AlternativeBackground")) sprintf(funclabel,"modexp");
   else sprintf(funclabel, "poly2");

   // Load the data
   char datasetname[200];
   sprintf(datasetname,"/data/mmozer/36X/MM95xMM95/datasets/data_Zee.root");

   char funclabel[200];
   if(Options.getBoolVal("AlternativeBackground")) sprintf(funclabel,"modexp");
   else sprintf(funclabel, "poly2");

   char treename[100];
   char cutstring[100];
   sprintf(treename,"T1");
   MainFit.addDataSetFromRootFile(treename, treename, datasetname);
   RooDataSet *data = MainFit.getDataSet(treename);
   if(njets < Options.getRealVal("NJetsMax")-0.5) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",Options.getBoolVal("FitCaloJets")?"nJets":"nPFJets", Options.getRealVal("NJetsMin"),Options.getBoolVal("FitCaloJets")?"nJets":"nPFJets" ,Options.getRealVal("NJetsMax"));
   else sprintf(cutstring,"(%s > (%d-0.5) )",Options.getBoolVal("FitCaloJets")?"nJets":"nPFJets",njets);
   std::cout << cutstring << std::endl;
   data = (RooDataSet *)data->reduce(cutstring);

   // build the fit likelihood
   RooAbsPdf *MainPDF = MainFit.buildModel("ZRatioFit");

   // Initialize the fit...
   char configfilename[200];
   sprintf(configfilename, "fitMinimum-Data-%s%s_%s.config",jetflavour,scale,funclabel);
   MainFit.initialize(configfilename);

   TCanvas *c = new TCanvas("c","fitResult");

   if(plotMass)
   {
      RooPlot* MassPlot = MakePlotMass(&MainFit, data, nbins,njets);    
      MassPlot->SetAxisColor(1,"x");
      MassPlot->SetLabelColor(1, "X");
      MassPlot->SetLabelColor(1, "Y");
      MassPlot->SetXTitle("m_{ee}[GeV/c^{2}]");

      MassPlot->SetYTitle("Events");
      MassPlot->Draw();
   } 
   else
   {
      RooPlot* MassPlot = MakePlotJets(&MainFit, data);    
      MassPlot->SetAxisColor(1,"x");
      MassPlot->SetLabelColor(1, "X");
      MassPlot->SetLabelColor(1, "Y");
      MassPlot->SetXTitle("N_{Jets}");    
      MassPlot->SetYTitle("Events");
      MassPlot->Draw();
   }
   */
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Make the plot for a given variable
RooPlot *MakePlotMass(MLFit* MainFit, RooDataSet* theData, int nbins, int njet)
{
   return NULL;

   /*
   MLOptions Options = GetDefaultOptions();

   RooRealVar* Var = MainFit->RealObservable("mee");
   RooRealVar* jets;
   if(Options.getBoolVal("FitCaloJets")) jets = MainFit->RealObservable("nJets");
   else jets = MainFit->RealObservable("nPFJets");
   jets->setVal(njet);

   double min=Var->getMin();
   double max=Var->getMax();
   RooPlot *plot = Var->frame(min,max,nbins );

   char cutstring[100];
   sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",Options.getBoolVal("FitCaloJets")?"nJets":"nPFJets", njet,Options.getBoolVal("FitCaloJets")?"nJets":"nPFJets" ,njet);


   // plot the data
   theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2),RooFit::Cut(cutstring) );

   // plot the total likelihood
   RooAbsPdf *thePdf = MainFit->getPdf("ZRatioFit");
   thePdf->plotOn(plot, RooFit::LineColor(kBlack),RooFit::Slice(*jets));

   char SpeciesLabel[50];
   sprintf(SpeciesLabel,"ZRatioFit_B%dj",njet);
   thePdf->plotOn(plot, RooFit::Components(SpeciesLabel),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed),RooFit::Slice(*jets));


   return plot;
   */
}

// Make the plot for a given variable
RooPlot *MakePlotJets(MLFit* MainFit, RooDataSet* theData)
{
   return NULL;

   /*
   MLOptions Options = GetDefaultOptions();

   RooRealVar* jets;
   if(Options.getBoolVal("FitCaloJets")) jets = MainFit->RealObservable("nJets");
   else jets = MainFit->RealObservable("nPFJets");

   double min=Options.getRealVal("NJetsMin")-0.5;
   double max=Options.getRealVal("NJetsMax")+0.5;
   RooPlot *plot = jets->frame(min,max,(int)(max-min));


   // plot the data
   theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2));

   // plot the total likelihood
   RooAbsPdf *thePdf = MainFit->getPdf("ZRatioFit");
   thePdf->plotOn(plot, RooFit::LineColor(kBlack));

   TString SpeciesLabel;
   for(int njet = Options.getRealVal("NJetsMin"); njet <Options.getRealVal("NJetsMax"); njet++ )
   {
      SpeciesLabel += TString("ZRatioFit_B");
      SpeciesLabel += njet; 
      SpeciesLabel += TString("j,");
   }
   SpeciesLabel += TString("ZRatioFit_B")+TString((int)Options.getRealVal("NJetsMax"));

   std::cout << SpeciesLabel << std::endl;

   thePdf->plotOn(plot, RooFit::Components(SpeciesLabel.Data()),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed));


   return plot;
   */
}
