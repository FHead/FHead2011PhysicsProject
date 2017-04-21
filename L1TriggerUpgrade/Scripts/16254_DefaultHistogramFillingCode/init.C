{
  std::cout << "FWCoreFWLite library loading ..." <<std::endl;
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();

  std::cout << "Macros & ntuple producer paths setting ..." <<std::endl;
  std::string tmp=gEnv->GetValue("Unix.*.Root.MacroPath","");
  tmp=tmp+std::string(":$CMSSW_BASE/src/UserCode/L1TriggerDPG/macros:$CMSSW_BASE/src/UserCode/L1TriggerUpgrade/macros");
  gEnv->SetValue("Unix.*.Root.MacroPath",tmp.c_str());

  tmp=gROOT->GetMacroPath();
  tmp=tmp+std::string(":$CMSSW_BASE/src/UserCode/L1TriggerDPG/macros:$CMSSW_BASE/src/UserCode/L1TriggerUpgrade/macros");
  gROOT->SetMacroPath(tmp.c_str());

  gSystem->AddIncludePath(" -I$CMSSW_BASE/src/UserCode/L1TriggerDPG/interface");
  gSystem->AddIncludePath(" -I$CMSSW_BASE/src/UserCode/L1TriggerDPG/macros");
  gSystem->AddIncludePath(" -I$CMSSW_BASE/src/UserCode/L1TriggerUpgrade/interface");
  gSystem->AddIncludePath(" -I$CMSSW_BASE/src/UserCode/L1TriggerUpgrade/macros");


  gROOT->ProcessLine(".include $CMSSW_BASE/src/UserCode/L1TriggerDPG/interface");
  gROOT->ProcessLine(".include $CMSSW_BASE/src/UserCode/L1TriggerDPG/macros"); 
  gROOT->ProcessLine(".include $CMSSW_BASE/src/UserCode/L1TriggerUpgrade/interface");
  gROOT->ProcessLine(".include $CMSSW_BASE/src/UserCode/L1TriggerUpgrade/macros"); 

  std::cout << "L1Ntuple library loading ..." <<std::endl;
  gROOT->ProcessLine(".L L1UpgradeNtuple.C+");

  /*
  std::cout << "L1Menu2015 library loading ..." <<std::endl;
  gROOT->ProcessLine(".L L1Menu2015.C+");

  std::cout << "EvaluateL1Menu library loading ..." <<std::endl;
  gROOT->ProcessLine(".L EvaluateL1Menu.C+");
  */
  std::cout << "---- initialization done ----"<<std::endl;
}
