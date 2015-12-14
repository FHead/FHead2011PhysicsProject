{
   Tree->SetAlias("L1P", "(L1PT * cosh(L1Eta))");
   Tree->SetAlias("L2P", "(L2PT * cosh(L2Eta))");
   Tree->SetAlias("L3P", "(L3PT * cosh(L3Eta))");
   Tree->SetAlias("L4P", "(L4PT * cosh(L4Eta))");
   Tree->SetAlias("Cut", "(Weight[0][0] * (L1P < 100 && L2P < 100 && L3P < 100 && L4P < 100 && MH > 100 && MH < 140 && M1 > 4 && M2 > 4 && M1 < 100 && M2 < 100))");
}
