{
   TFile *_file0 = TFile::Open("OutputFile.root");
   gROOT->Macro("SetAlias.C");
   ResultTree->Draw("Status == 3");
   cout << htemp->GetMean() << endl;
   cout << endl;

   ResultTree->Draw("FZJem", "Status == 3");
   cout << "FZJem " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("ZJem / (Sem+Bem+ZJem)", "Status == 3");
   cout << "RZJem " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("FZJme", "Status == 3");
   cout << "FZJme " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("ZJme / (Sme+Bme+ZJme)", "Status == 3");
   cout << "RZJme " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("FZJee", "Status == 3");
   cout << "FZJee " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("ZJee / (See+Bee+ZJee)", "Status == 3");
   cout << "RZJee " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("FZJmm", "Status == 3");
   cout << "FZJmm " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("ZJmm / (Smm+Bmm+ZJmm)", "Status == 3");
   cout << "RZJmm " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("FggZZem", "Status == 3");
   cout << "FggZZem " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("ggZZem / (Sem+Bem+ZJem)", "Status == 3");
   cout << "RggZZem " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("FggZZme", "Status == 3");
   cout << "FggZZme " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("ggZZme / (Sme+Bme+ZJme)", "Status == 3");
   cout << "RggZZme " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("FggZZee", "Status == 3");
   cout << "FggZZee " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("ggZZee / (See+Bee+ZJee)", "Status == 3");
   cout << "RggZZee " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("FggZZmm", "Status == 3");
   cout << "FggZZmm " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("ggZZmm / (Smm+Bmm+ZJmm)", "Status == 3");
   cout << "RggZZmm " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("Fem", "Status == 3");
   cout << "Fem " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("Bem / (Sem+Bem+ZJem)", "Status == 3");
   cout << "Rem " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("Fme", "Status == 3");
   cout << "Fme " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("Bme / (Sme+Bme+ZJme)", "Status == 3");
   cout << "Rme " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("Fee", "Status == 3");
   cout << "Fee " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("Bee / (See+Bee+ZJee)", "Status == 3");
   cout << "Ree " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;

   ResultTree->Draw("Fmm", "Status == 3");
   cout << "Fmm " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   ResultTree->Draw("Bmm / (Smm+Bmm+ZJmm)", "Status == 3");
   cout << "Rmm " << htemp->GetMean() << " " << htemp->GetMeanError() << endl;
   cout << endl;
}
