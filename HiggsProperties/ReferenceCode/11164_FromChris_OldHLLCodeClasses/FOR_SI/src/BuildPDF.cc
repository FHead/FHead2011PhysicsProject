#include <TRandom3.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <iostream>
#include <vector>
#include <BuildPDF.hh>

using namespace std;

#define GOLD 1.618034
#define GLIMIT 100.0
#define TINY 1.0e-20
#define ZEPS 1.0e-16
#define EPS 1.0e-16
#define ITMAX 2000
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d)
#define MOV3(a,b,c, d,e,f) (a)=(d);(b)=(e);(c)=(f)
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

BuildPDF::BuildPDF(int _type0, int _type1, int mass, char* dir_name){
  Init(_type0, _type1, mass, dir_name);
}

void BuildPDF::Init(int _type0, int _type1, int mass, char* dir_name) {
  // set seed and initialize random generator
  int jobpid   = getpid();
  TDatime *now = new TDatime();
  int today = now->GetDate();
  int clock = now->GetTime();
  int seed = today+clock+jobpid;
  gRandom = (TRandom3*) new TRandom3(seed);

  _mZ  = 91.1876;      // PDG value

  TYPE0 = _type0;
  TYPE1 = _type1;
  MASS = mass;
  DIR_NAME = dir_name;

  b_got_param = false;
  //
  // This is where models we build go (index 2)
  //
  b_H[2][0] = false;
  b_H[2][1] = false;
  b_H[2][2] = false;
  b_H[2][3] = false;

  b_H[0][0] = false;
  b_H[0][1] = false;
  b_H[0][2] = false;
  b_H[0][3] = false;

  b_H[1][0] = false;
  b_H[1][1] = false;
  b_H[1][2] = false;
  b_H[1][3] = false;

  //
  // Init the integrals to zero
  //
  double PDF_INTEGRAL[3][4];
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 4; j++){
      PDF_INTEGRAL[i][j] = 0.0;
    }
  }

  b_BKG[0] = false;
  b_BKG[1] = false;
  b_SIG[0] = false;
  b_SIG[1] = false;
  b_SB = false;

  //
  // Initiate 'discovery' exercise
  // if this, MASS is ignored from this function
  // We proceed to load the background info 
  // Signal must be done explicitly
  //
  if(TYPE0 < 0 || TYPE1 < 0){
    InitBKG();
      
    TYPE0 = -1;
    TYPE1 = -1;
  }
  
  //
  // Initiate the hypotheses
  //
  if(TYPE0 > 0){
    InitHYP(0, TYPE0);
  }
  if(TYPE1 > 0){
    InitHYP(1, TYPE1);
  }
  
}

void BuildPDF::InitBKG(){
  if(b_got_param == false){
    char* filename = new char[100];
    sprintf(filename, "%s/BKG/RECO_PDF.root", DIR_NAME);
    InitParam(filename);
    b_got_param = true;
  }
  InitHisto_SB();
  char* name = new char[100];
  sprintf(name, "%s/BKG/RECO_PDF.root", DIR_NAME);
  FillHisto_BKG(name);
}
 
void BuildPDF::InitHisto_SB(){
  if(b_SB == false){
    b_SB = true;
    //First we initiate BKG histograms
    for(int ij = 0; ij < 2; ij++){
      char *name0 = new char[50];
      sprintf(name0, "h_mH_BKG_%d", ij);
      h_mH_BKG[ij] = (TH1D*) new TH1D(name0,name0,N_M,min_M,max_M);
      for(int i_M = 0; i_M < N_M; i_M++){
	if(i_M%10 == 0) cout << i_M << "(" << N_M << ")" << endl;
	char *name1 = new char[50];
	sprintf(name1, "h_ANGLES_BKG_%d_%d", ij, i_M);
	h_ANGLES_BKG[ij][i_M] = (TH2D*) new TH2D(name1, name1, 
						 N_cosTHETA,min_cosTHETA,max_cosTHETA,
						 N_PHI, min_PHI, max_PHI);
	for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	  for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	    char *name2 = new char[50];
	    sprintf(name2, "h_angles_BKG_%d_%d_%d_%d",ij,i_M,i_cos,i_PHI);
	    h_angles_BKG[ij][i_M][i_cos][i_PHI] = (TH3D*) new TH3D(name2,name2, 
								   N_c1, min_c1, max_c1,
								   N_c2, min_c2, max_c2,
								   N_phi, min_phi, max_phi);
	  }
	}
      }
    }
    //NOW SIG histograms
    for(int ij = 0; ij < 2; ij++){
      char *name0 = new char[50];
      sprintf(name0, "h_mH_SIG_%d", ij);
      h_mH_SIG[ij] = (TH1D*) new TH1D(name0,name0,N_M,min_M,max_M);
      
      char *name1 = new char[50];
      sprintf(name1, "h_ANGLES_SIG_%d", ij);
      h_ANGLES_SIG[ij] = (TH2D*) new TH2D(name1, name1, 
					  N_cosTHETA,min_cosTHETA,max_cosTHETA,
					  N_PHI, min_PHI, max_PHI);
      for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  char *name2 = new char[50];
	  sprintf(name2, "h_angles_SIG_%d_%d_%d",ij,i_cos,i_PHI);
	  h_angles_SIG[ij][i_cos][i_PHI] = (TH3D*) new TH3D(name2,name2, 
							    N_c1, min_c1, max_c1,
							    N_c2, min_c2, max_c2,
							    N_phi, min_phi, max_phi);
	}
      }
    }
  }
}

void BuildPDF::InitSIG_GEN(int s_MASS){
  
  MASS_GEN = s_MASS;
  
  if(b_SIG[0] == true){
    h_mH_SIG[0]->Reset();
    h_ANGLES_SIG[0]->Reset();
    for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
      for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	h_angles_SIG[0][i_cos][i_PHI]->Reset();
      }
    }
  }
  b_SIG[0] = true;

  TH1D* temp1D;
  TH2D* temp2D;
  TH3D* temp3D;

  char* filename = new char[100];
  sprintf(filename, "%s/SIGNAL/%d/RECO_PDF.root", DIR_NAME, MASS_GEN);
  
  TFile* file = TFile::Open(filename,"READ");

  char *name0 = new char[50];
  sprintf(name0, "h_mH");
  temp1D = (TH1D*) file->Get(name0);

  cout << "Initiating Signal (GEN) from " << filename << endl;
  
  h_mH_SIG[0]->Add(temp1D);
  temp1D->Delete();
  h_mH_SIG[0]->Scale(1./h_mH_SIG[0]->Integral());
  
  char *name1 = new char[50];
  sprintf(name1, "h_ANGLES");
  temp2D = (TH2D*) file->Get(name1);
  h_ANGLES_SIG[0]->Add(temp2D);
  temp2D->Delete();
  double inte = h_ANGLES_SIG[0]->Integral();
  if(inte > 0.0){
    h_ANGLES_SIG[0]->Scale(1.0/inte);
  }
  for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
    for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
      char *name2 = new char[50];
      sprintf(name2, "h_angles_%d_%d",i_cos,i_PHI);
      temp3D = (TH3D*) file->Get(name2);
      h_angles_SIG[0][i_cos][i_PHI]->Add(temp3D);
      temp3D->Delete();
      inte = h_angles_SIG[0][i_cos][i_PHI]->Integral();
      if(inte > 0.0){
	h_angles_SIG[0][i_cos][i_PHI]->Scale(1.0/inte);
      }
    }
  }
  
  file->Close();
}

