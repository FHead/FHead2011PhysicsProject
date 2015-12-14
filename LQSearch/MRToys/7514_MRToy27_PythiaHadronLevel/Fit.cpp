#include <iostream>
#include <sstream>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "RooRealVar.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
using namespace std;

int main(int argc, char *argv[])
{
   double R2Cut = 0.5;
   if(argc >= 2)
   {
      stringstream str(argv[1]);
      str >> R2Cut;
   }

   string Option = "4";
   if(argc >= 3)
      Option = argv[2];

   TFile F("LQ150.root");
   TTree *Tree = (TTree *)F.Get("OutputTree");

   RooRealVar MR(Form("MR%s", Option.c_str()), "MR", 300, 999999);
   RooRealVar R(Form("R%s", Option.c_str()), "R", 0, 999999);
   RooArgSet TreeVar(MR, R);

   RooDataSet Data("Data", "Data", Tree, TreeVar,
      Form("MR%s > 300 && R%s > %f", Option.c_str(), Option.c_str(), sqrt(R2Cut)));

   RooRealVar Exp1("Exp1", "Exp1", -0.018, -1.0, 0.0);
   RooExponential Expo1("Expo1", "Expo1", MR, Exp1);

   RooRealVar Exp2("Exp2", "Exp2", -0.007, -1.0, 0.0);
   RooExponential Expo2("Expo2", "Expo2", MR, Exp2);

   RooRealVar Fraction("Fraction", "Fraction", 0.5, 0.0, 1.0);
   RooAddPdf Model("Model", "Model", Expo1, Expo2, Fraction);

   Model.fitTo(Data);
   Model.fitTo(Data);
   Model.fitTo(Data);
   Model.fitTo(Data);
   Model.fitTo(Data);

   cout << "[RESULT] R2 cut = " << R2Cut << endl;
   cout << "[RESULT] Exp1 = " << Exp1.getVal() << " +- " << Exp1.getError() << endl;
   cout << "[RESULT] Exp2 = " << Exp2.getVal() << " +- " << Exp2.getError() << endl;
   cout << "[RESULT] Fraction = " << Fraction.getVal() << " +- " << Fraction.getError() << endl;

   cout << "[RESULTEXP1] " << R2Cut << " " << Exp1.getVal() << " " << Exp1.getError() << endl;
   cout << "[RESULTEXP2] " << R2Cut << " " << Exp2.getVal() << " " << Exp2.getError() << endl;
   cout << "[RESULTFRACTION] " << R2Cut << " " << Fraction.getVal() << " " << Fraction.getError() << endl;

   return 0;
}


