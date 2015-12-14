// Set Fit Options
MLOptions GetDefaultOptions() {
  MLOptions opts;
  // Fit configuration
  opts.addBoolOption("fitCaloJets",      "Fit calojets, trackjets otherwise", kFALSE);
  opts.addBoolOption("altbkg",           "Use ModExp instead of Poly2",kTRUE);
  opts.addBoolOption("fitRatio",         "FitRatio directly",kTRUE);
  opts.addRealOption("njetmin",          "smallest jet number to consider",1);
  opts.addRealOption("njetmax",          "largest jet number to consider",4);
  
  return opts;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

MLFit theFit;

void myFit() {
  
  MLFit theFit;
  
  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  // define the structure of the dataset
  RooRealVar* mass = new RooRealVar("mee",  "Mass [GeV/c^{2}]" , 60., 110.);
  RooRealVar* weight = new RooRealVar("weight", "weight",1);
  RooRealVar* njets;
  if(opts.getBoolVal("fitCaloJets")) njets = new RooRealVar("nJets", "nJets",0.5, 20.5);
  else njets = new RooRealVar("nPFJets", "nPFJets",0.5, 20.5);

  theFit.AddFlatFileColumn(mass);
  theFit.AddFlatFileColumn(njets);

  // define a fit model
  theFit.addModel("myFit", "Ratio ZtoEE");
  // define species
  MLStrList speclist;
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){
    //signal
    char speclabel[50],specdesc[200];
    sprintf(speclabel,"Z%dj",nj);
    sprintf(specdesc,"Signal %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);
    speclist.Add(speclabel);
    //backgorund
    sprintf(speclabel,"B%dj",nj);
    sprintf(specdesc,"Background %dj Component",nj);
    theFit.addSpecies("myFit", speclabel, specdesc);
  }
 
  if(opts.getBoolVal("fitRatio"))  theFit.fitInclusiveRatioPoly(speclist, "Zincl",1);
  else  theFit.fitInclusive( speclist, "Zincl");

  // mLL PDF
  bool first=true;
  char speclabel[50],pdfname[200],specfirst[50];
  for(int nj = opts.getRealVal("njetmin"); nj <=opts.getRealVal("njetmax"); nj++){
    char jetlabel[200];
    if(opts.getBoolVal("fitCaloJets")) sprintf(jetlabel,"nJets");
    else sprintf(jetlabel,"nPFJets");
       
    //signal
    sprintf(speclabel,"Z%dj",nj);
    if(first){
      theFit.addPdfWName("myFit", speclabel , "mee",  "Cruijff", "sig_Mass");
      first = false;
      strcpy(specfirst,speclabel);
    }
    else{
      theFit.addPdfCopy("myFit",speclabel , "mee", specfirst);
    }
    sprintf(pdfname,"%dj",nj);
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);
    //background
    sprintf(speclabel,"B%dj",nj);
    sprintf(pdfname,"bkg_Mass%d",nj);   
    if(opts.getBoolVal("altbkg")) theFit.addPdfWName("myFit", speclabel , "mee",  "ModExp", pdfname );
    else theFit.addPdfWName("myFit",speclabel  , "mee",  "Poly2",   pdfname);
    sprintf(pdfname,"%dj",nj);
    theFit.addPdfWName("myFit",speclabel , jetlabel, "ExclJet", pdfname);
  }
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fit a sample of Z events
void FitZElectrons(const char* scale,int order=1) {
  
  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojets");
  else sprintf(jetflavour, "PFjets");

  char funclabel[200];
  if(opts.getBoolVal("altbkg")) sprintf(funclabel,"modexp");
  else sprintf(funclabel, "poly2");

  // Load the data
  char datasetname[200];
  sprintf(datasetname,"/data/mmozer/36X/MM95xMM95/datasets/data_Zee.root");
  
  char treename[100];
  char cutstring[100];
  sprintf(treename,"T1");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nJets":"nPFJets",opts.getRealVal("njetmin") ,opts.getBoolVal("fitCaloJets")?"nJets":"nPFJets" , opts.getRealVal("njetmax"));
  std::cout << cutstring << std::endl;
  data = (RooDataSet *)data->reduce(cutstring);
  data->Print("v");
  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");
  

  // Initialize the fit...
  char configname[200];
  sprintf(configname,"toy-%d%s.config",1,jetflavour);
  theFit.initialize(configname);

  // which order polynomial
  char parname[100];
  for(int i = order+1; i < 5 ; i++){
    sprintf(parname,"alpha%d_Zincl",i);
    theFit.getRealPar(parname)->setConstant(kTRUE);
    theFit.getRealPar(parname)->setVal(0);
  }

  // Print Fit configuration 
  myPdf->getParameters(data)->selectByAttrib("Constant",kTRUE)->Print("V");  
  myPdf->getParameters(data)->selectByAttrib("Constant",kFALSE)->Print("V");

  //myPdf->plotOn(testplot);
  //testplot = new RooPlot(*mass,*njets);

  RooFitResult *fitres =  myPdf->fitTo(*data,RooFit::FitOptions("MHTER"));
  fitres->Print("V");
  // write the config file corresponding to the fit minimum
  char configfilename[200];
  sprintf(configfilename, "fitMinimum-Data-%s%s_%s.config",jetflavour,scale,funclabel);
  theFit.writeConfigFile(configfilename);  

  //redo fit without constraints.
  sprintf(configname,"toy-%d%s.config",1,jetflavour);
  theFit.initialize(configname);
  for(int i = opts.getRealVal("njetmax") - opts.getRealVal("njetmin") ; i < 5 ; i++){
    sprintf(parname,"alpha%d_Zincl",i);
    theFit.getRealPar(parname)->setConstant(kTRUE);
    theFit.getRealPar(parname)->setVal(0);
  }

  RooFitResult *fitresFree = myPdf->fitTo(*data,RooFit::FitOptions("MHTER"));
  char configfilename[200];
  sprintf(configfilename, "fitMinimumFree-Data-%s%s_%s.config",jetflavour,scale,funclabel);
  theFit.writeConfigFile(configfilename);  

  double llratio = fitres->minNll() - fitresFree->minNll();
  double deltandf= opts.getRealVal("njetmax") - opts.getRealVal("njetmin") - order -1;
  double pvalue = ROOT::Math::chisquared_cdf_c(llratio, deltandf);
  std::cout << deltandf <<std::endl;
  std::cout << "log likelihood ratio: " << llratio << " P-value: " << pvalue  << std::endl;
  std::cout << "significane of deviation from linearity: " << sqrt(llratio)<< std::endl;
  std::cout <<  2*ROOT::Math::normal_cdf_c(sqrt(llratio))  <<  " " << ROOT::Math::gaussian_quantile_c(0.5*pvalue,1.) << std::endl;	

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotZElectrons(int njets, int nbins=19,const char* scale, bool plotMass=true) {

  myFit();

  // Various fit options...
  MLOptions opts = GetDefaultOptions();

  char jetflavour[200];
  if(opts.getBoolVal("fitCaloJets")) sprintf(jetflavour, "calojets");
  else sprintf(jetflavour, "PFjets");

  char funclabel[200];
  if(opts.getBoolVal("altbkg")) sprintf(funclabel,"modexp");
  else sprintf(funclabel, "poly2");

  // Load the data
  char datasetname[200];
  sprintf(datasetname,"/data/mmozer/36X/MM95xMM95/datasets/data_Zee.root");
 
  char funclabel[200];
  if(opts.getBoolVal("altbkg")) sprintf(funclabel,"modexp");
  else sprintf(funclabel, "poly2");
  
  char treename[100];
  char cutstring[100];
  sprintf(treename,"T1");
  theFit.addDataSetFromRootFile(treename, treename, datasetname);
  RooDataSet *data = theFit.getDataSet(treename);
  if(njets < opts.getRealVal("njetmax")-0.5) sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nJets":"nPFJets", opts.getRealVal("njetmin"),opts.getBoolVal("fitCaloJets")?"nJets":"nPFJets" ,opts.getRealVal("njetmax"));
  else sprintf(cutstring,"(%s > (%d-0.5) )",opts.getBoolVal("fitCaloJets")?"nJets":"nPFJets",njets);
  std::cout << cutstring << std::endl;
  data = (RooDataSet *)data->reduce(cutstring);

  // build the fit likelihood
  RooAbsPdf *myPdf = theFit.buildModel("myFit");

  // Initialize the fit...
  char configfilename[200];
  sprintf(configfilename, "fitMinimum-Data-%s%s_%s.config",jetflavour,scale,funclabel);
  theFit.initialize(configfilename);

  TCanvas *c = new TCanvas("c","fitResult");

  if(plotMass){
    RooPlot* MassPlot = MakePlotMass(&theFit, data, nbins,njets);    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("m_{ee}[GeV/c^{2}]");
    
    MassPlot->SetYTitle("Events");
    MassPlot->Draw();
  } 
  else{
    RooPlot* MassPlot = MakePlotJets(&theFit, data);    
    MassPlot->SetAxisColor(1,"x");
    MassPlot->SetLabelColor(1, "X");
    MassPlot->SetLabelColor(1, "Y");
    MassPlot->SetXTitle("N_{Jets}");    
    MassPlot->SetYTitle("Events");
    MassPlot->Draw();

  }
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Make the plot for a given variable
RooPlot *MakePlotMass(MLFit* theFit, RooDataSet* theData, int nbins, int njet)
{
  MLOptions opts = GetDefaultOptions();

  RooRealVar* Var = theFit->RealObservable("mee");
  RooRealVar* jets;
  if(opts.getBoolVal("fitCaloJets")) jets = theFit->RealObservable("nJets");
  else jets = theFit->RealObservable("nPFJets");
  jets->setVal(njet);

  double min=Var->getMin();
  double max=Var->getMax();
  RooPlot *plot = Var->frame(min,max,nbins );

  char cutstring[100];
  sprintf(cutstring,"(%s > (%d-0.5) )&& (%s < (%d + 0.5) )",opts.getBoolVal("fitCaloJets")?"nJets":"nPFJets", njet,opts.getBoolVal("fitCaloJets")?"nJets":"nPFJets" ,njet);


  // plot the data
  theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2),RooFit::Cut(cutstring) );

  // plot the total likelihood
  RooAbsPdf *thePdf = theFit->getPdf("myFit");
  thePdf->plotOn(plot, RooFit::LineColor(kBlack),RooFit::Slice(*jets));

  char speclabel[50];
  sprintf(speclabel,"myFit_B%dj",njet);
  thePdf->plotOn(plot, RooFit::Components(speclabel),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed),RooFit::Slice(*jets));

  
  return plot;
}

