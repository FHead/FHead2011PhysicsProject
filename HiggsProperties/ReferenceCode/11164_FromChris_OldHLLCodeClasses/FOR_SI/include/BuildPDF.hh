#ifndef BuildPDF_HH
#define BuildPDF_HH
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <algorithm>
#include <numeric>
#include <list>

using namespace std;

class BuildPDF {
public:
  BuildPDF(int _type0, int _type1, int mass, char* dir_name);
  ~BuildPDF();

  void InitBKG();
  void InitSIG_GEN(int s_MASS);
  void InitSIG_EVAL(int s_MASS);
  void InitHYP(int ihyp, int type);
  void InitParam(char* filename);
  void InitHisto_SB();
  void InitHisto(int ihyp);
  void FillHisto(int ihyp, int ihist, double sign, char *filename);
  void FillHisto_BKG(char *filename);
  void CleanUp();
  void GenerateMODEL(int ihyp, double par1, double par2);
  void GenerateEvents(int N_evt);
  void GenerateEvents(int N_sig, int N_bkg);
  void InitEval(int ihyp);
  void InitEval();
  double EvaluateNLL(double par1, double par2);
  vector<double> EvaluateDerNLL(double par1, double par2);

  vector<double> MeasurePar(int ihyp);

  void mnbrak(double *ax, double *bx, double *cx, int dim);
  double dbrent(double ax, double bx, double cx, double tol, int dim);
  double f1dim(double x);
  double df1dim(double x);
  void linmin(double p[], double xi[], double *fret);
  void frprmn(double p[], double ftol);

protected:
  void Init(int _type0, int _type1, int mass, char* dir_name);
  
  double _mZ;

  bool b_H[3][4]; //first index H0/H1/MODEL, second PDF comp.

  bool b_BKG[2];
  bool b_SIG[2];
  bool b_SB;

  bool SB_OPT;

  double PDF_INTEGRAL[3][4];

  int MASS;
  char *DIR_NAME;
  
  int MASS_GEN;
  int MASS_EVAL;

  int TYPE0;
  int TYPE1;

  int eval_hyp;
  int eval_type;

  int NEVT;

  double M[15000];
  double cosTHETA[15000];
  double PHI[15000];
  double c1[15000];
  double c2[15000];
  double phi[15000];

  //0 is BKG, 1 is SIG for that exercise
  double val[4][15000];

  bool b_got_param;

  //Parameters
  int N_M;
  int N_cosTHETA;
  int N_PHI;
  int N_c1;
  int N_c2;
  int N_phi;

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

  TBranch *b_N_M;
  TBranch *b_N_cosTHETA;
  TBranch *b_N_PHI;
  TBranch *b_N_c1;
  TBranch *b_N_c2;
  TBranch *b_N_phi;

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

  //
  //Here are the histograms
  //First index is the hypothesis
  //Second is the PDF component number
  //
  TH1D* h_mZstar[3][4];
  TH2D* h_ANGLES[3][4][20];
  TH3D* h_angles[3][4][20][20][20];

  TH1D* h_mH_BKG[2];
  TH2D* h_ANGLES_BKG[2][600];
  TH3D* h_angles_BKG[2][600][20][20];

  TH1D* h_mH_SIG[2];
  TH2D* h_ANGLES_SIG[2];
  TH3D* h_angles_SIG[2][20][20];

  //Some stuff for 2D minimization
  double pcom[2];
  double xicom[2];

};
#endif
