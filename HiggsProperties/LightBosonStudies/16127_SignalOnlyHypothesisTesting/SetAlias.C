{
   Tree->SetAlias("L1Px", "(L1PT*cos(L1Phi))");
   Tree->SetAlias("L1Py", "(L1PT*sin(L1Phi))");
   Tree->SetAlias("L1Pz", "(L1PT*sinh(L1Eta))");
   Tree->SetAlias("L1E",  "(L1PT*cosh(L1Eta))");
   Tree->SetAlias("L2Px", "(L2PT*cos(L2Phi))");
   Tree->SetAlias("L2Py", "(L2PT*sin(L2Phi))");
   Tree->SetAlias("L2Pz", "(L2PT*sinh(L2Eta))");
   Tree->SetAlias("L2E",  "(L2PT*cosh(L2Eta))");
   Tree->SetAlias("L3Px", "(L3PT*cos(L3Phi))");
   Tree->SetAlias("L3Py", "(L3PT*sin(L3Phi))");
   Tree->SetAlias("L3Pz", "(L3PT*sinh(L3Eta))");
   Tree->SetAlias("L3E",  "(L3PT*cosh(L3Eta))");
   Tree->SetAlias("L4Px", "(L4PT*cos(L4Phi))");
   Tree->SetAlias("L4Py", "(L4PT*sin(L4Phi))");
   Tree->SetAlias("L4Pz", "(L4PT*sinh(L4Eta))");
   Tree->SetAlias("L4E",  "(L4PT*cosh(L4Eta))");

   Tree->SetAlias("Z1Px", "(L1Px+L2Px)");
   Tree->SetAlias("Z1Py", "(L1Py+L2Py)");
   Tree->SetAlias("Z1Pz", "(L1Pz+L2Pz)");
   Tree->SetAlias("Z1E",  "(L1E+L2E)");
   Tree->SetAlias("Z2Px", "(L3Px+L4Px)");
   Tree->SetAlias("Z2Py", "(L3Py+L4Py)");
   Tree->SetAlias("Z2Pz", "(L3Pz+L4Pz)");
   Tree->SetAlias("Z2E",  "(L3E+L4E)");

   Tree->SetAlias("HPx", "(Z1Px+Z2Px)");
   Tree->SetAlias("HPy", "(Z1Py+Z2Py)");
   Tree->SetAlias("HPz", "(Z1Pz+Z2Pz)");
   Tree->SetAlias("HE", "(Z1E+Z2E)");

   Tree->SetAlias("HM", "sqrt(HE*HE-HPx*HPx-HPy*HPy-HPz*HPz)");
   Tree->SetAlias("Z1M", "sqrt(Z1E*Z1E-Z1Px*Z1Px-Z1Py*Z1Py-Z1Pz*Z1Pz)");
   Tree->SetAlias("Z2M", "sqrt(Z2E*Z2E-Z2Px*Z2Px-Z2Py*Z2Py-Z2Pz*Z2Pz)");

   Tree->SetMarkerStyle(20);
}
