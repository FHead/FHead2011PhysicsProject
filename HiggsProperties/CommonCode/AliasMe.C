void AliasMeLowerCase(TTree *Tree)
{
   Tree->SetAlias("l1px", "(l1pt*cos(l1phi))");
   Tree->SetAlias("l1py", "(l1pt*sin(l1phi))");
   Tree->SetAlias("l1pz", "(l1pt*sinh(l1eta))");
   Tree->SetAlias("l1p", "(l1pt*cosh(l1eta))");
   Tree->SetAlias("l2px", "(l2pt*cos(l2phi))");
   Tree->SetAlias("l2py", "(l2pt*sin(l2phi))");
   Tree->SetAlias("l2pz", "(l2pt*sinh(l2eta))");
   Tree->SetAlias("l2p", "(l2pt*cosh(l2eta))");
   Tree->SetAlias("l3px", "(l3pt*cos(l3phi))");
   Tree->SetAlias("l3py", "(l3pt*sin(l3phi))");
   Tree->SetAlias("l3pz", "(l3pt*sinh(l3eta))");
   Tree->SetAlias("l3p", "(l3pt*cosh(l3eta))");
   Tree->SetAlias("l4px", "(l4pt*cos(l4phi))");
   Tree->SetAlias("l4py", "(l4pt*sin(l4phi))");
   Tree->SetAlias("l4pz", "(l4pt*sinh(l4eta))");
   Tree->SetAlias("l4p", "(l4pt*cosh(l4eta))");
   Tree->SetAlias("hpx", "(l1px+l2px+l3px+l4px)");
   Tree->SetAlias("hpy", "(l1py+l2py+l3py+l4py)");
   Tree->SetAlias("hpz", "(l1pz+l2pz+l3pz+l4pz)");
   Tree->SetAlias("he", "(l1p+l2p+l3p+l4p)");
   Tree->SetAlias("hpt", "sqrt(hpx*hpx+hpy*hpy)");
   Tree->SetAlias("hp", "sqrt(hpx*hpx+hpy*hpy+hpz*hpz)");
   Tree->SetAlias("hm", "sqrt(he*he-hp*hp)");
   Tree->SetAlias("hy", "-0.5*log((he-hpz)/(he+hpz))");
}





