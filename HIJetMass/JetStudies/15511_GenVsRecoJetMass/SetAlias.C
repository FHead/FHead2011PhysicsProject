{
   t->SetAlias("deta", "(jteta-refetaG)");
   t->SetAlias("dphiraw", "(jtphi-refphiG)");
   t->SetAlias("dphi", "(dphiraw-2*3.14159*(dphiraw>3.14159)+2*3.14159*(dphiraw<-3.14159))");
   t->SetAlias("dr", "sqrt(dphi*dphi+deta*deta)");
}
