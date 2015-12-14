{
   MCTree->SetAlias("l1px", "(l1pt*cos(l1phi))");
   MCTree->SetAlias("l1py", "(l1pt*sin(l1phi))");
   MCTree->SetAlias("l1pz", "(l1pt*sinh(l1eta))");
   MCTree->SetAlias("l1p", "(l1pt*cosh(l1eta))");
   MCTree->SetAlias("l2px", "(l2pt*cos(l2phi))");
   MCTree->SetAlias("l2py", "(l2pt*sin(l2phi))");
   MCTree->SetAlias("l2pz", "(l2pt*sinh(l2eta))");
   MCTree->SetAlias("l2p", "(l2pt*cosh(l2eta))");
   MCTree->SetAlias("l3px", "(l3pt*cos(l3phi))");
   MCTree->SetAlias("l3py", "(l3pt*sin(l3phi))");
   MCTree->SetAlias("l3pz", "(l3pt*sinh(l3eta))");
   MCTree->SetAlias("l3p", "(l3pt*cosh(l3eta))");
   MCTree->SetAlias("l4px", "(l4pt*cos(l4phi))");
   MCTree->SetAlias("l4py", "(l4pt*sin(l4phi))");
   MCTree->SetAlias("l4pz", "(l4pt*sinh(l4eta))");
   MCTree->SetAlias("l4p", "(l4pt*cosh(l4eta))");
   MCTree->SetAlias("hpx", "(l1px+l2px+l3px+l4px)");
   MCTree->SetAlias("hpy", "(l1py+l2py+l3py+l4py)");
   MCTree->SetAlias("hpz", "(l1pz+l2pz+l3pz+l4pz)");
   MCTree->SetAlias("he", "(l1p+l2p+l3p+l4p)");
   MCTree->SetAlias("hpt", "sqrt(hpx*hpx+hpy*hpy)");
   MCTree->SetAlias("hp", "sqrt(hpx*hpx+hpy*hpy+hpz*hpz)");
   MCTree->SetAlias("hm", "sqrt(he*he-hp*hp)");
   MCTree->SetAlias("hy", "-0.5*log((he-hpz)/(he+hpz))");
}





