#include <TTree.h>
#include <TBranch.h>
#include <TFile.h>
#include <XtoZZ.cc>
#include <iostream>

#define PI (asin(1.)*2.)
using namespace std;

int main(int argc, char *argv[]){

  bool DEL_MEM = false;

  // read input settings
  char s_file[50];
  char s_ofile[50];
  int mode;
  int Nevent;

  for (int i=0;i<argc;i++){
    if (strncmp(argv[i],"-file",5)==0)  sscanf(argv[i],"-file=%s",  s_file);
    if (strncmp(argv[i],"-ofile",6)==0) sscanf(argv[i],"-ofile=%s",  s_ofile);
    if (strncmp(argv[i],"-mode",5)==0) sscanf(argv[i],"-mode=%d", &mode);
    if (strncmp(argv[i],"-Nevent",7)==0)  sscanf(argv[i],"-Nevent=%d", &Nevent);
  }

  //first we get the higgs mass and width, along with binning

  //Here we define the steps and bounds
  int N_M = 10;
  int N_cosTHETA = 10;
  int N_c1 = 10;
  int N_c2 = 10;
  int N_phi = 10;
  int N_PHI = 10;
  
  int b_angle;
  double min_M;
  double max_M;
  double min_cosTHETA;
  double max_cosTHETA;
  double min_c1;
  double max_c1;
  double min_c2;
  double max_c2;
  double min_phi;
  double max_phi;
  double min_PHI;
  double max_PHI;
  double mH;
  double wH;
  double INTEGRAL;
  int NTOT;
  int NPASS;

  //We get the steps and bounds from the file
  TBranch *b_N_M;
  TBranch *b_N_cosTHETA;
  TBranch *b_N_c1;
  TBranch *b_N_c2;
  TBranch *b_N_phi;
  TBranch *b_N_PHI;
  TBranch *b_min_M;
  TBranch *b_max_M;
  TBranch *b_min_cosTHETA;
  TBranch *b_max_cosTHETA;
  TBranch *b_min_c1;
  TBranch *b_max_c1;
  TBranch *b_min_c2;
  TBranch *b_max_c2;
  TBranch *b_min_phi;
  TBranch *b_max_phi;
  TBranch *b_min_PHI;
  TBranch *b_max_PHI;
  TBranch *b_b_angle;
  TBranch *b_mH;
  TBranch *b_wH;
  TBranch *b_INTEGRAL;
  
  TFile* file = TFile::Open(s_file, "READ");
  TTree* param = (TTree*) file->Get("cond");
 
  //We define these ine this file now

  //param->SetBranchAddress("N_M", &N_M, &b_N_M);
  //param->SetBranchAddress("N_cosTHETA", &N_cosTHETA, &b_N_cosTHETA);
  //param->SetBranchAddress("N_c1", &N_c1, &b_N_c1);
  //param->SetBranchAddress("N_c2", &N_c2, &b_N_c2);
  //param->SetBranchAddress("N_phi", &N_phi, &b_N_phi);
  //param->SetBranchAddress("N_PHI", &N_PHI, &b_N_PHI);
  
  param->SetBranchAddress("min_M", &min_M, &b_min_M);
  param->SetBranchAddress("max_M", &max_M, &b_max_M);
  param->SetBranchAddress("min_cosTHETA", &min_cosTHETA, &b_min_cosTHETA);
  param->SetBranchAddress("max_cosTHETA", &max_cosTHETA, &b_max_cosTHETA);
  param->SetBranchAddress("min_c1", &min_c1, &b_min_c1);
  param->SetBranchAddress("max_c1", &max_c1, &b_max_c1);
  param->SetBranchAddress("min_c2", &min_c2, &b_min_c2);
  param->SetBranchAddress("max_c2", &max_c2, &b_max_c2);
  param->SetBranchAddress("min_phi", &min_phi, &b_min_phi);
  param->SetBranchAddress("max_phi", &max_phi, &b_max_phi);
  param->SetBranchAddress("min_PHI", &min_PHI, &b_min_PHI);
  param->SetBranchAddress("max_PHI", &max_PHI, &b_max_PHI);
  param->SetBranchAddress("mH", &mH, &b_mH);
  param->SetBranchAddress("wH", &wH, &b_wH);
  param->SetBranchAddress("INTEGRAL", &INTEGRAL, &b_INTEGRAL);
  param->GetEntry(0);

  // Instantiate XtoZZ object
  XtoZZ* Resonance = new XtoZZ(mH, wH);
 
  //Initialize the resonance
  //TFile* filesmear = new TFile("root_inputs/cmsMuonSmearing.root");
  TFile* filesmear = new TFile("root_inputs/MADGRAPH_detector.root");
  vector<TH1D*> pTSmearing;
  vector<TH1D*> etaSmearing;
  char name[256];  
  for(int i=0; i<50; i++) {
    for(int j=0; j<24; j++) {
      sprintf(name,"pT_pT_%i_eta_%i",i,j);
      pTSmearing.push_back((TH1D*) filesmear->Get(string(name).c_str()));
      sprintf(name,"eta_pT_%i_eta_%i",i,j);
      etaSmearing.push_back((TH1D*) filesmear->Get(string(name).c_str()));
    }
  }

  SmearingFunction* smear = new SmearingFunction(pTSmearing, etaSmearing);
  Resonance->SetSmearingFunction(smear);
  Resonance->SetBoostDist("root_inputs/Hboost.root");

  double c1GEN;
  double c2GEN;
  double phiGEN;
  double PHIGEN;
  double cosTHETAGEN;
  double massHGEN;
  double massZ1GEN;
  double massZ2GEN;

  TBranch *b_c1;
  TBranch *b_c2;
  TBranch *b_phi;
  TBranch *b_PHI;
  TBranch *b_cosTHETA;
  TBranch *b_M;

  //Now we open the input tree
  TTree* intree = (TTree*) file->Get("data");
  intree->SetBranchAddress("M", &massZ2GEN, &b_M);
  intree->SetBranchAddress("c1", &c1GEN, &b_c1);
  intree->SetBranchAddress("c2", &c2GEN, &b_c2);
  intree->SetBranchAddress("phi", &phiGEN, &b_phi);
  intree->SetBranchAddress("PHI", &PHIGEN, &b_PHI);
  intree->SetBranchAddress("cosTHETA", &cosTHETAGEN, &b_cosTHETA);

  double c1;
  double c2;
  double phi;
  double PHI;
  double cosTHETA;
  double massH;
  double massZ1;
  double massZ2;
  double M;

 

  // define the output file's histograms
  // We build the (empty) histograms and put the 'angles' ones
  // already in the file - we then retrieve them on an event/by/event
  // basis because of memory issues
  TFile* outfile = TFile::Open(s_ofile,"recreate");
  
  
  //default type 0
  TH1D* h_mZstar; 
  TH2D* h_ANGLES[N_M];
  TH3D* h_angles[N_M][N_cosTHETA][N_PHI];
  
  //type 1
  TH1D* h_mZstar_1;
  TH1D* h_cosTHETA_1[N_M];
  TH3D* h_angles_1[N_M][N_cosTHETA];

  //type 2
  TH1D* h_mZstar_2;
  TH1D* h_PHI_2[N_M];
  TH3D* h_angles_2[N_M][N_PHI];

  //type 3
  TH2D* h_ANGLES_3;
  TH3D* h_angles_3[N_cosTHETA][N_PHI];

  //type 4
  TH1D* h_mZstar_4;
  TH3D* h_angles_4[N_M];

  //type 5
  TH1D* h_cosTHETA_5;
  TH3D* h_angles_5[N_cosTHETA];

  //type 6
  TH1D* h_PHI_6;
  TH3D* h_angles_6[N_PHI];

  //type 7
  TH3D* h_angles_7;

  //type 8
  TH1D* h_mZstar_8;
  TH2D* h_ANGLES_8[N_M];

  //type 9
  TH1D* h_mZstar_9;
  TH1D* h_cosTHETA_9;
  TH1D* h_PHI_9;
  TH1D* h_c1_9;
  TH1D* h_c2_9;
  TH1D* h_phi_9;

  if(mode == 1){
    h_mZstar = (TH1D*) new TH1D("h_mZstar", "h_mZstar", N_M, min_M, max_M);
    h_mZstar_1 = (TH1D*) new TH1D("h_mZstar_type1", "h_mZstar_type1", N_M, min_M, max_M);
    h_mZstar_2 = (TH1D*) new TH1D("h_mZstar_type2", "h_mZstar_type2", N_M, min_M, max_M);
    h_ANGLES_3 = (TH2D*) new TH2D("h_ANGLES_type3", "h_ANGLES_type3",
				  N_cosTHETA,min_cosTHETA,max_cosTHETA,
				  N_PHI, min_PHI, max_PHI);
  }
  h_mZstar_4 = (TH1D*) new TH1D("h_mZstar_type4", "h_mZstar_type4", N_M, min_M, max_M);
  h_cosTHETA_5 = (TH1D*) new TH1D("h_cosTHETA_type5", "h_cosTHETA_type5",
				  N_cosTHETA, min_cosTHETA, max_cosTHETA);
  h_PHI_6 = (TH1D*) new TH1D("h_PHI_type6", "h_PHI_type6",
			     N_PHI, min_PHI, max_PHI);
  h_angles_7 = (TH3D*) new TH3D("h_angles_type7", "h_angles_type7", 
				N_c1, min_c1, max_c1,
				N_c2, min_c2, max_c2,
				N_phi, min_phi, max_phi);
  h_mZstar_8 = (TH1D*) new TH1D("h_mZstar_type8", "h_mZstar_type8", N_M, min_M, max_M);
  h_mZstar_9 = (TH1D*) new TH1D("h_mZstar_type9", "h_mZstar_type9", N_M, min_M, max_M);
  h_cosTHETA_9 = (TH1D*) new TH1D("h_cosTHETA_type9", "h_cosTHETA_type9", N_cosTHETA, min_cosTHETA, max_cosTHETA);
  h_PHI_9 = (TH1D*) new TH1D("h_PHI_type9", "h_PHI_type9", N_PHI, min_PHI, max_PHI);
  h_c1_9 = (TH1D*) new TH1D("h_c1_type9", "h_c1_type9", N_c1, min_c1, max_c1);
  h_c2_9 = (TH1D*) new TH1D("h_c2_type9", "h_c2_type9", N_c2, min_c2, max_c2);
  h_phi_9 = (TH1D*) new TH1D("h_phi_type9", "h_phi_type9", N_phi, min_phi, max_phi);

  
  //
  // Now we do the other histograms
  //
  if(mode == 1){
    //type 0
    for(int i_M = 0; i_M < N_M; i_M++){
      char *name = new char[50];
      sprintf(name, "h_ANGLES_%d", i_M);
      h_ANGLES[i_M] = (TH2D*) new TH2D(name, name, 
				       N_cosTHETA,min_cosTHETA,max_cosTHETA,
				       N_PHI, min_PHI, max_PHI);
      for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  char *sname = new char[50];
	  sprintf(sname, "h_angles_%d_%d_%d", i_M, i_cos, i_PHI);
	  h_angles[i_M][i_cos][i_PHI] = (TH3D*) new TH3D(sname, sname, N_c1, min_c1, max_c1,
							 N_c2, min_c2, max_c2,
							 N_phi, min_phi, max_phi);
	  if(DEL_MEM){
	    outfile->cd();
	    h_angles[i_M][i_cos][i_PHI]->Write("", TObject::kOverwrite);
	    h_angles[i_M][i_cos][i_PHI]->Delete();
	  }
	}
      }
    }
    //type 1
    for(int i_M = 0; i_M < N_M; i_M++){
      char *name = new char[50];
      sprintf(name, "h_cosTHETA_type1_%d", i_M);
      h_cosTHETA_1[i_M] = (TH1D*) new TH1D(name, name, 
					   N_cosTHETA,min_cosTHETA,max_cosTHETA);
      for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	char *sname = new char[50];
	sprintf(sname, "h_angles_type1_%d_%d", i_M, i_cos);
	h_angles_1[i_M][i_cos] = (TH3D*) new TH3D(sname, sname, N_c1, min_c1, max_c1,
						  N_c2, min_c2, max_c2,
						  N_phi, min_phi, max_phi);
	if(DEL_MEM){
	  outfile->cd();
	  h_angles_1[i_M][i_cos]->Write("", TObject::kOverwrite);
	  h_angles_1[i_M][i_cos]->Delete();
	}
      }
    }
    //type 2
    for(int i_M = 0; i_M < N_M; i_M++){
      char *name = new char[50];
      sprintf(name, "h_PHI_type2_%d", i_M);
      h_PHI_2[i_M] = (TH1D*) new TH1D(name, name, 
				      N_PHI,min_PHI,max_PHI);
      for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	char *sname = new char[50];
	sprintf(sname, "h_angles_type2_%d_%d", i_M, i_PHI);
	h_angles_2[i_M][i_PHI] = (TH3D*) new TH3D(sname, sname, N_c1, min_c1, max_c1,
						  N_c2, min_c2, max_c2,
						  N_phi, min_phi, max_phi);
	if(DEL_MEM){
	  outfile->cd();
	  h_angles_2[i_M][i_PHI]->Write("", TObject::kOverwrite);
	  h_angles_2[i_M][i_PHI]->Delete();
	}
      }
    }
    //type 3
    for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
      for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	
	char *sname = new char[50];
	sprintf(sname, "h_angles_type3_%d_%d", i_cos, i_PHI);
	h_angles_3[i_cos][i_PHI] = (TH3D*) new TH3D(sname, sname, N_c1, min_c1, max_c1,
						    N_c2, min_c2, max_c2,
						    N_phi, min_phi, max_phi);
	if(DEL_MEM){
	  outfile->cd();
	  h_angles_3[i_cos][i_PHI]->Write("", TObject::kOverwrite);
	  h_angles_3[i_cos][i_PHI]->Delete();
	}
      }
    }
  }
  //Now for these we persistently keep the angles histos 
  //for time saving
  
  //type 4
  for(int i_M = 0; i_M < N_M; i_M++){
    char *sname = new char[50];
    sprintf(sname, "h_angles_type4_%d", i_M);
    h_angles_4[i_M] = (TH3D*) new TH3D(sname, sname, N_c1, min_c1, max_c1,
				       N_c2, min_c2, max_c2,
				       N_phi, min_phi, max_phi);
  }
  //type 5
  for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
    char *sname = new char[50];
    sprintf(sname, "h_angles_type5_%d", i_cos);
    h_angles_5[i_cos] = (TH3D*) new TH3D(sname, sname, N_c1, min_c1, max_c1,
					 N_c2, min_c2, max_c2,
					 N_phi, min_phi, max_phi);
  }
  //type 6
  for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
    char *sname = new char[50];
    sprintf(sname, "h_angles_type6_%d", i_PHI);
    h_angles_6[i_PHI] = (TH3D*) new TH3D(sname, sname, N_c1, min_c1, max_c1,
					 N_c2, min_c2, max_c2,
					 N_phi, min_phi, max_phi);
  }

  //type 8
  for(int i_M = 0; i_M < N_M; i_M++){
    char *sname = new char[50];
    sprintf(sname, "h_ANGLES_type8_%d", i_M);
    h_ANGLES_8[i_M] = (TH2D*) new TH2D(sname, sname, N_cosTHETA, min_cosTHETA, max_cosTHETA,
				       N_PHI, min_PHI, max_PHI);
  }
				      
  
  //
  // Now we loop through events to fill the histograms
  //

  int EVT_COUNT = 0;
  int NUM_EVT = intree->GetEntries();

  NTOT = 0;
  NPASS = 0;

  // Now we loop through events
  for(int ievt = 0; ievt < Nevent; ievt++) {
    //for(int ievt = 0; ievt < NUM_EVT; ievt++) {
    if(ievt%100000==0) cout << "event #" << ievt << " out of " << Nevent << endl;

    bool passed_cuts = false;
    while(passed_cuts == false){
      Resonance->GenBoost();
      intree->GetEntry(EVT_COUNT);
      EVT_COUNT++;
      if(EVT_COUNT >= NUM_EVT) EVT_COUNT = 0;
      
      Resonance->LoadEvent(massZ2GEN, cosTHETAGEN, PHIGEN, c1GEN, c2GEN, phiGEN);
      
      // compute the four-momenta of the four leptons
      Resonance->CalcGenMomenta();
      // smear the muons momenta according to detector
      Resonance->SmearMomenta(0);
      passed_cuts = Resonance->PassCuts(2.3, 10.0);
      NTOT++;
      if(passed_cuts){
	if(mH < 180){
	  Resonance->CalcRecoKinematics(true);
	} else {
	  Resonance->CalcRecoKinematics(false);
	}
	NPASS++;
      }
    }

    //Now we fill the event in the outtree
    TLorentzVector Z1, Z2, H;
   
    
   
    Z1 = Resonance->Get_Z1();
    Z2 = Resonance->Get_Z2();
    H = Resonance->Get_H();
  
    massH  = H.M();
    massZ1 = Z1.M();
    massZ2 = Z2.M();
    c1 = Resonance->Get_c1(); 
    c2 = Resonance->Get_c2(); 
    phi = Resonance->Get_phi();
    PHI = Resonance->Get_PHI();
    cosTHETA = Resonance->Get_cosTHETA();
    M = massZ2;

    if(phi < min_phi || phi >= max_phi ||
       M < min_M || M >= max_M ||
       PHI < min_PHI || PHI >= max_PHI ||
       cosTHETA < min_cosTHETA || cosTHETA >= max_cosTHETA ||
       c1 < min_c1 || c1 >= max_c1 ||
       c2 < min_c2 || c2 >= max_c2){
      ievt--;
      continue;
    }
    int i_M = int((M-min_M)*double(N_M)/(max_M-min_M));
    int i_cos = int((cosTHETA-min_cosTHETA)*double(N_cosTHETA)/(max_cosTHETA-min_cosTHETA));
    int i_PHI = int((PHI-min_PHI)*double(N_PHI)/(max_PHI-min_PHI));

    if(mode==1){
      //type 0
      for(;;){
	h_mZstar->Fill(M);
	h_ANGLES[i_M]->Fill(cosTHETA, PHI);
    
	if(DEL_MEM){
	  char *hname = new char[50];
	  sprintf(hname, "h_angles_%d_%d_%d", i_M, i_cos, i_PHI);
	  TH3D* temp = (TH3D*) outfile->Get(hname);
	  temp->Fill(c1,c2,phi);
	  outfile->cd();
	  temp->Write("", TObject::kOverwrite);
	  temp->Delete();
	} else {
	  h_angles[i_M][i_cos][i_PHI]->Fill(c1,c2,phi);
	}
	break;
      }
      //type 1
      for(;;){
	h_mZstar_1->Fill(M);
	h_cosTHETA_1[i_M]->Fill(cosTHETA);
	if(DEL_MEM){
	  char *hname = new char[50];
	  sprintf(hname, "h_angles_type1_%d_%d", i_M, i_cos);
	  TH3D* temp = (TH3D*) outfile->Get(hname);
	  temp->Fill(c1,c2,phi);
	  outfile->cd();
	  temp->Write("", TObject::kOverwrite);
	  temp->Delete();
	} else {
	  h_angles_1[i_M][i_cos]->Fill(c1,c2,phi);
	}
	break;
      }
      //type 2
      for(;;){
	h_mZstar_2->Fill(M);
	h_PHI_2[i_M]->Fill(PHI);
	if(DEL_MEM){
	  char *hname = new char[50];
	  sprintf(hname, "h_angles_type2_%d_%d", i_M, i_PHI);
	  TH3D* temp = (TH3D*) outfile->Get(hname);
	  temp->Fill(c1,c2,phi);
	  outfile->cd();
	  temp->Write("", TObject::kOverwrite);
	  temp->Delete();
	} else {
	  h_angles_2[i_M][i_PHI]->Fill(c1,c2,phi);
	}
	break;
      }
      //type 3
      for(;;){
	h_ANGLES_3->Fill(cosTHETA,PHI);
	if(DEL_MEM){
	  char *hname = new char[50];
	  sprintf(hname, "h_angles_type3_%d_%d", i_cos, i_PHI);
	  TH3D* temp = (TH3D*) outfile->Get(hname);
	  temp->Fill(c1,c2,phi);
	  outfile->cd();
	  temp->Write("", TObject::kOverwrite);
	  temp->Delete();
	} else {
	  h_angles_3[i_cos][i_PHI]->Fill(c1,c2,phi);
	}
	break;
      }
    }
    //type 4
    h_mZstar_4->Fill(M);
    h_angles_4[i_M]->Fill(c1,c2,phi);

    //type 5
    h_cosTHETA_5->Fill(cosTHETA);
    h_angles_5[i_cos]->Fill(c1,c2,phi);
     
    //type 6
    h_PHI_6->Fill(PHI);
    h_angles_6[i_PHI]->Fill(c1,c2,phi);

    //type 7
    h_angles_7->Fill(c1,c2,phi);

    //type 8
    h_mZstar_8->Fill(M);
    h_ANGLES_8[i_M]->Fill(cosTHETA,PHI);

    //type 9
    h_mZstar_9->Fill(M);
    h_cosTHETA_9->Fill(cosTHETA);
    h_PHI_9->Fill(PHI);
    h_c1_9->Fill(c1);
    h_c2_9->Fill(c2);
    h_phi_9->Fill(phi);
    
  }

  
  // write the remaining histograms to the outfile
  if(mode == 1){
    //type 0
    h_mZstar->Scale(INTEGRAL/double(NTOT));
    outfile->cd();
    h_mZstar->Write("", TObject::kOverwrite);
    h_mZstar->Delete();
    for(int iM = 0; iM < N_M; iM++){
      h_ANGLES[iM]->Scale(INTEGRAL/double(NTOT));
      outfile->cd();
      h_ANGLES[iM]->Write("", TObject::kOverwrite);
      h_ANGLES[iM]->Delete();
      if(DEL_MEM == false){
	for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	  for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	    h_angles[iM][i_cos][i_PHI]->Scale(INTEGRAL/double(NTOT));
	    outfile->cd();
	    h_angles[iM][i_cos][i_PHI]->Write("", TObject::kOverwrite);
	    h_angles[iM][i_cos][i_PHI]->Delete();
	  }
	}
      } else {
	for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	  for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	    char *name = new char[50];
	    sprintf(name, "h_angles_%d_%d_%d", iM, i_cos, i_PHI);
	    h_angles[iM][i_cos][i_PHI] = (TH3D*) outfile->Get(name);
	    h_angles[iM][i_cos][i_PHI]->Scale(INTEGRAL/double(NTOT));
	    outfile->cd();
	    h_angles[iM][i_cos][i_PHI]->Write("", TObject::kOverwrite);
	    h_angles[iM][i_cos][i_PHI]->Delete();
	  }
	}
      }
    }
    //type 1
    h_mZstar_1->Scale(INTEGRAL/double(NTOT));
     outfile->cd();
    h_mZstar_1->Write("", TObject::kOverwrite);
    h_mZstar_1->Delete();
    for(int iM = 0; iM < N_M; iM++){
      h_cosTHETA_1[iM]->Scale(INTEGRAL/double(NTOT));
      outfile->cd();
      h_cosTHETA_1[iM]->Write("", TObject::kOverwrite);
      h_cosTHETA_1[iM]->Delete();
      if(DEL_MEM == false){
	for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	  h_angles_1[iM][i_cos]->Scale(INTEGRAL/double(NTOT));
	  outfile->cd();
	  h_angles_1[iM][i_cos]->Write("", TObject::kOverwrite);
	  h_angles_1[iM][i_cos]->Delete();
	}
      } else {
	for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	  char *name = new char[50];
	  sprintf(name, "h_angles_type1_%d_%d", iM, i_cos);
	  h_angles_1[iM][i_cos] = (TH3D*) outfile->Get(name);
	  h_angles_1[iM][i_cos]->Scale(INTEGRAL/double(NTOT));
	  outfile->cd();
	  h_angles_1[iM][i_cos]->Write("", TObject::kOverwrite);
	  h_angles_1[iM][i_cos]->Delete();
	}
      }
    }
    //type 2
    h_mZstar_2->Scale(INTEGRAL/double(NTOT));
    outfile->cd();
    h_mZstar_2->Write("", TObject::kOverwrite);
    h_mZstar_2->Delete();
    for(int iM = 0; iM < N_M; iM++){
      h_PHI_2[iM]->Scale(INTEGRAL/double(NTOT));
      outfile->cd();
      h_PHI_2[iM]->Write("", TObject::kOverwrite);
      h_PHI_2[iM]->Delete();
      if(DEL_MEM == false){
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  h_angles_2[iM][i_PHI]->Scale(INTEGRAL/double(NTOT));
	  outfile->cd();
	  h_angles_2[iM][i_PHI]->Write("", TObject::kOverwrite);
	  h_angles_2[iM][i_PHI]->Delete();
	}
      } else {
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  char *name = new char[50];
	  sprintf(name, "h_angles_type2_%d_%d", iM, i_PHI);
	  h_angles_2[iM][i_PHI] = (TH3D*) outfile->Get(name);
	  h_angles_2[iM][i_PHI]->Scale(INTEGRAL/double(NTOT));
	  outfile->cd();
	  h_angles_2[iM][i_PHI]->Write("", TObject::kOverwrite);
	  h_angles_2[iM][i_PHI]->Delete();
	}
      }
    }
    //type 3
    h_ANGLES_3->Scale(INTEGRAL/double(NTOT));
    outfile->cd();
    h_ANGLES_3->Write("", TObject::kOverwrite);
    h_ANGLES_3->Delete();
    if(DEL_MEM == false){
      for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  h_angles_3[i_cos][i_PHI]->Scale(INTEGRAL/double(NTOT));
	  outfile->cd();
	  h_angles_3[i_cos][i_PHI]->Write("", TObject::kOverwrite);
	  h_angles_3[i_cos][i_PHI]->Delete();
	}
      }
    } else {
      for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  char *name = new char[50];
	  sprintf(name, "h_angles_type3_%d_%d", i_cos, i_PHI);
	  h_angles_3[i_cos][i_PHI] = (TH3D*) outfile->Get(name);
	  h_angles_3[i_cos][i_PHI]->Scale(INTEGRAL/double(NTOT));
	  outfile->cd();
	  h_angles_3[i_cos][i_PHI]->Write("", TObject::kOverwrite);
	  h_angles_3[i_cos][i_PHI]->Delete();
	}
      }
    }
  }
  //type 4
  h_mZstar_4->Scale(INTEGRAL/double(NTOT));
  outfile->cd();
  h_mZstar_4->Write("", TObject::kOverwrite);
  for(int iM = 0; iM < N_M; iM++){
    h_angles_4[iM]->Scale(INTEGRAL/double(NTOT));
    outfile->cd();
    h_angles_4[iM]->Write("", TObject::kOverwrite);
    h_angles_4[iM]->Delete();
  }
  //type 5
  h_cosTHETA_5->Scale(INTEGRAL/double(NTOT));
  outfile->cd();
  h_cosTHETA_5->Write("", TObject::kOverwrite);
  for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
    h_angles_5[i_cos]->Scale(INTEGRAL/double(NTOT));
    outfile->cd();
    h_angles_5[i_cos]->Write("", TObject::kOverwrite);
    h_angles_5[i_cos]->Delete();
  }
  //type 6
  h_PHI_6->Scale(INTEGRAL/double(NTOT));
  outfile->cd();
  h_PHI_6->Write("", TObject::kOverwrite);
  for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
    h_angles_6[i_PHI]->Scale(INTEGRAL/double(NTOT));
    outfile->cd();
    h_angles_6[i_PHI]->Write("", TObject::kOverwrite);
    h_angles_6[i_PHI]->Delete();
  }
  //type 7
  h_angles_7->Scale(INTEGRAL/double(NTOT));
  outfile->cd();
  h_angles_7->Write("", TObject::kOverwrite);
  
  //type 8
  h_mZstar_8->Scale(INTEGRAL/double(NTOT));
  outfile->cd();
  h_mZstar_8->Write("", TObject::kOverwrite);
  for(int iM = 0; iM < N_M; iM++){
    h_ANGLES_8[iM]->Scale(INTEGRAL/double(NTOT));
    outfile->cd();
    h_ANGLES_8[iM]->Write("", TObject::kOverwrite);
    h_ANGLES_8[iM]->Delete();
  }

  //type 9
  h_mZstar_9->Scale(INTEGRAL/double(NTOT));
  h_cosTHETA_9->Scale(INTEGRAL/double(NTOT));
  h_PHI_9->Scale(INTEGRAL/double(NTOT));
  h_c1_9->Scale(INTEGRAL/double(NTOT));
  h_c2_9->Scale(INTEGRAL/double(NTOT));
  h_phi_9->Scale(INTEGRAL/double(NTOT));
  outfile->cd();
  h_mZstar_9->Write("", TObject::kOverwrite);
  outfile->cd();
  h_cosTHETA_9->Write("", TObject::kOverwrite);
  outfile->cd();
  h_PHI_9->Write("", TObject::kOverwrite);
  outfile->cd();
  h_c1_9->Write("", TObject::kOverwrite);
  outfile->cd();
  h_c2_9->Write("", TObject::kOverwrite);
  outfile->cd();
  h_phi_9->Write("", TObject::kOverwrite);
  

  TTree* outtree = new TTree("data","data");
  outtree->Branch("N_M", &N_M, "N_M/I");
  outtree->Branch("N_cosTHETA", &N_cosTHETA, "N_cosTHETA/I");
  outtree->Branch("N_c1", &N_c1, "N_c1/I");
  outtree->Branch("N_c2", &N_c2, "N_c2/I");
  outtree->Branch("N_phi", &N_phi, "N_phi/I");
  outtree->Branch("N_PHI", &N_PHI, "N_PHI/I");
  
  outtree->Branch("min_M", &min_M, "min_M/D");
  outtree->Branch("max_M", &max_M, "max_M/D");
  outtree->Branch("min_cosTHETA", &min_cosTHETA, "min_cosTHETA/D");
  outtree->Branch("max_cosTHETA", &max_cosTHETA, "max_cosTHETA/D");
  outtree->Branch("min_c1", &min_c1, "min_c1/D");
  outtree->Branch("max_c1", &max_c1, "max_c1/D");
  outtree->Branch("min_c2", &min_c2, "min_c2/D");
  outtree->Branch("max_c2", &max_c2, "max_c2/D");
  outtree->Branch("min_phi", &min_phi, "min_phi/D");
  outtree->Branch("max_phi", &max_phi, "max_phi/D");
  outtree->Branch("min_PHI", &min_PHI, "min_PHI/D");
  outtree->Branch("max_PHI", &max_PHI, "max_PHI/D");
  
  outtree->Branch("b_angle", &b_angle, "b_angle/I");
  outtree->Branch("mH", &mH, "mH/D");
  outtree->Branch("wH", &wH, "wH/D");
  outtree->Branch("mode", &mode, "mode/I");
  outtree->Branch("INTEGRAL", &INTEGRAL, "INTEGRAL/D");
  outtree->Branch("NTOT", &NTOT, "NTOT/I");
  outtree->Branch("NPASS", &NPASS, "NPASS/I");


  outtree->Fill();
  outfile->cd();
  outtree->Write();
  outtree->Delete();

  outfile->Close();
}

