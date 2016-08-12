//---------------------------------------------------------------------------
#ifndef INTERPRETCOEFFICIENT_H_13657_AJSODGJAKSDJGKASJGKASDJGKADSJG
#define INTERPRETCOEFFICIENT_H_13657_AJSODGJAKSDJGKASJGKASDJGKADSJG
//---------------------------------------------------------------------------
class InterpretationCoefficients
{
public:
   double mh;
   double mw;
   double mt;
   double yt;
   double yta;
   double c3;
   double c4;
   double gww;
   double rho;
   double gv;
public:
   InterpretationCoefficients();
   void Print();
};
//---------------------------------------------------------------------------
// Toy functions to setup stuff
double InterpretedA2ZZ_Toy(const InterpretationCoefficients &c);
double InterpretedA3ZZ_Toy(const InterpretationCoefficients &c);
double InterpretedA4ZZ_Toy(const InterpretationCoefficients &c);
double InterpretedA2ZA_Toy(const InterpretationCoefficients &c);
double InterpretedA3ZA_Toy(const InterpretationCoefficients &c);
double InterpretedA2AA_Toy(const InterpretationCoefficients &c);
double InterpretedA3AA_Toy(const InterpretationCoefficients &c);
//---------------------------------------------------------------------------
// Top loop coefficients from Roberto with constant W loop values (1)3664
double InterpretedA2ZA_Roberto13364(const InterpretationCoefficients &c);
double InterpretedA3ZA_Roberto13364(const InterpretationCoefficients &c);
double InterpretedA2AA_Roberto13364(const InterpretationCoefficients &c);
double InterpretedA3AA_Roberto13364(const InterpretationCoefficients &c);
double acsc(double x);
//---------------------------------------------------------------------------
// Top loop and W loop coefficients for AA from Roberto (1)3666
double InterpretedA2AA_Roberto13366(const InterpretationCoefficients &c);
double InterpretedA3AA_Roberto13366(const InterpretationCoefficients &c);
double InterpretedA2AA_Top_Roberto13366(const InterpretationCoefficients &c);
double InterpretedA3AA_Top_Roberto13366(const InterpretationCoefficients &c);
double InterpretedA2AA_W_Roberto13366(const InterpretationCoefficients &c);
double InterpretedA3AA_W_Roberto13366(const InterpretationCoefficients &c);
//---------------------------------------------------------------------------
// Top loop and W loop coefficients for AA and ZA from Roberto (1)3711
double InterpretedA2ZA_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA3ZA_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA2AA_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA3AA_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA2ZA_Top_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA3ZA_Top_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA2ZA_W_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA3ZA_W_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA2AA_Top_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA3AA_Top_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA2AA_W_Roberto13711(const InterpretationCoefficients &c);
double InterpretedA3AA_W_Roberto13711(const InterpretationCoefficients &c);
//---------------------------------------------------------------------------
// Updated top loop coefficients for AA and ZA from Roberto (1)4167
double InterpretedA2ZA_Roberto14167(const InterpretationCoefficients &c);
double InterpretedA3ZA_Roberto14167(const InterpretationCoefficients &c);
double InterpretedA2AA_Roberto14167(const InterpretationCoefficients &c);
double InterpretedA3AA_Roberto14167(const InterpretationCoefficients &c);
double InterpretedA3ZA_Top_Roberto14167(const InterpretationCoefficients &c);
double InterpretedA3AA_Top_Roberto14167(const InterpretationCoefficients &c);
//---------------------------------------------------------------------------
// Updated ZA sign problem (1)5352
double InterpretedA2ZA_Roberto15352(const InterpretationCoefficients &c);
double InterpretedA3ZA_Roberto15352(const InterpretationCoefficients &c);
double InterpretedA2AA_Roberto15352(const InterpretationCoefficients &c);
double InterpretedA3AA_Roberto15352(const InterpretationCoefficients &c);
double InterpretedA2ZA_Top_Roberto15352(const InterpretationCoefficients &c);
double InterpretedA3ZA_Top_Roberto15352(const InterpretationCoefficients &c);
double InterpretedA2ZA_W_Roberto15352(const InterpretationCoefficients &c);
double InterpretedA3ZA_W_Roberto15352(const InterpretationCoefficients &c);
//---------------------------------------------------------------------------
#endif