void BuildPDF::InitSIG_EVAL(int s_MASS){
  
  MASS_EVAL = s_MASS;
  
  if(b_SIG[1] == true){
    h_mH_SIG[1]->Reset();
    h_ANGLES_SIG[1]->Reset();
    for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
      for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	h_angles_SIG[1][i_cos][i_PHI]->Reset();
      }
    }
  }
  b_SIG[1] = true;

  TH1D* temp1D;
  TH2D* temp2D;
  TH3D* temp3D;
  
  char* filename = new char[100];
  sprintf(filename, "%s/SIGNAL/%d/RECO_PDF.root", DIR_NAME, MASS_EVAL);
  
  TFile* file = TFile::Open(filename,"READ");
  
  char *name0 = new char[50];
  sprintf(name0, "h_mH");
  temp1D = (TH1D*) file->Get(name0);

  cout << "Initiating Signal (EVAL) from " << filename << endl;
  
  h_mH_SIG[1]->Add(temp1D);
  temp1D->Delete();
  h_mH_SIG[1]->Scale(1./h_mH_SIG[1]->Integral());
  
  char *name1 = new char[50];
  sprintf(name1, "h_ANGLES");
  temp2D = (TH2D*) file->Get(name1);
  h_ANGLES_SIG[1]->Add(temp2D);
  temp2D->Delete();
  double inte = h_ANGLES_SIG[1]->Integral();
  if(inte > 0.0){
    h_ANGLES_SIG[1]->Scale(1.0/inte);
  }
  for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
    for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
      char *name2 = new char[50];
      sprintf(name2, "h_angles_%d_%d",i_cos,i_PHI);
      temp3D = (TH3D*) file->Get(name2);
      h_angles_SIG[1][i_cos][i_PHI]->Add(temp3D);
      temp3D->Delete();
      inte = h_angles_SIG[1][i_cos][i_PHI]->Integral();
      if(inte > 0.0){
	h_angles_SIG[1][i_cos][i_PHI]->Scale(1.0/inte);
	h_angles_SIG[1][i_cos][i_PHI]->Scale(h_ANGLES_SIG[1]->GetBinContent(i_cos+1,i_PHI+1));
      }
    }
  }
  
  file->Close();
}
 

void BuildPDF::FillHisto_BKG(char *filename){
  TH1D* temp1D;
  TH2D* temp2D;
  TH3D* temp3D;
  
  for(int ij = 0; ij < 2; ij++){
    if(b_BKG[ij] == true){
      h_mH_BKG[ij]->Reset();
      for(int i_M = 0; i_M < N_M; i_M++){
	h_ANGLES_BKG[ij][i_M]->Reset();
	for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	  for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	    h_angles_BKG[ij][i_M][i_cos][i_PHI]->Reset();
	  }
	}
      }
    }
  }
  b_BKG[0] = true;
  b_BKG[1] = true;


  TFile* file = TFile::Open(filename,"READ");

  char *name0 = new char[50];
  sprintf(name0, "h_mH");
  temp1D = (TH1D*) file->Get(name0);

  cout << "Initiating Background from " << filename << endl;
  

  h_mH_BKG[0]->Add(temp1D);
  h_mH_BKG[1]->Add(temp1D);
  temp1D->Delete();
  h_mH_BKG[0]->Scale(1./h_mH_BKG[0]->Integral());
  h_mH_BKG[1]->Scale(1./h_mH_BKG[1]->Integral());
  for(int i_M = 0; i_M < N_M; i_M++){
    if(i_M%10 == 0) cout << i_M << "(" << N_M << ")" << endl;
    char *name1 = new char[50];
    sprintf(name1, "h_ANGLES_%d", i_M);
    temp2D = (TH2D*) file->Get(name1);
    h_ANGLES_BKG[0][i_M]->Add(temp2D);
    h_ANGLES_BKG[1][i_M]->Add(temp2D);
    temp2D->Delete();
    double inte = h_ANGLES_BKG[0][i_M]->Integral();
    if(inte > 0.0){
      h_ANGLES_BKG[0][i_M]->Scale(1.0/inte);
      h_ANGLES_BKG[1][i_M]->Scale(1.0/inte);
      h_ANGLES_BKG[1][i_M]->Scale(h_mH_BKG[1]->GetBinContent(i_M+1));
    }
    for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
      for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	char *name2 = new char[50];
	sprintf(name2, "h_angles_%d_%d_%d",i_M,i_cos,i_PHI);
	temp3D = (TH3D*) file->Get(name2);
	h_angles_BKG[0][i_M][i_cos][i_PHI]->Add(temp3D);
	h_angles_BKG[1][i_M][i_cos][i_PHI]->Add(temp3D);
	temp3D->Delete();
	inte = h_angles_BKG[0][i_M][i_cos][i_PHI]->Integral();
	if(inte > 0.0){
	  h_angles_BKG[0][i_M][i_cos][i_PHI]->Scale(1.0/inte);
	  h_angles_BKG[1][i_M][i_cos][i_PHI]->Scale(1.0/inte);
	  h_angles_BKG[1][i_M][i_cos][i_PHI]->Scale(h_ANGLES_BKG[1][i_M]->GetBinContent(i_cos+1,i_PHI+1));
	}
      }
    }
  }
  
  file->Close();
}

