{
   T2->SetAlias("L1Px", "(L1PT*cos(L1Phi))");
   T2->SetAlias("L1Py", "(L1PT*sin(L1Phi))");
   T2->SetAlias("L1Pz", "(L1PT*sinh(L1Eta))");
   T2->SetAlias("L1E",  "(L1PT*cosh(L1Eta))");
   T2->SetAlias("L2Px", "(L2PT*cos(L2Phi))");
   T2->SetAlias("L2Py", "(L2PT*sin(L2Phi))");
   T2->SetAlias("L2Pz", "(L2PT*sinh(L2Eta))");
   T2->SetAlias("L2E",  "(L2PT*cosh(L2Eta))");
   T2->SetAlias("L3Px", "(L3PT*cos(L3Phi))");
   T2->SetAlias("L3Py", "(L3PT*sin(L3Phi))");
   T2->SetAlias("L3Pz", "(L3PT*sinh(L3Eta))");
   T2->SetAlias("L3E",  "(L3PT*cosh(L3Eta))");
   T2->SetAlias("L4Px", "(L4PT*cos(L4Phi))");
   T2->SetAlias("L4Py", "(L4PT*sin(L4Phi))");
   T2->SetAlias("L4Pz", "(L4PT*sinh(L4Eta))");
   T2->SetAlias("L4E",  "(L4PT*cosh(L4Eta))");

   T2->SetAlias("Z1Px", "(L1Px+L2Px)");
   T2->SetAlias("Z1Py", "(L1Py+L2Py)");
   T2->SetAlias("Z1Pz", "(L1Pz+L2Pz)");
   T2->SetAlias("Z1E",  "(L1E+L2E)");
   T2->SetAlias("Z2Px", "(L3Px+L4Px)");
   T2->SetAlias("Z2Py", "(L3Py+L4Py)");
   T2->SetAlias("Z2Pz", "(L3Pz+L4Pz)");
   T2->SetAlias("Z2E",  "(L3E+L4E)");

   T2->SetAlias("HPx", "(Z1Px+Z2Px)");
   T2->SetAlias("HPy", "(Z1Py+Z2Py)");
   T2->SetAlias("HPz", "(Z1Pz+Z2Pz)");
   T2->SetAlias("HE", "(Z1E+Z2E)");

   T2->SetAlias("HM", "sqrt(HE*HE-HPx*HPx-HPy*HPy-HPz*HPz)");
   T2->SetAlias("Z1M", "sqrt(Z1E*Z1E-Z1Px*Z1Px-Z1Py*Z1Py-Z1Pz*Z1Pz)");
   T2->SetAlias("Z2M", "sqrt(Z2E*Z2E-Z2Px*Z2Px-Z2Py*Z2Py-Z2Pz*Z2Pz)");

   T2->SetMarkerStyle(20);
}
