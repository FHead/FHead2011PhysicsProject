{
   Tree->SetAlias("MatchingDEta", "(JetGenEta - JetEta)");
   Tree->SetAlias("MatchingRawDPhi", "(JetGenPhi - JetPhi)");
   Tree->SetAlias("MatchingDPhi", "(MatchingRawDPhi - (MatchingRawDPhi > 3.1415926535) * 2 * 3.1415926535 + (MatchingRawDPhi < -3.1415926535) * 2 * 3.1415926535)");
   Tree->SetAlias("MatchingDR", "sqrt(MatchingDEta * MatchingDEta + MatchingDPhi * MatchingDPhi)");
   
   Tree->SetAlias("SDMatchingDEta", "(JetEta - JetSDEta)");
   Tree->SetAlias("SDMatchingRawDPhi", "(JetPhi - JetSDPhi)");
   Tree->SetAlias("SDMatchingDPhi", "(SDMatchingRawDPhi - (SDMatchingRawDPhi > 3.1415926535) * 2 * 3.1415926535 + (SDMatchingRawDPhi < -3.1415926535) * 2 * 3.1415926535)");
   Tree->SetAlias("SDMatchingDR", "sqrt(SDMatchingDEta * SDMatchingDEta + SDMatchingDPhi * SDMatchingDPhi)");
   
   Tree->SetAlias("JetMatchingDEta", "(JetEta - NewJetEta)");
   Tree->SetAlias("JetMatchingRawDPhi", "(JetPhi - NewJetPhi)");
   Tree->SetAlias("JetMatchingDPhi", "(JetMatchingRawDPhi - (JetMatchingRawDPhi > 3.1415926535) * 2 * 3.1415926535 + (JetMatchingRawDPhi < -3.1415926535) * 2 * 3.1415926535)");
   Tree->SetAlias("JetMatchingDR", "sqrt(JetMatchingDEta * JetMatchingDEta + JetMatchingDPhi * JetMatchingDPhi)");

   Tree->SetAlias("JEC", "JetPT / NewJetPT");

   Tree->SetAlias("Baseline", "MCWeight * (MatchingDR < 0.2 && SDMatchingDR < 0.1 && JetMatchingDR < 0.02)");

   Tree->SetAlias("Region0", "(1*(SDRecoDR[0]<0.1)+2*(SDRecoDR[0]>0.1&&SDMaxDR[0]<SDRecoDR[0]/2)+3*(SDRecoDR[0]>0.1&&SDMaxDR[0]>SDRecoDR[0]/2))");
   Tree->SetAlias("Region7", "(1*(SDRecoDR[7]<0.1)+2*(SDRecoDR[7]>0.1&&SDMaxDR[7]<SDRecoDR[7]/2)+3*(SDRecoDR[7]>0.1&&SDMaxDR[7]>SDRecoDR[7]/2))");

   Tree->SetAlias("Inside0", "(((SDX2[0]-1)*(SDX2[0]-1)+SDY2[0]*SDY2[0] < 4) || ((SDX2[0]+1)*(SDX2[0]+1)+SDY2[0]*SDY2[0] < 4))");
   Tree->SetAlias("Inside7", "(((SDX2[7]-1)*(SDX2[7]-1)+SDY2[7]*SDY2[7] < 4) || ((SDX2[7]+1)*(SDX2[7]+1)+SDY2[7]*SDY2[7] < 4))");

   Tree->SetAlias("AverageGenX0", "((GenSDPT1[0]-GenSDPT2[0])/(GenSDPT1[0]+GenSDPT2[0]))");
   Tree->SetAlias("AverageGenX7", "((GenSDPT1[7]-GenSDPT2[7])/(GenSDPT1[7]+GenSDPT2[7]))");

   Tree->SetAlias("AverageX0", "((SDPT1[0]*SDX1[0]+SDPT2[0]*SDX2[0])/(SDPT1[0]+SDPT2[0]))");
   Tree->SetAlias("AverageY0", "((SDPT1[0]*SDY1[0]+SDPT2[0]*SDY2[0])/(SDPT1[0]+SDPT2[0]))");
   Tree->SetAlias("AverageX7", "((SDPT1[7]*SDX1[7]+SDPT2[7]*SDX2[7])/(SDPT1[7]+SDPT2[7]))");
   Tree->SetAlias("AverageY7", "((SDPT1[7]*SDY1[7]+SDPT2[7]*SDY2[7])/(SDPT1[7]+SDPT2[7]))");

   Tree->SetAlias("SD0R1", "sqrt(SDX1[0]*SDX1[0]+SDY1[0]*SDY1[0])");
   Tree->SetAlias("SD0R2", "sqrt(SDX2[0]*SDX2[0]+SDY2[0]*SDY2[0])");
   Tree->SetAlias("SD7R1", "sqrt(SDX1[7]*SDX1[7]+SDY1[7]*SDY1[7])");
   Tree->SetAlias("SD7R2", "sqrt(SDX2[7]*SDX2[7]+SDY2[7]*SDY2[7])");
}
