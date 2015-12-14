{
   Tree->SetAlias("hpx", "(l1pt * cos(l1phi) + l2pt * cos(l2phi) + l3pt * cos(l3phi) + l4pt * cos(l4phi))");
   Tree->SetAlias("hpy", "(l1pt * sin(l1phi) + l2pt * sin(l2phi) + l3pt * sin(l3phi) + l4pt * sin(l4phi))");
   Tree->SetAlias("hpt", "sqrt(hpx * hpx + hpy * hpy)");
   Tree->SetAlias("hpz", "(l1pt * sinh(l1eta) + l2pt * sinh(l2eta) + l3pt * sinh(l3eta) + l4pt * sinh(l4eta))");
   Tree->SetAlias("he", "(l1pt * cosh(l1eta) + l2pt * cosh(l2eta) + l3pt * cosh(l3eta) + l4pt * cosh(l4eta))");
   Tree->SetAlias("hy", "0.5 * log((he + hpz) / (he - hpz))");
   Tree->SetAlias("HYWeight", "((1.19005e+03 + -2.08029e+02 * hy * hy + 1.15469e+01 * hy * hy * hy * hy + -1.96945e-01 * hy * hy * hy * hy * hy * hy) / 1400)");
   Tree->SetAlias("HPTWeight", "(((-3.38 +hpt * 117.642 -hpt *hpt * 7.454) * 10 / 4276.4 * 4700.68 / 5200) * (hpt < 10) + ((6833 * exp(-0.0385 *hpt) + 57.226 * exp(-0.0112 *hpt)) / 5200) * (hpt > 10))");
   Tree->SetAlias("C", "(qqZZ_LogL_Template2 < 0)");

   Tree->Draw("exp(qqZZ_LogL_Template2)", "C");
   double TAverage = htemp->GetMean();
   Tree->SetAlias("T", Form("(exp(qqZZ_LogL_Template2) / %.10e)", TAverage));

   Tree->Draw("qqZZGenLikelihood / HYWeight / HPTWeight", "C");
   double GAverage = htemp->GetMean();
   Tree->SetAlias("G", Form("(qqZZGenLikelihood / HYWeight / HPTWeight / %.10e)", GAverage));

   Tree->Draw("qqZZGenLikelihood * Efficiency / HYWeight / HPTWeight", "C");
   double AAverage = htemp->GetMean();
   Tree->SetAlias("A", Form("(qqZZGenLikelihood * Efficiency / HYWeight / HPTWeight / %.10e)", AAverage));

   Tree->GetListOfAliases()->Print();
}


