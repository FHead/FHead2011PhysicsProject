
double GetGeneralScalar_aAI_aAI(LeptonVectors &leptons, double aAI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.+0;
}

double GetGeneralScalar_aAI_aAR(LeptonVectors &leptons, double aAI, double aAR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI)+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI)-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAI*aAI)+(aAR*aAR))*(C35*C35)+((aAI*aAI)+(aAR*aAR))*(C36*C36)+((aAI*aAI)+(aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI)-(aAR*aAR))*C36*C45+2*(-(aAI*aAI)-(aAR*aAR))*C35*C46)*C56))/4096.+0;
}

double GetGeneralScalar_aAI_aAdI(LeptonVectors &leptons, double aAI, double aAdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI)+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(-2*(aAdI*aAI)*E3456+((aAdI*aAdI)-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI)+(aAI*aAI))*(C35*C35)+((aAdI*aAdI)+(aAI*aAI))*(C36*C36)+((aAdI*aAdI)+(aAI*aAI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI)-(aAI*aAI))*C36*C45+2*((aAdI*aAdI)-(aAI*aAI))*C35*C46)*C56))/4096.+0;
}

double GetGeneralScalar_aAI_aAdR(LeptonVectors &leptons, double aAI, double aAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR)+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR)-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR)+(aAI*aAI))*(C35*C35)+((aAdR*aAdR)+(aAI*aAI))*(C36*C36)+((aAdR*aAdR)+(aAI*aAI))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR)-(aAI*aAI))*C36*C45+2*((aAdR*aAdR)-(aAI*aAI))*C35*C46)*C56))/4096.-0;
}