// Make the plot for a given variable
RooPlot *MakePlotJets(MLFit* theFit, RooDataSet* theData)
{
  MLOptions opts = GetDefaultOptions();

  RooRealVar* jets;
  if(opts.getBoolVal("fitCaloJets")) jets = theFit->RealObservable("nJets");
  else jets = theFit->RealObservable("nPFJets");

  double min=opts.getRealVal("njetmin")-0.5;
  double max=opts.getRealVal("njetmax")+0.5;
  RooPlot *plot = jets->frame(min,max,(int)(max-min));
  

  // plot the data
  theData->plotOn(plot, RooFit::DataError(RooAbsData::SumW2));

  // plot the total likelihood
  RooAbsPdf *thePdf = theFit->getPdf("myFit");
  thePdf->plotOn(plot, RooFit::LineColor(kBlack));

  TString speclabel;
  for(int njet = opts.getRealVal("njetmin"); njet <opts.getRealVal("njetmax"); njet++ ){
    speclabel += TString("myFit_B");
    speclabel += njet; 
    speclabel += TString("j,");
  }
  speclabel += TString("myFit_B")+TString((int)opts.getRealVal("njetmax"));
  
  std::cout << speclabel << std::endl;
  
  thePdf->plotOn(plot, RooFit::Components(speclabel.Data()),RooFit::LineColor(kBlack),RooFit::LineStyle(kDashed));

  
  return plot;
}