void BuildPDF::InitHYP(int ihyp, int type){
 
  if(type == 1){
    b_H[ihyp][0] = true;
    b_H[ihyp][1] = true;
    b_H[ihyp][2] = true;
    b_H[ihyp][3] = false;
    if(b_got_param == false){
      char* filename = new char[100];
      sprintf(filename, "%s/ROOT_SM_%d/RECO_PDF.root", DIR_NAME, MASS);
      InitParam(filename);
      b_got_param = true;
    }
  }
  if(type == 2){
    b_H[ihyp][0] = true;
    b_H[ihyp][1] = true;
    b_H[ihyp][2] = true;
    b_H[ihyp][3] = false;
    if(b_got_param == false){
      char* filename = new char[100];
      sprintf(filename, "%s/ROOT_SM_%d/RECO_PDF.root", DIR_NAME, MASS);
      InitParam(filename);
      b_got_param = true;
    }
  }
  if(type == 3){
    b_H[ihyp][0] = true;
    b_H[ihyp][1] = true;
    b_H[ihyp][2] = true;
    b_H[ihyp][3] = false;
    if(b_got_param == false){
      char* filename = new char[100];
      sprintf(filename, "%s/ROOT_SM_%d/RECO_PDF.root", DIR_NAME, MASS);
      InitParam(filename);
      b_got_param = true;
    }
  }
  if(type == 4){
    b_H[ihyp][0] = true;
    b_H[ihyp][1] = true;
    b_H[ihyp][2] = true;
    b_H[ihyp][3] = true;
    if(b_got_param == false){
      char* filename = new char[100];
      sprintf(filename, "%s/ROOT_PV_%d/RECO_PDF.root", DIR_NAME, MASS);
      InitParam(filename);
      b_got_param = true;
    }
  }
  //initialize the empty histograms for this PDF
  InitHisto(ihyp);
  
  //Now we fill the histograms from files
  if(type == 1){
    char *nameA = new char[100];
    sprintf(nameA, "%s/ROOT_SM_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 0, 1.0*_mZ*_mZ*_mZ*_mZ, nameA);
    char *nameBplus = new char[100];
    sprintf(nameBplus, "%s/ROOT_XPplus_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 1, 1.0*_mZ*_mZ, nameBplus);
    char *nameBminus = new char[100];
    sprintf(nameBminus, "%s/ROOT_XPminus_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 1, -1.0*_mZ*_mZ, nameBminus);
    char *nameC = new char[100];
    sprintf(nameC, "%s/ROOT_PS_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 2, 1.0, nameC);
  }
  if(type == 2){
    char *nameA = new char[100];
    sprintf(nameA, "%s/ROOT_SM_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 0, 1.0*_mZ*_mZ*_mZ*_mZ, nameA);
    char *nameBplus = new char[100];
    sprintf(nameBplus, "%s/ROOT_XQplus_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 1, 1.0*_mZ*_mZ, nameBplus);
    char *nameBminus = new char[100];
    sprintf(nameBminus, "%s/ROOT_XQminus_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 1, -1.0*_mZ*_mZ, nameBminus);
    char *nameC = new char[100];
    sprintf(nameC, "%s/ROOT_PS_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 2, 1.0, nameC);
  }
  if(type == 3){
    char *nameA = new char[100];
    sprintf(nameA, "%s/ROOT_SM_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 0, 1.0*_mZ*_mZ*_mZ*_mZ, nameA);
    char *nameBplus = new char[100];
    sprintf(nameBplus, "%s/ROOT_XYplus_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 1, 1.0*_mZ*_mZ, nameBplus);
    char *nameBminus = new char[100];
    sprintf(nameBminus, "%s/ROOT_XYminus_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 1, -1.0*_mZ*_mZ, nameBminus);
    char *nameC = new char[100];
    sprintf(nameC, "%s/ROOT_YY_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 2, 1.0, nameC);
  }
  if(type == 4){
    char *nameA = new char[100];
    sprintf(nameA, "%s/ROOT_PV_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 0, 1.0, nameA);
    char *nameBplus = new char[100];
    sprintf(nameBplus, "%s/ROOT_Vcosplus_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 1, 1.0, nameBplus);
    char *nameBminus = new char[100];
    sprintf(nameBminus, "%s/ROOT_Vcosminus_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 1, -1.0, nameBminus);
    char *nameCplus = new char[100];
    sprintf(nameCplus, "%s/ROOT_Vsinplus_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 2, 1.0, nameCplus);
    char *nameCminus = new char[100];
    sprintf(nameCminus, "%s/ROOT_Vsinminus_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 2, -1.0, nameCminus);
    char *nameD = new char[100];
    sprintf(nameD, "%s/ROOT_PA_%d/RECO_PDF.root", DIR_NAME, MASS);
    FillHisto(ihyp, 3, 1.0, nameD);
  }
  
}

void BuildPDF::InitParam(char* filename){
  TFile* file = TFile::Open(filename,"READ");
  TTree* param = (TTree*) file->Get("data");

  param->SetBranchAddress("N_M", &N_M, &b_N_M);
  param->SetBranchAddress("N_cosTHETA", &N_cosTHETA, &b_N_cosTHETA);
  param->SetBranchAddress("N_c1", &N_c1, &b_N_c1);
  param->SetBranchAddress("N_c2", &N_c2, &b_N_c2);
  param->SetBranchAddress("N_phi", &N_phi, &b_N_phi);
  param->SetBranchAddress("N_PHI", &N_PHI, &b_N_PHI);
  
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
  param->GetEntry(0);
  param->Delete();
  file->Close();
}

void BuildPDF::InitHisto(int ihyp){
  for(int ihist = 0; ihist < 4; ihist++){
    if(b_H[ihyp][ihist] == true){
      char *name0 = new char[50];
      sprintf(name0, "h_mZstar_%d_%d", ihyp, ihist);
      h_mZstar[ihyp][ihist] = (TH1D*) new TH1D(name0,name0,N_M,min_M,max_M);
      for(int i_M = 0; i_M < N_M; i_M++){
	char *name1 = new char[50];
	sprintf(name1, "h_ANGLES_%d_%d_%d", ihyp, ihist, i_M);
	h_ANGLES[ihyp][ihist][i_M] = (TH2D*) new TH2D(name1, name1, 
						      N_cosTHETA,min_cosTHETA,max_cosTHETA,
						      N_PHI, min_PHI, max_PHI);
	for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	  for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	    char *name2 = new char[50];
	    sprintf(name2, "h_angles_%d_%d_%d_%d_%d",ihyp,ihist,i_M,i_cos,i_PHI);
	    h_angles[ihyp][ihist][i_M][i_cos][i_PHI] = (TH3D*) new TH3D(name2,name2, 
									N_c1, min_c1, max_c1,
									N_c2, min_c2, max_c2,
									N_phi, min_phi, max_phi);
	  }
	}
      }
    }
  }
}
  
void BuildPDF::FillHisto(int ihyp, int ihist, double sign, char *filename){
  TH1D* temp1D;
  TH2D* temp2D;
  TH3D* temp3D;
  
  double INTEGRAL;
  TBranch *b_INTEGRAL;
  int N_hist;


  TFile* file = TFile::Open(filename,"READ");

  TTree* param = (TTree*) file->Get("data");
  param->SetBranchAddress("INTEGRAL", &INTEGRAL, &b_INTEGRAL);
  N_hist = param->GetEntries();
  param->GetEntry(0);
  param->Delete();
  
  char *name0 = new char[50];
  sprintf(name0, "h_mZstar");
  temp1D = (TH1D*) file->Get(name0);

  if(temp1D->Integral() < 0.0){
    sign *= -1.;
  }

  cout << "Initiating hypothesis " << ihyp << " , component " << ihist << endl;
  cout << "Integral from file = " << INTEGRAL*sign << endl;
  cout << "Integral from hist = " << sign*temp1D->Integral() << endl;

  //Change me later!!!!!!!!!!
  //PDF_INTEGRAL[ihyp][ihist] += sign*INTEGRAL;
  PDF_INTEGRAL[ihyp][ihist] += sign*temp1D->Integral();

  h_mZstar[ihyp][ihist]->Add(temp1D, sign/double(N_hist));
  temp1D->Delete();
  for(int i_M = 0; i_M < N_M; i_M++){
    char *name1 = new char[50];
    sprintf(name1, "h_ANGLES_%d", i_M);
    temp2D = (TH2D*) file->Get(name1);
    h_ANGLES[ihyp][ihist][i_M]->Add(temp2D, sign/double(N_hist));
    temp2D->Delete();
    for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
      for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	char *name2 = new char[50];
	sprintf(name2, "h_angles_%d_%d_%d",i_M,i_cos,i_PHI);
	temp3D = (TH3D*) file->Get(name2);
	h_angles[ihyp][ihist][i_M][i_cos][i_PHI]->Add(temp3D, sign/double(N_hist));
	temp3D->Delete();
      }
    }
  }

  file->Close();
}

void BuildPDF::CleanUp(){
  for(int ihyp = 0; ihyp < 3; ihyp++){
    for(int ihist = 0; ihist < 4; ihist++){
      if(b_H[ihyp][ihist] == true){
	h_mZstar[ihyp][ihist]->Delete();
	for(int i_M = 0; i_M < N_M; i_M++){
	  h_ANGLES[ihyp][ihist][i_M]->Delete();
	  for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	    for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	      h_angles[ihyp][ihist][i_M][i_cos][i_PHI]->Delete();
	    }
	  }
	}
      }
    }
  }
}
  

//
// par[0] = psi 
// par[1] = delta / Lambda/Mz
//
void BuildPDF::GenerateMODEL(int ihyp, double par1, double par2){
  //init MODEL histogram if not already done
  if(b_H[2][0] == false){
    b_H[2][0] = true;
    InitHisto(2);
  } else {
    //Reset the histograms for MODEL
    h_mZstar[2][0]->Reset();
    for(int i_M = 0; i_M < N_M; i_M++){
      h_ANGLES[2][0][i_M]->Reset();
      for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  h_angles[2][0][i_M][i_cos][i_PHI]->Reset();
	}
      }
    }
  }

  int type;
  if(ihyp == 0)
    type = TYPE0;
  if(ihyp == 1)
    type = TYPE1;

  //Now we build the normalized PDF for generation
  if(type == 1 || type == 2 || type == 3){
    //start with M dist
    double psi = par1;
    h_mZstar[2][0]->Add(h_mZstar[ihyp][0], cos(psi)*cos(psi));
    h_mZstar[2][0]->Add(h_mZstar[ihyp][1], sin(psi)*cos(psi));
    h_mZstar[2][0]->Add(h_mZstar[ihyp][2], sin(psi)*sin(psi));
    //
    //Prevent 0's
    //
    for(int ib = 0; ib < N_M; ib++){
      if(h_mZstar[2][0]->GetBinContent(ib+1) < 0.0)
	h_mZstar[2][0]->SetBinContent(ib+1,0.0);
    }
    h_mZstar[2][0]->Scale(1./h_mZstar[2][0]->Integral());
    for(int i_M = 0; i_M < N_M; i_M++){
      h_ANGLES[2][0][i_M]->Add(h_ANGLES[ihyp][0][i_M], cos(psi)*cos(psi));
      h_ANGLES[2][0][i_M]->Add(h_ANGLES[ihyp][1][i_M], sin(psi)*cos(psi));
      h_ANGLES[2][0][i_M]->Add(h_ANGLES[ihyp][2][i_M], sin(psi)*sin(psi));
      for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  if(h_ANGLES[2][0][i_M]->GetBinContent(i_cos+1,i_PHI+1) < 0.0){
	    h_ANGLES[2][0][i_M]->SetBinContent(i_cos+1,i_PHI+1,0.0);
	  }
	}
      }
      h_ANGLES[2][0][i_M]->Scale(1./h_ANGLES[2][0][i_M]->Integral());
      for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  h_angles[2][0][i_M][i_cos][i_PHI]->Add(h_angles[ihyp][0][i_M][i_cos][i_PHI], cos(psi)*cos(psi));
	  h_angles[2][0][i_M][i_cos][i_PHI]->Add(h_angles[ihyp][1][i_M][i_cos][i_PHI], sin(psi)*cos(psi));
	  h_angles[2][0][i_M][i_cos][i_PHI]->Add(h_angles[ihyp][2][i_M][i_cos][i_PHI], sin(psi)*sin(psi));
	  for(int i_c1 = 0; i_c1 < N_c1; i_c1++){
	    for(int i_c2 = 0; i_c2 < N_c2; i_c2++){
	      for(int i_phi = 0; i_phi < N_phi; i_phi++){
		if(h_angles[2][0][i_M][i_cos][i_PHI]->GetBinContent(i_c1+1,i_c2+1,i_phi+1) < 0.0){
		  h_angles[2][0][i_M][i_cos][i_PHI]->SetBinContent(i_c1+1,i_c2+1,i_phi+1, 0.0);
		}
	      }
	    }
	  }
	  h_angles[2][0][i_M][i_cos][i_PHI]->Scale(1./h_angles[2][0][i_M][i_cos][i_PHI]->Integral());
	}
      }
    }
  }
  //disable this for now
  if(type == 5){
    //start with M dist
    double psi = par1;
    double form = (1.0 - 1.0/par2);
    h_mZstar[2][0]->Add(h_mZstar[ihyp][0], form*form*cos(psi)*cos(psi));
    h_mZstar[2][0]->Add(h_mZstar[ihyp][1], form*sin(psi)*cos(psi));
    h_mZstar[2][0]->Add(h_mZstar[ihyp][2], sin(psi)*sin(psi));
    h_mZstar[2][0]->Scale(1./h_mZstar[2][0]->Integral());
    for(int i_M = 0; i_M < N_M; i_M++){
      h_ANGLES[2][0][i_M]->Add(h_ANGLES[ihyp][0][i_M], form*form*cos(psi)*cos(psi));
      h_ANGLES[2][0][i_M]->Add(h_ANGLES[ihyp][1][i_M], form*sin(psi)*cos(psi));
      h_ANGLES[2][0][i_M]->Add(h_ANGLES[ihyp][2][i_M], sin(psi)*sin(psi));
      h_ANGLES[2][0][i_M]->Scale(1./h_ANGLES[2][0][i_M]->Integral());
      for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  h_angles[2][0][i_M][i_cos][i_PHI]->Add(h_angles[ihyp][0][i_M][i_cos][i_PHI], form*form*cos(psi)*cos(psi));
	  h_angles[2][0][i_M][i_cos][i_PHI]->Add(h_angles[ihyp][1][i_M][i_cos][i_PHI], form*sin(psi)*cos(psi));
	  h_angles[2][0][i_M][i_cos][i_PHI]->Add(h_angles[ihyp][2][i_M][i_cos][i_PHI], sin(psi)*sin(psi));
	  h_angles[2][0][i_M][i_cos][i_PHI]->Scale(1./h_angles[2][0][i_M][i_cos][i_PHI]->Integral());
	}
      }
    }
  }
  if(type == 4){
    //start with M dist
    double psi = par1;
    double delta = par2;
    h_mZstar[2][0]->Add(h_mZstar[ihyp][0], cos(psi)*cos(psi));
    h_mZstar[2][0]->Add(h_mZstar[ihyp][1], cos(delta)*sin(psi)*cos(psi));
    h_mZstar[2][0]->Add(h_mZstar[ihyp][2], sin(delta)*sin(psi)*cos(psi));
    h_mZstar[2][0]->Add(h_mZstar[ihyp][3], sin(psi)*sin(psi));
    h_mZstar[2][0]->Scale(1./h_mZstar[2][0]->Integral());
    for(int i_M = 0; i_M < N_M; i_M++){
      h_ANGLES[2][0][i_M]->Add(h_ANGLES[ihyp][0][i_M], cos(psi)*cos(psi));
      h_ANGLES[2][0][i_M]->Add(h_ANGLES[ihyp][1][i_M], cos(delta)*sin(psi)*cos(psi));
      h_ANGLES[2][0][i_M]->Add(h_ANGLES[ihyp][2][i_M], sin(delta)*sin(psi)*cos(psi));
      h_ANGLES[2][0][i_M]->Add(h_ANGLES[ihyp][3][i_M], sin(psi)*sin(psi));
      h_ANGLES[2][0][i_M]->Scale(1./h_ANGLES[2][0][i_M]->Integral());
      for(int i_cos = 0; i_cos < N_cosTHETA; i_cos++){
	for(int i_PHI = 0; i_PHI < N_PHI; i_PHI++){
	  h_angles[2][0][i_M][i_cos][i_PHI]->Add(h_angles[ihyp][0][i_M][i_cos][i_PHI], cos(psi)*cos(psi));
	  h_angles[2][0][i_M][i_cos][i_PHI]->Add(h_angles[ihyp][1][i_M][i_cos][i_PHI], cos(delta)*sin(psi)*cos(psi));
	  h_angles[2][0][i_M][i_cos][i_PHI]->Add(h_angles[ihyp][2][i_M][i_cos][i_PHI], sin(delta)*sin(psi)*cos(psi));
	  h_angles[2][0][i_M][i_cos][i_PHI]->Add(h_angles[ihyp][3][i_M][i_cos][i_PHI], sin(psi)*sin(psi));
	  h_angles[2][0][i_M][i_cos][i_PHI]->Scale(1./h_angles[2][0][i_M][i_cos][i_PHI]->Integral());
	}
      }
    }
  }
}

void BuildPDF::GenerateEvents(int N_sig, int N_bkg){
  //Now we generate some events!!!!
  double _M, _cosTHETA, _PHI, _c1, _c2, _phi;
  
  NEVT = 0;
  
  if(b_BKG[0] == false || b_SIG[0] == false){
    cout << "ERROR: NEED TO INITIALIZE SIGNAL OR BKG FIRST!!!" << endl;
    return;
  }

  for(int i_evt = 0; i_evt < N_sig; i_evt++){
    
    _M = h_mH_SIG[0]->GetRandom();
    int i_M = int((_M-min_M)*double(N_M)/(max_M-min_M));
    if(i_M <= 0)
      i_M = 0;
    if(i_M >= N_M)
      i_M = N_M-1;
    h_ANGLES_SIG[0]->GetRandom2(_cosTHETA, _PHI);
    int i_cos = int((_cosTHETA-min_cosTHETA)*double(N_cosTHETA)/(max_cosTHETA-min_cosTHETA));
    if(i_cos <= 0)
      i_cos = 0;
    if(i_cos >= N_cosTHETA)
      i_cos = N_cosTHETA-1;
    int i_PHI = int((_PHI-min_PHI)*double(N_PHI)/(max_PHI-min_PHI));
    if(i_PHI <= 0)
      i_PHI = 0;
    if(i_PHI >= N_PHI)
      i_PHI = N_PHI-1;
    h_angles_SIG[0][i_cos][i_PHI]->GetRandom3(_c1,_c2,_phi);
    
    M[NEVT] = _M;
    cosTHETA[NEVT] = _cosTHETA;
    PHI[NEVT] = _PHI;
    c1[NEVT] = _c1;
    c2[NEVT] = _c2;
    phi[NEVT] = _phi;
    NEVT++;
    
  }

  for(int i_evt = 0; i_evt < N_bkg; i_evt++){
    
    _M = h_mH_BKG[0]->GetRandom();
    int i_M = int((_M-min_M)*double(N_M)/(max_M-min_M));
    if(i_M <= 0)
      i_M = 0;
    if(i_M >= N_M)
      i_M = N_M-1;
    h_ANGLES_BKG[0][i_M]->GetRandom2(_cosTHETA, _PHI);
    int i_cos = int((_cosTHETA-min_cosTHETA)*double(N_cosTHETA)/(max_cosTHETA-min_cosTHETA));
    if(i_cos <= 0)
      i_cos = 0;
    if(i_cos >= N_cosTHETA)
      i_cos = N_cosTHETA-1;
    int i_PHI = int((_PHI-min_PHI)*double(N_PHI)/(max_PHI-min_PHI));
    if(i_PHI <= 0)
      i_PHI = 0;
    if(i_PHI >= N_PHI)
      i_PHI = N_PHI-1;
    h_angles_BKG[0][i_M][i_cos][i_PHI]->GetRandom3(_c1,_c2,_phi);
    
    M[NEVT] = _M;
    cosTHETA[NEVT] = _cosTHETA;
    PHI[NEVT] = _PHI;
    c1[NEVT] = _c1;
    c2[NEVT] = _c2;
    phi[NEVT] = _phi;
    NEVT++;
  }

  //And we're done!!!!!

}

void BuildPDF::GenerateEvents(int N_evt){
  //Now we generate some events!!!!
  double _M, _cosTHETA, _PHI, _c1, _c2, _phi;
  
  NEVT = 0;


  for(int i_evt = 0; i_evt < N_evt; i_evt++){
 
    _M = h_mZstar[2][0]->GetRandom();
    int i_M = int((_M-min_M)*double(N_M)/(max_M-min_M));
    if(i_M <= 0)
      i_M = 0;
    if(i_M >= N_M)
      i_M = N_M-1;
    h_ANGLES[2][0][i_M]->GetRandom2(_cosTHETA, _PHI);
    int i_cos = int((_cosTHETA-min_cosTHETA)*double(N_cosTHETA)/(max_cosTHETA-min_cosTHETA));
    if(i_cos <= 0)
      i_cos = 0;
    if(i_cos >= N_cosTHETA)
      i_cos = N_cosTHETA-1;
    int i_PHI = int((_PHI-min_PHI)*double(N_PHI)/(max_PHI-min_PHI));
    if(i_PHI <= 0)
      i_PHI = 0;
    if(i_PHI >= N_PHI)
      i_PHI = N_PHI-1;
    h_angles[2][0][i_M][i_cos][i_PHI]->GetRandom3(_c1,_c2,_phi);
  
    M[NEVT] = _M;
    cosTHETA[NEVT] = _cosTHETA;
    PHI[NEVT] = _PHI;
    c1[NEVT] = _c1;
    c2[NEVT] = _c2;
    phi[NEVT] = _phi;
    NEVT++;
   
  }

  //And we're done!!!!!

}

vector<double> BuildPDF::MeasurePar(int ihyp){
  vector<double> ret;
  
  int type;
  if(ihyp == 0)
    type = TYPE0;
  if(ihyp == 1)
    type = TYPE1;

  if(type == 1 || type == 2 || type == 3){
    InitEval(ihyp);

    double ax, bx, cx;
    ax = -1.0*asin(1.0)/2.0;
    bx = asin(1.0)/2.0;
    mnbrak(&ax, &bx, &cx, 1);

    ret.push_back(dbrent(ax, bx, cx, 10e-7, 1));

    return ret;
  }

  if(type == 4){
    InitEval(ihyp);
    double p[2];
    p[0] = 0.0;
    p[1] = 0.0;
    frprmn(p, 10e-7);
    ret.push_back(p[0]);
    ret.push_back(p[1]);
  }

  if(type < 0){
    if(ihyp == 0){
      SB_OPT = false;
    }
    if(ihyp == 1){
      SB_OPT = true;
    }
    InitEval();
    double p[2];
    p[0] = 0.5*double(NEVT);
    p[1] = 0.5*double(NEVT);
    frprmn(p, 10e-7);
    ret.push_back(p[0]);
    ret.push_back(p[1]);
  }

  return ret;
}

void BuildPDF::InitEval(){
  int N_evt = NEVT;

  if(b_BKG[1] == false || b_SIG[1] == false){
    cout << "ERROR: NEED TO INITIALIZE SIGNAL OR BKG FIRST!!!" << endl;
    return;
  }

  eval_type = -1;
  eval_hyp = -1;

  double _M, _cosTHETA, _PHI, _c1, _c2, _phi;

  for(int i_evt = 0; i_evt < N_evt; i_evt++){
    _M = M[i_evt];
    _cosTHETA = cosTHETA[i_evt];
    _PHI = PHI[i_evt];
    _c1 = c1[i_evt];
    _c2 = c2[i_evt];
    _phi = phi[i_evt];

    int i_M = int((_M-min_M)*double(N_M)/(max_M-min_M));
    int i_cos = int((_cosTHETA-min_cosTHETA)*double(N_cosTHETA)/(max_cosTHETA-min_cosTHETA));
    int i_PHI = int((_PHI-min_PHI)*double(N_PHI)/(max_PHI-min_PHI));
    int i_c1 = int((_c1-min_c1)*double(N_c1)/(max_c1-min_c1));
    int i_c2 = int((_c2-min_c2)*double(N_c2)/(max_c2-min_c2));
    int i_phi = int((_phi-min_phi)*double(N_phi)/(max_phi-min_phi));
    if(i_M <= 0)
      i_M = 0;
    if(i_M >= N_M)
      i_M = N_M-1;
    if(i_cos <= 0)
      i_cos = 0;
    if(i_cos >= N_cosTHETA)
      i_cos = N_cosTHETA-1;
    if(i_PHI <= 0)
      i_PHI = 0;
    if(i_PHI >= N_PHI)
      i_PHI = N_PHI-1;
    if(i_c1 <= 0)
      i_c1 = 0;
    if(i_c1 >= N_c1)
      i_c1 = N_c1-1;
    if(i_c2 <= 0)
      i_c2 = 0;
    if(i_c2 >= N_c2)
      i_c2 = N_c2-1;
    if(i_phi <= 0)
      i_phi = 0;
    if(i_phi >= N_phi)
      i_phi = N_phi-1;
    
    if(SB_OPT == true){
      val[0][i_evt] = h_angles_BKG[1][i_M][i_cos][i_PHI]->GetBinContent(i_c1+1, i_c2+1, i_phi+1);
      val[1][i_evt] = h_angles_SIG[1][i_cos][i_PHI]->GetBinContent(i_c1+1, i_c2+1, i_phi+1);
      val[1][i_evt] *= h_mH_SIG[1]->GetBinContent(i_M+1);
    } else {
      val[0][i_evt] = h_mH_BKG[1]->GetBinContent(i_M+1);
      val[1][i_evt] = h_mH_SIG[1]->GetBinContent(i_M+1);
    }
  }
}


void BuildPDF::InitEval(int ihyp){
  int N_evt = NEVT;

  if(ihyp == 0){
    eval_type = TYPE0;
  }
  if(ihyp == 1)
    eval_type = TYPE1;

  double _M, _cosTHETA, _PHI, _c1, _c2, _phi;

  for(int i_evt = 0; i_evt < N_evt; i_evt++){
    _M = M[i_evt];
    _cosTHETA = cosTHETA[i_evt];
    _PHI = PHI[i_evt];
    _c1 = c1[i_evt];
    _c2 = c2[i_evt];
    _phi = phi[i_evt];

    int i_M = int((_M-min_M)*double(N_M)/(max_M-min_M));
    int i_cos = int((_cosTHETA-min_cosTHETA)*double(N_cosTHETA)/(max_cosTHETA-min_cosTHETA));
    int i_PHI = int((_PHI-min_PHI)*double(N_PHI)/(max_PHI-min_PHI));
    int i_c1 = int((_c1-min_c1)*double(N_c1)/(max_c1-min_c1));
    int i_c2 = int((_c2-min_c2)*double(N_c2)/(max_c2-min_c2));
    int i_phi = int((_phi-min_phi)*double(N_phi)/(max_phi-min_phi));
    if(i_M <= 0)
      i_M = 0;
    if(i_M >= N_M)
      i_M = N_M-1;
    if(i_cos <= 0)
      i_cos = 0;
    if(i_cos >= N_cosTHETA)
      i_cos = N_cosTHETA-1;
    if(i_PHI <= 0)
      i_PHI = 0;
    if(i_PHI >= N_PHI)
      i_PHI = N_PHI-1;
    if(i_c1 <= 0)
      i_c1 = 0;
    if(i_c1 >= N_c1)
      i_c1 = N_c1-1;
    if(i_c2 <= 0)
      i_c2 = 0;
    if(i_c2 >= N_c2)
      i_c2 = N_c2-1;
    if(i_phi <= 0)
      i_phi = 0;
    if(i_phi >= N_phi)
      i_phi = N_phi-1;
    for(int ihist = 0; ihist < 4; ihist++){
      if(b_H[ihyp][ihist] == true){
	val[ihist][i_evt] = h_angles[ihyp][ihist][i_M][i_cos][i_PHI]->GetBinContent(i_c1+1, i_c2+1, i_phi+1);
      } else {
	val[ihist][i_evt] = 0.0;
      }
    }
  }
}

double BuildPDF::EvaluateNLL(double par1, double par2){
  
  int ihyp = eval_hyp;
  int type = eval_type;
  int N_evt = NEVT;
  double NLL = 0.0;

  double DEN = 0.0;

  double C[4];

  if(type < 0){
    
    if(par1 < 0.0 || par2 < 0.0) return 1000000000.0;
   
    double N_sig = par2;
    double N_bkg = par1;
    NLL += N_sig+N_bkg;
    for(int i_evt = 0; i_evt < N_evt; i_evt++){
      double PROB = 0.0;
      PROB = N_bkg*val[0][i_evt] + N_sig*val[1][i_evt];
      if(PROB > 0.0){
	NLL -= log(PROB);
      } else {
	PROB = 0.00000000001;
	NLL -= log(PROB);
      }
    }
  }

  if(type >= 0){
    if(type == 1 || type == 2 || type == 3){
      double psi = par1;
      C[0] = cos(psi)*cos(psi);
      C[1] = cos(psi)*sin(psi);
      C[2] = sin(psi)*sin(psi);
      C[3] = 0.0;
      
      
      DEN = C[0]*PDF_INTEGRAL[ihyp][0]
	+ C[1]*PDF_INTEGRAL[ihyp][1]
	+ C[2]*PDF_INTEGRAL[ihyp][2];
    }
    
    if(type == 4){
      double psi = par1;
      double delta = par2;
      C[0] = cos(psi)*cos(psi);
      C[1] = sin(psi)*cos(psi)*cos(delta);
      C[2] = sin(psi)*cos(psi)*sin(delta);
      C[3] = sin(psi)*sin(psi);
      
      DEN = C[0]*PDF_INTEGRAL[ihyp][0]
	+ C[3]*PDF_INTEGRAL[ihyp][3];
    }
    
    double LPROB_TOT = 0.0;
    
    for(int i_evt = 0; i_evt < N_evt; i_evt++){
      double PROB = 0.0;
      for(int ihist = 0; ihist < 4; ihist++){
	if(b_H[ihyp][ihist] == true){
	  PROB += C[ihist]*val[ihist][i_evt];
	}
      }
      PROB /= DEN;
      if(PROB <= 0.0) PROB /= -10000.0;
      
      LPROB_TOT -= log(PROB);
    }
    
    
    NLL = LPROB_TOT;
    
    //cout << NLL << endl;
  }
    
  return NLL;
}
    
vector<double> BuildPDF::EvaluateDerNLL(double par1, double par2){
  
  double NLL = 0.0;

  vector<double> ret;

  int ihyp = eval_hyp;
  int type = eval_type;

  int N_evt = NEVT;
  

  if(type < 0){
   
    double N_sb[2];
    N_sb[0] = par1;
    N_sb[1] = par2;
    
    double dNLL[2];
    dNLL[0] = 0.0;
    dNLL[1] = 0.0;
    
    for(int i_evt = 0; i_evt < N_evt; i_evt++){
      double PROB = 0.0;
      for(int ihist = 0; ihist < 2; ihist++){
	PROB += N_sb[ihist]*val[ihist][i_evt];
      }
      for(int ihist = 0; ihist < 2; ihist++){
	dNLL[ihist] -= val[ihist][i_evt]/PROB;
      }
    }

    dNLL[0] += 1.0;
    dNLL[1] += 1.0;

    ret.push_back(dNLL[0]);
    ret.push_back(dNLL[1]);
  }

  if(type >= 0){
    double psi = par1;
    double delta = par2;
    
    double DEN = 0.0;
    
    double C[4];
    
    double INTE[4];
    
    
    if(type == 1 || type == 2 || type == 3){
      
      C[0] = cos(psi)*cos(psi);
      C[1] = cos(psi)*sin(psi);
      C[2] = sin(psi)*sin(psi);
      C[3] = 0.0;
      
      INTE[0] = PDF_INTEGRAL[ihyp][0];
      INTE[1] = PDF_INTEGRAL[ihyp][1];
      INTE[2] = PDF_INTEGRAL[ihyp][2];
      
      DEN = C[0]*PDF_INTEGRAL[ihyp][0]
	+ C[1]*PDF_INTEGRAL[ihyp][1]
	+ C[2]*PDF_INTEGRAL[ihyp][2];
    }
    
    if(type == 4){
      
      C[0] = cos(psi)*cos(psi);
      C[1] = sin(psi)*cos(psi)*cos(delta);
      C[2] = sin(psi)*cos(psi)*sin(delta);
      C[3] = sin(psi)*sin(psi);
      
      INTE[0] = PDF_INTEGRAL[ihyp][0];
      INTE[1] = PDF_INTEGRAL[ihyp][1];
      INTE[2] = PDF_INTEGRAL[ihyp][2];
      INTE[3] = PDF_INTEGRAL[ihyp][3];
      
      DEN = C[0]*PDF_INTEGRAL[ihyp][0]
	+ C[3]*PDF_INTEGRAL[ihyp][3];
    }
    
    double PROB_TOT[2];
    PROB_TOT[0] = 0.0;
    PROB_TOT[1] = 0.0;
    
    for(int i_evt = 0; i_evt < N_evt; i_evt++){
      double PROB = 0.0;
      for(int ihist = 0; ihist < 4; ihist++){
	if(b_H[ihyp][ihist] == true){
	  PROB += C[ihist]*val[ihist][i_evt];
	}
      }
      PROB /= DEN;
      if(PROB <= 0.0) PROB /= -10000.0;
      double fact;
      double fact2 = 0.0;
      if(type == 1 || type == 2 || type == 3){
	//fact = -C[0]*INTE[0]*val[1][i_evt]
	//+ 2.0*C[1]*(INTE[2]*val[0][i_evt]-INTE[0]*val[2][i_evt])
	//+ C[2]*INTE[2]*val[1][i_evt];
	fact = C[0]*(INTE[1]*val[0][i_evt]-INTE[0]*val[1][i_evt])
	  + 2.0*C[1]*(INTE[2]*val[0][i_evt]-INTE[0]*val[2][i_evt])
	  + C[2]*(INTE[2]*val[1][i_evt]-INTE[1]*val[2][i_evt]);
      }
      if(type == 4){
	fact = sin(2.0*psi)*(INTE[3]*val[0][i_evt]-INTE[0]*val[3][i_evt])
	  - C[0]*cos(delta)*INTE[0]*val[1][i_evt]
	  - C[0]*sin(delta)*INTE[0]*val[2][i_evt]
	  + C[3]*cos(delta)*INTE[3]*val[1][i_evt]
	  + C[3]*sin(delta)*INTE[3]*val[2][i_evt];
	fact2 = sin(psi)*cos(psi)*(sin(delta)*val[1][i_evt]-cos(delta)*val[2][i_evt]);
      }
      
      PROB_TOT[0] += fact/PROB;
      PROB_TOT[1] += fact2/PROB;
    }
    PROB_TOT[0] /= (DEN*DEN);
    PROB_TOT[1] /= DEN;
    
    ret.push_back(PROB_TOT[0]);
    ret.push_back(PROB_TOT[1]);
  }

  return ret;
}   

void BuildPDF::mnbrak(double *ax, double *bx, double *cx, int dim){
  double ulim,u,r,q,fu,dum;
  double fa, fb, fc;

  if(dim == 1){
    fa = EvaluateNLL(*ax, 0.0);
    fb = EvaluateNLL(*bx, 0.0);
  } else {
    fa = f1dim(*ax);
    fb = f1dim(*bx);
  }

  if(fb > fa){
    SHFT(dum,*ax,*bx,dum);
    SHFT(dum,fb,fa,dum);
  }
  *cx = (*bx)+GOLD*(*bx-*ax);
  if(dim == 1){
    fc = EvaluateNLL(*cx, 0.0);
  } else {
    fc = f1dim(*cx);
  }
  while(fb > fc){
    r = (*bx-*ax)*(fb-fc);
    q = (*bx-*cx)*(fb-fa);
    u = (*bx)-((*bx-*cx)*q-(*bx-*ax)*r)/
      (2.0*SIGN(max(fabs(q-r),TINY),q-r));
    ulim = (*bx)+GLIMIT*(*cx-*bx);

    if((*bx-u)*(u-*cx) > 0.0){
      if(dim == 1){
	fu = EvaluateNLL(u, 0.0);
      } else {
	fu = f1dim(u);
      }
      if(fu < fc){
	*ax=(*bx);
	*bx=u;
	fa = fb;
	fb = fu;
	return;
      } else if (fu > fb) {
	*cx = u;
	fc = fu;
	return;
      }
      u = (*cx)+GOLD*(*cx-*bx);
      if(dim == 1){
	fu = EvaluateNLL(u, 0.0);
      } else {
	fu = f1dim(u);
      }
    } else if ((*cx-u)*(u-ulim) > 0.0){
      if(dim == 1){
	fu = EvaluateNLL(u, 0.0);
      } else {
	fu = f1dim(u);
      }
      if(fu < fc){
	SHFT(*bx,*cx,u,*cx+GOLD*(*cx-*bx));
	SHFT(fb,fc,fu,EvaluateNLL(u, 0.0));
      }
    } else if ((u-ulim)*(ulim-*cx) >= 0.0){
      u=ulim;
      if(dim == 1){
	fu = EvaluateNLL(u, 0.0);
      } else {
	fu = f1dim(u);
      }
    } else {
      u = (*cx)+GOLD*(*cx-*bx);
      if(dim == 1){
	fu = EvaluateNLL(u, 0.0);
      } else {
	fu = f1dim(u);
      }
    }
    SHFT(*ax,*bx,*cx,u);
    SHFT(fa,fb,fc,fu);
  }
}

double BuildPDF::dbrent(double ax, double bx, double cx, double tol, int dim){
  
  vector<double> der;

  int iter,ok1,ok2;
  double a,b,d,d1,d2,du,dv,dw,dx,e=0.0;
  double fu,fv,fw,fx,olde,tol1,tol2,u,u1,u2,v,w,x,xm,xmin;

  a = (ax < cx ? ax : cx);
  b = (ax > cx ? ax : cx);

  x=w=v=bx;
  if(dim == 1){
    fw=fv=fx=EvaluateNLL(x, 0.0);
    der = EvaluateDerNLL(x, 0.0);
    dw=dv=dx=der[0];
  } else {
    fw=fv=fx=f1dim(x);
    dw=dv=dx=df1dim(x);
  }
  for(iter = 1; iter <= ITMAX; iter++){
    xm = 0.5*(a+b);
    tol1 = tol*fabs(x)+ZEPS;
    tol2=2.0*tol1;
    if(fabs(x-xm) <= (tol2-0.5*(b-a))) {
      xmin = x;
      return xmin;
    }
    if(fabs(e) > tol1){
      d1=2.0*(b-a);
      d2=d1;
      if(dw != dx) d1 = (w-x)*dx/(dx-dw);
      if(dv != dx) d2 = (v-x)*dx/(dx-dv);
      u1=x+d1;
      u2=x+d2;
      ok1 = (a-u1)*(u1-b) > 0.0 && dx*d1 <= 0.0;
      ok2 = (a-u2)*(u2-b) > 0.0 && dx*d2 <= 0.0;
      olde = e;
      e = d; 
      if(ok1 || ok2){
	if(ok1 && ok2)
	  d=(fabs(d1) < fabs(d2) ? d1 : d2);
	else if(ok1)
	  d=d1;
	else 
	  d=d2;
	if(fabs(d) <= fabs(0.5*olde)){
	  u=x+d;
	  if(u-a < tol2 || b-u < tol2)
	    d=SIGN(tol1,xm-x);
	} else {
	  d=0.5*(e=(dx >= 0.0 ? a-x : b-x));
	}
      } else {
	d=0.5*(e=(dx >= 0.0 ? a-x : b-x));
      }
    } else {
      d=0.5*(e=(dx >= 0.0 ? a-x : b-x));
    }
    if(fabs(d) >= tol1){
      u = x+d;
      if(dim == 1){
	fu = EvaluateNLL(u, 0.0);
      } else {
	fu = f1dim(u);
      }
    } else {
      u=x+SIGN(tol1,d);
      if(dim == 1){
	fu = EvaluateNLL(u, 0.0);
      } else {
	fu = f1dim(u);
      }
      if(fu > fx){
	xmin = x;
	return xmin;
      }
    }
    if(dim == 1){
      der = EvaluateDerNLL(u, 0.0);
      du = der[0];
    } else {
      du = df1dim(u);
    }
    if(fu <= fx){
      if(u >= x) a=x; else b=x;
      MOV3(v,fv,dv, w,fw,dw);
      MOV3(w,fw,dw, x,fx,dx);
      MOV3(x,fx,dx, u,fu,du);
    } else {
      if(u < x) a=u; else b=u;
      if(fu <= fw || w == x){
	MOV3(v,fv,dv, w,fw,dw);
	MOV3(w,fw,dw, u,fu,du);
      } else if(fu < fv || v == x || v == w){
	MOV3(v,fv,dv, u,fu,du);
      }
    }
  }
  cout << "ERROR: TOO MANY ITERATIONS IN dbrent!!!" << endl << endl;
  return 0.0;
} 

double BuildPDF::f1dim(double x){
 
  double f, xt[2];
  
  for(int j = 0; j < 2; j++){
    xt[j] = pcom[j]+x*xicom[j];
  }

  f = EvaluateNLL(xt[0],xt[1]);

  return f;
}

double BuildPDF::df1dim(double x){
 
  double df1 = 0.0;
  double xt[2];
  
  for(int j = 0; j < 2; j++){
    xt[j] = pcom[j]+x*xicom[j];
  }

  vector<double> ret = EvaluateDerNLL(xt[0], xt[1]);

  for(int j = 0; j < 2; j++){
    df1 += ret[j]*xicom[j];
  }

  return df1;
}

void BuildPDF::linmin(double p[], double xi[], double *fret){
  int j;
  double xx,xmin,bx,ax;

  for(j = 0; j < 2; j++){
    pcom[j] = p[j];
    xicom[j] = xi[j];
  }

  ax = 0.0;
  xx = 1.0;
  mnbrak(&ax,&xx,&bx,2);

  xmin = dbrent(ax,xx,bx,10e-8,2);
  *fret = f1dim(xmin);
  for(j = 0; j < 2; j++){
    xi[j] *= xmin;
    p[j] += xi[j];
  }

}

void BuildPDF::frprmn(double p[], double ftol){

  vector<double> der;

  int its;
  double gg,gam,fp,dgg, fret;
  double g[2],h[2],xi[2];

  fp = EvaluateNLL(p[0],p[1]);
  der = EvaluateDerNLL(p[0], p[1]);
  xi[0] = der[0];
  xi[1] = der[1];
  for(int j = 0; j < 2; j++){
    g[j] = -xi[j];
    xi[j] = h[j] = g[j];
  }

  for(its=1; its < ITMAX; its++){
    linmin(p,xi,&fret);
    if(2.0*fabs(fret-fp) <= ftol*(fabs(fret)+fabs(fp)+EPS)){
      return;
    }

    fp = fret;
    der = EvaluateDerNLL(p[0], p[1]);
    xi[0] = der[0];
    xi[1] = der[1];
    dgg=gg=0.0;
    for(int j = 0; j < 2; j++){
      gg += g[j]*g[j];
      dgg += (xi[j]+g[j])*xi[j];
    }
    if(gg == 0.0){
      return;
    }
    gam = dgg/gg;
    for(int j = 0; j < 2; j++){
      g[j] = -xi[j];
      xi[j] = h[j] = g[j]+gam*h[j];
    }
  }
}
  