double GetGeneralScalar_aAI_aZAI(LeptonVectors &leptons, double aAI, double aZAI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+8*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+8*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(gL+gR)*(-2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(-aAI*aZAI)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C34*C34)*(C56*C56)+C34*((2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+((-aAI)*(-aZAI)*gL+(aAI)*(aZAI)*gR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C35*C35)+(2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(aAI*aZAI*gL*(M1*M1*M1*M1)+aAI*aZAI*gR*(M1*M1*M1*M1)+aAI*aZAI*gL*(M2*M2*M2*M2)+aAI*aZAI*gR*(M2*M2*M2*M2)-(((aAI)*(aZAI)*gL+(-aAI)*(-aZAI)*gR)*(M1*M1)+((-aAI)*(-aZAI)*gL+(aAI)*(aZAI)*gR)*(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C45*C45)+(2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+((-aAI)*(aZAI)*gL-(-aAI)*(-aZAI)*gR)*(MZ*MZ)*(-(M1*M1*M1*M1)-(M2*M2*M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C46*C46)+2*(gL+gR)*(-2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(-aAI*aZAI)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*C35*C46)*C56+2*(gL+gR)*(-2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(-aAI*aZAI)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*C36*C45*(2*C35*C46+C34*C56)+(C36*C36)*(-2*(gL+gR)*(-2*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(-aAI*aZAI)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C45*C45)+(2*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAI*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAI*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAI*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAI*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAI*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(aAI*aZAI*gL*(M1*M1*M1*M1)+aAI*aZAI*gR*(M1*M1*M1*M1)+aAI*aZAI*gL*(M2*M2*M2*M2)+aAI*aZAI*gR*(M2*M2*M2*M2)-(((-aAI)*(-aZAI)*gL+(aAI)*(aZAI)*gR)*(M1*M1)+((aAI)*(aZAI)*gL+(-aAI)*(-aZAI)*gR)*(M2*M2))*(MZ*MZ))*(wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAI_aZAR(LeptonVectors &leptons, double aAI, double aZAR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-2*aAI*aZAR*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+8*aAI*aZAR*gL*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*(C46*C46)+8*aAI*aZAR*gR*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)-2*aAI*aZAR*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)-2*(gL+gR)*((aAI*aZAR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(aAI*aZAR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C34*C34)*(C56*C56)+C34*(((((-aAI)*(aZAR))*gL+((aAI)*(-aZAR))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(((-aAI)*(aZAR))*gL+((aAI)*(-aZAR))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C35*C35)+(MZ*wZ*(aAI*(-aZAR*(gL+gR)*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))))+((((aAI)*(-aZAR))*gL+((-aAI)*(aZAR))*gR)*(M1*M1)+(((-aAI)*(aZAR))*gL+((aAI)*(-aZAR))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45)+((((aAI)*(-aZAR))*gL+((-aAI)*(aZAR))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(((aAI)*(-aZAR))*gL+((-aAI)*(aZAR))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C46*C46)+2*(gL+gR)*((aAI*aZAR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(aAI*aZAR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C35*C46)*C56+2*(gL+gR)*((aAI*aZAR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(aAI*aZAR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C36*C45*(2*C35*C46+C34*C56)+(C36*C36)*(-2*(gL+gR)*((aAI*aZAR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(aAI*aZAR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45)+(MZ*wZ*(aAI*(-aZAR*(gL+gR)*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))))+((((-aAI)*(aZAR))*gL+((aAI)*(-aZAR))*gR)*(M1*M1)+(((aAI)*(-aZAR))*gL+((-aAI)*(aZAR))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAI_aZAdI(LeptonVectors &leptons, double aAI, double aZAdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*(gL+gR)*E3456*(2*aAI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAI*aZAdI)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C36*C45-C35*C46)+C34*(((((-aAI)*(aZAdI))*gL+((aAI)*(aZAdI))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(((-aAI)*(aZAdI))*gL+((aAI)*(aZAdI))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C35*C35)+(MZ*wZ*(aAI*(-(aZAdI*(gL-gR)*(M1-M2)*(M1+M2)*(M1*M2-(MZ*MZ))*(M1*M2+(MZ*MZ)))))+((((aAI)*(aZAdI))*gL+((-aAI)*(aZAdI))*gR)*(M1*M1)+(((-aAI)*(aZAdI))*gL+((aAI)*(aZAdI))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45)+((((aAI)*(aZAdI))*gL+((-aAI)*(aZAdI))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(((aAI)*(aZAdI))*gL+((-aAI)*(aZAdI))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C46*C46))*C56+(C36*C36)*((MZ*wZ*(aAI*(aZAdI*(gL-gR)*(M1-M2)*(M1+M2)*(M1*M2-(MZ*MZ))*(M1*M2+(MZ*MZ))))+((((-aAI)*(aZAdI))*gL+((aAI)*(aZAdI))*gR)*(M1*M1)+(((aAI)*(aZAdI))*gL+((-aAI)*(aZAdI))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAI_aZAdR(LeptonVectors &leptons, double aAI, double aZAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*(gL+gR)*E3456*((-aAI*aZAdR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(-aAI*aZAdR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C36*C45-C35*C46)+C34*((-2*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAI*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAI*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+((-aAI)*(aZAdR)*gL+(aAI)*(aZAdR)*gR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C35*C35)+(-aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(aAI*aZAdR*gL*(M1*M1*M1*M1)-aAI*aZAdR*gR*(M1*M1*M1*M1)-aAI*aZAdR*gL*(M2*M2*M2*M2)+aAI*aZAdR*gR*(M2*M2*M2*M2)-(((aAI)*(aZAdR)*gL+(-aAI)*(aZAdR)*gR)*(M1*M1)+((-aAI)*(aZAdR)*gL+(aAI)*(aZAdR)*gR)*(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C45*C45)+(2*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)-2*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+3*aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAI*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-4*aAI*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+((-aAI)*(aZAdR)*gL-(-aAI)*(aZAdR)*gR)*(MZ*MZ)*(-(M1*M1*M1*M1)-(M2*M2*M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C46*C46))*C56+(C36*C36)*((aAI*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-aAI*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-aAI*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAI*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAI*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAI*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAI*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAI*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(-aAI*aZAdR*gL*(M1*M1*M1*M1)+aAI*aZAdR*gR*(M1*M1*M1*M1)+aAI*aZAdR*gL*(M2*M2*M2*M2)-aAI*aZAdR*gR*(M2*M2*M2*M2)-(((-aAI)*(aZAdR)*gL+(aAI)*(aZAdR)*gR)*(M1*M1)+((aAI)*(aZAdR)*gL+(-aAI)*(aZAdR)*gR)*(M2*M2))*(MZ*MZ))*(wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAI_aZI(LeptonVectors &leptons, double aAI, double aZI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*aAI*aZI*gL*gR*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-2*aAI*aZI*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-2*aAI*aZI*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+4*aAI*aZI*gL*gR*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aAI*aZI*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aAI*aZI*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+4*aAI*aZI*gL*gR*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aAI*aZI*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aAI*aZI*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-4*aAI*aZI*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)-2*aAI*aZI*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)-2*aAI*aZI*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)+4*aAI*aZI*gL*gR*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)+2*aAI*aZI*(gL*gL)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)+2*aAI*aZI*(gR*gR)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)-2*((gL+gR)*(gL+gR))*((+aAI*aZI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(-aAI*aZI)*(MZ*MZ)*(wZ*wZ))*(C34*C34)*(C56*C56)+C34*(-4*gL*gR*((aAI*aZI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAI*aZI)*(MZ*MZ)*(wZ*wZ))*(C36*C36)-4*gL*gR*((aAI*aZI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAI*aZI)*(MZ*MZ)*(wZ*wZ))*(C45*C45)-2*C36*(-2*((gL*gL)+(gR*gR))*((+aAI*aZI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(-aAI*aZI)*(MZ*MZ)*(wZ*wZ))*C45)+C46*(2*(aAI*((M1-MZ)*(M1+MZ)*((aZI)*(gL*gL)+(aZI)*(gR*gR))*(-(M2*M2)+(MZ*MZ))+((aZI)*(gL*gL)+(aZI)*(gR*gR))*(MZ*MZ)*(wZ*wZ)))*C46))*C56+(C35*C35)*(-2*((gL+gR)*(gL+gR))*((+aAI*aZI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(-aAI*aZI)*(MZ*MZ)*(wZ*wZ))*(C46*C46)+2*(aAI*((M1-MZ)*(M1+MZ)*((aZI)*(gL*gL)+(aZI)*(gR*gR))*(-(M2*M2)+(MZ*MZ))+((aZI)*(gL*gL)+(aZI)*(gR*gR))*(MZ*MZ)*(wZ*wZ)))*C34*C56)+C35*(-C36*(C45*(-4*((gL+gR)*(gL+gR))*((+aAI*aZI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(-aAI*aZI)*(MZ*MZ)*(wZ*wZ))*C46))+C34*(8*gL*gR*((+aAI*aZI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(-aAI*aZI)*(MZ*MZ)*(wZ*wZ))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI))*C45)+C35*(4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAI_aZR(LeptonVectors &leptons, double aAI, double aZR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*aAI*aZR*gL*gR*MZ*wZ*(M1*M1)*(C36*C36)*(C45*C45)+2*aAI*aZR*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)+2*aAI*aZR*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)+4*aAI*aZR*gL*gR*MZ*wZ*(M2*M2)*(C36*C36)*(C45*C45)+2*aAI*aZR*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)+2*aAI*aZR*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)-8*aAI*aZR*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)-4*aAI*aZR*wZ*(gL*gL)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)-4*aAI*aZR*wZ*(gR*gR)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)-2*((gL+gR)*(gL+gR))*((-aAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C34*C34)*(C56*C56)+C34*(-4*gL*gR*((-aAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C36*C36)-4*gL*gR*((-aAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C45*C45)-2*C36*(-2*((gL*gL)+(gR*gR))*((-aAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45)+C46*(2*(aAI*(MZ*wZ*((aZR)*(gL*gL)+(aZR)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C46))*C56+(C35*C35)*(-2*((gL+gR)*(gL+gR))*((-aAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C46*C46)+2*(aAI*(MZ*wZ*((aZR)*(gL*gL)+(aZR)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C34*C56)+C35*(-C36*(C45*(-4*((gL+gR)*(gL+gR))*((-aAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46))+C34*(8*gL*gR*((-aAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZR*aZR))*C45)+C35*(4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAI_aZdI(LeptonVectors &leptons, double aAI, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(C46*(2*(aAI*(MZ*wZ*((-aZdI)*(gL*gL)+(aZdI)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C46))*C56+E3456*(-2*C36*(((gL+gR)*(gL+gR))*((aAI*aZdI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAI*aZdI)*(MZ*MZ)*(wZ*wZ))*C45)+C35*(2*((gL+gR)*(gL+gR))*((aAI*aZdI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAI*aZdI)*(MZ*MZ)*(wZ*wZ))*C46)+2*((gL-gR)*(gL-gR))*((aAI*aZdI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAI*aZdI)*(MZ*MZ)*(wZ*wZ))*C34*C56)+(C35*C35)*(2*(aAI*(MZ*wZ*((aZdI)*(gL*gL)+(-aZdI)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+C35*(4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAI_aZdR(LeptonVectors &leptons, double aAI, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(C46*(2*(aAI*((M1-MZ)*(M1+MZ)*((aZdR)*(gL*gL)+(-aZdR)*(gR*gR))*(-(M2*M2)+(MZ*MZ))+((aZdR)*(gL*gL)+(-aZdR)*(gR*gR))*(MZ*MZ)*(wZ*wZ)))*C46))*C56+E3456*(-2*C36*(((gL+gR)*(gL+gR))*((-aAI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45)+C35*(2*((gL+gR)*(gL+gR))*((-aAI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46)+2*((gL-gR)*(gL-gR))*((-aAI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C34*C56)+(C35*C35)*(2*(aAI*((M1-MZ)*(M1+MZ)*((-aZdR)*(gL*gL)+(aZdR)*(gR*gR))*(-(M2*M2)+(MZ*MZ))+((-aZdR)*(gL*gL)+(aZdR)*(gR*gR))*(MZ*MZ)*(wZ*wZ)))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+C35*(4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAI_ahI(LeptonVectors &leptons, double aAI, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-2*aAI*ahI*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*C36+2*aAI*ahI*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+2*aAI*ahI*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36-2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36+2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C45*C45)*C36-2*aAI*ahI*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*C45+2*aAI*ahI*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+2*aAI*ahI*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45-2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45+2*aAI*ahI*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C36*C36)*C45+aAI*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46+aAI*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46-aAI*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-aAI*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-aAI*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46-aAI*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46+aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46+aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46-aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46-aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46+C34*(-2*gL*gR*(MZ*MZ)*((aAI*ahI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAI*ahI)*(MZ*MZ)*(wZ*wZ))*C45-2*C36*(gL*gR*(MZ*MZ)*((aAI*ahI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAI*ahI)*(MZ*MZ)*(wZ*wZ)))+C46*((MZ*MZ)*(aAI*((gL*gL)+(gR*gR))*(ahI*(M1-MZ)*(M1+MZ)*(-(M2*M2)+(MZ*MZ))+ahI*(MZ*MZ)*(wZ*wZ)))))*C56+E3456*(aAI*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46-0-aAI*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46+aAI*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46-0-aAI*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46-0-2*aAI*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46+2*aAI*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46+C35*((MZ*MZ)*(((-aAI)*(gL*gL)+(aAI)*(gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))+(C35*C35)*((MZ*MZ)*(aAI*((gL*gL)+(gR*gR))*(ahI*(M1-MZ)*(M1+MZ)*(-(M2*M2)+(MZ*MZ))+ahI*(MZ*MZ)*(wZ*wZ)))*C46)+C35*(-aAI*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)-aAI*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)+aAI*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)+aAI*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)+aAI*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)+aAI*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)-aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46)-aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46)+aAI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46)+aAI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46)+2*gL*gR*(MZ*MZ)*((aAI*ahI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAI*ahI)*(MZ*MZ)*(wZ*wZ))*C45*C46-C36*(-2*gL*gR*(MZ*MZ)*((aAI*ahI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAI*ahI)*(MZ*MZ)*(wZ*wZ))*C46+C45*((MZ*MZ)*(aAI*((gL*gL)+(gR*gR))*(ahI*(M1-MZ)*(M1+MZ)*(-(M2*M2)+(MZ*MZ))+ahI*(MZ*MZ)*(wZ*wZ)))))+C34*((MZ*MZ)*(aAI*((gL*gL)+(gR*gR))*(ahI*(M1-MZ)*(M1+MZ)*(-(M2*M2)+(MZ*MZ))+ahI*(MZ*MZ)*(wZ*wZ))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aAI_ahR(LeptonVectors &leptons, double aAI, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAI*aAI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAI*aAI))*(C36*C45-C35*C46))+C34*(((aAI*aAI))*(C35*C35)+((aAI*aAI))*(C36*C36)+((aAI*aAI))*((C45*C45)+(C46*C46))+2*(-(aAI*aAI))*C36*C45+2*(-(aAI*aAI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*aAI*ahR*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36+2*aAI*ahR*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36-4*aAI*ahR*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36+2*aAI*ahR*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45+2*aAI*ahR*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45-4*aAI*ahR*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45-0-aAI*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46-aAI*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46-0-aAI*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46-aAI*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+2*aAI*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*C46+2*aAI*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*C46+C34*(-2*gL*gR*(MZ*MZ)*((-aAI*ahR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45-2*C36*(gL*gR*(MZ*MZ)*((-aAI*ahR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))+C46*((MZ*MZ)*(aAI*((gL*gL)+(gR*gR))*(ahR*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))*C56+E3456*(aAI*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46-aAI*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46-aAI*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46+aAI*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-0-aAI*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46+aAI*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46+aAI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46-aAI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46-0-aAI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46+aAI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46+C35*((MZ*MZ)*(((-aAI)*(gL*gL)+(aAI)*(gR*gR))*(ahR*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahR*(MZ*MZ)*(wZ*wZ)))))+(C35*C35)*((MZ*MZ)*(aAI*((gL*gL)+(gR*gR))*(ahR*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C46)+C35*(aAI*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)+aAI*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)+aAI*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)+aAI*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)-2*aAI*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46)-2*aAI*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46)+2*gL*gR*(MZ*MZ)*((-aAI*ahR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45*C46-C36*(-2*gL*gR*(MZ*MZ)*((-aAI*ahR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46+C45*((MZ*MZ)*(aAI*((gL*gL)+(gR*gR))*(ahR*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))+C34*((MZ*MZ)*(aAI*((gL*gL)+(gR*gR))*(ahR*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aAR_aAR(LeptonVectors &leptons, double aAR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.+0;
}

double GetGeneralScalar_aAR_aAdI(LeptonVectors &leptons, double aAR, double aAdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI)+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI)-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI)+(aAR*aAR))*(C35*C35)+((aAdI*aAdI)+(aAR*aAR))*(C36*C36)+((aAdI*aAdI)+(aAR*aAR))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI)-(aAR*aAR))*C36*C45+2*((aAdI*aAdI)-(aAR*aAR))*C35*C46)*C56))/4096.+0;
}

double GetGeneralScalar_aAR_aAdR(LeptonVectors &leptons, double aAR, double aAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR)+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(-2*(aAdR*aAR)*E3456+((aAdR*aAdR)-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR)+(aAR*aAR))*(C35*C35)+((aAdR*aAdR)+(aAR*aAR))*(C36*C36)+((aAdR*aAdR)+(aAR*aAR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR)-(aAR*aAR))*C36*C45+2*((aAdR*aAdR)-(aAR*aAR))*C35*C46)*C56))/4096.-0;
}

double GetGeneralScalar_aAR_aZAI(LeptonVectors &leptons, double aAR, double aZAI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*aAR*aZAI*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-8*aAR*aZAI*gL*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*(C46*C46)-8*aAR*aZAI*gR*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)+2*aAR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)-2*(gL+gR)*((-aAR*aZAI)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(-aAR*aZAI)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C34*C34)*(C56*C56)+C34*((((aAR*(aZAI))*gL+(aAR*(aZAI))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+((aAR*(aZAI))*gL+(aAR*(aZAI))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C35*C35)+(MZ*wZ*(aAR*(aZAI*(gL+gR)*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))))+(((aAR*(aZAI))*gL+(aAR*(aZAI))*gR)*(M1*M1)+((aAR*(aZAI))*gL+(aAR*(aZAI))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45)+(((aAR*(aZAI))*gL+(aAR*(aZAI))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+((aAR*(aZAI))*gL+(aAR*(aZAI))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C46*C46)+2*(gL+gR)*((-aAR*aZAI)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(-aAR*aZAI)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C35*C46)*C56+2*(gL+gR)*((-aAR*aZAI)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(-aAR*aZAI)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C36*C45*(2*C35*C46+C34*C56)+(C36*C36)*(-2*(gL+gR)*((-aAR*aZAI)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(-aAR*aZAI)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45)+(MZ*wZ*(aAR*(aZAI*(gL+gR)*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))))+(((aAR*(aZAI))*gL+(aAR*(aZAI))*gR)*(M1*M1)+((aAR*(aZAI))*gL+(aAR*(aZAI))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAR_aZAR(LeptonVectors &leptons, double aAR, double aZAR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+8*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+8*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(gL+gR)*(-2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(-aAR*aZAR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C34*C34)*(C56*C56)+C34*((2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAR*(aZAR*(gL+gR)))*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C35*C35)+(2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(aAR*(aZAR*(gL+gR)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))))*(wZ*wZ))*(C45*C45)+(2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAR*(-aZAR)*gL-0-aAR*(aZAR)*gR)*(MZ*MZ)*(-(M1*M1*M1*M1)-(M2*M2*M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C46*C46)+2*(gL+gR)*(-2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(-aAR*aZAR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*C35*C46)*C56+2*(gL+gR)*(-2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(-aAR*aZAR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*C36*C45*(2*C35*C46+C34*C56)+(C36*C36)*(-2*(gL+gR)*(-2*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(-aAR*aZAR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C45*C45)+(2*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAR*aZAR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAR*aZAR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAR*aZAR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAR*aZAR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAR*aZAR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(aAR*(aZAR*(gL+gR)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))))*(wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAR_aZAdI(LeptonVectors &leptons, double aAR, double aZAdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*(gL+gR)*E3456*((aAR*aZAdI)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(aAR*aZAdI)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C36*C45-C35*C46)+C34*((2*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)-2*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+3*aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAR*aZAdI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-4*aAR*aZAdI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAR*(aZAdI*(gL-gR)))*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C35*C35)+(aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(aAR*(-(aZAdI*(gL-gR)*(M1-M2)*(M1+M2)*((M1*M1)+(M2*M2)-(MZ*MZ)))))*(wZ*wZ))*(C45*C45)+(-2*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAR*aZAdI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAR*aZAdI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAR*(aZAdI)*gL-0-aAR*(aZAdI)*gR)*(MZ*MZ)*(-(M1*M1*M1*M1)-(M2*M2*M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C46*C46))*C56+(C36*C36)*((-aAR*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+aAR*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+aAR*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAR*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAR*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-aAR*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-aAR*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(aAR*(aZAdI*(gL-gR)*(M1-M2)*(M1+M2)*((M1*M1)+(M2*M2)-(MZ*MZ))))*(wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAR_aZAdR(LeptonVectors &leptons, double aAR, double aZAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*(gL+gR)*E3456*(2*aAR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAR*aZAdR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C36*C45-C35*C46)+C34*((((aAR*(-aZAdR))*gL+(aAR*(aZAdR))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+((aAR*(-aZAdR))*gL+(aAR*(aZAdR))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C35*C35)+(MZ*wZ*(aAR*(-(aZAdR*(gL-gR)*(M1-M2)*(M1+M2)*(M1*M2-(MZ*MZ))*(M1*M2+(MZ*MZ)))))+(((aAR*(aZAdR))*gL+(aAR*(-aZAdR))*gR)*(M1*M1)+((aAR*(-aZAdR))*gL+(aAR*(aZAdR))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45)+(((aAR*(aZAdR))*gL+(aAR*(-aZAdR))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+((aAR*(aZAdR))*gL+(aAR*(-aZAdR))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C46*C46))*C56+(C36*C36)*((MZ*wZ*(aAR*(aZAdR*(gL-gR)*(M1-M2)*(M1+M2)*(M1*M2-(MZ*MZ))*(M1*M2+(MZ*MZ))))+(((aAR*(-aZAdR))*gL+(aAR*(aZAdR))*gR)*(M1*M1)+((aAR*(aZAdR))*gL+(aAR*(-aZAdR))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAR_aZI(LeptonVectors &leptons, double aAR, double aZI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*aAR*aZI*gL*gR*MZ*wZ*(M1*M1)*(C36*C36)*(C45*C45)-2*aAR*aZI*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)-2*aAR*aZI*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)-4*aAR*aZI*gL*gR*MZ*wZ*(M2*M2)*(C36*C36)*(C45*C45)-2*aAR*aZI*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)-2*aAR*aZI*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)+8*aAR*aZI*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)+4*aAR*aZI*wZ*(gL*gL)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)+4*aAR*aZI*wZ*(gR*gR)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)-2*((gL+gR)*(gL+gR))*((aAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C34*C34)*(C56*C56)+C34*(-4*gL*gR*((aAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C36*C36)-4*gL*gR*((aAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C45*C45)-2*C36*(-2*((gL*gL)+(gR*gR))*((aAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45)+C46*(2*(MZ*wZ*((-aAR)*(aZI)*(gL*gL)-(aAR)*(aZI)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46))*C56+(C35*C35)*(-2*((gL+gR)*(gL+gR))*((aAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C46*C46)+2*(-MZ*wZ*((aAR)*(aZI)*(gL*gL)-(-aAR)*(aZI)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C34*C56)+C35*(-C36*(C45*(-4*((gL+gR)*(gL+gR))*((aAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46))+C34*(8*gL*gR*((aAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI))*C45)+C35*(4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAR_aZR(LeptonVectors &leptons, double aAR, double aZR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*aAR*aZR*gL*gR*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-2*aAR*aZR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-2*aAR*aZR*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+4*aAR*aZR*gL*gR*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aAR*aZR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aAR*aZR*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+4*aAR*aZR*gL*gR*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aAR*aZR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aAR*aZR*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-4*aAR*aZR*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)-2*aAR*aZR*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)-2*aAR*aZR*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)+4*aAR*aZR*gL*gR*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)+2*aAR*aZR*(gL*gL)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)+2*aAR*aZR*(gR*gR)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)-2*((gL+gR)*(gL+gR))*((+aAR*aZR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(-aAR*aZR)*(MZ*MZ)*(wZ*wZ))*(C34*C34)*(C56*C56)+C34*(-4*gL*gR*((aAR*aZR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAR*aZR)*(MZ*MZ)*(wZ*wZ))*(C36*C36)-4*gL*gR*((aAR*aZR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAR*aZR)*(MZ*MZ)*(wZ*wZ))*(C45*C45)-2*C36*(-2*((gL*gL)+(gR*gR))*((+aAR*aZR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(-aAR*aZR)*(MZ*MZ)*(wZ*wZ))*C45)+C46*(2*(-aAR*aZR*(gL*gL)*(M1*M1)*(M2*M2)-aAR*aZR*(gR*gR)*(M1*M1)*(M2*M2)+aAR*aZR*(gL*gL)*(M1*M1)*(MZ*MZ)+aAR*aZR*(gR*gR)*(M1*M1)*(MZ*MZ)+aAR*aZR*(gL*gL)*(M2*M2)*(MZ*MZ)+aAR*aZR*(gR*gR)*(M2*M2)*(MZ*MZ)-aAR*aZR*(gL*gL)*(MZ*MZ*MZ*MZ)-aAR*aZR*(gR*gR)*(MZ*MZ*MZ*MZ)+((aAR)*(aZR)*(gL*gL)+(aAR)*(aZR)*(gR*gR))*(MZ*MZ)*(wZ*wZ))*C46))*C56+(C35*C35)*(-2*((gL+gR)*(gL+gR))*((+aAR*aZR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(-aAR*aZR)*(MZ*MZ)*(wZ*wZ))*(C46*C46)+2*(-aAR*aZR*(gL*gL)*(M1*M1)*(M2*M2)-aAR*aZR*(gR*gR)*(M1*M1)*(M2*M2)+aAR*aZR*(gL*gL)*(M1*M1)*(MZ*MZ)+aAR*aZR*(gR*gR)*(M1*M1)*(MZ*MZ)+aAR*aZR*(gL*gL)*(M2*M2)*(MZ*MZ)+aAR*aZR*(gR*gR)*(M2*M2)*(MZ*MZ)-aAR*aZR*(gL*gL)*(MZ*MZ*MZ*MZ)-aAR*aZR*(gR*gR)*(MZ*MZ*MZ*MZ)+((aAR)*(aZR)*(gL*gL)-(-aAR)*(aZR)*(gR*gR))*(MZ*MZ)*(wZ*wZ))*C34*C56)+C35*(-C36*(C45*(-4*((gL+gR)*(gL+gR))*((+aAR*aZR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(-aAR*aZR)*(MZ*MZ)*(wZ*wZ))*C46))+C34*(8*gL*gR*((+aAR*aZR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(-aAR*aZR)*(MZ*MZ)*(wZ*wZ))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZR*aZR))*C45)+C35*(4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAR_aZdI(LeptonVectors &leptons, double aAR, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(C46*(2*(aAR*aZdI*(gL*gL)*(M1*M1)*(M2*M2)-aAR*aZdI*(gR*gR)*(M1*M1)*(M2*M2)-aAR*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ)+aAR*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ)-aAR*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ)+aAR*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ)+aAR*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ)-aAR*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ)+((aAR)*(-aZdI)*(gL*gL)+(aAR)*(aZdI)*(gR*gR))*(MZ*MZ)*(wZ*wZ))*C46))*C56+E3456*(-2*C36*(((gL+gR)*(gL+gR))*((aAR*aZdI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45)+C35*(2*((gL+gR)*(gL+gR))*((aAR*aZdI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46)+2*((gL-gR)*(gL-gR))*((aAR*aZdI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C34*C56)+(C35*C35)*(2*(-aAR*aZdI*(gL*gL)*(M1*M1)*(M2*M2)+aAR*aZdI*(gR*gR)*(M1*M1)*(M2*M2)+aAR*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ)-aAR*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ)+aAR*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ)-aAR*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ)-aAR*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ)+aAR*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ)+((aAR)*(aZdI)*(gL*gL)-(-aAR)*(-aZdI)*(gR*gR))*(MZ*MZ)*(wZ*wZ))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+C35*(4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAR_aZdR(LeptonVectors &leptons, double aAR, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(C46*(2*(MZ*wZ*((-aAR)*(aZdR)*(gL*gL)-(aAR)*(-aZdR)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46))*C56+E3456*(-2*C36*(((gL+gR)*(gL+gR))*((aAR*aZdR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAR*aZdR)*(MZ*MZ)*(wZ*wZ))*C45)+C35*(2*((gL+gR)*(gL+gR))*((aAR*aZdR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAR*aZdR)*(MZ*MZ)*(wZ*wZ))*C46)+2*((gL-gR)*(gL-gR))*((aAR*aZdR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAR*aZdR)*(MZ*MZ)*(wZ*wZ))*C34*C56)+(C35*C35)*(2*(-MZ*wZ*((aAR)*(-aZdR)*(gL*gL)-(-aAR)*(aZdR)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+C35*(4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAR_ahI(LeptonVectors &leptons, double aAR, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-2*aAR*ahI*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36-2*aAR*ahI*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36+4*aAR*ahI*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36-0-2*aAR*ahI*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45-2*aAR*ahI*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45+4*aAR*ahI*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45+aAR*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46+aAR*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46+aAR*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+aAR*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46-2*aAR*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*C46-2*aAR*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*C46+C34*(-2*gL*gR*(MZ*MZ)*((aAR*ahI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45-2*C36*(gL*gR*(MZ*MZ)*((aAR*ahI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))+C46*((MZ*MZ)*(((-aAR)*(gL*gL)-(aAR)*(gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))*C56+E3456*(-aAR*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46+aAR*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46+aAR*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-0-aAR*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46+aAR*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46-0-aAR*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46-0-aAR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46+aAR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46+aAR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46-0-aAR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46+C35*((MZ*MZ)*(aAR*(gL-gR)*(gL+gR)*(ahI*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahI*(MZ*MZ)*(wZ*wZ)))))+(C35*C35)*((MZ*MZ)*(-((aAR)*(gL*gL)+(aAR)*(gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C46)+C35*(-aAR*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)-aAR*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)-aAR*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)-aAR*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)+2*aAR*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46)+2*aAR*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46)+2*gL*gR*(MZ*MZ)*((aAR*ahI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45*C46-C36*(-2*gL*gR*(MZ*MZ)*((aAR*ahI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46+C45*((MZ*MZ)*(-((aAR)*(gL*gL)+(aAR)*(gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))+C34*((MZ*MZ)*(-((aAR)*(gL*gL)+(aAR)*(gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aAR_ahR(LeptonVectors &leptons, double aAR, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(+(aAR*aAR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*((-(aAR*aAR))*(C36*C45-C35*C46))+C34*(((aAR*aAR))*(C35*C35)+((aAR*aAR))*(C36*C36)+((aAR*aAR))*((C45*C45)+(C46*C46))+2*(-(aAR*aAR))*C36*C45+2*(-(aAR*aAR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-2*aAR*ahR*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*C36+2*aAR*ahR*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+2*aAR*ahR*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36-2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C45*C45)*C36+2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C45*C45)*C36-0-2*aAR*ahR*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*C45+2*aAR*ahR*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+2*aAR*ahR*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45-2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*(C36*C36)*C45+2*aAR*ahR*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C36*C36)*C45+aAR*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46+aAR*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46-0-aAR*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-aAR*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-aAR*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46-aAR*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46+aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46+aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46-0-aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46-aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46+C34*(-2*gL*gR*(MZ*MZ)*((aAR*ahR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAR*ahR)*(MZ*MZ)*(wZ*wZ))*C45-2*C36*(gL*gR*(MZ*MZ)*((aAR*ahR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAR*ahR)*(MZ*MZ)*(wZ*wZ)))+C46*((MZ*MZ)*(((-aAR)*(gL*gL)-(aAR)*(gR*gR))*(ahR*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahR*(MZ*MZ)*(wZ*wZ)))))*C56+E3456*(aAR*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46-aAR*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46+aAR*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46-aAR*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46-0-2*aAR*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46+2*aAR*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46+C35*((MZ*MZ)*(aAR*(gL-gR)*(gL+gR)*(-ahR*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))+(C35*C35)*((MZ*MZ)*(-((aAR)*(gL*gL)+(aAR)*(gR*gR))*(ahR*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahR*(MZ*MZ)*(wZ*wZ)))*C46)+C35*(-aAR*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)-aAR*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)+aAR*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)+aAR*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)+aAR*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)+aAR*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)-aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46)-aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46)+aAR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46)+aAR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46)+2*gL*gR*(MZ*MZ)*((aAR*ahR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAR*ahR)*(MZ*MZ)*(wZ*wZ))*C45*C46-C36*(-2*gL*gR*(MZ*MZ)*((aAR*ahR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAR*ahR)*(MZ*MZ)*(wZ*wZ))*C46+C45*((MZ*MZ)*(-((aAR)*(gL*gL)+(aAR)*(gR*gR))*(ahR*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahR*(MZ*MZ)*(wZ*wZ)))))+C34*((MZ*MZ)*(-((aAR)*(gL*gL)+(aAR)*(gR*gR))*(ahR*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahR*(MZ*MZ)*(wZ*wZ))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aAdI_aAdI(LeptonVectors &leptons, double aAdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.+0;
}

double GetGeneralScalar_aAdI_aAdR(LeptonVectors &leptons, double aAdI, double aAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI)-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI)+(aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI)+(aAdR*aAdR))*(C35*C35)+((aAdI*aAdI)+(aAdR*aAdR))*(C36*C36)+((aAdI*aAdI)+(aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI)+(aAdR*aAdR))*C36*C45+2*((aAdI*aAdI)+(aAdR*aAdR))*C35*C46)*C56))/4096.-0;
}

double GetGeneralScalar_aAdI_aZAI(LeptonVectors &leptons, double aAdI, double aZAI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*(gL+gR)*E3456*(2*aAdI*aZAI*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdI*aZAI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdI*aZAI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdI*aZAI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdI*aZAI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdI*aZAI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdI*aZAI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdI*aZAI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAdI*aZAI)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C36*C45-C35*C46)+C34*((aAdI*(-(aZAI*(-gL+gR))*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C35*C35)+(aAdI*(MZ*(wZ*(aZAI*(gL-gR)*(M1-M2)*(M1+M2)*((M1*M1)*(M2*M2)-(MZ*MZ)*((MZ*MZ)+(wZ*wZ)))))))*(C45*C45)+(aAdI*(-(aZAI*(gL-gR))*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C46*C46))*C56+(C36*C36)*((aAdI*(MZ*(wZ*(-(aZAI*(gL-gR)*(M1-M2)*(M1+M2)*((M1*M1)*(M2*M2)-(MZ*MZ)*((MZ*MZ)+(wZ*wZ))))))))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAdI_aZAR(LeptonVectors &leptons, double aAdI, double aZAR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*(gL+gR)*E3456*((-aAdI*aZAR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(-aAdI*aZAR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C36*C45-C35*C46)+C34*((aAdI*(aZAR*(gL-gR)*((M2-MZ)*(M2+MZ)*(-(M1*M1)+(MZ*MZ))*(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))+(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))))*(C35*C35)+(aAdI*(MZ*(aZAR*(gL-gR)*(M1-M2)*(M1+M2)*MZ*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-((M1*M1)+(M2*M2)-(MZ*MZ))*(wZ*wZ)))))*(C45*C45)+(aAdI*(aZAR*(gL-gR)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)*(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))+(MZ*MZ)*(-(M1*M1*M1*M1)-(M2*M2*M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))))*(C46*C46))*C56+(C36*C36)*((aAdI*(MZ*(-(aZAR*(gL-gR)*(M1-M2)*(M1+M2)*MZ*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-((M1*M1)+(M2*M2)-(MZ*MZ))*(wZ*wZ))))))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAdI_aZAdI(LeptonVectors &leptons, double aAdI, double aZAdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*aAdI*aZAdI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*aAdI*aZAdI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-8*aAdI*aZAdI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-8*aAdI*aZAdI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdI*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdI*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdI*aZAdI*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAdI*aZAdI*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAdI*aZAdI*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAdI*aZAdI*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(gL+gR)*(2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAdI*aZAdI)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C34*C34)*(C56*C56)+C34*((aAdI*(aZAdI*(gL+gR)*((M2-MZ)*(M2+MZ)*(-(M1*M1)+(MZ*MZ))*(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))+(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))))*(C35*C35)+(aAdI*(aZAdI*(gL+gR)*((M2-MZ)*(M2+MZ)*(-(M1*M1)+(MZ*MZ))*(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))+(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))))*(C45*C45)+(aAdI*(aZAdI*(gL+gR)*((M2-MZ)*(M2+MZ)*(-(M1*M1)+(MZ*MZ))*(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))+(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))))*(C46*C46)+2*(gL+gR)*(2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAdI*aZAdI)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*C35*C46)*C56+2*(gL+gR)*(2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAdI*aZAdI)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*C36*C45*(2*C35*C46+C34*C56)+(C36*C36)*(-2*(gL+gR)*(2*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdI*aZAdI*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdI*aZAdI*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdI*aZAdI*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdI*aZAdI*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdI*aZAdI*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdI*aZAdI*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdI*aZAdI*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAdI*aZAdI)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C45*C45)+(aAdI*(aZAdI*(gL+gR)*((M2-MZ)*(M2+MZ)*(-(M1*M1)+(MZ*MZ))*(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))+(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAdI_aZAdR(LeptonVectors &leptons, double aAdI, double aZAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*aAdI*aZAdR*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-8*aAdI*aZAdR*gL*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*(C46*C46)-8*aAdI*aZAdR*gR*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdI*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)-2*(gL+gR)*((-aAdI*aZAdR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(-aAdI*aZAdR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C34*C34)*(C56*C56)+C34*((aAdI*(-(aZAdR*(gL+gR))*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C35*C35)+(aAdI*(MZ*(wZ*(-aZAdR*(gL+gR)*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))))*(C45*C45)+(aAdI*(-(aZAdR*(gL+gR))*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C46*C46)+2*(gL+gR)*((-aAdI*aZAdR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(-aAdI*aZAdR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C35*C46)*C56+2*(gL+gR)*((-aAdI*aZAdR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(-aAdI*aZAdR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C36*C45*(2*C35*C46+C34*C56)+(C36*C36)*(-2*(gL+gR)*((-aAdI*aZAdR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(-aAdI*aZAdR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45)+(aAdI*(MZ*(wZ*(-aZAdR*(gL+gR)*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAdI_aZI(LeptonVectors &leptons, double aAdI, double aZI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(C46*(2*(MZ*wZ*((aAdI)*(aZI)*(gL*gL)-(aAdI)*(aZI)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46))*C56+E3456*(-2*C36*(((gL+gR)*(gL+gR))*((aAdI*aZI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdI*aZI)*(MZ*MZ)*(wZ*wZ))*C45)+C35*(2*((gL+gR)*(gL+gR))*((aAdI*aZI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdI*aZI)*(MZ*MZ)*(wZ*wZ))*C46)+2*((gL-gR)*(gL-gR))*((aAdI*aZI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdI*aZI)*(MZ*MZ)*(wZ*wZ))*C34*C56)+(C35*C35)*(2*(-MZ*wZ*((aAdI)*(aZI)*(gL*gL)-(aAdI)*(aZI)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI))*C45)+C35*(4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAdI_aZR(LeptonVectors &leptons, double aAdI, double aZR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(C46*(2*(aAdI*aZR*(gL*gL)*(M1*M1)*(M2*M2)-aAdI*aZR*(gR*gR)*(M1*M1)*(M2*M2)-aAdI*aZR*(gL*gL)*(M1*M1)*(MZ*MZ)+aAdI*aZR*(gR*gR)*(M1*M1)*(MZ*MZ)-aAdI*aZR*(gL*gL)*(M2*M2)*(MZ*MZ)+aAdI*aZR*(gR*gR)*(M2*M2)*(MZ*MZ)+aAdI*aZR*(gL*gL)*(MZ*MZ*MZ*MZ)-aAdI*aZR*(gR*gR)*(MZ*MZ*MZ*MZ)+((-aAdI)*(aZR)*(gL*gL)+(aAdI)*(aZR)*(gR*gR))*(MZ*MZ)*(wZ*wZ))*C46))*C56+E3456*(-2*C36*(((gL+gR)*(gL+gR))*((-aAdI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45)+C35*(2*((gL+gR)*(gL+gR))*((-aAdI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46)+2*((gL-gR)*(gL-gR))*((-aAdI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C34*C56)+(C35*C35)*(2*(-aAdI*aZR*(gL*gL)*(M1*M1)*(M2*M2)+aAdI*aZR*(gR*gR)*(M1*M1)*(M2*M2)+aAdI*aZR*(gL*gL)*(M1*M1)*(MZ*MZ)-aAdI*aZR*(gR*gR)*(M1*M1)*(MZ*MZ)+aAdI*aZR*(gL*gL)*(M2*M2)*(MZ*MZ)-aAdI*aZR*(gR*gR)*(M2*M2)*(MZ*MZ)-aAdI*aZR*(gL*gL)*(MZ*MZ*MZ*MZ)+aAdI*aZR*(gR*gR)*(MZ*MZ*MZ*MZ)+((aAdI)*(aZR)*(gL*gL)-(aAdI)*(aZR)*(gR*gR))*(MZ*MZ)*(wZ*wZ))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZR*aZR))*C45)+C35*(4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAdI_aZdI(LeptonVectors &leptons, double aAdI, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*aAdI*aZdI*gL*gR*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+2*aAdI*aZdI*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+2*aAdI*aZdI*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-4*aAdI*aZdI*gL*gR*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aAdI*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aAdI*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-4*aAdI*aZdI*gL*gR*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aAdI*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aAdI*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+4*aAdI*aZdI*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)+2*aAdI*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)+2*aAdI*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)-4*aAdI*aZdI*gL*gR*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)-2*aAdI*aZdI*(gL*gL)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)-2*aAdI*aZdI*(gR*gR)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)-2*((gL+gR)*(gL+gR))*((-(aAdI*aZdI))*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(aAdI*aZdI)*(MZ*MZ)*(wZ*wZ))*(C34*C34)*(C56*C56)+C34*(-4*gL*gR*((aAdI*aZdI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdI*aZdI)*(MZ*MZ)*(wZ*wZ))*(C36*C36)-4*gL*gR*((aAdI*aZdI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdI*aZdI)*(MZ*MZ)*(wZ*wZ))*(C45*C45)-2*C36*(-2*((gL*gL)+(gR*gR))*((-(aAdI*aZdI))*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(aAdI*aZdI)*(MZ*MZ)*(wZ*wZ))*C45)+C46*(2*(-(aAdI*aZdI*(gL*gL)*(M1*M1)*(M2*M2))-aAdI*aZdI*(gR*gR)*(M1*M1)*(M2*M2)+aAdI*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ)+aAdI*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ)+aAdI*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ)+aAdI*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ)-aAdI*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ)-aAdI*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ)+((-aAdI)*(-aZdI)*(gL*gL)+(aAdI)*(aZdI)*(gR*gR))*(MZ*MZ)*(wZ*wZ))*C46))*C56+(C35*C35)*(-2*((gL+gR)*(gL+gR))*((-(aAdI*aZdI))*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(aAdI*aZdI)*(MZ*MZ)*(wZ*wZ))*(C46*C46)+2*(-(aAdI*aZdI*(gL*gL)*(M1*M1)*(M2*M2))-aAdI*aZdI*(gR*gR)*(M1*M1)*(M2*M2)+aAdI*aZdI*(gL*gL)*(M1*M1)*(MZ*MZ)+aAdI*aZdI*(gR*gR)*(M1*M1)*(MZ*MZ)+aAdI*aZdI*(gL*gL)*(M2*M2)*(MZ*MZ)+aAdI*aZdI*(gR*gR)*(M2*M2)*(MZ*MZ)-aAdI*aZdI*(gL*gL)*(MZ*MZ*MZ*MZ)-aAdI*aZdI*(gR*gR)*(MZ*MZ*MZ*MZ)+((aAdI)*(aZdI)*(gL*gL)-(aAdI)*(-aZdI)*(gR*gR))*(MZ*MZ)*(wZ*wZ))*C34*C56)+C35*(-C36*(C45*(-4*((gL+gR)*(gL+gR))*((-(aAdI*aZdI))*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(aAdI*aZdI)*(MZ*MZ)*(wZ*wZ))*C46))+C34*(8*gL*gR*((-(aAdI*aZdI))*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(aAdI*aZdI)*(MZ*MZ)*(wZ*wZ))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+C35*(4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAdI_aZdR(LeptonVectors &leptons, double aAdI, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*aAdI*aZdR*gL*gR*MZ*wZ*(M1*M1)*(C36*C36)*(C45*C45)-2*aAdI*aZdR*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)-2*aAdI*aZdR*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)-4*aAdI*aZdR*gL*gR*MZ*wZ*(M2*M2)*(C36*C36)*(C45*C45)-2*aAdI*aZdR*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)-2*aAdI*aZdR*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)+8*aAdI*aZdR*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)+4*aAdI*aZdR*wZ*(gL*gL)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)+4*aAdI*aZdR*wZ*(gR*gR)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)-2*((gL+gR)*(gL+gR))*((aAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C34*C34)*(C56*C56)+C34*(-4*gL*gR*((-aAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C36*C36)-4*gL*gR*((-aAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C45*C45)-2*C36*(-2*((gL*gL)+(gR*gR))*((aAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45)+C46*(2*(MZ*wZ*((aAdI)*(aZdR)*(gL*gL)-(aAdI)*(-aZdR)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46))*C56+(C35*C35)*(-2*((gL+gR)*(gL+gR))*((aAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C46*C46)+2*(-MZ*wZ*((aAdI)*(-aZdR)*(gL*gL)-(aAdI)*(aZdR)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C34*C56)+C35*(-C36*(C45*(-4*((gL+gR)*(gL+gR))*((aAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46))+C34*(8*gL*gR*((aAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+C35*(4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAdI_ahI(LeptonVectors &leptons, double aAdI, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-aAdI*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46+aAdI*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46-aAdI*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+aAdI*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+2*aAdI*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*C46-0-2*aAdI*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*C46+C34*(C46*((MZ*MZ)*(((aAdI)*(gL*gL)-(aAdI)*(gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))*C56+E3456*(-2*aAdI*ahI*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*C45+2*aAdI*ahI*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*C45+2*aAdI*ahI*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*C45-2*aAdI*ahI*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*C45+2*aAdI*ahI*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C45-2*C36*(gL*gR*(MZ*MZ)*((aAdI*ahI)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdI*ahI)*(MZ*MZ)*(wZ*wZ)))+aAdI*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46+aAdI*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46-aAdI*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-aAdI*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-0-aAdI*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46-aAdI*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46+aAdI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46+aAdI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46-aAdI*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46-aAdI*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46+C35*((MZ*MZ)*(aAdI*((gL*gL)+(gR*gR))*(ahI*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahI*(MZ*MZ)*(wZ*wZ)))))+(C35*C35)*((MZ*MZ)*(-((aAdI)*(gL*gL)+(-aAdI)*(gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C46)+C35*(aAdI*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)-aAdI*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)+aAdI*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)-aAdI*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)-2*aAdI*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46)+2*aAdI*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46)-C36*(C45*((MZ*MZ)*(-((aAdI)*(gL*gL)+(-aAdI)*(gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))+C34*((MZ*MZ)*(-((aAdI)*(gL*gL)+(-aAdI)*(gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aAdI_ahR(LeptonVectors &leptons, double aAdI, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdI*aAdI))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdI*aAdI))*(C36*C45-C35*C46))+C34*(((aAdI*aAdI))*(C35*C35)+((aAdI*aAdI))*(C36*C36)+((aAdI*aAdI))*((C45*C45)+(C46*C46))+2*((aAdI*aAdI))*C36*C45+2*((aAdI*aAdI))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-aAdI*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46+aAdI*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46+aAdI*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-aAdI*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46+aAdI*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-aAdI*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46+aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46+aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46-0-aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46+C34*(C46*((MZ*MZ)*(((aAdI)*(gL*gL)-(aAdI)*(gR*gR))*(ahR*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahR*(MZ*MZ)*(wZ*wZ)))))*C56+E3456*(2*aAdI*ahR*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*C45+2*aAdI*ahR*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*C45-4*aAdI*ahR*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*C45-0-2*C36*(gL*gR*(MZ*MZ)*((-aAdI*ahR)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))-aAdI*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46-aAdI*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46-0-aAdI*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46-aAdI*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46+2*aAdI*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46+2*aAdI*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46+C35*((MZ*MZ)*(aAdI*((gL*gL)+(gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))+(C35*C35)*((MZ*MZ)*(-((aAdI)*(gL*gL)+(-aAdI)*(gR*gR))*(ahR*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahR*(MZ*MZ)*(wZ*wZ)))*C46)+C35*(aAdI*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)-aAdI*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)-aAdI*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)+aAdI*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)-aAdI*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)+aAdI*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)+aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46)-aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46)-aAdI*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46)+aAdI*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46)-C36*(C45*((MZ*MZ)*(-((aAdI)*(gL*gL)+(-aAdI)*(gR*gR))*(ahR*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahR*(MZ*MZ)*(wZ*wZ)))))+C34*((MZ*MZ)*(-((aAdI)*(gL*gL)+(-aAdI)*(gR*gR))*(ahR*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahR*(MZ*MZ)*(wZ*wZ))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aAdR_aAdR(LeptonVectors &leptons, double aAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.-0;
}

double GetGeneralScalar_aAdR_aZAI(LeptonVectors &leptons, double aAdR, double aZAI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*(gL+gR)*E3456*((aAdR*aZAI)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(aAdR*aZAI)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C36*C45-C35*C46)+C34*((-2*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)+3*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-4*aAdR*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+((aAdR)*(-aZAI)*gL+(aAdR)*(aZAI)*gR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C35*C35)+(-aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(aAdR*aZAI*gL*(M1*M1*M1*M1)-aAdR*aZAI*gR*(M1*M1*M1*M1)-aAdR*aZAI*gL*(M2*M2*M2*M2)+aAdR*aZAI*gR*(M2*M2*M2*M2)-(((aAdR)*(aZAI)*gL+(aAdR)*(-aZAI)*gR)*(M1*M1)+((aAdR)*(-aZAI)*gL+(aAdR)*(aZAI)*gR)*(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C45*C45)+(2*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)-2*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)+3*aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+3*aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)-aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAI*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)-4*aAdR*aZAI*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+((-aAdR)*(aZAI)*gL-(aAdR)*(-aZAI)*gR)*(MZ*MZ)*(-(M1*M1*M1*M1)-(M2*M2*M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C46*C46))*C56+(C36*C36)*((aAdR*aZAI*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-aAdR*aZAI*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-aAdR*aZAI*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAI*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-aAdR*aZAI*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAdR*aZAI*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAdR*aZAI*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAI*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAI*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAI*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAI*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+aAdR*aZAI*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(-aAdR*aZAI*gL*(M1*M1*M1*M1)+aAdR*aZAI*gR*(M1*M1*M1*M1)+aAdR*aZAI*gL*(M2*M2*M2*M2)-aAdR*aZAI*gR*(M2*M2*M2*M2)-(((aAdR)*(-aZAI)*gL+(aAdR)*(aZAI)*gR)*(M1*M1)+((aAdR)*(aZAI)*gL+(aAdR)*(-aZAI)*gR)*(M2*M2))*(MZ*MZ))*(wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAdR_aZAR(LeptonVectors &leptons, double aAdR, double aZAR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*(gL+gR)*E3456*(2*aAdR*aZAR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdR*aZAR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAdR*aZAR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C36*C45-C35*C46)+C34*(((((aAdR)*(aZAR))*gL+((aAdR)*(-aZAR))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(((aAdR)*(aZAR))*gL+((aAdR)*(-aZAR))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C35*C35)+(MZ*wZ*(aAdR*(aZAR*(gL-gR)*(M1-M2)*(M1+M2)*((M1*M1)*(M2*M2)-(MZ*MZ*MZ*MZ))))+((((aAdR)*(-aZAR))*gL+((aAdR)*(aZAR))*gR)*(M1*M1)+(((aAdR)*(aZAR))*gL+((aAdR)*(-aZAR))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45)+((((aAdR)*(-aZAR))*gL+((aAdR)*(aZAR))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(((aAdR)*(-aZAR))*gL+((aAdR)*(aZAR))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C46*C46))*C56+(C36*C36)*((MZ*wZ*(aAdR*(aZAR*(gL-gR)*(M1-M2)*(M1+M2)*(-((M1*M1)*(M2*M2))+(MZ*MZ*MZ*MZ))))+((((aAdR)*(aZAR))*gL+((aAdR)*(-aZAR))*gR)*(M1*M1)+(((aAdR)*(-aZAR))*gL+((aAdR)*(aZAR))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAdR_aZAdI(LeptonVectors &leptons, double aAdR, double aZAdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-2*aAdR*aZAdI*gL*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gR*MZ*wZ*(M1*M1*M1*M1)*(M2*M2)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gL*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gR*MZ*wZ*(M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+8*aAdR*aZAdI*gL*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*(C46*C46)+8*aAdR*aZAdI*gR*wZ*(M1*M1)*(M2*M2)*(MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gL*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gR*wZ*(M1*M1)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gL*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gR*wZ*(M2*M2)*(MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gL*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gR*(M1*M1)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gL*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdI*gR*(M2*M2)*(MZ*MZ*MZ)*(wZ*wZ*wZ)*(C35*C35)*(C46*C46)-2*(gL+gR)*((aAdR*aZAdI)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(aAdR*aZAdI)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C34*C34)*(C56*C56)+C34*(((((aAdR)*(aZAdI))*gL+((aAdR)*(aZAdI))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(((aAdR)*(aZAdI))*gL+((aAdR)*(aZAdI))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C35*C35)+(MZ*wZ*(aAdR*(aZAdI*(gL+gR)*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))))+((((aAdR)*(aZAdI))*gL+((aAdR)*(aZAdI))*gR)*(M1*M1)+(((aAdR)*(aZAdI))*gL+((aAdR)*(aZAdI))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45)+((((aAdR)*(aZAdI))*gL+((aAdR)*(aZAdI))*gR)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(((aAdR)*(aZAdI))*gL+((aAdR)*(aZAdI))*gR)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C46*C46)+2*(gL+gR)*((aAdR*aZAdI)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(aAdR*aZAdI)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C35*C46)*C56+2*(gL+gR)*((aAdR*aZAdI)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(aAdR*aZAdI)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C36*C45*(2*C35*C46+C34*C56)+(C36*C36)*(-2*(gL+gR)*((aAdR*aZAdI)*MZ*wZ*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))+(aAdR*aZAdI)*((M1*M1)+(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*(C45*C45)+(MZ*wZ*(aAdR*(aZAdI*(gL+gR)*((M1*M1*M1*M1)*(M2*M2)+(M2*M2)*(MZ*MZ*MZ*MZ)+(M1*M1)*((M2*M2*M2*M2)-4*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)))))+((((aAdR)*(aZAdI))*gL+((aAdR)*(aZAdI))*gR)*(M1*M1)+(((aAdR)*(aZAdI))*gL+((aAdR)*(aZAdI))*gR)*(M2*M2))*(MZ*MZ*MZ)*(wZ*wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAdR_aZAdR(LeptonVectors &leptons, double aAdR, double aZAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.+((el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-8*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-8*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(gL+gR)*(2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAdR*aZAdR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C34*C34)*(C56*C56)+C34*((2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+((aAdR)*(aZAdR)*gL+(aAdR)*(aZAdR)*gR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C35*C35)+(2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(aAdR*aZAdR*gL*(M1*M1*M1*M1)+aAdR*aZAdR*gR*(M1*M1*M1*M1)+aAdR*aZAdR*gL*(M2*M2*M2*M2)+aAdR*aZAdR*gR*(M2*M2*M2*M2)-(((aAdR)*(aZAdR)*gL+(aAdR)*(aZAdR)*gR)*(M1*M1)+((aAdR)*(aZAdR)*gL+(aAdR)*(aZAdR)*gR)*(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C45*C45)+(2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+((-aAdR)*(aZAdR)*gL-(aAdR)*(aZAdR)*gR)*(MZ*MZ)*(-(M1*M1*M1*M1)-(M2*M2*M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C46*C46)+2*(gL+gR)*(2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAdR*aZAdR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*C35*C46)*C56+2*(gL+gR)*(2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAdR*aZAdR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*C36*C45*(2*C35*C46+C34*C56)+(C36*C36)*(-2*(gL+gR)*(2*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdR*aZAdR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAdR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAdR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(aAdR*aZAdR)*(MZ*MZ)*((M1*M1*M1*M1)+(M2*M2*M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))*(wZ*wZ))*(C45*C45)+(2*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2*M2*M2)+2*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2*M2*M2)-3*aAdR*aZAdR*gL*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gR*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gL*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)-3*aAdR*aZAdR*gR*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+aAdR*aZAdR*gL*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gR*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*gL*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+4*aAdR*aZAdR*gR*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gL*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)+aAdR*aZAdR*gR*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)-aAdR*aZAdR*gL*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gR*(M1*M1)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gL*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)-aAdR*aZAdR*gR*(M2*M2)*(MZ*MZ*MZ*MZ*MZ*MZ)+(MZ*MZ)*(aAdR*aZAdR*gL*(M1*M1*M1*M1)+aAdR*aZAdR*gR*(M1*M1*M1*M1)+aAdR*aZAdR*gL*(M2*M2*M2*M2)+aAdR*aZAdR*gR*(M2*M2*M2*M2)-(((aAdR)*(aZAdR)*gL+(aAdR)*(aZAdR)*gR)*(M1*M1)+((aAdR)*(aZAdR)*gL+(aAdR)*(aZAdR)*gR)*(M2*M2))*(MZ*MZ))*(wZ*wZ))*C34*C56)))/4096.+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aAdR_aZI(LeptonVectors &leptons, double aAdR, double aZI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(C46*(2*(aAdR*((M1-MZ)*(M1+MZ)*((aZI)*(gL*gL)+(-aZI)*(gR*gR))*(-(M2*M2)+(MZ*MZ))+((aZI)*(gL*gL)+(-aZI)*(gR*gR))*(MZ*MZ)*(wZ*wZ)))*C46))*C56+E3456*(-2*C36*(((gL+gR)*(gL+gR))*((aAdR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45)+C35*(2*((gL+gR)*(gL+gR))*((aAdR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46)+2*((gL-gR)*(gL-gR))*((aAdR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C34*C56)+(C35*C35)*(2*(aAdR*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)*((aZI)*(gL*gL)-(aZI)*(gR*gR))+((-aZI)*(gL*gL)+(aZI)*(gR*gR))*(MZ*MZ)*(wZ*wZ)))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI))*C45)+C35*(4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAdR_aZR(LeptonVectors &leptons, double aAdR, double aZR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(C46*(2*(aAdR*(MZ*wZ*((aZR)*(gL*gL)-(aZR)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C46))*C56+E3456*(-2*C36*(((gL+gR)*(gL+gR))*((aAdR*aZR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdR*aZR)*(MZ*MZ)*(wZ*wZ))*C45)+C35*(2*((gL+gR)*(gL+gR))*((aAdR*aZR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdR*aZR)*(MZ*MZ)*(wZ*wZ))*C46)+2*((gL-gR)*(gL-gR))*((aAdR*aZR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdR*aZR)*(MZ*MZ)*(wZ*wZ))*C34*C56)+(C35*C35)*(2*(aAdR*(-MZ*wZ*((aZR)*(gL*gL)+(-aZR)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZR*aZR))*C45)+C35*(4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAdR_aZdI(LeptonVectors &leptons, double aAdR, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*aAdR*aZdI*gL*gR*MZ*wZ*(M1*M1)*(C36*C36)*(C45*C45)+2*aAdR*aZdI*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)+2*aAdR*aZdI*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)+4*aAdR*aZdI*gL*gR*MZ*wZ*(M2*M2)*(C36*C36)*(C45*C45)+2*aAdR*aZdI*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)+2*aAdR*aZdI*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)-8*aAdR*aZdI*gL*gR*wZ*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)-4*aAdR*aZdI*wZ*(gL*gL)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)-4*aAdR*aZdI*wZ*(gR*gR)*(MZ*MZ*MZ)*(C36*C36)*(C45*C45)-2*((gL+gR)*(gL+gR))*((-(aAdR*aZdI))*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C34*C34)*(C56*C56)+C34*(-4*gL*gR*((aAdR*aZdI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C36*C36)-4*gL*gR*((aAdR*aZdI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C45*C45)-2*C36*(-2*((gL*gL)+(gR*gR))*((-(aAdR*aZdI))*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C45)+C46*(2*(aAdR*(MZ*wZ*((-aZdI)*(gL*gL)-(aZdI)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C46))*C56+(C35*C35)*(-2*((gL+gR)*(gL+gR))*((-(aAdR*aZdI))*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*(C46*C46)+2*(aAdR*(-MZ*wZ*((aZdI)*(gL*gL)+(aZdI)*(gR*gR))*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C34*C56)+C35*(-C36*(C45*(-4*((gL+gR)*(gL+gR))*((-(aAdR*aZdI))*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46))+C34*(8*gL*gR*((-(aAdR*aZdI))*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+C35*(4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAdR_aZdR(LeptonVectors &leptons, double aAdR, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*aAdR*aZdR*gL*gR*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+2*aAdR*aZdR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+2*aAdR*aZdR*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-4*aAdR*aZdR*gL*gR*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aAdR*aZdR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aAdR*aZdR*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-4*aAdR*aZdR*gL*gR*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aAdR*aZdR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aAdR*aZdR*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+4*aAdR*aZdR*gL*gR*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)+2*aAdR*aZdR*(gL*gL)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)+2*aAdR*aZdR*(gR*gR)*(MZ*MZ*MZ*MZ)*(C36*C36)*(C45*C45)-4*aAdR*aZdR*gL*gR*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)-2*aAdR*aZdR*(gL*gL)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)-2*aAdR*aZdR*(gR*gR)*(MZ*MZ)*(wZ*wZ)*(C36*C36)*(C45*C45)-2*((gL+gR)*(gL+gR))*((-aAdR*aZdR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(aAdR*aZdR)*(MZ*MZ)*(wZ*wZ))*(C34*C34)*(C56*C56)+C34*(-4*gL*gR*((aAdR*aZdR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdR*aZdR)*(MZ*MZ)*(wZ*wZ))*(C36*C36)-4*gL*gR*((aAdR*aZdR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdR*aZdR)*(MZ*MZ)*(wZ*wZ))*(C45*C45)-2*C36*(-2*((gL*gL)+(gR*gR))*((-aAdR*aZdR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(aAdR*aZdR)*(MZ*MZ)*(wZ*wZ))*C45)+C46*(2*(aAdR*((M1-MZ)*(M1+MZ)*((aZdR)*(gL*gL)+(aZdR)*(gR*gR))*(-(M2*M2)+(MZ*MZ))+((aZdR)*(gL*gL)+(aZdR)*(gR*gR))*(MZ*MZ)*(wZ*wZ)))*C46))*C56+(C35*C35)*(-2*((gL+gR)*(gL+gR))*((-aAdR*aZdR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(aAdR*aZdR)*(MZ*MZ)*(wZ*wZ))*(C46*C46)+2*(aAdR*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)*((-aZdR)*(gL*gL)-(aZdR)*(gR*gR))+((aZdR)*(gL*gL)+(aZdR)*(gR*gR))*(MZ*MZ)*(wZ*wZ)))*C34*C56)+C35*(-C36*(C45*(-4*((gL+gR)*(gL+gR))*((-aAdR*aZdR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(aAdR*aZdR)*(MZ*MZ)*(wZ*wZ))*C46))+C34*(8*gL*gR*((-aAdR*aZdR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(aAdR*aZdR)*(MZ*MZ)*(wZ*wZ))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+C35*(4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aAdR_ahI(LeptonVectors &leptons, double aAdR, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(aAdR*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46-aAdR*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46-aAdR*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46+aAdR*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-aAdR*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46+aAdR*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46+aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46-aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C36*C45*C46-aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46+aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C36*C45*C46+C34*(C46*((MZ*MZ)*(-(aAdR*(gL-gR)*(gL+gR)*(ahI*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahI*(MZ*MZ)*(wZ*wZ))))))*C56+E3456*(-2*aAdR*ahI*gL*gR*wZ*(M1*M1)*(MZ*MZ*MZ)*C45-2*aAdR*ahI*gL*gR*wZ*(M2*M2)*(MZ*MZ*MZ)*C45+4*aAdR*ahI*gL*gR*wZ*(MZ*MZ*MZ*MZ*MZ)*C45-0-2*C36*(gL*gR*(MZ*MZ)*((aAdR*ahI)*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))+aAdR*ahI*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46+aAdR*ahI*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46+aAdR*ahI*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46+aAdR*ahI*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46-0-2*aAdR*ahI*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C46-0-2*aAdR*ahI*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C46+C35*((MZ*MZ)*(((aAdR)*(gL*gL)+(aAdR)*(gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))+(C35*C35)*((MZ*MZ)*(aAdR*(gL-gR)*(gL+gR)*(ahI*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahI*(MZ*MZ)*(wZ*wZ)))*C46)+C35*(-(aAdR*ahI*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46))+aAdR*ahI*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)+aAdR*ahI*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)-aAdR*ahI*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)+aAdR*ahI*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)-aAdR*ahI*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)-aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46)+aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*(C46*C46)+aAdR*ahI*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46)-aAdR*ahI*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*(C46*C46)-C36*(C45*((MZ*MZ)*(aAdR*(gL-gR)*(gL+gR)*(ahI*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahI*(MZ*MZ)*(wZ*wZ)))))+C34*((MZ*MZ)*(aAdR*(gL-gR)*(gL+gR)*(ahI*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahI*(MZ*MZ)*(wZ*wZ))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aAdR_ahR(LeptonVectors &leptons, double aAdR, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return ((el*el*el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(2*(-(aAdR*aAdR))*(C34*C34)*(C56*C56)-2*(C36*C45-C35*C46)*(((aAdR*aAdR))*(C36*C45-C35*C46))+C34*(((aAdR*aAdR))*(C35*C35)+((aAdR*aAdR))*(C36*C36)+((aAdR*aAdR))*((C45*C45)+(C46*C46))+2*((aAdR*aAdR))*C36*C45+2*((aAdR*aAdR))*C35*C46)*C56))/4096.-((el*el)*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-aAdR*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46+aAdR*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46-0-aAdR*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+aAdR*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+2*aAdR*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*C46-2*aAdR*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*C36*C45*C46+C34*(C46*((MZ*MZ)*(-(aAdR*(gL-gR)*(gL+gR)*(-ahR*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))))))*C56+E3456*(-2*aAdR*ahR*gL*gR*(M1*M1)*(M2*M2)*(MZ*MZ)*C45+2*aAdR*ahR*gL*gR*(M1*M1)*(MZ*MZ*MZ*MZ)*C45+2*aAdR*ahR*gL*gR*(M2*M2)*(MZ*MZ*MZ*MZ)*C45-2*aAdR*ahR*gL*gR*(MZ*MZ*MZ*MZ*MZ*MZ)*C45+2*aAdR*ahR*gL*gR*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C45-2*C36*(gL*gR*(MZ*MZ)*((aAdR*ahR)*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-(aAdR*ahR)*(MZ*MZ)*(wZ*wZ)))+aAdR*ahR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46+aAdR*ahR*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46-0-aAdR*ahR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-0-aAdR*ahR*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-aAdR*ahR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46-0-aAdR*ahR*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46+aAdR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46+aAdR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ*MZ*MZ)*C46-0-aAdR*ahR*(gL*gL)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46-0-aAdR*ahR*(gR*gR)*(MZ*MZ*MZ*MZ)*(wZ*wZ)*C46+C35*((MZ*MZ)*(((aAdR)*(gL*gL)+(aAdR)*(gR*gR))*(ahR*(M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)-ahR*(MZ*MZ)*(wZ*wZ)))))+(C35*C35)*((MZ*MZ)*(aAdR*(gL-gR)*(gL+gR)*(-ahR*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))*C46)+C35*(aAdR*ahR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)-aAdR*ahR*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)+aAdR*ahR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)-aAdR*ahR*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)-2*aAdR*ahR*wZ*(gL*gL)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46)+2*aAdR*ahR*wZ*(gR*gR)*(MZ*MZ*MZ*MZ*MZ)*(C46*C46)-C36*(C45*((MZ*MZ)*(aAdR*(gL-gR)*(gL+gR)*(-ahR*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ))))))+C34*((MZ*MZ)*(aAdR*(gL-gR)*(gL+gR)*(-ahR*MZ*wZ*((M1*M1)+(M2*M2)-2*(MZ*MZ)))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aZAI_aZAI(LeptonVectors &leptons, double aZAI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aZAI_aZAR(LeptonVectors &leptons, double aZAI, double aZAR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI)-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI))+((aZAR)*(aZAR)))*(gL*gL)+(((aZAI)*(aZAI))+((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI)+(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI))+((-aZAR)*(-aZAR)))*(gL*gL)+(((-aZAI)*(-aZAI))+((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI)-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI)-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI)+(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI)-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aZAI_aZAdI(LeptonVectors &leptons, double aZAI, double aZAdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI)-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI))+((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAI)*(aZAI))+((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))+((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI))+((aZAdI)*(aZAdI)))*(gL*gL)+(((-aZAI)*(-aZAI))+((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI)-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+4*(aZAdI*aZAI)*E3456*((2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C36*C45-(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46-((gL-gR)*(gL-gR))*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))*C34*C56)+(C36*C36)*(-2*((aZAdI*aZAdI)-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))+((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI)-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aZAI_aZAdR(LeptonVectors &leptons, double aZAI, double aZAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR)-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR-aZAI)*(aZAdR-aZAI)))*(gL*gL)+(((aZAdR+aZAI)*(aZAdR+aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(-2*aZAdR*aZAI*(gL-gR)*(gL+gR)*(M1-M2)*(M1+M2)*(MZ*MZ)*((M1*M1)*(2*(M2*M2)-(MZ*MZ)-(wZ*wZ))-(M2*M2)*((MZ*MZ)+(wZ*wZ)))+(aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))+((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR+aZAI)*(aZAdR+aZAI)))*(gL*gL)+(((aZAdR-aZAI)*(aZAdR-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR)-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR)-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(2*aZAdR*aZAI*(gL-gR)*(gL+gR)*(M1-M2)*(M1+M2)*(MZ*MZ)*((M1*M1)*(2*(M2*M2)-(MZ*MZ)-(wZ*wZ))-(M2*M2)*((MZ*MZ)+(wZ*wZ)))+(aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))+((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR)-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aZAI_aZI(LeptonVectors &leptons, double aZAI, double aZI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*aZAI*aZI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-4*aZAI*aZI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-4*aZAI*aZI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-4*aZAI*aZI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+2*aZAI*aZI*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAI*aZI*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAI*aZI*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAI*aZI*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAI*aZI*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAI*aZI*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAI*aZI*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAI*aZI*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*(gL+gR)*((gL*gL)+(gR*gR))*((+aZAI*aZI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*(C34*C34)*(C56*C56)+C34*(-2*gL*gR*(aZAI*(aZI*(gL+gR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ))))*(C36*C36)+2*gL*gR*(aZAI*(aZI*(gL+gR)*(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ))))*(C45*C45)+C36*(4*((gL*gL*gL)+(gR*gR*gR))*((+aZAI*aZI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C45)+C46*(2*(-aZAI*((aZI)*(gL*gL*gL)+(aZI)*(gR*gR*gR))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46))*C56+(C35*C35)*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((+aZAI*aZI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*(C46*C46)+2*(-aZAI*((aZI)*(gL*gL*gL)+(aZI)*(gR*gR*gR))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C34*C56)-C35*(C36*(C45*(-4*(gL+gR)*((gL*gL)+(gR*gR))*((+aZAI*aZI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46))-C34*(4*gL*gR*(gL+gR)*((+aZAI*aZI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI))*C45)+C35*(4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAI_aZR(LeptonVectors &leptons, double aZAI, double aZR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*aZAI*aZR*gR*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)+2*aZAI*aZR*MZ*wZ*(gL*gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)+2*aZAI*aZR*gL*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)+2*aZAI*aZR*MZ*wZ*(gR*gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)+2*aZAI*aZR*gR*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)+2*aZAI*aZR*MZ*wZ*(gL*gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)+2*aZAI*aZR*gL*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)+2*aZAI*aZR*MZ*wZ*(gR*gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)-2*(gL+gR)*((gL*gL)+(gR*gR))*((-aZAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)))*(C34*C34)*(C56*C56)+C34*(-2*gL*gR*(aZAI*(MZ*(-wZ*(aZR*(gL+gR)*((M1*M1)+(M2*M2))))))*(C36*C36)+2*gL*gR*(aZAI*(MZ*(wZ*(aZR*(gL+gR)*((M1*M1)+(M2*M2))))))*(C45*C45)+C36*(4*((gL*gL*gL)+(gR*gR*gR))*((-aZAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)))*C45)+C46*(2*(aZAI*MZ*wZ*((aZR)*(gL*gL*gL)+(aZR)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C46))*C56+(C35*C35)*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((-aZAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)))*(C46*C46)+2*(aZAI*MZ*wZ*((aZR)*(gL*gL*gL)+(aZR)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C34*C56)-C35*(C36*(C45*(-4*(gL+gR)*((gL*gL)+(gR*gR))*((-aZAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)))*C46))-C34*(4*gL*gR*(gL+gR)*((-aZAI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZR*aZR))*C45)+C35*(4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAI_aZdI(LeptonVectors &leptons, double aZAI, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(-2*gL*gR*(aZAI*(MZ*(-wZ*(aZdI*(gL-gR)*(M1-M2)*(M1+M2)))))*(C36*C36)+2*gL*gR*(aZAI*(MZ*(wZ*(aZdI*(gL-gR)*(-(M1*M1)+(M2*M2))))))*(C45*C45)+C46*(2*(aZAI*MZ*wZ*((-aZdI)*(gL*gL*gL)+(aZdI)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C46))*C56+E3456*(C36*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAI*aZdI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C45)+C35*(2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAI*aZdI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)+2*(gL+gR)*((gL-gR)*(gL-gR))*((aZAI*aZdI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C34*C56)+(C35*C35)*(2*(aZAI*MZ*wZ*((aZdI)*(gL*gL*gL)+(-aZdI)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+C35*(4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAI_aZdR(LeptonVectors &leptons, double aZAI, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(-2*gL*gR*(aZAI*(MZ*(aZdR*(gL-gR)*(M1-M2)*(M1+M2)*MZ)))*(C36*C36)+2*gL*gR*(aZAI*(MZ*(aZdR*(gL-gR)*(M1-M2)*(M1+M2)*MZ)))*(C45*C45)+C46*(2*(-aZAI*((aZdR)*(gL*gL*gL)+(-aZdR)*(gR*gR*gR))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46))*C56+E3456*(C36*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((-aZAI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)))*C45)+C35*(2*(gL+gR)*((gL*gL)+(gR*gR))*((-aZAI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)))*C46)+2*(gL+gR)*((gL-gR)*(gL-gR))*((-aZAI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)))*C34*C56)+(C35*C35)*(2*(-aZAI*((-aZdR)*(gL*gL*gL)+(aZdR)*(gR*gR*gR))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+C35*(4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAI_ahI(LeptonVectors &leptons, double aZAI, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-2*ahI*aZAI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*C36-0-2*ahI*aZAI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*C36+ahI*aZAI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+ahI*aZAI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+ahI*aZAI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+ahI*aZAI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36-2*ahI*aZAI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*C45-0-2*ahI*aZAI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*C45+ahI*aZAI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+ahI*aZAI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+ahI*aZAI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+ahI*aZAI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+2*ahI*aZAI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46+2*ahI*aZAI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46-ahI*aZAI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-ahI*aZAI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-ahI*aZAI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-ahI*aZAI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46+C34*(gL*gR*(MZ*MZ)*(aZAI*(gL+gR)*(-2*ahI*(M1*M1)*(M2*M2)+ahI*((M1*M1)+(M2*M2))*(MZ*MZ)))*C45+C36*(gL*gR*(MZ*MZ)*(aZAI*(gL+gR)*(-2*ahI*(M1*M1)*(M2*M2)+ahI*((M1*M1)+(M2*M2))*(MZ*MZ))))+C46*((MZ*MZ)*(-aZAI*((gL*gL*gL)+(gR*gR*gR))*(2*ahI*(M1*M1)*(M2*M2)-ahI*((M1*M1)+(M2*M2))*(MZ*MZ)))))*C56+E3456*(-ahI*aZAI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45+ahI*aZAI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45+ahI*aZAI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45-ahI*aZAI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45+C36*(gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(ahI*aZAI*wZ)))+ahI*aZAI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46-ahI*aZAI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46+ahI*aZAI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46-ahI*aZAI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46+C35*(-((MZ*MZ)*((-((-aZAI)*(gL*gL*gL))-(aZAI)*(gR*gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)))))))+(C35*C35)*((MZ*MZ)*(-aZAI*((gL*gL*gL)+(gR*gR*gR))*(2*ahI*(M1*M1)*(M2*M2)-ahI*((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)-C35*(2*ahI*aZAI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)+2*ahI*aZAI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)-ahI*aZAI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)-ahI*aZAI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)-ahI*aZAI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)-ahI*aZAI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)+gL*gR*(MZ*MZ)*(aZAI*(gL+gR)*(-2*ahI*(M1*M1)*(M2*M2)+ahI*((M1*M1)+(M2*M2))*(MZ*MZ)))*C45*C46+C36*(gL*gR*(MZ*MZ)*(aZAI*(gL+gR)*(-2*ahI*(M1*M1)*(M2*M2)+ahI*((M1*M1)+(M2*M2))*(MZ*MZ)))*C46+C45*((MZ*MZ)*(-aZAI*((gL*gL*gL)+(gR*gR*gR))*(2*ahI*(M1*M1)*(M2*M2)-ahI*((M1*M1)+(M2*M2))*(MZ*MZ)))))-C34*((MZ*MZ)*(-aZAI*((gL*gL*gL)+(gR*gR*gR))*(2*ahI*(M1*M1)*(M2*M2)-ahI*((M1*M1)+(M2*M2))*(MZ*MZ))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aZAI_ahR(LeptonVectors &leptons, double aZAI, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAI*aZAI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAI*aZAI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((-aZAI)*(-aZAI)))*(gL*gL)+(((aZAI)*(aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAI)*(aZAI)))*(gL*gL)+(((-aZAI)*(-aZAI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAI*aZAI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAI*aZAI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAI*aZAI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(ahR*aZAI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45+ahR*aZAI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45+ahR*aZAI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45+ahR*aZAI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45-0-ahR*aZAI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46-ahR*aZAI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46-ahR*aZAI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46-ahR*aZAI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+C34*(gL*gR*(MZ*MZ)*(aZAI*(gL+gR)*(ahR*MZ*wZ*((M1*M1)+(M2*M2))))*C45+C36*(gL*gR*(MZ*MZ)*(aZAI*(gL+gR)*(ahR*MZ*wZ*((M1*M1)+(M2*M2)))))+C46*((MZ*MZ)*(-aZAI*((gL*gL*gL)+(gR*gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2))))))*C56+E3456*(ahR*aZAI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45-0-ahR*aZAI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45-ahR*aZAI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45+ahR*aZAI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45+C36*(gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(-(ahR*aZAI*MZ))))+2*ahR*aZAI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46-0-2*ahR*aZAI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46-ahR*aZAI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46+ahR*aZAI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-0-ahR*aZAI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46+ahR*aZAI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46+C35*(-((MZ*MZ)*((-((-aZAI)*(gL*gL*gL))-(aZAI)*(gR*gR*gR))*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ))))))+(C35*C35)*((MZ*MZ)*(-aZAI*((gL*gL*gL)+(gR*gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2))))*C46)-C35*(-ahR*aZAI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)-ahR*aZAI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)-ahR*aZAI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)-ahR*aZAI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)+gL*gR*(MZ*MZ)*(aZAI*(gL+gR)*(ahR*MZ*wZ*((M1*M1)+(M2*M2))))*C45*C46+C36*(gL*gR*(MZ*MZ)*(aZAI*(gL+gR)*(ahR*MZ*wZ*((M1*M1)+(M2*M2))))*C46+C45*((MZ*MZ)*(-aZAI*((gL*gL*gL)+(gR*gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2))))))-C34*((MZ*MZ)*(-aZAI*((gL*gL*gL)+(gR*gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2)))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aZAR_aZAR(LeptonVectors &leptons, double aZAR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aZAR_aZAdI(LeptonVectors &leptons, double aZAR, double aZAdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI)-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI+aZAR)*(aZAdI+aZAR)))*(gL*gL)+(((aZAdI-aZAR)*(aZAdI-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(2*aZAdI*aZAR*(gL-gR)*(gL+gR)*(M1-M2)*(M1+M2)*(MZ*MZ)*((M1*M1)*(2*(M2*M2)-(MZ*MZ)-(wZ*wZ))-(M2*M2)*((MZ*MZ)+(wZ*wZ)))+(aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))+((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI-aZAR)*(aZAdI-aZAR)))*(gL*gL)+(((aZAdI+aZAR)*(aZAdI+aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI)-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI)-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(-2*aZAdI*aZAR*(gL-gR)*(gL+gR)*(M1-M2)*(M1+M2)*(MZ*MZ)*((M1*M1)*(2*(M2*M2)-(MZ*MZ)-(wZ*wZ))-(M2*M2)*((MZ*MZ)+(wZ*wZ)))+(aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))+((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI)-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aZAR_aZAdR(LeptonVectors &leptons, double aZAR, double aZAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR)-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR))+((aZAR)*(aZAR)))*(gL*gL)+(((aZAdR)*(aZAdR))+((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))+((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR))+((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAdR)*(aZAdR))+((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR)-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+4*(aZAdR*aZAR)*E3456*((2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C36*C45-(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46-((gL-gR)*(gL-gR))*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))*C34*C56)+(C36*C36)*(-2*((aZAdR*aZAdR)-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))+((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR)-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aZAR_aZI(LeptonVectors &leptons, double aZAR, double aZI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-2*aZAR*aZI*gR*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)-2*aZAR*aZI*MZ*wZ*(gL*gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)-2*aZAR*aZI*gL*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)-2*aZAR*aZI*MZ*wZ*(gR*gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)-2*aZAR*aZI*gR*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)-2*aZAR*aZI*MZ*wZ*(gL*gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)-2*aZAR*aZI*gL*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)-2*aZAR*aZI*MZ*wZ*(gR*gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)-2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)))*(C34*C34)*(C56*C56)+C34*(-2*gL*gR*(MZ*wZ*((((aZAR)*(aZI))*gL+(aZAR*(aZI))*gR)*(M1*M1)+((aZAR*(aZI))*gL+((aZAR)*(aZI))*gR)*(M2*M2)))*(C36*C36)+2*gL*gR*(MZ*wZ*((((-aZAR)*(aZI))*gL-((aZAR)*(aZI))*gR)*(M1*M1)-(((aZAR)*(aZI))*gL+(aZAR*(aZI))*gR)*(M2*M2)))*(C45*C45)+C36*(4*((gL*gL*gL)+(gR*gR*gR))*((aZAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)))*C45)+C46*(2*(MZ*wZ*((-aZAR)*(aZI)*(gL*gL*gL)-(aZAR)*(aZI)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C46))*C56+(C35*C35)*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)))*(C46*C46)+2*(-MZ*wZ*((aZAR)*(aZI)*(gL*gL*gL)-(-aZAR)*(aZI)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C34*C56)-C35*(C36*(C45*(-4*(gL+gR)*((gL*gL)+(gR*gR))*((aZAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)))*C46))-C34*(4*gL*gR*(gL+gR)*((aZAR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI))*C45)+C35*(4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAR_aZR(LeptonVectors &leptons, double aZAR, double aZR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*aZAR*aZR*gR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-4*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-4*aZAR*aZR*gL*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-4*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+2*aZAR*aZR*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAR*aZR*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAR*aZR*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAR*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAR*aZR*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)+2*aZAR*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*(gL+gR)*((gL*gL)+(gR*gR))*((+aZAR*aZR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*(C34*C34)*(C56*C56)+C34*(-2*gL*gR*(2*aZAR*aZR*gL*(M1*M1)*(M2*M2)+2*aZAR*aZR*gR*(M1*M1)*(M2*M2)-aZAR*aZR*gL*(M1*M1)*(MZ*MZ)-aZAR*aZR*gR*(M1*M1)*(MZ*MZ)-aZAR*aZR*gL*(M2*M2)*(MZ*MZ)-aZAR*aZR*gR*(M2*M2)*(MZ*MZ))*(C36*C36)+2*gL*gR*(-2*aZAR*aZR*gL*(M1*M1)*(M2*M2)-2*aZAR*aZR*gR*(M1*M1)*(M2*M2)+aZAR*aZR*gL*(M1*M1)*(MZ*MZ)+aZAR*aZR*gR*(M1*M1)*(MZ*MZ)+aZAR*aZR*gL*(M2*M2)*(MZ*MZ)+aZAR*aZR*gR*(M2*M2)*(MZ*MZ))*(C45*C45)+C36*(4*((gL*gL*gL)+(gR*gR*gR))*((+aZAR*aZR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C45)+C46*(2*(-2*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2)-2*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2)+aZAR*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ)+aZAR*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ)+aZAR*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ)+aZAR*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ))*C46))*C56+(C35*C35)*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((+aZAR*aZR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*(C46*C46)+2*(-2*aZAR*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2)-2*aZAR*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2)+aZAR*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ)+aZAR*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ)+aZAR*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ)+aZAR*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ))*C34*C56)-C35*(C36*(C45*(-4*(gL+gR)*((gL*gL)+(gR*gR))*((+aZAR*aZR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46))-C34*(4*gL*gR*(gL+gR)*((+aZAR*aZR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZR*aZR))*C45)+C35*(4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAR_aZdI(LeptonVectors &leptons, double aZAR, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(-2*gL*gR*(-aZAR*aZdI*gL*(M1*M1)*(MZ*MZ)+aZAR*aZdI*gR*(M1*M1)*(MZ*MZ)+aZAR*aZdI*gL*(M2*M2)*(MZ*MZ)-aZAR*aZdI*gR*(M2*M2)*(MZ*MZ))*(C36*C36)+2*gL*gR*(-aZAR*aZdI*gL*(M1*M1)*(MZ*MZ)+aZAR*aZdI*gR*(M1*M1)*(MZ*MZ)+aZAR*aZdI*gL*(M2*M2)*(MZ*MZ)-aZAR*aZdI*gR*(M2*M2)*(MZ*MZ))*(C45*C45)+C46*(2*(2*aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2)-2*aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2)-aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ)+aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ)-aZAR*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ)+aZAR*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ))*C46))*C56+E3456*(C36*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAR*aZdI)*MZ*wZ*((M1*M1)+(M2*M2)))*C45)+C35*(2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAR*aZdI)*MZ*wZ*((M1*M1)+(M2*M2)))*C46)+2*(gL+gR)*((gL-gR)*(gL-gR))*((aZAR*aZdI)*MZ*wZ*((M1*M1)+(M2*M2)))*C34*C56)+(C35*C35)*(2*(-2*aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2)+2*aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2)+aZAR*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ)-aZAR*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ)+aZAR*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ)-aZAR*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+C35*(4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAR_aZdR(LeptonVectors &leptons, double aZAR, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(-2*gL*gR*(MZ*wZ*((((aZAR)*(-aZdR))*gL+(aZAR*(aZdR))*gR)*(M1*M1)+((aZAR*(aZdR))*gL+((aZAR)*(-aZdR))*gR)*(M2*M2)))*(C36*C36)+2*gL*gR*(MZ*wZ*((((-aZAR)*(aZdR))*gL-((aZAR)*(-aZdR))*gR)*(M1*M1)-(((aZAR)*(-aZdR))*gL+(aZAR*(aZdR))*gR)*(M2*M2)))*(C45*C45)+C46*(2*(MZ*wZ*((-aZAR)*(aZdR)*(gL*gL*gL)-(aZAR)*(-aZdR)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C46))*C56+E3456*(C36*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAR*aZdR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C45)+C35*(2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAR*aZdR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)+2*(gL+gR)*((gL-gR)*(gL-gR))*((aZAR*aZdR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C34*C56)+(C35*C35)*(2*(-MZ*wZ*((aZAR)*(-aZdR)*(gL*gL*gL)-(-aZAR)*(aZdR)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+C35*(4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAR_ahI(LeptonVectors &leptons, double aZAR, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-ahI*aZAR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36-0-ahI*aZAR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36-0-ahI*aZAR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36-ahI*aZAR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36-0-ahI*aZAR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45-ahI*aZAR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45-ahI*aZAR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45-0-ahI*aZAR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45+ahI*aZAR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46+ahI*aZAR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46+ahI*aZAR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+ahI*aZAR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+C34*(gL*gR*(MZ*MZ)*(-aZAR*(gL+gR)*(ahI*MZ*wZ*((M1*M1)+(M2*M2))))*C45+C36*(gL*gR*(MZ*MZ)*(-aZAR*(gL+gR)*(ahI*MZ*wZ*((M1*M1)+(M2*M2)))))+C46*((MZ*MZ)*(((-aZAR)*(gL*gL*gL)-(aZAR)*(gR*gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2))))))*C56+E3456*(-ahI*aZAR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45+ahI*aZAR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45+ahI*aZAR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45-ahI*aZAR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45+C36*(gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(ahI*aZAR*MZ)))-2*ahI*aZAR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46+2*ahI*aZAR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46+ahI*aZAR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-0-ahI*aZAR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46+ahI*aZAR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46-0-ahI*aZAR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46+C35*(-((MZ*MZ)*(-(aZAR*((gL*gL*gL)-(gR*gR*gR))*(2*ahI*(M1*M1)*(M2*M2)-ahI*((M1*M1)+(M2*M2))*(MZ*MZ)))))))+(C35*C35)*((MZ*MZ)*((-((aZAR)*(gL*gL*gL))-(aZAR)*(gR*gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2))))*C46)-C35*(ahI*aZAR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)+ahI*aZAR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)+ahI*aZAR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)+ahI*aZAR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)+gL*gR*(MZ*MZ)*(-aZAR*(gL+gR)*(ahI*MZ*wZ*((M1*M1)+(M2*M2))))*C45*C46+C36*(gL*gR*(MZ*MZ)*(-aZAR*(gL+gR)*(ahI*MZ*wZ*((M1*M1)+(M2*M2))))*C46+C45*((MZ*MZ)*((-((aZAR)*(gL*gL*gL))-(aZAR)*(gR*gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2))))))-C34*((MZ*MZ)*((-((aZAR)*(gL*gL*gL))-(aZAR)*(gR*gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aZAR_ahR(LeptonVectors &leptons, double aZAR, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-6*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAR*aZAR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)+2*(aZAR*aZAR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAR)*(aZAR)))*(gL*gL)+(((-aZAR)*(-aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((-aZAR)*(-aZAR)))*(gL*gL)+(((aZAR)*(aZAR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*(-(aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*(-(aZAR*aZAR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+(((aZAR*aZAR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*(-(aZAR*aZAR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-2*ahR*aZAR*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*C36-0-2*ahR*aZAR*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C45*C45)*C36+ahR*aZAR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36-0-2*ahR*aZAR*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*C45-0-2*ahR*aZAR*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C36*C36)*C45+ahR*aZAR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+ahR*aZAR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+ahR*aZAR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+ahR*aZAR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+2*ahR*aZAR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46+2*ahR*aZAR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46-0-ahR*aZAR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-ahR*aZAR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-ahR*aZAR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-ahR*aZAR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46+C34*(gL*gR*(MZ*MZ)*(-aZAR*(gL+gR)*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ)))*C45+C36*(gL*gR*(MZ*MZ)*(-aZAR*(gL+gR)*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ))))+C46*((MZ*MZ)*(((-aZAR)*(gL*gL*gL)-(aZAR)*(gR*gR*gR))*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ)))))*C56+E3456*(-ahR*aZAR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45+ahR*aZAR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45+ahR*aZAR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45-ahR*aZAR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45+C36*(gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(ahR*aZAR*wZ)))+ahR*aZAR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46-0-ahR*aZAR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46+ahR*aZAR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46-0-ahR*aZAR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46+C35*(-((MZ*MZ)*(-(aZAR*((gL*gL*gL)-(gR*gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2))))))))+(C35*C35)*((MZ*MZ)*((-((aZAR)*(gL*gL*gL))-(aZAR)*(gR*gR*gR))*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)-C35*(2*ahR*aZAR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)+2*ahR*aZAR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)-ahR*aZAR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)-ahR*aZAR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)-ahR*aZAR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)-ahR*aZAR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)+gL*gR*(MZ*MZ)*(-aZAR*(gL+gR)*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ)))*C45*C46+C36*(gL*gR*(MZ*MZ)*(-aZAR*(gL+gR)*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ)))*C46+C45*((MZ*MZ)*((-((aZAR)*(gL*gL*gL))-(aZAR)*(gR*gR*gR))*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ)))))-C34*((MZ*MZ)*((-((aZAR)*(gL*gL*gL))-(aZAR)*(gR*gR*gR))*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aZAdI_aZAdI(LeptonVectors &leptons, double aZAdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aZAdI_aZAdR(LeptonVectors &leptons, double aZAdI, double aZAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI)+(aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR))+((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdR)*(aZAdR))+((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))+(aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR))+((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdR)*(aZAdR))+((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI)+(aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI)+(aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))+(aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI)+(aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aZAdI_aZI(LeptonVectors &leptons, double aZAdI, double aZI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(-2*gL*gR*(MZ*wZ*((((aZAdI)*(aZI))*gL+(-(aZAdI*(aZI)))*gR)*(M1*M1)+((-(aZAdI*(aZI)))*gL+((aZAdI)*(aZI))*gR)*(M2*M2)))*(C36*C36)+2*gL*gR*(MZ*wZ*((((aZAdI)*(aZI))*gL-((aZAdI)*(aZI))*gR)*(M1*M1)-(((aZAdI)*(aZI))*gL+(-(aZAdI*(aZI)))*gR)*(M2*M2)))*(C45*C45)+C46*(2*(MZ*wZ*((aZAdI)*(aZI)*(gL*gL*gL)-(aZAdI)*(aZI)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C46))*C56+E3456*(C36*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAdI*aZI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C45)+C35*(2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAdI*aZI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)+2*(gL+gR)*((gL-gR)*(gL-gR))*((aZAdI*aZI)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C34*C56)+(C35*C35)*(2*(-MZ*wZ*((aZAdI)*(aZI)*(gL*gL*gL)-(aZAdI)*(aZI)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI))*C45)+C35*(4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAdI_aZR(LeptonVectors &leptons, double aZAdI, double aZR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(-2*gL*gR*(-aZAdI*aZR*gL*(M1*M1)*(MZ*MZ)+aZAdI*aZR*gR*(M1*M1)*(MZ*MZ)+aZAdI*aZR*gL*(M2*M2)*(MZ*MZ)-aZAdI*aZR*gR*(M2*M2)*(MZ*MZ))*(C36*C36)+2*gL*gR*(-aZAdI*aZR*gL*(M1*M1)*(MZ*MZ)+aZAdI*aZR*gR*(M1*M1)*(MZ*MZ)+aZAdI*aZR*gL*(M2*M2)*(MZ*MZ)-aZAdI*aZR*gR*(M2*M2)*(MZ*MZ))*(C45*C45)+C46*(2*(2*aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2)-2*aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2)-aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ)+aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ)-aZAdI*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ)+aZAdI*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ))*C46))*C56+E3456*(C36*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((-aZAdI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)))*C45)+C35*(2*(gL+gR)*((gL*gL)+(gR*gR))*((-aZAdI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)))*C46)+2*(gL+gR)*((gL-gR)*(gL-gR))*((-aZAdI*aZR)*MZ*wZ*((M1*M1)+(M2*M2)))*C34*C56)+(C35*C35)*(2*(-2*aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(M2*M2)+2*aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(M2*M2)+aZAdI*aZR*(gL*gL*gL)*(M1*M1)*(MZ*MZ)-aZAdI*aZR*(gR*gR*gR)*(M1*M1)*(MZ*MZ)+aZAdI*aZR*(gL*gL*gL)*(M2*M2)*(MZ*MZ)-aZAdI*aZR*(gR*gR*gR)*(M2*M2)*(MZ*MZ))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZR*aZR))*C45)+C35*(4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAdI_aZdI(LeptonVectors &leptons, double aZAdI, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*aZAdI*aZdI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+4*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+4*aZAdI*aZdI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+4*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-2*aZAdI*aZdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdI*aZdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdI*aZdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdI*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdI*aZdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdI*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*(gL+gR)*((gL*gL)+(gR*gR))*((-(aZAdI*aZdI))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*(C34*C34)*(C56*C56)+C34*(-2*gL*gR*(2*aZAdI*aZdI*gL*(M1*M1)*(M2*M2)+2*aZAdI*aZdI*gR*(M1*M1)*(M2*M2)-aZAdI*aZdI*gL*(M1*M1)*(MZ*MZ)-aZAdI*aZdI*gR*(M1*M1)*(MZ*MZ)-aZAdI*aZdI*gL*(M2*M2)*(MZ*MZ)-aZAdI*aZdI*gR*(M2*M2)*(MZ*MZ))*(C36*C36)+2*gL*gR*(-2*aZAdI*aZdI*gL*(M1*M1)*(M2*M2)-2*aZAdI*aZdI*gR*(M1*M1)*(M2*M2)+aZAdI*aZdI*gL*(M1*M1)*(MZ*MZ)+aZAdI*aZdI*gR*(M1*M1)*(MZ*MZ)+aZAdI*aZdI*gL*(M2*M2)*(MZ*MZ)+aZAdI*aZdI*gR*(M2*M2)*(MZ*MZ))*(C45*C45)+C36*(4*((gL*gL*gL)+(gR*gR*gR))*((-(aZAdI*aZdI))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C45)+C46*(2*(-2*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2)-2*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2)+aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ)+aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ)+aZAdI*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ)+aZAdI*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ))*C46))*C56+(C35*C35)*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((-(aZAdI*aZdI))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*(C46*C46)+2*(-2*aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(M2*M2)-2*aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(M2*M2)+aZAdI*aZdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ)+aZAdI*aZdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ)+aZAdI*aZdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ)+aZAdI*aZdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ))*C34*C56)-C35*(C36*(C45*(-4*(gL+gR)*((gL*gL)+(gR*gR))*((-(aZAdI*aZdI))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46))-C34*(4*gL*gR*(gL+gR)*((-(aZAdI*aZdI))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+C35*(4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAdI_aZdR(LeptonVectors &leptons, double aZAdI, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-2*aZAdI*aZdR*gR*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)-2*aZAdI*aZdR*MZ*wZ*(gL*gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)-2*aZAdI*aZdR*gL*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)-2*aZAdI*aZdR*MZ*wZ*(gR*gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)-2*aZAdI*aZdR*gR*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)-2*aZAdI*aZdR*MZ*wZ*(gL*gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)-2*aZAdI*aZdR*gL*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)-2*aZAdI*aZdR*MZ*wZ*(gR*gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)-2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)))*(C34*C34)*(C56*C56)+C34*(-2*gL*gR*(MZ*wZ*((((aZAdI)*(-aZdR))*gL+(-(aZAdI*(aZdR)))*gR)*(M1*M1)+((-(aZAdI*(aZdR)))*gL+((aZAdI)*(-aZdR))*gR)*(M2*M2)))*(C36*C36)+2*gL*gR*(MZ*wZ*((((aZAdI)*(aZdR))*gL-((aZAdI)*(-aZdR))*gR)*(M1*M1)-(((aZAdI)*(-aZdR))*gL+(-(aZAdI*(aZdR)))*gR)*(M2*M2)))*(C45*C45)+C36*(4*((gL*gL*gL)+(gR*gR*gR))*((aZAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)))*C45)+C46*(2*(MZ*wZ*((aZAdI)*(aZdR)*(gL*gL*gL)-(aZAdI)*(-aZdR)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C46))*C56+(C35*C35)*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)))*(C46*C46)+2*(-MZ*wZ*((aZAdI)*(-aZdR)*(gL*gL*gL)-(aZAdI)*(aZdR)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C34*C56)-C35*(C36*(C45*(-4*(gL+gR)*((gL*gL)+(gR*gR))*((aZAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)))*C46))-C34*(4*gL*gR*(gL+gR)*((aZAdI*aZdR)*MZ*wZ*((M1*M1)+(M2*M2)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+C35*(4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAdI_ahI(LeptonVectors &leptons, double aZAdI, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(ahI*aZAdI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36-ahI*aZAdI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36-0-ahI*aZAdI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36+ahI*aZAdI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36-ahI*aZAdI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45+ahI*aZAdI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45+ahI*aZAdI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45-ahI*aZAdI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45-0-ahI*aZAdI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46+ahI*aZAdI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46-ahI*aZAdI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+ahI*aZAdI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+C34*(gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(ahI*aZAdI*wZ))*C45+C36*(gL*gR*(MZ*MZ)*((-gL+gR)*(M1-M2)*(M1+M2)*MZ*(ahI*aZAdI*wZ)))+C46*((MZ*MZ)*(((aZAdI)*(gL*gL*gL)-(aZAdI)*(gR*gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2))))))*C56+E3456*(-2*ahI*aZAdI*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C45-0-2*ahI*aZAdI*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C45+ahI*aZAdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45+ahI*aZAdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45+ahI*aZAdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45+ahI*aZAdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45+C36*(gL*gR*(MZ*MZ)*(aZAdI*(gL+gR)*(-2*ahI*(M1*M1)*(M2*M2)+ahI*((M1*M1)+(M2*M2))*(MZ*MZ))))+2*ahI*aZAdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46+2*ahI*aZAdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46-ahI*aZAdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-0-ahI*aZAdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-0-ahI*aZAdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46-0-ahI*aZAdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46+C35*(-((MZ*MZ)*(-aZAdI*((gL*gL*gL)+(gR*gR*gR))*(2*ahI*(M1*M1)*(M2*M2)-ahI*((M1*M1)+(M2*M2))*(MZ*MZ))))))+(C35*C35)*((MZ*MZ)*((-((aZAdI)*(gL*gL*gL))-(-aZAdI)*(gR*gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2))))*C46)-C35*(-ahI*aZAdI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)+ahI*aZAdI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)-ahI*aZAdI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)+ahI*aZAdI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)+gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(ahI*aZAdI*wZ))*C45*C46+C36*(gL*gR*(MZ*MZ)*((-gL+gR)*(M1-M2)*(M1+M2)*MZ*(ahI*aZAdI*wZ))*C46+C45*((MZ*MZ)*((-((aZAdI)*(gL*gL*gL))-(-aZAdI)*(gR*gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2))))))-C34*((MZ*MZ)*((-((aZAdI)*(gL*gL*gL))-(-aZAdI)*(gR*gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aZAdI_ahR(LeptonVectors &leptons, double aZAdI, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdI*aZAdI)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdI*aZAdI)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdI)*(aZAdI)))*(gL*gL)+(((aZAdI)*(aZAdI)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdI*aZAdI))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdI*aZAdI))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdI*aZAdI)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdI*aZAdI))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-ahR*aZAdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36-0-ahR*aZAdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAdI*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45-0-ahR*aZAdI*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45-ahR*aZAdI*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+ahR*aZAdI*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45-0-2*ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46+2*ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46+ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46+ahR*aZAdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-ahR*aZAdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46+C34*(gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(-(ahR*aZAdI*MZ)))*C45+C36*(gL*gR*(MZ*MZ)*((-gL+gR)*(M1-M2)*(M1+M2)*MZ*(-(ahR*aZAdI*MZ))))+C46*((MZ*MZ)*(((aZAdI)*(gL*gL*gL)-(aZAdI)*(gR*gR*gR))*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ)))))*C56+E3456*(ahR*aZAdI*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45+ahR*aZAdI*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45+ahR*aZAdI*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45+ahR*aZAdI*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45+C36*(gL*gR*(MZ*MZ)*(aZAdI*(gL+gR)*(ahR*MZ*wZ*((M1*M1)+(M2*M2)))))-ahR*aZAdI*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46-ahR*aZAdI*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46-ahR*aZAdI*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46-ahR*aZAdI*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46+C35*(-((MZ*MZ)*(-aZAdI*((gL*gL*gL)+(gR*gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2)))))))+(C35*C35)*((MZ*MZ)*((-((aZAdI)*(gL*gL*gL))-(-aZAdI)*(gR*gR*gR))*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)-C35*(-2*ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)+2*ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)+ahR*aZAdI*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)-ahR*aZAdI*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)+ahR*aZAdI*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)-ahR*aZAdI*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)+gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(-(ahR*aZAdI*MZ)))*C45*C46+C36*(gL*gR*(MZ*MZ)*((-gL+gR)*(M1-M2)*(M1+M2)*MZ*(-(ahR*aZAdI*MZ)))*C46+C45*((MZ*MZ)*((-((aZAdI)*(gL*gL*gL))-(-aZAdI)*(gR*gR*gR))*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ)))))-C34*((MZ*MZ)*((-((aZAdI)*(gL*gL*gL))-(-aZAdI)*(gR*gR*gR))*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aZAdR_aZAdR(LeptonVectors &leptons, double aZAdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-0;
}

double GetGeneralScalar_aZAdR_aZI(LeptonVectors &leptons, double aZAdR, double aZI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(-2*gL*gR*(aZAdR*aZI*gL*(M1*M1)*(MZ*MZ)-aZAdR*aZI*gR*(M1*M1)*(MZ*MZ)-aZAdR*aZI*gL*(M2*M2)*(MZ*MZ)+aZAdR*aZI*gR*(M2*M2)*(MZ*MZ))*(C36*C36)+2*gL*gR*(aZAdR*aZI*gL*(M1*M1)*(MZ*MZ)-aZAdR*aZI*gR*(M1*M1)*(MZ*MZ)-aZAdR*aZI*gL*(M2*M2)*(MZ*MZ)+aZAdR*aZI*gR*(M2*M2)*(MZ*MZ))*(C45*C45)+C46*(2*(-aZAdR*((aZI)*(gL*gL*gL)+(-aZI)*(gR*gR*gR))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46))*C56+E3456*(C36*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAdR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)))*C45)+C35*(2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAdR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)))*C46)+2*(gL+gR)*((gL-gR)*(gL-gR))*((aZAdR*aZI)*MZ*wZ*((M1*M1)+(M2*M2)))*C34*C56)+(C35*C35)*(2*(aZAdR*((aZI)*(gL*gL*gL)-(aZI)*(gR*gR*gR))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI))*C45)+C35*(4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAdR_aZR(LeptonVectors &leptons, double aZAdR, double aZR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(C34*(-2*gL*gR*(MZ*wZ*(((aZAdR*(aZR))*gL+(aZAdR*(-aZR))*gR)*(M1*M1)+((aZAdR*(-aZR))*gL+(aZAdR*(aZR))*gR)*(M2*M2)))*(C36*C36)+2*gL*gR*(MZ*wZ*(((aZAdR*(aZR))*gL-(aZAdR*(aZR))*gR)*(M1*M1)-((aZAdR*(aZR))*gL+(aZAdR*(-aZR))*gR)*(M2*M2)))*(C45*C45)+C46*(2*(aZAdR*MZ*wZ*((aZR)*(gL*gL*gL)-(aZR)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C46))*C56+E3456*(C36*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAdR*aZR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C45)+C35*(2*(gL+gR)*((gL*gL)+(gR*gR))*((aZAdR*aZR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)+2*(gL+gR)*((gL-gR)*(gL-gR))*((aZAdR*aZR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C34*C56)+(C35*C35)*(2*(-aZAdR*MZ*wZ*((aZR)*(gL*gL*gL)+(-aZR)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C34*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZR*aZR))*C45)+C35*(4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAdR_aZdI(LeptonVectors &leptons, double aZAdR, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(2*aZAdR*aZdI*gR*MZ*wZ*(gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)+2*aZAdR*aZdI*MZ*wZ*(gL*gL*gL)*(M1*M1)*(C36*C36)*(C45*C45)+2*aZAdR*aZdI*gL*MZ*wZ*(gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)+2*aZAdR*aZdI*MZ*wZ*(gR*gR*gR)*(M1*M1)*(C36*C36)*(C45*C45)+2*aZAdR*aZdI*gR*MZ*wZ*(gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)+2*aZAdR*aZdI*MZ*wZ*(gL*gL*gL)*(M2*M2)*(C36*C36)*(C45*C45)+2*aZAdR*aZdI*gL*MZ*wZ*(gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)+2*aZAdR*aZdI*MZ*wZ*(gR*gR*gR)*(M2*M2)*(C36*C36)*(C45*C45)-2*(gL+gR)*((gL*gL)+(gR*gR))*((-(aZAdR*aZdI))*MZ*wZ*((M1*M1)+(M2*M2)))*(C34*C34)*(C56*C56)+C34*(-2*gL*gR*(MZ*wZ*(((aZAdR*(aZdI))*gL+(aZAdR*(aZdI))*gR)*(M1*M1)+((aZAdR*(aZdI))*gL+(aZAdR*(aZdI))*gR)*(M2*M2)))*(C36*C36)+2*gL*gR*(MZ*wZ*(((aZAdR*(-aZdI))*gL-(aZAdR*(aZdI))*gR)*(M1*M1)-((aZAdR*(aZdI))*gL+(aZAdR*(aZdI))*gR)*(M2*M2)))*(C45*C45)+C36*(4*((gL*gL*gL)+(gR*gR*gR))*((-(aZAdR*aZdI))*MZ*wZ*((M1*M1)+(M2*M2)))*C45)+C46*(2*(aZAdR*MZ*wZ*((-aZdI)*(gL*gL*gL)-(aZdI)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C46))*C56+(C35*C35)*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((-(aZAdR*aZdI))*MZ*wZ*((M1*M1)+(M2*M2)))*(C46*C46)+2*(-aZAdR*MZ*wZ*((aZdI)*(gL*gL*gL)+(aZdI)*(gR*gR*gR))*((M1*M1)+(M2*M2)))*C34*C56)-C35*(C36*(C45*(-4*(gL+gR)*((gL*gL)+(gR*gR))*((-(aZAdR*aZdI))*MZ*wZ*((M1*M1)+(M2*M2)))*C46))-C34*(4*gL*gR*(gL+gR)*((-(aZAdR*aZdI))*MZ*wZ*((M1*M1)+(M2*M2)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+C35*(4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAdR_aZdR(LeptonVectors &leptons, double aZAdR, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(4*aZAdR*aZdR*gR*(gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+4*aZAdR*aZdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+4*aZAdR*aZdR*gL*(gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)+4*aZAdR*aZdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(C36*C36)*(C45*C45)-2*aZAdR*aZdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdR*aZdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdR*aZdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdR*aZdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdR*aZdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdR*aZdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdR*aZdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*aZAdR*aZdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ)*(C36*C36)*(C45*C45)-2*(gL+gR)*((gL*gL)+(gR*gR))*((-aZAdR*aZdR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*(C34*C34)*(C56*C56)+C34*(-2*gL*gR*(2*aZAdR*aZdR*gL*(M1*M1)*(M2*M2)+2*aZAdR*aZdR*gR*(M1*M1)*(M2*M2)-aZAdR*aZdR*gL*(M1*M1)*(MZ*MZ)-aZAdR*aZdR*gR*(M1*M1)*(MZ*MZ)-aZAdR*aZdR*gL*(M2*M2)*(MZ*MZ)-aZAdR*aZdR*gR*(M2*M2)*(MZ*MZ))*(C36*C36)+2*gL*gR*(-2*aZAdR*aZdR*gL*(M1*M1)*(M2*M2)-2*aZAdR*aZdR*gR*(M1*M1)*(M2*M2)+aZAdR*aZdR*gL*(M1*M1)*(MZ*MZ)+aZAdR*aZdR*gR*(M1*M1)*(MZ*MZ)+aZAdR*aZdR*gL*(M2*M2)*(MZ*MZ)+aZAdR*aZdR*gR*(M2*M2)*(MZ*MZ))*(C45*C45)+C36*(4*((gL*gL*gL)+(gR*gR*gR))*((-aZAdR*aZdR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C45)+C46*(2*(-aZAdR*((aZdR)*(gL*gL*gL)+(aZdR)*(gR*gR*gR))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46))*C56+(C35*C35)*(-2*(gL+gR)*((gL*gL)+(gR*gR))*((-aZAdR*aZdR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*(C46*C46)+2*(aZAdR*((-aZdR)*(gL*gL*gL)-(aZdR)*(gR*gR*gR))*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C34*C56)-C35*(C36*(C45*(-4*(gL+gR)*((gL*gL)+(gR*gR))*((-aZAdR*aZdR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46))-C34*(4*gL*gR*(gL+gR)*((-aZAdR*aZdR)*(2*(M1*M1)*(M2*M2)-((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+C35*(4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZAdR_ahI(LeptonVectors &leptons, double aZAdR, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(ahI*aZAdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36-ahI*aZAdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36-ahI*aZAdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36+ahI*aZAdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C45*C45)*C36-ahI*aZAdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+ahI*aZAdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+ahI*aZAdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45-ahI*aZAdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C36*C36)*C45+2*ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46-2*ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C36*C45*C46-ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46+ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C36*C45*C46-0-ahI*aZAdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46+ahI*aZAdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C36*C45*C46+C34*(gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(ahI*aZAdR*MZ))*C45+C36*(gL*gR*(MZ*MZ)*((-gL+gR)*(M1-M2)*(M1+M2)*MZ*(ahI*aZAdR*MZ)))+C46*((MZ*MZ)*(-(aZAdR*((gL*gL*gL)-(gR*gR*gR))*(2*ahI*(M1*M1)*(M2*M2)-ahI*((M1*M1)+(M2*M2))*(MZ*MZ))))))*C56+E3456*(-ahI*aZAdR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C45-0-ahI*aZAdR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C45-ahI*aZAdR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C45-ahI*aZAdR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C45+C36*(gL*gR*(MZ*MZ)*(-aZAdR*(gL+gR)*(ahI*MZ*wZ*((M1*M1)+(M2*M2)))))+ahI*aZAdR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C46+ahI*aZAdR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C46+ahI*aZAdR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C46+ahI*aZAdR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C46+C35*(-((MZ*MZ)*((-((aZAdR)*(gL*gL*gL))-(aZAdR)*(gR*gR*gR))*(ahI*MZ*wZ*((M1*M1)+(M2*M2)))))))+(C35*C35)*((MZ*MZ)*(aZAdR*((gL*gL*gL)-(gR*gR*gR))*(2*ahI*(M1*M1)*(M2*M2)-ahI*((M1*M1)+(M2*M2))*(MZ*MZ)))*C46)-C35*(2*ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)-2*ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(C46*C46)-ahI*aZAdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)+ahI*aZAdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*(C46*C46)-ahI*aZAdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)+ahI*aZAdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C46*C46)+gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(ahI*aZAdR*MZ))*C45*C46+C36*(gL*gR*(MZ*MZ)*((-gL+gR)*(M1-M2)*(M1+M2)*MZ*(ahI*aZAdR*MZ))*C46+C45*((MZ*MZ)*(aZAdR*((gL*gL*gL)-(gR*gR*gR))*(2*ahI*(M1*M1)*(M2*M2)-ahI*((M1*M1)+(M2*M2))*(MZ*MZ)))))-C34*((MZ*MZ)*(aZAdR*((gL*gL*gL)-(gR*gR*gR))*(2*ahI*(M1*M1)*(M2*M2)-ahI*((M1*M1)+(M2*M2))*(MZ*MZ))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aZAdR_ahR(LeptonVectors &leptons, double aZAdR, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+((el*el)*(1.0/(M1*M1*M1*M1))*(1.0/(M2*M2*M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)-6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2*M2*M2)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)+6*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ*MZ*MZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1*M1*M1)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-4*gL*gR*(aZAdR*aZAdR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gL*gL)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*(aZAdR*aZAdR)*(gR*gR)*(M2*M2*M2*M2)*(MZ*MZ)*(wZ*wZ)*(C35*C35)*(C46*C46)-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C34*C34)*(C56*C56)+C34*(((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C35*C35)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*(C45*C45)+((((aZAdR)*(aZAdR)))*(gL*gL)+(((aZAdR)*(aZAdR)))*(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*(C46*C46)+2*((aZAdR*aZAdR))*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46)*C56+(C36*C36)*(-2*((aZAdR*aZAdR))*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*(C45*C45)+((aZAdR*aZAdR)*(4*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*(-2*(M1*M1)*(M2*M2*M2*M2)*(MZ*MZ)+(M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(2*(M2*M2*M2*M2)-2*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))))*C34*C56)+2*((aZAdR*aZAdR))*C36*C45*(2*(2*gL*gR*(M1*M1)*(M2*M2)*((M1-MZ)*(M2-MZ)*(M1+MZ)*(M2+MZ)+(MZ*MZ)*(wZ*wZ))+(gL*gL)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ)))+(gR*gR)*((M2*M2*M2*M2)*(MZ*MZ)*((MZ*MZ)+(wZ*wZ))+(M1*M1)*(M2*M2)*(MZ*MZ)*(-3*(M2*M2)+(MZ*MZ)+(wZ*wZ))+(M1*M1*M1*M1)*(3*(M2*M2*M2*M2)-3*(M2*M2)*(MZ*MZ)+(MZ*MZ*MZ*MZ)+(MZ*MZ)*(wZ*wZ))))*C35*C46+((gL*gL)+(gR*gR))*((MZ*MZ)*(wZ*wZ)*((M1*M1+M2*M2)*(M1*M1+M2*M2))+pow(-2*(M1*M1)*(M2*M2)+((M1*M1)+(M2*M2))*(MZ*MZ),2))*C34*C56)))/8192.-(el*(1.0/(M1*M1))*(1.0/(M2*M2))*pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(ahR*aZAdR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36-ahR*aZAdR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C45*C45)*C36-ahR*aZAdR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36+ahR*aZAdR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C45*C45)*C36-ahR*aZAdR*gR*wZ*(gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45+ahR*aZAdR*gL*wZ*(gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C36*C36)*C45+ahR*aZAdR*gR*wZ*(gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45-ahR*aZAdR*gL*wZ*(gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C36*C36)*C45-ahR*aZAdR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46+ahR*aZAdR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*C36*C45*C46-0-ahR*aZAdR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+ahR*aZAdR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*C36*C45*C46+C34*(gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(ahR*aZAdR*wZ))*C45+C36*(gL*gR*(MZ*MZ)*((-gL+gR)*(M1-M2)*(M1+M2)*MZ*(ahR*aZAdR*wZ)))+C46*((MZ*MZ)*(-(aZAdR*((gL*gL*gL)-(gR*gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2)))))))*C56+E3456*(-2*ahR*aZAdR*gR*(gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C45-0-2*ahR*aZAdR*gL*(gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C45+ahR*aZAdR*gR*(gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45+ahR*aZAdR*gL*(gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C45+ahR*aZAdR*gR*(gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45+ahR*aZAdR*gL*(gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C45+C36*(gL*gR*(MZ*MZ)*(-aZAdR*(gL+gR)*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ))))+2*ahR*aZAdR*(gL*gL*gL)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46+2*ahR*aZAdR*(gR*gR*gR)*(M1*M1)*(M2*M2)*(MZ*MZ)*C46-0-ahR*aZAdR*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-0-ahR*aZAdR*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ*MZ)*C46-ahR*aZAdR*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46-0-ahR*aZAdR*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ*MZ)*C46+C35*(-((MZ*MZ)*((-((aZAdR)*(gL*gL*gL))-(aZAdR)*(gR*gR*gR))*(2*ahR*(M1*M1)*(M2*M2)-ahR*((M1*M1)+(M2*M2))*(MZ*MZ))))))+(C35*C35)*((MZ*MZ)*(aZAdR*((gL*gL*gL)-(gR*gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2))))*C46)-C35*(-ahR*aZAdR*wZ*(gL*gL*gL)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)+ahR*aZAdR*wZ*(gR*gR*gR)*(M1*M1)*(MZ*MZ*MZ)*(C46*C46)-ahR*aZAdR*wZ*(gL*gL*gL)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)+ahR*aZAdR*wZ*(gR*gR*gR)*(M2*M2)*(MZ*MZ*MZ)*(C46*C46)+gL*gR*(MZ*MZ)*((gL-gR)*(M1-M2)*(M1+M2)*MZ*(ahR*aZAdR*wZ))*C45*C46+C36*(gL*gR*(MZ*MZ)*((-gL+gR)*(M1-M2)*(M1+M2)*MZ*(ahR*aZAdR*wZ))*C46+C45*((MZ*MZ)*(aZAdR*((gL*gL*gL)-(gR*gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2))))))-C34*((MZ*MZ)*(aZAdR*((gL*gL*gL)-(gR*gR*gR))*(-ahR*MZ*wZ*((M1*M1)+(M2*M2)))))*C56)))/8192.+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_aZI_aZI(LeptonVectors &leptons, double aZI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI))*C45)+C35*(4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZI_aZR(LeptonVectors &leptons, double aZI, double aZR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI)+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI))+((aZR)*(aZR)))*(gL*gL*gL*gL)+(((aZI)*(aZI))+((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI))+((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI))+((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI)+(aZR*aZR))*C45)+C35*(4*(-(aZI*aZI)-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI)+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI)+(aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZI*aZI)+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI)+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZI_aZdI(LeptonVectors &leptons, double aZI, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))+(aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI)+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((-aZI)*(-aZI))+((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZI)*(aZI))+((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI))+((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI))+((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI)+(aZI*aZI))*C45)+C35*(4*((aZdI*aZdI)-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI)+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI)+(aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+E3456*(2*C36*((aZdI*aZI)*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C45)+C35*(-2*(aZdI*aZI)*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(aZdI*aZI)*((gL*gL-gR*gR)*(gL*gL-gR*gR))*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI)+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI)+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZI_aZdR(LeptonVectors &leptons, double aZI, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR)+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR-aZI)*(aZdR-aZI)))*(gL*gL*gL*gL)+(((aZdR+aZI)*(aZdR+aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR+aZI)*(aZdR+aZI)))*(gL*gL*gL*gL)+(((aZdR-aZI)*(aZdR-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR)+(aZI*aZI))*C45)+C35*(4*((aZdR*aZdR)-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR)+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR)+(aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR)+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR)+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZI_ahI(LeptonVectors &leptons, double aZI, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+ahI*aZI*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35+ahI*aZI*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35+ahI*aZI*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46+ahI*aZI*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46+(ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46-2*ahI*aZI*(gL*gL)*(gR*gR)*(MZ*MZ)*C35*C45*C46+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*((ahI*aZI)*(MZ*MZ)+((aZI*aZI))*C45)+((ahI*(aZI))*(gL*gL*gL*gL)+(ahI*(aZI))*(gR*gR*gR*gR))*(MZ*MZ)*C46+C35*(((ahI*(aZI))*(gL*gL*gL*gL)+(ahI*(aZI))*(gR*gR*gR*gR))*(MZ*MZ)+4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*(ahI*aZI)*(gL*gL)*(gR*gR)*(MZ*MZ)*C45+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(2*(ahI*aZI)*(gL*gL)*(gR*gR)*(MZ*MZ)*(C45*C45)+2*(ahI*aZI)*(gL*gL)*(gR*gR)*(MZ*MZ)*(-(C35*C46)+C34*C56)+C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)-((ahI*(aZI))*(gL*gL*gL*gL)+(ahI*(aZI))*(gR*gR*gR*gR))*(MZ*MZ)*C46+C35*((-((ahI*(aZI))*(gL*gL*gL*gL))-(ahI*(aZI))*(gR*gR*gR*gR))*(MZ*MZ)-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZI_ahR(LeptonVectors &leptons, double aZI, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZI*aZI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZI*aZI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZI*aZI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+(ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C34*(((((-aZI)*(-aZI)))*(gL*gL*gL*gL)+(((aZI)*(aZI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZI)*(aZI)))*(gL*gL*gL*gL)+(((-aZI)*(-aZI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZI*aZI))*C45)+C35*(4*(-(aZI*aZI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZI*aZI))*(gL*gL)*(gR*gR)*C34*C56)+E3456*((MZ*MZ)*(-((ahR*(aZI))*(gL*gL*gL*gL)+(ahR*(-aZI))*(gR*gR*gR*gR))*C46)+C35*(((ahR*(aZI))*(gL*gL*gL*gL)-(ahR*(aZI))*(gR*gR*gR*gR))*(MZ*MZ)))+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)+C35*(-2*(+(aZI*aZI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZI*aZI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZR_aZR(LeptonVectors &leptons, double aZR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZR*aZR))*C45)+C35*(4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZR_aZdI(LeptonVectors &leptons, double aZR, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))+(aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI)+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdI+aZR)*(aZdI+aZR)))*(gL*gL*gL*gL)+(((aZdI-aZR)*(aZdI-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI-aZR)*(aZdI-aZR)))*(gL*gL*gL*gL)+(((aZdI+aZR)*(aZdI+aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI)+(aZR*aZR))*C45)+C35*(4*((aZdI*aZdI)-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI)+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI)+(aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI)+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI)+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZR_aZdR(LeptonVectors &leptons, double aZR, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR)+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR))+((aZR)*(aZR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR))+((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR))+((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR))+((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR)+(aZR*aZR))*C45)+C35*(4*((aZdR*aZdR)-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR)+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR)+(aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+E3456*(2*C36*((aZdR*aZR)*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C45)+C35*(-2*(aZdR*aZR)*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(aZdR*aZR)*((gL*gL-gR*gR)*(gL*gL-gR*gR))*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR)+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR)+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZR_ahI(LeptonVectors &leptons, double aZR, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+(ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZR*aZR))*C45)+C35*(4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+E3456*((MZ*MZ)*(-((ahI*(-aZR))*(gL*gL*gL*gL)+(ahI*(aZR))*(gR*gR*gR*gR))*C46)+C35*(((-ahI*(aZR))*(gL*gL*gL*gL)-(ahI*(-aZR))*(gR*gR*gR*gR))*(MZ*MZ)))+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)+C35*(-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZR_ahR(LeptonVectors &leptons, double aZR, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((aZR*aZR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)+2*(aZR*aZR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)+(aZR*aZR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+ahR*aZR*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35+ahR*aZR*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35+ahR*aZR*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46+ahR*aZR*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46+(ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46-0-2*ahR*aZR*(gL*gL)*(gR*gR)*(MZ*MZ)*C35*C45*C46+C34*(((((aZR)*(aZR)))*(gL*gL*gL*gL)+(((-aZR)*(-aZR)))*(gR*gR*gR*gR))*(C35*C35)+((((-aZR)*(-aZR)))*(gL*gL*gL*gL)+(((aZR)*(aZR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*((ahR*aZR)*(MZ*MZ)+((aZR*aZR))*C45)+((ahR*(aZR))*(gL*gL*gL*gL)+(ahR*(aZR))*(gR*gR*gR*gR))*(MZ*MZ)*C46+C35*(((ahR*(aZR))*(gL*gL*gL*gL)+(ahR*(aZR))*(gR*gR*gR*gR))*(MZ*MZ)+4*(-(aZR*aZR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*(ahR*aZR)*(gL*gL)*(gR*gR)*(MZ*MZ)*C45+2*((aZR*aZR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(2*(ahR*aZR)*(gL*gL)*(gR*gR)*(MZ*MZ)*(C45*C45)+2*(ahR*aZR)*(gL*gL)*(gR*gR)*(MZ*MZ)*(-(C35*C46)+C34*C56)+C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)-((ahR*(aZR))*(gL*gL*gL*gL)+(ahR*(aZR))*(gR*gR*gR*gR))*(MZ*MZ)*C46+C35*((-((ahR*(aZR))*(gL*gL*gL*gL))-(ahR*(aZR))*(gR*gR*gR*gR))*(MZ*MZ)-2*(+(aZR*aZR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(+(aZR*aZR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZdI_aZdI(LeptonVectors &leptons, double aZdI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+C35*(4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZdI_aZdR(LeptonVectors &leptons, double aZdI, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI)-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR))+((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR))+((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR))+((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR))+((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI)+(aZdR*aZdR))*C45)+C35*(4*((aZdI*aZdI)+(aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI)-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI)+(aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdI*aZdI)-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI)-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZdI_ahI(LeptonVectors &leptons, double aZdI, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+(ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+C35*(4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+E3456*(2*C36*((ahI*aZdI)*(gL*gL)*(gR*gR)*(MZ*MZ))+(MZ*MZ)*(2*(ahI*aZdI)*(gL*gL)*(gR*gR)*C45-((ahI*(aZdI))*(gL*gL*gL*gL)+(ahI*(aZdI))*(gR*gR*gR*gR))*C46)+C35*(((-ahI*(aZdI))*(gL*gL*gL*gL)-(ahI*(aZdI))*(gR*gR*gR*gR))*(MZ*MZ)))+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)+C35*(-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZdI_ahR(LeptonVectors &leptons, double aZdI, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-((aZdI*aZdI)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46))-2*(aZdI*aZdI)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdI*aZdI)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)-ahR*aZdI*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35+ahR*aZdI*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35+ahR*aZdI*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46-0-ahR*aZdI*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46+(ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C34*(((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdI)*(aZdI)))*(gL*gL*gL*gL)+(((aZdI)*(aZdI)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdI*aZdI))*C45)+((ahR*(-aZdI))*(gL*gL*gL*gL)+(ahR*(aZdI))*(gR*gR*gR*gR))*(MZ*MZ)*C46+C35*(((ahR*(aZdI))*(gL*gL*gL*gL)+(ahR*(-aZdI))*(gR*gR*gR*gR))*(MZ*MZ)+4*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdI*aZdI))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)-((ahR*(-aZdI))*(gL*gL*gL*gL)+(ahR*(aZdI))*(gR*gR*gR*gR))*(MZ*MZ)*C46+C35*((-((ahR*(aZdI))*(gL*gL*gL*gL))-(ahR*(-aZdI))*(gR*gR*gR*gR))*(MZ*MZ)-2*(-(aZdI*aZdI))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdI*aZdI))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZdR_aZdR(LeptonVectors &leptons, double aZdR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+C35*(4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(C35*(-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZdR_ahI(LeptonVectors &leptons, double aZdR, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+ahI*aZdR*(gL*gL*gL*gL)*(MZ*MZ)*(C46*C46)*C35-ahI*aZdR*(gR*gR*gR*gR)*(MZ*MZ)*(C46*C46)*C35-ahI*aZdR*(gL*gL*gL*gL)*(MZ*MZ)*(C35*C35)*C46+ahI*aZdR*(gR*gR*gR*gR)*(MZ*MZ)*(C35*C35)*C46+(ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+((ahI*(aZdR))*(gL*gL*gL*gL)+(ahI*(-aZdR))*(gR*gR*gR*gR))*(MZ*MZ)*C46+C35*(((ahI*(-aZdR))*(gL*gL*gL*gL)+(ahI*(aZdR))*(gR*gR*gR*gR))*(MZ*MZ)+4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)-((ahI*(aZdR))*(gL*gL*gL*gL)+(ahI*(-aZdR))*(gR*gR*gR*gR))*(MZ*MZ)*C46+C35*((-((ahI*(-aZdR))*(gL*gL*gL*gL))-(ahI*(aZdR))*(gR*gR*gR*gR))*(MZ*MZ)-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_aZdR_ahR(LeptonVectors &leptons, double aZdR, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*(-(aZdR*aZdR)*(gL*gL*gL*gL)*(C35*C35)*(C46*C46)-2*(aZdR*aZdR)*(gL*gL)*(gR*gR)*(C35*C35)*(C46*C46)-(aZdR*aZdR)*(gR*gR*gR*gR)*(C35*C35)*(C46*C46)+(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C34*C34)*(C56*C56)+(ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C34*(((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C35*C35)+((((aZdR)*(aZdR)))*(gL*gL*gL*gL)+(((aZdR)*(aZdR)))*(gR*gR*gR*gR))*(C46*C46)+2*(gL*gL)*(gR*gR)*C45*(((aZdR*aZdR))*C45)+C35*(4*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C46))*C56+(C36*C36)*((-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*(C45*C45)+2*((aZdR*aZdR))*(gL*gL)*(gR*gR)*C34*C56)+E3456*(2*C36*((ahR*aZdR)*(gL*gL)*(gR*gR)*(MZ*MZ))+(MZ*MZ)*(2*(ahR*aZdR)*(gL*gL)*(gR*gR)*C45-((ahR*(aZdR))*(gL*gL*gL*gL)+(ahR*(aZdR))*(gR*gR*gR*gR))*C46)+C35*(((ahR*(-aZdR))*(gL*gL*gL*gL)-(ahR*(aZdR))*(gR*gR*gR*gR))*(MZ*MZ)))+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)+C35*(-2*(-(aZdR*aZdR))*((gL*gL+gR*gR)*(gL*gL+gR*gR))*C46)-2*(-(aZdR*aZdR))*((gL*gL*gL*gL)+(gR*gR*gR*gR))*C34*C56))))/8192.;
}

double GetGeneralScalar_ahI_ahI(LeptonVectors &leptons, double ahI, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahI*ahI))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_ahI_ahR(LeptonVectors &leptons, double ahI, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahI*ahI)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahI*ahI)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahI*ahI)+(ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

double GetGeneralScalar_ahR_ahR(LeptonVectors &leptons, double ahR, bool UpType)
{
   const double Pi = CONST_PI;
   
   double M1 = (leptons.Lepton11 + leptons.Lepton12).GetMass();
   double M2 = (leptons.Lepton21 + leptons.Lepton22).GetMass();

   const double s = (leptons.Lepton11 + leptons.Lepton12 + leptons.Lepton21 + leptons.Lepton22).GetMass2();
   const double MZ = CONST_MZ;
   const double wZ = CONST_WZ;
   
   const double vh = CONST_VH;
   const double gL = CONST_GL;
   const double gR = CONST_GR;
   const double EE = CONST_EE;
   const double el = -EE;

   FourVector P3 = leptons.Lepton11;
   FourVector P4 = leptons.Lepton12;
   FourVector P5 = leptons.Lepton21;
   FourVector P6 = leptons.Lepton22;

   if(M1 < M2)
   {
      swap(M1, M2);
      swap(P3, P5);
      swap(P4, P6);
   }

   double C34 = P3 * P4;
   double C35 = P3 * P5;
   double C36 = P3 * P6;
   double C45 = P4 * P5;
   double C46 = P4 * P6;
   double C56 = P5 * P6;
   double E3456 = EPS(P3, P4, P5, P6);

   return 0+(pow(Pi,-7)*(1.0/s)*(1/(vh*vh))*pow((1.0/(s*s))*((M1*M1*M1*M1)-2*(M1*M1)*(s+(M2*M2))+((M2*M2-s)*(M2*M2-s))),0.5)*(1.0/((MZ*MZ)*(wZ*wZ)+((M1*M1-MZ*MZ)*(M1*M1-MZ*MZ))))*(1.0/((MZ*MZ)*(wZ*wZ)+((M2*M2-MZ*MZ)*(M2*M2-MZ*MZ))))*((ahR*ahR)*(gL*gL*gL*gL)*(MZ*MZ*MZ*MZ)*C35*C46+(ahR*ahR)*(gR*gR*gR*gR)*(MZ*MZ*MZ*MZ)*C35*C46+C36*(C45*(2*((ahR*ahR))*(gL*gL)*(gR*gR)*(MZ*MZ*MZ*MZ)))))/8192.;
}

